/*
 * uart.h
 *
 *  Created on: Dec 30, 2016
 *      Author: rada
 */

#ifndef UART_H_
#define UART_H_

#define USART_BAUDRATE 	(2400)
#define BAUD_PRESCALE 	(((( F_CPU / 16) + ( USART_BAUDRATE / 2) ) / ( USART_BAUDRATE ) ) - 1)
#define waitTxReady()	while (( UCSRA & (1 << UDRE ) ) == 0)

extern volatile uint8_t uart_rx;
extern void uart_tx(uint8_t tx);
extern void uart_init(void);


#endif /* UART_H_ */
