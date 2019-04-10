# Run in docker

Simple and fast setup of FSC.IO on Docker is also available.

## Install Dependencies

- [Docker](https://docs.docker.com) Docker 17.05 or higher is required
- [docker-compose](https://docs.docker.com/compose/) version >= 1.10.0

## Docker Requirement

- At least 7GB RAM (Docker -> Preferences -> Advanced -> Memory -> 7GB or above)
- If the build below fails, make sure you've adjusted Docker Memory settings and try again.

## Build fsc base environment image

```bash
git clone https://dockerbuild:dockerbuild@github.com/FutureSharesCloud/fsc.git  --depth 1
git checkout devlop origin/devlop
cd fsc/Docker/dev-gitlab/builder
docker build . -t fscio/builder
```
## Build fsc devlop environment image

```bash
git clone https://dockerbuild:dockerbuild@github.com/FutureSharesCloud/fsc.git 
git checkout devlop origin/devlop
cd fsc/Docker/dev-gitlab
```
If you would like to target a specific branch/tag, you may use a build argument. For example, if you wished to generate a docker image based off of the 1.6.1 tag, you could do the following:
```
docker build -t fscio/fsc --build-arg branch=devlop  --build-arg symbol=FSC  --build-arg  gitlabAuthentication=<username:passwd> .
```

## Start nodfsc docker container only

```bash
docker run --name nodfsc -p 8888:8888 -p 9876:9876 -t fscio/fsc nodfscd.sh -e --http-alias=nodfsc:8888 --http-alias=127.0.0.1:8888 --http-alias=localhost:8888 arg1 arg2
```

Enjoy it, guys!
