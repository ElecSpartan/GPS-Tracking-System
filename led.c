#include "led.h"

void RGB_set(char mask){
    mask &= 0X0E;
    GPIO_PORTF_DATA_R=mask;
}

void RGB_clear(char mask){
    mask &= 0X0E;
    GPIO_PORTF_DATA_R &= ~mask;
}