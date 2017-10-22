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




/* BEGIN PROGRAMA main.c */

/* INICIO DEFINES BOTOES E LEDS */
#define BOTAO_NIVEL_AGUA_H  (PINB & 0b00100000)
#define LED_NIVEL_AGUA1_H   PIN_B4_H
#define LED_NIVEL_AGUA1_L   PIN_B4_L
#define LED_NIVEL_AGUA2_H   PIN_B3_H
#define LED_NIVEL_AGUA2_L   PIN_B3_L
#define LED_NIVEL_AGUA3_H   PIN_B2_H
#define LED_NIVEL_AGUA3_L   PIN_B2_L

#define BOTAO_PROGRAMA_H    (PINB & 0b00000010)
#define LED_EXTRA_RAPIDO_H  PIN_B0_H 
#define LED_EXTRA_RAPIDO_L  PIN_B0_L
#define LED_PESADO_H        PIN_D7_H
#define LED_PESADO_L        PIN_D7_L

#define BOTAO_ENXAGUE_H     (PIND & 0b01000000)
#define LED_ENXAGUE_H       PIN_D5_H
#define LED_ENXAGUE_L       PIN_D5_L

#define BOTAO_ETAPAS_H      (PIND & 0b00010000)
#define LED_ETAPA1_H        PIN_D3_H
#define LED_ETAPA1_L        PIN_D3_L
#define LED_ETAPA2_H        PIN_D2_H
#define LED_ETAPA2_L        PIN_D2_L
#define LED_ETAPA3_H        PIN_D1_H
#define LED_ETAPA3_L        PIN_D1_L
#define LED_ETAPA4_H        PIN_D0_H
#define LED_ETAPA4_L        PIN_D0_L

#define LED_MOTOR_ESQ_H     PIN_C1_H
#define LED_MOTOR_ESQ_L     PIN_C1_L
#define LED_MOTOR_DIR_H     PIN_C0_H
#define LED_MOTOR_DIR_L     PIN_C0_L

#define BOTAO_INICIA_H      (PINC & 0b00100000)

#define SENSOR_NIVEL_AGUA1_H  (PINC & 0b00010000)
#define SENSOR_NIVEL_AGUA2_H  (PINC & 0b00001000)
#define SENSOR_NIVEL_AGUA3_H  (PINC & 0b00000100)
/* FIM DEFINES BOTOES E LEDS */

void controlar_nivel_agua(char *estado_nivel_agua, char *botao_nagua_released);
void controlar_programa(char *estado_programa, char *botao_programa_released,
                        int *tempo_molho_longo, int *tempo_lavar,
                        int *tempo_centrifugar);
void controlar_etapas(char *estado_etapa, char *botao_etapas_released, char *estado, struct stTCY *st);
void controlar_enxague_extra(char *enxague_extra, char *botao_enxague_released);

char esta_cheio(char estado_nivel_agua);
char esta_vazio(char estado_nivel_agua);

