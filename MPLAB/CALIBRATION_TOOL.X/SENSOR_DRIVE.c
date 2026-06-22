/*
 * File:   CALIBRATION_TOOL.c
 * Author: Jose.Hurtado
 *
 * Created on 18 de junio de 2026, 04:04 PM
 */
#include <xc.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int ind=0;
unsigned char datal,datah,result;

ISR(USART_RXC_vect)
{
    cli();
    ind=ind+1;
    if (ind<2)
    {   datah=UDR;
        PORTB=datah;  // Show received byte
    }// if
    
    if (ind>1)
    {
        datal=UDR;
        PORTB=datal;  // Show received byte
        // new code    
        result=datah<<6;
        datah=result;
        result=datal & 0b11111100;
        datal=result;
        result=datal>>2;
        datal=result;
        result=datal | datah;
        //    
    }// if  
    sei();
}// ISR

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
    ADMUX=0b01100000;   //REFS1_0,RFS0_1,ADLAR_0,MUX4_0,MUX3_0,MUX2_0,MUX1_0,MUX0_0 RIGHT ADJUSTED TO BETTER REOLUTION.
    ADCSRA=0b11000000;  //ADEN_1,ADCS_START_0,ADATE_0,ADIF_FLAG,ADIE_1,ADPS2_0,ADPS1_0,ADPSO_0.
    PORTB=0b00000000;
    PORTC=0b00000000;    
    UCSRC=0b00000110;   //USREL_0,UMSEL_0,UPM1_0,UPM0_0,USBS_0,UCSZ1_1,UCSZ0_1,USPOL_0
    UBRRL=0b00011001;   //2400
    UBRRH=0b00000000;   //2400
    UCSRC=0b10000110;   //USREL_1,UMSEL_0,UPM1_0,UPM0_0,USBS_0,UCSZ1_1,UCSZ0_1,USPOL_0
    UCSRB=0b10010000;   //RXCIE_1,TXCIE_0,UDRIE_0,RXEN_1,TXEN_0,UCSZ2_0,RXB8_0,TXB8_0.
    result=0b00000000;
    EEPROM_Write(0x00,result);
    sei();
    _delay_ms(1000); 
    //int valuel=EEPROM_Read(0x00);        
    result=EEPROM_Read(0x00);
    
    while(1)
    {
        if (ADCSRA &(1<<ADIF))
            {
            //PORTB=read_value;
            //PORTC=ADCH;
            if (ADCH >result)// ((ADCH>datah) && (ADCL>datal)) when I have ab Electrer sensor.
                {
                PORTC|=(1<<PC0);
                }// if 11.
            ADCSRA=0b11010000;  //ADEN_1,ADCS_START_0,ADATE_0,ADIF_FLAG,ADIE_1,ADPS2_0,ADPS1_0,ADPSO_0.
            }//if 1        
        if (ind>1)
            {
            EEPROM_Write(0x00, result);
            ind=0;
            }//if 2
        _delay_ms(1000);
    }// while.   
    return;
}