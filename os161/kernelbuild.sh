#!/bin/bash

cd ~/ece344/os161
#./configure --ostree=$HOME/ece344/root
make
cd ~/ece344/os161
cd kern/conf
./config ASST1
cd ~/ece344/os161/kern
cd compile/ASST1
make depend
make
make install
echo "KERNEL BUILD!!"
