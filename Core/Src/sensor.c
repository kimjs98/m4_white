//###########################################################################
//
// FILE		: sensor.c
//
// TITLE		: m4_white sensor source file.
//
// Author	: Lee Jinho, Kim Jinseong
//
// Company	: Maze & Hz
//
//###########################################################################
// $Release Date: 2023.01.27 $
//###########################################################################

#include "device.h"
#include "sensor.h"

#define ADC_SET_SQR1(_ADCNB_) 					(ADC_SQR1_RK(_ADCNB_, 16)|\
												ADC_SQR1_RK(_ADCNB_, 15) |\
												ADC_SQR1_RK(_ADCNB_, 14) |\
												ADC_SQR1_RK(_ADCNB_, 13) )

#define ADC_SET_SQR2(_ADCNB1_, _ADCNB2_)		(ADC_SQR2_RK(_ADCNB1_, 12)|\
												ADC_SQR2_RK(_ADCNB1_, 11) |\
												ADC_SQR2_RK(_ADCNB1_, 10) |\
												ADC_SQR2_RK(_ADCNB1_, 9) |\
												ADC_SQR2_RK(_ADCNB2_, 8) |\
												ADC_SQR2_RK(_ADCNB2_, 7))
							
#define ADC_SET_SQR3(_ADCNB_) 					(ADC_SQR3_RK(_ADCNB_, 6)|\
												ADC_SQR3_RK(_ADCNB_, 5) |\
												ADC_SQR3_RK(_ADCNB_, 4) |\
												ADC_SQR3_RK(_ADCNB_, 3) |\
												ADC_SQR3_RK(_ADCNB_, 2) |\
												ADC_SQR3_RK(_ADCNB_, 1))

#if 1
#define ADC_1	0x0
#define ADC_2	0x1
#define ADC_3	0x2
#define ADC_4	0x3
#define ADC_5	0x4
#define ADC_6	0x5
#define ADC_7	0x6
#define ADC_8	0x7
#define ADC_9	0x8
#define ADC_10	0x9
#define ADC_11	0xa
#define ADC_12	0xb
#define ADC_13	0xc
#define ADC_14	0xd
#define ADC_15	0xe
#define ADC_16	0xf
#endif

#define SEN_ON 	0x1L
#define SEN_OFF	0x10000L
//PD08 ~ PD15

typedef volatile enum
{
	#if 1
	SEN0 = 8,
	SEN1 ,
	SEN2 ,
	SEN3 ,
	SEN4 ,
	SEN5 ,
	SEN6 ,
	SEN7 ,
	SEN_END = 8,
	
	SQR = 3,
	SQR_1 = 1,
	SQR_2= 2,
	SQR_3= 3,
	POS = 3,
	ADC_NUM =16
	#endif
}sensor_num;

volatile uint32 sen_shoot_arr[ SEN_END ] = 
{
	SEN0, SEN1, SEN2, SEN3, SEN4, SEN5, SEN6, SEN7
};

volatile uint32 sen_adc_seq[ ADC_NUM ] = 
{
	ADC_1 , ADC_2 ,  ADC_3 ,   ADC_4 ,   ADC_5 ,   ADC_6 ,   ADC_7 ,  ADC_8,
	ADC_9 , ADC_10 ,  ADC_11,  ADC_12 ,  ADC_13 ,  ADC_14 ,  ADC_15,  ADC_16
};

void timer9_sensor_ISR() 
{
	HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_8);	// DEBUG
	
	g_int32_sen_cnt++;
	if(g_int32_sen_cnt >= SEN_END)
	{		
		g_int32_sen_cnt = 0;
		HAL_TIM_Base_Stop_IT(&htim9);	// sensor interrupt stop 
	}
}