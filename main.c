/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16F1827
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"

#include "ledMatrix.h"
#include "snake.h"
#include "ai.h"

void deactivateElevator(){
    LATAbits.LATA3 = 0;
    LATAbits.LATA7 = 0;
    
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    TRISAbits.TRISA2 = 1;
    TRISAbits.TRISA3 = 0;
    TRISAbits.TRISA4 = 1;
    TRISAbits.TRISA7 = 0;
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB3 = 1;
}

//void test(uint8_t lh, uint8_t ch, uint8_t lf, uint8_t cf, uint8_t* ai_inputs){
//    snake_setHeadPosition(lh+8*ch);
//    snake_setFoodPosition(lf+8*cf);
//    ledSet(lf,cf);
//    snake_getSurroundings(ai_inputs);
//    ai_inputs[8] == 0 ? ledClear(3,3) : ledSet(3,3);
//    ai_inputs[9] == 0 ? ledClear(3,4) : ledSet(3,4);
//    ai_inputs[10] == 0 ? ledClear(3,5) : ledSet(3,5);
//    ai_inputs[11] == 0 ? ledClear(4,5) : ledSet(4,5);
//    ai_inputs[12] == 0 ? ledClear(5,5) : ledSet(5,5);
//    ai_inputs[13] == 0 ? ledClear(5,4) : ledSet(5,4);
//    ai_inputs[14] == 0 ? ledClear(5,3) : ledSet(5,3);
//    ai_inputs[15] == 0 ? ledClear(4,3) : ledSet(4,3);
//    sendMatrix();
//    __delay_ms(500);
//    ledClear(lf,cf);
//}

/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    deactivateElevator();
    snake_initiate();
//    ai_initiate();
    initMAX7219();
    
//    uint8_t ai_inputs[16];
//    ledSet(4,4);
//    while(1){
//        uint8_t lh = 3, ch = 3;
//        
//        test(lh, ch, lh-1, ch-1, ai_inputs);
//        test(lh, ch, lh-1, ch, ai_inputs);
//        test(lh, ch, lh-1, ch+1, ai_inputs);
//        test(lh, ch, lh, ch+1, ai_inputs);
//        test(lh, ch, lh+1, ch+1, ai_inputs);
//        test(lh, ch, lh+1, ch, ai_inputs);
//        test(lh, ch, lh+1, ch-1, ai_inputs);
//        test(lh, ch, lh, ch-1, ai_inputs);
//        
//        lh = 5, ch = 3;
//        
//        test(lh, ch, lh-1, ch-1, ai_inputs);
//        test(lh, ch, lh-1, ch, ai_inputs);
//        test(lh, ch, lh-1, ch+1, ai_inputs);
//        test(lh, ch, lh, ch+1, ai_inputs);
//        test(lh, ch, lh+1, ch+1, ai_inputs);
//        test(lh, ch, lh+1, ch, ai_inputs);
//        test(lh, ch, lh+1, ch-1, ai_inputs);
//        test(lh, ch, lh, ch-1, ai_inputs);
//        
//        lh = 6, ch = 2;
//        
//        test(lh, ch, lh-1, ch-1, ai_inputs);
//        test(lh, ch, lh-1, ch, ai_inputs);
//        test(lh, ch, lh-1, ch+1, ai_inputs);
//        test(lh, ch, lh, ch+1, ai_inputs);
//        test(lh, ch, lh+1, ch+1, ai_inputs);
//        test(lh, ch, lh+1, ch, ai_inputs);
//        test(lh, ch, lh+1, ch-1, ai_inputs);
//        test(lh, ch, lh, ch-1, ai_inputs);
//        
//        lh = 2, ch = 4;
//        
//        test(lh, ch, lh-1, ch-1, ai_inputs);
//        test(lh, ch, lh-1, ch, ai_inputs);
//        test(lh, ch, lh-1, ch+1, ai_inputs);
//        test(lh, ch, lh, ch+1, ai_inputs);
//        test(lh, ch, lh+1, ch+1, ai_inputs);
//        test(lh, ch, lh+1, ch, ai_inputs);
//        test(lh, ch, lh+1, ch-1, ai_inputs);
//        test(lh, ch, lh, ch-1, ai_inputs);
//    }
    
    uint8_t* field = snake_getField();
    
    for(uint8_t i = 0; i < 8; i++){
        for(uint8_t j = 0; j < 8; j++){
            if(field[i+j*8]>0){
                ledSet(i,j);
            } else{
                ledClear(i,j);
            }
        }
    }
    uint8_t foodPosition = snake_getFoodPosition();
    ledSet(foodPosition&0x03, foodPosition>>3);
    sendMatrix();
    
    uint8_t d = 0;
    
//    if(ai_is_ai_trained_read()==0){
//        for(int i = 0; i < 1000; i++){
//            snake_getSurroundings(ai_getInputField());
//            ai_propagate(snake_move(ai_run()));
//        }
//        ai_is_ai_trained_write(1);
//    }
    
    while (1)
    {
        // Add your application code
        __delay_ms(100);
        snake_getSurroundings(ai_getInputField());
        ai_propagate(snake_move(ai_run()));
        for(uint8_t i = 0; i < 8; i++){
            for(uint8_t j = 0; j < 8; j++){
                if(field[i+j*8]>0){
                    ledSet(i,j);
                } else{
                    ledClear(i,j);
                }
            }
        }
        uint8_t foodPosition = snake_getFoodPosition();
        ledSet(foodPosition&0x03, foodPosition>>3);
        sendMatrix();
    }
}
/**
 End of File
*/