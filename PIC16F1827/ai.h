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

    int8_t Y0[N0];
    int8_t Y1[N1];
    int8_t Y2[N2];
    int Z1[N1];
    int Z2[N2];
    int8_t W1[N0][N1];
    int8_t B1[N1];
    int8_t W2[N1][N2];
    int8_t B2[N2];

    int8_t DC_DY2[N2];

    int DC_DZ2[N2];

    int8_t DC_DB2[N2];
    int8_t DC_DW2[N1][N2];
    int8_t DC_DY1[N1];

    int DC_DZ1[N1];

    int8_t DC_DB1[N1];
    int8_t DC_DW1[N0][N1];

    uint8_t choice;
    
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

#ifdef	__cplusplus
}
#endif

#endif	/* AI_H */

