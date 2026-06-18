/*
 * File:   SENSOR_CALIBRATOR.c
 * Author: jlhb1984
 *
 * Created on June the 18th, 2026.
 * Analog input: ADC0 PA0 40.
 * Receiver data: RXD PD0 14.
 * Transmitter data: TXD PD1 15. 
 */

#include <avr/io.h>
#include <avr/interrupt.h> // Essential for ISR and sei().
#include <util/delay.h>

#define F_CPU 1000000UL
#define SET_BIT(REG,BIT)    (REG|=(1<<BIT))
#define CLEAR_BIT(REG,BIT)  (REG&=~(1<<BIT))
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))

uint8_t low_byte;
uint8_t high_byte;
unsigned char datah,datal;
int cont=0;

ISR(ADC_vect){
    cli();
    low_byte=ADCL;
    high_byte=ADCH;
    //PORTB=ADCL;
    if ((low_byte>=datal)&&(high_byte>=datah))
    {
        SET_BIT(PORTB,0);
    }
    sei();
}

int main(void) {
    DDRA=0b11111110;    //PA0 ADC0 40 ANALOG INPUT. REST AS OUTPUT.
    DDRB=0b11111111;    //PORTB AS OUTPUT.
    DDRD=0b11111110;    //PD0 RXD INPUT,PD1_TXD_OUTPUT,REST AS OUTPUT.    
    ADCSRA=0b10001000;  //ADEN_1,ADCS_START_0,ADATE_0,ADIF_FLAG,ADIE_1,ADPS2_0,ADPS1_0,ADPSO_0.       
    UBRRH=0b00000000;
    UBRRL=0b00011001;   //2400 BAUDIOS.
    UCSRA=0b00000000;   //RXC_F,TXC_F,UDRE_F,FE_F,DOR_F,PE_F,U2X_0,F,MOCM_0.
    UCSRC=0b10000110;   //USREL_1/0,UMSEL_0,UPM1_0,UPM0_0,USBS_0,UCSZ1_1,UCSZ0_1,UCPOL_0.
    UCSRB=0b00011000;   //RXCIE_0,TXCIE_0,UDRIE_0,RXEN_1,TXEN_1,UCSZ_0,RXB8_0,TXB8_0.
    sei();    

    while (1) {        
        while (!(UCSRA & (1<<RXC)))
        {
            if (cont<1)
            {
            datah=UDR;
            cont=cont+1;
            }//if
            if (cont>0)
            {
            datal=UDR;
            cont=0;
            }//if
        }// while serial.
        ADCSRA|=(1 << ADSC);//START ADC
        datal=0b11111111;
        datah=0b00000001;
        sei();
    }//while
}//main