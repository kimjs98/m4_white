/*
 * motor.c
 *
 *  Created on: 2022. 3. 10.
 *      Author: kimjs
 */

#define	_MOTOR_

#include "device.h"
#include "motor.h"

///////////////////////////////////////////////    motor information   ///////////////////////////////////////////////////

//#define WHEEL_RADIUS		36
//#define Gear_Ratio 			3.35
//#define M_PI				3.141592653589

//#define SAMPLE_FRQ			0.00025			//250us
#define SAMPLE_FRQ_MS			0.25

//PULSE_TO_D = (WHEEL_RADIUS * M_PI) / (encoder_pulse * 4) / geer_ratio
//(36 * M_PI) / 2048 / 3.35
#define PULSE_TO_D				0.016484569660

//PULSE_TO_V = (WHEEL_RADIUS * M_PI) / (encoder_pulse * 4) / geer_ratio / SAMPLE_FRQ
//(36 * M_PI) / 2048 / 3.35 / 0.00025
#define PULSE_TO_V  			65.93827864344


////////////////////////////////////////////       PID information       ///////////////////////////////////////////////////

//#define MAX_PID_OUT			8950.0
//#define MIN_PID_OUT			-8950.0

#define MAX_PID_OUT				5012.0
#define MIN_PID_OUT				-5012.0

#define PWM_CONVERT				0.3333333333333

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#define DOWN_KP				( float32 )( 0.00725 )
#define	DOWN_KP				( float32 )( 0.007 )  // 0.1
//#define	DOWN_KP				( float32 )( 0.0065 )  // 0.2

#define DOWN_KD				( float32 )( 0.005 )	//3.4
//#define DOWN_KD				( float32 )( 0.01 )		//2.4

float32	am_g_motor_step = 0.0;

//float32	am_Rmotor_step = 0.0;
//float32	am_Lmotor_step = 0.0;

/* motor variable struct initialize func */

void init_motor_variable( motor_vari *pm )
{
	memset( ( void * )pm , 0x00 , sizeof( motor_vari ) );

	pm->fp32kp = 0.6; // 0.8
	pm->fp32ki = 0.00002;
	pm->fp32kd = 0.65; // 0.85 
	pm->int32accel = 5;

	/* test */
	pm->fp32user_vel = 0;
	g_flag.start_flag = 1;
}

