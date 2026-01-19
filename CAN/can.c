#include<LPC21xx.h>
#include"types.h"
#include"delay.h"
#include"can_defines.h"
void Init_CAN1(void){
    //cfg P0.25 as CAN1_Rx Pin(RD1)
    PINSEL1 |= RD1_PIN_0_25;
    //reset CAN1 Controller
    C1MOD=1<<RM_BIT;
    //all recievd messages are accepted
    //bypasses the normal acceptanc filter logic
    AFMR = 1<<ACCBP_BIT;
    //set baud rate for CAN
    C1BTR=BTR_LVAL;
    //enable CAN1 controller
    C1MOD &= ~(1<<RM_BIT);
}
