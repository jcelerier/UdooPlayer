UdooPlayer
==========

A loop player for the UDOO, based on libaudiotool

Installation on a new UDOO image (Ubuntu 12.04)

  sudo add-apt-repository ppa:ubuntu-toolchain-r/test
  sudo add-apt-repository ppa:ubuntu-sdk-team/ppa
  sudo apt-get update
  sudo apt-get dist-upgrade
  sudo apt-get install g++-4.8 ubuntu-sdk libportaudiocpp0 libportaudio-dev libavfilter-dev libavformat-dev libavcodec-dev cmake
  

Build KDE Frameworks 5 Archive : 
  
  mkdir ~/kf5
  cd ~/kf5

  git clone git://anongit.kde.org/extra-cmake-modules
  cd extra-cmake-modules
  mkdir build
  cd build
  cmake ..
  make
  make install
  
  cd ~/kf5
  wget http://download.kde.org/stable/frameworks/5.0.0/karchive-5.0.0.tar.xz
  tar -xvf karchive-5.0.0.tar.xz
  cd karchive-5.0.0.tar.xz
  mkdir build
  cd build
  cmake ..
  make
  make install
  
