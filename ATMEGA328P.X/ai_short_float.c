
#include "mcc_generated_files/mcc.h"
#include "ai.h"
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

uint8_t choice;

void ai_initiate(){
    for(uint8_t j = 0; j < N1; j++){
        B1[j] = (float)(rand()%32)-64.0;
        for(uint8_t i = 0; i < N0; i++){
            W1[i][j] = (float)(rand()%32)-64.0;
        }
    }
}

int8_t* ai_getInputField(){
    return Y0;
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
        Y1[j] = (float)sigmoid(Z1[j])/255.0;
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
    
    float S[N1];
    if(incentive == 0){
        for(uint8_t i = 0; i < N1; i++){
            S[i] = 1.0;
        }
        S[choice] = 0.0;
    } else{
        for(uint8_t i = 0; i < N1; i++){
            S[i] = 0.0;
        }
        S[choice] = 1.0;
    }
    
    for(uint8_t j = 0; j < N1; j++){
        DC_DY1[j] = 2*(Y1[j] - S[j]);
    }
    
    for(uint8_t j = 0; j < N1; j++){
        DC_DZ1[j] = DC_DY1[j]*(float)de_sigmoid(Z1[j])/255.0;
        DC_DB1[j] = DC_DZ1[j];
        for(uint8_t i = 0; i < N0; i++){
            DC_DW1[i][j] = DC_DZ1[j]*Y0[i]);
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
    for(uint8_t i = 0; i < N0; i++){
        print(Y0[i]);
    }
    for(uint8_t j = 0; j < N1; j++){
        print(Y1[j]);
    }
    for(uint8_t j = 0; j < N1; j++){
        print((uint8_t)B1[j]);
    }
    for(uint8_t i = 0; i < N0; i++){
        for(uint8_t j = 0; j < N1; j++){
            print((uint8_t)W1[i][j]);
        }
    }
    
    for(uint8_t j = 0; j < N1; j++){
        print((uint8_t)(Z1[j]&0xffu));
        print((uint8_t)(Z1[j]>>8));
    }
    for(uint8_t j = 0; j < N1; j++){
        print((uint8_t)(DC_DZ1[j]&0xffu));
        print((uint8_t)(DC_DZ1[j]>>8));
    }
    for(uint8_t j = 0; j < N1; j++){
        print((uint8_t)DC_DY1[j]);
    }
    for(uint8_t j = 0; j < N1; j++){
        print((uint8_t)DC_DB1[j]);
    }
    for(uint8_t i = 0; i < N0; i++){
        for(uint8_t j = 0; j < N1; j++){
            print((uint8_t)DC_DW1[i][j]);
        }
    }
    for(uint8_t i = 0; i < N1; i++){
        print(sigmoid(Z1[i]));
    }
    for(uint8_t i = 0; i < N1; i++){
        print(de_sigmoid(Z1[i]));
    }
}