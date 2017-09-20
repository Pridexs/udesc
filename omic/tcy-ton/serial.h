
#ifndef _SERIAL_H_
#define _SERIAL_H_ 1

#include <stdio.h>
#include <stdint.h>

#define FOSC F_CPU // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void USART_init( unsigned int ubrr);
void USART_putc( unsigned char data );
int USART_putchar( char data, FILE *stream );
unsigned char USART_getc( void );
int USART_getchar( FILE *stream );
void USART_flush( void );



#endif


