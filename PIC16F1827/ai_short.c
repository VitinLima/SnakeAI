
#include "mcc_generated_files/mcc.h"
#include "ai_short.h"
#include "sigmoid.h"
#include "serialCommunication.h"

//int8_t input[N0];

int8_t Y0[N0];
int8_t Y1[N1];
int Z1[N1];
int8_t B1[N1];
int8_t W1[N0][N1];

int8_t DC_DY1[N1];
int8_t DC_DZ1[N1];
int8_t DC_DB1[N1];
int8_t DC_DW1[N0][N1];

int8_t S[N1];

uint8_t choice;

void ai_initiate(){
    for(uint8_t j = 0; j < N1; j++){
        B1[j] = (rand()%32)-16;
        for(uint8_t i = 0; i < N0; i++){
            W1[i][j] = (rand()%32)-16;
        }
    }
}

int8_t* ai_getInputField(){
    return Y0;
}

uint8_t ai_run(){
    for(uint8_t i = 0; i < N0; i++){
        if(Y0[i]>0){
            Y0[i] = 1<<PRECISION;
        }
    }
    
    for(uint8_t j = 0; j < N1; j++){
        Z1[j] = B1[j];
        for(uint8_t i = 0; i < N0; i++){
            Z1[j] += (Y0[i]*W1[i][j])>>PRECISION;
        }
        Y1[j] = (int8_t)(((int)sigmoid(Z1[j]>>PRECISION)<<PRECISION)/255);
    }
    
    choice = 0;
    for(uint8_t i = 1; i < N1; i++){
        if(Y1[i]>Y1[choice]){
            choice = i;
        }
    }
    return choice;
}

void ai_propagate(int8_t incentive){
    if(incentive == 0){
        return;
    }
    
    if(incentive == -1){
        incentive = 0;
    }
    
    if(incentive == 0){
        for(uint8_t i = 0; i < N1; i++){
            S[i] = 1<<PRECISION;
        }
        S[choice] = 0;
    } else{
        for(uint8_t i = 0; i < N1; i++){
            S[i] = 0;
        }
        S[choice] = 1<<PRECISION;
    }
    
    
    for(uint8_t j = 0; j < N1; j++){
        DC_DY1[j] = 2*(Y1[j]-S[j]);
    }
    
    for(uint8_t j = 0; j < N1; j++){
        DC_DZ1[j] = ((int)DC_DY1[j]*((int)de_sigmoid(Z1[j]>>PRECISION)<<PRECISION)/255)>>PRECISION;
        DC_DB1[j] = DC_DZ1[j];
        for(uint8_t i = 0; i < N0; i++){
            DC_DW1[i][j] = (DC_DZ1[j]*Y0[i])>>PRECISION;
        }
    }
    
    for(uint8_t j = 0; j < N1; j++){
        B1[j] -= DC_DB1[j];
        for(uint8_t i = 0; i < N0; i++){
            W1[i][j] -= DC_DW1[i][j];
        }
    }
}

void ai_printAI(){
    printString("Y0");
    printString("int8_t");
    for(uint8_t i = 0; i < N0; i++){
        print((uint8_t)Y0[i]);
    }
    printString("Y1");
    printString("int8_t");
    for(uint8_t j = 0; j < N1; j++){
        print((uint8_t)Y1[j]);
    }
    printString("Z1");
    printString("int16_t");
    for(uint8_t j = 0; j < N1; j++){
        printInteger(Z1[j]);
    }
    printString("B1");
    printString("int8_t");
    for(uint8_t j = 0; j < N1; j++){
        print((uint8_t)B1[j]);
    }
    printString("W1");
    printString("int8_t");
    for(uint8_t i = 0; i < N0; i++){
        for(uint8_t j = 0; j < N1; j++){
            print((uint8_t)W1[i][j]);
        }
    }
    printString("S1");
    printString("uint8_t");
    for(uint8_t i = 0; i < N1; i++){
        print(sigmoid((int)Z1[i]));
    }
    
    printString("DC_DY1");
    printString("int8_t");
    for(uint8_t j = 0; j < N1; j++){
        print((uint8_t)DC_DY1[j]);
    }
    printString("DC_DZ1");
    printString("int8_t");
    for(uint8_t j = 0; j < N1; j++){
        print((uint8_t)DC_DZ1[j]);
    }
    printString("DC_DB1");
    printString("int8_t");
    for(uint8_t j = 0; j < N1; j++){
        print((uint8_t)DC_DB1[j]);
    }
    printString("DC_DW1");
    printString("int8_t");
    for(uint8_t i = 0; i < N0; i++){
        for(uint8_t j = 0; j < N1; j++){
            print((uint8_t)DC_DW1[i][j]);
        }
    }
    printString("DS1");
    printString("uint8_t");
    for(uint8_t i = 0; i < N1; i++){
        print(de_sigmoid((int)Z1[i]));
    }
}