int main2(void)
{
    DDRB = 0b11011101;
    DDRC = 0b11000011;
    DDRD = 0b10110111;

    // tcy1 = Controla os leds das estapas
    // tcy2 = Controla o tempo do molho longo e fica piscando os leds referentes aos motores
    // tcy3 = Controla o tempo para ficar lavando
    st_TCY tcy1, tcy2, tcy3;
    st_TON ton1, ton2;
    TCY_init(&tcy1);
    TCY_init(&tcy2);
    TCY_init(&tcy3);

    /*  Maquina de estados principal
    estado == 0 == 'desligado';
    estado == 1 == configuracao;
    estado == 2 == lavando (vai para uma segunda maquina de estados)
    */
    char estado = 0;
    char botao_inicia_released = 0;
    
    /* Estados nivel agua 
    estado_nivel_agua == 1 == nivel agua baixo;
    estado_nivel_agua == 2 == nivel agua medio;
    estado_nivel_agua == 3 == nivel agua alto;
    */
    char estado_nivel_agua = 1;
    // Variavel para controle
    char botao_nagua_released = 0;
    
    /* Estados programa
    estado_programa == 1 == extra_rapido;
    estado_programa == 2 == pesado;
    */
    char estado_programa = 1;
    char botao_programa_released = 0;

    /* Enxague extra
    enxague_extra == 0 == sem enxague extra
    enxague_extra == 1 == com exangue extra
    */
    char enxague_extra = 0;
    char botao_enxague_released = 0;

    /* Etapas
    estado_etapa == 0 == molho longo
    estado_etapa == 1 == lavar
    estado_etapa == 2 == enxaguar
    estado_etapa == 3 == centrifugar
    */
    char estado_etapa = 0;
    char botao_etapas_released = 0;
    
    /* Variavel para controle os estados individuais de cada etapa
    0-1 para controlar os estados do molho longo
    2-4 para controlar os estados da lavagem
    5-8 para controlar os estados do enxague
    9-10 para controlar os estados de centrifugar
    */
    char estado_individual = 0;

    int tempo_molho_longo   = 10000;
    int tempo_lavar         = 12000;
    int tempo_centrifugar   = 5000;
    
    while (1) {

        tcy1.IN = 1;
        tcy1.PT = 1000;
        TCY(&tcy1);

        // IF estado == 1 == desligado
        if (estado == 0) {
            // Apaga todos os leds
            LED_NIVEL_AGUA1_L;
            LED_NIVEL_AGUA2_L;
            LED_NIVEL_AGUA3_L;
            LED_EXTRA_RAPIDO_L;
            LED_ENXAGUE_L;
            LED_ETAPA1_L;
            LED_ETAPA2_L;
            LED_ETAPA3_L;
            LED_ETAPA4_L;
            LED_MOTOR_ESQ_L;
            LED_MOTOR_DIR_L;
            
            // Se algum botao pressionar, passa para o proximo estado
            if (BOTAO_NIVEL_AGUA_H || BOTAO_PROGRAMA_H || BOTAO_ENXAGUE_H ||
                BOTAO_ETAPAS_H || (BOTAO_INICIA_H && botao_inicia_released)) {
                estado = 1;
                botao_inicia_released = 0;
            } else if (!BOTAO_INICIA_H) {
                botao_inicia_released = 1;
            }
            
        // IF estado == 1 == configuracao
        } else if (estado == 1) {
            controlar_nivel_agua(&estado_nivel_agua, &botao_nagua_released);
            controlar_programa(&estado_programa, &botao_programa_released,
                                &tempo_molho_longo, &tempo_lavar, &tempo_centrifugar);
            controlar_enxague_extra(&enxague_extra, &botao_enxague_released);
            controlar_etapas(&estado_etapa, &botao_etapas_released, &estado, &tcy1);

            if (BOTAO_INICIA_H && botao_inicia_released == 1)  {
                estado = 2;
                botao_inicia_released = 0;
            } else if (!BOTAO_INICIA_H) {
                botao_inicia_released = 1;
            }

        // IF estado == 2 == Lavando
        } else if (estado == 2) {
            
            // IF estado_etapa == 0 == molho longo
            // 0. Verifica se tem agua, se nao enche ate nivel especificado
            // 1. Espera tempo_molho_longo millisegundos
            if (estado_etapa == 0) {
                // Se o estado individual da lavagem não estar no range especifico
                // Retorne para o inicio daquele estado.
                if (estado_individual > 1)
                    estado_individual = 0;
                
                if (estado_individual == 0) {
                    if ( !esta_cheio(estado_nivel_agua) ) {
                        // Acende led azul (faltou portas) e fica enchendo
                    } else {
                        estado_individual = 1;
                        TCY_init(&tcy2);
                    }
                } else if (estado_individual == 1) {
                    tcy2.IN = 1;
                    tcy2.PT = tempo_molho_longo;
                    TCY(&tcy2);

                    if (tcy2.Q == 1) {
                        estado_etapa = 1;
                        estado_individual = 2;
                    }
                }

            // IF estado_etapa == 1 == lavar
            // 2. Verifica se tem agua, se nao enche
            // 3. Fica alternando motor por tempo_lavar ms
            // 4. Esvazia
            } else if (estado_etapa == 1) {
                // Se o estado individual da lavagem não estar no range especifico
                // Retorne para o inicio daquele estado.
                if (estado_individual < 1 || estado_individual > 4)
                    estado_individual = 2;

                if (estado_individual == 2) {
                    if ( !esta_cheio(estado_nivel_agua) ) {
                        // Acende led azul (faltou portas) e fica enchendo
                    } else {
                        estado_individual = 3;
                        TCY_init(&tcy2);
                        TCY_init(&tcy3);
                    }
                } else if (estado_individual == 3) {
                    tcy2.IN = 1;
                    tcy2.PT = 500;
                    TCY(&tcy2);
                    if (tcy2.Q) LED_MOTOR_ESQ_H; else LED_MOTOR_ESQ_L;
                    if (!tcy2.Q) LED_MOTOR_DIR_H; else LED_MOTOR_DIR_L;

                    tcy3.IN = 1;
                    tcy3.PT = tempo_lavar;
                    TCY(&tcy3);
                    if (tcy3.Q) {
                        estado_individual = 4;
                        TCY_init(&tcy3);
                        LED_MOTOR_DIR_L;
                        LED_MOTOR_ESQ_L;
                    }
                } else if (estado_individual == 4) {
                    if ( esta_cheio(estado_nivel_agua) ) {
                        // Acende led azul (faltou portas) e esvazia
                    } else {
                        estado_etapa = 2;
                        estado_individual = 5;
                    }
                }

            // IF estado_etapa == 2 == Enxaguar
            // 5. Verifica se tem agua, se tem esvazia
            // 6. Enche de agua ate nivel especificado
            // 7. Fica alternando motor por 5 segundos
            // 8. Esvazia (se tiver enxague extra, volte etapa 5)
            } else if (estado_etapa == 2) {
                // Se o estado individual da lavagem não estar no range especifico
                // Retorne para o inicio daquele estado.
                if (estado_individual < 5 || estado_individual > 8) {
                    estado_individual = 5;
                }

                if (estado_individual == 5) {
                    if (esta_cheio(estado_nivel_agua)) {
                        //Acende led Azul (faltou portas) e esvazia
                    } else {
                        estado_individual = 6;
                    }
                }
                else if (estado_individual == 6) {
                    if ( !esta_cheio(estado_nivel_agua) ) {
                        // Acende led azul (faltou portas) e fica enchendo
                    } else {
                        estado_individual = 7;
                        TCY_init(&tcy2);
                        TCY_init(&tcy3);
                    }
                } else if (estado_individual == 7) {
                    tcy2.IN = 1;
                    tcy2.PT = 500;
                    TCY(&tcy2);
                    if (tcy2.Q) LED_MOTOR_ESQ_H; else LED_MOTOR_ESQ_L;
                    if (!tcy2.Q) LED_MOTOR_DIR_H; else LED_MOTOR_DIR_L;

                    tcy3.IN = 1;
                    tcy3.PT = 5000;
                    TCY(&tcy3);
                    if (tcy3.Q) {
                        estado_individual = 8;
                        TCY_init(&tcy3);
                        LED_MOTOR_DIR_L;
                        LED_MOTOR_ESQ_L;
                    }
                } else if (estado_individual == 8) {
                    if ( esta_vazio(estado_nivel_agua) ) {
                        // Acende led azul (faltou portas) e esvazia
                    } else {
                        if (enxague_extra == 1) {
                            estado_individual = 5;
                            enxague_extra = 0;
                            LED_ENXAGUE_L;
                        } else {
                            estado_etapa = 3;
                            estado_individual = 9;
                            LED_MOTOR_DIR_L;
                            LED_MOTOR_ESQ_L;
                        }
                    }
                }

            // IF estado_etapa == 3 == Centrifugar
            // 9. Verifica se tem agua, se tiver esvazia
            // 10. Fica girando motor para um sentido por tempo_centrifugar ms
            } else if (estado_etapa == 3) {
                // Se o estado individual da lavagem não estar no range especifico
                // Retorne para o inicio daquele estado.
                if (estado_individual < 9 || estado_individual > 10) {
                    estado_individual = 9;
                }

                if (estado_individual == 9) {
                    if ( !esta_vazio(estado_nivel_agua)) {
                        // Acende led azul (faltou portas) e esvazia
                    } else {
                        estado_individual = 10;
                        TCY_init(&tcy3);
                        LED_MOTOR_DIR_H;
                        LED_MOTOR_ESQ_L;
                    }
                } else if (estado_individual == 10) {
                    tcy3.IN = 1;
                    tcy3.PT = tempo_centrifugar;
                    TCY(&tcy3);
                    if (tcy3.Q) {
                        LED_MOTOR_DIR_L;
                        LED_MOTOR_ESQ_L;
                        TCY_init(&tcy3);
                        estado_etapa = 0;
                        estado = 1;
                    }
                }
            }

            controlar_enxague_extra(&enxague_extra, &botao_enxague_released);
            controlar_etapas(&estado_etapa, &botao_etapas_released, &estado, &tcy1);

            if (BOTAO_INICIA_H && botao_inicia_released == 1)  {
                estado = 0;
                botao_inicia_released = 0;
            } else if (!BOTAO_INICIA_H) {
                botao_inicia_released = 1;
            }
        }

        _delay_ms(1);
        
    }

    return 0;
}

