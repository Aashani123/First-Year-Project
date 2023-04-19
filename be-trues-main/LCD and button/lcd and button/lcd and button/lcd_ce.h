/*
 * lcd_ce.h
 *
 * Created: 11/26/2021 5:57:04 PM
 *  Author: Charith-Eranga
 */ 


#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdlib.h>

#define lcd_dir DDRC	//data direction
#define lcd_port PORTC	//data port direction
#define RS PC2	//register pin (high data,low cmd)
#define EN PC3	//enable pin#include <avr/io.h>

void lcd_cstmchar(char cgram_rc, char *icon);
void lcd_rc(char row,char colm);
void LoadingScr();

void lcd_cmd(unsigned char cmd)
{
	lcd_port = (lcd_port & 0x0F)|(cmd & 0xF0); //sending upper nibble
	lcd_port &=~(1<<RS); //set to cmd ,RS=0 for cmd
	lcd_port |=(1<<EN); // Enable pulse
	_delay_us(1);
	lcd_port &=~(1<<EN);	//disable pulse
	_delay_us(200);
	
	lcd_port =(lcd_port & 0x0F)|(cmd<<4); //sending low nibble
	lcd_port |= (1<<EN);
	_delay_us(1);
	lcd_port &= ~ (1<<EN);
	_delay_ms(2);
	
}

void lcd_data(unsigned char data)
{
	lcd_port = (lcd_port & 0x0F)|(data & 0xF0); // upper nibble send
	lcd_port |=(1<<RS);	//RS=1 for data pin
	lcd_port |=(1<<EN); //pulse enable
	_delay_us(1);
	lcd_port &=~(1<<EN);
	_delay_us(200);
	
	lcd_port =(lcd_port & 0x0F)|(data<<4); //sending low nibble
	lcd_port |= (1<<EN);
	_delay_us(1);
	lcd_port &= ~ (1<<EN);
	_delay_ms(2);
}

void lcd_str(char *str)
{
	while(*str){
		lcd_data(*str++);
	}
}


void lcd_init()
{
	lcd_dir = 0xFF;
	_delay_ms(15);
	
	lcd_cmd(0x32);	//4bit mode initialize
	lcd_cmd(0x28);	//4bit 5*8 matrix
	lcd_cmd(0x80);	//1st row
	lcd_cmd(0xC0);  //2nd row
	lcd_cmd(0x0E);  //enable cursor
	lcd_cmd(0x01);	//clr
	lcd_cmd(0x0C);	//cursor disable
	LoadingScr();
}


void lcd_rc(char row,char colm)   //selecting row and column
{
	if (row==2)
	lcd_cmd(0xC0 |colm);
	else
	lcd_cmd(0x80 |colm);
	
}


void lcd_cstmchar(char cgram_rc, char *icon){
	lcd_cmd(0x40 +(cgram_rc*8));
	for (int i=0;i<8;i++){
		lcd_data(icon[i]);
	}
	lcd_cmd(0x80);
	
}

/////////////////////////Screen//////////////////////////
void LoadingScr(){
	lcd_cmd(0x80);
	lcd_str("     Welcome    ");
	_delay_ms(17);
	
	for (int i=0;i<16;i++){
		
		char Loading[7]={0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f};
		lcd_cstmchar(2,Loading);
		lcd_rc(2,i);
		lcd_data(2);
		_delay_ms(1);
	}
	_delay_ms(1);
	lcd_cmd(0x01);
}

void mainscr(int blk,int other)
{
		    char arrowL[7]={0x02,0x06,0x0E,0x1E,0x0E,0x06,0x02};
		    char arrowR[7]={0x08,0x0C,0x0E,0x0F,0x0E,0x0C,0x08};
			char intstr1[3];
			char intstr2[3];
		    itoa(blk,intstr1,10);
			itoa(other,intstr2,10);
			
		    _delay_ms(10);
		    lcd_cmd(0x01);
		    _delay_ms(1);
		    
		    lcd_cstmchar(0,arrowL);
		    lcd_rc(2,0);
		    lcd_data(0);
			
			lcd_rc(0,2);
			lcd_str("Black :");
			if (blk==1){
				lcd_rc(0,10);
				lcd_str("High  ");
			}
			else{
				lcd_rc(0,10);
				lcd_str("Low");
			}
			
			
			lcd_rc(2,2);
			lcd_str("Other : ");
			if (other==1){
				lcd_rc(2,10);
				lcd_str("High  ");
			}
			else{
				lcd_rc(2,10);
				lcd_str("Low");
			}
			
			
			lcd_cmd(0x0C);
		    lcd_cstmchar(1,arrowR);
		    lcd_rc(2,15);
		    lcd_data(1);
}


