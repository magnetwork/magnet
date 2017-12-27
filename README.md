
MAGNET is a X11 POS/POW + Masternodes Network.
http://magnetwork.io

Block Spacing: 90 Seconds
Stake Minimum Age: 24 Hours
Stake Maximum Age: 48 Days

Masternode Port: 17177

LINUX BUILD (magnetd)
===========================

Dependencies Installation (Ubuntu & Debian)
-------------------------------------------

Build requirements:

    sudo apt-get install build-essential libtool automake autotools-dev autoconf pkg-config libssl-dev libgmp3-dev libevent-dev bsdmainutils
    
All boost development packages:
    
    sudo apt-get install libboost-all-dev    

BerkeleyDB is required for the wallet. db4.8 packages are available [here](https://launchpad.net/~bitcoin/+archive/bitcoin).
You can add the repository and install using the following commands:

    sudo add-apt-repository ppa:bitcoin/bitcoin
    sudo apt-get update
    sudo apt-get install libdb4.8-dev libdb4.8++-dev
    
 miniupnpc for UPnP Support:

    sudo apt-get install libminiupnpc-dev
    
    
Build magnetd
-------------

If all dependencies are met, you can run the following command to build magnetd:

    git clone https://github.com/magnetwork/magnet.git && \
    cd magnet && \
    chmod +x src/leveldb/build_detect_platform && \
    chmod +x src/secp256k1/autogen.sh && \
    cd src/leveldb && \
    make libleveldb.a libmemenv.a && \
    cd .. && \
    make -f makefile.unix && strip magnetd
    
Or with script:    
    
    git clone https://github.com/magnetwork/magnet.git && \
    cd magnet && \
    chmod +x compile.sh && \
    ./compile.sh
