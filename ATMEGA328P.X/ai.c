
#include "mcc_generated_files/mcc.h"
#include "ai.h"
#include "sigmoid.h"
#include "serialCommunication.h"

int8_t Y0[N0];
int8_t Y1[N1];
int8_t Y2[N2];
int Z1[N1];
int Z2[N2];
int8_t B1[N1];
int8_t W1[N0][N1];
int8_t B2[N2];
int8_t W2[N1][N2];

int8_t DC_DY2[N2];

int DC_DZ2[N2];

int8_t DC_DB2[N2];
int8_t DC_DW2[N1][N2];
int8_t DC_DY1[N1];

int DC_DZ1[N1];

int8_t DC_DB1[N1];
int8_t DC_DW1[N0][N1];

uint8_t choice;

//void weights1_write(uint8_t add1, uint8_t add2, int8_t val){
//    eeprom_write(ADD_W1 + N0*add1 + add2, (unsigned char)val);
//}
//void biases1_write(uint8_t add, int8_t val){
//    eeprom_write(ADD_B1 + add, (unsigned char)val);
//}
//void weights2_write(uint8_t add1, uint8_t add2, int8_t val){
//    eeprom_write(ADD_W2 + N1*add1 + add2, (unsigned char)val);
//}
//void biases2_write(uint8_t add, int8_t val){
//    eeprom_write(ADD_B2 + add, (unsigned char)val);
//}
//int8_t weights1_read(uint8_t add1, uint8_t add2){
//    return (int8_t)eeprom_read(ADD_W1 + add1*N0 + add2);
//}
//int8_t biases1_read(uint8_t add){
//    return (int8_t)eeprom_read(ADD_B1 + add);
//}
//int8_t weights2_read(uint8_t add1, uint8_t add2){
//    return (int8_t)eeprom_read(ADD_W2 + add1*N1 + add2);
//}
//int8_t biases2_read(uint8_t add){
//    return (int8_t)eeprom_read(ADD_B2 + add);
//}
//
//void ai_is_ai_initiated_write(uint8_t val){
//    unsigned char c = eeprom_read(ADD_IS_AI_INITIATED);
//    if(val){
//        (c) |= 1UL << (0);
//    } else{
//        (c) &= ~(1UL << (0));
//    }
//    eeprom_write(ADD_IS_AI_INITIATED, c);
//}
//uint8_t ai_is_ai_initiated_read(){
//    return (uint8_t)(eeprom_read(ADD_IS_AI_INITIATED)&0x01);
//}
//void ai_is_ai_trained_write(uint8_t val){
//    unsigned char c = eeprom_read(ADD_IS_AI_TRAINED);
//    if(val){
//        (c) |= 1UL << (1);
//    } else{
//        (c) &= ~(1UL << (1));
//    }
//    eeprom_write(ADD_IS_AI_TRAINED, c);
//}
//uint8_t ai_is_ai_trained_read(){
//    return (uint8_t)(eeprom_read(ADD_IS_AI_TRAINED)&0x02);
//}
//
//void ai_maxScore_write(int8_t val){
//    eeprom_write(ADD_MAX_SCORE, (unsigned char)val);
//}
//uint8_t ai_maxScore_read(){
//    return (uint8_t)eeprom_read(ADD_MAX_SCORE);
//}
//void ai_scores_write(uint8_t add, int8_t val){
//    eeprom_write(ADD_SCORES, (unsigned char)val);
//}
//uint8_t ai_scores_read(uint8_t add){
//    return (uint8_t)eeprom_read(ADD_SCORES);
//}

void ai_initiate(){
//    if(ai_is_ai_initiated_read()){
//        return;
//    }
    for(uint8_t j = 0; j < N1; j++){
        B1[j] = (rand()>>8)-64;
        for(uint8_t i = 0; i < N0; i++){
            W1[i][j] = (rand()>>8)-64;
        }
    }
    for(uint8_t j = 0; j < N2; j++){
        B2[j] = (rand()>>8)-64;
        for(uint8_t i = 0; i < N1; i++){
            W2[i][j] = (rand()>>8)-64;
        }
    }
//    ai_is_ai_initiated_write(1);
}

int8_t* ai_getInputField(){
    return Y0;
}

