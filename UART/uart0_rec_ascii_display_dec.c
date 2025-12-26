#include "delay.h"
#include "uart0.h"
#include "types.h"

int main(){
    u8 ch;
    UART0_Init();
    while (1){
        ch = UART0_RxChar();
        UART0_TxInt(ch);
        delay_ms(200);
    }
}

