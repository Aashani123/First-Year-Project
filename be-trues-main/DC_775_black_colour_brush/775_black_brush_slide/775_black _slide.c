/*
 * dc_code.c
 *
 * Created: 5/19/2022 8:48:03 PM
 * Author : www
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 1600000UL


int main(void)
{
	//detect black  color
	
	DDRB |= (1<<PB3);  //port pb3 output
	DDRB |= (1<<PB4);  //port pb4 output

	
    /* Replace with your application code */
    while (1) 
    {
		
		unsigned int d=3000;
		
		//clock wise
		PORTB|=(1<<3);		//motor 1 on
		_delay_ms(d);
		PORTB&=~(1<<3);		//motor 1 off
		_delay_ms(d);
		
		
		//anti clock
		PORTB|=(1<<4);		//motor 1 on
		_delay_ms(d);
		PORTB&=~(1<<4);		//motor 1 off

}
}

