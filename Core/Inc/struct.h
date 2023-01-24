/*
 * struct.h
 *
 *  Created on: Mar 10, 2022
 *      Author: kimjs
 */

#ifndef __STRUCT_H_
#define __STRUCT_H_


#ifdef __STRUCT__

#undef __STRUCT__
#define __STRUCT_EXT__

#else
#define __STRUCT_EXT__	extern
#endif



typedef volatile struct bit_field_flag
{

	UINT32	motor_start:1;
	UINT32	motor_ISR_flag:1;
	UINT32	move_state:1;
	UINT32	start_flag:1;
	UINT32	cross_flag:1;
	UINT32	speed_up_flag:1;
	UINT32	debug_flag:1;
	UINT32	fast_flag:1;
	UINT32	lineout_flag:1;
	UINT32	err:1;
	UINT32	speed_up_start:1;
	UINT32	speed_up:1;
	UINT32	straight_run:1;


}bit_field_flag_t;

__STRUCT_EXT__ bit_field_flag_t	g_flag;


typedef volatile struct motor_variable
{
	UINT32		u32qep_sample;
	UINT32		u32decel_flag;

	INT32		int32qep_value;
	INT32		int32accel;

	float32		fp32next_acc;

	float32		fp32distance_sum;
	float32		fp32err_distance;
	float32		fp32user_distacne;

	float32		fp32user_vel;
	float32		fp32next_vel;

	float32		fp32current_vel[ 4 ];
	float32		fp32cur_vel_avr;

	float32		fp32err_vel[ 4 ];
	float32		fp32err_vel_sum;

	float32		fp32PID_output;
	float32		fp32kp;
	float32		fp32ki;
	float32		fp32kd;
	float32		fp32proportion_val;
	float32		fp32differential_val;
	float32		fp32integral_val;

	float32		fp32decel_distance;
	float32		fp32decel_vel;

	float32		fp32gone_distance;
	float32		fp32tick_distance;

}motor_vari;

__STRUCT_EXT__ motor_vari	r_motor;
__STRUCT_EXT__ motor_vari	l_motor;


#endif /* INC_STRUCT_H_ */
