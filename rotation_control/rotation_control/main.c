

//Libraries
#include "defs.h"
#include <avr/io.h>		//ATMEGA328P registers
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "usart.h"
#include "ticks.h"

//Global variables
unsigned long int count = 0;
char string_buffer[50] = {0};

//Functions prototypes



int main(void){
	//Port configuration
	//1 -> output, 0 -> input
    DDRB |= 0b00000010;		//Set PB1 (arduino digital pin 9) as output	
	DDRD &= ~(1 << DDD2);     // Set PD2/INT0 (arduino digital pin 2) as input
	
	USART_Init();	//Start USART
	
	EICRA |= 0b00000011;    //The rising edge of INT0 generates an interrupt request (ISC00, ISC01)
	EIMSK |= (1 << INT0);     //Turns on INT0
	ticks_init();
	sei();          // turn on interrupts
	
	USART_StrTx("WELCOME\r\n");
	
    while ( TRUE ) {
		//PORTB |= 0b00000010;  // Set PB1 (arduino digital pin 9) to 1
		//_delay_ms(50);
		
		//PORTB &= 0b11111101; // Set PB1 (arduino digital pin 9) to 0
		//_delay_ms(50);
		count = millis();
		if(count%1000 == 0){
			sprintf(string_buffer, "%lu \r\n", count);
			USART_StrTx(string_buffer);
		}
    }
	
	return 0;
}

//INT0 Interrupt
ISR (INT0_vect){
	//count++;
	//sprintf(string_buffer, "%lu \r\n", count);
	//USART_StrTx(string_buffer);
}
