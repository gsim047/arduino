#!/bin/bash

#/home/user/bin/

if [ -e /dev/ttyUSB0 ]; then
	echo "ttyUSB0!"
	arduino-cli upload -b esp8266:esp8266:generic -p /dev/ttyUSB0 $1 $2 $3 $4 $5 $6 $7
else
	if [ -e /dev/ttyACM0 ]; then
		echo "ttyACM0!"
		arduino-cli upload -b esp8266:esp8266:generic -p /dev/ttyACM0 $1 $2 $3 $4 $5 $6 $7
	else
		echo "none tty..."
	fi
fi

