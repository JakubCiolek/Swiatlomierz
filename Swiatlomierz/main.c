/*
 * main.c
 *
 * Created: 1/14/2023 2:54:46 AM
 *  Author: Kubotronic
 */ 					/* crystal f				 */

#include <xc.h>
#include <util/delay.h>
#include "BH1750.h"
//****main.c****//
#include "lcd.h"
short absolute(short n)
{
	if(n<0)
	{
		return -n;
	}
	else
	{
		return n;
	}
}
void DislpayInterface(int mode)
{
	switch(mode)
	{
		case 0:
		lcd_gotoxy(0,0);
		lcd_puts(">ISO|");
		lcd_gotoxy(0,3);
		lcd_puts("   A|");
		lcd_gotoxy(0,6);
		lcd_puts("   T|");
		break;
	
		case 1:

		lcd_gotoxy(0,0);
		lcd_puts(" ISO|");
		lcd_gotoxy(0,3);
		lcd_puts(">  A|");
		lcd_gotoxy(0,6);
		lcd_puts("   T|");
		break;	
		case 2:
		lcd_gotoxy(0,0);
		lcd_puts(" ISO|");
		lcd_gotoxy(0,3);
		lcd_puts("   A|");
		lcd_gotoxy(0,6);
		lcd_puts(">  T|");
		break;
		default:
		break;
	}
};
//float apaturetab[9]={22.0,16.0,11.0,8.0,5.6,4.0,2.8,2.0,1.4};
void displayA(short A)
{
	switch(A)
	{
		case 0:
		lcd_gotoxy(11,3);
		lcd_puts("22.0");
		break;
		case 1:
		lcd_gotoxy(11,3);
		lcd_puts("16.0");
		break;
		case 2:
		lcd_gotoxy(11,3);
		lcd_puts("11.0");
		break;
		case 3:
		lcd_gotoxy(11,3);
		lcd_puts("8.0 ");
		break;
		case 4:
		lcd_gotoxy(11,3);
		lcd_puts("5.6 ");
		break;
		case 5:
		lcd_gotoxy(11,3);
		lcd_puts("4.0 ");
		break;
		case 6:
		lcd_gotoxy(11,3);
		lcd_puts("2.8 ");
		break;
		case 7:
		lcd_gotoxy(11,3);
		lcd_puts("2.0 ");
		break;
		case 8:
		lcd_gotoxy(11,3);
		lcd_puts("1.4 ");
		break;
		default:
		if(A>8)
		{
			lcd_gotoxy(11,3);
			lcd_puts("1.4 ");		
		}
		else
		{
			lcd_gotoxy(11,3);
			lcd_puts("22.0");
		}
		
		break;
		
	}
}
//short timetab[10]={2,4,8,15,30,60,125,250,500,1000};
void displayT(short T)
{
	switch(T)
	{
		case 0:
		lcd_gotoxy(11,6);
		lcd_puts("1/2    ");
		break;
		case 1:
		lcd_gotoxy(11,6);
		lcd_puts("1/4    ");
		break;
		case 2:
		lcd_gotoxy(11,6);
		lcd_puts("1/8    ");
		break;
		case 3:
		lcd_gotoxy(11,6);
		lcd_puts("1/15   ");
		break;
		case 4:
		lcd_gotoxy(11,6);
		lcd_puts("1/30   ");
		break;
		case 5:
		lcd_gotoxy(11,6);
		lcd_puts("1/60   ");
		break;
		case 6:
		lcd_gotoxy(11,6);
		lcd_puts("1/125  ");
		break;
		case 7:
		lcd_gotoxy(11,6);
		lcd_puts("1/250  ");
		break;
		case 8:
		lcd_gotoxy(11,6);
		lcd_puts("1/500  ");
		break;
		case 9:
		lcd_gotoxy(11,6);
		lcd_puts("1/1000 ");
		break;
		case 10:
		lcd_gotoxy(11,6);
		lcd_puts("1/2000 ");
		break;
		default:
		if(T>10)
		{
			lcd_gotoxy(11,6);
			lcd_puts("1/2000 ");
		}
		else
		{
			lcd_gotoxy(11,6);
			lcd_puts("1/2    ");
		}
		break;
		
	}
}

//short isotab[6]={1600,800,400,200,100,50};
void displayISO(short ISO)
{
	switch(ISO)
	{
		case 0:
		lcd_gotoxy(11,0);
		lcd_puts("1600");
		break;
		case 1:
		lcd_gotoxy(11,0);
		lcd_puts("800 ");
		break;
		case 2:
		lcd_gotoxy(11,0);
		lcd_puts("400 ");
		break;
		case 3:
		lcd_gotoxy(11,0);
		lcd_puts("200 ");
		break;
		case 4:
		lcd_gotoxy(11,0);
		lcd_puts("100 ");
		break;
		case 5:
		lcd_gotoxy(11,0);
		lcd_puts("50  ");
		break;
		default:
		break;
		
	}
}
//================================enkoder ==========================
#define _BV(bit) (1 << (bit))

int8_t enc_delta;

