#ifndef __CAN_SCC_H__
#define __CAN_SCC_H__

#define ID_SOC					0
#define ID_SCC					1

#define MSGOBJ_ID_STATUS 		1
#define MSGOBJ_ID_IN_SCC		2
#define MSGOBJ_ID_OUT_SCC		3
#define MSGOBJ_ID_IN_SCE      	4
#define MSGOBJ_ID_OUT_SCE       5
#define MSGOBJ_ID_IN_SHC    	6
#define MSGOBJ_ID_OUT_SHC 		7
#define MSGOBJ_ID_IN_X1	    	8
#define MSGOBJ_ID_OUT_X1 		9
#define MSGOBJ_ID_CLR_BTC		10
#define MSGOBJ_ID_CLR_BTH		11

#define MSGOBJ_NUM_STATUS   	1
#define MSGOBJ0_NUM_IN_SCC     	2
#define MSGOBJ0_NUM_OUT_SCC     3
#define MSGOBJ0_NUM_IN_SCE	    4
#define MSGOBJ0_NUM_OUT_SCE	    5
#define MSGOBJ0_NUM_IN_SHC	    6
#define MSGOBJ0_NUM_OUT_SHC	    7
#define MSGOBJ0_NUM_IN_X1	    8
#define MSGOBJ0_NUM_OUT_X1	    9
#define MSGOBJ1_NUM_IN_SCE	    10
#define MSGOBJ1_NUM_OUT_SCE 	11
#define MSGOBJ1_NUM_IN_SHC	    12
#define MSGOBJ1_NUM_OUT_SHC	    13
#define MSGOBJ1_NUM_IN_X1	    14
#define MSGOBJ1_NUM_OUT_X1	    15
#define MSGOBJ0_NUM_CLR_BTC		16
#define MSGOBJ1_NUM_CLR_BTC		17
#define MSGOBJ0_NUM_CLR_BTH		18
#define MSGOBJ1_NUM_CLR_BTH		19

extern unsigned char ucCANDispStatus[8];
extern unsigned char ucCANClearBTC[8];
extern unsigned char ucCANInSCE[8];
extern unsigned char ucCANOutSCE[8];

extern unsigned char ucCAN0InSCC[8];
extern unsigned char ucCAN0OutSCC[8];

#endif
