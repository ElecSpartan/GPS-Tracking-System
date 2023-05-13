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

#ifndef GENERALGPIO_H
#define GENERALGPIO_H

#define SW2   0x01
#define RED   0x02
#define BLUE  0x04
#define GREEN 0x08
#define RGB   0x0E
#define SW1   0x10

void digitalPinMode(char port, uint32_t pin, uint32_t mode);

void digitalPortMode(char port, uint32_t mode);

void digitalPinWrite(char port, uint32_t pin, uint32_t out);

void digitalPortWrite(char port, uint32_t data);

void portFInit(void);

void LED_ON(uint8_t LED);

void LED_OFF(uint8_t LED);

uint8_t switch1(void);

uint8_t switch2(void);

#endif
