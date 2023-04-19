/*
 * JT-160 Dc motor (black).c
 *

 */ 

#include <avr/io.h>


#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int main(void)
{
	
	DDRA  |= (1<<PA0);  //port pa0 output
	DDRC |= (1<<PC1);  //port pc1 output

	/* Replace with your application code */
	while (1)
	{
		
		PORTA|=(1<<0);
		_delay_ms(2000);
		
		PORTA|=(1<<0);
		_delay_ms(5000);
		
		PORTA|=(1<<0);
		_delay_ms(2000);
		
		PORTA|=(1<<0);
		_delay_ms(5000);
	}
}

