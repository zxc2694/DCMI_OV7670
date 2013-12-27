/**
  ******************************************************************************
  * @file    DCMI/Camera/camera_api.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    30-September-2011
  * @brief   This file contains the routinue needed to configure OV9655/OV2640 
  *          Camera modules.
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
#include "camera_api.h"
#include "OV7670.h"
#include "main.h"
/** @addtogroup STM32F4xx_StdPeriph_Examples
  * @{
  */
extern JOYState_TypeDef state;
/** @addtogroup DCMI_Camera
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Image Formats */
const uint8_t *ImageForematArray[] =
{
  "BMP RGB Format    ",
  "BMP YUV Format     ",
};
static __IO uint32_t TimingDelay;
__IO uint32_t PressedKey = 0;
uint8_t ValueMin = 0, ValueMax = 2;
ImageFormat_TypeDef ImageFormat;

extern const u8 OV7670_RGB_reg[OV7670_RGB_REG_NUM][2];
extern const u8 OV7670_YUV_reg[OV7670_YUV_REG_NUM][2];
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initialize resources used for this demo. 
  * @param  None
  * @retval Digit value
  */
uint8_t Demo_Init(void)
{
  __IO uint32_t tmpValue = 0;
  PressedKey = NOKEY;
  
 /* Configure the IO Expander */
  if(key_board_config())
  {  
    LCD_DisplayStringLine(LINE(6), (uint8_t*)"4x4 KEY BOARD Init OK         ");
    Delay(200000);
  }
  else
  {
    LCD_SetTextColor(LCD_COLOR_RED);  
    LCD_DisplayStringLine(LINE(6), (uint8_t*)"4x4 KEY BOARD Init FAILED Please Reset the board");
    while (1);
  }

  /* 使能键盘中断*/
  KEY_INT_Config();

  Demo_LCD_Clear();
  LCD_DisplayStringLine(LINE(6), (uint8_t*)"Main Menu:              ");
  LCD_DisplayStringLine(LINE(7), (uint8_t*)"==========");
  LCD_DisplayStringLine(LINE(8), (uint8_t*)"Use UP and DOWN Buttons to Navigate");
  LCD_DisplayStringLine(LINE(9), (uint8_t*)"Use SEL Button to Select Image Format");

  LCD_DisplayStringLine(LINE(11), (uint8_t*)"Select the Image Format:");
  Display_Menu(ValueMin, ValueMax);

  while (1)
  {
    /* If "UP" pushbutton is pressed */
    if (state == JOY_UP)
    {    
      /* Increase the value of the digit */
      if (tmpValue == ValueMin)
      {
        tmpValue = ValueMax - 1;
      }
      else
      {
        tmpValue--;
      }
      /* Display new Menu */
      Display_Menu(tmpValue, ValueMax);
      
      state = JOY_NONE;
    }
    /* If "DOWN" pushbutton is pressed */
    if (state == JOY_DOWN)
    {      
      /* Decrease the value of the digit */
      if (tmpValue == (ValueMax - 1))
      {
        tmpValue = ValueMin;
      }
      else
      {
        tmpValue++;
      }
      /* Display new Menu */
      Display_Menu(tmpValue, ValueMax);
      
      state = JOY_NONE;
    }
    /* If "SEL" pushbutton is pressed */
    if (state == JOY_SEL)
    {
      state = JOY_NONE;

      /* Return the digit value and exit */
      return (ImageFormat_TypeDef)tmpValue;
    }
  }
}

/**
  * @brief  Display the navigation menu.
  * @param  None
  * @retval None
  */
void Display_Menu(uint8_t ForematIndex, uint8_t MaxForematIndex)
{
  uint32_t index;

  for(index=0; index<MaxForematIndex; index++)
  {
    if(index == ForematIndex)
    {
      LCD_SetTextColor(LCD_COLOR_RED);
      LCD_DisplayStringLine(LINE(12 + index), (uint8_t*)ImageForematArray[index]);
      LCD_SetTextColor(LCD_COLOR_WHITE);
    }
    else
    {
      LCD_DisplayStringLine(LINE(12 + index), (uint8_t*)ImageForematArray[index]);  
    }
  }
}

void Camera_configformat(ImageFormat_TypeDef ImageFormat)
{
   u8 temp,i;
  
   if(ImageFormat==RGB565)
   {
        SCCB_WriteByte(0x0B, 0x00);
        
        temp = SCCB_ReadByte(0x0B);  //读摄像头ID
	
        if(temp==0x73)//OV7670
	
        {  
	  for(i=0;i<OV7670_RGB_REG_NUM;i++)
             SCCB_WriteByte(OV7670_RGB_reg[i][0],OV7670_RGB_reg[i][1]);   
	}
   }
   else 
   {
        SCCB_WriteByte(0x0B, 0x00);
        
        temp = SCCB_ReadByte(0x0B);  //读摄像头ID
	
        if(temp==0x73)//OV7670
	
        {  
	  for(i=0;i<OV7670_YUV_REG_NUM;i++)
             SCCB_WriteByte(OV7670_YUV_reg[i][0],OV7670_YUV_reg[i][1]);   
	}
   }
        //这里加入1s延时等待摄像头稳定      
        Delay(1000000);  
}

/**
  * @brief  Configures OV9655 or OV2640 Camera module mounted on STM324xG-EVAL board.
  * @param  ImageBuffer: Pointer to the camera configuration structure
  * @retval None
  */
void Camera_Config(void)
{
    switch (ImageFormat)
    {
      case RGB565:
      {
        /* Configure the OV9655 camera and set the QQVGA mode */
        Camera_Init();
        Camera_configformat(RGB565);
        DCMI_CaptureCmd(ENABLE); 
        break;
      }
      case YUV:
      {
        /* Configure the OV9655 camera and set set the QVGA mode */
        Camera_Init();
        Camera_configformat(YUV);
        DCMI_CaptureCmd(ENABLE); 
        break;
      }
      default:
      {
        /* Configure the OV9655 camera and set the QQVGA mode */
        Camera_Init();
        Camera_configformat(RGB565);
        DCMI_CaptureCmd(ENABLE); 
        break;
      } 
    }
}

/**
  * @brief  Clear LCD screen.
  * @param  None
  * @retval None
  */
void Demo_LCD_Clear(void)
{
  uint32_t j;
  for( j= 5; j < 19; j++ ) 
  {
    LCD_ClearLine(LINE(j));
  }
}

/**
  * @brief  Empty function.
  * @param  None
  * @retval None
  */
void NullFunc(void)
{
}

/**
  * @}
  */ 

/**
  * @}
  */ 
  
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
