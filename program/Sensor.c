#include "sccb.h"
#include "main.h"
//#include "camera_api.h"
#include "Sensor_config.h"
//#include "stm32f10x_lib.h"

extern const u8 OV7670_reg[OV7670_REG_NUM][2];
extern const u8 OV7725_reg[OV7725_REG_NUM][2];

/////////////////////////////
//VSYNC GPIO INIT
//guanfu_wang
void Sensor_GPIO_Init(void)//
{
  
  GPIO_InitTypeDef GPIO_InitStructure;
   // Enable GPIOC  clock
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  Sensor_VSYNC_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;////上拉 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIO_VSYNC, &GPIO_InitStructure);
 
}

//////////////////////////////////////////////////
////函数功能：中断配制
//guanfu_wang
/*
void Sensor_Interrupts_Config(void)//VSYNC 中断
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
} 

void Sensor_EXTI_Config(void)//VSYNC 中断
{
  EXTI_InitTypeDef EXTI_InitStructure;
  

  GPIO_EXTILineConfig(GPIO_PORT_SOURCE_VSYNC_CMOS, GPIO_PIN_SOURCE_VSYNC_CMOS);
  EXTI_InitStructure.EXTI_Line = EXTI_LINE_VSYNC_CMOS;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising ;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  EXTI_GenerateSWInterrupt(EXTI_LINE_VSYNC_CMOS);

}
*/

void delay_us(u32 time_cnt)
{ 
  u32 i;
  for(i=0;i<time_cnt;i++);
  //return 0;
}

void DCMI_Interface_Init(void)
{
  DCMI_InitTypeDef DCMI_InitStructure;
  DMA_InitTypeDef  DMA_InitStructure;
  
  /*
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_PriorityGroup_2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
 */
  /*** Configures the DCMI to interface with the OV9655 camera module ***/
  /* Enable DCMI clock */
  RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);

  /* DCMI configuration */ 
  DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_SnapShot;//DCMI_CaptureMode_Continuous;
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
  
  //DCMI_ITConfig(DCMI_IT_VSYNC, ENABLE);
  
  /* DCMI configuration */
  DCMI_Init(&DCMI_InitStructure);

  /* DMA2 IRQ channel Configuration */
  DMA_Init(DMA2_Stream1, &DMA_InitStructure);

  DMA_Cmd(DMA2_Stream1, ENABLE); 
          
  DCMI_Cmd(ENABLE); 

  //delay_us(4000000); 
  
  //DCMI_CaptureCmd(ENABLE);

}
/*
void DCMI_IRQHandler(void)
{
  if( DCMI_GetITStatus(DCMI_IT_VSYNC)!= RESET)
  {
    DMA_Cmd(DMA2_Stream1, ENABLE); 
    delay_us(4000000); 
    DCMI_CaptureCmd(ENABLE);
    DCMI_ClearITPendingBit(DCMI_IT_VSYNC);
  }
}
*/

//返回1成功，

void Sensor_init(void)
{
	u8 temp;
	u8 i=0;
        u16 j,k;
            
        OV7670_HW_Init();
        
	SCCB_GPIO_Config();

        DCMI_Interface_Init();
        
        SCCB_WriteByte(0x12, 0x80);  //Reset SCCB
        
        for(j=0;j<700;j++)
        
           delay_us(40000); //软件复位后也要延时     
           
        SCCB_WriteByte(0x0B, 0x00);
        
        temp = SCCB_ReadByte(0x0B);  //读ID
	
        if(temp==0x73)//OV7670
	
        {  
          //OV7670_SetReg();
	  for(i=0;i<OV7670_REG_NUM;i++)
             SCCB_WriteByte(OV7670_reg[i][0],OV7670_reg[i][1]); 
          
	}
  
        
        for(k=0;k<400;k++)
          
          delay_us(100000); 
        
        DCMI_CaptureCmd(ENABLE); 
             

} 

///////////////////

