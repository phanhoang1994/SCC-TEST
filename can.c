#include <stdint.h>
#include <stdbool.h>

//#define PART_TM4C123AE6PM

#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "inc/hw_can.h"

#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/can.h"

#include "global.h"
#include "can_scc.h"
#include "function.h"

#include "driverlib/pin_map.h"
#include "driverlib/rom.h"

tCANMsgObject xMsgObject0InSCE;
tCANMsgObject xMsgObject1InSCE;
unsigned char ucCAN0InSCE[8];
unsigned char ucCAN1InSCE[8];

volatile unsigned char ucCANBusoff;
extern unsigned long ulInport;

void vCAN0Handler(void)
{
	unsigned long ulStatus, ulCtrl;
	
	ulStatus = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);
	ulCtrl = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
	if(ulCtrl & CAN_STATUS_BUS_OFF){ ucCANBusoff = 1;}

	CANIntClear(CAN0_BASE, ulStatus);
}

void vCAN1Handler(void)
{
 	unsigned long ulStatus, ulCtrl;

	ulStatus = CANIntStatus(CAN1_BASE, CAN_INT_STS_CAUSE);
	switch(ulStatus)
	{
		case MSGOBJ1_NUM_IN_SCE:
		{
	 	 	CANMessageGet(CAN1_BASE, MSGOBJ1_NUM_IN_SCE, &xMsgObject1InSCE, 1);	 	 	
			break;
		}
		default:
		{
			ulCtrl = CANStatusGet(CAN1_BASE, CAN_STS_CONTROL);
			if(ulCtrl & CAN_STATUS_BUS_OFF){ ucCANBusoff = 1;}
			break;
		}
	}
	
	CANIntClear(CAN1_BASE, ulStatus);
}

void CANConfigureNetwork(void)
{
	//------------------------------------------------------------
	// CAN0
	//------------------------------------------------------------
	// DataInSCE
	xMsgObject0InSCE.ui32MsgID = MSGOBJ_ID_IN_SCE;
	xMsgObject0InSCE.ui32MsgIDMask = 0;
	xMsgObject0InSCE.ui32Flags = 0;
	xMsgObject0InSCE.ui32MsgLen = 8;
	xMsgObject0InSCE.pui8MsgData = ucCAN0InSCE;
		
	//------------------------------------------------------------
	// CAN1
	//------------------------------------------------------------
	// DataInSCE
	xMsgObject1InSCE.ui32MsgID = MSGOBJ_ID_IN_SCE;
	xMsgObject1InSCE.ui32MsgIDMask = 0xFFFFFFFF;
	xMsgObject1InSCE.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
	xMsgObject1InSCE.ui32MsgLen = 8;
	xMsgObject1InSCE.pui8MsgData = ucCAN1InSCE;
	CANMessageSet(CAN1_BASE, MSGOBJ1_NUM_IN_SCE, &xMsgObject1InSCE, MSG_OBJ_TYPE_RX);	
}
 
void vCANConfig(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	
	GPIOPinConfigure(GPIO_PE4_CAN0RX);
	GPIOPinConfigure(GPIO_PE5_CAN0TX);
	GPIOPinTypeCAN(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
	CANInit(CAN0_BASE);

	CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 100000);
	CANEnable(CAN0_BASE);
	CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR);

	//CAN1
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	GPIOPinConfigure(GPIO_PA0_CAN1RX);
	GPIOPinConfigure(GPIO_PA1_CAN1TX); 
	GPIOPinTypeCAN(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN1);
	CANInit(CAN1_BASE);

	CANBitRateSet(CAN1_BASE, SysCtlClockGet(), 100000);
	CANEnable(CAN1_BASE);
	CANIntEnable(CAN1_BASE, CAN_INT_MASTER | CAN_INT_ERROR);

	CANConfigureNetwork();
	ucCANBusoff = 0;
	
	IntEnable(INT_CAN0_TM4C123);
 	IntEnable(INT_CAN1_TM4C123);
}

void vCANSend(void)
{
	unsigned long *pulData;
		
	pulData = (unsigned long *)ucCAN0InSCE;
	*pulData = ulInport;
	CANMessageSet(CAN0_BASE, MSGOBJ0_NUM_IN_SCE, &xMsgObject0InSCE, MSG_OBJ_TYPE_TX);
}

