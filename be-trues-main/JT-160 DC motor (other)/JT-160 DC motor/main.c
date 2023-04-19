/*
 * JT-160 DC motor.c
 *
 * Created: 5/23/2022 1:44:57 PM
 * Author : Lenovo pc
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int main(void)
{
	
	DDRA  |= (1<<PA2);  //port pa2 output
	DDRA  |= (1<<PA3);  //port pa3 output

	/* Replace with your application code */
	while (1)
	{
		
		PORTA|=(1<<2);
		_delay_ms(2000);
		
		PORTA|=(1<<2);
		_delay_ms(5000);
		
		PORTA|=(1<<2);
		_delay_ms(2000);
		
PORTA|=(1<<2);
		_delay_ms(5000);
	}
}

