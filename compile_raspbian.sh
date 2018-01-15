#!/bin/bash

#Install dependencies
sudo apt-get update
sudo apt-get upgrade

sudo apt-get install build-essential libtool automake autotools-dev autoconf pkg-config libssl-dev libgmp3-dev libevent-dev bsdmainutils libboost-system-dev libboost-filesystem-dev libboost-chrono-dev libboost-program-options-dev libboost-test-dev libboost-thread-dev libboost-all-dev git libdb++-dev

sudo add-apt-repository ppa:bitcoin/bitcoin
sudo apt-get update
sudo apt-get install libdb4.8-dev libdb4.8++-dev

#For QT magnet version
sudo apt-get install libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler

#Get magnet source code
git clone https://github.com/magnetwork/magnet.git

#Compiling magnetd (CLI)
cd magnet 
chmod +x src/leveldb/build_detect_platform 
chmod +x src/secp256k1/autogen.sh
cd src/leveldb
make libleveldb.a libmemenv.a
cd .. 
make -f makefile.unix && strip magnetd

#Compiling QT version (GUI)
cd ../
qmake -qt=qt5 USE_UPNP=- 
make
