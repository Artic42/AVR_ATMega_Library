/*
 * ATmega328P.cpp
 *
 * Created: 08/10/2018 14:20:11
 * Author : Artic42
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <GPIO.h>
#include <Timer.h>
#include <USART.h>

void Initialize_HW (void);
char PositiveEdge(char input);

char LEDFlag,ButtonFlag;

int main(void)
{
    Initialize_HW();
	
	LEDFlag = 0;
	ButtonFlag = 0;
	sei(); //Enable interrupt system
	
	char Button_Positive_Edge;
    while (1) 
    {
		if (LEDFlag == 1) {
			LEDFlag = 0;
			GPIO_Toggle(PB,PIN0);
		}
	}
		if (ButtonFlag == 1) {
			ButtonFlag = 0;
			if(PositiveEdge ((char) GPIO_Read(PB,PIN2)))	{	GPIO_Toggle(PB,PIN5);	}
		}
}

void Initialize_HW (void)
{
	GPIO_ConfigureAsInput(PB,PIN2,PULLUP_OFF);
	GPIO_ConfigureAsOutput(PB,PIN0,BTRUE);

	Timer_SelectClockSource(TIMER_0,PRESCALE_1024);
	Timer_EnableOverflowInterrupt(TIMER_0);

	USART_SetBaud16M (9600);
	USART_ModeSelection (0);
	USART_SetCharacterSize (8);
	USART_EnableTransmitter();
	USART_DisableParityBit();
}

char PositiveEdge (char input)
{
	static char Prv_Value;
	char temp;
	temp = Prv_Value;
	Prv_Value = input;

	if (temp == 0 && input == 1)	{	return 1;	}
	else						{	return 0;	}
}

ISR (TIMER0_OVF_vect) 
{
	static int LedCounter=0, ButtonCounter=0;
	Timer_SetValue(TIMER_0,101); //This makes so the ISR execute every 10ms aprox 101.5 Hz aztually
	
	LedCounter++;
	ButtonCounter++;

	if (LedCounter >= 100) {	LEDFlag=1;		LedCounter=0;		}
	if (ButtonCounter >= 5) {	ButtonFlag=1;	ButtonCounter=0;	}
}
