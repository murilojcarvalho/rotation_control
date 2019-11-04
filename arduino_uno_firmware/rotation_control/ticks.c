#include "ticks.h"

volatile unsigned long int tick_1ms = 0, tick=0, pwm_tick=0, pwm_duty=0;

/***************************************************************************************************************************************************************
*	void tick_init(void)
*	Initiates TIMER0 to generate a 1ms tick
*	Prerequisite:	F_CPU defined in main.h
*
*	Arguments:		Range:				Description:
*	void			N/A					N/A
*
*	Return:			None
****************************************************************************************************************************************************************/
void ticks_init( void )
{
	TCCR0A |= (1 << WGM01);				// Set the Timer0 Mode to CTC
	OCR0A = ((F_CPU*0.0001)/8)-1;		// OCRn =  [ (clock_speed / Prescaler_value) * Desired_time_in_Seconds ] - 1 =  [ (16000000 / 8) * 100us ] - 1 = 199
	TIMSK0 |= (1 << OCIE0A);			//Set the ISR COMPA vect
	TCCR0B |= (1 << CS01);	// set prescaler to 8 and start the timer
}

/***************************************************************************************************************************************************************
*	char ticks(unsigned int interval,unsigned int *tickCompareValue)
*	Triggers a tick (return = 1) when the function is called and the time specified in interval has passed since last tick.
*	Prerequisite:	F_CPU
*
*	Arguments:			Range:				Description:
*	interval			1 - 65535 ms		Time between each tick
*	tickCompareValue	pointer				Stores compare value for next tick. Gets incremented by interval value each time a tick is triggered 
*
*	Return:				0					Tick not trigged
						1					Tick trigged and timerCompareValue updated
****************************************************************************************************************************************************************/
unsigned long int millis(void)
{
	unsigned long int tick_1ms_temp;
	
	ATOMIC_BLOCK(ATOMIC_FORCEON){
		tick_1ms_temp = tick_1ms;
	}
	
	return tick_1ms_temp;
}

/*****************************************************************************************************************************************************************
*	TIMER1 Compare Output A Interrupt Service Routine
*	Increment ms_Counter at a rate of 1 ms
*
******************************************************************************************************************************************************************/
ISR( TIMER0_COMPA_vect )
{
	tick++;
	if(tick >= 10){
		tick=0;
		tick_1ms++;
	}
	
	pwm_tick++;
	if(pwm_tick>=pwm_period){
		pwm_tick = 0;
		PORTB |= 0b00000010;  // Set PB1 (arduino digital pin 9) to 1
	}
	else if(pwm_tick>=pwm_duty){
			PORTB &= 0b11111101; // Set PB1 (arduino digital pin 9) to 0
	}
}

void set_duty_PWM(unsigned char pwm_duty_temp){
	pwm_duty = pwm_duty_temp;
}

