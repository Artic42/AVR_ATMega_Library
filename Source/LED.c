/*
File Name:	<++>
//
Compiler:	<++>
Author:		<++>
Description:	<++>
Testd on:	<++>
*/

/****************************************
*		Include			*
*****************************************/

#include"GPIO.h"
#include<avr/io.h>

/****************************************
*	Private Definitions		*
****************************************/

#define LED PORTD,PIN3
#define BUTTON PORTC,PIN4

/****************************************
*		Code			*
****************************************/
int main (void)
{
	GPIO_ConfigureAsOutput(LED,BFALSE);
	GPIO_ConfigureAsInput(BUTTON,BTRUE);

	while (BTRUE)
	{
		//GPIO_Write(LED,GPIO_Read (BUTTON));
		GPIO_Write(PORTD,PIN3,BTRUE);
	}

	return 0;
}

