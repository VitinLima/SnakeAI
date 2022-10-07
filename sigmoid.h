/* 
 * File:   sigmoid.h
 * Author: 160047412
 *
 * Created on October 4, 2022, 5:35 PM
 */

#ifndef SIGMOID_H
#define	SIGMOID_H

const uint8_t sigmoidValues[16];
const uint8_t de_sigmoidValues[16];

uint8_t sigmoid(uint8_t z);

uint8_t de_sigmoid(uint8_t z);

#endif	/* SIGMOID_H */

