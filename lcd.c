#include "lcd.h"

void LCD_MOSI8bitEn(void){
    digitalPinMode('D', 0, 1);
    digitalPinMode('D', 1, 1);
    digitalPinMode('D', 2, 1);
    digitalPinMode('D', 3, 1);
    digitalPinMode('E', 0, 1);
    digitalPinMode('E', 1, 1);
    digitalPinMode('E', 2, 1);
    digitalPinMode('E', 3, 1);

    /*
        A7 A6 A5    E3 E2 E1 E0 D3 D2 D1 D0
        || || ||    || || || || || || || ||
        RS RW EN    D7 D6 D5 D4 D3 D2 D1 D0
    */

    digitalPinMode('A', 5, 1);
    digitalPinMode('A', 6, 1);
    digitalPinMode('A', 7, 1);

}

void LCD_MOSI8bit(uint32_t mosi){

    /*
        E3 -> A0 -> D7
        E2 -> A1 -> D6
        E1 -> A2 -> D5
        E0 -> A3 -> D4
        D3 -> A4 -> D3
        D2 -> A5 -> D2
        D1 -> A6 -> D1
        D0 -> A7 -> D0

        A7 A6 A5    E3 E2 E1 E0 D3 D2 D1 D0
        || || ||    || || || || || || || ||
        RS RW EN    D7 D6 D5 D4 D3 D2 D1 D0
    */

    //digitalPortWrite('D', mosi & 0x0f);
    //digitalPortWrite('E', (mosi >> 4) & 0x0f);

    *(GPIO_PORTD_DATA_BITS_R + (0x03C/sizeof(uint32_t))) = (mosi & 0x0f);
    *(GPIO_PORTE_DATA_BITS_R + (0x03C/sizeof(uint32_t))) = ((mosi >> 4) & 0x0f);
}

void LCD_MOSI8bitCommand(uint32_t command){

    digitalPinWrite('A', 5, 0);
    LCD_MOSI8bit(command);
    digitalPinWrite('A', 7, LCD_Command);
    digitalPinWrite('A', 6, LCD_Write);

    digitalPinWrite('A', 5, 1);
    delayMillis(1);
    digitalPinWrite('A', 5, 0);

    LCD_MOSI8bit(0);
}

void LCD_MOSI8bitChar(uint32_t data){

    digitalPinWrite('A', 5, 0);

    LCD_MOSI8bit(data);

    digitalPinWrite('A', 7, LCD_Data);
    digitalPinWrite('A', 6, LCD_Write);

    digitalPinWrite('A', 5, 1);
    delayMillis(1);
    digitalPinWrite('A', 5, 0);

    digitalPinWrite('A', 7, 0);
    digitalPinWrite('A', 6, 0);

    LCD_MOSI8bit(0);

    LCD_MOSI8bitCommand(0x06);
}

void LCD_MOSI8bitStr(unsigned char* pt){
    while(*pt){
        LCD_MOSI8bitChar(*pt);
        pt++;
    }
}

void LCD_8bit_Init(void){
    LCD_MOSI8bitEn();
    LCD_MOSI8bitCommand(0x30);
    LCD_MOSI8bitCommand(0x0f);
    LCD_MOSI8bitCommand(0x01);
    LCD_MOSI8bitCommand(0x02);
    LCD_MOSI8bitCommand(0x38);
}
