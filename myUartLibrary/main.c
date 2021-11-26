#include <msp430.h> 
#include <stdio.h>

void write_uart_byte(char value) {
    while(UCA1STAT & UCBUSY);
    UCA1TXBUF = value;
}
void write_uart_string(char *str) {
    unsigned int i = 0;
    while (str[i] != '\0') {
        write_uart_byte(str[i++]);
    }
}
void write_uart_uint(unsigned int l) {
    char buf[sizeof(l) * 8 + 1];
    sprintf(buf, "%d", l);
    write_uart_string(buf);
}
