
#include "mcc_generated_files/mcc.h"
#include "snake.h"
#include "ledMatrix.h"

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

uint8_t field[64];
uint8_t mapping[8] = {55, 63, 7, 8, 9, 1, 57, 56};
uint8_t snakeSize;
uint8_t headPosition;
uint8_t foodPosition;
uint8_t remainingMoves;

void snake_initiate(){
    for(uint8_t i = 0; i < 64; i++){
        field[i] = 0;
    }
    headPosition = ((uint8_t)rand())&0x3f;
    foodPosition = ((uint8_t)rand())&0x3f;
    snakeSize = 1;
    remainingMoves = MOVES_RECHARGE;
    field[headPosition] = snakeSize;
}

int8_t snake_move(uint8_t direction){
    remainingMoves--;
    for(uint8_t i = 0; i < 64; i++){
        if(field[i] > 0){
            field[i]--;
        }
    }
    int8_t incentive = NOTHING;
    direction &= 0x03;
    switch(direction){
        case UP:
            if((headPosition&0x07) == 0){
                incentive = KILL;
            } else{
                headPosition--;
            }
            break;
        case DOWN:
            if((headPosition&0x07) == 7){
                incentive = KILL;
            } else{
                headPosition++;
            }
            break;
        case LEFT:
            if((headPosition>>3) == 0){
                incentive = KILL;
            } else{
                headPosition -= 8;
            }
            break;
        case RIGHT:
            if((headPosition>>3) == 7){
                incentive = KILL;
            } else{
                headPosition += 8;
            }
            break;
    }
    if(incentive == KILL){
        snake_initiate();
    } else if(field[headPosition] > 0){
        incentive = KILL;
        snake_initiate();
    } else{
        if(headPosition == foodPosition){
            remainingMoves = MOVES_RECHARGE;
            incentive = FOOD;
            snakeSize++;
            do{
                foodPosition = ((uint8_t)rand())&0x1f;
            }while(field[foodPosition] > 0);
        }
        field[headPosition] = snakeSize;
    }
    if(remainingMoves == 0){
        incentive = KILL;
        snake_initiate();
    }
    return incentive;
}

uint8_t* snake_getField(){
    return field;
}

void snake_getSurroundings(uint8_t* surroundings){
    for(uint8_t i = 0; i < 16; i++){
        surroundings[i] = 0;
    }
    if((headPosition&0x07) == 0){
        surroundings[0] = 1;
        surroundings[1] = 1;
        surroundings[2] = 1;
    } else if((headPosition&0x07) == 7){
        surroundings[4] = 1;
        surroundings[5] = 1;
        surroundings[6] = 1;
    }
    if((headPosition>>3) == 0){
        surroundings[6] = 1;
        surroundings[7] = 1;
        surroundings[0] = 1;
    } else if((headPosition>>3) == 7){
        surroundings[2] = 1;
        surroundings[3] = 1;
        surroundings[4] = 1;
    }
    uint8_t p;
    for(uint8_t i = 0; i < 8; i++){
        p = (headPosition+mapping[i])&0x3f;
        if(p==foodPosition){
            surroundings[i+8] = 1;
        }
        if(field[p] > 0){
            surroundings[i] = 1;
        }
    }
}

uint8_t snake_getHeadPosition(){
    return headPosition;
}
void snake_setHeadPosition(uint8_t pos){
    headPosition = pos;
}

uint8_t snake_getFoodPosition(){
    return foodPosition;
}
void snake_setFoodPosition(uint8_t pos){
    foodPosition = pos;
}