#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "lcd_ce.h"
#include "ultrasonic.h"

int main()
{
	lcd_init();
	
	// Ultrasonic --------------------------
	char numberString[4];
	uint16_t d1, d2;
	int distance, previous_distance = 0;
	_delay_ms(100);
	// -------------------------------------
	
	while (1)
	{		
		// get ultrasonic reading ------------------------------------------------------------------
		HCSR04Init(PD0);
		HCSR04Trigger(PD0);
		d1 = GetPulseWidth(PD1); 
		
		HCSR04Init(PD2);
		HCSR04Trigger(PD2);
		d2 = GetPulseWidth(PD3);

		if(d1 == US_ERROR || d2 == US_ERROR)
		{
			lcd_cmd(0x80);
			lcd_str("Error!");
		}
		else
		{
			distance = (d1 > d2)? ((d1 - d2)*0.034/2.0 + 1) : ((d2 - d1)*0.034/2.0 + 1);
			
			if (distance != previous_distance)
			{
				lcd_clear();
				
				lcd_cmd(0x80);
				itoa(distance, numberString, 10);
				lcd_str(numberString);
				lcd_str(" cm");
				
				previous_distance = distance;
			}
			
			_delay_ms(30);
		}
		// -----------------------------------------------------------------------------------------
	}
	
	return 0;
}
