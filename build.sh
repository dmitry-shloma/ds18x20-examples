#!/bin/sh

rm -rf ./build
mkdir -p ./build/ws
avr-gcc -mmcu=atmega8 -g -Os --std=c99 -c ./src/lcd/lcd.c -o ./build/ws/lcd.o
avr-gcc -mmcu=atmega8 -g -Os --std=c99 -c ./src/onewire/onewire.c -o ./build/ws/onewire.o
avr-gcc -mmcu=atmega8 -g -Os --std=c99 ./build/ws/lcd.o ./build/ws/onewire.o ./src/ds18x20-examples/main.c -o ./build/ws/ws.out
avr-objcopy -j .text -j .data -O ihex ./build/ws/ws.out ./build/ws/ws.hex
