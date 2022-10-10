/* 
 * File:   sigmoid.h
 * Author: 160047412
 *
 * Created on October 4, 2022, 5:35 PM
 */

#ifndef SIGMOID_H
#define	SIGMOID_H

const uint8_t sigmoidValues[16] = {128, 186, 225, 243, 250, 253, 254, 255, 16, 16, 16, 16, 16, 16, 30, 69};
const uint8_t de_sigmoidValues[16] = {64, 50, 27, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 27, 50};

uint8_t sigmoid(int z);

uint8_t de_sigmoid(int z);

#endif	/* SIGMOID_H */

