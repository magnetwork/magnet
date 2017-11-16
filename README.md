
MAGNET is a X11 POS/POW + Masternodes Network.

MAGNET uses libsecp256k1,
			  libgmp,
			  Boost1.55,
			  OR Boost1.57,  
			  Openssl1.01p,
			  Berkeley DB 4.8,
			  QT5 to compile


Block Spacing: 60 Seconds
Stake Minimum Age: 24 Hours

Port: 17177
RPC Port: 17178


BUILD LINUX
-----------
1) git clone https://github.com/magnetwork/magnet.git MAGNET

2) cd MAGNET/src/leveldb

3) make libleveldb.a libmemenv.a

(check permissions if any error)

4) cd ..

5) sudo make -f makefile.unix            # Headless magnet

(optional)

6) strip magnetd

7) sudo cp magnetd /usr/local/bin




BUILD WINDOWS
-------------

1) Download Qt from https://download.qt.io/archive/qt/ and install

2) Download Magnet source from https://github.com/magnetwork/magnet/archive/master.zip 

2.1) Unpack to C:/magnet

3) Install Perl for windows from the homepage http://www.activestate.com/activeperl/downloads

4) Download Python 2.7 https://www.python.org/downloads/windows/

4.1) While installing python make sure to add python.exe to the path.

5) Run msys.bat located in C:\MinGW49-32\msys\1.0

6) cd /C/magnet/src/leveldb

7) Type "TARGET_OS=NATIVE_WINDOWS make libleveldb.a libmemenv.a" and hit enter to build leveldb

8) Exit msys shell

9) Open windows command prompt

10) cd C:/dev

11) Type "49-32-qt5.bat" and hit enter to run

12) cd ../magnet

13) Type "qmake USE_UPNP=0" and hit enter to run

14) Type "mingw32-make" and hit enter to start building. When it's finished you can find your .exe in the release folder.
