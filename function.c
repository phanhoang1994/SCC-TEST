#include <stdint.h>
#include <stdbool.h>

/* Standard includes. */
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#include "global.h"
#include "can_scc.h"
#include "function.h"
#include "uart4.h"

#define SAMPLE			4
extern unsigned char ucUART4FrameTx[UART4_FRAME_SIZE];

unsigned long ulSample[SAMPLE];
unsigned char ucSampleIndex;

unsigned long ulInport;
unsigned long ulPreInp;
unsigned long ulOutport;

unsigned long ulTimerCAN0Tx;
unsigned long ulTimerInport;

volatile unsigned char ucOVOut;

volatile unsigned long ulTimer_buzzer;
volatile unsigned long ulTimer_ledrun;
volatile unsigned char uc_ledrunStatus;

extern volatile unsigned char ucCANBusoff;
extern unsigned char ucCAN1InSCE[];

extern void vCANSend(void);
extern void vCANConfig(void);

void vInput(void)
{
	unsigned long result, all_or=0, all_and=0;
	unsigned char i;
	
	//I0..I7	
	ulSample[ucSampleIndex] = (unsigned long)GPIOPinRead(GPIO_PORTD_BASE, 0xFF) << 8;
	//I8..I15
	ulSample[ucSampleIndex] |= (unsigned long)GPIOPinRead(GPIO_PORTB_BASE, 0xFF);
	ulSample[ucSampleIndex] &= 0x0000FFFF;
	
	all_or = ulSample[0];
	all_and = all_or;
	for(i=1;i<SAMPLE;i++)
	{
		all_or |= ulSample[i];
		all_and &= ulSample[i];
	}

	result = ~ulInport;
	result &= 0x0000FFFF;
	
	result &= all_or;
	result |= all_and;
	
	ulInport = ~result;
	ulInport &= 0x0000FFFF;
	
	if(++ucSampleIndex>=SAMPLE) ucSampleIndex=0;
}

void vOutput(void)
{		
	if(ulTimer_ledrun == 0)
	{ 
		if(uc_ledrunStatus > 0)
		{
			_ledrun_on();
			uc_ledrunStatus = 0;
		}
		else
		{
			_ledrun_off();
			uc_ledrunStatus = 1;
		}
		ulTimer_ledrun = 1000;
	}
	
	if(ulTimer_buzzer == 0)
	{
		ulTimer_buzzer = 800;
		if(ucOVOut == 1){ ucOVOut = 0;} else {ucOVOut = 1;}
	}

	if(_isset(ulOutport, PIN_GONG)){ _Q0_on();}else{ _Q0_off();};
	if(_isset(ulOutport, PIN_FAN)){ _Q1_on();}else{ _Q1_off();};
	if(_isset(ulOutport, PIN_LIGHT)){ _Q2_on();}else{ _Q2_off();};
	if(_isset(ulOutport, PIN_OVLO)){ _Q3_on(); if(ucOVOut == 1){ _buzzer_on();} else { _buzzer_off();}}else{ _Q3_off(); _buzzer_off();}
	if(_isset(ulOutport, PIN_RDC1)){ _Q4_on();} else { _Q4_off();}
	if(_isset(ulOutport, PIN_RDO1)){ _Q5_on();} else { _Q5_off();}
	if(_isset(ulOutport, PIN_RDC2)){ _Q6_on();} else { _Q6_off();};	
	if(_isset(ulOutport, PIN_RDO2)){ _Q7_on();} else { _Q7_off();};
	if(_isset(ulOutport, PIN_Y1)){ _Q8_on();}else{ _Q8_off();};
	if(_isset(ulOutport, PIN_Y2)){ _Q9_on();}else{ _Q9_off();};
	if(_isset(ulOutport, PIN_Y3)){ _Q10_on();}else{ _Q10_off();};
	if(_isset(ulOutport, PIN_Y4)){ _Q11_on();}else{ _Q11_off();};
	if(_isset(ulOutport, PIN_Y5)){ _Q12_on();}else{ _Q12_off();};
	if(_isset(ulOutport, PIN_Y6)){ _Q13_on();}else{ _Q13_off();};
	if(_isset(ulOutport, PIN_Y7)){ _Q14_on();}else{ _Q14_off();};
	if(_isset(ulOutport, PIN_Y8)){ _Q15_on();}else{ _Q15_off();};
}

void vPoll(void)
{
 	unsigned long *pulData;
 	
 	if(ucCANBusoff == 1)
 	{ 
		SysCtlPeripheralReset(SYSCTL_PERIPH_CAN0);
		SysCtlPeripheralReset(SYSCTL_PERIPH_CAN1);
	 	vCANConfig(); 
	 	ucCANBusoff = 0;
 	}
 	
	if(ulTimerInport == 0)
	{ 
		vInput();		
		if(ulInport != ulPreInp){ ulPreInp = ulInport; ulTimerCAN0Tx = 0;}
		ulTimerInport = TR_INP;
	}
	
	pulData = (unsigned long *)ucCAN1InSCE;
	ulOutport = *pulData;
	vOutput();
	if(ulTimerCAN0Tx == 0){ vCANSend(); ulTimerCAN0Tx = TR_UPDATE;}	
}

void vSysTickTimerExpired(void)
{ 
	if(ulTimerCAN0Tx > 0){ --ulTimerCAN0Tx;}
	if(ulTimerInport > 0){ --ulTimerInport;}
	if(ulTimer_ledrun > 0){ --ulTimer_ledrun;}
	if(ulTimer_buzzer > 0){ --ulTimer_buzzer;}
}



