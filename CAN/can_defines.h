#ifndef __CAN_DEFINES_H__
#define __CAN_DEFINES_H__

//defines required for C1BTR
#define FOSC 12000000
#define CCLK (FOSC*5)
#define PCLK (CCLK/4)
#define QUANTA 15
#define BIT_RATE 125000//Hz
#define BRP (PCLK/(BIT_RATE*QUANTA))
#define SAMPLE_POINT (0.7*QUANTA)
#define TSEG1 ((int)SAMPLE_POINT-1)
#define TSEG2 (QUANTA-(1+TSEG1))
#define SJW ((TSEG2>=2)?4:(TSEG2-1))
#define TD1_PIN
#define RD1_PIN_0_25 0x00040000
//cfg values for CxBTR sfr
#define SAM 0 //0/01,sample bus 1/3 times(s) 
#define BTR_LVAL (SAM<<23 | ((TSEG2-1)<<20) | ((TSEG1-1)<<16) | ((SJW-1)<<14) | (BRP-1))
//CxCMR sfr bit defines
#define TR_BIT 0
#define RRB_BIT 2
#define STB1_BIT 5
//CxGSR sfr bit defines
#define RBS_BIT 0
#define TBS1_BIT 2
#define TCS1_BIT 3
//CxTFI1/CxRFS sfr bit defines
#define RTR_BIT 30
#define DLC_BIT 16
//CxMOD sfr bit defines
#define RM_BIT 0
//AFMR sfr bit defines
#define ACCOFF_BIT 0
#define ACCBP_BIT 1

#endif