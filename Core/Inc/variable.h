//###########################################################################
//
// FILE		: variable.h
//
// TITLE	: variable.h file.
//
// Author	: Lee Jin Ho
//
// Company	: Maze & Hz
//
//###########################################################################
// $Release Date: 2022.08.26 $
//###########################################################################


#ifdef _MAIN_
	#ifndef __VARIABLE_EXT__
		#define __VARIABLE_EXT__
	#endif
#else
	#ifndef __VARIABLE_EXT__
		#define __VARIABLE_EXT__	extern
	#endif
#endif	

#define SENSOR_TIMER_ENABLE		do{	HAL_TIM_Base_Start_IT(&htim9);	}while(0);
#define SENSOR_TIMER_DISABLE	do{	HAL_TIM_Base_Stop_IT(&htim9);	}while(0);

#define MOTOR_TIMER_ENABLE		do{	HAL_TIM_Base_Start_IT(&htim4);	}while(0);
#define MOTOR_TIMER_DISABLE		do{	HAL_TIM_Base_Stop_IT(&htim4);	}while(0);

#define PRINT TxPrintf("Flow\n");

__VARIABLE_EXT__ int32	flag;
__VARIABLE_EXT__ int32	g_int32_sen_cnt;

__VARIABLE_EXT__ Uint32 g_sen[16];

