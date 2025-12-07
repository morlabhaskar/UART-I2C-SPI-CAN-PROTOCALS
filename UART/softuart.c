//bit-banging implementation
#include<LPC21xx.h>
#include "delay.h"
#include "types.h"
#include "defines.h"

#define TXD_PIN 0
#define RXD_PIN 1
#define BAUD9600 104
#define BAUD BAUD9600

void softUART_Init(void){
    //set TXD_PIN as high
    IOSET0 = 1<<TXD_PIN;
    //cfg TXD_PIN as gpio output pin
    IODIR0 |= 1<<TXD_PIN;
    //set RXD_PIN as high(default)
    // IOSET0 = 1<<RXD_PIN;
    //cfg RXD_PIN as gpio input pin(default)
    // IODIR0 &= ~(1<<RXD_PIN);
}

void softUART_Tx(u8 sDat){
    u8 i;
    //issue start bit '0'
    IOCLR0 = 1<<TXD_PIN;
    //wait for ~104uS @9600 baud
    delay_us(BAUD);
    //loop for 8 data bits, to serialize out
    //bit by bit lsb to msb @9600 baud
    for(i=0;i<=7;i++){
        //issue bits via so/TxD line lsb to msb order
        // IOPIN0 = ((IOPIN0 &~(1<<TXD_PIN)) | (((sDat>>i)&1)<<TXD_PIN));
        READWRITEBIT(IOPIN0,TXD_PIN,sDat,i);
        //wait for ~104uS @9600 baud
        delay_us(BAUD);
    }
    //issue stop bit '1'
    IOSET0 = 1<<TXD_PIN;
    //wait for ~104uS @9600 baud
    delay_us(BAUD);
}

u8 softUART_Rx(void){
    u8 i,rDat;
    //wait untill start bit '0' is detected
    while(READBIT(IOPIN0,RXD_PIN)==1);
    //wait for ~half bit period
    delay_us(BAUD/2);
    //loop for 8 data bits, to serialize in
    //bit by bit lsb to msb @9600 baud and store in rDat
    for(i=0;i<=7;i++){
        //wait for ~104uS @9600 baud
        delay_us(BAUD);
        //read and update read bit positionally into rDat
        // rDat = ((rDat &~ (1<<i)) | (((IOPIN0>>RXD_PIN)&1)<<i));
        READWRITEBIT(rDat,i,IOPIN0,RXD_PIN);
    }
    //wait for ~104uS @9600
    delay_us(BAUD);
    //wait for untill stop bit
    while(READBIT(IOPIN0,RXD_PIN)!=1);
    // return recieved byte
    return rDat;
}


