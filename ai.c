
#include "mcc_generated_files/mcc.h"
#include "ai.h"
#include "sigmoid.h"

uint8_t Y0[N0];
uint8_t Y1[N1];
uint8_t Y2[N2];
int16_t Z1[N1];
int16_t Z2[N2];

void weights1_write(uint8_t add1, uint8_t add2, int8_t val){
    eeprom_write(ADD_W1 + N0*add1 + add2, (unsigned char)val);
}
void biases1_write(uint8_t add, int8_t val){
    eeprom_write(ADD_B1 + add, (unsigned char)val);
}
void weights2_write(uint8_t add1, uint8_t add2, int8_t val){
    eeprom_write(ADD_W2 + N1*add1 + add2, (unsigned char)val);
}
void biases2_write(uint8_t add, int8_t val){
    eeprom_write(ADD_B2 + add, (unsigned char)val);
}
int8_t weights1_read(uint8_t add1, uint8_t add2){
    return (int8_t)eeprom_read(ADD_W1 + add1*N0 + add2);
}
int8_t biases1_read(uint8_t add){
    return (int8_t)eeprom_read(ADD_B1 + add);
}
int8_t weights2_read(uint8_t add1, uint8_t add2){
    return (int8_t)eeprom_read(ADD_W2 + add1*N1 + add2);
}
int8_t biases2_read(uint8_t add){
    return (int8_t)eeprom_read(ADD_B2 + add);
}

void ai_is_ai_initiated_write(uint8_t val){
    unsigned char c = eeprom_read(ADD_IS_AI_INITIATED);
    if(val){
        (c) |= 1UL << (0);
    } else{
        (c) &= ~(1UL << (0));
    }
    eeprom_write(ADD_IS_AI_INITIATED, c);
}
uint8_t ai_is_ai_initiated_read(){
    return (uint8_t)(eeprom_read(ADD_IS_AI_INITIATED)&0x01);
}
void ai_is_ai_trained_write(uint8_t val){
    unsigned char c = eeprom_read(ADD_IS_AI_TRAINED);
    if(val){
        (c) |= 1UL << (1);
    } else{
        (c) &= ~(1UL << (1));
    }
    eeprom_write(ADD_IS_AI_TRAINED, c);
}
uint8_t ai_is_ai_trained_read(){
    return (uint8_t)(eeprom_read(ADD_IS_AI_TRAINED)&0x02);
}

void ai_maxScore_write(int8_t val){
    eeprom_write(ADD_MAX_SCORE, (unsigned char)val);
}
uint8_t ai_maxScore_read(){
    return (uint8_t)eeprom_read(ADD_MAX_SCORE);
}
void ai_scores_write(uint8_t add, int8_t val){
    eeprom_write(ADD_SCORES, (unsigned char)val);
}
uint8_t ai_scores_read(uint8_t add){
    return (uint8_t)eeprom_read(ADD_SCORES);
}

void ai_initiate(){
    if(ai_is_ai_initiated_read()){
        return;
    }
    for(uint8_t j = 0; j < N1; j++){
        biases1_write(j, (int8_t)rand());
        for(uint8_t i = 0; i < N0; i++){
            weights1_write(i,j, (int8_t)rand());
        }
    }
    for(uint8_t j = 0; j < N2; j++){
        biases2_write(j, (int8_t)rand());
        for(uint8_t i = 0; i < N1; i++){
            weights2_write(i,j, (int8_t)rand());
        }
    }
    ai_is_ai_initiated_write(1);
}

uint8_t* ai_getInputField(){
    return Y0;
}

uint8_t ai_run(){
    int16_t z;
    for(uint8_t j = 0; j < N1; j++){
        Z1[j] = biases1_read(j);
        for(uint8_t i = 0; i < N0; i++){
            z = (int16_t)Y0[i];
            z *= weights1_read(i,j);
            z /= 255;
            Z1[j] += z;
        }
        Y1[j] = sigmoid((uint8_t)Z1[j]);
    }
    for(uint8_t j = 0; j < N2; j++){
        Z2[j] = biases2_read(j);
        for(uint8_t i = 0; i < N1; i++){
            z = (int16_t)Y1[i];
            z *= weights2_read(i,j);
            z /= 255;
            Z2[j] += z;
        }
        Y2[j] = sigmoid((uint8_t)Z2[j]);
    }
    
    uint8_t choice = 0;
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
    
}

//void ai_propagate(uint8_t* answer){
//    
//}