/*
Svpwm.c
	use DynaSinTable to calculate four sinusoid components in misalignment error of magnetic encoder

*/
#ifndef Svpwm_H_INCLUDED
#define Svpwm_H_INCLUDED
#include "CFG_Driver.h"
#include "DynaSinTable.h" 
#include <stdio.h>
typedef struct Svpwm {
	uint8_t Channel;
	double Omega;
	volatile uint16_t* CurrentIn_p;//in F16.0 Ampliture input i  maximum is 1024 
	volatile uint16_t* Pwm_p; //F16 i_pwm of all channels maximum is 1024  
	volatile double* Theta_p;//
	volatile uint32_t* FullCountIn_p; //F32.0 address of multi cycle encoder count 
	volatile DynaSinTableStr_t* DynaStr_p;
}SvpwmStr_t;

void Svpwm_lay(SvpwmStr_t* Str_p, DynaSinTableStr_t* DynaStr_p, int16_t* Pwm_p, double* Theta_p);
/* Space vector PWM */
#define Svpwm_FULL_SCALE (2^13)
#define Svpwm_ONE_PERIOD (2^5)
#define Svpwm_CHANNEL 2
#define Svpwm_DIVISION_SHIFT 10 
#define Svpwm_OMEGA  (2*PI/Svpwm_FULL_SCALE*Svpwm_ONE_PERIOD)
/* Following data should be fill after identification*/
/* encoder count at the A phase excitation nearest next to the zero count of encoder*/
#define Svpwm_0A_count 10
#define Svpwm_THETA0 (-2*PI/Svpwm_FULL_SCALE*Svpwm_0A_count)
/* encoder count at the B phase excitation after the A phase*/
#define Svpwm_0B_count 10
#define Svpwm_THETA1 (-2*PI/Svpwm_FULL_SCALE*Svpwm_0B_count)

#ifndef TO_COMPILE_LIB_C

uint8_t Svpwm_step(void* void_p);
extern DynaSinTableStr_t SvpwmSinTable_str ;

extern int32_t SvpwmSinTable_S0_p[Svpwm_CHANNEL * 3]; //F2.30
extern int32_t SvpwmSinTable_S_p[Svpwm_CHANNEL * 3];  //F2.30
extern int32_t SvpwmSinTable_s_p[Svpwm_CHANNEL];    //F2.30
extern uint16_t SvpwmSinTable_pwm_p[Svpwm_CHANNEL];   //F16
extern int32_t SvpwmSinTable_TwoCos_p[Svpwm_CHANNEL]; //F3.29
extern double SvpwmSinTable_Theta_p[Svpwm_CHANNEL] ;
SvpwmStr_t Svpwm_str = {
	.Channel = Svpwm_CHANNEL, //channel oumber of sinusoid waves
	.Omega = Svpwm_OMEGA };

#define Svpwm_LAY(){\
		Svpwm_lay(&Svpwm_str,&SvpwmSinTable_str,SvpwmSinTable_Pwm_p,SvpwmSinTable_Theta_p);\
		DynaSinTable_lay(&SvpwmSinTable_str,SvpwmSinTable_S0_p,SvpwmSinTable_S_p,SvpwmSinTable_TwoCos_p, SvpwmSinTable_s_p);\
	}
#else
extern uint8_t Svpwm_step(void* void_p);

#endif //TO_COMPILE_LIB_C

#endif //Svpwm_H_INCLUDED
