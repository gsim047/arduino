#!/bin/bash

#MODEL=`cat /home/user/bin/esp_model.txt`
PORT=`cat /home/user/bin/esp_port.txt`

echo arduino-cli show ...
#echo model $MODEL
echo port $PORT
#arduino-cli compile -b esp8266:esp8266:generic $1
arduino-cli monitor -p $PORT -c baudrate=115200