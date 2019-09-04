
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <util/delay.h>
#include "uart.h"

#define SET_ON()	do{PORTD |= (1 << PD3);}while(0)
#define SET_OFF()	do{PORTD &= (~(1 << PD3));}while(0)


void setup() {
	// Setup pin direction
	DDRB = 0xff;
	DDRD = 1 << PD3;

	// Internal pull-ups
	PORTB = 0xff;
	PORTD = (1 << PD6) | (1 << PD5) | (1 << PD4);

	uart_init();
	_delay_ms(100);
}

// Checks if activation pin is triggered
bool isTimingRequired(void)
{
	uint8_t r = PIND & (1 << PD2);
	return (r > 0);
}

// reads user selection 1 to 12.
uint8_t readUserInput(void)
{
	uint8_t retVal = 12;

	uint8_t b = PINB;
	if(b == 0xff){
		// No pin on port B activated. Check port D
		uint8_t d = PIND;

		if((d & (1 << PD6)) == 0){
			retVal = 9;
		}else if((d & (1 << PD5)) == 0){
			retVal = 10;
		}else if((d & (1 << PD4)) == 0){
			retVal = 11;
		}
	}else{
		if((b & (1 << PB7)) == 0){
			retVal = 1;
		}else if((b & (1 << PB6)) == 0){
			retVal = 2;
		}else if((b & (1 << PB5)) == 0){
			retVal = 3;
		}else if((b & (1 << PB4)) == 0){
			retVal = 4;
		}else if((b & (1 << PB3)) == 0){
			retVal = 5;
		}else if((b & (1 << PB2)) == 0){
			retVal = 6;
		}else if((b & (1 << PB1)) == 0){
			retVal = 7;
		}else if((b & (1 << PB0)) == 0){
			retVal = 8;
		}
	}

	return retVal;
}

//void wait1s(void){
//	uint8_t i;
//	for( i = 0; (i < 10) && isTimingRequired(); i++){
//		_delay_ms(100);
//	}
//}

int main( void )
{
	setup();

	while(1){
		uint8_t time, pauseCount;
		uint8_t totalPauseCount = 1;
		uint8_t elapsed = 0;

		time = readUserInput();
		pauseCount = uart_rx;
		if(pauseCount > 12){
			pauseCount = 12;
		}

		if(isTimingRequired()){
			while(elapsed < time){
				SET_ON();
				_delay_ms(1000);
				elapsed ++;

				if((elapsed < time) && (totalPauseCount < pauseCount)){
					SET_OFF();
					totalPauseCount ++;
					_delay_ms(1000);
					elapsed ++;
				}
			}
		}
	}

}
