# Basics

## Docker
### Install docker
sudo apt install docker.io

### Setup docker
sudo groupadd docker
sudo usermod -aG docker ${USER}
#### Test setup
su -s ${USER}

### Test docker
docker run hello-world

## Images
### Get the image
docker pull python  
As docker shares OS kernels, it will be linux as well.

### List all local images
docker images

### Remove images
docker image rm 

## Containers
### Run a container
docker run --name myPython -it python:latest /bin/bash  
1. -it: interactive container with a terminal  

docker run --name daemon -d ubuntu /bin/sh -c "while true; do echo hello world; sleep 1; done"  
run a container on background

docker start myPython  
run an existing container by name

### Stop a container
docker stop myPython  

### Remove a container
docker rm myPython

### List all containers
docker ps -a  

### Exit a container
exit

### Check logs without entering
docker logs -f -t --tail 30 container_name

### Enter into a container running in background
docker attach myPython

## Volumes
A directory to be mounted to a container
### Create a volume
docker volume create --name test_volume

### List all volume
docker volume ls

### Inspect a volume
docker volume inspect test_volume

### Delete a volume
docker volume rm test_volume


## Dockerfile
A script to build a container

### Keywords:
CMD: Default command to run just after a container has started. (Can be overridden by docker run)  
ENTRYPOINT: Default command to run just after a container has started. (CANNOT be overidden by docker run)  
 


## Docker compose
A script of "docker run" for several containers which collabrate with each other

### Install
sudo curl -L "https://github.com/docker/compose/releases/download/1.25.5/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose  
sudo chmod +x /usr/local/bin/docker-compose  
sudo ln -s /usr/local/bin/docker-compose /usr/bin/docker-compose  

### Common steps:
1. build docker image with Dockerfile
2. start service with docker-compose

### Keywords
services： 即我们要开始定义服务，每个docker容器为一个服务。  
app： 这里我们定义了第一个服务，app 为其名字  
build: build an image with Dockerfile in the provided path  
image: use directly an image  
expose: Expose ports WITHOUT publishing them to the host machine  
ports: Expose ports WITH publishing them to the host machine  
env_file: Set the environment variables for a container  
command: Default command to run just after a container has started. (CMD in Dockerfile)  


#### Build
CONTEXT: Either a path to a directory containing a Dockerfile, or a url to a git repository.
DOCKERFILE: Alternate Dockerfile.
ARGS: Define environment variables

### Build & start
docker-compose build: build image with predefined scripts
docker-compose up -d: Create and start containers, leave them background running
docker-compose up -d --build: execute the above two commands

### Execute a command in a container
docker-compose exec containerName COMMAND

### Stop and remove
docker-compose down -v

# Examples
## Docker with Nginx
1. Prepare a webpage, such as index.html:
<html>
    <body>
        <h1>Hello from Docker container!</h1>
        <ul>
            <li>Change this line and have a look.</li>
        </ul>
    </body>
</html>

2. run -d --name "test-nginx" -p 8080:80 -v $(pwd):/usr/share/nginx/html:ro nginx:latest
-p: map host 8080 port to docker 80 port  
-v: mount current directory (which contains the index.html) to /usr/share/nginx/html inside docker

3. visit http://127.0.0.1:8080/ from host machine


## Docker with flask

## More on: https://djangostars.com/blog/what-is-docker-and-how-to-use-it-with-python/

## Docker with flask Ngix
https://testdriven.io/blog/dockerizing-flask-with-postgres-gunicorn-and-nginx/
