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

#include "inc/hw_types.h"
#include "inc/hw_sysctl.h"
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


#include "uart4.h"
#include "global.h"
#include "function.h"

unsigned char ucUART4FrameTx[UART4_FRAME_SIZE];

volatile unsigned char ucUART4DelayTx;
volatile unsigned char ucUART4DelayRx;
volatile unsigned char ucUART4DelaySendRequest;
volatile unsigned char ucUART4BufferRx[UART4_FRAME_SIZE];
volatile unsigned char ucUART4CounterRx;

volatile eUartStateHandler eUART4StateRx;
static volatile unsigned char ucUART4CounterTx;
static volatile unsigned char ucUART4RdIndexTx;
unsigned char ucUART4IntervalTx;

void vUART4Config(void)
{
 	// Thiet lap thong so cho Port UART4 - giao tiep voi inverter
	// Toc do baud 11520, 8 bit, 1 stop, no parity
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC); 
	
 	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART4);	
	GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);
	
	GPIOPinConfigure(GPIO_PC4_U4RX);
	GPIOPinConfigure(GPIO_PC5_U4TX);

	HWREG(GPIO_PORTC_BASE + GPIO_O_AMSEL) &= ~0x30;
	
	UARTConfigSetExpClk(UART4_BASE, SysCtlClockGet(), 9600,
                       (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                        UART_CONFIG_PAR_EVEN));
                           	
	#if(DEBUG_VIEW==1)
		#warning "UART4 baurate is 19200, 8bit, 1stop, even parity"
	#endif

	// Enable received interrupt and receive time out interrupt
  IntEnable(INT_UART4_TM4C123);
  UARTIntEnable(UART4_BASE, UART_INT_RX | UART_INT_RT | UART_INT_TX);	// Interrupt receive and  timeout			   
	UARTFIFOLevelSet(UART4_BASE,UART_FIFO_TX2_8,UART_FIFO_RX2_8);
	_dir_off();
	eUART4StateRx=STATE_RX_IDLE;
}

//*-----------------------------------------------------------*/
// Ham xu ly ngat UART1
void vUART4Handler(void)
{
    unsigned char ucData,i;
	unsigned long ulStatus;

	// Doc trang thai tao ngat va xoa de cho ngat moi.
    ulStatus = UARTIntStatus(UART1_BASE, true);
    UARTIntClear(UART1_BASE, ulStatus);
		
	if(ulStatus==UART_INT_TX)
	{
		i=0;
		while((i<8)&(ucUART4CounterTx>0)&(ucUART4RdIndexTx>=16))
		{
			UARTCharPutNonBlocking(UART1_BASE, ucUART4FrameTx[ucUART4RdIndexTx]);
		 	++i;
			--ucUART4CounterTx;
			++ucUART4RdIndexTx;
		}
		ucUART4DelayTx = ucUART4IntervalTx;
	}	
	else if((ulStatus & (UART_INT_TX|UART_INT_RT))!=0)
	{
		while(UARTCharsAvail(UART1_BASE))
		{
			ucUART4DelayRx=UART4_INTERVAL_RX;
			ucData = UARTCharGetNonBlocking(UART1_BASE);
			switch(eUART4StateRx)
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
					ucUART4CounterRx = 0;
					ucUART4BufferRx[ucUART4CounterRx++] = ucData;
					eUART4StateRx = STATE_RX_RECEIVE;
					break;
				}
				case STATE_RX_RECEIVE:
				{
					if(ucUART4CounterRx<UART4_FRAME_SIZE)
					{
						ucUART4BufferRx[ucUART4CounterRx++] = ucData;
					}
					else
					{
						eUART4StateRx = STATE_RX_ERROR;
					}
					break;
				}
			}
		}	
	}
}

/*-----------------------------------------------------------*/
// Ham phat chuoi ky tu
void vUART4PutString(unsigned char *pucStr)
{
	// Gui ky tu cho den het chuoi, khi do noi dung = 0.
	while(*pucStr){UARTCharPut(UART4_BASE, *pucStr++);};
}


// Send message in buffer.
void vUART4Send(unsigned char ucLen)
{
	// Put transmit frame to tx buffer.
	ucUART4CounterTx=ucLen;
	ucUART4RdIndexTx=0;
	_dir_on();
	while((ucUART4RdIndexTx<16)&&(ucUART4CounterTx>0))
	{
		UARTCharPut(UART4_BASE, ucUART4FrameTx[ucUART4RdIndexTx]);
		--ucUART4CounterTx;
		++ucUART4RdIndexTx;
	}

	// Transmit again.	
	ucUART4DelayTx = 40 ; // >=11 character ,baudrate=2500 => 36ms
}

