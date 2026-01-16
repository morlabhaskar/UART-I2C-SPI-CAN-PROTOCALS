#include<LPC21xx.h>
#include "i2c.h"
#include "i2c_eeprom.h"
#include "i2c_eeprom_defines.h"
#include "delay.h"

u8 r;
int main(){
	IODIR0 |= 1<<4 | 1<<5;
	init_i2c();
	i2c_eeprom_bytewrite(0x50, 0x10, 0xAB);
	r = i2c_eeprom_randomread(0x50, 0x10);
	if(r == 0xAB)
		IOSET0 = 1<<4;
	else
		IOSET0=1<<5;
	while(1);
}
