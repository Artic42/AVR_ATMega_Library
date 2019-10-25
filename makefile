#Variable definitions

CC = avr-gcc
CFLAGS = -c -Wall
IPATH = -ISource/Headers
TARGET = -mmcu=atmega328p

#Default make command, ussually the more general one

blink: bin/libATMega328P.so Blinky.c
	$(CC) $(CFLAG) $(IPATH) $(TARGET) Blinky.c ATMega/bin/GPIO.lib ATMega/bin/Timer.lib  -o bin/Blinky.elf
