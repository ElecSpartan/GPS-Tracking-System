#ifndef TM4C_H
#define TM4C_H
#include "tm4c123gh6pm.h"
#endif
#ifndef STDINT_H
#define STDINT_H
#include <stdint.h>
#endif
#ifndef MATH_H
#define MATH_H
#include <math.h>
#endif
#ifndef _GENERALGPIO_H
#define _GENERALGPIO_H
#include "generalGPIO.h"
#endif
#ifndef _UART_H
#define _UART_H
#include "uart.h"
#endif

#ifndef LCD_H
#define LCD_H

#define LCD_Write 0
#define LCD_Read 1
#define LCD_Command 0
#define LCD_Data 1

void LCD_MOSI8bitEn(void);

void LCD_MOSI8bit(uint32_t mosi);

void LCD_MOSI8bitCommand(uint32_t command);

void LCD_MOSI8bitChar(uint32_t data);

void LCD_MOSI8bitStr(unsigned char* pt);

void LCD_8bit_Init(void);

#endif

