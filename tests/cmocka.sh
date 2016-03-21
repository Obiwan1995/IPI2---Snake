#!/bin/bash
sudo apt-get install cmake -y --force-yes

cd tests/cmocka-1.0.1
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release ..
make
sudo make install
cd ../../..