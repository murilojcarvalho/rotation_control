/*
 * ticks.h
 *
 * Created: 04/05/2019 00:56:05
 *  Author: Microgenios
 */ 


#ifndef TICKS_H_
#define TICKS_H_

/* Código de referência: 
	- https://www.avrfreaks.net/forum/timer-tick-function-and-overflow-arithmetic 
	- Modificado por Fernando Simplicio;
	- Edited by Murilo Jose de Carvalho
*/

void ticks_init( void );
unsigned long int millis(void);


#endif /* TICKS_H_ */