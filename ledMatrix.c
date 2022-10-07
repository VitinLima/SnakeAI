
#include "mcc_generated_files/mcc.h"
#include "ledMatrix.h"

void txMAX7219(uint8_t addr0, uint8_t dat0){
    LATBbits.LATB1 = 0;
    SPI1_WriteByte(addr0);
    while(!PIR1bits.SSP1IF);
    PIR1bits.SSP1IF = 0;
    SPI1_WriteByte(dat0);
    while(!PIR1bits.SSP1IF);
    PIR1bits.SSP1IF = 0;
    LATBbits.LATB1 = 1;
}

void initMAX7219(){
    LATBbits.LATB1 = 1;
    TRISBbits.TRISB1 = 0;
    SSP1CON1bits.SSPEN = 1;
    txMAX7219(0x09,0x00); // Decode mode = 0
    txMAX7219(0x0A,0x00); // Intensity 17/32
    txMAX7219(0x0C,0x00); // Shutdown mode = 0
    txMAX7219(0x0B,0x07); // Scan Limit
    txMAX7219(0x0C,0x01); // Shutdown mode = 1
    txMAX7219(0x0F,0x01); // Display-Test = 1
    __delay_ms(1000);
    txMAX7219(0x0F,0x00); // Display-Test = 0
    txMAX7219(0x0C,0x01); // Shutdown mode = 1
}

void ledSet(uint8_t l, uint8_t c){
    (matrix[l]) |= 1UL << (c);
}

void ledClear(uint8_t l, uint8_t c){
    (matrix[l]) &= ~(1UL << (c));
}

void sendMatrix(){
    uint8_t b;
    uint8_t nb;
    for(uint8_t i=0;i<8;i++){
#if HORIZONTAL_FLIP==1
        b = matrix[7-i];
#else
        b = matrix[i];
#endif
#if VERTICAL_FLIP==1
        nb = 0x00;
        for(uint8_t j = 0; j < 8; j++){
            nb |= b&0x01;
            nb <<= 1;
            b >>= 1;
        }
        txMAX7219(i+1,nb);
#else
        txMAX7219(i+1,b);
#endif
    }
}

