/****************************************************************************
*							USART.c											*
*****************************************************************************
*																			*
*	Compiler:				Atmel Studio 7									*
*	Author:					Artic42											*
*	Version:				1.0												*
*	Board:					Atmel ATMega 328P (Arduino UNO)					*
*	Date:					12/14/2013										*
*																			*
*	Description:			Set of function to control USART system			*
*							of the ATmega328P and compatibles				*
*	Requirements:			None											*
*																			*
****************************************************************************/

#include <avr/io.h>
#include <USART.h>



/****************************************************************************
*						USART_SetBaud16M							*
*****************************************************************************
*			Set the selected baudrate for the 16MHz clock freq.				*
*****************************************************************************
*								Parameters									*
*	Baud:		The selected baudrate										*
****************************************************************************/

void USART_SetBaud16M (long Baud)
{
	UCSR0A	|=	0x02;

	switch (Baud)
	{
	case   2400:	UBRR0 = 832; 	break;
	case   4800:	UBRR0 = 416; 	break;
	case   9600:	UBRR0 = 207; 	break;
	case  14400:	UBRR0 = 138; 	break;
	case  19200:	UBRR0 = 103; 	break;
	case  28800:	UBRR0 =  68; 	break;
	case  38400:	UBRR0 =  51; 	break;
	case  57600:	UBRR0 =  34; 	break;
	case  76800:	UBRR0 =  25; 	break;
	case 115200:	UBRR0 =  16;	break;
	case 230400:	UBRR0 =   8;	break;
	}
}

/****************************************************************************
*						USART_ModeSelection						*
*****************************************************************************
*					Set the selected mode in the USART						*
*****************************************************************************
*								Parameters									*
*	Mode:		The selected mode for the USART								*
*****************************************************************************
*						Possible values for Mode							*
*	ASYNCHRONOUS_MODE, SYNCHRONOUS_MODE, MASTER_SPI							*
****************************************************************************/

void USART_ModeSelection (char Mode)
{
	char Temporal1,Temporal2;

	Temporal1 = Mode << 6;
	Temporal2 = Temporal1 | 0x3F; //0011 111

	UCSR0C  |= Temporal1;
	UCSR0C	&= Temporal2;
}

/****************************************************************************
*						USART_EnableParityBit								*
*****************************************************************************
*							Enables parity bit								*
****************************************************************************/

void USART_EnableParityBit (char ParityMode)
{
	UCSR0C |= 0x20; //0010 0000
	USART_ParityModeSelection(ParityMode);
}

/****************************************************************************
*						USART_DisableParityBit								*
*****************************************************************************
*							Disable parity bit								*
****************************************************************************/

void USART_DisableParityBit (void)
{
	UCSR0C &= 0xCF; //1100 1111
}

/****************************************************************************
*						USART_ParityModeSelection					*
*****************************************************************************
*					Set the selected parity mode in the USART				*
*****************************************************************************
*								Parameters									*
*	ParityMode:		The selected parity mode for the USART					*
*****************************************************************************
*						Possible values for Mode							*
*	EVEN, ODD																*
****************************************************************************/

void USART_ParityModeSelection (char ParityMode)
{
	if (ParityMode)	{UCSR0C |= 0x10;}  //0001 0000
	else			{UCSR0C &= 0xEF;}  //1110 1111
}

/****************************************************************************
*					USART_SetStopBitQuantity						*
*****************************************************************************
*			Set the selected number of stop bits in the USART				*
*****************************************************************************
*								Parameters									*
*	StopBits:		How many stop bits do we want 1 or 2.					*
****************************************************************************/

void USART_SetStopBitQuantity (int StopBits)
{
	if (StopBits == 1)	{ UCSR0C &= 0XF7; }//1111 0111
	if (StopBits == 2)	{ UCSR0C |= 0x08; }//0000 1000
}

/****************************************************************************
*						USART_SetCharacterSize					*
*****************************************************************************
*					Set the caracther size for the USART					*
*****************************************************************************
*								Parameters									*
*	CharacterSize:		Number of bits in a character 5-9					*
****************************************************************************/

void USART_SetCharacterSize (int CharacterSize)
{
	switch (CharacterSize)
	{
	case 5: UCSR0C &= 0xF9; 				break;
	case 6: UCSR0C &= 0xFB; UCSR0C |= 0x02;	break;
	case 7: UCSR0C &= 0xFD; UCSR0C |= 0x04; break;
	case 8:
	case 9: 				UCSR0C |= 0x06; break;
	}
	if (CharacterSize < 9)	{	UCSR0B &= 0xFB;	}
	else					{	UCSR0B |= 0x04;	}
}

/****************************************************************************
*					USART_ReadUSART8bitCharacter					*
*****************************************************************************
*					Read the 8bit character from the USART					*
****************************************************************************/

char USART_ReadUSART8bitCharacter (void)
{
	return UDR0;
}

/****************************************************************************
*					USART_WriteUSART8bitCharacter					*
*****************************************************************************
*					Read the 8bit character from the USART					*
****************************************************************************/

void USART_WriteUSART8bitCharacter (char Character)
{
	UDR0 = Character;
}

/****************************************************************************
*					USART_ReadUSART9bitCharacter					*
*****************************************************************************
*					Read the 8bit character from the USART					*
****************************************************************************/

int USART_ReadUSART9bitCharacter (void)
{
	int LSB,HSB,Character;
	char Temp;

	Temp = UCSR0B &= 0x02;
	if (Temp)	{	HSB=1;	}
	else		{	HSB=0;	}

	LSB = (int) UDR0;
	HSB = HSB << 8;

	Character = LSB | HSB;
	return Character;
}

