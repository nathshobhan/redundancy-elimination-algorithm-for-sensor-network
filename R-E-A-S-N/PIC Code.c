#include<p18f4520.h>   //to include controller specific header file

#pragma config OSC = HS  //Oscillator selection {4, 10, 20, 25 MHz}
#pragma config WDT = OFF  //disable watchdog timer
#pragma config LVP = OFF  //disable low voltage programming
#pragma config PBADEN = OFF //disable PORT B analog input???????????????????????????????????

//Macros defined for LCD
#define RW PORTBbits.RB1
#define RS PORTBbits.RB0
#define EN PORTBbits.RB2

//function prototypes
void ADC_Init(void);
unsigned int Get_ADC_Result(void);
void ms_delay(unsigned int time);

void init_lcd(void);
void lcd_command(unsigned char cmd);
void lcd_data(unsigned char data);

//main function
void main()
{
    unsigned int result;
    unsigned char i,thousands, hundreds, tens, ones;

    //input-output port configuration
    //declare PORT C as output for LCD
    //TRISC = 0x00;
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2 = 0;
    TRISCbits.TRISC3 = 0;
    TRISCbits.TRISC4 = 0;
    TRISCbits.TRISC5 = 0;
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7 = 0;
    //For RS and E of LCD declared as output
    TRISBbits.TRISB6 = 0;
    TRISBbits.TRISB7 = 0;
    //For sensor input (1 Sensor A)
    TRISAbits.TRISA0 = 1;
    //For led
    TRISAbits.TRISA1 = 0;

    //Initialization of A/D and LCD
    init_lcd();
    ADC_Init();

    //main code starts here
    while(1)
    {
        result = Get_ADC_Result();
        i = result/1000 ;
        thousands = i + 0x30;
        lcd_data (thousands);
        i = (result%1000)/100;
        hundreds = i + 0x30;
        lcd_data (hundreds);
        i = ((result%1000)%100)/10;
        tens = i + 0x30;
        lcd_data (tens);
        i = result%10 ;
        ones = i + 0x30;
        lcd_data (ones);
        ms_delay(5000); //5 seconds delay
    }
}

unsigned int Get_ADC_Result()
{
    unsigned int ADC_Res = 0;
    ADCON0bits.GO = 1;  //start conversion
    while(ADCON0bits.GO);  //wait till conversion is complete
    ADC_Res = (unsigned int)ADRESH;  //Since left justified
    return ADC_Res;
}

void ADC_Init()
{
    //initialize ADC module. It contains 5 important registers
    /*
        ADCON0 = bit 7-6 Unimplemented 00 -- bit 5-2 Channel 0 Select 0000 -- bit 1 A/D idle 0 - bit 0 A/D Disabled
    */
    ADCON0 = 0b00000000; //A/D module is OFF and channel 0 is selected
    /*
        ADCON1 = bit 7-6 Unimplemented 00 -- bit 5 VSS 0 -- bit 4 VDD 0 -- bit 3-0 Control bits 1110 Select AN0 analog input
    */
    ADCON1 = 0b00001110;
    /*
        ADCON2 = bit 7 Left Justified(Copy ADRESH) 0 -- bit 6 Unimplemented 0 -- bit 5-3 2Tad 001 -- bit 2-0 Fosc/64 110
    */
    ADCON2 = 0b00001110;
    ADCON0bits.ADON = 1;  //A/D Converter module is enabled
}

void init_lcd(void)
{
    lcd_command(0x38);
    ms_delay(25);
    lcd_command(0x01);
    ms_delay(25);
    lcd_command(0x0C);
    ms_delay(25);
    lcd_command(0x80);
    ms_delay(25);
}

void lcd_command(unsigned char cmd)
{
    PORTC = cmd;
    RS = 0;
    RW = 0;
    EN = 1;
    ms_delay(25);
    EN = 0;
}

void lcd_data(unsigned char data)
{
    PORTC = data;
    RS = 1;
    RW = 0;
    EN = 1;
    ms_delay(25);
    EN = 0;
}

void ms_delay(unsigned int time)
{
    unsigned int i, j;
    for(i = 0;i<time;i++)
        for(j = 0;j<275;j++); //calibrated for 1ms in MPLAB
}
