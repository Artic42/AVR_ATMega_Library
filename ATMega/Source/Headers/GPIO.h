
/****************************************************************************
*							GPIO.h								*
*****************************************************************************
*				Header required to work with GPIO.c				*
****************************************************************************/
#ifndef GPIO_H_
#define GPIO_H_

/****************************************************************************
* 								Prototypes									*
****************************************************************************/

extern void GPIO_ConfigureAsOutput (char Port, char Pin, char DefaultValue);
extern void GPIO_ConfigureAsInput (char Port,char Pin,char PullUp);
extern void GPIO_Write (char Port,char Pin, char Value);
extern char GPIO_Read (char Port,char Pin);
extern void GPIO_Toggle (char Port,char Pin);

/*****************************************************************************
* 								Definitions									 *
*****************************************************************************/

#define PB			'B'
#define PC			'C'
#define PD			'D'

#define PIN0		0
#define PIN1		1
#define PIN2		2
#define PIN3		3
#define PIN4		4
#define PIN5		5
#define PIN6		6
#define PIN7		7

#define PULLUP_ON	1
#define PULLUP_OFF	0

#define BTRUE		1
#define BFALSE		0

#endif /* GPIO_H_ */
