#include <LPC21xx.h>
#include "delay.h"
#include "uart0.h"
int main(){
    UART0_Init();
    UART0_TxChar('A');
    UART0_TxChar('#');
    delay_ms(1000);
    UART0_TxString("welcome to vector");
    UART0_TxChar('#');
    delay_ms(1000);
    UART0_TxInt(1234);
    UART0_TxChar('#');
    delay_ms(1000);
    UART0_TxFloat(123.456, 3);
    UART0_TxChar('#');
    delay_ms(1000);
    UART0_TxHex(12);
    UART0_TxChar('#');
    delay_ms(1000);
    UART0_TxOct(12);
    UART0_TxChar('#');
    delay_ms(1000);
    while (1);
}
