
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <util/delay.h>

#define SET_ON()			do{PORTD |= (1 << PD1);}while(0)
#define SET_OFF()			do{PORTD &= (~(1 << PD1));}while(0)
#define LED_OFF()			do{PORTA |= (1 << PA1);}while(0)
#define LED_ON()			do{PORTA &= (~(1 << PA1));}while(0)
#define isTimingRequired()	((PIND & (1 << PD0)) > 0)

void setup() {
	// Setup pin direction
	DDRA = (1 << PA1);
	DDRB = 0;
	DDRD = (1 << PD1);

	// Internal pull-ups
	PORTB = 0xff;
	PORTD = (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5);

	LED_ON();
}


// reads user selection 1 to 12.
uint8_t readUserInput(void)
{
	uint8_t retVal = 1;

	uint8_t b = PINB;
	if(b == 0xff){
		// No pin on port B activated. Check port D
		uint8_t d = PIND;

		if((d & (1 << PD2)) == 0){
			retVal = 9;
		}else if((d & (1 << PD3)) == 0){
			retVal = 8;
		}else if((d & (1 << PD4)) == 0){
			retVal = 7;
		}else if((d & (1 << PD5)) == 0){
			retVal = 6;
		}
	}else{
		if((b & (1 << PB7)) == 0){
			retVal = 5;
		}else if((b & (1 << PB6)) == 0){
			retVal = 4;
		}else if((b & (1 << PB5)) == 0){
			retVal = 3;
		}else if((b & (1 << PB4)) == 0){
			retVal = 2;
		}else if((b & (1 << PB3)) == 0){
			retVal = 1;
		}else if((b & (1 << PB2)) == 0){
			retVal = 12;
		}else if((b & (1 << PB1)) == 0){
			retVal = 11;
		}else if((b & (1 << PB0)) == 0){
			retVal = 10;
		}
	}

	return retVal;
}

int main( void )
{
	setup();

	volatile uint8_t targetCount = 0;
	volatile uint8_t totalCount = 0;

	while(1){

		if(isTimingRequired()){
			totalCount = 0;
			targetCount = readUserInput();

			while(totalCount < targetCount){
				LED_OFF();
				SET_ON();
				_delay_ms(1000);
				LED_ON();
				SET_OFF();
				_delay_ms(1000);

				totalCount++;
			}
		}
	}

}
