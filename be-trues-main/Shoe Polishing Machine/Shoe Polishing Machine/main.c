/*
 * lcd and button.c
 *
 * Created: 4/23/2022 6:15:58 PM
 * Author : Charith Eranga
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "lcd_ce.h"
#include "Ultrasonic_distance.h"
#include "dryfan.h"
#include "Brush_Motor.h"


int other_polish_level();
int black_polish_level();
int color_Detection();
void Sound();


int main()
{
	DDRA=DDRA &(~(1<<7))&(~(1<<6))&(~(1<<4))&(~(1<<5));		//button
	DDRA  |= (1<<PA0);  //port pa1 output
	DDRC  |= (1<<PC1); //port pc1 output
	DDRA  |= (1<<PA2);  //port pa2 output
	DDRA  |= (1<<PA3);  //port pa3 output
	DDRD = DDRD |(1<<7)|(1<<6)|(1<<4)|(1<<5);
	lcd_init();
	int interface=1;
	int black,other,color,dry=1;
	int size= maxShoe();
	
	black=black_polish_level();
	other=other_polish_level();
	color=color_Detection();
	
	lcd_cmd(0x01);
	lcd_cmd(0x80);	//1st row
	lcd_str("1. Quick START");
	lcd_cmd(0xC0);  //2nd row
	lcd_str("2. Setting");
	
	
	while (1)
	{		
		if (PINA==(1<<4))   //quick start button
		{
			black=black_polish_level();
			other=other_polish_level();
			color=color_Detection();
			_delay_ms(300);
			
			if (color==1)	//black color shoes detect
			{
				lcd_cmd(0x01);  //clear display
				lcd_rc(1,1);
				lcd_str("Black Color");
				lcd_rc(2,1);
				lcd_str("Detected");
				_delay_ms(300);
				
				if (black==1)	//black polish level high
				{
					if (dry==1)		//if dry fan activated 1, deactivated 0
					{
						lcd_cmd(0x01);  //clear display
						lcd_rc(1,1);
						lcd_str("Dry-Fan is");
						lcd_rc(2,1);
						lcd_str("Activated");
						dryfan();	//dryfan working
					}
				
					lcd_cmd(0x01);
					lcd_cmd(0x80);	//1st row display
					lcd_str("Machine Status :");
					lcd_cmd(0xC0);  //2nd row display
					lcd_str("Polishing");
					
					if (size>=1 && size<5)
					{   
						PORTD|=(1<<4);	//pipe carrying motor1 on
						PORTA|=(1<<0);	//pump motor on
						_delay_ms(850);
						PORTA&=~(1<<0);	//pump motor off
						PORTD&=~(1<<4);	//pipe carrying motor1 off
						
							PORTD|=(1<<5);		//motor 1 on pipe back to the start position
							_delay_ms(850);
							PORTD&=~(1<<5);
						
					}else if (size>=5 && size<10)
					{
						//PORTA = 0x05; //pump motor on
						PORTA|=(1<<0);
						PORTD|=(1<<4);	//pipe carrying motor1 on
						_delay_ms(750);
						PORTA&=~(1<<0);  //pump motor off
						PORTD&=~(1<<4);		//pipe carrying motor1 off
						
						PORTD|=(1<<5);		//motor 1 on pipe back to the start position
						_delay_ms(750);
						PORTD&=~(1<<5);
						
					}else if (size>=10 && size<15)
					{
						//PORTA = 0x05;	//pump motor on
						PORTA|=(1<<0);
						PORTD|=(1<<4);	//pipe carrying motor1 on
						_delay_ms(650);
						PORTA&=~(1<<0);	//pump motor off
						PORTD&=~(1<<4);		//pipe carrying motor1 off
						
						PORTD|=(1<<5);		//motor 1 on pipe back to the start position
						_delay_ms(650);
						PORTD&=~(1<<5);
					}
					else{
						lcd_cmd(0x01);
						lcd_cmd(0x80);	//1st row
						lcd_str("Shoe size Error");
						Sound();
						break;								//shoe should be under 35cm and over 19cm
					}
					
					black_brush();							// black polish brush motor working
					dryfan();
					
					lcd_cmd(0x01);
					lcd_cmd(0x80);	//1st row
					lcd_str("Polishing");
					lcd_cmd(0xC0);  //2nd row
					lcd_str("Completed !!!");
					Sound();
				}
				else{
					lcd_cmd(0x01);  //clear display
					lcd_rc(1,1);
					lcd_str("Black Polish is");
					lcd_rc(2,1);
					lcd_str("level Low");
					Sound();
					_delay_ms(300);
				}
			}
			else{							//other color shoes detect
				lcd_cmd(0x01);				
				lcd_rc(1,1);
				lcd_str("Other Colour");
				lcd_rc(2,1);
				lcd_str("Detected");
				_delay_ms(300);
				
				if (other==1)					//black polish level high							
				{
					if (dry==1)					//if dry fan activated 1, deactivated 0
					{
						lcd_cmd(0x01);			
						lcd_rc(1,1);
						lcd_str("Dry-Fan is");
						lcd_rc(2,1);
						lcd_str("Activated");
						dryfan();				//dryfan activated
					}
			
					lcd_cmd(0x01);
					lcd_cmd(0x80);	//1st row
					lcd_str("Machine Status :");
					lcd_cmd(0xC0);  //2nd row
					lcd_str("Polishing");
					
					if (size>=1 && size<5)
					{
						PORTA|=(1<<2);		//pump motor on
						PORTD|=(1<<6);		//pipe carrying motor2 on
						_delay_ms(850);
						PORTA&=~(1<<2);		//pump motor off
						PORTD&=~(1<<6);		//pipe carrying motor2 off
						
						PORTD|=(1<<7);		//motor 1 (pipe back to the start position)
						_delay_ms(850);
						PORTD&=~(1<<7);		
						
					}else if (size>=5 && size<10)
					{
						PORTA|=(1<<2);		//pump motor on
						PORTD|=(1<<6);		//pipe carrying motor2 on
						_delay_ms(750);
						PORTA&=~(1<<2);		//pump motor off
						PORTD&=~(1<<6);		//pipe carrying motor2 off
						
						PORTD|=(1<<7);		//motor 1 (pipe back to the start position)
						_delay_ms(750);
						PORTD&=~(1<<7);		
						
					}else if (size>=10 && size<15)
					{
						PORTA|=(1<<2);		//pump motor on
						PORTD|=(1<<6);		//pipe carrying motor2 on
						_delay_ms(650);
						PORTA&=~(1<<2);		//pump motor off
						PORTD&=~(1<<6);		//pipe carrying motor2 off
						
						PORTD|=(1<<7);		//motor 1 (pipe back to the start position)
						_delay_ms(650);
						PORTD&=~(1<<7);		
						
					}else{
						lcd_cmd(0x01);
						lcd_cmd(0x80);	//1st row
						lcd_str("Shoe size Error");
						Sound();
						break;				//shoe should be under 35cm and over 19cm
					}
					
					other_brush();			// black polish brush motor working
					dryfan();				

					lcd_cmd(0x01);
					lcd_cmd(0x80);	//1st row
					lcd_str("Polishing");
					lcd_cmd(0xC0);  //2nd row 
					lcd_str("Completed !!!");
					Sound();
					}
					
					else{
					lcd_cmd(0x01);  //clear display
					lcd_rc(1,1);
					lcd_str("Other Polish is");
					lcd_rc(2,1);
					lcd_str("level Low");
					Sound();
					_delay_ms(300);
				}
			}
			
		}
		
		else if (PINA==(1<<5))	//Menu	
		{
			if (interface == 1){
				
				info(size,color); 
				interface=2;
			}
			else if (interface==2)
			{
				mainscr(black,other); 
				interface=3;
			}
			else if (interface==3)
			{
				fanscr(dry);		
				int select=0;
				while (select==0)
				{
					if(PINA==(1<<7))  //high
					{
						select=0; 
						dry=1;		// activated
						fanscr(dry);
					}
					else if (PINA==(1<<6)) //low
					{
						select=0; 
						dry=0;		// Deactivated
						fanscr(dry);
					}
					else if (PINA==(1<<4))   //save button
					{
						select=1;		 
						updated();
						_delay_ms(50);
						
						lcd_cmd(0x01);
						lcd_cmd(0x80);	//1st row
						lcd_str("1. Quick START");
						lcd_cmd(0xC0);  //2nd row
						lcd_str("2. Setting");
						
					}
					else if (PINA==(1<<5)) //exit without saving
					{
						interface=1;
						select=1;
					}
				}
				interface=1;
			}
		}
	}
}


int black_polish_level(){
	int black;
	DDRB = DDRB &(~(1<<2))&(~(1<<1));
	
	if((PINB & (1<<1))!=0){
		black=1;
	}
	else{  
		lcd_cmd(0x01);
		lcd_cmd(0x80);	//1st row
		lcd_str("Polish level low");
		lcd_cmd(0xC0);
		lcd_str("Black");
		_delay_ms(300);
		black=0;
	}
	return black;
}

int other_polish_level(){
	int other;
	DDRB = DDRB &(~(1<<2))&(~(1<<1));
	
	if((PINB & (1<<2))!=0){
		other=1;
	}
	else{
		lcd_cmd(0x01);
		lcd_cmd(0x80);	//1st row
		lcd_str("Polish level low");
		lcd_cmd(0xC0);
		lcd_str("Other");
		_delay_ms(300);
		other=0;
	}
	return other;
}

//shoe color detection
int color_Detection()
{
	DDRB = DDRB &(~(1<<0));
	int black_shoes=0;
	int color_select=0;
	int pin_value=PINB & (1<<0);
	
	if (pin_value==1)
	{
		black_shoes=1;
	}
	if (pin_value!=1)
	{		
		lcd_cmd(0x01);  //clear display
		lcd_rc(1,1);
		lcd_str("Choose correct");
		lcd_rc(2,1);
		lcd_str("colour:");

		while (color_select==0)
		{
			if (PINA ==(1<<6))
			{
				black_shoes=1;
				lcd_rc(2,9);
				lcd_str(" Black");
				color_select=1;
			}
			else if (PINA ==(1<<7))
			{
				black_shoes=0;
				lcd_rc(2,9);
				lcd_str(" Other");
				color_select=1;
			}
			else if (PINA==(1<<4))   //save button
			{
				color_select=1;
				updated();
				_delay_ms(100);
				break;
			}
			color_select=0;
		}
	}
	return black_shoes;
}


//buzzer code
void Sound()
{
	DDRB  |= (1<<PB7);// Configure pin DDB0 as the output of buzzer
	int error=1;
		if(error==1){
			PORTB=PORTB |(1<<7);/* Switch is open, pin_status = 1, buzzer will sound;*/
			_delay_ms(50);
			PORTB=PORTB &(~(1<<7));
			error=0;
		}
}