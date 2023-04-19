/*
 * Ultrasonic_distance.h
 *
 * Created: 5/14/2022 7:20:06 PM
 *  Author: Charith Eranga
 */ 


#ifndef ULTRASONIC_DISTANCE_H_
#define ULTRASONIC_DISTANCE_H_

#define US_PORT PORTD           // we have connected the Ultrasonic sensor on port C. to use the ultrasonic we need two pins of the ultrasonic to be connected on port C
#define	US_PIN	PIND            // we need to initialize the pin resistor when we want to take input.
#define US_DDR 	DDRD            // we need data-direction-resistor (DDR) to set the direction of data flow. input or output. we will define it later, now we're just naming it.

#define US_ERROR		-1      // we're defining two more variables two know if the ultrasonic sensor is working or not
#define	US_NO_OBSTACLE	-2

int distance;
char numberString[4];

void HCSR04Init(uint8_t trig)
{
	// we're setting the trigger pin as output as it will generate ultrasonic sound wave
	US_DDR|=(1<<trig);
}

void HCSR04Trigger(uint8_t trig)
{   // this function will generate ultrasonic sound wave for 15 microseconds
	//Send a 10uS pulse on trigger line
	
	US_PORT|=(1<<trig);	//high
	_delay_us(15);				//wait 15uS
	US_PORT&=~(1<<trig);	//low
}

uint16_t GetPulseWidth(uint8_t pos)
{
	// this function will be used to measure the pulse duration. When the ultra sound echo back after hitting an object
	// the microcontroller will read the pulse using the echo pin of the ultrasonic sensor connected to it.
	
	uint32_t i,result;

	// Section - 1: the following lines of code before the section - 2 is checking if the ultrasonic is working or not
	// it check the echo pin for a certain amount of time. If there is no signal it means the sensor is not working or not connect properly
	for(i=0;i<600000;i++)
	{
		if(!(US_PIN & (1<<pos)))
		continue;	//Line is still low, so wait
		else
		break;		//High edge detected, so break.
	}

	if(i==600000)
	return US_ERROR;	//Indicates time out
	
	//High Edge Found
	
	// Section -2 : This section is all about preparing the timer for counting the time of the pulse. Timers in microcontrllers is used for timimg operation
	//Setup Timer1
	TCCR1A=0X00;
	TCCR1B=(1<<CS11);	// This line sets the resolution of the timer. Maximum of how much value it should count.
	TCNT1=0x00;			// This line start the counter to start counting time

	// Section -3 : This section checks weather the there is any object or not
	for(i=0;i<600000;i++)                // the 600000 value is used randomly to denote a very small amount of time, almost 40 miliseconds
	{
		if(US_PIN & (1<<pos))
		{
			if(TCNT1 > 60000) break; else continue;   // if the TCNT1 value gets higher than 60000 it means there is not object in the range of the sensor
		}
		else
		break;
	}

	if(i==600000)
	return US_NO_OBSTACLE;	//Indicates time out

	//Falling edge found

	result=TCNT1;          // microcontroller stores the the value of the counted pulse time in the TCNT1 register. So, we're returning this value to the
	// main function for utilizing it later

	//Stop Timer
	TCCR1B=0x00;

	if(result > 60000)
	return US_NO_OBSTACLE;	//No obstacle
	else
	return (result>>1);
}


int maxShoe(){
	
	uint16_t d1, d2;
	//int distance;
	_delay_ms(100);
	
	
	HCSR04Init(PD0);
	HCSR04Trigger(PD0);
	d1 = GetPulseWidth(PD1);
	
	HCSR04Init(PD2);
	HCSR04Trigger(PD2);
	d2 = GetPulseWidth(PD3);

	if(d1 == US_ERROR || d2 == US_ERROR)
	{
		lcd_cmd(0x80);
		lcd_str("!");
	}
	else
	{
		if (d1 == d2){
			distance=d1;
			distance=distance*0.034/2.0 + 1;
		}
		if (d1>d2){
			d1=d1*0.034/2.0 + 1;
			distance=d1;
			}else{
			d2=d2*0.034/2.0 + 1;
			distance=d2;
		}
	}
	return distance;
}

#endif /* ULTRASONIC_DISTANCE_H_ */