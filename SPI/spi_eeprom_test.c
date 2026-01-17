#include<LPC214x.h>
#include"types.h"
#include"delay.h"
#include"lcd.h"
#include"lcd_defines.h"
#include"spi.h"
u8 data;
int main(){
    
    Init_LCD();
    Init_SPI();
    StrLCD("25LC512 TEST");
    delay_ms(1000);
    byteWrite(0x0010,'A');
    data=byteRead(0x0010);
    CmdLCD(GOTO_LINE2_POS0);
    if(data=='A'){
        StrLCD("CORRECT");
    }else{
        StrLCD("WRONG");
    }
}
