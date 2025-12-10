#include "types.h"
void UART0_Init(void);
void UART0_TxChar(u8);
u8 UART0_RxChar(void);
void UART0_TxString(const char *str);
