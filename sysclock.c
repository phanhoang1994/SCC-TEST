//**************************************
//* File: 			sysclock.c
//*	Date: 			10/11/12
//*	Creator:		PhanTrongHieu
//* Last modify:	14/01/13
//* Description:	This file is in CAN communication lift control system project.
//*					The functions in this file representated to display matrix led of ThienNam 
//*					elevator indicator. The hardware was designed by LeDuy(leduy@tne.vn).
//*					The hardware was edited by TrongHieu.
//*					This file is copywritghted by ThienNam Join Stock Company (www.tne.vn).
//* Version: 		V1.0. 
//*************************************
#include <stdint.h>
#include <stdbool.h>

/* Standard includes. */
#include "driverlib/systick.h"
#include "global.h"

extern void vSysTickTimerExpired(void);

void vSysTickHandler(void)
{
	vSysTickTimerExpired();
}

void vSysTickConfig(void)
{
	SysTickPeriodSet((CPU_CLOCK_HZ / TICK_RATE_HZ)-1UL);
	SysTickIntEnable();
}


