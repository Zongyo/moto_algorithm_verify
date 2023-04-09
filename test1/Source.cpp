#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include"DynaSinTable.h"


int main(){
	uint32_t angle = 0;

	int32_t sine = (int32_t)(sin(M_PI / 16) * (1UL <<30));
	int32_t sine7875 = (int32_t)(sin(M_PI * 7 / 16) * (1UL << 30));
	int32_t sine_3[6] = { -sine , 0 , sine , sine7875 ,1 << 30, sine7875 };
	int32_t table[6] = { 0 };
	int32_t two_cos[2] = { (int32_t)(2 * cos(M_PI / 16) * (1UL << 29)),(int32_t)(2 * cos(M_PI / 16) * (1UL << 29)) };
	int32_t sin_step[2] = {0};
	uint32_t full_mech_angle = angle*1024.0/360;

	
	printf("deg = %d\n", angle);

	DynaSinTableStr_t CompSinTable_str = { 0 };
	CompSinTable_str.FullCountIn_p = &full_mech_angle;

	CompSinTable_str.FullScale = 1024;
	CompSinTable_str.Channel = 2;
	CompSinTable_str.CountPerPeri = 32;
	CompSinTable_str.DiviShift = 10;

	//CompSinTable_str

	uint8_t error;
	DynaSinTable_lay(&CompSinTable_str, sine_3, table, two_cos, sin_step);
	double l[3];
	double s[3] , c[3];
	double N[3];
	double x = full_mech_angle % 1024;
	s[0] = (double)table[0] ;
	s[1] = (double)table[1] ;
	s[2] = (double)table[2] ;

	c[0] = (double)table[3];
	c[1] = (double)table[4];
	c[2] = (double)table[5];

	N[0] = (double)CompSinTable_str.N[0];
	N[1] = (double)CompSinTable_str.N[1];
	N[2] = (double)CompSinTable_str.N[2];
	
	l[0] = (x - N[1]) * (x - N[2]) / (2048);
	l[1] = -(x - N[0]) * (x - N[2]) / (1024);
	l[2] = (x - N[0]) * (x - N[1]) / (2048);
	double ans = (s[0] * l[0] + s[1] * l[1] + s[2] * l[2]) / (1UL << 30);
	double ans2 = (c[0] * l[0] + c[1] * l[1] + c[2] * l[2]) / (1UL << 30);
	//printf("sin(%f) = %f\n", x*360/1024, ans);
	//printf("cos(%f) = %f\n", x * 360 / 1024, ans2);
	for (int i = 0; i <2048; i++)
	{
		if (i % 32 == 0)
		{
			printf("---------------------------------------------\n");
			if (i%1024 == 0)
			{
				printf("***************************************************\n");
			}
		}
		full_mech_angle = i;
		error = DynaSinTable_step(&CompSinTable_str);
		double a = sin(M_PI * (i % 1024) / 512);
		double b = (double)CompSinTable_str.s_p[0] / (1UL << 30);
		double err = a - b;
		if (a-b>0.001 || a - b < -0.001)
		{
			printf("deg=%f ans=%.4f cal=%.4f err=%f \n",(i%1024)*360.0/1024,a,b, err);
		}
	}

	for (int i = 2048; i > 0; i--)
	{
		if (i % 32 == 0)
		{
			printf("---------------------------------------------\n");
			if (i % 1024 == 0)
			{
				printf("***************************************************\n");
			}
		}
		full_mech_angle = i;
		error = DynaSinTable_step(&CompSinTable_str);
		double a = sin(M_PI * (i % 1024) / 512);
		double b = (double)CompSinTable_str.s_p[0] / (1UL << 30);
		double err = a - b;
		if (err > 0.001 || err < -0.001)
		{
			printf("deg=%f ans=%.4f cal=%.4f err=%f \n", (i % 1024)*360.0 / 1024, a, b, err);
		}
	}

}