
#include "mcc_generated_files/mcc.h"
#include "serialCommunication.h"
    
#define SF 0x0Fu
#define EF 0x0Au
#define SC 0xF1u
#define SF_N 0x1Fu
#define EF_N 0x1Au

void print(uint8_t b){
    if(b == SF){
        USART0_Write(SC);
        USART0_Write(SF_N);
    } else if(b == EF){
        USART0_Write(SC);
        USART0_Write(EF_N);
    } else if(b == SC){
        USART0_Write(SC);
        USART0_Write(SC);
    } else{
        USART0_Write(b);
    }
}

void printInteger(int i){
    print((uint8_t)i);
    print((uint8_t)(i>>8));
}

void printFloat(float f){
    union {
        float f;
        uint32_t u;
    } fb;
    fb.f = f;
    for(uint8_t i = 0; i < sizeof(fb); i++){
        print((uint8_t)(fb.u>>(8*i)));
    }
}

void printString(const char *str){
    for(uint8_t i = 0; str[i]!='\0'; i++){
        print((uint8_t)str[i]);
    }
}

void startMessage(){
    USART0_Write(SF);
}

void endMessage(){
    USART0_Write(EF);
}