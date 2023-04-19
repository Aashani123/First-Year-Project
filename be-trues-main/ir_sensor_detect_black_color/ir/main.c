/*
 * ir.c
 *
 * Created: 5/23/2022 9:12:41 AM
 * Author : www
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define f_cpu  16000000UL


int main(void)
{

	PORTB&=~(1<<0);//PIN B0 is input

	while (1)
	{
		if(PINB &(1<<PB0))
		{
			PORTB = PORTB |(1<<PB0);
			_delay_ms(10);
		}
		else
		{
			PORTB &=(1<<PB0);
			_delay_ms(10);
		}

	}
}


