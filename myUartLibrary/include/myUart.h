/*
 * myUart.h
 *
 *  Created on: 2021. 4. 19.
 *      Author: JHKim
 */

#ifndef INCLUDE_MYUART_H_
#define INCLUDE_MYUART_H_

void write_uart_byte(char value);
void write_uart_string(char *str);
void write_uart_uint(unsigned int l);

#endif /* INCLUDE_MYUART_H_ */
