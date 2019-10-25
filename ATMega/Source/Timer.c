/****************************************************************************
*							Timer.c											*
*****************************************************************************
*																			*
*	Compiler:				Atmel Studio 7									*
*	Author:					Artic42											*
*	Version:				1.0												*
*	Board:					Atmel ATMega 328P (Arduino UNO)					*
*	Date:					12/14/2013										*
*																			*
*	Description:			Set of function to control standard features of	*
*							timers 0,1 & 2 of the ATmega328P and compatibles*
*	Requirements:			None											*
*																			*											
****************************************************************************/

#include <avr/io.h>
#include <Timer.h>

/****************************************************************************
*					Timer_ConfigureComparatorNonPWM					*
*****************************************************************************
*			It configures the comparator in 4 different modes				*
*****************************************************************************
*								Parameters									*
*	Timer:	 		Timer which you want to configure						*
*	Comparator:		The comparator you're going to configure				*
*	Mode:			Comparator mode	you want to select						*
*****************************************************************************
*								Non-PWM Modes								*
*	Mode0:			Comparator disconnected									*
*	Mode1:			Toggle OCxA on compare match							*
*	Mode2:			Reset OCxA on compare match								*
*	Mode3:			Set OCxA on compare match								*
*****************************************************************************
*								PWM Modes									*
*	Mode0:			Comparator disconnected									*
*	Mode1:			Comparator disconnected									*
*	Mode2:			Reset OCxA on compare match								*
*	Mode3:			Set OCxA on compare match								*
****************************************************************************/

void Timer_ConfigureComparatorMode (int Timer,char Comparator,int Mode)
{
	char Shift,Temp1,Temp2;

	if (Comparator == 'A')	{	Shift=6;	}
	else					{	Shift=4;	}

	Temp1	=	Mode << Shift;
	Temp2	=	Temp1 || 0xCF;
	
	switch (Timer)
	{
		case 0:
			TCCR0A |= Temp1;
			TCCR0A &= Temp2;
		break;
		
		case 1:
			TCCR1A |= Temp1;
			TCCR1A &= Temp2;
		break;
		
		case 2:
			TCCR2A |= Temp1;
			TCCR2A &= Temp2;
		break;
	}
}


/****************************************************************************
*						Timer_SelectClockSource						*
*****************************************************************************
*	It configures the timer to the different pre-scaler and external clocks	*
*****************************************************************************
*								Parameters									*
*	Timer:	 		Timer which you want to configure						*
*	Source:			Comparator mode	you want to select						*
*****************************************************************************
*	Source0:		Timer Disconnected										*
*	Source1:		Prescaling=1											*
*	Source2:		Prescaling=8											*
*	Source3:		Prescaling=64											*
*	Source4:		Prescaling=256											*
*	Source5:		Prescaling=1024											*
*	Source6:		External clock source, clock on falling edge			*
*	Source7:		External clock source, clock on rising edge				*
****************************************************************************/

void Timer_SelectClockSource (int Timer,int Source)
{
	char Temp;

	Temp = Source | 0xF8;

	switch (Timer)
	{
		case 0:
			TCCR0B |= Source;
			TCCR0B &= Temp;
		break;
		
		case 1:
			TCCR1B |= Source;
			TCCR1B &= Temp;
		break;
		
		case 2:
			TCCR2B |= Source;
			TCCR2B &= Temp;
		break;
	}
}


/****************************************************************************
*					Timer_EnbaleOverflowInterrupt					*
*****************************************************************************
*		Enables the overflow interrupt of the selected timer				*
*****************************************************************************
*								Parameters									*
*	Timer:	 		Timer that you want select								*
****************************************************************************/

void Timer_EnableOverflowInterrupt (int Timer)
{
	switch (Timer)
	{
		case 0:	TIMSK0 |= 0x01; break;
		case 1:	TIMSK1 |= 0x01; break;
		case 2:	TIMSK2 |= 0x01;	break;
	}
}

/****************************************************************************
*					Timer_EnbaleOverflowInterrupt					*
*****************************************************************************
*		Disables the overflow interrupt of the selected timer				*
*****************************************************************************
*								Parameters									*
*	Timer:	 		Timer that you want select								*
****************************************************************************/

