#Variable definitions

CC = avr-gcc
CFLAGS = -c -Wall
IPATH = -ISource/Headers
TARGET = -mmcu=atmega328p

#Default make command, ussually the more general one

blink: Blinky.c
	$(CC) $(CFLAG) $(IPATH) $(TARGET) Blinky.c bin/libATMega328P.so  -o bin/Blinky.elf

#Chack library
