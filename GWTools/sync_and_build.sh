#!/bin/bash

HOST=192.168.1.93
# BUILD_FOLDER=Pidventure

ROOT_FOLDER=projects/TAGE

FULL_PATH=$ROOT_FOLDER/$PROJECT_FOLDER/gw

echo $FULL_PATH

#HOST=192.168.2.65
#HOST=m3pi
#HOST=m3pi.local

rsync -av -e ssh ../../../ --exclude='.git' --exclude='build' --exclude='Datawork' --exclude='Tools' --exclude='.xcodeproj' pi@$HOST:~/$ROOT_FOLDER

if [ ! -z "$1" ]; then

	if [ $1 -eq "0" ]; then
		ssh pi@$HOST << END
		# sudo killall runme
		cd $FULL_PATH && make 2>&1
END
	elif [ $1 -eq "1" ]; then
		ssh pi@$HOST << END
		# sudo killall runme
		cd $FULL_PATH && make 2>&1 && ./install.sh rpi
END
	fi
fi
