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
    ai_initiate();
    initMAX7219();
    
//    if(ai_is_ai_trained_read()==0){
//        for(uint16_t i = 0; i < 1000; i++){
//            snake_getSurroundings(ai_getInputField());
//            ai_propagate(snake_move(ai_run()));
//            setLine(0,(uint8_t)(i>>2));
//            setLine(1,(uint8_t)(i&0x03));
//            sendMatrix();
//        }
//        ai_is_ai_trained_write(1);
//    }
    
    uint8_t* field = snake_getField();
    
    for(uint8_t i = 0; i < BOARD_SIZE; i++){
        for(uint8_t j = 0; j < BOARD_SIZE; j++){
            if(field[i+j*BOARD_SIZE]>0){
                ledSet(i,j);
            } else{
                ledClear(i,j);
            }
        }
    }
    
    uint8_t foodPosition = snake_getFoodPosition();
    ledSet(foodPosition%BOARD_SIZE, foodPosition/BOARD_SIZE);
    sendMatrix();
    
    while (1)
    {
        // Add your application code
        __delay_ms(500);
        snake_getSurroundings(ai_getInputField());
        uint8_t choice = ai_run();
        int8_t incentive = snake_move(choice);
        ai_propagate(incentive);
        for(uint8_t i = 0; i < BOARD_SIZE; i++){
            for(uint8_t j = 0; j < BOARD_SIZE; j++){
                if(field[i+j*BOARD_SIZE]>0){
                    ledSet(i,j);
                } else{
                    ledClear(i,j);
                }
            }
        }
        ledClear(0,6);
        ledClear(2,6);
        ledClear(1,5);
        ledClear(1,7);
        ledClear(4,6);
        ledClear(6,6);
        ledClear(5,5);
        ledClear(5,7);
        ledClear(4,1);
        ledClear(6,1);
        ledClear(5,0);
        ledClear(5,2);
        if(Y0[0]>0){
            ledSet(0,6);
        } else if(Y0[1]>0){
            ledSet(2,6);
        }
        if(Y0[2]>0){
            ledSet(1,5);
        } else if(Y0[3]>0){
            ledSet(1,7);
        }
        if(Y0[4]>0){
            ledSet(4,6);
        } else if(Y0[5]>0){
            ledSet(6,6);
        }
        if(Y0[6]>0){
            ledSet(5,5);
        } else if(Y0[7]>0){
            ledSet(5,7);
        }
        switch(choice){
            case 0:
                ledSet(4,1);
                break;
            case 1:
                ledSet(6,1);
                break;
            case 2:
                ledSet(5,0);
                break;
            case 3:
                ledSet(5,2);
                break;
        }
        ledClear(7,0);
        ledClear(7,1);
        if(incentive == -1){
            ledSet(7,0);
        } else if(incentive == 1){
            ledSet(7,1);
        }
        uint8_t foodPosition = snake_getFoodPosition();
        ledSet(foodPosition%BOARD_SIZE, foodPosition/BOARD_SIZE);
        sendMatrix();
    }
}
/**
 End of File
*/