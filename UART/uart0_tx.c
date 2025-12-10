#include<LPC21xx.h>
#include "delay.h"
#include "defines.h"
#include "uart0.h"

#define SEL_SW 16 //@p1.16
main(){
    UART0_Init();
    while(1){
        if(READBIT(IOPIN1,SEL_SW)==0){
            UART0_TxChar('a');
        }
        else{
            UART0_TxChar('A');
        }
        delay_ms(100);
    }
}
