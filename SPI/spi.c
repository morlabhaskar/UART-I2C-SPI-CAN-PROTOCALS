#include "types.h"
#include "spi_defines.h"

void Init_SPI(){
    //cfg req gpio pins as MOSI,MISO,CLK,CS
    //cfg spi mode,serial order as per slave
    //cfg spi speed/freq
}
u8 spi(u8 sData){
    //write to spi data buffer
    //to start serialization
    //wait untill serial complete
    //read & return received rData
}
void writeEnable(){
    //make cs low
    //spi(WREN)
    //make cs high
}
void writeDisable(){
    //make cs low
    //spi(WRDI)
    //make cs high
}
void byteWrite(u16 wBuffAddr,u8 wByte){
    writeEnable();
    //make chip select low
    //spi(WRITE);
    //spi(wBuffAddr MSB byte)
    //spi(wBuffAddr LSB byte)
    //spi(wByte)
    //make chip select high
    //delay_ms(5)
    writeDisable();
}
void byteRead(u16 rBuffAddr){
    u8 rByte;
    //make chip select low
    //spi(READ)
    //spi(rBuffAddr MSB byte)
    //spi(rBuffAddr LSB byte)
    //rByte=spi(dummyByte)
    //make chip select high
    return rByte;
}