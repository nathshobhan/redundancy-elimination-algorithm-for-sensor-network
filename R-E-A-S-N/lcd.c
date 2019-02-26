#include<p18f4520.h>
#define ldata PORTD
#define rs PORTBbits.RB0
#define rw PORTBbits.RB1
#define en PORTBbits.RB2
void msdelay(unsigned int time)
{
unsigned int i,j;
for(i=0;i<time;i++)
{
	for(j=0;j<275;j++);	
}		
	
	
}



void lcdcmd(unsigned char value)
{
	ldata=value;
	rs=0;
	rw=0;
	en=1;
	msdelay(15);
	en=0;
}

void lcddata(unsigned char value)
{
	ldata=value;
	rs=1;
	rw=0;
	en=1;
	msdelay(15);
	en=0;
}		
void main()
{
	TRISD=0;
	TRISB=0;
	en=0;
	
	msdelay(250);
	lcdcmd(0x38);//lcd matrix
	msdelay(250);
	lcdcmd(0x0E);//displavoid lcdcmd(unsigned char value)
{
	ldata=value;
	rs=0;
	rw=0;
	en=1;
	msdelay(15);
	en=0;
}

void lcddata(unsigned char value)
{
	ldata=value;
	rs=1;
	rw=0;
	en=1;
	msdelay(15);
	en=0;
}		y on
	msdelay(15);
	lcdcmd(0x01);//clear lcd
	msdelay(15);
	lcdcmd(0x06);//shift cursor right
	msdelay(15);
	lcdcmd(0x86);//line 1
	msdelay(15);
	
	lcddata('M');
	msdelay(15);
	lcddata('C');
	msdelay(15);
	lcddata('E');

	
}




		