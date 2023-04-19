/*
 * dryfan.h
 *
 * Created: 5/15/2022 4:49:31 AM
 *  Author: Charith Eranga
 */ 


#ifndef DRYFAN_H_
#define DRYFAN_H_

unsigned char cnt=0;

void speedControl(unsigned int speed){
	float _dutyCycle;
	unsigned int dutyCycle;
	_dutyCycle=speed*(100.0/1024);//speed the clock cycle
	dutyCycle=10+(int)_dutyCycle;
	if(cnt<dutyCycle)	PORTC|=(1<<0);
	if(cnt>=dutyCycle)	PORTC&=~(1<<0);
	if(cnt>=100)	cnt=0;
}

void dryfan(void){
	
	unsigned int adcResult;
	//PortD as output
	PORTC|=(1<<0);
	//PortA as input
	//DDRA=1;
	PORTA&=~(1<<1);
	//Set timer 0 prescaler to 1:8
	TCCR0=0x02;
	//Clear timer 0 overflow flag
	TIFR=0x01;
	//Enable timer 0 interrupt
	TIMSK=0x01;
	//Enable timer 0 interrupt
	TIMSK=0x01;
	//Set global interrupt
	sei();
	//Turn on the ADC module
	ADCSRA|=(1<<ADEN);
	//Select ADC7 channel
	ADMUX|=0x01;

		//Start the conversion
		ADCSRA|=(1<<ADSC);
		//Wait for the completion
		while((ADCSRA&(1<<ADSC))==1);
		//Read the result
		adcResult=ADCL+(ADCH<<8);
		speedControl(adcResult);
		_delay_ms(3000); //need -> time up
		//PORTC=0x00;
		PORTC&=~(1<<0);
}

ISR(TIMER0_OVF_vect){
	//Load TCNT0 with -5 to make a 10 uS interrupt time
	TCNT0=-5;
	cnt+=1;
	TIFR=0x01;
}


#endif /* DRYFAN_H_ */