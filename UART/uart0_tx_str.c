#include <LPC21xx.h>
#include "delay.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "uart0.h"

int main(void){
    UART0_Init();  // Initialize UART0
    while(1){
        UART0_TxString("Hello"); // Send string
        delay_ms(200);
    }
}