void setup() {
    main2();
}

void loop() {
    
}

void controlar_nivel_agua(char *estado_nivel_agua, char *botao_nagua_released) {
    if (BOTAO_NIVEL_AGUA_H && *botao_nagua_released == 1) {
        (*estado_nivel_agua)++;
        *botao_nagua_released = 0;
        
        if(*estado_nivel_agua > 3) {
            *estado_nivel_agua = 1;
        }
        
    } else if (!BOTAO_NIVEL_AGUA_H) {
        *botao_nagua_released = 1;
    }
    
    if (*estado_nivel_agua == 1) {
        LED_NIVEL_AGUA1_H;
        LED_NIVEL_AGUA2_L;
        LED_NIVEL_AGUA3_L;
    } else if (*estado_nivel_agua == 2) {
        LED_NIVEL_AGUA1_L;
        LED_NIVEL_AGUA2_H;
        LED_NIVEL_AGUA3_L;
    } else if (*estado_nivel_agua == 3) {
        LED_NIVEL_AGUA1_L;
        LED_NIVEL_AGUA2_L;
        LED_NIVEL_AGUA3_H;
    }
}

void controlar_programa(char *estado_programa, char *botao_programa_released,
                        int *tempo_molho_longo, int *tempo_lavar,
                        int *tempo_centrifugar) {
    if (BOTAO_PROGRAMA_H && *botao_programa_released == 1) {
        (*estado_programa)++;
        *botao_programa_released = 0;
        
        if(*estado_programa > 2) {
            *estado_programa = 1;
        }
        
    } else if (!BOTAO_PROGRAMA_H) {
        *botao_programa_released = 1;
    }

    if (*estado_programa == 1) {
        LED_EXTRA_RAPIDO_H;
        LED_PESADO_L;
        *tempo_molho_longo   = 10000;
        *tempo_lavar         = 12000;
        *tempo_centrifugar   = 5000;
    } else if (*estado_programa == 2) {
        LED_EXTRA_RAPIDO_L;
        LED_PESADO_H;
        *tempo_molho_longo   = 15000;
        *tempo_lavar         = 15000;
        *tempo_centrifugar   = 8000;
    }
}

