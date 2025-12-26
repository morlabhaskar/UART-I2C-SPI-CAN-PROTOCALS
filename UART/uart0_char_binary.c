#include<LPC21xx.h>
#include "uart0.h"
#include "delay.h"
#include "types.h"

void Display_On_LEDs(u8 data){
    IO0CLR = (0xFF << 16);
    IO0SET = ((data & 0xFF) << 16);
    // IO0SET = (~data & 0xF0) << 16;
}

int main(){
    u8 ch;
    IODIR0 |= (0xFF<<16);
    UART0_Init();
    while(1){
        ch = UART0_RxChar();
        Display_On_LEDs(ch);
    }
}
