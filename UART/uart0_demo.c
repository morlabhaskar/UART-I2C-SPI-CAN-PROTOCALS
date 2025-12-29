#include <LPC21xx.h>
#include "delay.h"
#include "uart0.h"
int main(){
    UART0_Init();
    //UART0_TxChar('A');
    //delay_ms(1000);
    UART0_TxString("welcome to vector");
    //delay_ms(1000);
    //UART0_TxInt(1234);
    // delay_s(1);
    // f32UART_tx(123.456, 3);
    // delay_s(1);
    while (1);
}
