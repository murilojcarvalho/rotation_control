//Macros
#define F_CPU 16000000UL		//used with delay function
#define TRUE  1

//Libraries
#include <avr/io.h>		//ATMEGA328P registers
#include <util/delay.h>


int main(void){
	//Port configuration
	//1 -> output, 0 -> input
    DDRB = 0xFF; 
	
    while ( TRUE ) {
		PORTB |= 0b00000010;  // Set PB1 (arduino digital pin 9)
		_delay_ms(1000);
		
		PORTB &= 0b11111101; // Clear PB1 (arduino digital pin 9)
		_delay_ms(1000);
    }
	
	return 0;
}


