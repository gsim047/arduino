#!/bin/bash

MODEL=esp8266:esp8266:generic
#CMD=/home/user/bin/arduino-cli
CMD=arduino-cli

$CMD compile -b $MODEL $1 $2 $3 $4 $5 $6 $7