uint8_t ai_run(){
    for(uint8_t i = 0; i < N0; i++){
        if(Y0[i] > 0){
            Y0[i] = 16;
        }
    }
    
    for(uint8_t j = 0; j < N1; j++){
        Z1[j] = B1[j];
        for(uint8_t i = 0; i < N0; i++){
            Z1[j] += ((int)Y0[i]*(int)W1[i][j])/16;
        }
        Y1[j] = sigmoid(Z1[j])/16;
    }
    for(uint8_t j = 0; j < N2; j++){
        Z2[j] = B2[j];
        for(uint8_t i = 0; i < N1; i++){
            Z2[j] += ((int)Y1[i]*(int)W2[i][j])/16;
        }
        Y2[j] = sigmoid(Z2[j])/16;
    }
    
    choice = 0;
    for(uint8_t i = 1; i < N2; i++){
        if(Y2[i]>Y2[choice]){
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
    
    int8_t S[N2];
    if(incentive == 0){
        for(uint8_t i = 0; i < N2; i++){
            S[i] = 16;
        }
        S[choice] = 0;
    } else{
        for(uint8_t i = 0; i < N2; i++){
            S[i] = 0;
        }
        S[choice] = 16;
    }
    
    for(uint8_t j = 0; j < N2; j++){
        DC_DY2[j] = 2*((int)Y2[j] - (int)S[j]);
    }
    
    for(uint8_t j = 0; j < N1; j++){
        DC_DY1[j] = 0;
    }
    
    for(uint8_t j = 0; j < N2; j++){
        DC_DZ2[j] = ((int)DC_DY2[j]*(int)de_sigmoid(Z2[j]))/16/16;
        DC_DB2[j] = DC_DZ2[j];
        for(uint8_t i = 0; i < N1; i++){
            DC_DW2[i][j] = ((int)DC_DZ2[j]*(int)Y1[i])/16;
            DC_DY1[i] += ((int)DC_DZ2[j]*(int)W2[i][j])/16;
        }
    }
    for(uint8_t j = 0; j < N1; j++){
        DC_DZ1[j] = ((int)DC_DY1[j]*(int)de_sigmoid(Z1[j]))/16/16;
        DC_DB1[j] = DC_DZ1[j];
        for(uint8_t i = 0; i < N0; i++){
            DC_DW1[i][j] = ((int)DC_DZ1[j]*(int)Y0[i])/16;
        }
    }
    
    for(uint8_t j = 0; j < N2; j++){
        B2[j] -= DC_DB2[j];
        for(uint8_t i = 0; i < N1; i++){
            W2[i][j] -= DC_DW2[i][j];
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
    for(uint8_t j = 0; j < N2; j++){
        print(Y2[j]);
    }
    for(uint8_t j = 0; j < N1; j++){
        print((uint8_t)B1[j]);
    }
    for(uint8_t j = 0; j < N2; j++){
        print((uint8_t)B2[j]);
    }
    for(uint8_t i = 0; i < N0; i++){
        for(uint8_t j = 0; j < N1; j++){
            print((uint8_t)W1[i][j]);
        }
    }
    for(uint8_t i = 0; i < N1; i++){
        for(uint8_t j = 0; j < N1; j++){
            print((uint8_t)W2[i][j]);
        }
    }
    
    for(uint8_t j = 0; j < N1; j++){
        print((uint8_t)(Z1[j]&0xffu));
        print((uint8_t)(Z1[j]>>8));
    }
    for(uint8_t j = 0; j < N2; j++){
        print((uint8_t)(Z2[j]&0xffu));
        print((uint8_t)(Z2[j]>>8));
    }
    for(uint8_t j = 0; j < N1; j++){
        print((uint8_t)(DC_DZ1[j]&0xffu));
        print((uint8_t)(DC_DZ1[j]>>8));
    }
    for(uint8_t j = 0; j < N2; j++){
        print((uint8_t)(DC_DZ2[j]&0xffu));
        print((uint8_t)(DC_DZ2[j]>>8));
    }
    for(uint8_t j = 0; j < N1; j++){
        print((uint8_t)DC_DY1[j]);
    }
    for(uint8_t j = 0; j < N2; j++){
        print((uint8_t)DC_DY2[j]);
    }
    for(uint8_t j = 0; j < N1; j++){
        print((uint8_t)DC_DB1[j]);
    }
    for(uint8_t j = 0; j < N2; j++){
        print((uint8_t)DC_DB2[j]);
    }
    for(uint8_t i = 0; i < N0; i++){
        for(uint8_t j = 0; j < N1; j++){
            print((uint8_t)DC_DW1[i][j]);
        }
    }
    for(uint8_t i = 0; i < N1; i++){
        for(uint8_t j = 0; j < N2; j++){
            print((uint8_t)DC_DW2[i][j]);
        }
    }
    for(uint8_t i = 0; i < N1; i++){
        print(sigmoid(Z1[i]));
//        print(sigmoid(16*(i-8)));
//        print(0);
    }
    for(uint8_t i = 0; i < N2; i++){
        print(sigmoid(Z2[i]));
//        print(sigmoid(16*(i-4)));
    }
    for(uint8_t i = 0; i < N1; i++){
        print(de_sigmoid(Z1[i]));
//        print(sigmoid(16*(i)));
    }
    for(uint8_t i = 0; i < N2; i++){
        print(de_sigmoid(Z2[i]));
//        print(sigmoid(16*(i+4)));
    }
}

//void ai_propagate(uint8_t* answer){
//    
//}