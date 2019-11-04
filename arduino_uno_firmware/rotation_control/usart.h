#ifndef __USART_H__
#define __USART_H__
				
#define BAUD 9600
#define MYUBRR (((F_CPU/16)/BAUD)-1)
#include <avr/io.h>
#include "main.h"
#include <util/delay.h>					

void USART_Init(void);
void USART_Transmit(unsigned char data);
unsigned char USART_Receive( void );
void USART_StrTx(const char*);
void USART_rxIE(void);
void read_usart_rx_buffer(char *temp_usart_rx_buffer);

#endif