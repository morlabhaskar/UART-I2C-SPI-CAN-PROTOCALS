#include<LPC214x.h>
#include "types.h"
#include "delay.h"
#include "spi_defines.h"

void Init_SPI(void){
    //cfg req gpio pins as MOSI,MISO,CLK,CS
    // P0.4=SCK, P0.5=MISO, P0.6=MOSI
    PINSEL0 &= ~(0xFF << 8);     // Clear P0.4–P0.7
    PINSEL0 |=  (0x15 << 8);     // 01 01 01 00 → SPI0, P0.7 GPIO
    IODIR0 |= (1<<7);
    IOSET0  = (1<<7);            // CS HIGH (inactive)
    //cfg spi mode,serial order as per slave
    S0SPCR = (1<<5);           // Master mode, 8-bit, CPOL=0, CPHA=0
    //cfg spi speed/freq
    S0SPCCR = 8;               // SPI clock speed (must be >= 8)
}
//SPI Send & Receive
u8 spi(u8 sData){
    //write to spi data buffer
    S0SPDR = sData;
    //to start serialization
    // (serialization starts automatically)
    //wait untill serial complete
    while(!(S0SPSR & (1<<7)));   // SPIF flag  // Wait for transfer done
    //read & return received rData
    return S0SPDR;
}
//EEPROM Write Enable
void writeEnable(void){
    //make cs low
    IOCLR0 = (1<<7);
    //spi(WREN)
    spi(WREN);
    //make cs high
    IOSET0 = (1<<7);
}
//EEPROM Write Disable
void writeDisable(void){
    //make cs low
    IOCLR0 = (1<<7);
    //spi(WRDI)
    spi(WRDI);
    //make cs high
    IOSET0 = (1<<7);
}
//EEPROM Byte Write
void byteWrite(u16 wBuffAddr,u8 wByte){
    writeEnable();
    //make chip select low
    IOCLR0 = (1<<7);
    //spi(WRITE);
    spi(WRITE);
    //spi(wBuffAddr MSB byte)
    spi(wBuffAddr >> 8);
    //spi(wBuffAddr LSB byte)
    spi(wBuffAddr & 0xFF);
    //spi(wByte)
    spi(wByte);
    //make chip select high
    IOSET0 = (1<<7);
    //delay_ms(5)
    delay_ms(5);
    writeDisable();
}
//EEPROM Byte Read
u8 byteRead(u16 rBuffAddr){
    u8 rByte;
    //make chip select low
    IOCLR0 = (1<<7);
    //spi(READ)
    spi(READ);
    //spi(rBuffAddr MSB byte)
    spi(rBuffAddr >> 8);
    //spi(rBuffAddr LSB byte)
    spi(rBuffAddr & 0xFF);
    //rByte=spi(dummyByte)
    rByte = spi(0xFF);
    //make chip select high
    IOSET0 = (1<<7);
    return rByte;
}
