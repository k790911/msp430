/*
 * LCD_MSP430.c
 *
 *  Created on: 2021. 4. 8.
 *      Author: JHKim
 */


#include "LCD_MSP430.h"

void LCD_PULSE(){ // for enable pins L-H-L
    EN_LOW;
    __delay_cycles(200);
    EN_HIGH;
    __delay_cycles(200);
    EN_LOW;
    __delay_cycles(200);
}

void LCD_SEND_BYTE(uint8_t ByteToSend, uint8_t Mode){
    LCD_OUT &= ~(LCD_PIN_MASK); // Clear all pins
    // -- Caution -- //
    LCD_OUT |= (ByteToSend >> 2) & 0b00111100;
    if ( Mode == DATA_MODE ){
        RS_HIGH;
    }
    else{
        RS_LOW;
    }
    LCD_PULSE();

    LCD_OUT &= ~(LCD_PIN_MASK); // Clear all pins
    // -- Caution -- //
    LCD_OUT |= (ByteToSend << 2) & 0b00111100;
    if ( Mode == DATA_MODE ){
        RS_HIGH;
    }
    else{
        RS_LOW;
    }
    LCD_PULSE();
}

void LCD_SET_CURSOR(uint8_t Col, uint8_t Row){
    int Row_offsets[] = { 0x00, 0x40, 0x10, 0x50 };
    if ( Row >= 4 ){
        Row = 4 - 1;
    }
    LCD_SEND_COMMAND(LCD_SETDDRAMADDR | (Col + Row_offsets[Row]) );
}

void LCD_CLEAR(){
    LCD_SEND_COMMAND(LCD_CLEARDISPLAY);
    LCD_SEND_COMMAND(LCD_RETURNHOME);
}

void LCD_SEND_COMMAND(uint8_t Cmd){
    LCD_SEND_BYTE(Cmd, CMD_MODE);
}
void LCD_SEND_DATA(uint8_t Data){
    LCD_SEND_BYTE(Data, DATA_MODE);
}
void LCD_INIT(){
    LCD_DIR |=  LCD_PIN_MASK; // Output mode
    LCD_OUT &~ ~LCD_PIN_MASK; // Clear

    __delay_cycles(100000);

    // Step 1. Set 4-bit mode
    RS_LOW;
    EN_LOW;
    LCD_OUT = 0b00001000; // Data
    LCD_PULSE();

    LCD_SEND_COMMAND(0x28);
    LCD_SEND_COMMAND(0x0E);
    LCD_SEND_COMMAND(0x06);
}
void LCD_PRINT(char *Text){
    char *c;
    c = Text;
    while ((c != 0) && (*c != 0)){
        LCD_SEND_DATA(*c);
        c++;
    }
}



