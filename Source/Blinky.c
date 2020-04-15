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

void Initialize_HW (void);

int timerFlag;
int LedCounter=0,input;

int main(void)
{
    Initialize_HW();
	
	sei(); //Enable interrupt system
	
    while (1) 
    {
		input=GPIO_Read(PB,PIN2);
		if (timerFlag == 1)
		{
			timerFlag = 0;
			LedCounter++;
			
			if (LedCounter > 100)
			{
				LedCounter = 0;
				GPIO_Toggle(PB,PIN0);
			}		
			
		}
	}
}

void Initialize_HW (void)
{
	GPIO_ConfigureAsInput(PC,PIN4,PULLUP_ON);
	GPIO_ConfigureAsOutput(PD,PIN3,BTRUE);
	
	Timer_SelectClockSource(TIMER_0,PRESCALE_1024);
	Timer_EnableOverflowInterrupt(TIMER_0);
}

ISR (TIMER0_OVF_vect) 
{
	Timer_SetValue(TIMER_0,101);
	timerFlag = 1;
}
