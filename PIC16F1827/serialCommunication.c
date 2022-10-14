
#include "mcc_generated_files/mcc.h"
#include "serialCommunication.h"
    
#define SF 0x0Fu
#define EF 0x0Au
#define SC 0xF1u
#define SF_N 0x1Fu
#define EF_N 0x1Au

void print(uint8_t b){
    if(b == SF){
        EUSART_Write(SC);
        EUSART_Write(SF_N);
    } else if(b == EF){
        EUSART_Write(SC);
        EUSART_Write(EF_N);
    } else if(b == SC){
        EUSART_Write(SC);
        EUSART_Write(SC);
    } else{
        EUSART_Write(b);
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
    EUSART_Write(SF);
}

void endMessage(){
    EUSART_Write(EF);
}