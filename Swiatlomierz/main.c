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

void DislpayInterface(int mode)
{
	switch(mode)
	{
		case 0:
		lcd_gotoxy(0,0);
		lcd_puts(">ISO|");
		lcd_gotoxy(0,3);
		lcd_puts("  A|");
		lcd_gotoxy(0,6);
		lcd_puts("  T|");
		break;
	
		case 1:

		lcd_gotoxy(0,0);
		lcd_puts(" ISO|");
		lcd_gotoxy(0,3);
		lcd_puts("> A|");
		lcd_gotoxy(0,6);
		lcd_puts("  T|");
		break;	
		case 2:
		lcd_gotoxy(0,0);
		lcd_puts(" ISO|");
		lcd_gotoxy(0,3);
		lcd_puts("  A|");
		lcd_gotoxy(0,6);
		lcd_puts("> T|");
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
		lcd_puts("8.0");
		break;
		case 4:
		lcd_gotoxy(11,3);
		lcd_puts("5.6");
		break;
		case 5:
		lcd_gotoxy(11,3);
		lcd_puts("4.0");
		break;
		case 6:
		lcd_gotoxy(11,3);
		lcd_puts("2.8");
		break;
		case 7:
		lcd_gotoxy(11,3);
		lcd_puts("2.0");
		break;
		case 8:
		lcd_gotoxy(11,3);
		lcd_puts("1.4");
		break;
		default:
		if(A>8)
		{
			lcd_gotoxy(11,3);
			lcd_puts("1.4");		
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
		lcd_gotoxy(9,6);
		lcd_puts("1/2");
		break;
		case 1:
		lcd_gotoxy(9,6);
		lcd_puts("1/4");
		break;
		case 2:
		lcd_gotoxy(9,6);
		lcd_puts("1/8");
		break;
		case 3:
		lcd_gotoxy(9,6);
		lcd_puts("1/15");
		break;
		case 4:
		lcd_gotoxy(9,6);
		lcd_puts("1/30");
		break;
		case 5:
		lcd_gotoxy(9,6);
		lcd_puts("1/60");
		break;
		case 6:
		lcd_gotoxy(9,6);
		lcd_puts("1/125");
		break;
		case 7:
		lcd_gotoxy(9,6);
		lcd_puts("1/250");
		break;
		case 8:
		lcd_gotoxy(9,6);
		lcd_puts("1/500");
		break;
		case 9:
		lcd_gotoxy(9,6);
		lcd_puts("1/1000");
		break;
		case 10:
		lcd_gotoxy(9,6);
		lcd_puts("1/2000");
		break;
		default:
		if(T>10)
		{
			lcd_gotoxy(9,6);
			lcd_puts("1/1000");
		}
		else
		{
			lcd_gotoxy(9,6);
			lcd_puts("1/2");
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
		lcd_puts("800");
		break;
		case 2:
		lcd_gotoxy(11,0);
		lcd_puts("400");
		break;
		case 3:
		lcd_gotoxy(11,0);
		lcd_puts("200");
		break;
		case 4:
		lcd_gotoxy(11,0);
		lcd_puts("100");
		break;
		case 5:
		lcd_gotoxy(11,0);
		lcd_puts("50");
		break;
		default:
		break;
		
	}
}
//================================enkoder ==========================
#define _BV(bit) (1 << (bit))

// W tym przykladzie enkoder jest podlaczony do pinow PIND4 i PIND5
// w main jest wlaczone podciagniecie - jezeli masz te rezystory to nie bedzie to potrzebne


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
	if(przerwa) _delay_ms(10);

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
int8_t Read1StepEncoder()
{
	ReadEncoder();
	int8_t val=enc_delta;
	enc_delta=0;
	return val;
}

int8_t Read2StepEncoder()
{
	ReadEncoder();
	int8_t val=enc_delta;
	enc_delta=val & 1;
	return val>>1;
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
	
	//=============================== deklaracja zmiennych do obliczeñ ===========================
	//short apaturetab[8]={0,1,2,3,4,5,6,7};
	//short timetab[9]={0,1,2,3,4,5,6,7,8};
	//short isotab[6]={0,1,2,3,4,5};
	//short lxtab[9]={0,1,2,3,4,5,6,7,8};
	//float apaturetab[9]={22.0,16.0,11.0,8.0,5.6,4.0,2.8,2.0,1.4};
	//short timetab[10]={2,4,8,15,30,60,125,250,500,1000};
	//short isotab[6]={1600,800,400,200,100,50};
	short lxtab[11]={19200,9600,4800,2400,1200,600,300,150,75,35,20};
	short initA = 6;
	short initT=6;
	short initISO=3;
	short initLx =5;
	short A = initA;
	short T = initT;
	short ISO = initISO;
	short lx;
	//=================================================================================
	
	//================================ ustawienie pinów jako input ====================
	
	//DDRD = 0b00000000;
	PORTD|=1<<PIND2; //przycisk enkodera
	PORTD|=1<<PIND3; // przycisk
	PORTD|=_BV(PIND4) | _BV(PIND5);
	//======================= enkoder =============
	//=============================================
		
	lcd_init(LCD_DISP_ON);    // init lcd and turn on
	short mode=1;
	//lcd_charMode(DOUBLESIZE);
	DislpayInterface(mode); // wyswietlenie interfejsu 
	displayA(A);
	displayT(T);
	displayISO(ISO);
	int dupa=0;
	while(1){
							// =========== obs³uga przycisku do zmiany trybu ========================
		
							if(bit_is_clear(PIND,2)) // zmiana trybu //przycisk enkodera
							{
								if(mode<3)
								{
									mode++;	
									DislpayInterface(mode);			
								}
								else
								{
									mode=0;
									DislpayInterface(mode);
								}
								_delay_ms(15);
							}
							// =================================================================================
		
		
							//===============przycisk pomiaru ========================
		
							if(bit_is_clear(PIND,3)) //przycisk
							{
								char str[20];
								float light = ReadLight(); //tutaj musi byæ odczyt z czujnika
								lcd_gotoxy(10,2);
								sprintf(str, "%g", light);
								lcd_puts(str);
								short shift=0;
								
// 								if(mode==1)
// 								{
// 									//lx = (initLx/lxmes)/2; // tutaj cos mo¿e byæ Ÿle
// 									//shift=(initISO-ISO)+(initA-A)+lx;
// 									T=T-shift;
// 									if(T>10)
// 									{
// 										T=10;
// 									}
// 									else if(T<0)
// 									{
// 										T=0;
// 									}
// 								}
// 								else if(mode==2)
// 								{
// 									//lx = (initLx/lxmes)/2; // tutaj cos mo¿e byæ Ÿle
// 									//shift=(initISO-ISO)+(initT-T)+lx;
// 									A=A-shift;
// 									if(A>8)
// 									{
// 										A=8;
// 									}
// 									else if(A<0)
// 									{
// 										A=0;
// 									}
// 								}
// 									mode=0;
// 									DislpayInterface(mode);	
							}
							//==================================================================
								
								// ======================== plus enkoder ======================
								switch(Read2StepEncoder())  // zwieksza lub zmniejsza x od zero do dziesiec
								{
									case -1 : dupa=1;	 
																
// 									if(mode==0)//iso
// 									{
// 										if(ISO>0)
// 										{
// 											ISO--;
// 											displayISO(ISO);
// 										}
// 									}
// 									else if(mode==1)//A
// 									{
// 										if(A>0)
// 										{
// 											A--;
// 											displayA(A);
// 										}
// 									}
// 									else//T
// 									{
// 										if(T>0)
// 										{
// 											T--;
// 											displayT(T);
// 										}
// 									} 
									break;
									case 0  :	break;
									case 1  : dupa=2;	
																	
// 									if(mode==0)//iso
// 									{
// 										if(ISO<5)
// 										{
// 											ISO++;
// 											displayISO(ISO);
// 										}
// 									}
// 									else if(mode==1)//A
// 									{
// 										if(A<8)
// 										{
// 											A++;
// 											displayA(A);
// 										}
// 									}
// 									else//T
// 									{
// 										if(T<10)
// 										{
// 											T++;
// 											displayT(T);
// 										}
// 									} 
									break;
								};
								if(dupa==1)
								{
									lcd_gotoxy(10,5);
									lcd_puts("-");
								}
								else if (dupa ==2)
								{
									lcd_gotoxy(10,5);
									lcd_puts("+");
								}
									//================================== minus enkoder ==================

								
								
						//======================================================================= 
	}
		
	return 0;
}