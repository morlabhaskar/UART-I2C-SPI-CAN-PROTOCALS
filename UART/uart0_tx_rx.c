#include <LPC21xx.h>
#include "uart_defines.h"
#include "uart0.h"
#include "types.h"

int main(){
    u8 ch;
    UART0_Init();
    while (1){
        ch = UART0_RxChar(); // user types in VT1
        UART0_TxChar(ch);
    }
}
