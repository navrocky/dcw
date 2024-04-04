#!/bin/bash

IMAGE_NAME=dcw-build

docker build --progress=plain --tag ${IMAGE_NAME} -f Dockerfile.uclibc .

id=$(docker create ${IMAGE_NAME})
mkdir -p dist
docker cp $id:/build/cli/dcw ./dist/
docker rm -v $id
