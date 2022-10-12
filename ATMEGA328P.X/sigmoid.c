
#include "mcc_generated_files/mcc.h"
#include "sigmoid.h"

const uint8_t sigmoidValues[16] = {128, 186, 225, 243, 250, 253, 254, 255, 16, 16, 16, 16, 16, 16, 30, 69};
const uint8_t de_sigmoidValues[16] = {64, 50, 27, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 27, 50};

uint8_t sigmoid(int8_t z){
    z /= 16;
    if(z < -8){
        return 16;
    }
    if(z > 7){
        return 255;
    }
    if(z < 0){
        z += 16;
    }
    return sigmoidValues[(uint8_t)z];
}

uint8_t de_sigmoid(int8_t z){
    z /= 16;
    if(z < -8){
        return 16u;
    }
    if(z > 7){
        return 16u;
    }
    if(z < 0){
        z += 16;
    }
    return de_sigmoidValues[(uint8_t)z];
}