/* 
 * File:   snake.h
 * Author: 160047412
 *
 * Created on October 4, 2022, 9:40 PM
 */

#ifndef SNAKE_H
#define	SNAKE_H

#ifdef	__cplusplus
extern "C" {
#endif

#define NOTHING 0
#define KILL -1
#define FOOD 1
    
    uint8_t field[64];
    uint8_t mapping[8];
    uint8_t snakeSize;
    void snake_initiate();
    int8_t snake_move(uint8_t direction);
    uint8_t* snake_getField();
    void snake_getSurroundings(uint8_t* surroundings);
    uint8_t snake_getHeadPosition();
    void snake_setHeadPosition(uint8_t pos);
    uint8_t snake_getFoodPosition();
    void snake_setFoodPosition(uint8_t pos);

#ifdef	__cplusplus
}
#endif

#endif	/* SNAKE_H */