/****************************************************************************
*					USART_WriteUSART9bitCharacter					*
*****************************************************************************
*					Read the 8bit character from the USART					*
****************************************************************************/

void USART_WriteUSART9bitCharacter (int Character)
{
	int LSB,HSB;

	LSB = Character & 0x00FF;
	HSB = Character & 0xFF00;

	if (HSB)	{	UCSR0B |= 0x01;	}
	else		{	UCSR0B &= 0xFE;	}

	UDR0 = (char) LSB;
}

/****************************************************************************
*				USART_EnableTransmitCompleteInterrupt				*
*****************************************************************************
*				Enable the TX complete interrupt flag of the USART			*
****************************************************************************/

void USART_EnableTransmitCompleteInterrupt (void)
{
	UCSR0B |= 0x40;
}

/****************************************************************************
*				USART_DisableTransmitCompleteInterrupt			*
*****************************************************************************
*				Disable the TX complete interrupt flag of the USART			*
****************************************************************************/

void USART_DisableTransmitCompleteInterrupt (void)
{
	UCSR0B &= 0xBF;
}

/****************************************************************************
*				USART_EnableReceiveCompleteInterrupt				*
*****************************************************************************
*				Enable the RX complete interrupt flag of the USART			*
****************************************************************************/

void USART_EnableReceiveCompleteInterrupt (void)
{
	UCSR0B |= 0x80;
}

/****************************************************************************
*				USART_DisableReceiveCompleteInterrupt				*
*****************************************************************************
*				Disable the RX complete interrupt flag of the USART			*
****************************************************************************/

void USART_DisableReceiveCompleteInterrupt (void)
{
	UCSR0B &= 0x7F;
}

/****************************************************************************
*				USART_EnableDataRegisterEmptyInterrupt			*
*****************************************************************************
*		Enable the data register empty interrupt flag of the USART			*
****************************************************************************/

void USART_EnableDataRegisterEmptyInterrupt (void)
{
	UCSR0B |= 0x20;
}

/****************************************************************************
*				USART_DisableDataRegisterEmptyInterrupt			*
*****************************************************************************
*		Disable the Data Register Empty interrupt flag of the USART			*
****************************************************************************/

void USART_DisableDataRegisterEmptyInterrupt (void)
{
	UCSR0B &= 0xDF;
}

/****************************************************************************
*							USART_EnableReceiver					*
*****************************************************************************
*						Enable the receiver of the USART					*
****************************************************************************/

void USART_EnableReceiver (void)
{
	UCSR0B |= 0x10;
}

/****************************************************************************
*						USART_DisableReceiver						*
*****************************************************************************
*						Disable the receiver of the USART					*
****************************************************************************/

void USART_DisableReceiver (void)
{
	UCSR0B &= 0xEF;
}

/****************************************************************************
*							USART_EnableTransmitter				*
*****************************************************************************
*							Enable the transmitter of the USART				*
****************************************************************************/

void USART_EnableTransmitter (void)
{
	UCSR0B |= 0x08;
}

/****************************************************************************
*						USART_DisableTransmitter					*
*****************************************************************************
*						Disable the transmitter of the USART				*
****************************************************************************/

void USART_DisableTransmitter (void)
{
	UCSR0B &= 0xF7;
}

/****************************************************************************
*					USART_ReceiverCompleteState					*
*****************************************************************************
*				Read the state of the receiver complete flag				*
****************************************************************************/

char USART_ReceiverCompleteState (void)
{
	char Temp;

	Temp = (char) UCSR0A & 0x80;

	return Temp;
}

/****************************************************************************
*					USART_TransmitterCompleteState				*
*****************************************************************************
*				Read the state of the transmit complete flag				*
****************************************************************************/

char USART_TransmitterCompleteState (void)
{
	char Temp;

	Temp = (char) UCSR0A & 0x40;

	return Temp;
}

/****************************************************************************
*					USART_DataRegisterEmptyState				*
*****************************************************************************
*				Read the state of the receive complete flag				*
****************************************************************************/

char USART_DataRegisterEmptyState (void)
{
	char Temp;

	Temp = (char) UCSR0A & 0x20;

	return Temp;
}

/****************************************************************************
*					USART_FrameErrorFlagState						*
*****************************************************************************
*					Read the state of the frame error flag					*
****************************************************************************/

char USART_FrameErrorFlagState (void)
{
	char Temp;

	Temp = (char) UCSR0A & 0x10;

	return Temp;
}

/****************************************************************************
*						USART_DataOverRunFlagState				*
*****************************************************************************
*				Read the state of the data over run flag					*
****************************************************************************/

char USART_DataOverRunFlagState (void)
{
	char Temp;

	Temp = (char) UCSR0A & 0x08;

	return Temp;
}

/****************************************************************************
*					USART_ParityErrorFlagState					*
*****************************************************************************
*					Read the state of the parity error flag					*
****************************************************************************/

char USART_ParityErrorFlagState (void)
{
	char Temp;

	Temp = (char) UCSR0A & 0x04;

	return Temp;
}

/****************************************************************************
*						USART_CheckAnyUSARTError					*
*****************************************************************************
*						Check if there's any USART Error					*
****************************************************************************/

char USART_CheckAnyUSARTError (void)
{
	char Temp1,Temp2,Temp3,Error;

	Temp1	=	USART_FrameErrorFlagState();
	Temp2	=	USART_DataOverRunFlagState();
	Temp3	=	USART_ParityErrorFlagState();
	Error	=	Temp1 || Temp2	|| Temp3;

	return Error;
}

