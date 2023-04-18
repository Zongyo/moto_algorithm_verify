/*
LLFeedBack.c
    use DynaSinTable to calculate four sinusoid components in misalignment error of magnetic encoder

*/
#ifndef LLFeedBack_H_INCLUDED
#define LLFeedBack_H_INCLUDED
#include <stdint.h>

typedef struct LLFeedBack {
    uint16_t LLLimit; //F7.9 Lead Lag angle count limit
    uint8_t LLLimit_Expon; //F8.0 Lead Lag angle count limit exponential
    uint16_t Lambda; //F0.16 accumulator forgetting factor
    uint8_t Lambda_Expon; //F8.0 accumulator forgetting factor exponential
    uint8_t LLKi; //F0.9 K_i coeficient
    uint8_t LLKi_Expon; //F8.0 K_i coeficient exponent 
    uint16_t CountOut; //F16  Count output  
    int16_t DiffCountAcc; //F16.0 diff count accumulation
    uint16_t* CountOut_p;//F16  address of Count output 
    int16_t* DiffCountAcc_p; //F16.0 address of diff count accumulation
    uint16_t* CountIn_p; //F16.0 address of one cycle encoder count
    int8_t* DiffCountIn_p; //F8.0 address of Cmd Sense Count Difference
}LLFeedBackStr_t;

/* Lead-Lag Feedback Contrallor */
// machanic and electronic angle ration 
#define M_E_RATIAL 50
// 90 degree = FULL_SCALE/M_E_RATIAL/4 count = 2^14/50/4=81.92 count, 81.92*2^9=41943 count in F7.9
#define MAX_LEAD_LAG_COUNT 41943
#define MAX_LEAD_LAG_EXPON 9
// lambda 0.95 F0.16 0.95*2^16=62259
#define LAMBDA_MANTISA 62259
#define LAMBDA_EXPON 16 
// K_I 0~255 F0.9=F8.0>>9 
#define LLK_I_MANTISA 127
#define LLK_I_EXPON 9

void LLFeedBack_lay(LLFeedBackStr_t* Str_p);
uint8_t LLFeedBack_step(void* void_p);
extern LLFeedBackStr_t LLFeedBack_str;


#define LLFeedBack_LAY(){\
	    LLFeedBack_lay(&LLFeedBack_str);\
    }



#endif

