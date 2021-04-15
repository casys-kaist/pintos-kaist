
#!/bin/bash
# Tested on Ubuntu 18.04.1 LTS
set -ex

sudo apt-get -y update

# gcc
sudo apt-get -y install gcc=4:7.4.0-1ubuntu2.3
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 30
sudo update-alternatives --set gcc /usr/bin/gcc-7
gcc --version | grep "7.5.0-3ubuntu1~18.04"

# qemu
sudo apt-get -y install qemu=1:2.11+dfsg-1ubuntu7.36
qemu-x86_64 --version | grep "1:2.11+dfsg-1ubuntu7.36"

# make
sudo apt-get -y install make

echo OK
