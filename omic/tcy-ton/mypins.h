

#ifndef _MYPINS_H_
#define _MYPINS_H_ 1


#ifdef PORTA
#define PIN_A0_H PORTA |= 0b00000001
#define PIN_A0_L PORTA &= 0b11111110
#define PIN_A0_R (PINA  &  0b00000001)
#define PIN_A1_H PORTA |= 0b00000010
#define PIN_A1_L PORTA &= 0b11111101
#define PIN_A1_R (PINA  &  0b00000010)
#define PIN_A2_H PORTA |= 0b00000100
#define PIN_A2_L PORTA &= 0b11111011
#define PIN_A2_R (PINA  &  0b00000100)
#define PIN_A3_H PORTA |= 0b00001000
#define PIN_A3_L PORTA &= 0b11110111
#define PIN_A3_R (PINA  &  0b00001000)
#define PIN_A4_H PORTA |= 0b00010000
#define PIN_A4_L PORTA &= 0b11101111
#define PIN_A4_R (PINA  &  0b00010000)
#define PIN_A5_H PORTA |= 0b00100000
#define PIN_A5_L PORTA &= 0b11011111
#define PIN_A5_R (PINA  &  0b00100000)
#define PIN_A6_H PORTA |= 0b01000000
#define PIN_A6_L PORTA &= 0b10111111
#define PIN_A6_R (PINA  &  0b01000000)
#define PIN_A7_H PORTA |= 0b10000000
#define PIN_A7_L PORTA &= 0b01111111
#define PIN_A7_R (PINA  &  0b10000000)
#endif // PORTA

#ifdef PORTB
#define PIN_B0_H PORTB |= 0b00000001
#define PIN_B0_L PORTB &= 0b11111110
#define PIN_B0_R (PINB  &  0b00000001)
#define PIN_B1_H PORTB |= 0b00000010
#define PIN_B1_L PORTB &= 0b11111101
#define PIN_B1_R (PINB  &  0b00000010)
#define PIN_B2_H PORTB |= 0b00000100
#define PIN_B2_L PORTB &= 0b11111011
#define PIN_B2_R (PINB  &  0b00000100)
#define PIN_B3_H PORTB |= 0b00001000
#define PIN_B3_L PORTB &= 0b11110111
#define PIN_B3_HL (PORTB & 0b00001000)
#define PIN_B3_R (PINB  &  0b00001000)
#define PIN_B4_H PORTB |= 0b00010000
#define PIN_B4_L PORTB &= 0b11101111
#define PIN_B4_R (PINB  &  0b00010000)
#define PIN_B5_H PORTB |= 0b00100000
#define PIN_B5_L PORTB &= 0b11011111
#define PIN_B5_R (PINB  &  0b00100000)
#define PIN_B6_H PORTB |= 0b01000000
#define PIN_B6_L PORTB &= 0b10111111
#define PIN_B6_R (PINB  &  0b01000000)
#define PIN_B7_H PORTB |= 0b10000000
#define PIN_B7_L PORTB &= 0b01111111
#define PIN_B7_R (PINB  &  0b10000000)
#endif // PORTB

#ifdef PORTC
#define PIN_C0_H PORTC |= 0b00000001
#define PIN_C0_L PORTC &= 0b11111110
#define PIN_C0_R (PINC  &  0b00000001)
#define PIN_C1_H PORTC |= 0b00000010
#define PIN_C1_L PORTC &= 0b11111101
#define PIN_C1_R (PINC  &  0b00000010)
#define PIN_C2_H PORTC |= 0b00000100
#define PIN_C2_L PORTC &= 0b11111011
#define PIN_C2_R (PINC  &  0b00000100)
#define PIN_C3_H PORTC |= 0b00001000
#define PIN_C3_L PORTC &= 0b11110111
#define PIN_C3_R (PINC  &  0b00001000)
#define PIN_C4_H PORTC |= 0b00010000
#define PIN_C4_L PORTC &= 0b11101111
#define PIN_C4_R (PINC  &  0b00010000)
#define PIN_C5_H PORTC |= 0b00100000
#define PIN_C5_L PORTC &= 0b11011111
#define PIN_C5_R (PINC  &  0b00100000)
#define PIN_C6_H PORTC |= 0b01000000
#define PIN_C6_L PORTC &= 0b10111111
#define PIN_C6_R (PINC  &  0b01000000)
#define PIN_C7_H PORTC |= 0b10000000
#define PIN_C7_L PORTC &= 0b01111111
#define PIN_C7_R (PINC  &  0b10000000)
#endif // PORTC


#ifdef PORTD
#define PIN_D0_H PORTD |= 0b00000001
#define PIN_D0_L PORTD &= 0b11111110
#define PIN_D0_R (PIND  &  0b00000001)
#define PIN_D1_H PORTD |= 0b00000010
#define PIN_D1_L PORTD &= 0b11111101
#define PIN_D1_R (PIND  &  0b00000010)
#define PIN_D2_H PORTD |= 0b00000100
#define PIN_D2_L PORTD &= 0b11111011
#define PIN_D2_R (PIND  &  0b00000100)
#define PIN_D3_H PORTD |= 0b00001000
#define PIN_D3_L PORTD &= 0b11110111
#define PIN_D3_R (PIND  &  0b00001000)
#define PIN_D4_H PORTD |= 0b00010000
#define PIN_D4_L PORTD &= 0b11101111
#define PIN_D4_R (PIND  &  0b00010000)
#define PIN_D5_H PORTD |= 0b00100000
#define PIN_D5_L PORTD &= 0b11011111
#define PIN_D5_R (PIND  &  0b00100000)
#define PIN_D6_H PORTD |= 0b01000000
#define PIN_D6_L PORTD &= 0b10111111
#define PIN_D6_R (PIND  &  0b01000000)
#define PIN_D7_H PORTD |= 0b10000000
#define PIN_D7_L PORTD &= 0b01111111
#define PIN_D7_R (PIND  &  0b10000000)
#endif // PORTD

#endif // _MYPINS_H_

