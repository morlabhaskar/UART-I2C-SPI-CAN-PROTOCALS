//spi_eeprom_test.c
#include<LPC21xx.h>
#include"types.h"
#include"delay.h"
#include"lcd.h"
#include"lcd_defines.h"
#include "spi.h"
#include "spi_eeprom.h"

// #define GLED (1<<16)
// #define RLED (1<<17)
// u8 i,t;
// u8  rxData[26] __attribute__((at(0x40000010)));
// int main(){
// 	Init_SPI0();
// 	IODIR1 |= (GLED|RLED);
//     for(i=0;i<26;i++){
//     	ByteWrite(i,'A'+i);
//      	t=ByteRead(i);
// 		rxData[i]=t;
// 	   	if(rxData[i]=='A'+i)	 
//         	IOSET1 = GLED;
// 		else
// 			IOSET1 = RLED; 	 
// 		delay_ms(1000);
// 		IOCLR1 = (GLED|RLED);
// 		delay_ms(500);	 
//  	}	 
//    	while(1);
// }

#define GLED (1<<16)
#define RLED (1<<17)
u8 data;
u16 t=0x0010;
int main(){
	Init_SPI0();
	IODIR1 |= (GLED|RLED);
    IOCLR1  = (GLED | RLED);
    ByteWrite(t,'A');
    delay_ms(10);
    data=ByteRead(t);
    if(data != 'A')
        IOSET1 = GLED;
    else
        IOSET1 = RLED;
   	while(1);
}

