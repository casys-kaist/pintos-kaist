
#!/bin/bash
# Tested on Ubuntu 16.04 (STANDARD-1 KCLOUD VM)
set -ex

sudo apt-get -y update

# gcc
sudo apt-get install -y software-properties-common python-software-properties
sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt update && sudo apt install g++-7 -y

#sudo apt-get -y install gcc=4:7.4.0-1ubuntu2.3
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 30
sudo update-alternatives --set gcc /usr/bin/gcc-7
gcc --version | grep "7.5.0-3ubuntu1~16.04"

# qemu
sudo apt-get -y install qemu=1:2.5+dfsg-5ubuntu10.51
qemu-x86_64 --version | grep "1:2.5+dfsg-5ubuntu10.51"

# make
sudo apt-get -y install make

echo OK
