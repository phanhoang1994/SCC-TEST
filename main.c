//**************************************
//* File: 			display.c
//*	Date: 			10/11/12
//*	Creator:		TrongHieu(tronghieu@tne.vn)
//* Last modify:	14/01/13
//* Description:	This file is in CAN communication lift control system project.
//*					The functions in this file representated to display matrix led of ThienNam 
//*					elevator indicator. The hardware was designed by LeDuy(leduy@tne.vn).
//*					The hardware was edited by TrongHieu.
//*					This file is copywritghted by ThienNam Join Stock Company (www.tne.vn).
//* Version: 		V1.0. 
//*************************************


// define de su dung chuong trinh trong ROM
#define TARGET_IS_TM4C123_RA1

/* Standard includes. */
#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_gpio.h"
#include "inc/hw_types.h"
#include "inc/hw_can.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_ints.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/systick.h"
#include "driverlib/can.h"
//#include "driverlib/fpu.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/watchdog.h"

#include "can_scc.h"
#include "sysclock.h"
#include "global.h"
#include "function.h"
#include "uart4.h"

void vHardwareConfig(void);
extern void vPoll(void);
extern void vSysTickConfig(void);
extern void vCANConfig(void);
volatile unsigned char ucWDT;
extern void vUART4Config(void);

void vWDTHandler(void)
{ 
	if(ucWDT == 0){ WatchdogIntClear(WATCHDOG0_BASE);}
	ucWDT = 1;
}

int main(void)
{
	vHardwareConfig();
	while(1)
	{ 	
		vPoll();
		ucWDT = 0;
	}
} 

void vWDTConfig(void)
{
   SysCtlPeripheralEnable(SYSCTL_PERIPH_WDOG0);
   IntEnable(INT_WATCHDOG);
   WatchdogReloadSet(WATCHDOG0_BASE, 50000000);
   WatchdogResetEnable(WATCHDOG0_BASE);
   WatchdogEnable(WATCHDOG0_BASE);
}

void vHardwareConfig(void)
{
	#if (LM3S2965_EVB_DEBUG == 1)
		#warning "We are debugging, please to config LM3S2965_EVB_DEBURG = 0 in global.h"
	#endif
	
	/* Set the clocking to run from the PLL at 50 MHz */
  	ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_8MHZ);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB); 	// IN0...IN7
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);	// IN8...IN15

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
		
	// set up outport
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
	HWREG(GPIO_PORTF_BASE + GPIO_O_AFSEL) &= ~0x01;
	HWREG(GPIO_PORTF_BASE + GPIO_O_DEN) |= 0x01;
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;

	GPIOPinTypeGPIOOutput(GPIO_PORTG_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
	GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_6|GPIO_PIN_7);
	GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_3);
	
	// set up inport
	// Enable the peripherals used by the application.
	HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= 0x80;
	HWREG(GPIO_PORTD_BASE + GPIO_O_AFSEL) &= ~0x80;
	HWREG(GPIO_PORTD_BASE + GPIO_O_DEN) |= 0x80;
	HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0;
	
	GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, 0xFF);
	GPIOPadConfigSet(GPIO_PORTB_BASE, 0xFF,	GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, 0xFF);
	GPIOPadConfigSet(GPIO_PORTD_BASE, 0xFF,	GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

	_buzzer_off();

	vCANConfig();
	vUART4Config();
	vSysTickConfig();
	SysTickEnable();
	vWDTConfig();
	IntMasterEnable();
	
} 
