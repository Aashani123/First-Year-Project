/*
 * lcd and button.c
 *
 * Created: 4/23/2022 6:15:58 PM
 * Author : Charith Eranga
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "button.h"
#include "lcd_ce.h"


int main(void)
{
	lcd_init();
	int interface=0;
	int fspeed=0,color=3;
	int black=0, other=0, size=10;
	mainscr(black,other);
	
	while (1)
	{
		if (PINA==(1<<3))   // back
		{
			interface+=1;
			if (interface == 1){
				info(size,color);
			}
			else if (interface==2)
			{
				mainscr(black,other);
			}
			else{
				interface=0;
			}
		}
		
		//fan configuration screen
		else if (PINA==(1<<4))			
		{
			fanscr(fspeed);
			_delay_ms(100);
			int select=0;
			while (select==0)
			{
				if(PINA==(1<<7))  //high
				{
					select=0;
					fspeed=1;
					fanscr(fspeed);
				}
				else if (PINA==(1<<6)) //low
				{
					select=0;
					fspeed=0;
					fanscr(fspeed);
				}
				else if (PINA==(1<<3))   //ok button
				{
					select=1;
					updated();
					_delay_ms(50);
				}
			}mainscr(black,other);
		}
		
		else{
			PORTB=0x00;
		}
	}
}

