/****************************************************************************
*							GPIO.c								*
*****************************************************************************
*																			*
*	Compiler:				AVR-GCC											*
*	Author:					Artic42											*
*	Version:				1.0												*
*	Board:					Atmel ATMega 328P (Arduino UNO)					*
*	Date:					11/27/2013										*
*																			*
*	Description:			Set of function to control GPIO port (B,C,D)	*
*							of the ATmega 328P and compatibles				*
*	Requirements:			None											*
*																			*
****************************************************************************/

#include <avr/io.h>
#include <GPIO.h>



/****************************************************************************
*						GPIO_ConfigureAsOutput						*
*****************************************************************************
*				It configures the selected Pin as at Output					*
*****************************************************************************
*								Parameters									*
*	Port:	 		Port of the pin that you want to configure as output	*
*	Pin:			Number of the pin you want to configure as output		*
*	DeafaultValue:	Value TRUE or FALSE for the pin to be written in the	*
*					pin														*
****************************************************************************/

void GPIO_ConfigureAsOutput (char Port, char Pin, char DefaultValue)

{
	char Temp;

	Temp = 0x01 << Pin;

	switch (Port)
	{
	case PB:	DDRB |= Temp;	break;
	case PC:	DDRC |= Temp;	break;
	case PD:	DDRD |= Temp;	break;
	}

	GPIO_Write (Port,Pin,DefaultValue);
}


/****************************************************************************
*						GPIO_ConfigureAsInput						*
*****************************************************************************
*				It configures the selected Pin as an Input					*
*****************************************************************************
*								Parameters									*
*	Port:	 		Port of the pin that you want to configure as output	*
*	Pin:			Number of the pin you want to configure as output		*
*	PullUp:			If true the PullUp resistance is enabled				*
****************************************************************************/

void GPIO_ConfigureAsInput (char Port,char Pin,char PullUp)
{
	char Temp;

	Temp = 0x01 << Pin;
	Temp = ~Temp;

	switch (Port)
	{
	case PB:	DDRB &= Temp;	break;
	case PC:	DDRC &= Temp;	break;
	case PD:	DDRD &= Temp;	break;
	}

	GPIO_Write(Port,Pin,PullUp);
}

/****************************************************************************
*								GPIO_Write							*
*****************************************************************************
*				It writes the digital value on the pin you want				*
*****************************************************************************
*								Parameters									*
*	Port:	 		Port of the pin that you want to configure as output	*
*	Pin:			Number of the pin you want to configure as output		*
*	Value:			Value TRUE or FALSE for the pin to be written in the	*
*					pin														*
****************************************************************************/

void GPIO_Write (char Port,char Pin, char Value)
{
	char Temp;

	Temp = 0x01 << Pin;

	if (Value)
	{
		switch (Port)
		{
		case PB:	PORTB |= Temp;	break;
		case PC:	PORTC |= Temp;	break;
		case PD:	PORTD |= Temp;	break;
		}
	}
	else
	{
		Temp = ~Temp;
		switch (Port)
		{
		case PB:	PORTB &= Temp;	break;
		case PC:	PORTC &= Temp;	break;
		case PD:	PORTD &= Temp;	break;
		}
	}
}

/****************************************************************************
*								GPIO_Read							*
*****************************************************************************
*				It read the digital value from the pin you want				*
*****************************************************************************
*								Parameters									*
*	Port:	 		Port of the pin that you want to configure as output	*
*	Pin:			Number of the pin you want to configure as output		*
*																			*
*								  Return									*
*	Return:			It returns the value of the requested pin				*
****************************************************************************/

char GPIO_Read (char Port,char Pin)
{
	char 	Temp1,Temp2,Value;

	switch (Port)
	{
	case PB:	Temp1=PINB;	break;
	case PC:	Temp1=PINC;	break;
	case PD:	Temp1=PIND;	break;
	default:	Temp1=0;
	}
	Temp2 = 0x01 << Pin;
	Value = Temp1 & Temp2;

	return Value;
}

/****************************************************************************
*								GPIO_Toggle						*
*****************************************************************************
*				It read the digital value from the pin you want				*
*****************************************************************************
*								Parameters									*
*	Port:	 		Port of the pin that you want to configure as output	*
*	Pin:			Number of the pin you want to configure as output		*
*																			*
*								  Return									*
*	Return:			It returns the value of the requested pin				*
****************************************************************************/

void GPIO_Toggle (char Port,char Pin)
{
	char Temp;

	Temp = 0x01 << Pin;

	switch (Port)
	{
	case PB:	PORTB = PORTB ^ Temp;	break;
	case PC:	PORTC = PORTC ^ Temp;	break;
	case PD:	PORTD = PORTD ^ Temp;	break;
	}
}
