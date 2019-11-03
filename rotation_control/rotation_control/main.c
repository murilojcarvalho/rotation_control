//Libraries
#include "defs.h"
#include <avr/io.h>		//ATMEGA328P registers
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "usart.h"
#include "ticks.h"
#include "pwm.h"

//Global variables
unsigned long int count = 0;
char string_buffer[50] = {0};

//Functions prototypes
void init(void);


int main(void){
	init();
	
    while ( TRUE ) {
		
		Pwm1ASetDuty(10);
		
    }
	
	return 0;
}

//INT0 Interrupt
ISR (INT0_vect){
	count++;
	sprintf(string_buffer, "%lu \r\n", count);
	USART_StrTx(string_buffer);
}

void init(void){
	//Port configuration
	//1 -> output, 0 -> input
	DDRB |= 0b00000010;		//Set PB1 (arduino digital pin 9) as output
	DDRD &= ~(1 << DDD2);     // Set PD2/INT0 (arduino digital pin 2) as input
	
	USART_Init();	//Start USART
	
	Pwm1AInit();	//Enable PWM1
	
	//Interrupt Config
	EICRA |= 0b00000011;    //The rising edge of INT0 generates an interrupt request (ISC00, ISC01)
	EIMSK |= (1 << INT0);     //Turns on INT0
	ticks_init();
	sei();          // turn on interrupts
	
	USART_StrTx("WELCOME\r\n");
}