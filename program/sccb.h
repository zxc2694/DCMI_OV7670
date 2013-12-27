#ifndef _sccb_H
#define _sccb_H

  #include "stm32f4xx.h"
  #define OV7670_RGB_REG_NUM  176
  #define OV7670_YUV_REG_NUM  178

  #define  SCCB_SDA_PIN   GPIO_Pin_13
  #define  SCCB_SCL_PIN   GPIO_Pin_3
  #define  SCCB_SDA_GPIO      GPIOC
  #define  SCCB_SCL_GPIO      GPIOB

  #define SCCB_SDA_High  GPIO_SetBits(SCCB_SDA_GPIO,SCCB_SDA_PIN)
  #define SCCB_SDA_Low   GPIO_ResetBits(SCCB_SDA_GPIO,SCCB_SDA_PIN)
  #define SCCB_SCL_High  GPIO_SetBits(SCCB_SCL_GPIO,SCCB_SCL_PIN)
  #define SCCB_SCL_Low   GPIO_ResetBits(SCCB_SCL_GPIO,SCCB_SCL_PIN)
  #define SCCB_ACK_STATE  SCCB_SDA_GPIO->IDR & SCCB_SDA_PIN

  #define Sensor_VSYNC_PIN    GPIO_Pin_7
  #define GPIO_VSYNC          GPIOB
  #define RCC_VSYNC_Clock     RCC_AHB2Periph_GPIOB

  #define GPIO_PIN_VSYNC_CMOS                GPIO_Pin_3
  #define EXTI_LINE_VSYNC_CMOS               EXTI_Line3
  #define GPIO_PORT_SOURCE_VSYNC_CMOS        GPIO_PortSourceGPIOC
  #define GPIO_PIN_SOURCE_VSYNC_CMOS         GPIO_PinSource3

/////////////////////////////////////////
void XCLK_init_ON(void);//STM32 mco功能开启 输出时钟给CMOS传感器

void Camera_Powerdown(void);
void Sensor_init(void);
void Sensor_GPIO_Init(void);
void Sensor_EXTI_Config(void);
void Sensor_Interrupts_Config(void);


///////////////////////////////////////////
void Camera_Reset(void);
void Camera_Init(void);
void OV7670_HW_Init(void);
void SCCB_GPIO_Config(void);
void SCCB_SDA_OUT_Config(void);
void SCCB_SDA_IN_Config(void);
void SCCB_Start(void);
void SCCB_Stop(void);
void SCCB_data_trans(u8 outdata);
u8 SCCB_data_receive(void);
void SCCB_WriteByte(u8 reg_addr,u8 data);
u8 SCCB_ReadByte(u8 reg_addr);
void DCMI_Interface_Init(void);

#endif /* _IIC_H */


