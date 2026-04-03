#!/bin/bash

MODEL=esp8266:esp8266:generic
PORT=/dev/ttyUSB0
#CMD=/home/user/bin/arduino-cli
CMD=arduino-cli

if [ -e /dev/ttyUSB0 ]; then
	echo "ttyUSB0!"
else
	if [ -e /dev/ttyACM0 ]; then
		echo "ttyACM0!"
		PORT=/dev/ttyACM0
	else
		echo "none tty..."
		exit 1
	fi
fi


$CMD upload -b $MODEL -p $PORT $1 $2 $3 $4 $5 $6 $7
