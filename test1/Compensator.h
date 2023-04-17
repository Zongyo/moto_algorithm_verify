/*
Compensator.c
    use DynaSinTable to calculate four sinusoid components in misalignment error of magnetic encoder

*/

#ifndef Compensator_H_INCLUDED
#define Compensator_H_INCLUDED
#include <stdint.h>
#include <math.h>
#include "DynaSinTable.h" 

/* compensator */
#define Comp_FULL_SCALE 16384
#define Comp_ONE_PERIOD 256
#define Comp_CHANNEL 4
#define Comp_DIVISION_SHIFT 18 
#define Comp_OMEGA  ( 2*PI*Comp_ONE_PERIOD/Comp_FULL_SCALE )
/* fill the following macro by identification result*/
//偏心誤差的最大gain
#define Comp_EXPON 24
#define AMP0 0
#define AMP1 1274
#define AMP2 0
#define AMP3 426
#define AMP4 0
#define Comp_THETA1 0
#define Comp_THETA2 0.1
#define Comp_THETA3 0
#define Comp_THETA4 0.1

typedef struct Compensator {
    int32_t A0;//Fx.Expon DC offset
    uint8_t Expon; //F8.0 group exponent of offset bias and sinusoid waves error
    uint8_t Channel;//F8.0
    double Omega;  // Dynamic Look Up Table interval angle 
    uint16_t Count; //F16.0 encoder count after compensation
    int8_t CountDiff; //F8.0 difference of goad count and sensed count 
    uint16_t* Count_p;//F16.0 compensated single cycle encoder count 
    int8_t* CountDiff_p;//F8.0 difference of goad and sensed encoder count 
    uint32_t* A_p;//Fx.Expon Amplitude of 0 to 4 mode	
    int32_t* s_p; //F2.32 sin values of all channels at the input count 
    double* Theta_p;//
    uint32_t* FullCountIn_p; //F32.0 address of multi cycle encoder count before compensated 
    uint32_t* FullCountGoad_p; //F32.0 address of position goad of multi cycle encoder count  
    DynaSinTableStr_t* DynaStr_p;
}CompensatorStr_t;

void Compensator_lay(CompensatorStr_t* Str_p, DynaSinTableStr_t* DynaStr_p, uint32_t* A_p, int32_t* s_p, double* Theta_p);

extern uint8_t Compensator_step(void* void_p);
extern int32_t CompSinTable_S0_p[];
extern int32_t CompSinTable_S_p[];
extern int32_t CompSinTable_s_p[];
extern int32_t CompSinTable_TwoCos_p[];
extern uint32_t Compensator_A_p[];
extern double CompSinTable_Theta_p[];
extern DynaSinTableStr_t CompSinTable_str;
extern CompensatorStr_t Compensator_str;
#endif //TO_COMPILE_LIB_C

#define Compensator_LAY(){\
	Compensator_lay(&Compensator_str,&CompSinTable_str,Compensator_A_p,CompSinTable_s_p,CompSinTable_Theta_p);\
    DynaSinTable_lay(&CompSinTable_str,CompSinTable_S0_p,CompSinTable_S_p,CompSinTable_TwoCos_p, CompSinTable_s_p);\
}

