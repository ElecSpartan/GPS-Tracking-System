#include "tm4c123gh6pm.h"

void portF_init(void);

int main(void){
	portF_init();
	while(1){
		
	}
}

void portF_init(void){
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;// Enable port F clock
	while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R5) == 0){};
	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;		// Unlock PortF PF0
	GPIO_PORTF_CR_R = 0x0E;					// Allow changes to PF1-3
	GPIO_PORTF_DIR_R = 0x0E;				// PF3,PF2,PF1 output
	GPIO_PORTF_AFSEL_R = 0x00;				// No alternate function
	GPIO_PORTF_PCTL_R = 0x00000000;			// GPIO clear bit PCTL
	GPIO_PORTF_DEN_R = 0x0E;				// Enable digital pins PF1-PF3
	GPIO_PORTF_AMSEL_R = 0x00;				// Disable analog function
}