#include "i2c.h"
#include "i2c_eeprom.h"
#include "i2c_eeprom_defines.h"
#include "delay.h"
#include "lcd.h"
#include "arduino.h"

u8 r;
int main(){
    Init_LCD();
	init_i2c();
	i2c_eeprom_bytewrite(0x50, 0x10, 0xAB);
	r = i2c_eeprom_randomread(0x50, 0x10);
	if(r == 0xAB){
        StrLCD("CORRECT");
	}else{
        StrLCD("WRONG");
	}
	while(1);
}
