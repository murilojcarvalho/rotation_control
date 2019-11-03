//Libraries
#include "main.h"

//Global variables
unsigned int rpm = 0;
unsigned long int previous_rpm_millis=0, current_rpm_millis=0;
char string_buffer[100] = {0};

//Functions prototypes
void init(void);
void proporcional_control(void);


int main(void){
	init();
	
    while ( TRUE ) {
		//Pwm1ASetDuty(10);
		set_duty_PWM(50);
		current_rpm_millis = millis();
		if(current_rpm_millis - previous_rpm_millis >= serial_publish_interval){
			previous_rpm_millis = current_rpm_millis;
			sprintf(string_buffer, "%u \r\n", rpm);
			USART_StrTx(string_buffer);
		}
    }
	
	return 0;
}

//INT0 Interrupt
ISR (INT0_vect){
	//ATOMIC_BLOCK(ATOMIC_FORCEON){
		//current_rpm_millis = millis();
		//rpm = 60/(current_rpm_millis - previous_rpm_millis)*7;
		rpm++;
		//sprintf(string_buffer, "%u \r\n", rpm);
		//USART_StrTx(string_buffer);
	//}
}

void init(void){
	//Port configuration
	//1 -> output, 0 -> input
	DDRB |= 0b00000010;		//Set PB1 (arduino digital pin 9) as output
	DDRD &= ~(1 << DDD2);     // Set PD2/INT0 (arduino digital pin 2) as input
	
	USART_Init();	//Start USART
	
	//Pwm1AInit();	//Enable PWM
	
	//Interrupt Config
	EICRA |= 0b00000011;    //The rising edge of INT0 generates an interrupt request (ISC00, ISC01)
	EIMSK |= (1 << INT0);     //Turns on INT0
	ticks_init();
	sei();          // turn on interrupts
	
	USART_StrTx("WELCOME\r\n");
}

void proporcional_control(void){
	
}