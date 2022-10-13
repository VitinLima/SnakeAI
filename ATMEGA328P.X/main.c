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

#define _XTAL_FREQ 16000000
#define __delay_us(x) __builtin_avr_delay_cycles((unsigned long)((x)*(_XTAL_FREQ/1000000.0)))
#define __delay_ms(x) __builtin_avr_delay_cycles((unsigned long)((x)*(_XTAL_FREQ/1000.0)))

#include "mcc_generated_files/mcc.h"
#include "snake.h"
#include "ai_short_float.h"
#include "serialCommunication.h"

/*
    Main application
*/
int main(void)
{
    /* Initializes MCU, drivers and middleware */
    SYSTEM_Initialize();

    /* Replace with your application code */
    snake_initiate();
    ai_initiate();
    
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
    
//    for(uint8_t i = 0; i < BOARD_LENGTH; i++){
//        print(field[i]);
//    }
//    
//    print(snake_getFoodPosition());
    
    while (1){
        __delay_ms(100);
        snake_getSurroundings(ai_getInputField());
        uint8_t choice = ai_run();
        int8_t incentive = snake_move(choice);
        ai_propagate(incentive);
        startMessage();
        if(incentive==-1){
            ai_printAI();
//            printString("data");
//            printString("uint8_t");
//            print(snake_getHeadPosition());
//            printString("data");
//            printString("uint8_t");
//            print(snake_getFoodPosition());
//            snake_initiate();
        }
        printString("field");
        printString("uint8_t");
        for(uint8_t i = 0; i < BOARD_LENGTH; i++){
            print(field[i]);
        }
        printString("food");
        printString("uint8_t");
        print(snake_getFoodPosition());
        endMessage();
    }
}
/**
    End of File
*/
