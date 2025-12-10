#include<LPC21xx.h>
#include "uart_defines.h"
#include "types.h"
// void CfgPortPinFunc(u32 portNo,u32 pinNo,u32 pinFunc){
//     if(portNo==0){
//         if(pinNo<16){
//             PINSEL0 = ((PINSEL0 &~(3<<(pinNo*2))) | (pinFunc<<(pinNo*2)));
//         }
//         else if(pinNo>=16 && pinNo<=31){
//             PINSEL1 = ((PINSEL1 &~ (3<<((pinNo-16)*2))) | (pinFunc<<((pinNo-16)*2)));
//         }
//     }
//     else if(portNo==1){
//         //not required for lpc2129
//     }
// }

void UART0_Init(void){
    //cfg p0.0 as TXDO and p0.1 as RXDO 
    // CfgPortPinFunc(0,0,TXDO_PIN_0_1);
    // CfgPortPinFunc(0,1,RXDO_PIN_0_1);
    PINSEL0 = ((PINSEL0 &~(3<<(0*2))) | (1<<(0*2)));
    PINSEL0 = ((PINSEL0 &~(3<<(1*2))) | (1<<(1*2)));
    //cfg UART0 line control for:
    //8 data bits,No parity,1 stop bit(8N1)
    //DLAB = 1 (to access baud rate divisor register)
    U0LCR = 0x83; //U0LCR = WORD_LEN | (1<<DLAB_BIT);
    // U0DLL = DIVISOR;
    // U0DLM = DIVISOR >> 8;  //U0DLM = 0;
    U0DLL = 97;
    U0DLM = 0;
    //Disable DLAB (to access THR and RBR sfrs)
    U0LCR &= ~(1<<DLAB_BIT);   //U0LCR = 0x03
}
void UART0_TxChar(u8 TxByte){
    //load the data byte into UART0 Transmit Buffer
    U0THR = TxByte;
    //wait untill Transmission complete status
    while(((U0LSR>>TEMT_BIT)&1)==0);
}
u8 UART0_RxChar(void){
    //wait untill Receiver Data Ready(RDR==1)
    while(((U0LSR>>RDR_BIT)&1)==0);
    //Return the received data byte from Receiver Buffer Register
    return U0RBR;
}

void UART0_TxString(const char *str) {
    while(*str) {          // loop until null-terminator
        UART0_TxChar(*str); // send one character at a time
        str++;              // move to next character
    }
}