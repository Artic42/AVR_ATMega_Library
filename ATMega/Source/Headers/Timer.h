/****************************************************************************
*							Timer.h								*
*****************************************************************************
*				Header required to work with Timer.cpp			*
****************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

/****************************************************************************
* 								Prototypes									*
****************************************************************************/

extern void Timer_ConfigureComparatorMode (char Timer,char Comparator,char Mode);
extern void Timer_SelectClockSource (char Timer,char Source);
extern void Timer_EnableOverflowInterrupt (char Timer);
extern void Timer_DisableOverflowInterrupt (char Timer);
extern void Timer_EnableCompareAInterrupt (char Timer);
extern void Timer_DisableComapareAInterrupt (char Timer);
extern void Timer_EnableCompareBInterrupt (char Timer);
extern void Timer_DisableComapareBInterrupt (char Timer);
extern void Timer_SetValue (char Timer,int Value);
extern void Timer_SetValueComparatorA (char Timer,int Value);
extern void Timer_SetValueComparatorB (char Timer,int Value);


/*****************************************************************************
* 								Definitions									 *
*****************************************************************************/

#define TIMER_0				0
#define TIMER_1				1
#define TIMER_2				2

#define COMPA				'A'
#define COMPB				'B'

#define MODE0				0
#define MODE1				1
#define MODE2				2
#define MODE3				3

#define TIMER_DISCONNECT	0
#define NO_PRESCALE			1
#define PRESCALE_8			2
#define PRESCALE_64			3
#define PRESCALE_256		4
#define PRESCALE_1024		5
#define EXTERN_CLK_FALLEDGE 6
#define EXTERN_CLK_UPEDGE	7

#endif /* TIMER_H_ */
