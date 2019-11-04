/*
 * main.h
 *
 * Created: 03/11/2019 13:50:22
 *  Author: MURILO
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000UL		//used with delay function
#define TRUE  1
#define blink_interval	500
#define serial_interval	500

#include "defs.h"
#include <avr/io.h>		//ATMEGA328P registers
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include "usart.h"
#include "ticks.h"

#endif /* MAIN_H_ */