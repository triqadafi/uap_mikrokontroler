/*******************************************************
This program was created by the CodeWizardAVR V3.33 
Automatic Program Generator
© Copyright 1998-2018 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 12/7/2018
Author  : 
Company : 
Comments: 


Chip type               : ATmega16A
Program type            : Application
AVR Core Clock frequency: 11.059200 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/
#include <mega16a.h>
#include <delay.h>
// Alphanumeric LCD functions
#include <alcd.h>
#include <stdio.h>


// Voltage Reference: AREF pin
#define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (0<<ADLAR))

// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
    ADMUX=adc_input | ADC_VREF_TYPE;
    // Delay needed for the stabilization of the ADC input voltage
    delay_us(10);
    // Start the AD conversion
    ADCSRA|=(1<<ADSC);
    // Wait for the AD conversion to complete
    while ((ADCSRA & (1<<ADIF))==0);
    ADCSRA|=(1<<ADIF);
    return ADCW;
}

    
    float v_ref = 1.2;
    float v_1 = 0;
    float v_2 = 0;
    char buff[16];

void main(void)
{
    // Port Settings
    DDRA=0x00;
    DDRB=0xFF;

    // ADC initialization
    // ADC Clock frequency: 691.200 kHz
    // ADC Voltage Reference: AREF pin
    // ADC Auto Trigger Source: ADC Stopped
    ADMUX=ADC_VREF_TYPE;
    ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (1<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);
    SFIOR=(0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);

    // Alphanumeric LCD initialization
    // Connections are specified in the
    // Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
    // RS - PORTD Bit 0
    // RD - PORTD Bit 1
    // EN - PORTD Bit 2
    // D4 - PORTD Bit 4
    // D5 - PORTD Bit 5
    // D6 - PORTD Bit 6
    // D7 - PORTD Bit 7
    // Characters/line: 16
    lcd_init(16);


    while (1){
        v_1 = (read_adc(0)/1024.0) * v_ref * 1000;
        v_2 = (read_adc(1)/1024.0) * v_ref * 1000;
        sprintf(buff,"V1: %07.2f mV", (v_1<1000)?v_1:1000.00);
        lcd_gotoxy(0,0);
        lcd_puts(buff);
        lcd_gotoxy(0,1);
        sprintf(buff,"V2: %07.2f mV", (v_2<1000)?v_2:1000.00);
        lcd_puts(buff);
        delay_ms(500);
    }
}
