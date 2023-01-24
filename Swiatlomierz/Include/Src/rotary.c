#include "rotary.h"

static uint8_t rotarystatus=0;
static uint8_t wait=0;

void RotaryInit(void)
{
	//set pins as input
	ROTDDR &= ~((1<<ROTPA)|(1<<ROTPB));
	//enable interrnal pullups;
	ROTPORT |= (1<<ROTPA)|(1<<ROTPB);
}
void RotaryCheckStatus(void)
{
	//reading rotary and button
	//check if rotation is left
	if(ROTA & (!wait))
	wait=1;
	if (ROTB & ROTA & (wait))
	{
		rotarystatus=2;
		wait=2;
	}
	else if(ROTA & (!ROTB) & wait)
	{
		rotarystatus=1;
		wait=2;
	}
	if ((!ROTA)&!(ROTB)&(wait==2))
	wait=0;
}

//return button status
uint8_t RotaryGetStatus(void)
{
	return rotarystatus;
}
//reset status
void RotaryResetStatus(void)
{
	rotarystatus=0;
}

