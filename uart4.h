#ifndef __UART1_H__
#define __UART1_H__

#define UART4_FRAME_SIZE 								255
#define UART4_INTERVAL_TX               25
#define UART4_INTERVAL_RX               25
#define UART4_INTERVAL_SEND_REQ         100

typedef enum
{
    STATE_RX_INIT,          
    STATE_RX_ERROR,         
    STATE_RX_IDLE,          
    STATE_RX_RECEIVE        
} eUartStateHandler;

extern void vUART4Config(void);
extern void vUART4Handler(void);
extern void vUART4PutString(unsigned char *pucStr);
extern void vUART4Send(unsigned char ucLen);
#endif
