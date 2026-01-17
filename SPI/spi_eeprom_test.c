#include<LPC214x.h>
#include"types.h"
#include"delay.h"
#include"lcd.h"
#include"lcd_defines.h"
#include"spi.h"
u8 data;
int main(){
    IODIR1 |= (1<<16) | (1<<17);
    IOCLR1 &= ~(1<<16);
    IOCLR1 &= ~(1<<17);
    Init_LCD();
    Init_SPI();
    delay_ms(10);
    StrLCD("25LC512 TEST");
    delay_ms(1000);
    byteWrite(0x0010,'A');
    delay_ms(1000);
    data=byteRead(0x0010);
    CmdLCD(CLEAR_LCD);
    if(data=='A'){
        StrLCD("CORRECT");
        IOSET1 = 1<<16;
    }else{
        StrLCD("WRONG");
        IOSET1 = 1<<17;
    }
    while(1);
}
