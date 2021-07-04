#!/bin/sh
 
usage() {
  echo "usage:"
  echo " -s             : 打开Simrobot"
  echo " -b             : 打开bush"
  echo " -make -s       : 变异Simrobot"
  echo " -make          : 编译Nao"
  echo " -l <robotIp>   : 执行login"
  exit 1
}
 
if [ "$1" = "-s" ]; then
  nohup ../Build/Linux/SimRobot/Develop/SimRobot &
  exit
elif [ "$1" = "-b" ]; then
  nohup ../Build/Linux/bush/Develop/bush &
  exit
elif [ "$1" = "-h" ]; then
  usage
elif [ "$1" = "-l" ]; then
  ../Make/Linux/login $2
  exit
elif [ "$1" = "make" ]; then
  if [ "$2" = "-s" ]; then
    cd ../Make/Common
    ../../Util/SimRobot/Util/mare/Linux/bin/mare qtinclude="/usr/include/x86_64-linux-gnu/qt5" ssse3=true avx2=true SimRobot config=Develop
  else
    cd ../Make/Common
    ../../Util/SimRobot/Util/mare/Linux/bin/mare qtinclude="/usr/include/x86_64-linux-gnu/qt5" ssse3=true avx2=true Nao config=Develop
  fi
fi