void timer4_motor_ISR()
{
	// htim->Instance->ARR 		// counter period(auto-reload register) set
	// htim->Instance->psc 		// prescaler set

	//cnt = TIM8->CNT;			// encoder count input
	//TIM8->CNT = 0;			// encoder count clear

#if 1 // motor interrupt

	/* qep value sampling */
	r_motor.u32qep_sample = TIM8->CNT;		// encoder cnt
	l_motor.u32qep_sample = TIM1->CNT;		// encoder cnt

	/* qep reset */
	TIM8->CNT = 0;							// encoder count clear
	TIM1->CNT = 0;							// encoder count clear

	r_motor.int32qep_value = r_motor.u32qep_sample > 1024 ? (int32)( r_motor.u32qep_sample ) - 2049 : (int32)r_motor.u32qep_sample;
	l_motor.int32qep_value = l_motor.u32qep_sample > 1024 ? (int32)( l_motor.u32qep_sample ) - 2049 : (int32)l_motor.u32qep_sample;
	
	/* distance compute */
	r_motor.fp32tick_distance = ( float32 )r_motor.int32qep_value * ( float32 )PULSE_TO_D;
	r_motor.fp32distance_sum += r_motor.fp32tick_distance;
	r_motor.fp32err_distance = r_motor.fp32user_distacne - r_motor.fp32distance_sum;

	l_motor.fp32tick_distance = ( float32 )l_motor.int32qep_value * ( float32 )PULSE_TO_D;
	l_motor.fp32distance_sum += l_motor.fp32tick_distance;
	l_motor.fp32err_distance = l_motor.fp32user_distacne - l_motor.fp32distance_sum;

	/* average velocity compute */
	r_motor.fp32current_vel[ 3 ] = r_motor.fp32current_vel[ 2 ];
	r_motor.fp32current_vel[ 2 ] = r_motor.fp32current_vel[ 1 ];
	r_motor.fp32current_vel[ 1 ] = r_motor.fp32current_vel[ 0 ];
	r_motor.fp32current_vel[ 0 ] = ( float32 )r_motor.int32qep_value * ( float32 )PULSE_TO_V;
	r_motor.fp32cur_vel_avr = ( r_motor.fp32current_vel[ 0 ] + r_motor.fp32current_vel[ 1 ] + r_motor.fp32current_vel[ 2 ] + r_motor.fp32current_vel[ 3 ] ) * 0.25;

	l_motor.fp32current_vel[ 3 ] = l_motor.fp32current_vel[ 2 ];
	l_motor.fp32current_vel[ 2 ] = l_motor.fp32current_vel[ 1 ];
	l_motor.fp32current_vel[ 1 ] = l_motor.fp32current_vel[ 0 ];
	l_motor.fp32current_vel[ 0 ] = ( float32 )l_motor.int32qep_value * ( float32 )PULSE_TO_V;
	l_motor.fp32cur_vel_avr = ( l_motor.fp32current_vel[ 0 ] + l_motor.fp32current_vel[ 1 ] + l_motor.fp32current_vel[ 2 ] + l_motor.fp32current_vel[ 3 ] ) * 0.25;

	/* decelation a point of time flag */
	if( r_motor.u32decel_flag ) //if move_to_move or move_end function called
	{
		if( r_motor.fp32decel_distance >= ( float32 )fabs( ( double )( r_motor.fp32err_distance ) ) )
		{
		
			/*
			if( g_secinfo[ g_int32mark_cnt ].int32dir & STRAIGHT )
			{
				RED_ON;
				BLUE_OFF;
			*/
			r_motor.fp32user_vel = r_motor.fp32decel_vel; //user_vel -> decel_vel
			r_motor.u32decel_flag = 0;

			/* accelation start flag OFF */
			g_flag.speed_up = 0;
			g_flag.speed_up_start = 0;

			//g_err.fp32over_dist = 0.0;
		}
	}
	else if( l_motor.u32decel_flag ) //if move_to_move or move_end function called
	{
		if( l_motor.fp32decel_distance >= ( float32 )fabs( ( double )( l_motor.fp32err_distance ) ) )
		{
		
			/*
			if( g_secinfo[ g_int32mark_cnt ].int32dir & STRAIGHT )
			{
				RED_ON;
				BLUE_OFF;
			*/
			l_motor.fp32user_vel = l_motor.fp32decel_vel; //user_vel -> decel_vel
			l_motor.u32decel_flag = 0;

			/* accelation start flag OFF */
			g_flag.speed_up = 0;
			g_flag.speed_up_start = 0;

			//g_err.fp32over_dist = 0.0;
		}
	}
	else;
	
	r_motor.fp32next_acc = ( float32 )r_motor.int32accel;
	l_motor.fp32next_acc = ( float32 )l_motor.int32accel;

	/* accel & decel compute */
	if( r_motor.fp32user_vel > r_motor.fp32next_vel )
	{
		r_motor.fp32next_vel += ( ( float32 )fabs( ( double )( r_motor.fp32next_acc ) ) * ( float32 )SAMPLE_FRQ_MS );
		if( r_motor.fp32user_vel < r_motor.fp32next_vel )
			r_motor.fp32next_vel = r_motor.fp32user_vel;
	}
	else if( r_motor.fp32user_vel < r_motor.fp32next_vel )
	{
		r_motor.fp32next_vel -= ( ( float32 )fabs( ( double )( r_motor.fp32next_acc ) ) * ( float32 )SAMPLE_FRQ_MS );
		if( r_motor.fp32user_vel > r_motor.fp32next_vel )
			r_motor.fp32next_vel = r_motor.fp32user_vel;
	}
	else;

	if( l_motor.fp32user_vel > l_motor.fp32next_vel )
	{
		l_motor.fp32next_vel += ( ( float32 )fabs( ( double )( l_motor.fp32next_acc ) ) * ( float32 )SAMPLE_FRQ_MS );
		if( l_motor.fp32user_vel < l_motor.fp32next_vel )
			l_motor.fp32next_vel = l_motor.fp32user_vel;
	}
	else if( l_motor.fp32user_vel < l_motor.fp32next_vel )
	{
		l_motor.fp32next_vel -= ( ( float32 )fabs( ( double )( r_motor.fp32next_acc ) ) * ( float32 )SAMPLE_FRQ_MS );
		if( l_motor.fp32user_vel > l_motor.fp32next_vel )
			l_motor.fp32next_vel = l_motor.fp32user_vel;
	}
	else;


	/* motor PID compute */
	r_motor.fp32err_vel_sum -= r_motor.fp32err_vel[ 3 ];
	r_motor.fp32err_vel[ 3 ] = r_motor.fp32err_vel[ 2 ];
	r_motor.fp32err_vel[ 2 ] = r_motor.fp32err_vel[ 1 ];
	r_motor.fp32err_vel[ 1 ] = r_motor.fp32err_vel[ 0 ];
	//r_motor.fp32err_vel[ 0 ] = ( r_motor.fp32next_vel * g_fp32right_handle ) - r_motor.fp32cur_vel_avr;	// g_fp32right_handle -> x
	r_motor.fp32err_vel[ 0 ] = ( r_motor.fp32next_vel ) - r_motor.fp32cur_vel_avr;
	r_motor.fp32err_vel_sum += r_motor.fp32err_vel[ 0 ];

	r_motor.fp32proportion_val = r_motor.fp32kp * r_motor.fp32err_vel[ 0 ];
	r_motor.fp32integral_val = r_motor.fp32ki * r_motor.fp32err_vel_sum;
	r_motor.fp32differential_val = r_motor.fp32kd * ( ( r_motor.fp32err_vel[ 0 ] - r_motor.fp32err_vel[ 3 ] ) + ( ( float32 )3.0 * ( r_motor.fp32err_vel[ 1 ] - r_motor.fp32err_vel[ 2 ] ) ) );
	r_motor.fp32PID_output += r_motor.fp32proportion_val + r_motor.fp32integral_val + r_motor.fp32differential_val;

	
	l_motor.fp32err_vel_sum -= l_motor.fp32err_vel[ 3 ];
	l_motor.fp32err_vel[ 3 ] = l_motor.fp32err_vel[ 2 ];
	l_motor.fp32err_vel[ 2 ] = l_motor.fp32err_vel[ 1 ];
	l_motor.fp32err_vel[ 1 ] = l_motor.fp32err_vel[ 0 ];
	//l_motor.fp32err_vel[ 0 ] = ( l_motor.fp32next_vel * g_fp32right_handle ) - l_motor.fp32cur_vel_avr;	// g_fp32right_handle -> x
	l_motor.fp32err_vel[ 0 ] = ( l_motor.fp32next_vel ) - l_motor.fp32cur_vel_avr;
	l_motor.fp32err_vel_sum += l_motor.fp32err_vel[ 0 ];

	l_motor.fp32proportion_val = l_motor.fp32kp * l_motor.fp32err_vel[ 0 ];
	l_motor.fp32integral_val = l_motor.fp32ki * l_motor.fp32err_vel_sum;
	l_motor.fp32differential_val = l_motor.fp32kd * ( ( l_motor.fp32err_vel[ 0 ] - l_motor.fp32err_vel[ 3 ] ) + ( ( float32 )3.0 * ( l_motor.fp32err_vel[ 1 ] - l_motor.fp32err_vel[ 2 ] ) ) );
	l_motor.fp32PID_output += l_motor.fp32proportion_val + l_motor.fp32integral_val + l_motor.fp32differential_val;

	if( g_flag.start_flag ) 
	{
		/* PID -> PWM */
		if( r_motor.fp32PID_output > 0.0 )
		{
			if( r_motor.fp32PID_output > MAX_PID_OUT )
				r_motor.fp32PID_output = MAX_PID_OUT;

			right_motor_dir_GPIO_Port->BSRR = right_motor_pwm_Pin;  // gpio set;
			TIM3->CCR2 = ( UINT32 )( r_motor.fp32PID_output * PWM_CONVERT );

		}
		else
		{
			if( r_motor.fp32PID_output < MIN_PID_OUT )
				r_motor.fp32PID_output = MIN_PID_OUT;

			right_motor_dir_GPIO_Port->BSRR = (UINT32)right_motor_pwm_Pin << 16U; 	// gpio reset
			TIM3->CCR2 = ( UINT32 )( r_motor.fp32PID_output * PWM_CONVERT * (-1) );
		}

		if( l_motor.fp32PID_output > 0.0 )
		{
			if( l_motor.fp32PID_output > MAX_PID_OUT )
				l_motor.fp32PID_output = MAX_PID_OUT;
			
			left_motor_dir_GPIO_Port->BSRR = (UINT32)left_motor_pwm_Pin << 16U; 	// gpio reset
			TIM3->CCR1 = ( UINT32 )( l_motor.fp32PID_output * PWM_CONVERT * (-1) );
		}
		else
		{
			if( l_motor.fp32PID_output < MIN_PID_OUT )
				l_motor.fp32PID_output = MIN_PID_OUT;

			left_motor_dir_GPIO_Port->BSRR = left_motor_pwm_Pin;  // gpio set;
			TIM3->CCR1 = ( UINT32 )( l_motor.fp32PID_output * PWM_CONVERT );
		}

	}
	else 
	{
		right_motor_dir_GPIO_Port->BSRR = (UINT32)right_motor_pwm_Pin << 16U;	// gpio reset
		left_motor_dir_GPIO_Port->BSRR = (UINT32)left_motor_pwm_Pin << 16U; 	// gpio reset

		//GpioDataRegs.GPBSET.bit.GPIO48 = 1; // left
		//GpioDataRegs.GPBCLEAR.bit.GPIO49 = 1; // right

		/* motor stop */
		TIM3->CCR1 = 0;
		TIM3->CCR2 = 0;
	}
#endif

}
