#include<LPC21xx.h>
#include "types.h"
#include "i2c_defines.h"

void init_i2c(void){
    //cfg p0.2,p0.3 for SCL,SDA functions using PINSEL0
    PINSEL0 |= SCL_0_2 | SDA_0_3;
    //cfg speed for I2C serial communication
    I2SCLH = I2C_DIVIDER;
    I2SCLL = I2C_DIVIDER;
    //I2C peripheral enable for communication
    I2CONSET = 1<<I2EN_BIT;
}
void i2c_start(void){
    //start condition
    I2CONSET = 1<<STA_BIT;
    //wait for start bit status
    while(((I2CONSET>>SI_BIT)&1)==0);
    //clear start condition
    I2CONCLR = 1<<STAC_BIT;
}
void i2c_restart(void){
    //start condition
    I2CONSET = 1<<STA_BIT;
    //clear SIC bit to initiate repeated start
    I2CONCLR = 1<<SIC_BIT;
    //wait for restart bit status
    while(((I2CONSET>>SI_BIT)&1)==0);
    //clear start condition
    I2CONCLR = 1<<STAC_BIT;
}
void i2c_stop(void){
    //start condition
    I2CONSET = 1<<STO_BIT;
    //clear SIC bit to initiate stop
    I2CONCLR = 1<<SIC_BIT;
}
void i2c_write(u8 data){
    //put data into I2DAT
    I2DAT = data;
    //clear SIC_BIT initiates serialization out or transmission begins
    I2CONCLR = 1<<SIC_BIT;
    //wait for SI bit status , end of serialization or transmission finished
    while(((I2CONSET>>SI_BIT)&1)==0);
}
u8 i2c_nack(void){
    //clear SIC_BIT initiates serialization in
    I2CONCLR = 1<<SIC_BIT;
    //wait for SI BIT status, end of serialization
    while(((I2CONSET>>SI_BIT)&1)==0);
    return I2DAT;
}
u8 i2c_mack(void){
    //cfg AA_BIT, to issue mack
    I2CONSET = 1<<AA_BIT;
    //clear SIC_BIT initiates serialization in
    I2CONCLR = 1<<SIC_BIT;
    //wait for SI_BIT status ,end of serialization
    while(((I2CONSET>>SI_BIT)&1)==0);
    //clear AA_BIT
    I2CONCLR = 1<<AAC_BIT;
    return I2DAT;
}
