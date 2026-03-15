#!/bin/bash

MODEL=`cat /home/user/bin/esp_model.txt`

echo arduino-cli compile ...
echo model $MODEL
#arduino-cli compile -b esp8266:esp8266:generic $1
arduino-cli -v compile -e -b $MODEL $1
