wget https://git.cryptomilk.org/projects/cmocka.git/snapshot/cmocka-1.0.1.tar.gz
tar -xvf cmocka-1.0.1.tar.gz
cd cmocka-1.0.1
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release ..
make
sudo make install