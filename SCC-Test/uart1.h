#ifndef __UART1_H__
#define __UART1_H__

#define UART1_FRAME_SIZE 	255
#define UART1_INTERVAL_TX               25
#define UART1_INTERVAL_RX               25
#define UART1_INTERVAL_SEND_REQ         100

typedef enum
{
    STATE_RX_INIT,          
    STATE_RX_ERROR,         
    STATE_RX_IDLE,          
    STATE_RX_RECEIVE        
} eUartStateHandler;

extern void vUART1Config(void);
extern void vUART1Handler(void);
extern void vUART1PutString(unsigned char *pucStr);
extern void vUART1Send(unsigned char ucLen);
#endif
