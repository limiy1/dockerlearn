# pull official base image
FROM python:3.8.1-slim-buster

# set environment variables
ENV PYTHONDONTWRITEBYTECODE 1
ENV PYTHONUNBUFFERED 1

# install system dependencies
RUN apt-get update && apt-get install -y netcat build-essential cmake

# install dependencies
RUN pip install --upgrade pip
COPY ./requirements.txt /usr/src/app/requirements.txt
RUN pip install -r /usr/src/app/requirements.txt

# copy and build c-source code
WORKDIR /usr/src/c/
COPY ./sourceCode/* ./
RUN cmake . && make

# copy project
WORKDIR /usr/src/app
COPY ./entrypoint.sh /usr/src/app/entrypoint.sh
COPY ./manage.py /usr/src/app/manage.py
COPY ./project /usr/src/app/project

# run entrypoint.sh
ENTRYPOINT ["/usr/src/app/entrypoint.sh"]
