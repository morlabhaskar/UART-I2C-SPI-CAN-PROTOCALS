#include "i2c.h"
#include "delay.h"

void i2c_eeprom_bytewrite(u8 slaveAddr,u8 wBufAddr,u8 data){
    //issue i2c start
    i2c_start();
    //slaveAddr + w , & take ACK
    i2c_write(slaveAddr<<1);
    //wBufAddr,ACK
    i2c_write(wBufAddr);
    //data,ACK
    i2c_write(data);
    //issue i2c stop
    i2c_stop();
    //write cycle delay
    delay_ms(10);
}
u8 i2c_eeprom_randomread(u8 slaveAddr,u8 rBufAddr){
    u8 data;
    //start condition
    i2c_start();
    //slaveAddr + w, & take ACK
    i2c_write(slaveAddr<<1);
    //wBufAddr, & take ACK
    i2c_write(rBufAddr);
    //restart
    i2c_restart();
    //slaveAddr + r, & take ACK
    i2c_write(slaveAddr<<1 | 1);
    //read byte & provide nack
    data = i2c_nack();
    //stop condition
    i2c_stop();
    return data;
}
void i2c_eeprom_pagewrite(u8 slaveAddr,u8 wBufStartAddr,s8 *p,u8 nBytes){
    u8 i;
    //issue start condition
    i2c_start();
    //slaveAddr + w, & take ACK
    i2c_write(slaveAddr<<1);
    //wBufStartAddr, & take ACK
    i2c_write(wBufStartAddr);
    for(i=0;i<nBytes;i++){
        //wData, & take ACK
        i2c_write(p[i]);
    }
    //issue stop condition
    i2c_stop();
    //delay for internal write_cycle in eeprom
    delay_ms(10);
}
void i2c_eeprom_seqread(u8 slaveAddr,u8 rBufStartAddr,s8 *p,u8 nBytes){
    u8 i;
    //issue start condition
    i2c_start();
    //slaveAddr + w, & take ACK
    i2c_write(slaveAddr<<1);
    //rBufStartAddr, & take ACK
    i2c_write(rBufStartAddr);
    //issue repeated start condition
    i2c_restart();
    //slaveAddr + r, & take ACK
    i2c_write(slaveAddr<<1 | 1);
    for(i=0;i<nBytes-1;i++){
        //read (n-1) bytes, for each, provide mack
        p[i] = i2c_mack();
    }
    //read nth (last) byte , & provide nack
    p[i] = i2c_nack();
    //issue stop condition
    i2c_stop();
}
