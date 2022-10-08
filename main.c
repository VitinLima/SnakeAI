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
    //ai_initiate();
    initMAX7219();
    
//    uint8_t* field = snake_getField();
    
//    for(uint8_t i = 0; i < 8; i++){
//        for(uint8_t j = 0; j < 8; j++){
//            if(field[i+j*8]>0){
//                ledSet(i,j);
//            } else{
//                ledClear(i,j);
//            }
//        }
//    }
//    uint8_t foodPosition = snake_getFoodPosition();
//    ledSet(foodPosition&0x03, foodPosition>>3);
//    sendMatrix();
    
//    uint8_t d = 0;
    
    while(1){
        for(uint8_t i = 0; i < 8; i++){
            setColumn(i, 0b10010110);
            sendMatrix();
            __delay_ms(200);
            setColumn(i, 0x00);
        }
    }
    
    while(1){
//        __delay_ms(500);
//        snake_move(d++);
//        if(d == 4){
//            d = 0;
//        }
//        for(uint8_t i = 0; i < 8; i++){
//            for(uint8_t j = 0; j < 8; j++){
//                if(field[i+j*8]>0){
//                    ledSet(i,j);
//                } else{
//                    ledClear(i,j);
//                }
//            }
//        }
//        uint8_t foodPosition = snake_getFoodPosition();
//        ledSet(foodPosition&0x03, foodPosition>>3);
//        sendMatrix();
    }
    
    /*if(ai_is_ai_trained_read()==0){
        for(int i = 0; i < 1000; i++){
            snake_getSurroundings(ai_getInputField());
            ai_propagate(snake_move(ai_run()));
        }
        ai_is_ai_trained_write(1);
    }
    
    while (1)
    {
        // Add your application code
        __delay_ms(500);
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
    }*/
}
/**
 End of File
*/