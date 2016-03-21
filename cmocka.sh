#!/bin/bash
sudo apt-get install cmake -y --force-yes

cd lib/cmocka-1.0.1
rm -Rf build
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release ..
make
sudo make install
cd ../../..