
#include "mcc_generated_files/mcc.h"
#include "ai_short_float.h"
#include "sigmoid.h"
#include "serialCommunication.h"

int8_t input[N0];

float Y0[N0];
float Y1[N1];
float Z1[N1];
float B1[N1];
float W1[N0][N1];

float DC_DY1[N1];
float DC_DZ1[N1];
float DC_DB1[N1];
float DC_DW1[N0][N1];

float S[N1];

uint8_t choice;

void ai_initiate(){
    for(uint8_t j = 0; j < N1; j++){
        B1[j] = (float)(rand()%32)-16.0f;
        for(uint8_t i = 0; i < N0; i++){
            W1[i][j] = (float)(rand()%32)-16.0f;
        }
    }
}

int8_t* ai_getInputField(){
    return input;
}

uint8_t ai_run(){
    for(uint8_t i = 0; i < N0; i++){
        Y0[i] = (float)input[i];
    }
    
    for(uint8_t j = 0; j < N1; j++){
        Z1[j] = B1[j];
        for(uint8_t i = 0; i < N0; i++){
            Z1[j] += Y0[i]*W1[i][j];
        }
        Y1[j] = (float)sigmoid((int)Z1[j])/255.0f;
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
            S[i] = 1.0f;
        }
        S[choice] = 0.0f;
    } else{
        for(uint8_t i = 0; i < N1; i++){
            S[i] = 0.0f;
        }
        S[choice] = 1.0f;
    }
    
    
    for(uint8_t j = 0; j < N1; j++){
        DC_DY1[j] = 2.0f*(Y1[j]-S[j]);
    }
    
    for(uint8_t j = 0; j < N1; j++){
        DC_DZ1[j] = DC_DY1[j]*(float)de_sigmoid((int)Z1[j])/255.0f;
        DC_DB1[j] = DC_DZ1[j];
        for(uint8_t i = 0; i < N0; i++){
            DC_DW1[i][j] = DC_DZ1[j]*Y0[i];
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
    printString("Y0float");
    for(uint8_t i = 0; i < N0; i++){
        printFloat(Y0[i]);
//        printFloat(0.35);
    }
    printString("Y1float");
    for(uint8_t j = 0; j < N1; j++){
        printFloat(Y1[j]);
//        printFloat(0.35f);
    }
    printString("Z1float");
    for(uint8_t j = 0; j < N1; j++){
        printFloat(Z1[j]);
    }
    printString("B1float");
    for(uint8_t j = 0; j < N1; j++){
        printFloat(B1[j]);
    }
    printString("W1float");
    for(uint8_t i = 0; i < N0; i++){
        for(uint8_t j = 0; j < N1; j++){
            printFloat(W1[i][j]);
        }
    }
    printString("S1uint8_t");
    for(uint8_t i = 0; i < N1; i++){
        print(sigmoid((int)Z1[i]));
    }
    
    printString("DC_DY1float");
    for(uint8_t j = 0; j < N1; j++){
        printFloat(DC_DY1[j]);
    }
    printString("DC_DZ1float");
    for(uint8_t j = 0; j < N1; j++){
        printFloat(DC_DZ1[j]);
    }
    printString("DC_DB1float");
    for(uint8_t j = 0; j < N1; j++){
        printFloat(DC_DB1[j]);
    }
    printString("DC_DW1float");
    for(uint8_t i = 0; i < N0; i++){
        for(uint8_t j = 0; j < N1; j++){
            printFloat(DC_DW1[i][j]);
        }
    }
    printString("DS1uint8_t");
    for(uint8_t i = 0; i < N1; i++){
        print(de_sigmoid((int)Z1[i]));
    }
}