//Libraries
#include "main.h"

//Global variables
unsigned int rpm = 0;
unsigned char pulse_rpm_count=0;
unsigned long int previous_blink_millis=0, current_blink_millis=0;
unsigned long int previous_rpm_millis=0, current_rpm_millis=0;
char string_buffer[100] = {0};
unsigned char led_builtin_status=0;
unsigned int rpm_set_point=1000;
unsigned char pwm=0;

//Functions prototypes
void init(void);
void linear_control(void);


int main(void){
	init();
	
    while ( TRUE ) {
		current_blink_millis = millis();
		if(current_blink_millis - previous_blink_millis >= blink_interval){
			led_builtin_status = !led_builtin_status;
			if(led_builtin_status){
				Set_bit(PORTB, 5);
			}
			else{
				Clr_bit(PORTB, 5);
			}
			previous_blink_millis = current_blink_millis;
			linear_control();
			sprintf(string_buffer, "%u RPM \r\n", rpm);
			USART_StrTx(string_buffer);
		}
    }
	
	return 0;
}

//INT0 Interrupt
ISR (INT0_vect){
	ATOMIC_BLOCK(ATOMIC_FORCEON){
		pulse_rpm_count++;
		if(pulse_rpm_count>=7){
			pulse_rpm_count=0;
			current_rpm_millis = millis();
			rpm = (float)60000/(current_rpm_millis - previous_rpm_millis);
			previous_rpm_millis = current_rpm_millis;
		}
	}
}

void init(void){
	//Port configuration
	//1 -> output, 0 -> input
	DDRB |= 0b00100010;		//Set PB1 (arduino digital pin 9) and PB5 (arduino digital pin 13) as output
	DDRD &= ~(1 << DDD2);     // Set PD2/INT0 (arduino digital pin 2) as input
	
	USART_Init();	//Start USART
	
	//Interrupt Config
	EICRA |= 0b00000011;    //The rising edge of INT0 generates an interrupt request (ISC00, ISC01)
	EIMSK |= (1 << INT0);     //Turns on INT0
	ticks_init();
	sei();          // turn on interrupts
	
	USART_StrTx("WELCOME\r\n");
}

void linear_control(void){
	if(rpm < rpm_set_point-10){
		if(pwm<100){
			pwm++;
		}
	}
	else if(rpm > rpm_set_point+10){
		if(pwm>0){
			pwm--;
		}
	}
	set_duty_PWM(pwm);
}