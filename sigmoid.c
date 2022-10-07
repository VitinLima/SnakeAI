
#include "mcc_generated_files/mcc.h"
#include "sigmoid.h"

const uint8_t sigmoidValues[16] = {128, 186, 225, 243, 250, 253, 254, 255, 0, 0, 1, 2, 5, 12, 30, 69};
const uint8_t de_sigmoidValues[16] = {64, 50, 27, 12, 5, 2, 1, 0, 0, 0, 1, 2, 5, 12, 27, 50};

uint8_t sigmoid(int8_t z){
    return sigmoidValues[((uint8_t)z)>>4];
}

uint8_t de_sigmoid(int8_t z){
    return de_sigmoidValues[((uint8_t)z)>>4];
}