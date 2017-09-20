
#include "ieclib.h"

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

