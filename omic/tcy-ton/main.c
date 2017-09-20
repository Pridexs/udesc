/*
 */

#define LED_H PIN_D6_H
#define LED_L PIN_D6_L


#include <avr/io.h>
#include <avr/interrupt.h>

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

#include <util/delay.h>
#include "serial.h"
#include "mypins.h"

#include "ieclib.h"


FILE mystdout = FDEV_SETUP_STREAM(USART_putchar, USART_getchar, _FDEV_SETUP_RW);


int main(void)
{
    char i,l;
    st_TCY tcy1, tcy2;
    st_TON ton1, ton2;

    DDRB = 0b11001110;
    DDRC = 0b11111111;
    DDRD = 0b11111010;
    ///             ^--- RX como entrada

    USART_init(9600);
    stdout = stdin = &mystdout;

    i=240;
    l=0;
    PIN_D5_H;

    /**
    O programa a seguir foi construído com base no diagrama abaixo
    - Pisca D5 a cada 50ms
    - Pisca D7 a cada 10ms se B0 está pressionado
    - Se D2 está pressionado, liga D3 após 20ms e, após mais 20ms liga D4
    - Ligar B3 ao pressionar B5 e só desligar qdo B4 for pressionado
        --Apertou um vez B5, B3 liga e fica mesmo que B5 se liberado.
          B3 só vai desligar ao pressionar B4

    Sim, você pode interconectar os blocos para resolver os problemas
    É como se estivesse fazendo um esquema elétrico, cada bloco é um componente
    com a sua funcionalidade.


                   tcy1
    -----------[IN  TCY  Q]------(PIN_D5)
         50----[PT      ET]

                               tcy2
    ----|PIN_B0_R|---------[IN  TCY  Q]------(PIN_D7)
                     10----[PT      ET]

                                ton1
    ----|PIN_D2_R|---------[IN  TON  Q]---+--(PIN_D3)
                     20----[PT      ET]   |
                                          |              ton2
                                          +---------[IN  TON  Q]------(PIN_D4)
                                              20----[PT      ET]

    --+-|PIN_B5_R|---------+-------|!PIN_B4_R|---------------(PIN_B3)
      |                    |
      +-|PIN_B3_HL|--------+


    */

    /* cada bloco é uma estrutura e precisa ser inicializado */
    TCY_init(&tcy1);
    TCY_init(&tcy2);
    TON_init(&ton1);
    TON_init(&ton2);

    while (1) {
        /* Para cada bloco, sempre setar primeiro as entradas,
        depois executá-lo e depois ler suas saídas */
        tcy1.IN = 1;
        tcy1.PT = 50;
        TCY(&tcy1);
        if(tcy1.Q) PIN_D5_H; else PIN_D5_L;

        tcy2.IN = PIN_B0_R;
        tcy2.PT = 10;
        TCY(&tcy2);
        if(tcy2.Q) PIN_D7_H; else PIN_D7_L;

        /* Executar primeiro os blocos mais a esquerda do diagrama. */
        ton1.IN = PIN_D2_R;
        ton1.PT = 20;
        TON(&ton1);
        if(ton1.Q) PIN_D3_H; else PIN_D3_L;

        ton2.IN = ton1.Q;
        ton2.PT = 20;
        TON(&ton2);
        if(ton2.Q) PIN_D4_H; else PIN_D4_L;

        if(!PIN_B4_R && (PIN_B5_R || PIN_B3_HL)) PIN_B3_H; else PIN_B3_L;

        _delay_ms(1);
    }

    return 0;
}

