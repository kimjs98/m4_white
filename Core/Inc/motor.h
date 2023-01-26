//###########################################################################
//
// FILE		: motor.h
//
// TITLE		: m4_white motor header file.
//
// Author	: Kim Jinseong
//
// Company	: Maze & Hz
//
//###########################################################################
// $Release Date: 2023.01.26 $
//##########################################################################


#ifndef __MOTOR_H_
#define __MOTOR_H_

#ifdef	_MOTOR_
	#ifndef _MOTOR_GLOBAL_
		#define _MOTOR_GLOBAL_	
	#endif
#else
	#ifndef _MOTOR_GLOBAL_
		#define _MOTOR_GLOBAL_	extern
	#endif
#endif

_MOTOR_GLOBAL_ void init_motor_variable( motor_vari *pm );
_MOTOR_GLOBAL_ void timer4_motor_ISR();

#endif /* __MOTOR_H_ */
