#!/bin/bash

cd src
make -j
stat_make=$?

make install
stat_install=$?
make clean 
stat_clean=$?

cd ../bin
./install.sh
stat_install_config=$?
cd ..

echo "========================================"
echo " RESULTS "
echo "make        : ${stat_make}"
echo "make install: ${stat_install}"
echo "make clean  : ${stat_clean}"
echo "install.sh  : ${stat_install_config}"
echo 
echo "where 0 means OK"
echo "========================================"
