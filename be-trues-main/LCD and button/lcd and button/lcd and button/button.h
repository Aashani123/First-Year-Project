/*
 * button.h
 *
 * Created: 4/23/2022 11:30:06 AM
 *  Author: Charith Eranga
 */ 

#ifndef BUTTON_H_
#define BUTTON_H_

void button_initial();

#endif /* BUTTON_H_ */


void button_initial(){
	DDRA=DDRA &(~(1<<7))&(~(1<<6))&(~(1<<5))&(~(1<<4));
}
