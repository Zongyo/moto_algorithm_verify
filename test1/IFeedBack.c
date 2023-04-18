/*
IFeedBack.c
	use DynaSinTable to calculate four sinusoid components in misalignment error of magnetic encoder

*/
#define TO_COMPILE_LIB_C
/*HW Interrupt Sharer Timer0*/
#include "IFeedBack.h"

IFeedBackStr_t IFeedBack_str = {
	.MaxCurr = MAX_CURRENT ,
	.MinCurr = MIN_CURRENT ,
	.CurrKp = Curr_K_P ,
	.CurrKi = Curr_K_I ,
	.CurrKp_Expon = Curr_K_P_EXPON ,
	.CurrKi_Expon = Curr_K_I_EXPON
};

void IFeedBack_lay(IFeedBackStr_t* Str_p) {
	Str_p->CurrentOut_p = &Str_p->CurrentOut;
}

uint8_t IFeedBack_step(void* void_p) {
	IFeedBackStr_t* Str_p = (IFeedBackStr_t*)void_p;
	uint16_t Current;
	Current = Str_p->CurrKi * (*Str_p->DiffCountAccIn_p) +
		Str_p->CurrKp * (*Str_p->DiffCountIn_p);//F16.0 <= F8.0*F16.0+F8.0*F8.0
	if (Current > Str_p->MaxCurr)
		Current = Str_p->MaxCurr;
	if (Current < Str_p->MinCurr)
		Current = Str_p->MinCurr;
	Str_p->CurrentOut = Current;//F16.0=F16.0+F7.9
	return 0;
}

