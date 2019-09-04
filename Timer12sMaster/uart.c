#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"


volatile uint8_t uart_rx;

ISR(USART_RX_vect)
{
	uart_rx = UDR;
}

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
	UCSRB = (1<<TXEN) | (1<<RXEN) | (1 << RXCIE);
	sei();

}
