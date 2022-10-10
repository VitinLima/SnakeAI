
#include "mcc_generated_files/mcc.h"

void send(uint8_t b){
    if(b == 0x0Au){
        USART0_Write(0x0Cu);
        USART0_Write(0x1Au);
    } else if(b == 0x0Cu){
        USART0_Write(0x0Cu);
        USART0_Write(0x1Cu);
    } else{
        USART0_Write(b);
    }
}