void ReadEncoder()
{
	static int8_t last;
	static uint8_t laststate;
	static uint8_t counters[2];	//Tablica zawieraj¹ca liczniki
	int8_t newpos, diff;
	
	uint8_t state=PINB;
	if(((state^laststate) & _BV(PIND4)) && (counters[0]==0))
	{
		counters[0]=200;
		laststate&=(~_BV(PIND4));
		laststate|=(state & _BV(PIND4));
	}

	if(((state^laststate) & _BV(PIND5)) && (counters[1]==0))
	{
		counters[1]=200;
		laststate&=(~_BV(PIND5));
		laststate|=(state & _BV(PIND5));
	}

	uint8_t przerwa=0;
	for(uint8_t c=0;c<2;c++)
	if(counters[c])
	{
		counters[c]--;
		przerwa=1;			//Robimy opóŸnienie tylko jeœli któryœ z liczników by³ !=0
	}
	if(przerwa) _delay_ms(1);

	newpos=0;
	if((PIND & _BV(PIND4))==0) newpos=3;
	if((PIND & _BV(PIND5))==0) newpos^=1;	// konwersja kodu Graya na binarny
	diff=last-newpos;
	if(diff & 1)
	{				// bit 0 = krok
		last=newpos;
		enc_delta+=(diff & 2)-1;	//bit 1 - kierunek
	}
}

int8_t Read4StepEncoder()
{
	ReadEncoder();
	int8_t val=enc_delta;
	enc_delta=val & 3;
	return val>>2;
}
//==================================================================
int main(void){
	short A = 4;
	short T =7;
	short ISO = 2;
	//================================ ustawienie pinów jako input ====================
	PORTD|=1<<PIND2; //przycisk enkodera
	PORTD|=1<<PIND3; // przycisk
	//======================= enkoder =============
	PORTD|=_BV(PIND4) | _BV(PIND5);
	//=============================================
	lcd_init(LCD_DISP_ON);    // init lcd and turn on
	short mode=1;
	//lcd_charMode(DOUBLESIZE);
	DislpayInterface(mode); // wyswietlenie interfejsu 
	displayA(A);
	displayT(T);
	displayISO(ISO);
	while(1){
							// =========== obs³uga przycisku do zmiany trybu ========================
		
							if(bit_is_clear(PIND,2)) // zmiana trybu //przycisk enkodera
							{
								if(mode<3)
								{
									mode++;		
								}
								else
								{
									mode=0;
								}
								DislpayInterface(mode);
								_delay_ms(15);
							}
							// =================================================================================
		
		
							//===============przycisk pomiaru ========================
		
							if(bit_is_clear(PIND,3)) //przycisk
							{
								if(mode==1)
								{
									float light = ReadLight(); //tutaj musi byæ odczyt z czujnika
									
									short lx=0;
									short lxtab[12]={14144,7072,3536,1768,884,442,221,110,55,27,13,8};
										if(light>15000)
										{
											lx=0;
											
										}
										else
										{
											for(uint8_t i=0 ;i<11;i++)
											{
												lxtab[i]= absolute(lxtab[i]-light);
											}
											short min=lxtab[0];
											for(uint8_t i=0 ;i<11;i++)
											{
												if(lxtab[i]<=min)
												{
													min=lxtab[i];
													lx=i;
												}
											}
											
										}
									
									short evlx = 5-lx;
									short evIS0 = 2-ISO;
									short shift;
										short evA = A-4;
										shift=evA+evIS0+evlx;
										T=7+shift;
										if(T>10)
										{
											T=10;
										}
										else if(T<0)
										{
											T=0;
										}
										displayT(T);
										shift=0;
										//char str[10];
										//lcd_gotoxy(1,2);
										//sprintf(str, "%g", light);
										//lcd_puts(str);
								}
								else if (mode==2)
								{
									float light = ReadLight(); //tutaj musi byæ odczyt z czujnika
									
									short lx=0;
									short lxtab[11]={14144,7072,3536,1768,884,221,110,55,27,13,8};
									for(uint8_t i=0 ;i<11;i++)
									{
										lxtab[i]= absolute(lxtab[i]-light);
									}
									short min=lxtab[0];
									for(uint8_t i=0 ;i<11;i++)
									{
										if(lxtab[i]<=min)
										{
											min=lxtab[i];
											lx=i;
										}
									}
									short evlx = 5-lx;
									short evIS0 = 2-ISO;
									short shift;
									
									
									short evT= 7-T;
									shift=evT+evIS0+evlx;
									A=4-shift;
									if(A>8)
									{
										A=8;
									}
									else if(A<0)
									{
										A=0;
									}
									displayA(A);
									shift=0;
									//char str[10];
									//lcd_gotoxy(1,2);
									//sprintf(str, "%g", light);
									//lcd_puts(str);
								}
								

								 
							}
							//==================================================================
								
								// ======================== plus enkoder ======================
								switch(Read4StepEncoder())  // zwieksza lub zmniejsza x od zero do dziesiec
								{
									case 1 : 
									if(mode==0)//iso
 									{
 										if(ISO>0)
 										{
 											ISO--;
 											displayISO(ISO);

 										}
 									}
 									else if(mode==1)//A
 									{
 										if(A>0)
 										{
 											A--;
 											displayA(A);
											
 										}
 									}
 									else//T
 									{
 										if(T>0)
 										{
 											T--;
 											displayT(T);
											 
 										}
 									} 
									break;
									case 0  :	break;
									case -1  : 	
																	
 									if(mode==0)//iso
 									{
 										if(ISO<5)
 										{
 											ISO++;
 											displayISO(ISO);
											
 										}
 									}
 									else if(mode==1)//A
 									{
 										if(A<8)
 										{
 											A++;
 											displayA(A);
											
 										}
 									}
 									else//T
 									{
 										if(T<10)
 										{
 											T++;
 											displayT(T);
											
 										}
 									} 
									break;
								};
								
								
								
									//================================== minus enkoder ==================

								
								
						//======================================================================= 
	}
		
	return 0;
}