/* 
 * File:   ai.h
 * Author: 160047412
 *
 * Created on October 4, 2022, 9:42 PM
 */

#ifndef AI_H
#define	AI_H

#ifdef	__cplusplus
extern "C" {
#endif

#define N0 8
#define N1 4
#define N2 4

#define ADD_W1 0
#define ADD_B1 ADD_W1+N0*N1
#define ADD_W2 ADD_B1+N1
#define ADD_B2 ADD_W2+N2*N1
#define ADD_IS_AI_INITIATED ADD_B2+N2
#define ADD_IS_AI_TRAINED ADD_IS_AI_INITIATED
#define ADD_MAX_SCORE ADD_IS_AI_INITIATED+1
#define ADD_SCORES ADD_MAX_SCORE+1
    
//    void weights1_write(uint8_t add1, uint8_t add2, int8_t val);
//    void biases1_write(uint8_t add, int8_t val);
//    void weights2_write(uint8_t add1, uint8_t add2, int8_t val);
//    void biases2_write(uint8_t add, int8_t val);
//    int8_t weights1_read(uint8_t add1, uint8_t add2);
//    int8_t biases1_read(uint8_t add);
//    int8_t weights2_read(uint8_t add1, uint8_t add2);
//    int8_t biases2_read(uint8_t add);
//    
//    void ai_is_ai_initiated_write(uint8_t val);
//    uint8_t ai_is_ai_initiated_read();
//    void ai_is_ai_trained_write(uint8_t val);
//    uint8_t ai_is_ai_trained_read();
//    
//    void ai_maxScore_write(int8_t val);
//    uint8_t ai_maxScore_read();
//    void ai_scores_write(uint8_t add, int8_t val);
//    uint8_t ai_scores_read(uint8_t add);
    
    void ai_initiate();
    int8_t* ai_getInputField();
    uint8_t ai_run();
    void ai_propagate(int8_t incentive);
//    void ai_propagate(uint8_t* answer);
    void ai_printAI();

#ifdef	__cplusplus
}
#endif

#endif	/* AI_H */

