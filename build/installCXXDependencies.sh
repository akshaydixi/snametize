#!/bin/sh

echo "deb http://archive.ubuntu.com/ubuntu/ trusty main restricted" | sudo tee -a /etc/apt/sources.list
sudo apt-get update -qq
sudo apt-get install -qq libboost-program-options-dev g++-4.8 make cmake