void controlar_enxague_extra(char *enxague_extra, char *botao_enxague_released) {
    if (BOTAO_ENXAGUE_H && (*botao_enxague_released) == 1) {
        (*enxague_extra)++;
        *botao_enxague_released = 0;
        
        if(*enxague_extra > 1) {
            *enxague_extra = 0;
        }
    } else if (!BOTAO_ENXAGUE_H) {
        *botao_enxague_released = 1;
    }

    if (*enxague_extra == 0) {
        LED_ENXAGUE_L;
    } else if (*enxague_extra == 1) {
        LED_ENXAGUE_H;
    }
}

void controlar_etapas(char *estado_etapa, char *botao_etapas_released, 
                        char *estado, struct stTCY *st) {
    if (BOTAO_ETAPAS_H && (*botao_etapas_released) == 1) {
        (*estado_etapa)++;
        *botao_etapas_released = 0;

        if (*estado_etapa > 3) {
            *estado_etapa = 0;
        }

        LED_MOTOR_DIR_L;
        LED_MOTOR_ESQ_L;
    } else if (!BOTAO_ETAPAS_H) {
        *botao_etapas_released = 1;
    }

    if (*estado_etapa == 0) {
        if (*estado == 1 || st->Q) LED_ETAPA1_H; else LED_ETAPA1_L;
        LED_ETAPA2_H;
        LED_ETAPA3_H;
        LED_ETAPA4_H;
    } else if (*estado_etapa == 1) {
        LED_ETAPA1_L;
        if (st->Q || *estado == 1) LED_ETAPA2_H; else LED_ETAPA2_L;
        LED_ETAPA3_H;
        LED_ETAPA4_H;
    } else if (*estado_etapa == 2) {
        LED_ETAPA1_L;
        LED_ETAPA2_L;
        if (st->Q || *estado == 1) LED_ETAPA3_H; else LED_ETAPA3_L;
        LED_ETAPA4_H;
    } else if (*estado_etapa == 3) {
        LED_ETAPA1_L;
        LED_ETAPA2_L;
        LED_ETAPA3_L;
        if (st->Q || *estado == 1) LED_ETAPA4_H; else LED_ETAPA4_L;
    }

}

char esta_cheio(char estado_nivel_agua) {
    if (estado_nivel_agua == 1 && SENSOR_NIVEL_AGUA1_H && !SENSOR_NIVEL_AGUA2_H
            && !SENSOR_NIVEL_AGUA3_H)
        return 1;
    
    if (estado_nivel_agua == 2 && SENSOR_NIVEL_AGUA1_H && SENSOR_NIVEL_AGUA2_H
            && !SENSOR_NIVEL_AGUA3_H)
        return 1;
    
    if (estado_nivel_agua == 3 && SENSOR_NIVEL_AGUA1_H && SENSOR_NIVEL_AGUA2_H
            && SENSOR_NIVEL_AGUA3_H)
        return 1;
    
    return 0;
}

char esta_vazio(char estado_nivel_agua) {
    if (!SENSOR_NIVEL_AGUA1_H && !SENSOR_NIVEL_AGUA2_H && !SENSOR_NIVEL_AGUA3_H)
        return 1;
    
    return 0;
}