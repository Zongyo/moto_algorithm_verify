/*
Svpwm_cfg_2c.h
	use DynaSinTable to calculate four sinusoid components in misalignment error of magnetic encoder
usage :
	0. Modify the configuration macro in this file to match your need
	1. Include this file
	2. Call Svpwm_LAY()  to layout Svpwm
	3. Connect Svpwm_str.TaskId to previous stage Task Block
	4. Connect Svpwm_str.CurrentIn_p,  to up-Stream Task Block
	5. Connect Svpwm_str.FullCountIn_p to up-Stream Task Block
	6. Connect Svpwm_str.PwmOut_p to down-Stream TaskBlock
*/
#include <math.h>
#define IntPoPwm_NEXTNUM 1
/* Space vector PWM */
/* Step motor 2 phase need 2 channel of pwm out*/
#define IntPoPwm_CHANN 2
/* Step motor has 200 Step for 14bits encoder has 1<<14 counts
2^14 counts= 200 Step  => 1 count = 200/2^14 step
take 1/2 step as a uint => 1 step = 2 uint
1Count =200/2^14 step => 1Count= 400/2^14 uint
omega= 100/2^12 uint/Count  = 100>>12=OmegaMan>>OmegaExp
	OmegaMan = 100
	OmegaExp =12
unit = count * omega uint/count
unit(F16) =(count(F16) * OmegaMan) >>OmegaExp
unit(F3.13)%(2*Chann<<13) =((count(F16) * OmegaMan) >> (OmegaExp-13))% (2*Chann<<13)

*/
#define IntPoPwm_OMEGAMAN  100
#define IntPoPwm_OMEGAEXP  12
#define OFFSET 512
/* IntPoPwm_ALPHA  is the Phase angle in Algular uint
 The 1'st A phase QCount to this positive side of the zero count of encoder
 for example 1'st A phase count is 2 then IntPoPwm_ALPHA is 2
*/
#define IntPoPwm_ALPHA  2

#define IntPoPwm_MdWt (int16_t)(8192/sqrt(2.0))
/* for 10 bits 2 channel pwm
(1,0)(0,1)(-1,0)(0,-1), 1: (1<<10)-1 0:(1<<9)-1 -1:0
*/

#define MAX_CURRENT 511.0
#define MIN_CURRENT (-511.0)
#define NO_CURRENT 0.0

#define IntPoPwm_Table_INI {\
		{MAX_CURRENT,NO_CURRENT},\
		{NO_CURRENT,MAX_CURRENT},\
		{MIN_CURRENT,NO_CURRENT},\
		{NO_CURRENT,MIN_CURRENT}}