void Timer_DisableOverflowInterrupt (int Timer)
{
	switch (Timer)
	{
		case 0: TIMSK0 &= 0xFE;	break;
		case 1: TIMSK1 &= 0xFE;	break;
		case 2: TIMSK2 &= 0xFE;	break;
	}
}

/****************************************************************************
*					Timer_EnableCompareAInterrupt					*
*****************************************************************************
*		Enables the comparator A match interrupt of the selected timer		*
*****************************************************************************
*								Parameters									*
*	Timer:	 		Timer that you want select								*
****************************************************************************/

void Timer_EnableCompareAInterrupt (int Timer)
{
	switch (Timer)
	{
		case 0: TIMSK0 |= 0x02; break;
		case 1: TIMSK1 |= 0x02; break;
		case 2: TIMSK2 |= 0x02; break;
	}
}

/****************************************************************************
*					Timer_DisableComapareAInterrupt					*
*****************************************************************************
*		Disables tFDhe comparator A match interrupt of the selected timer		*
*****************************************************************************
*								Parameters									*
*	Timer:	 		Timer that you want select								*
****************************************************************************/

void Timer_DisableComapareAInterrupt (int Timer)
{
	switch (Timer)
	{
		case 0: TIMSK0 &= 0xFD; break;
		case 1: TIMSK0 &= 0xFD; break;
		case 2: TIMSK0 &= 0xFD; break;
	}
}

/****************************************************************************
*					Timer_EnableCompareBInterrupt					*
*****************************************************************************
*		Enables the comparator B match interrupt of the selected timer		*
*****************************************************************************
*								Parameters									*
*	Timer:	 		Timer that you want select								*
****************************************************************************/

void Timer_EnableCompareBInterrupt (int Timer)
{
	switch (Timer)
	{
		case 0: TIMSK0 |= 0x04; break;
		case 1: TIMSK1 |= 0x04; break;
		case 2: TIMSK2 |= 0x04; break;
	}
}

/****************************************************************************
*					Timer_DisableComapareBInterrupt					*
*****************************************************************************
*		Disables the comparator B match interrupt of the selected timer		*
*****************************************************************************
*								Parameters									*
*	Timer:	 		Timer that you want select								*
****************************************************************************/

void Timer_DisableComapareBInterrupt (int Timer)
{
	switch (Timer)
	{
		case 0: TIMSK0 &= 0xFB; break;
		case 1: TIMSK1 &= 0xFB; break;
		case 2: TIMSK2 &= 0xFB; break;
	}
}


/****************************************************************************
*							  Timer_SerValue							*
*****************************************************************************
*		Set an exact Value on the timer										*
*****************************************************************************
*								Parameters									*
*	Timer:	 		Timer that you want select								*
*	Value:			The value we want to set
****************************************************************************/

void Timer_SetValue (int Timer,int Value)
{
	switch (Timer)
	{
		case 0: TCNT0 = (char) Value; 	break;
		case 1: TCNT1 = Value; 			break;
		case 2: TCNT2 = Value; 			break;
	}
}

/****************************************************************************
*				  Timer_SerValueComparatorA							*
*****************************************************************************
*		Set an exact Value on the comparator A								*
*****************************************************************************
*								Parameters									*
*	Timer:	 		Timer that you want select								*
*	Value:			The value we want to set
****************************************************************************/

void Timer_SetValueComparatorA (int Timer,int Value)
{
	switch (Timer)
	{
	case 0:	OCR0A = (char) Value;	break;
	case 1:	OCR1A = Value;			break;
	case 2:	OCR2A = Value;			break;
	}
}

/****************************************************************************
*				  Timer_SerValueComparatorB							*
*****************************************************************************
*		Set an exact Value on the comparator B								*
*****************************************************************************
*								Parameters									*
*	Timer:	 		Timer that you want select								*
*	Value:			The value we want to set
****************************************************************************/

void Timer_SetValueComparatorB (int Timer,int Value)
{
	switch (Timer)
	{
		case 0:	OCR0B = (char) Value;	break;
		case 1:	OCR1B = Value;			break;
		case 2:	OCR2B = Value;			break;
	}
}
