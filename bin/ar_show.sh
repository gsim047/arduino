#!/bin/bash

#MODEL=`cat /home/user/bin/esp_model.txt`
#PORT=`cat /home/user/bin/esp_port.txt`
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


echo arduino-cli show ...
#echo model $MODEL
echo port $PORT
#arduino-cli compile -b esp8266:esp8266:generic $1
$CMD monitor -p $PORT -c baudrate=115200
