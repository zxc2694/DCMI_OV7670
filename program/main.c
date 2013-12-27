/**
  ******************************************************************************
  * @file    DCMI/Camera/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    30-September-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include  "lcd_log.h"
#include "OV7670.h"

/** @addtogroup STM32F4xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup DCMI_Camera
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
RCC_ClocksTypeDef RCC_Clocks;
OV7670_IDTypeDef OV7670_Camera_ID;
uint8_t buffer[40];
//extern Camera_TypeDef Camera;
extern ImageFormat_TypeDef ImageFormat;
extern __IO uint8_t ValueMax;
extern const uint8_t *ImageForematArray[];

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
  this is done through SystemInit() function which is called from startup
  file (startup_stm32f4xx.s) before to branch to application main.
  To reconfigure the default setting of SystemInit() function, refer to
  system_stm32f4xx.c file
  */

  /* SysTick end of count event each 10ms */
  //RCC_GetClocksFreq(&RCC_Clocks);
  //SysTick_Config(RCC_Clocks.HCLK_Frequency / 100);

  /* Initialize LEDs and push-buttons mounted on STM324xG-EVAL board */
  STM_EVAL_LEDInit(LED1);
  STM_EVAL_LEDInit(LED2);
  STM_EVAL_LEDInit(LED3);
  //¶¨ÒåWAKEUP¼üÎªÅÄÕÕ¼ü
  STM_EVAL_PBInit(BUTTON_WAKEUP , BUTTON_MODE_EXTI);
  STM_EVAL_LEDOn(LED1);

 /* Initialize the LCD */
  STM324xG_LCD_Init();
  LCD_Clear(Black);
  LCD_SetTextColor(White);

  LCD_LOG_SetHeader("STM32 Camera Demo");
  LCD_LOG_SetFooter ("   Copyright (c) STMicroelectronics" );

  LCD_SetTextColor(LCD_COLOR_YELLOW);
  LCD_DisplayStringLine(LINE(4), (uint8_t*)buffer);
  LCD_SetTextColor(LCD_COLOR_WHITE);
  Delay(20000);

  /* Initialize demo */
  //ImageFormat = (ImageFormat_TypeDef)Demo_Init();
  
  /* Configure the Camera module mounted on STM324xG-EVAL board */
  Demo_LCD_Clear();
  LCD_DisplayStringLine(LINE(4), "Camera Init..               ");

  sprintf((char*)buffer, " Image selected: %s", ImageForematArray[ImageFormat]);
  LCD_DisplayStringLine(LINE(4),(uint8_t*)buffer);
  
  /* Insert 80ms delay: wait 80ms */
  Delay(80000); 

  LCD_ClearLine(LINE(4));
  Demo_LCD_Clear();
   
  /* LCD Display window */
  //LCD_SetDisplayWindow(239, 319, 240, 320);
  LCD_WriteReg(LCD_REG_3, 0x1038);
  LCD_WriteReg(LCD_REG_144, 0x0011);
  LCD_WriteReg(LCD_REG_8,  0x0208); /* set the back porch and front porch */
  //LCD_WriteRAM_Prepare(); 
  
  Camera_Init();
  Camera_configformat(RGB565);
  DCMI_CaptureCmd(ENABLE);
  
  while(1)
  {
    /* Blink LD1, LED2 and LED4 */
    STM_EVAL_LEDToggle(LED1);
    STM_EVAL_LEDToggle(LED2);
    STM_EVAL_LEDToggle(LED3);

    /* Insert 100ms delay */
    Delay(100000);
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
