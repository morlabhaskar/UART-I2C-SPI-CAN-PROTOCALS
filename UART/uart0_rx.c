#include<LPC21xx.h>
#include "uart0.h"

#define SUCCESS_STATUS_PIN 4 //@p0.4
#define FAILURE_STATUS_PIN 5 //@p0.5

main(){
    UART0_Init();
    IODIR0 |= 1<<SUCCESS_STATUS_PIN | 1<<FAILURE_STATUS_PIN;
    while(1){
        if(UART0_RxChar()=='a'){
            IOPIN0 ^= 1<<SUCCESS_STATUS_PIN;
        }
        else{
            IOPIN0 ^= 1<<FAILURE_STATUS_PIN;
        }
    }
}
