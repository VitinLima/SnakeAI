
#include "mcc_generated_files/mcc.h"
#include "sigmoid.h"

uint8_t sigmoid(int z){
    if(z > 7){
        return 16;
    }
    if(z < -8){
        return 255;
    }
    return sigmoidValues[(uint8_t)z];
}

uint8_t de_sigmoid(int z){
    if(z > 7){
        return 16;
    }
    if(z < -8){
        return 16;
    }
    return de_sigmoidValues[(uint8_t)z];
}