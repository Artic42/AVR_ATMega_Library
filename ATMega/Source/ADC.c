/****************************************************************************
*									ADC.cpp									*
*****************************************************************************
*																			*
*	Compiler:				Atmel Studio 7									*
*	Author:					Artic42											*
*	Version:				1.0												*
*	Board:					Atmel ATMega 328P (Arduino UNO)					*
*	Date:					12/14/2013										*
*																			*
*	Description:			Set of function to control ADC systems			*
*							of the ATmega328P and compatibles				*
*	Requirements:			None											*
*																			*
****************************************************************************/

#include <avr/io.h>
#include <ADC.h>

/****************************************************************************
*						ADC_SelectRefPin							*
*****************************************************************************
*			Selects the Reference we want to use for the ADC				*
*****************************************************************************
*								Parameters									*
*	Reference:		Wanted voltage reference								*
*****************************************************************************
*					Possible values for reference							*
*	EXTERNAL_AREFPIN, INTERNAL_AVCC, INTERNAL_1_1V							*
****************************************************************************/

void ADC_SelectRefPin (char Reference)
{
	char Temp1,Temp2;

	Temp1 = Reference << 6;
	Temp2 = Temp1 || 0x3F;

	ADMUX |= Temp1;
	ADMUX &= Temp2;
}

/****************************************************************************
*								ADC_AdjustResult							*
*****************************************************************************
*	Selects if the result of the ADC should adjust left or right			*
*****************************************************************************
*								Parameters									*
*	Side:	The side for the adjust of the result							*
*****************************************************************************
*						Possible values for side							*
*	LEFT, RIGHT																*
****************************************************************************/

void ADC_AdjustResult (int Side)
{

}
