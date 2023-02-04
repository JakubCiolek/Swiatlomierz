
#include "BH1750.h"

float ReadLight(){

	uint8_t datain[1]={0x20};
	uint8_t tab[2] = {10,10};
	tw_init(TW_FREQ_400K,true);
	if(tw_master_transmit(0x23, datain,1,false) != 0)
	{
		return 123.3;
	}
	_delay_ms(150);
	if(tw_master_receive(0x23,tab,2)!=0)
	{
		return 321.1;
	}
	float lux = (tab[0]*256+tab[1])/1.2;
	return lux;
}