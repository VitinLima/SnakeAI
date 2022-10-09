
#include "mcc_generated_files/mcc.h"
#include "snake.h"
#include "ledMatrix.h"

uint8_t field[BOARD_LENGTH];
uint8_t mapping[8] = {
    BOARD_LENGTH-BOARD_SIZE-1,
    BOARD_LENGTH-1,
    BOARD_SIZE-1,
    BOARD_SIZE,
    BOARD_SIZE+1,
    1,
    BOARD_LENGTH-BOARD_SIZE+1,
    BOARD_LENGTH-BOARD_SIZE};
uint8_t snakeSize;
uint8_t headPosition;
uint8_t foodPosition;
uint8_t remainingMoves;

void snake_initiate(){
    for(uint8_t i = 0; i < BOARD_LENGTH; i++){
        field[i] = 0;
    }
    headPosition = rand()%BOARD_LENGTH;
    foodPosition = rand()%BOARD_LENGTH;
    snakeSize = 1;
    remainingMoves = MOVES_RECHARGE;
    field[headPosition] = snakeSize;
}

int8_t snake_move(uint8_t direction){
    remainingMoves--;
    for(uint8_t i = 0; i < BOARD_LENGTH; i++){
        if(field[i] > 0){
            field[i]--;
        }
    }
    int8_t incentive = NOTHING;
    direction &= 0x03;
    switch(direction){
        case UP:
            if((headPosition%BOARD_SIZE) == 0){
                incentive = KILL;
            } else{
                headPosition--;
            }
            break;
        case DOWN:
            if((headPosition%BOARD_SIZE) == (BOARD_SIZE-1)){
                incentive = KILL;
            } else{
                headPosition++;
            }
            break;
        case LEFT:
            if((headPosition/BOARD_SIZE) == 0){
                incentive = KILL;
            } else{
                headPosition -= 8;
            }
            break;
        case RIGHT:
            if((headPosition/BOARD_SIZE) == (BOARD_SIZE-1)){
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
                foodPosition = rand()%BOARD_LENGTH;
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
    for(uint8_t i = 0; i < 8; i++){
        surroundings[i] = 0;
    }
    uint8_t lh = headPosition%BOARD_SIZE;
    uint8_t ch = headPosition/BOARD_SIZE;
    uint8_t lf = foodPosition%BOARD_SIZE;
    uint8_t cf = foodPosition/BOARD_SIZE;
    if(lh == 0){
        surroundings[0] = 1;
    } else if(lh == (BOARD_SIZE-1)){
        surroundings[1] = 1;
    }
    if(ch == 0){
        surroundings[2] = 1;
    } else if(ch == (BOARD_SIZE-1)){
        surroundings[3] = 1;
    }
    uint8_t p;
    for(uint8_t i = 0; i < 4; i++){
        p = (headPosition+mapping[i])%BOARD_LENGTH;
        if(field[p] > 0){
            surroundings[i] = 1;
        }
    }
    if(lf<lh){
        surroundings[4] = 1;
    } else if(lf>lh){
        surroundings[5] = 1;
    }
    if(cf<ch){
        surroundings[6] = 1;
    } else if(cf>ch){
        surroundings[7] = 1;
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