#pragma once
/*
IFeedBack.c
    use DynaSinTable to calculate four sinusoid components in misalignment error of magnetic encoder

*/
#ifndef IFeedBack_H_INCLUDED
#define IFeedBack_H_INCLUDED
#include <stdint.h>

typedef struct IFeedBack {
    uint16_t MaxCurr;   //F16.0 maximun current
    uint16_t MinCurr;   //F16.0 minimun current
    uint8_t CurrKi;     //F0.9 K_i coeficient
    uint8_t CurrKi_Expon; //F8.0 K_i coeficient exponent 
    uint8_t CurrKp;     //F0.9 K_p coeficient
    uint8_t CurrKp_Expon; //F8.0 K_p coeficient exponent 
    uint16_t CurrentOut; //F16  Current output
    //output pointers  
    uint16_t* CurrentOut_p;//F16  address of Current output 
    //input pointers
    uint16_t* DiffCountAccIn_p; //F16.0 address of one cycle encoder count
    int8_t* DiffCountIn_p; //F8.0 address of Cmd Sense Count Difference
}IFeedBackStr_t;

/* Current FeedbackControled */
// Maximun Current uint16_t F16.0
#define MAX_CURRENT 1023
// Minimun Current uint16_t F10.6,  MIN_Current=MAX_Current/8
#define MIN_CURRENT 128
#define Curr_EXPON 0

// At Satulate the  Error Count_sat is 8 count (error more than 8 count the feedback is saturated)
// I_max= K_p * Count_sat => K_p= 1024/8= 128
// Current K_p uint8_t F8.0 0~255
#define Curr_K_P 127
#define Curr_K_P_EXPON 0

// lambda=0.95 steady state error count=4
// count_acc=lambd * count_acc +error => count_acc = error/(1-lambda)
// steady state error integer count_acc= 4/(1-0.95)=80
// I_max= K_i * Count_acc => K_p= 1024/80= 12.8
// Current K_I 0~255 F4.4=F8.0>>4 
#define Curr_K_I 127
#define Curr_K_I_EXPON 4

void IFeedBack_lay(IFeedBackStr_t* Str_p);
uint8_t IFeedBack_step(void* void_p);

extern IFeedBackStr_t IFeedBack_str;

#define IFeedBack_LAY(){\
	    IFeedBack_lay(&IFeedBack_str);\
}

#endif
