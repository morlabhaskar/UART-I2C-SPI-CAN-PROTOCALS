//spi.c
#include<LPC214x.h>
#include "types.h"
#include "delay.h"
#include "spi_defines.h"

// void CfgPortPinFunc(u32 PortNo,u32 PinNo,u32 PinFunc){
//     if(PortNo==0){
//         if(PinNo<16){
//             PINSEL0=((PINSEL0 &~ (3<<(PinNo*2))) | (PinFunc<<(PinNo*2)));
//         }
//         else if(PinNo>=16 && PinNo<=31){
//             PINSEL1=((PINSEL1 &~ (3<<((PinNo-16)*2))) | (PinFunc<<((PinNo-16)*2)));
//         }
//     }
//     else if(PortNo==1){
//         //not required for LPC2129
//     }
// }
// void Init_SPI(void){
//     //cfg req gpio pins as MOSI,MISO,CLK,CS
//     CfgPortPinFunc(0, 4, 1);   // P0.4 → SCK
//     CfgPortPinFunc(0, 5, 1);   // P0.5 → MISO
//     CfgPortPinFunc(0, 6, 1);   // P0.6 → MOSI
//     // CfgPortPinFunc(0, 7, 0);   // P0.7 → GPIO (CS) not mandotary default also GPIO
//     // CS pin
//     IODIR0 |= (1<<CS);
//     IOSET0  = (1<<CS);            // CS HIGH (inactive)
//     //cfg spi mode,serial order as per slave
//     S0SPCR = (1<<MASTER_MODE_BIT);//1<<5   Master mode, 8-bit, CPOL=0, CPHA=0
//     // S0SPCR = 0x20;
//     //cfg spi speed/freq
//     S0SPCCR = 8;               // SPI clock speed (must be >= 8)
//     // S0SPCCR = 60;               // SPI clock speed (must be >= 8)
// }
// //SPI Send & Receive
// u8 spi(u8 sData){
//     //write to spi data buffer
//     S0SPDR = sData;
//     //to start serialization
//     // (serialization starts automatically)
//     //wait for SPIF flag untill serial complete
//     // while((S0SPSR & (1<<SPIF_BIT))==0);
//     while(((S0SPSR>>SPIF_BIT)&1)==0);
//     //read & return received rData
//     return S0SPDR;
// }
// //EEPROM Write Enable
// void writeEnable(void){
//     //make cs low
//     IOCLR0 = (1<<CS);
//     //spi(WREN)
//     spi(WREN);
//     //make cs high
//     IOSET0 = (1<<CS);
// }
// //EEPROM Write Disable
// void writeDisable(void){
//     //make cs low
//     IOCLR0 = (1<<CS);
//     //spi(WRDI)
//     spi(WRDI);
//     //make cs high
//     IOSET0 = (1<<CS);
// }
// u8 readStatus(void){
//     u8 status;
//     IOCLR0 = (1<<CS);      // CS LOW
//     spi(RDSR);
//     status = spi(0xFF);
//     IOSET0 = (1<<CS);      // CS HIGH
//     return status;
// }
// void waitWriteComplete(void){
//     while(readStatus() & (1<<WIP));
// }
// //EEPROM Byte Write
// void byteWrite(u16 wBuffAddr,u8 data){
//     writeEnable();
//     //make chip select low
//     IOCLR0 = (1<<CS);
//     //spi(WRITE);
//     spi(WRITE);
//     //spi(wBuffAddr MSB byte)
//     spi(wBuffAddr >> 8);
//     //spi(wBuffAddr LSB byte)
//     spi(wBuffAddr & 0xFF);
//     //spi(data)
//     spi(data);
//     //make chip select high
//     IOSET0 = (1<<CS);
//     //EEPROM write time ≈ 5 ms
//     // delay_ms(5);
//     // writeDisable();
//     waitWriteComplete();
// }
// //EEPROM Byte Read
// u8 byteRead(u16 rBuffAddr){
//     u8 rByte;
//     //make chip select low
//     IOCLR0 = (1<<CS);
//     //spi(READ)
//     spi(READ);
//     //spi(rBuffAddr MSB byte)
//     spi(rBuffAddr >> 8);
//     //spi(rBuffAddr LSB byte)
//     spi(rBuffAddr & 0xFF);
//     //rByte=spi(dummyByte)
//     rByte = spi(DUMMY);
//     //make chip select high
//     IOSET0 = (1<<CS);
//     return rByte;
// }

void Init_SPI0(void){
    PINSEL0 = SCK0 | MISO0 | MOSI0 ;//select SPI pin functionality 
    S0SPCCR = 60;// bit clock rate
    // S0SPCR = ((1<<MASTER_MODE_BIT)|Mode_3);//spi module in master mode,CPOL =1,CCPHA = 1. MSB first
    S0SPCR = ((1<<MASTER_MODE_BIT)|Mode_0);//spi module in master mode,CPOL =1,CCPHA = 1. MSB first
    // IOPIN0 |= (1<<CS);
    IOSET0 = (1<<CS); 
    IODIR0 |= (1<<CS);
}

u8 SPI0(u8 data){
    u8 status;
    status = S0SPSR;//clear SPIF
    S0SPDR = data; //load spi tx reg
     while(((S0SPSR>>SPIF_BIT)&1)==0);//wait for tx to complete
    return S0SPDR; // read data from SPI data reg,place into buffer
}




