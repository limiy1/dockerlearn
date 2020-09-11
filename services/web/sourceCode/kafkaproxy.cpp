#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <csignal>
#include <cstring>
  
#include "librdkafka/rdkafkacpp.h"  

extern "C"{
	int sendMessage(const char* iBroker, const char* iTopic, const char* iMsg);
}

class ExampleDeliveryReportCb : public RdKafka::DeliveryReportCb {
public:
	static const int kDELIVERY_STATUS_UNKNOWN = 0;
	static const int kDELIVERY_STATUS_SUCCESS = 1;
	static const int kDELIVERY_STATUS_FAIL    = 2;
	int _deliverStatus = ExampleDeliveryReportCb::kDELIVERY_STATUS_UNKNOWN;
	void dr_cb (RdKafka::Message &message) {
		/* If message.err() is non-zero the message delivery failed permanently
	     * for the message. */
		if (message.err()){
			std::cout << "% Message delivery failed: " << message.errstr() << std::endl;
			_deliverStatus = kDELIVERY_STATUS_FAIL;
		} else {
			std::cout << "% Message delivered to topic " << message.topic_name() << " [" << message.partition() << "] at offset " << message.offset() << std::endl;
			_deliverStatus = kDELIVERY_STATUS_SUCCESS;
		}
	}
};

int sendMessage(const char* iBroker, const char* iTopic, const char* iMsg){  
    printf("Hello kafka :) \n");

    if (iMsg == NULL) return ExampleDeliveryReportCb::kDELIVERY_STATUS_FAIL;
    std::string topic(iTopic ? iTopic : "test_kafkacpp");
    std::string broker(iBroker ? iBroker : "kafka:9092");
    std::string message(iMsg);
    
    /*
     * Create configuration object
     */
    RdKafka::Conf *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);

    std::string errstr;

    /* Set bootstrap broker(s) as a comma-separated list of
     * host or host:port (default port 9092).
     * librdkafka will use the bootstrap brokers to acquire the full
     * set of brokers from the cluster. */
    if (conf->set("bootstrap.servers", broker.c_str(), errstr) !=
        RdKafka::Conf::CONF_OK) {
      std::cerr << errstr << std::endl;
      exit(1);
    }
    
    
    /* Set the delivery report callback. */
    ExampleDeliveryReportCb ex_dr_cb;

    if (conf->set("dr_cb", &ex_dr_cb, errstr) != RdKafka::Conf::CONF_OK) {
      std::cerr << errstr << std::endl;
      exit(1);
    }
    
    /*
     * Create producer instance.
     */
    RdKafka::Producer *producer = RdKafka::Producer::create(conf, errstr);
    if (!producer) {
      std::cerr << "Failed to create producer: " << errstr << std::endl;
      exit(1);
    }

    delete conf;
    
    
    /* Push the message to broker asyn */

    /*
     * Send/Produce message.
     * This is an asynchronous call, on success it will only
     * enqueue the message on the internal producer queue.
     * The actual delivery attempts to the broker are handled
     * by background threads.
     * The previously registered delivery report callback
     * is used to signal back to the application when the message
     * has been delivered (or failed permanently after retries).
     */
    bool retry = false;
    do {
      RdKafka::ErrorCode err =
        producer->produce(
                          /* Topic name */
                          topic.c_str(),
                          /* Any Partition: the builtin partitioner will be
                           * used to assign the message to a topic based
                           * on the message key, or random partition if
                           * the key is not set. */
                          RdKafka::Topic::PARTITION_UA,
                          /* Make a copy of the value */
                          RdKafka::Producer::RK_MSG_COPY /* Copy payload */,
                          /* Value */
                          const_cast<char *>(message.c_str()), message.size(),
                          /* Key */
                          NULL, 0,
                          /* Timestamp (defaults to current time) */
                          0,
                          /* Message headers, if any */
                          NULL,
                          /* Per-message opaque value passed to
                           * delivery report */
                          NULL);

      if (err != RdKafka::ERR_NO_ERROR) {
        std::cout << "% Failed to produce to topic " << topic << ": " <<
          RdKafka::err2str(err) << std::endl;

        if (err == RdKafka::ERR__QUEUE_FULL) {
          /* If the internal queue is full, wait for
           * messages to be delivered and then retry.
           * The internal queue represents both
           * messages to be sent and messages that have
           * been sent or failed, awaiting their
           * delivery report callback to be called.
           *
           * The internal queue is limited by the
           * configuration property
           * queue.buffering.max.messages */
          producer->poll(1000/*block for max 1000ms*/);
          retry = true;
        }
      } else {
        std::cout << "% Enqueued message (" << message.size() << " bytes) " <<
          "for topic " << topic << std::endl;
      }

      /* A producer application should continually serve
       * the delivery report queue by calling poll()
       * at frequent intervals.
       * Either put the poll call in your main loop, or in a
       * dedicated thread, or call it after every produce() call.
       * Just make sure that poll() is still called
       * during periods where you are not producing any messages
       * to make sure previously produced messages have their
       * delivery report callback served (and any other callbacks
       * you register). */
      producer->poll(0);
    } while(retry);
    
    producer->flush(1000);
    
    return ex_dr_cb._deliverStatus;
}
