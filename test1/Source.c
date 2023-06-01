#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include "IntPoPwm.h"
#include "SinTable.h"
#include "Compenastor_2.h"

#define D2R 3.1415926 / 180
#define G  16384
int main(){
	uint32_t encoderCount = 0;
	uint16_t current_gain = 1024;
	uint32_t cmd_angle = 0;
	SinTable_LAY();
	Compensator_LAY();
	Compensator_str.FullCountIn_p = &encoderCount;
	Compensator_str.FullCountGoad_p = &cmd_angle;
	IntPoPwm_lay(&IntPoPwm_str, IntPoPwm_PwmOut_p, IntPoPwm_Table_p, IntPoPwm_NextTask_p);
	IntPoPwm_str.CurrentIn_p = &current_gain;
	IntPoPwm_str.CountIn_p = &encoderCount;

	int l = 512;
	for (int i = 0; i < l; i++)
	{
		//IntPoPwm_step(&IntPoPwm_str);
		encoderCount += 64 ;
		Compensator_step(&Compensator_str);
		printf("%d\n" ,);

	}
}
