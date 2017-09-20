#include <avr/io.h>
#include <avr/interrupt.h>

/* mypins.h */

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

/* end mypins.h */

/* begin iectypes.h */

#define UINT unsigned int
#define BOOL char
#define SINT signed int
#define BYTE char
#define REAL float

/* end iectypes.h */

/* begin ieclib */

struct stTCY{
    //##VAR_INPUT
    UINT IN;
    UINT PT;
    //##END_VAR
    
    //##VAR_OUTPUT
    BOOL Q;
    UINT ET;
    //##END_VAR
    #ifdef IEC_TIME_BY_ISR
    BYTE oldt;
    #endif
};
typedef struct stTCY st_TCY;

struct stTON{
    
    //##VAR_INPUT
    UINT IN;
    UINT PT;
    //##END_VAR
    
    //##VAR_OUTPUT
    UINT Q;
    UINT ET;
    //##END_VAR
};
typedef struct stTON st_TON;

void TCY_init(struct stTCY *st){
    st->Q=0;
    st->ET=0;
    st->IN = 0;
    #ifdef IEC_TIME_BY_ISR
    st->oldt=0;
    #endif
}

void TCY(struct stTCY *st){
    #ifndef IEC_TIME_BY_ISR
    if(st->IN == 1){
        st->ET++;
        if(st->ET >= st->PT){
            st->Q = !st->Q;
            st->ET=0;
        }
    }else{
        st->ET = 0;
        st->Q = 0;
    }
    #else
    if(st->IN == 0){
        st->Q = 0;
        st->ET = 0;
        st->oldt = time_sec_div_100;
    }else{
        if(st->oldt != time_sec_div_100){
            st->oldt = time_sec_div_100;
            st->ET++;
            if(st->ET >= st->PT){
                st->Q = !st->Q;
                st->ET=0;
            }
        }
    }
    #endif
}

void TON_init(struct stTON *st){
    st->Q=0;
    st->ET=0;
}
void TON(struct stTON *st){
    if(st->IN == 0){
        st->Q = 0;
        st->ET = 0;
    }else{
        st->ET++;
        if(st->ET >= st->PT){
            st->Q = 1;
            st->ET--;
        }
    }
}

/* end ieclib */




/* BEGIN PROGRAMA */


 /* INICIO CONTROLE NIVEL AGUA */
 #define BOTAO_NIVEL_AGUA_H (PINB & 0b00100000)
 
 #define LED_NIVEL_AGUA1_H PIN_B4_H
 #define LED_NIVEL_AGUA1_L PIN_B4_L
 
 #define LED_NIVEL_AGUA2_H PIN_B3_H
 #define LED_NIVEL_AGUA2_L PIN_B3_L
 
 #define LED_NIVEL_AGUA3_H PIN_B2_H
 #define LED_NIVEL_AGUA3_L PIN_B2_L
 /* FIM CONTROLE NIVEL AGUA */


int main2(void)
{
    /*  Maquina de estados principal
        estado == 0 == 'desligado';
        estado == 1 == configuracao;
        estado == 2 == ?
    */
    char estado = 0;

    /* Estados nivel agua 
        estado_nivel_agua == 1 == nivel agua baixo;
        estado_nivel_agua == 2 == nivel agua medio;
        estado_nivel_agua == 3 == nivel agua alto;
    */
    char estado_nivel_agua = 1;

    /* Estados programa
        estado_programa == 1 == extra_rapido;
        estado_programa == 2 == pesado;
    */
    char estado_programa = 1;

    st_TCY tcy1, tcy2;
    st_TON ton1, ton2;

    DDRB = 0b11011111;
    DDRC = 0b11111111;
    DDRD = 0b11111111;

    // Exemplo
    //DDRD = 0b11111110;
    /////             ^--- RX como entrada

    char botao_nagua_released = 0;

    while (1) {
        if (estado == 0) {
            LED_NIVEL_AGUA1_L;
            LED_NIVEL_AGUA2_L;
            LED_NIVEL_AGUA3_L;
            // ... Apagar outras leds ainda nao configuradas

            if (BOTAO_NIVEL_AGUA_H /* e outros botoes... */ ) {
                estado = 1;
            }

        // IF estado == 1 == configuracao
        } else if (estado == 1) {

            /* BEGIN Controle Nivel Agua */
            if (BOTAO_NIVEL_AGUA_H && botao_nagua_released == 1) {
                estado_nivel_agua++;
                botao_nagua_released = 0;
    
                if(estado_nivel_agua > 3) {
                    estado_nivel_agua = 1;
                }

                if (estado_nivel_agua == 1) {
                    LED_NIVEL_AGUA1_H;
                    LED_NIVEL_AGUA2_L;
                    LED_NIVEL_AGUA3_L;
                } else if (estado_nivel_agua == 2) {
                    LED_NIVEL_AGUA1_L;
                    LED_NIVEL_AGUA2_H;
                    LED_NIVEL_AGUA3_L;
                } else if (estado_nivel_agua == 3) {
                    LED_NIVEL_AGUA1_L;
                    LED_NIVEL_AGUA2_L;
                    LED_NIVEL_AGUA3_H;
                }
            }
    
            if (!BOTAO_NIVEL_AGUA_H) {
                botao_nagua_released = 1;
            }
            /* END Controle Nivel Agua */

        }
        
    }

    return 0;
}

void setup() {
  main2();
}

void loop() {
  
}

