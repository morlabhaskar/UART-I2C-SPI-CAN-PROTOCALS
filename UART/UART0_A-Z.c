/*
Write an ECP for transmitting characters A-Z from LPC21xx based CPU to the hyper
terminal of PC through UART for every switch press from user. 
*/
#include <LPC21xx.h>
#include "delay.h"
#include "uart0.h"
#define SW 19 
int main(void){
    char ch = 'A';
    IODIR0 &= ~(1<<SW);
    UART0_Init();
    while(1){
        if(((IOPIN0 >> SW)&1)==0){
            UART0_TxChar(ch++);
            if (ch > 'Z')
                ch = 'A';
            while(((IOPIN0 >> SW)&1)==0);
        }
    }
}
