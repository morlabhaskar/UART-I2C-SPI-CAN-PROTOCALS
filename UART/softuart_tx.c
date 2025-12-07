#include "softuart.h"
#include "delay.h"
main(){
    softUART_Init();
    while(1){
        softUART_Tx('A');
    }
}
