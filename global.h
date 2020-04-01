#ifndef __GLOBAL_H__
#define __GLOBAL_H__

//----------------------------------------------
// Cac khai bao thong so
//----------------------------------------------
#define TR_UPDATE	100
#define TR_INP		25

#define TR_GONG		1000		// 1s
//#define TR_FAN		10
#define TR_DRC		500			// 500 ms
#define TR_RDC		20000		// 20 s
#define TR_RDO		20000		// 20s
#define TR_DCD		1000		// 1s
#define TR_DOD		3000		// 3s
#define TR_GOL		1000		// 1s
#define TR_GCL		1000		// 1s

#define TR_RESET	3000		//3000 ms

#define ID_SOC		0
#define ID_SCC_1	1
#define ID_SCC_2	2

#define IS_CAN_BUFFER		(1)

#define CPU_CLOCK_HZ		50000000
#define TICK_RATE_HZ		1000
//----------------------------------------------
// Cac khai bao function
//----------------------------------------------
#define TRUE	1
#define FALSE	0

#define True	1
#define False	0

#define true	1
#define false	0

typedef union
{
	unsigned long LONG;
	unsigned int INT[2];
	unsigned char BYTE[4];
} DWORD;

typedef union
{
	unsigned int INT;
	unsigned char BYTE[2];
} WORD;

typedef unsigned char boolean;

#define _clear(x,y)  	x &= ~(1UL<<y) 	
#define _set(x,y)		x |= (1UL<<y)
#define _toggle(x,y)		x ^= (1UL<<y)
#define _isset(x,y)		((x & (1UL<<y)) != 0)
#define _isclear(x,y)	((x & (1UL<<y)) == 0)

#endif
