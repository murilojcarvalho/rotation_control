/*
 * ticks.h
 *
 * Created: 04/05/2019 00:56:05
 *  Author: Microgenios
 */ 


#ifndef TICKS_H_
#define TICKS_H_

/* Código de referência: 
	- https://sites.google.com/site/qeewiki/books/avr-guide/timers-on-the-atmega328
	- Edited by Murilo Jose de Carvalho
*/

#include <util/atomic.h>
#include <avr/io.h>		//ATMEGA328P registers
#include "main.h"

#define		pwm_period	100		//100Hz -> 1/(100us * 100) = 

void ticks_init( void );
unsigned long int millis(void);
void set_duty_PWM(unsigned char pwm_duty_temp);


#endif /* TICKS_H_ */