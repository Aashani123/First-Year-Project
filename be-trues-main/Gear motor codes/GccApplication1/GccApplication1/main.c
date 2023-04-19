/*
 * Author : Aashani
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRD |= (15<<4);		//make portD 4-7 pins as output
	
	while(1)
	{
		unsigned int d=3000;
		
		//clock wise
		PORTD|=(1<<4);		//motor 1 on
		_delay_ms(d);
		PORTD&=~(1<<4);		//motor 1 off
		_delay_ms(d);
		PORTD|=(1<<6);		//motor 2 on
		_delay_ms(d);
		PORTD&=~(1<<6);		//motor 2 off
		_delay_ms(d);
		
		//anti clock	
		PORTD|=(1<<5);		//motor 1 on
		_delay_ms(d);
		PORTD&=~(1<<5);		//motor 1 off
		_delay_ms(d);
		PORTD|=(1<<7);		//motor 2 on
		_delay_ms(d);
		PORTD&=~(1<<7);		//motor 2 off
		_delay_ms(d);
	}
}



