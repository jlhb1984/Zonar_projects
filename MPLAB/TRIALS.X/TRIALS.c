/*
 * File:   TRIALS.c
 * Author: Jose.Hurtado
 *
 * Created on 20 de junio de 2026, 06:32 PM
 */


#include <xc.h>

void main(void) {
    uint8_t datal=0b11111111;
    uint8_t datah = 0b00000011;
    uint8_t result;
    
    result=datah<<6;
    datah=result;
    result=datal & 0b11111100;
    datal=result;
    result=datal>>2;
    datal=result;
    result=datal | datah;
    
    while(1);   // keep program alive for debugging
}
