#include "ticks.h"

volatile unsigned long int tick_1ms = 0;

/***************************************************************************************************************************************************************
*	void tick_init(void)
*	Initiates TIMER1 to generate a 1ms tick
*	Prerequisite:	F_CPU defined in global.h
*
*	Arguments:		Range:				Description:
*	void			N/A					N/A
*
*	Return:			None
****************************************************************************************************************************************************************/
void ticks_init( void )
{
	TCCR1B |= (1 << WGM12);			// Set timer1 in CTC-mode with OCR1A as compare register
	TIMSK1 |= (1 << OCIE1A);		// Enable CTC Output Compare 1A interrupt

	OCR1A = F_CPU/1000;				// timer1-value that corresponds to 1 ms
	TCCR1B |= (1 << CS10);			// Set timer1 clock source to F_CPU with no prescaling	
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
ISR( TIMER1_COMPA_vect )
{
	tick_1ms++;
}

