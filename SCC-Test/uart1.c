/*
* Filename.......: UART1.c
*
* Created by.....: Phan Trong Hieu<tronghieu@ecoh.vn>
* Description....: Functions is used to control UART1 of LM3S2965.
* Licence........: This file is property of ecoh.vn
* Creation Date..: 06-12-2009
* Last change....: 11-04-2013
* This File is changed to used for SOC210 project of ThienNam elevator JSC. 
*/

#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "inc/hw_uart.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"

#include "uart1.h"
#include "global.h"
#include "event.h"
#include "function.h"

unsigned char ucUART1FrameTx[UART1_FRAME_SIZE];

volatile unsigned char ucUART1DelayTx;
volatile unsigned char ucUART1DelayRx;
volatile unsigned char ucUART1DelaySendRequest;
volatile unsigned char ucUART1BufferRx[UART1_FRAME_SIZE];
volatile unsigned char ucUART1CounterRx;

volatile eUartStateHandler eUART1StateRx;
static volatile unsigned char ucUART1CounterTx;
static volatile unsigned char ucUART1RdIndexTx;
unsigned char ucUART1IntervalTx;

void vUART1Config(void)
{
	// Enable the peripherals used by the application.
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_6);
	GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_PIN_6);
    	
	// Thiet lap thong so cho Port UART1 - giao tiep voi module GSM-SIM900
	// Toc do baud 11520, 8 bit, 1 stop, no parity
   	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC); 
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);	
	GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);

	UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 19200,
                       (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                        UART_CONFIG_PAR_EVEN));
	#if(DEBUG_VIEW==1)
		#warning "UART1 baurate is 19200, 8bit, 1stop, even parity"
	#endif

	// Enable received interrupt and receive time out interrupt
    IntEnable(INT_UART1_TM4C123);
    UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT | UART_INT_TX);	// Interrupt receive and  timeout			   
	UARTFIFOLevelSet(UART1_BASE,UART_FIFO_TX2_8,UART_FIFO_RX2_8);
	ucUART1DelaySendRequest = UART1_INTERVAL_SEND_REQ;
}

//*-----------------------------------------------------------*/
// Ham xu ly ngat UART1
void vUART1Handler(void)
{
    unsigned char ucData,i;
	unsigned long ulStatus;

	// Doc trang thai tao ngat va xoa de cho ngat moi.
    ulStatus = UARTIntStatus(UART1_BASE, true);
    UARTIntClear(UART1_BASE, ulStatus);
		
	if(ulStatus==UART_INT_TX)
	{
		i=0;
		while((i<8)&(ucUART1CounterTx>0)&(ucUART1RdIndexTx>=16))
		{
			UARTCharPutNonBlocking(UART1_BASE, ucUART1FrameTx[ucUART1RdIndexTx]);
		 	++i;
			--ucUART1CounterTx;
			++ucUART1RdIndexTx;
		}
		ucUART1DelayTx = ucUART1IntervalTx;
	}	
	else if((ulStatus & (UART_INT_TX|UART_INT_RT))!=0)
	{
		while(UARTCharsAvail(UART1_BASE))
		{
			ucUART1DelayRx=UART1_INTERVAL_RX;
			ucData = UARTCharGetNonBlocking(UART1_BASE);
			switch(eUART1StateRx)
			{
				case STATE_RX_INIT:
				{

					break;
				}
				case STATE_RX_ERROR:
				{

					break;
				}		
				case STATE_RX_IDLE:
				{
					ucUART1CounterRx = 0;
					ucUART1BufferRx[ucUART1CounterRx++] = ucData;
					eUART1StateRx = STATE_RX_RECEIVE;
					break;
				}
				case STATE_RX_RECEIVE:
				{
					if(ucUART1CounterRx<UART1_FRAME_SIZE)
					{
						ucUART1BufferRx[ucUART1CounterRx++] = ucData;
					}
					else
					{
						eUART1StateRx = STATE_RX_ERROR;
					}
					break;
				}
			}
		}	
	}
}

/*-----------------------------------------------------------*/
// Ham phat chuoi ky tu
void vUART1PutString(unsigned char *pucStr)
{
	// Gui ky tu cho den het chuoi, khi do noi dung = 0.
	while(*pucStr){UARTCharPut(UART1_BASE, *pucStr++);};
}


// Send message in buffer.
void vUART1Send(unsigned char ucLen)
{
	// Put transmit frame to tx buffer.
	ucUART1CounterTx=ucLen;
	ucUART1RdIndexTx=0;
	DIR_ON();
	while((ucUART1RdIndexTx<16)&(ucUART1CounterTx>0))
	{
		UARTCharPutNonBlocking(UART1_BASE, ucUART1FrameTx[ucUART1RdIndexTx]);
		--ucUART1CounterTx;
		++ucUART1RdIndexTx;
	}

	// Transmit again.	
	ucUART1DelayTx = ucUART1IntervalTx; // >=11 character ,baudrate=2500 => 36ms
	ucUART1DelaySendRequest = UART1_INTERVAL_SEND_REQ;
}

