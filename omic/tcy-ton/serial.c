
#include <avr/io.h>

#include "serial.h"

void USART_init( unsigned int ubrr)
{
 /*Set baud rate */
 UBRR0H = (unsigned char)(ubrr>>8);
 UBRR0L = (unsigned char)ubrr;
/* Enable receiver and transmitter */
 UCSR0B = (1<<RXEN0)|(1<<TXEN0);
 /* Set frame format: 8data, 2stop bit */
 UCSR0C = (0<<USBS0)|(3<<UCSZ00);
}

void USART_putc( unsigned char data )
{
 /* Wait for empty transmit buffer */
 while ( !( UCSR0A & (1<<UDRE0)) )
 ;
 /* Put data into buffer, sends the data */
 UDR0 = data;
}

int USART_putchar( char data, FILE *stream )
{
 /* Wait for empty transmit buffer */
 while ( !( UCSR0A & (1<<UDRE0)) )
 ;
 /* Put data into buffer, sends the data */
 UDR0 = data;
 return 0;
}


unsigned char USART_getc( void )
{
 /* Wait for data to be received */
 while ( !(UCSR0A & (1<<RXC0)) )
 ;
 /* Get and return received data from buffer */
 return UDR0;
}

int USART_getchar( FILE *stream )
{
 /* Wait for data to be received */
 while ( !(UCSR0A & (1<<RXC0)) )
 ;
 /* Get and return received data from buffer */
 return UDR0;
}

void USART_flush( void )
{
 unsigned char dummy;
 while ( UCSR0A & (1<<RXC0) ) dummy = UDR0;
}





