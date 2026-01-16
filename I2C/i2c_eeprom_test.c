#include<LPC21xx.h>
#include<string.h>
#include "i2c.h"
#include "i2c_eeprom.h"
#include "i2c_eeprom_defines.h"
#include "delay.h"
#include "lcd.h"

// u8 t __attribute__((at(0x40000000)));
// s8 rbuff[18] __attribute__((at(0x40000040)))="";
u8 t __attribute__((at(0x7FD00000)));
s8 rbuff[18] __attribute__((at(0x7FD00040)))="";
s8 wbuff[] = "ABCDEF";
// s8 rbuff[10];
int main(){
	IODIR0 |= (1<<4) | (1<<5);  // LED pins output
    IOCLR0 = (1<<4) | (1<<5);   // clear LEDs
	Init_LCD();
    init_i2c();
    i2c_eeprom_pagewrite(I2C_EEPROM_SA1,0x00,wbuff,7);
    delay_ms(1000);
    i2c_eeprom_seqread(I2C_EEPROM_SA1,0x00,rbuff,7);
	rbuff[6] = '\0';
	// StrLCD(rbuff);
	if(strcmp(wbuff,rbuff)==0){
		IOSET0 = 1<<4;
		StrLCD("CORRECT");
	}
	else{
		IOSET0=1<<5;
		StrLCD("WRONG");
	}
	while(1);
}
