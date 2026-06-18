/*
 * File:   CALIB.c
 * Author: Jose.Hurtado
 *
 * Created on 18 de junio de 2026, 04:04 PM
 */


#include <xc.h>
#include <util/delay.h>


void EEPROM_Write(unsigned int address, unsigned char data)
{
    while (EECR & (1 << EEWE));   // Wait if write in progress
    EEAR = address;               // Set address
    EEDR = data;                  // Set data
    EECR |= (1 << EEMWE);         // Enable write
    EECR |= (1 << EEWE);          // Start write
}


unsigned char EEPROM_Read(unsigned int address)
{
    while (EECR & (1 << EEWE));   // Wait if writing
    EEAR = address;               // Set address
    EECR |= (1 << EERE);          // Start read
    return EEDR;                  // Return data
}


void main(void) {
    DDRA=0b11111110;    //PA0 ADC0 40 ANALOG INPUT. REST AS OUTPUT.
    DDRB=0b11111111;    //PORTB AS OUTPUT.
    DDRC=0b11111111;
    DDRD=0b11111110;    //PD0 RXD INPUT,PD1_TXD_OUTPUT,REST AS OUTPUT.
    ADMUX=0b01000000;
    ADCSRA=0b11000000;  //ADEN_1,ADCS_START_0,ADATE_0,ADIF_FLAG,ADIE_1,ADPS2_0,ADPS1_0,ADPSO_0.
    PORTB=0b00000000;
    PORTC=0b00000000;
    _delay_ms(1000);
    int value=2;        //Value gotten from calibration tool.
    // EEPROM_Write(0x00, value); Enable when serial communication be ready!
    int read_value=EEPROM_Read(0x00);
    //
    while(1)
    {
        if (ADCSRA &(1<<ADIF))
            {
            PORTB=read_value;
            //PORTC=ADCH;
            if (ADCH >value)
                {
                PORTC|=(1<<PC0);
                }// if 2.
            ADCSRA=0b11010000;  //ADEN_1,ADCS_START_0,ADATE_0,ADIF_FLAG,ADIE_1,ADPS2_0,ADPS1_0,ADPSO_0.
            }// if 1
        _delay_ms(1000);
    }// while.   
    return;
}
