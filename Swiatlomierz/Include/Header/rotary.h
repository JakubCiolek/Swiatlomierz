#ifndef ROTARY_H
#define ROTARY_H
#include <avr/io.h>
//define port where encoder is connected
#define ROTPORT PORTD
#define ROTDDR DDRD
#define ROTPIN PIND
//define rotary encoder pins
#define ROTPA PIND4
#define ROTPB PIND5
//define macros to check status
#define ROTA !((1<<ROTPA)&ROTPIN)
#define ROTB !((1<<ROTPB)&ROTPIN)
//prototypes
void RotaryInit(void);
void RotaryCheckStatus(void);
uint8_t RotaryGetStatus(void);
void RotaryResetStatus(void);
#endif
