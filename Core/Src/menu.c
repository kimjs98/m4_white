#include "device.h"
#include "menu.h"

#define SW_U  		HAL_GPIO_ReadPin(SW_U_GPIO_Port, SW_U_Pin)
#define SW_D  		HAL_GPIO_ReadPin(SW_D_GPIO_Port, SW_D_Pin)
#define SW_R  		HAL_GPIO_ReadPin(SW_R_GPIO_Port, SW_R_Pin)
#define SW_L  		HAL_GPIO_ReadPin(SW_L_GPIO_Port, SW_L_Pin)

#define DEBOUNCE	HAL_Delay(50)

typedef enum menu 
{
	HEIGHT = 3,
	WIDTH = 5, 
	NINE = 9
}e_menu;

void PrintMenu(void)
{
	TxPrintf("\n\n");
	TxPrintf("========   STM32F407VGT6 Monitor V1.0   ========\n");	
	TxPrintf("========   by Lee Jin Ho Maze 23rd   =======\n");	
	TxPrintf("=====  https://blog.naver.com/zazz0907  ======\n\n");
}

void System_Information(void)
{
	TxPrintf("SYSCLK_Frequency : %d\n", HAL_RCC_GetSysClockFreq() / 1000000);
	TxPrintf("HCLK_Frequency : %d\n", HAL_RCC_GetHCLKFreq() / 1000000);
	TxPrintf("PCLK2(APB2)_Frequency : %d\n", HAL_RCC_GetPCLK1Freq() / 1000000);	
	TxPrintf("PCLK1(APB1)_Frequency : %d\n", HAL_RCC_GetPCLK2Freq() / 1000000);
}

void (*menu_func[ HEIGHT ][ WIDTH ] )( void ) = 
{
	NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL
};

const char menu_print[ HEIGHT ][ WIDTH ][ NINE ] =
{
	"DEBUG  1", "Map_Info", "        ", "        ","        ",
	"DEBUG  2", "        ", "        ", "        ","        ",
	"DEBUG  3", "        ", "        ", "        ","        ",
};

void menu (void)
{
	INT32 int32_height=0;
	INT32 int32_width=0;
		
	while (1)
		{
			if( int32_width)
			{
	
				
				if( ( !SW_L ) )
				{
					while( !SW_L );
					DEBOUNCE;
					int32_width--;
					flag++; 
				}
	
				if( ( !SW_R ) )
				{
					while( !SW_R );
					DEBOUNCE;
					int32_width++;
					flag++; 
					
					if( int32_width >= WIDTH ) int32_width = 1;
				}
	
				if( ( !SW_D ) )
				{
					while( !SW_D );
					DEBOUNCE;
					flag++; 
					
					menu_func[ int32_height ][ int32_width ]();
				}
			}
	
			else
			{
				if( (!SW_U) )
				{
					while( !SW_U );
					DEBOUNCE;
					int32_height--;
					flag++;
					
					if(int32_height < 0)	int32_height = HEIGHT - 1;
				}
	
				else if( ( !SW_D ) )
				{
					while( !SW_D );
					DEBOUNCE;
					int32_height++;
					flag++;
					
					if(int32_height >= HEIGHT)	int32_height = 0;
				}
	
				
				else if( ( !SW_R ) )
				{
					while( !SW_R );
					DEBOUNCE;
					int32_width++;
					flag++;
				}
	
				else;
			}
	
			if( flag )
			{
				VFDPrintf( ( char * )menu_print[ int32_height ][ int32_width ] );
				flag = 0;
			}
	
		}
		
		
	}
	


