#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include "DynaSinTable.h"
#include "Svpwm.h"
#include "Compensator.h"
int main(){
	uint32_t angle = 0;
	uint16_t gain = 1024;

	Svpwm_str.FullCountIn_p = &angle;
	Svpwm_str.CurrentIn_p = &gain;

	Compensator_str.FullCountIn_p = &angle;
	CompSinTable_str.FullCountIn_p = &angle;

	DynaSinTable_lay(&CompSinTable_str, CompSinTable_S0_p, CompSinTable_S_p, CompSinTable_TwoCos_p, CompSinTable_s_p);
	Compensator_lay(&Compensator_str, &CompSinTable_str, Compensator_A_p, CompSinTable_s_p, CompSinTable_Theta_p);
	DynaSinTable_lay(&CompSinTable_str, CompSinTable_S0_p, CompSinTable_S_p, CompSinTable_TwoCos_p, CompSinTable_s_p);
	
	//for svpwm test
	/*
	Svpwm_lay(&Svpwm_str, &SvpwmSinTable_str, SvpwmSinTable_pwm_p, SvpwmSinTable_Theta_p);
	DynaSinTable_lay(&SvpwmSinTable_str, SvpwmSinTable_S0_p, SvpwmSinTable_S_p, SvpwmSinTable_TwoCos_p, SvpwmSinTable_s_p);
	double rad = 0 ;
	uint32_t val1, val2 ,val3;
	for (int i = 0, ct = 0 ; i < 16384 ; i=i+1,ct++)
	{
		angle = i;
		rad =2*M_PI*50.0*(i/16384.0);
		val1 = int32_t(sin(rad) * 32768.0) + 0x8000;
		val2 = int32_t(cos(rad) * 32768.0) + 0x8000;
		
		Svpwm_step(&Svpwm_str);
		
		printf("encoder:%5d rad:%4.4f real=%4d calculate=%4d \n", i, rad,val1, (int32_t)Svpwm_str.Pwm_p[0]);
		//printf("sin=%x  cos=%x \n\n", val1, val2);
	}
	*/
	//for comp test
	for (int i = 0, ct = 0; i < 16384; i = i + 16, ct++)
	{
		angle = i;
		Compensator_step((void*)&Compensator_str);
	}
}