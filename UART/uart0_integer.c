#include<LPC21xx.h>
#include "defines.h"
#include "delay.h"
#include "uart0.h"

main(){
    UART0_Init();
    while(1){
        UART0_TxInt(1234);
        UART0_TxChar('\n');
        delay_ms(200);
    }
}
