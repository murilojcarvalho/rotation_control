/*
 * ticks.h
 *
 * Created: 04/05/2019 00:56:05
 *  Author: Microgenios
 */ 


#ifndef TICKS_H_
#define TICKS_H_

/* C�digo de refer�ncia: 
	- https://sites.google.com/site/qeewiki/books/avr-guide/timers-on-the-atmega328
	- Edited by Murilo Jose de Carvalho
*/

#include <util/atomic.h>
#include <avr/io.h>		//ATMEGA328P registers
#include "main.h"

void ticks_init( void );
unsigned long int millis(void);


#endif /* TICKS_H_ */