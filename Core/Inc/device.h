#ifndef __DEVICE_H
#define __DEVICE_H

#ifndef STM32F4xx_DATA_TYPES
#define STM32F4xx_DATA_TYPES

typedef unsigned char   BOOL;
typedef unsigned char   BYTE;

typedef int             INT32;
typedef unsigned int    UINT32;
typedef int             int32;
typedef unsigned int    uint32;
typedef unsigned int    Uint32;


typedef float           float32;
typedef long double     float64;

#define UP		3
#define FALL	2
#define ON		1
#define ON_L	1L
#define OFF		0
#define TRUE 	1
#define FALSE 	0
#define HIGH	1
#define LOW		0
//#define NULL	(void *)0

#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

// hal header
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"


// own header
#include "variable.h"
#include "struct.h"
#include "menu.h"
#include "vfd.h"
#include "motor.h"
#include "sensor.h"

#endif
