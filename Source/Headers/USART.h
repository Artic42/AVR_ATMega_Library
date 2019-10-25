/****************************************************************************
*							USART.h								*
*****************************************************************************
*				Header required to work with USART.c				*
****************************************************************************/

#ifndef USART_H_
#define USART_H_

/****************************************************************************
* 								Prototypes									*
****************************************************************************/

extern void USART_SetBaud16M (long Baud);
extern void USART_ModeSelection (char Mode);
extern void USART_EnableParityBit (char ParityMode);
extern void USART_DisableParityBit (void);
extern void USART_ParityModeSelection (char ParityMode);
extern void USART_SetStopBitQuantity (int StopBits);
extern void USART_SetCharacterSize (int CharacterSize);
extern char USART_ReadUSART8bitCharacter (void);
extern void USART_WriteUSART8bitCharacter (char Character);
extern int  USART_ReadUSART9bitCharacter (void);
extern void USART_WriteUSART9bitCharacter (int Character);
extern void USART_EnableTransmitCompleteInterrupt (void);
extern void USART_DisableTransmitCompleteInterrupt (void);
extern void USART_EnableReceiveCompleteInterrupt (void);
extern void USART_DisableReceiveCompleteInterrupt (void);
extern void USART_EnableDataRegisterEmptyInterrupt (void);
extern void USART_DisableDataRegisterEmptyInterrupt (void);
extern void USART_EnableReceiver (void);
extern void USART_DisableReceiver (void);
extern void USART_EnableTransmitter (void);
extern void USART_DisableTransmitter (void);
extern char USART_ReceiverCompleteState (void);
extern char USART_TransmitterCompleteState (void);
extern char USART_DataRegisterEmptyState (void);
extern char USART_FrameErrorFlagState (void);
extern char USART_DataOverRunFlagState (void);
extern char USART_ParityErrorFlagState (void);
extern char USART_CheckAnyUSARTError (void);

/*****************************************************************************
* 								Definitions									 *
*****************************************************************************/

#define ASYNCHRONOUS_MODE	0;
#define SYNCHRONOUS_MODE	1;
#define MASTER_SPI			2;

#define EVEN				0;
#define ODD					1;


#endif /* USART_H_ */
