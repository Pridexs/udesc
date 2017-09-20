@echo off
cd bin
cd Release
avrdude -c arduino -b 115200 -P COM9 -p atmega328p -U flash:w:avr-blink.hex:i
PAUSE
