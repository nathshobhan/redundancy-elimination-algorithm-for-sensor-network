#include<p18f4520.h>
#define rs PORTBbits.RB4
#define rw PORTBbits.RB5
#define en PORTBbits.RB6
#define lcd PORTD
#define r1 PORTCbits.RC0
#define r2 PORTCbits.RC1
#define r3 PORTCbits.RC2
#define r4 PORTCbits.RC3
#define c1 PORTCbits.RC4
#define c2 PORTCbits.RC5
#define c3 PORTCbits.RC6
#define c4 PORTCbits.RC7

void delay_ms(unsigned int value)
{
unsigned int i,j;
for(i=0;i<value;i++)
{
	for(j=0;j<275;j++);
}


}
 
int keypad();
 
void lcd_ini();
 
void lcd_display(unsigned int);
 
void cmd(unsigned char);
 
void lcd_str(unsigned char*);
 
unsigned int i;
unsigned int m;
 
void main() 
   {
        TRISB=0x00;
        TRISC=0x00;
        TRISD=0x00;
        lcd_ini();
        while(1)
          {  
               keypad();
               lcd_display(m);
 
          }
    }
 
void lcd_display(unsigned int x)
  {
      lcd=x;
      rs=1;
      rw=0;
      en=1;
      delay_ms(100);
      en=0;
  }
 
void cmd(unsigned char m)
  {
      lcd=m;
      rs=0;
      rw=0;
      en=1;
      delay_ms(10);
      en=0;
  }
 
void lcd_ini()
  {
      cmd(0x38);
      cmd(0x0e);
      cmd(0x01);
      cmd(0x06); 
      cmd(0x80);
  }
 
void lcd_str(unsigned char *str)
   {
        while(*str!='\0')
          {
               lcd_display(*str);
               str++;
          }
    }
 
int keypad()
   {
        PORTC=0xff;
        while(1) 
          {
              r1=0;
              r4=r3=r2=1;
              if(c1==0)
                 {
                      m='7';
                      delay_ms(10);
                      return m;
                  }
              else if(c2==0)
                {
                     m='8';
                     delay_ms(10);
                     return m;
                }
             else if(c3==0)
                {
                     m='9';
                     delay_ms(10);
                     return m;
               }
           else if(c4==0)
              {
                    m='/';
                    delay_ms(10);
                    return m;
              }
           r1=r3=r4=1;
           r2=0;
           if(c1==0)
              {
                   m='4';
                   delay_ms(10);
                   return m;
               }
           else if(c2==0)
              {
                   m='5';
                   delay_ms(10);
                   return m;
              }
           else if(c3==0)
              {
                   m='6';
                   delay_ms(10);
                   return m;
               }
            else if(c4==0)
               {
                   m='*';
                   delay_ms(10);
                   return m;
               }
            r2=r1=r4=1;
            r3=0;
            if(c1==0)
              {
                  m='1';
                  delay_ms(10);
                  return m;
              }
           else if(c2==0)
              {
                  m='2';
                  delay_ms(10);
                  return m;
              }
           else if(c3==0)
              {
                  m='3';
                  delay_ms(10);
                  return m;
              }
           else if(c4==0)
              {
                  m='-';
                  delay_ms(10);
                  return m;
              }
           r3=r2=r1=1;
           r4=0;
           if(c1==0)
              {
                  cmd(0x01);
                  delay_ms(500);
              }
           else if(c2==0)
              {
                    m='0';
                    delay_ms(10);
                    return m;
               }
            else if(c3==0)
               {
                   m='=';
                   delay_ms(10);
                   return m;
               }
            else if(c4==0)
              {
                  m='+';
                  delay_ms(10);
                  return m;
              }
         }
   }

