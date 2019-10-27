#Variable definitions

ARCHIVER= ar
AFLAGS= -cvq
CC = avr-gcc
CFLAGS = -c -Wall 
IPATH = -ISource/Headers 
TARGET = -mmcu=atmega328p
MAIN_LIBRARY = ../bin/libATMega328P.so
LIBRARY_OBJECTS = bin/*.lib

#Complete makes

static: bin/GPIO.lib bin/USART.lib bin/ADC.lib bin/Timer.lib
	@$(ARCHIVER) $(AFLAGS) $(MAIN_LIBRARY) $(LIBRARY_OBJECTS)
	@echo "Static library completed"

#Individual make commands

bin/GPIO.lib: Source/GPIO.c Source/Headers/GPIO.h
	@$(CC) $(CFLAGS) $(IPATH) $(TARGET) Source/GPIO.c -o bin/GPIO.lib
	@echo "GPIO builded"
bin/USART.lib: Source/USART.c Source/Headers/USART.h
	@$(CC) $(CFLAGS) $(IPATH) $(TARGET) Source/USART.c -o bin/USART.lib
	@echo "USART builded"
bin/ADC.lib: Source/ADC.c Source/Headers/ADC.h
	@$(CC) $(CFLAGS) $(IPATH) $(TARGET) Source/ADC.c -o bin/ADC.lib
	@echo "ADC builded"
bin/Timer.lib: Source/Timer.c Source/Headers/Timer.h
	@$(CC) $(CFLAGS) $(IPATH) $(TARGET) Source/Timer.c -o bin/Timer.lib
	@echo "Timer builded"

#Extra make commands

clean:
	@rm -r bin/*.lib
	@echo "Files deleted"

GPIO: bin/GPIO.lib
USART: bin/USART.lib
ADC: bin/ADC.lib
Timer: bin/Timer.lib
