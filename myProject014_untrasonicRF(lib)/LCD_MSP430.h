/*
 * LCD_MSP430.h
 *
 *  Created on: 2021. 4. 8.
 *      Author: JHKim
 */

#ifndef BASE_FILE_HEADER_LCD_MSP430_H_
#define BASE_FILE_HEADER_LCD_MSP430_H_

#include <msp430.h>
#include <stdint.h>

#define     LCD_DIR         P2DIR
#define     LCD_OUT         P2OUT

#define     LCD_PIN_RS      BIT0
#define     LCD_PIN_EN      BIT1
#define     LCD_PIN_D4      BIT2
#define     LCD_PIN_D5      BIT3
#define     LCD_PIN_D6      BIT4
#define     LCD_PIN_D7      BIT5

#define     LCD_PIN_DATA    LCD_PIN_D4|LCD_PIN_D5|LCD_PIN_D6|LCD_PIN_D7
#define     LCD_PIN_MASK    LCD_PIN_RS|LCD_PIN_EN|LCD_PIN_DATA

#define     EN_LOW          LCD_OUT &= ~LCD_PIN_EN
#define     EN_HIGH         LCD_OUT |=  LCD_PIN_EN
#define     RS_LOW          LCD_OUT &= ~LCD_PIN_RS
#define     RS_HIGH         LCD_OUT |=  LCD_PIN_RS

#define     TRUE            1
#define     FALSE           0

#define     DATA_MODE       TRUE
#define     CMD_MODE        FALSE

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00


void LCD_PULSE(void);
void LCD_SEND_BYTE(uint8_t, uint8_t);
void LCD_SET_CURSOR(uint8_t, uint8_t);
void LCD_CLEAR(void);
void LCD_INIT(void);
void LCD_PRINT(char *str);
void LCD_SEND_COMMAND(uint8_t);
void LCD_SEND_DATA(uint8_t);


#endif /* BASE_FILE_HEADER_LCD_MSP430_H_ */
