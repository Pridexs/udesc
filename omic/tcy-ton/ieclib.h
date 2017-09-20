
#ifndef _IECLIB_H_
#define _IECLIB_H_ 1

#include "iectypes.h"

//#define IEC_TIME_BY_ISR



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
void TCY_init(struct stTCY *st);
void TCY(struct stTCY *st);


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
void TON_init(struct stTON *st);
void TON(struct stTON *st);


#endif // _IECLIB_H_

