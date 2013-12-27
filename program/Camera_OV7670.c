/**
  ******************************************************************************
  * @file    Camera_OV7670.c 
  * @author  Jacky.Cheng
  * @version V1.0.0
  * @date    1-June-2012
  * @brief   
  ******************************************************************************
  * @attention
  *
  * 摄像头配置和DCMI模式配置
  ******************************************************************************
  */
#include "main.h"
#include "Sensor_config.h"

extern ImageFormat_TypeDef ImageFormat;

void DCMI_Interface_Init(void)
{
  DCMI_InitTypeDef DCMI_InitStructure;
  DMA_InitTypeDef  DMA_InitStructure;
   
  /* Enable DCMI clock */
  RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);

  /* DCMI configuration */ 
  //DCMI捕捉模式的设置，默认是连续模式,会看到连续的移动图像
  //用户在使用的时候可调整为SnapShot(抓拍)，也就是单帧
  DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_Continuous;//DCMI_CaptureMode_SnapShot;
  DCMI_InitStructure.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;
  DCMI_InitStructure.DCMI_PCKPolarity = DCMI_PCKPolarity_Falling;
  DCMI_InitStructure.DCMI_VSPolarity = DCMI_VSPolarity_High;
  DCMI_InitStructure.DCMI_HSPolarity = DCMI_HSPolarity_High;
  DCMI_InitStructure.DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;
  DCMI_InitStructure.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b;

  /* Configures the DMA2 to transfer Data from DCMI */
  /* Enable DMA2 clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
  
  /* DMA2 Stream1 Configuration */
  DMA_DeInit(DMA2_Stream1);

  DMA_InitStructure.DMA_Channel = DMA_Channel_1;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = DCMI_DR_ADDRESS;	
  DMA_InitStructure.DMA_Memory0BaseAddr = FSMC_LCD_ADDRESS;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = 1;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  
  //DCMI中断配置，在使用帧中断或者垂直同步中断的时候打开
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  NVIC_InitStructure.NVIC_IRQChannel = DCMI_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  //使能DCMI中断
  DCMI_ITConfig(DCMI_IT_VSYNC, ENABLE);
  
  /* DCMI configuration */
  DCMI_Init(&DCMI_InitStructure);

  /* DMA2 IRQ channel Configuration */
  DMA_Init(DMA2_Stream1, &DMA_InitStructure);

  DMA_Cmd(DMA2_Stream1, ENABLE); 
          
  DCMI_Cmd(ENABLE); 

}

/*DCMI中断处理函数，这里使用的是垂直同步中断，用户可根据需要自己调整中断的方式*/

void DCMI_IRQHandler(void)
{
  if( DCMI_GetITStatus(DCMI_IT_VSYNC)!= RESET)
  {
    DCMI_ClearITPendingBit(DCMI_IT_VSYNC);
    //LCD_WindowModeDisable();
    LCD_SetDisplayWindow(239, 319, 240, 320);
    LCD_WriteRAM_Prepare();      
  }
}

//返回1成功，

void Camera_Init(void)
{	
    u16 j;
            
    OV7670_HW_Init();
        
    SCCB_GPIO_Config();

    DCMI_Interface_Init();
        
    SCCB_WriteByte(0x12, 0x80);  //软件复位摄像头
        
    //软件复位后必须要加延时 500ms
    for(j=0;j<500;j++)
        
       Delay(1000);                           
} 

///////////////////

