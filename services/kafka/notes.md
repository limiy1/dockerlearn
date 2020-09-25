# Authentication
https://docs.confluent.io/3.0.0/kafka/sasl.html  
Can be SSL and SASL/SCRAM  

## SARL/SCRAM
Credentials can be created in Zookeeper using kafka-configs  

### Add users
docker exec dockerlearn_zookeeper_1 kafka-configs --zookeeper localhost:2181 --alter --add-config 'SCRAM-SHA-256=[password=admin-secret]' --entity-type users --entity-name admin

### Describe users
docker exec dockerlearn_zookeeper_1 kafka-configs --zookeeper localhost:2181 --entity-type users --entity-name alice --describe


## SASL/PLAIN_TEXT
Use jaas file to config: kafka_server_jaas.conf
https://blog.csdn.net/zhangshenghang/article/details/90264636  
https://docs.vmware.com/en/VMware-Smart-Assurance/10.1.0/sa-ui-installation-config-guide-10.1.0/GUID-3E473EC3-732A-4963-81BD-13BCCD3AC700.html

## SASL/SSL
https://docs.vmware.com/en/VMware-Smart-Assurance/10.1.0/sa-ui-installation-config-guide-10.1.0/GUID-DF659094-60D3-4E1B-8D63-3DE3ED8B0EDF.html

# Authorization (ACL)
Control which user can do what

## Add ACLs:

### Admin user
docker exec dockerlearn_kafka_1 kafka-acls --bootstrap-server localhost:9094 --command-config /var/ssl/adminconfig.properties  --add --allow-principal User:admin  --operation All --topic '*' --cluster

### Singler operation
docker exec dockerlearn_kafka_1 kafka-acls --bootstrap-server localhost:9094 --command-config /var/ssl/adminconfig.properties  --add --allow-principal User:mike  --operation Read --topic 'test_topic'

### Consumer
docker exec dockerlearn_kafka_1 kafka-acls --bootstrap-server localhost:9094 --command-config /var/ssl/adminconfig.properties  --add --allow-principal User:mike --consumer --topic 'test_topic' --group 'rmoff'

## List existing ACLs:
docker exec dockerlearn_kafka_1 kafka-acls --bootstrap-server localhost:9094 --command-config /var/ssl/adminconfig.properties --list --topic test_topic --resource-pattern-type match



## List users
bin/kafka-configs.sh --zookeeper 172.21.0.9:2181 --describe --entity-type users --entity-name writer  

# General Configuration
## Broker Files
server.properties: able to use enviroment variable to config at /opt/kafka_2.12-2.5.0/config/server.properties, or /etc/kafka/server.properties
producer.properties:   
consumer.properties:   

## Zookeeper files
 /opt/zookeeper-3.4.13/conf/zoo.cfg


## Message size (broker, producer)

## Partition
Different partition of the same topic contains different messages. We can use more consumers to consume them in parallel.


# Connections
https://www.confluent.io/blog/kafka-client-cannot-connect-to-broker-on-aws-on-docker-etc/
