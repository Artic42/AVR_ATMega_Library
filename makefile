#Variable definitions

CC = avr-gcc
DOWNLOADER = avrdude
MCU = -p m328p
CFLAGS = -c -Wall
IPATH = -ISource/Headers
TARGET = -mmcu=atmega328p
PROGRAMMER = -c atmelice_isp



#Default make command, ussually the more general one

all:

#Make command for building individual projects

bin/Blinky.elf: Source/Blinky.c
	$(CC) $(CFLAG) $(IPATH) $(TARGET) Source/Blinky.c bin/libATMega328P.so  -o bin/Blinky.elf
	@echo "Blinky builded"
bin/HelloWorld.elf: Source/HelloWorld.c
	$(CC) $(CFLAG) $(IPATH) $(TARGET) Source/HelloWorld.c bin/libATMega328P.so -o bin/HelloWorld.elf
	@echo "Hello World builded"

#Make command for downloading individual projects

delete:
	$(DOWNLOADER) $(MCU) $(PROGRAMMER) -e

dwBlinky: bin/Blinky.elf
	$(DOWNLOADER) $(MCU) $(PROGRAMMER) -e
	$(DOWNLOADER) $(MCU) $(PROGRAMMER) -u flash:w:bin/Blinky.elf
	@echo "Blinky downloaded"
dwHelloWorld.elf: bin/HelloWorld.elf
	$(DOWNLOADER) $(MCU) $(PROGRAMMER) -e
	$(DOWNLOADER) $(MCU) $(PROGRAMMER) -U flash:w:bin/HelloWorld.elf
	@echo "Hello World downloaded"

#Check library

#Special orders to build only one of the examples

Blinky: bin/Blinky.elf
HelloWorld: bin/HelloWorld.elf
