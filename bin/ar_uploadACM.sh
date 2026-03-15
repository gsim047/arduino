#!/bin/bash

MODEL=`cat /home/user/bin/esp_model.txt`
#PORT=`cat /home/user/bin/esp_port.txt`
PORT="/dev/ttyACM0"

echo arduino-cli upload ...
echo model $MODEL
echo port $PORT
#arduino-cli compile -b esp8266:esp8266:generic $1
arduino-cli -v upload -b $MODEL -p $PORT $1
