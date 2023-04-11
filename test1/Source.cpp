#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include "DynaSinTable.h"
#include "Svpwm.h"

int main(){
	uint32_t angle = 500;
	uint16_t gain = 512;
	Svpwm_str.FullCountIn_p = &angle;
	Svpwm_str.CurrentIn_p = &gain;
	Svpwm_lay(&Svpwm_str, &SvpwmSinTable_str, SvpwmSinTable_pwm_p, SvpwmSinTable_Theta_p);
	DynaSinTable_lay(&SvpwmSinTable_str, SvpwmSinTable_S0_p, SvpwmSinTable_S_p, SvpwmSinTable_TwoCos_p, SvpwmSinTable_s_p);

	Svpwm_step(&Svpwm_str);

}