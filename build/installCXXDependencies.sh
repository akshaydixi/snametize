#!/bin/sh

sudo apt-get install software-properties-common python-software-properties
sudo apt-get-repository "deb http://archive.ubuntu.com/ubuntu/ trusty main restricted" -y
sudo apt-get update -qq
sudo apt-get install -qq libboost-program-options-dev gcc-4.8 make cmake
