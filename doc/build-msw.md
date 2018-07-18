Copyright (c) 2009-2012 Bitcoin Developers
Distributed under the MIT/X11 software license, see the accompanying
file license.txt or http://www.opensource.org/licenses/mit-license.php.
This product includes software developed by the OpenSSL Project for use in
the OpenSSL Toolkit (http://www.openssl.org/).  This product includes
cryptographic software written by Eric Young (eay@cryptsoft.com) and UPnP
software written by Thomas Bernard.


See readme-qt.rst for instructions on building Magnet QT, the
graphical user interface.

CURRENT WINDOWS BUILD
===================

Compilers Supported
-------------------
Releases are cross-compiled under linux using MXE (M cross environment) http://mxe.cc

Script
------------
#!/bin/bash
export PATH=/home/mnt/mxe/usr/bin:$PATH

MXE_INCLUDE_PATH=/home/mnt/mxe/usr/i686-w64-mingw32.static/include
MXE_LIB_PATH=/home/mnt/mxe/usr/i686-w64-mingw32.static/lib

i686-w64-mingw32.static-qmake-qt5 \
    BOOST_LIB_SUFFIX=-mt \
    BOOST_THREAD_LIB_SUFFIX=_win32-mt \
    BOOST_INCLUDE_PATH=$MXE_INCLUDE_PATH/boost \
    BOOST_LIB_PATH=$MXE_LIB_PATH \
    OPENSSL_INCLUDE_PATH=$MXE_INCLUDE_PATH/openssl \
    OPENSSL_LIB_PATH=$MXE_LIB_PATH \
    BDB_INCLUDE_PATH=$MXE_INCLUDE_PATH \
    BDB_LIB_PATH=$MXE_LIB_PATH \
    MINIUPNPC_INCLUDE_PATH=$MXE_INCLUDE_PATH \
    MINIUPNPC_LIB_PATH=$MXE_LIB_PATH \
    SECP256K1_LIB_PATH=/home/mnt/magnet/src/secp256k1/lib \
    SECP256K1_INCLUDE_PATH=/home/mnt/magnet/src/secp256k1/include \
    QMAKE_LRELEASE=/home/mnt/mxe/usr/i686-w64-mingw32.static/qt5/bin/lrelease magnet.pro

make -f Makefile.Release

OLDER BUILD (UNTESTED FOR MAGNET)
===================

Dependencies
------------
Libraries you need to download separately and build:

                default path               download
OpenSSL         \openssl-1.0.1p-mgw        http://www.openssl.org/source/
Berkeley DB     \db-4.8.30.NC-mgw          http://www.oracle.com/technology/software/products/berkeley-db/index.html
Boost           \boost-1.57.0-mgw          http://www.boost.org/users/download/
miniupnpc       \miniupnpc-1.6-mgw         http://miniupnp.tuxfamily.org/files/
Secp256k1       \secp256k1                 https://github.com/bitcoin/secp256k1

Their licenses:
OpenSSL        Old BSD license with the problematic advertising requirement
Berkeley DB    New BSD license with additional requirement that linked software must be free open source
Boost          MIT-like license
miniupnpc      New (3-clause) BSD license
Secp256k1

Versions used in this release:
OpenSSL      1.0.1p
Berkeley DB  4.8.30.NC
Boost        1.57.0
miniupnpc    1.6
Secp256k1    


OpenSSL
-------
MSYS magnet:
un-tar sources with MSYS 'tar xfz' to avoid issue with symlinks (OpenSSL ticket 2377)
change 'MAKE' env. variable from 'C:\MinGW32\bin\mingw32-make.exe' to '/c/MinGW32/bin/mingw32-make.exe'

cd /c/dev/coindeps32/openssl-1.0.1p-mgw
./config
make

Berkeley DB
-----------
MSYS magnet:

    cd /c/dev/coindeps32/db-4.8.30.NC-mgw/build_unix
    sh ../dist/configure --enable-mingw --enable-cxx
    make

Boost
-----
DOS prompt:

    downloaded boost jam 3.1.18
    cd \dev\coindeps32\boost-1.57.0-mgw
    bjam toolset=gcc --build-type=complete stage

Secp256k1
-----------
MSYS magnet:

    ./autogen.sh
    ./configure --enable-module-recovery --prefix /c/dev/coindeps32/Secp256k1
    make
    make install

MiniUPnPc
---------
UPnP support is optional, make with USE_UPNP= to disable it.

MSYS magnet:

    cd /c/miniupnpc-1.6-mgw
    make -f Makefile.mingw
    mkdir miniupnpc
    cp *.h miniupnpc/

Build Magnetd
-------
DOS prompt:

    cd \magnet\src
    mingw32-make -f makefile.mingw
    strip magnetd.exe
