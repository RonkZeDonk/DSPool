#!/usr/bin/env bash

if [ ! "$(docker ps -a -q -f name=dkp)" ]; then
    echo Starting docker build environment...
    docker run --rm -dit -u $(id -u):$(id -g) -v $PWD:/src --name dkp devkitpro/devkitarm:20240918

    if [ ! -d "$PWD/devkitpro" ]; then
        echo "Copying dkp folder to $PWD for headers (check compile_flags.txt for include locations)"
        docker cp dkp:/opt/devkitpro devkitpro
    fi
else
    echo "couldn't create container; a container with name 'dkp' already exists!"
fi

echo
echo "Run commands within the container with 'docker exec -w /src dkp <COMMAND>'"
echo "For example: run 'make' with 'docker exec -w /src dkp make'"
