#include "generalGPIO.h"

void digitalPinMode(char port, uint32_t pin, uint32_t mode){
    uint32_t pinD = 1 << pin, clk = 1;
    volatile uint32_t* baseAddress;

    switch(port){
        case 'A': baseAddress = GPIO_PORTA_DATA_BITS_R; clk = clk << 0; if(pin>7) return; break;
        case 'B': baseAddress = GPIO_PORTB_DATA_BITS_R; clk = clk << 1; if(pin>7) return; break;
        case 'C': baseAddress = GPIO_PORTC_DATA_BITS_R; clk = clk << 2; if(pin>7) return; break;
        case 'D': baseAddress = GPIO_PORTD_DATA_BITS_R; clk = clk << 3; if(pin>7) return; break;
        case 'E': baseAddress = GPIO_PORTE_DATA_BITS_R; clk = clk << 4; if(pin>5) return; break;
        case 'F': baseAddress = GPIO_PORTF_DATA_BITS_R; clk = clk << 5; if(pin>4) return; break;
        default: return;
    }

    SYSCTL_RCGCGPIO_R |= clk; // Connect Clock to Port
    while((SYSCTL_PRGPIO_R & clk) == 0); // Wait for Clock

    *((volatile uint32_t*)(baseAddress + (0x520/sizeof(uint32_t))))  = 0x4C4F434B; // Unlock

    *((volatile uint32_t*)(baseAddress + (0x524/sizeof(uint32_t)))) |=  pinD; // CR

    *((volatile uint32_t*)(baseAddress + (0x420/sizeof(uint32_t)))) &= ~pinD; // AFSEL
    *((volatile uint32_t*)(baseAddress + (0x52C/sizeof(uint32_t)))) &= ~((0xf)<<(pin*4)); // PCTL
    *((volatile uint32_t*)(baseAddress + (0x528/sizeof(uint32_t)))) &= ~pinD; // AMSEL
    *((volatile uint32_t*)(baseAddress + (0x51C/sizeof(uint32_t)))) |=  pinD; // DEN

    if(mode == 1){ // Output
        *((volatile uint32_t*)(baseAddress + (0x400/sizeof(uint32_t)))) |=  pinD; // DIR
        *((volatile uint32_t*)(baseAddress + (0x510/sizeof(uint32_t)))) |=  pinD; // PUR
        *((volatile uint32_t*)(baseAddress + (0x514/sizeof(uint32_t)))) &= ~pinD; // PDN
    }
    else if(mode == 0){ // Input
        *((volatile uint32_t*)(baseAddress + (0x400/sizeof(uint32_t)))) &= ~pinD; // DIR
        *((volatile uint32_t*)(baseAddress + (0x510/sizeof(uint32_t)))) &= ~pinD; // PUR
        *((volatile uint32_t*)(baseAddress + (0x514/sizeof(uint32_t)))) |=  pinD; // PDN
    }

    *((volatile uint32_t*)baseAddress) &= 1; // DATA
}

void digitalPortMode(char port, uint32_t mode){
    int i = (port == 'F')? 5 : (port == 'E')? 6 : 8, j = 0;
    while(j<i){
        digitalPinMode(port, j++, mode%2);
        mode = mode >> 1;
    }
}

void digitalPinWrite(char port, uint32_t pin, uint32_t out){
    uint32_t pinD = 1 << pin, pinOffset;
    volatile uint32_t* baseAddress;

    switch(port){
        case 'A': baseAddress = GPIO_PORTA_DATA_BITS_R; if(pin>7) return; break;
        case 'B': baseAddress = GPIO_PORTB_DATA_BITS_R; if(pin>7) return; break;
        case 'C': baseAddress = GPIO_PORTC_DATA_BITS_R; if(pin>7) return; break;
        case 'D': baseAddress = GPIO_PORTD_DATA_BITS_R; if(pin>7) return; break;
        case 'E': baseAddress = GPIO_PORTE_DATA_BITS_R; if(pin>5) return; break;
        case 'F': baseAddress = GPIO_PORTF_DATA_BITS_R; if(pin>4) return; break;
        default: return;
    }

    if(!((*((volatile uint32_t*)(baseAddress + (0x400/sizeof(uint32_t))))) | pinD))
        return;

    switch (pin) {
        case 0:
            pinOffset = 0x04;
            break;
        case 1:
            pinOffset = 0x08;
            break;
        case 2:
            pinOffset = 0x10;
            break;
        case 3:
            pinOffset = 0x20;
            break;
        case 4:
            pinOffset = 0x40;
            break;
        case 5:
            pinOffset = 0x80;
            break;
        case 6:
            pinOffset = 0x100;
            break;
        case 7:
            pinOffset = 0x200;
            break;
        default:
            return;
    }

    if(out == 0)
        *(((volatile uint32_t*)baseAddress + (pinOffset/sizeof(uint32_t)))) &= ~pinD;
    else if(out == 1)
        *(((volatile uint32_t*)baseAddress + (pinOffset/sizeof(uint32_t)))) |=  pinD;
    else
        return;
}

void digitalPortWrite(char port, uint32_t data){
    int i = (port == 'F')? 5 : (port == 'E')? 6 : 8, j = 0;
    while(j<i){
        digitalPinWrite(port, j++, data%2);
        data = data >> 1;
    }
}

void portFInit(void){

    SYSCTL_RCGCGPIO_R |= 0x20;
    while((SYSCTL_PRGPIO_R & 0x20) == 0) {}

    GPIO_PORTF_AFSEL_R &= ~0x1f;
    GPIO_PORTF_PCTL_R &= ~0x1f;
    GPIO_PORTF_AMSEL_R &= ~0x1f;
    GPIO_PORTF_DIR_R |= 0xE;
    GPIO_PORTF_DEN_R |= 0x1f;
    GPIO_PORTF_PUR_R &= ~0xE;
    GPIO_PORTF_DATA_R &= ~0x1f;

}

void LED_ON(uint8_t LED){
    GPIO_PORTF_DATA_R |= LED;
}

void LED_OFF(uint8_t LED){
    GPIO_PORTF_DATA_R &= ~LED;
}

uint8_t switch1(void){
    return ((GPIO_PORTF_DATA_R & SW1) >> 4);
}

uint8_t switch2(void){
    return (GPIO_PORTF_DATA_R & SW2);
}
