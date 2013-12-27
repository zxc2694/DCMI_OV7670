#ifndef __OV7670_H
#define __OV7670_H

/* Includes ------------------------------------------------------------------*/
#include "camera_api.h"
#define OV7670_device_wraddr 0x42
#define OV7670_device_rdaddr 0x43

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  uint8_t Manufacturer_ID1;
  uint8_t Manufacturer_ID2;
  uint8_t Version;
  uint8_t PID;
}OV7670_IDTypeDef;

void OV7670_HW_Init(void);
void OV7670_Reset(void);
void OV7670_ReadID(OV7670_IDTypeDef* OV7670ID);
void OV7670_Init(ImageFormat_TypeDef ImageFormat);
void OV7670_QQVGAConfig(void);
void OV7670_QVGAConfig(void);
void OV7670_BrightnessConfig(uint8_t Brightness);
uint8_t WrCmos7670(uint16_t Addr, uint8_t Data);
uint8_t RdCmos7670(uint16_t Addr);
void set_Cmos7670reg(void);
#endif