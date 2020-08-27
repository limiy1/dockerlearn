# pull official base image
FROM python:3.8.1-slim-buster

# set environment variables
ENV PYTHONDONTWRITEBYTECODE 1
ENV PYTHONUNBUFFERED 1

# install system dependencies
RUN apt-get update && apt-get install -y netcat build-essential cmake wget

# install dependencies
RUN pip install --upgrade pip
COPY ./requirements.txt /usr/src/app/requirements.txt
RUN pip install -r /usr/src/app/requirements.txt

# copy project
WORKDIR /usr/src/app
COPY ./entrypoint.sh /usr/src/app/entrypoint.sh
COPY ./manage.py /usr/src/app/manage.py
COPY ./project /usr/src/app/project

# install rdkafka
WORKDIR /usr/src/kafka
RUN wget --no-check-certificate --content-disposition https://github.com/edenhill/librdkafka/archive/v1.5.0.tar.gz
RUN tar -xf librdkafka-1.5.0.tar.gz
WORKDIR /usr/src/kafka/librdkafka-1.5.0
RUN ./configure --prefix /usr
RUN make && make install

# copy and build c-source code
WORKDIR /usr/src/c/
COPY ./sourceCode/* ./
RUN cmake . && make

# run entrypoint.sh
WORKDIR /usr/src/app
ENTRYPOINT ["/usr/src/app/entrypoint.sh"]
