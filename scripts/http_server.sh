#!/bin/bash

SERVER_ROOT=./coverage

if [ "$1" == "start" ];then
    if [ -f "scripts/pid" ];then
        echo "already got one want another?"
    else
        python3 -m http.server --directory $SERVER_ROOT &
        echo $! >> ./scripts/pid
    fi
fi

if [ "$1" == "stop" ];then
    if [ -f "./scripts/pid" ];then
        kill $(cat ./scripts/pid)
        rm -rf ./scripts/pid
    fi
fi