void fanscr(int working)
{
	char arrowL[7]={0x02,0x06,0x0E,0x1E,0x0E,0x06,0x02};
	char arrowR[7]={0x08,0x0C,0x0E,0x0F,0x0E,0x0C,0x08};
	char intstr1[4];
	itoa(working,intstr1,10);
	
	_delay_ms(10);
	lcd_cmd(0x01);
	_delay_ms(1);
	
	lcd_cstmchar(0,arrowL);
	lcd_rc(2,0);
	lcd_data(0);
	
	lcd_rc(0,3);
	lcd_str("Dry-Fan on/off :");
	
	if (working==1){
		lcd_rc(2,2);
		lcd_str("Activated   ");
	}
	else{
		lcd_rc(2,2);
		lcd_str("Deactivated ");
	}
	

	lcd_cmd(0x0C);
	lcd_cstmchar(1,arrowR);
	lcd_rc(2,15);
	lcd_data(1);
}


void info(int dis, int color)
{
	char arrowL[7]={0x02,0x06,0x0E,0x1E,0x0E,0x06,0x02};
	char arrowR[7]={0x08,0x0C,0x0E,0x0F,0x0E,0x0C,0x08};
	char intstr1[1];
	itoa(dis,intstr1,10);
	
	_delay_ms(10);
	lcd_cmd(0x01);
	_delay_ms(1);
	
	lcd_cstmchar(0,arrowL);
	lcd_rc(2,0);
	lcd_data(0);
	
	lcd_rc(0,2);
	lcd_str("Distance:");
	lcd_rc(0,11);
	lcd_str(intstr1);
	lcd_rc(0,14);
	lcd_str("cm");
	
	lcd_rc(2,2);
	lcd_str("Color:");
	if (color==1)
	{
		lcd_rc(2,9);
		lcd_str("Black");
	}
	else if (color==0)
	{
		lcd_rc(2,9);
		lcd_str("Other");
	}
	else{
		lcd_rc(2,9);
		lcd_str("Not");
	}
	
	lcd_cmd(0x0C);
	lcd_cstmchar(1,arrowR);
	lcd_rc(2,15);
	lcd_data(1);
}

void updated()
{	
	_delay_ms(10);
	lcd_cmd(0x01);
	_delay_ms(1);
	
	lcd_rc(0,0);
	lcd_str("Update");
	lcd_rc(2,0);
	lcd_str("Successfully");
}

/////////////////////Custom character/////////////////////////
/*
Left arrow
0 0 0 1 0	r1 = 0x02
0 0 1 1 0	r2 = 0x06
0 1 1 1 0	r3 = 0x0E
1 1 1 1 0	r4 = 0x1E
0 1 1 1 0	r5 = 0x0E
0 0 1 1 0	r6 = 0x06
0 0 0 1 0	r7 = 0x02

Right arrow
0 1 0 0 0	r1 = 0x08
0 1 1 0 0	r2 = 0x0C
0 1 1 1 0	r3 = 0x0E
0 1 1 1 1	r4 = 0x0F
0 1 1 1 0	r5 = 0x0E
0 1 1 0 0	r6 = 0x0C
0 1 0 0 0	r7 = 0x08

complete
1 1 1 1 1	r1 = 0x1f
1 1 1 1 1	r2 = 0x1f
1 1 1 1 1	r3 = 0x1f
1 1 1 1 1	r4 = 0x1f
1 1 1 1 1	r5 = 0x1f
1 1 1 1 1	r6 = 0x1f
1 1 1 1 1	r7 = 0x1f


char Loading[7]={0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f};
char arrowl[7]={0x02,0x06,0x0E,0x1E,0x0E,0x06,0x02};
char arrowR[7]={0x08,0x0C,0x0E,0x0F,0x0E,0x0C,0x08};
*/