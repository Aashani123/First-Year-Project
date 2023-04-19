/*
 * Brush_Motor1.h
 *
 * Created: 5/21/2022 10:15:06 PM
 *  Author: Charith Eranga
 */ 


#ifndef BRUSH_MOTOR1_H_
#define BRUSH_MOTOR1_H_

void black_brush()
{
	//when black color detected
	DDRB |= (1<<PB3);  //port pb3 output
	DDRB |= (1<<PB4);  //port pb4 output
	
	int count=0;
	while (count<2)
	{
		unsigned int d=2000;
		//clock wise
		PORTB|=(1<<3);		//motor 1 on
		_delay_ms(d);
		PORTB&=~(1<<3);		//motor 1 off
		
		//anti clock
		PORTB|=(1<<4);		//motor 1 on
		_delay_ms(d);
		PORTB&=~(1<<4);		//motor 1 off
		
		count+=1;
	}
}

void other_brush()
{
	DDRB |= (1<<PB5);  //port pb5 output
	DDRB |= (1<<PB6);  //port pb6  output
	int count=0;
	while (count<2){
		unsigned int d=2000;
		//clock wise
		PORTB|=(1<<5);		//motor 1 on
		_delay_ms(d);
		PORTB&=~(1<<5);		//motor 1 off
		
		//anti clock
		PORTB|=(1<<6);		//motor 1 on
		_delay_ms(d);
		PORTB&=~(1<<6);		//motor 1 off
		
		count+=1;
	}
}

#endif /* BRUSH_MOTOR1_H_ */