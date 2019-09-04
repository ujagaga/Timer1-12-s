#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"


void uart_tx(uint8_t tx)
{
	waitTxReady();
	UDR = tx;
}

void uart_init(void)
{
	DDRD |= (1 << PD1);
	UBRRL = (unsigned char)BAUD_PRESCALE;
	UBRRH = (BAUD_PRESCALE >> 8);
	UCSRB = (1<<TXEN);
}
