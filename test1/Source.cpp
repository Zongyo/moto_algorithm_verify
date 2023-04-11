#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include "DynaSinTable.h"
#include "Svpwm.h"

int main(){
	uint32_t angle = 0;
	uint16_t gain = 1024;

	Svpwm_str.FullCountIn_p = &angle;
	Svpwm_str.CurrentIn_p = &gain;
	Svpwm_lay(&Svpwm_str, &SvpwmSinTable_str, SvpwmSinTable_pwm_p, SvpwmSinTable_Theta_p);
	DynaSinTable_lay(&SvpwmSinTable_str, SvpwmSinTable_S0_p, SvpwmSinTable_S_p, SvpwmSinTable_TwoCos_p, SvpwmSinTable_s_p);
	double rad = 0 ;
	uint32_t val1, val2;
	for (int i = 0, ct = 0 ; i < 16384 ; i=i+38,ct++)
	{
		angle = i;
		rad =2*M_PI*50.0*(i/16384.0);
		val1 = int32_t(sin(rad) * 32768.0) + 0x8000;
		val2 = int32_t(cos(rad) * 32768.0) + 0x8000;
		
		Svpwm_step(&Svpwm_str);
		printf("encoder:%5d rad:%4.4f s=%4d c=%4d \n", i, rad, abs(val1 - (int32_t)Svpwm_str.Pwm_p[0]), abs(val2 - (int32_t)Svpwm_str.Pwm_p[1]));
		//printf("sin=%x  cos=%x \n\n", val1, val2);
	}
}