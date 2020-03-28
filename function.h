#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#define STATE_DR_IDLE	0
#define STATE_CD_START	1
#define STATE_CD_CMD	2
#define STATE_CD_DELAY	3
#define STATE_OD_START	4
#define STATE_OD_CMD	5
#define STATE_OD_DELAY	6 

#define RUN	0
#define LU	1
#define LD	2
#define BTS	3
#define DRZ	4

// Inport
#define PIN_OVL	0
#define PIN_HLD	1
#define PIN_SP1	2
#define PIN_SG1	3
#define PIN_DO2	4
#define PIN_DC2	5
#define PIN_DO1	6
#define PIN_DC1	7
#define PIN_GC2	8
#define PIN_GO2	9
#define PIN_GC1	10
#define PIN_GO1	11
#define PIN_SP2	12
#define PIN_SG2	13
#define PIN_X1	14
#define PIN_X2 	15

//Outport
#define SCC_V1_2	0

#define PIN_GONG	0
#define PIN_FAN		1
#define PIN_LIGHT	2
#define PIN_OVLO	3
#define PIN_RDC1	4
#define PIN_RDO1	5
#define PIN_RDC2	6
#define PIN_RDO2	7
#define PIN_Y1		8
#define PIN_Y2		9
#define PIN_Y3		10	
#define PIN_Y4		11
#define PIN_Y5		12
#define PIN_Y6		13
#define PIN_Y7		14
#define PIN_Y8		15

#define _ledrun_on()		GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_3,GPIO_PIN_3)
#define _ledrun_off()	GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_3,0)

#define _lederr_on()		GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_4,GPIO_PIN_4)
#define _lederr_off()	GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_4,0)

#define _buzzer_on()		GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_7,GPIO_PIN_7)
#define _buzzer_off()	GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_7,0)

#define _dir_on()		GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,GPIO_PIN_6)
#define _dir_off()		GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,0)

#if(SCC_V1_2 == 0)
	#define _Q0_on() GPIOPinWrite(GPIO_PORTG_BASE,GPIO_PIN_0,GPIO_PIN_0)
	#define _Q1_on() GPIOPinWrite(GPIO_PORTG_BASE,GPIO_PIN_1,GPIO_PIN_1)
	#define _Q2_on() GPIOPinWrite(GPIO_PORTG_BASE,GPIO_PIN_2,GPIO_PIN_2)
	#define _Q3_on() GPIOPinWrite(GPIO_PORTG_BASE,GPIO_PIN_3,GPIO_PIN_3)
	#define _Q4_on() GPIOPinWrite(GPIO_PORTG_BASE,GPIO_PIN_4,GPIO_PIN_4)
	#define _Q5_on() GPIOPinWrite(GPIO_PORTG_BASE,GPIO_PIN_5,GPIO_PIN_5)
	#define _Q6_on() GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_0,GPIO_PIN_0)
	#define _Q7_on() GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,GPIO_PIN_1)
	#define _Q8_on() GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,GPIO_PIN_2)
	#define _Q9_on() GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,GPIO_PIN_3)
	#define _Q10_on() GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_2,GPIO_PIN_2)
	#define _Q11_on() GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3,GPIO_PIN_3)
	#define _Q12_on() GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,GPIO_PIN_4)
	#define _Q13_on() GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_5,GPIO_PIN_5)
	#define _Q14_on() GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_6,GPIO_PIN_6)
	#define _Q15_on() GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_7,GPIO_PIN_7)

	#define _Q0_off() GPIOPinWrite(GPIO_PORTG_BASE,GPIO_PIN_0,0)
	#define _Q1_off() GPIOPinWrite(GPIO_PORTG_BASE,GPIO_PIN_1,0)
	#define _Q2_off() GPIOPinWrite(GPIO_PORTG_BASE,GPIO_PIN_2,0)
	#define _Q3_off() GPIOPinWrite(GPIO_PORTG_BASE,GPIO_PIN_3,0)
	#define _Q4_off() GPIOPinWrite(GPIO_PORTG_BASE,GPIO_PIN_4,0)
	#define _Q5_off() GPIOPinWrite(GPIO_PORTG_BASE,GPIO_PIN_5,0)
	#define _Q6_off() GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_0,0)
	#define _Q7_off() GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,0)
	#define _Q8_off() GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,0)
	#define _Q9_off() GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,0)
	#define _Q10_off() GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_2,0)
	#define _Q11_off() GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3,0)
	#define _Q12_off() GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,0)
	#define _Q13_off() GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_5,0)
	#define _Q14_off() GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_6,0)
	#define _Q15_off() GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_7,0)
#else
	#define _Q0_on() GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,GPIO_PIN_2)
	#define _Q1_on() GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,GPIO_PIN_3)
	#define _Q2_on() GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_2,GPIO_PIN_2)
	#define _Q3_on() GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3,GPIO_PIN_3)
	#define _Q4_on() GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,GPIO_PIN_4)
	#define _Q5_on() GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_5,GPIO_PIN_5)
	#define _Q6_on() GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_6,GPIO_PIN_6)
	#define _Q7_on() GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_7,GPIO_PIN_7)
	#define _Q8_on() GPIOPinWrite(GPIO_PORTG_BASE,GPIO_PIN_0,GPIO_PIN_0)
	#define _Q9_on() GPIOPinWrite(GPIO_PORTG_BASE,GPIO_PIN_1,GPIO_PIN_1)
	#define _Q10_on() GPIOPinWrite(GPIO_PORTG_BASE,GPIO_PIN_2,GPIO_PIN_2)
	#define _Q11_on() GPIOPinWrite(GPIO_PORTG_BASE,GPIO_PIN_3,GPIO_PIN_3)
	#define _Q12_on() GPIOPinWrite(GPIO_PORTG_BASE,GPIO_PIN_4,GPIO_PIN_4)
	#define _Q13_on() GPIOPinWrite(GPIO_PORTG_BASE,GPIO_PIN_5,GPIO_PIN_5)
	#define _Q14_on() GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_0,GPIO_PIN_0)
	#define _Q15_on() GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,GPIO_PIN_1)
	
	#define _Q0_off() GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,0)
	#define _Q1_off() GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,0)
	#define _Q2_off() GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_2,0)
	#define _Q3_off() GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3,0)
	#define _Q4_off() GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,0)
	#define _Q5_off() GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_5,0)
	#define _Q6_off() GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_6,0)
	#define _Q7_off() GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_7,0)
	#define _Q8_off() GPIOPinWrite(GPIO_PORTG_BASE,GPIO_PIN_0,0)
	#define _Q9_off() GPIOPinWrite(GPIO_PORTG_BASE,GPIO_PIN_1,0)
	#define _Q10_off() GPIOPinWrite(GPIO_PORTG_BASE,GPIO_PIN_2,0)
	#define _Q11_off() GPIOPinWrite(GPIO_PORTG_BASE,GPIO_PIN_3,0)
	#define _Q12_off() GPIOPinWrite(GPIO_PORTG_BASE,GPIO_PIN_4,0)
	#define _Q13_off() GPIOPinWrite(GPIO_PORTG_BASE,GPIO_PIN_5,0)
	#define _Q14_off() GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_0,0)
	#define _Q15_off() GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,0)
#endif
#endif
