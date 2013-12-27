
#ifndef _SENSOR_CONFIG_H
#define _SENSOR_CONFIG_H

#include"sccb.h"

const u8 OV7670_RGB_reg[OV7670_RGB_REG_NUM][2]=
{	       
        {0x3a, 0x0c},//0x0c     
        {0x32, 0x80},//0x00
        {0x17, 0x16},//0x16
        {0x18, 0x04},//0x04
        {0x19, 0x02},//0x02
        {0x1a, 0x7b},//0x7b,
        {0x03, 0x02},//0x06,
        
        {0x1B, 0x00},
        {0x3B, 0x10},
            
        {0x11, 0x01},//0x40//内部时钟分频,直接使用外部时钟
        {0x6b, 0x0A},//PLL 重要参数   
        {0x3e, 0x00},//PCLK 分频
        {0x73, 0x00},//
        
        {0x0c, 0x00},     
        {0x70, 0x3a},
        {0x71, 0x35},
        {0x72, 0x11},
        {0xa2, 0x02},
        {0x11, 0x81},
        
        {0x7a, 0x12},//0x20
        {0x7b, 0x08},//0x1c
        {0x7c, 0x16},//0x28
        {0x7d, 0x30},//0x3c
        {0x7e, 0x5e},//0x55
        {0x7f, 0x72},//0x68
        {0x80, 0x82},//0x76
        {0x81, 0x8e},//0x80
        {0x82, 0x9a},//0x88
        {0x83, 0xa4},//0x8f
        {0x84, 0xac},//0x96
        {0x85, 0xb8},//0xa3
        {0x86, 0xc3},//0xaf
        {0x87, 0xd6},//0xc4
        {0x88, 0xe6},//0xd7
        {0x89, 0xf2},//0xe8
        
        {0x13, 0xe0},
        {0x00, 0x00},//AGC
        {0x10, 0x10},//
        {0x0d, 0x00},
        {0x14, 0x28},//0x38, limit the max gain
        {0xa5, 0x05},
        {0xab, 0x07},
        {0x24, 0x3c},//0x75
        {0x25, 0x36},//0x63
        {0x26, 0x72},//0xa5
        {0x27, 0x08},//
        {0x28, 0x08},//
        {0x2c, 0x08},//
        
        {0x9f, 0x78},
        {0xa0, 0x68},
        {0xa1, 0x03},//0x0b,
        {0xa6, 0xdf},//0xd8,
        {0xa7, 0xdf},//0xd8,
        {0xa8, 0xf0},
        {0xa9, 0x90},
        {0xaa, 0x94},
        {0x13, 0xe5},
        {0x0e, 0x61},
        {0x0f, 0x4b},
        {0x16, 0x02},
        
        {0x1e, 0x07},//0x07,
        {0x21, 0x02},
        {0x22, 0x91},
        {0x29, 0x07},
        {0x33, 0x0b},
        {0x35, 0x0b},
        {0x37, 0x1d},
        {0x38, 0x71},
        {0x39, 0x2a},
        
        {0x3c, 0x68},
        {0x4d, 0x40},
        {0x4e, 0x20},
        {0x69, 0x55},//固定增益
        {0x74, 0x19},
        {0x8d, 0x4f},
        {0x8e, 0x00},
        {0x8f, 0x00},
        {0x90, 0x00},
        {0x91, 0x00},
        {0x92, 0x00},//0x19,//0x66
        {0x96, 0x00},
        {0x9a, 0x80},
        {0xb0, 0x84},
        {0xb1, 0x0c},
        {0xb2, 0x0e},
        {0xb3, 0x82},
        {0xb8, 0x0a},
        {0x43, 0x14},
        {0x44, 0xf0},
        {0x45, 0x34},
        {0x46, 0x58},
        {0x47, 0x28},
        {0x48, 0x3a},
        {0x59, 0x88},
        {0x5a, 0x88},
        {0x5b, 0x44},
        {0x5c, 0x67},
        {0x5d, 0x49},
        {0x5e, 0x0e},
        
        {0x62, 0x00},
        {0x63, 0x00},
        {0x64, 0x02},//0x04
        {0x65, 0x20},//0x20
        {0x66, 0x00},//0x05
        {0x94, 0x04},
        {0x95, 0x08},
        {0x6c, 0x0a},
        {0x6d, 0x55},
        {0x6e, 0x11},
        {0x6f, 0x9f},//0x9e for advance AWB
        {0x6a, 0x40},
        
        {0x01, 0x40},//蓝色通道增益
        {0x02, 0x40},//红色通道增益
        {0x13, 0xe7},
         
        {0x4f, 0x98},//0x80
        {0x50, 0x98},//0x80
        {0x51, 0x00},//0x00
        {0x52, 0x28},//0x22
        {0x53, 0x70},//0x5e
        {0x54, 0x98},//0x80
            
        {0x55, 0x10},//亮度
        {0x56, 0x30},//对比度
        {0x57, 0x80},//对比度中心
        
        {0x58, 0x9e},        
        {0x41, 0x08},
        {0x3f, 0x05},//边缘增强调整
        {0x75, 0x05},
        {0x76, 0xe1},
        {0x4c, 0x0F},//噪声抑制强度
        {0x77, 0x0a},
        {0x3d, 0xc2},//0xc0,
        {0x4b, 0x09},
        {0xc9, 0xe0},
        {0x41, 0x38},
        {0x34, 0x11},
        
        {0x3b, 0x10},//0x00,//0x02,
        {0xa4, 0x89},//0x88
        {0x96, 0x00},
        {0x97, 0x30},
        {0x98, 0x20},
        {0x99, 0x30},
        {0x9a, 0x84},
        {0x9b, 0x29},
        {0x9c, 0x03},
        {0x9d, 0x4c},
        {0x9e, 0x3f},
        {0x78, 0x04},        
        {0x79, 0x01},
        {0xc8, 0xf0},
        {0x79, 0x0f},
        {0xc8, 0x00},
        {0x79, 0x10},
        {0xc8, 0x7e},
        {0x79, 0x0a},
        {0xc8, 0x80},
        {0x79, 0x0b},
        {0xc8, 0x01},
        {0x79, 0x0c},
        {0xc8, 0x0f},
        {0x79, 0x0d},
        {0xc8, 0x20},
        {0x79, 0x09},
        {0xc8, 0x80},
        {0x79, 0x02},
        {0xc8, 0xc0},
        {0x79, 0x03},
        {0xc8, 0x40},
        {0x79, 0x05},
        {0xc8, 0x30},
        {0x79, 0x26},
        {0x09, 0x01},//0x02
        {0x3b, 0x02},//0x82,//0xc0,//0xc2,        //night mode
         
        {0x40, 0xd0},//输出模式选择，QVGA ，RGB格式
        {0x42, 0x00},//DSP彩条输出使能
        {0x12, 0x14}, //COM7,0x14
        {0x15, 0x08},//重要参数 
};

const u8 OV7670_YUV_reg[OV7670_YUV_REG_NUM][2]=
{	 
        {0x3a, 0x18},   
        {0x3d, 0x81},//0xc0,
        {0x32, 0x80},//0x00
        {0x17, 0x16},//0x16
        {0x18, 0x04},//0x04
        {0x19, 0x02},//0x02
        {0x1a, 0x7b},//0x7b,
        {0x03, 0x02},//0x06,
        
        {0x1B, 0x00},
        {0x3B, 0x10},
            
        {0x11, 0x40},//内部时钟分频,直接使用外部时钟
            
        {0x0c, 0x00},
        {0x3e, 0x00},//PCLK 分频
        {0x70, 0x3a},
        {0x71, 0x35},
        {0x72, 0x11},
        {0x73, 0x00},//
        {0xa2, 0x02},
        {0x11, 0x81},
        
        {0x7a, 0x12},//0x20
        {0x7b, 0x08},//0x1c
        {0x7c, 0x16},//0x28
        {0x7d, 0x30},//0x3c
        {0x7e, 0x5e},//0x55
        {0x7f, 0x72},//0x68
        {0x80, 0x82},//0x76
        {0x81, 0x8e},//0x80
        {0x82, 0x9a},//0x88
        {0x83, 0xa4},//0x8f
        {0x84, 0xac},//0x96
        {0x85, 0xb8},//0xa3
        {0x86, 0xc3},//0xaf
        {0x87, 0xd6},//0xc4
        {0x88, 0xe6},//0xd7
        {0x89, 0xf2},//0xe8
        
        {0x13, 0xe0},
        {0x00, 0x00},//AGC
        {0x10, 0x10},//
        {0x0d, 0x00},
        {0x14, 0x28},//0x38, limit the max gain
        {0xa5, 0x05},
        {0xab, 0x07},
        {0x24, 0x3c},//0x75
        {0x25, 0x36},//0x63
        {0x26, 0x72},//0xa5
        {0x27, 0x08},//
        {0x28, 0x08},//
        {0x2c, 0x08},//
        
        {0x9f, 0x78},
        {0xa0, 0x68},
        {0xa1, 0x03},//0x0b,
        {0xa6, 0xdf},//0xd8,
        {0xa7, 0xdf},//0xd8,
        {0xa8, 0xf0},
        {0xa9, 0x90},
        {0xaa, 0x94},
        {0x13, 0xe5},
        {0x0e, 0x61},
        {0x0f, 0x4b},
        {0x16, 0x02},
        
        {0x1e, 0x07},//0x07,
        {0x21, 0x02},
        {0x22, 0x91},
        {0x29, 0x07},
        {0x33, 0x0b},
        {0x35, 0x0b},
        {0x37, 0x1d},
        {0x38, 0x71},
        {0x39, 0x2a},
        
        {0x3c, 0x68},
        {0x4d, 0x40},
        {0x4e, 0x20},
        {0x69, 0x55},//固定增益
        {0x6b, 0x0A},//PLL 重要参数
        {0x74, 0x19},
        {0x8d, 0x4f},
        {0x8e, 0x00},
        {0x8f, 0x00},
        {0x90, 0x00},
        {0x91, 0x00},
        {0x92, 0x00},//0x19,//0x66
        {0x96, 0x00},
        {0x9a, 0x80},
        {0xb0, 0x84},
        {0xb1, 0x0c},
        {0xb2, 0x0e},
        {0xb3, 0x82},
        {0xb8, 0x0a},
        {0x43, 0x14},
        {0x44, 0xf0},
        {0x45, 0x34},
        {0x46, 0x58},
        {0x47, 0x28},
        {0x48, 0x3a},
        {0x59, 0x88},
        {0x5a, 0x88},
        {0x5b, 0x44},
        {0x5c, 0x67},
        {0x5d, 0x49},
        {0x5e, 0x0e},
        
        {0x62, 0x00},
        {0x63, 0x00},
        {0x64, 0x02},//0x04
        {0x65, 0x20},//0x20
        {0x66, 0x00},//0x05
        {0x94, 0x04},
        {0x95, 0x08},
        {0x6c, 0x0a},
        {0x6d, 0x55},
        {0x6e, 0x11},
        {0x6f, 0x9f},//0x9e for advance AWB
        {0x6a, 0x40},
        
        {0x01, 0x40},//蓝色通道增益
        {0x02, 0x40},//红色通道增益
        {0x13, 0xe7},
         
        {0x4f, 0x98},//0x80
        {0x50, 0x98},//0x80
        {0x51, 0x00},//0x00
        {0x52, 0x28},//0x22
        {0x53, 0x70},//0x5e
        {0x54, 0x98},//0x80
            
        {0x55, 0x10},//亮度
        {0x56, 0x30},//对比度
        {0x57, 0x80},//对比度中心
        
        {0x58, 0x9e},        
        {0x41, 0x08},
        {0x3f, 0x05},//边缘增强调整
        {0x75, 0x05},
        {0x76, 0xe1},
        {0x4c, 0x0F},//噪声抑制强度
        {0x77, 0x0a},

        {0x4b, 0x09},
        {0xc9, 0xe0},
        {0x41, 0x38},
        {0x34, 0x11},
        {0x3b, 0x10},//0x00,//0x02,
        {0xa4, 0x89},//0x88,
        {0x96, 0x00},
        {0x97, 0x30},
        {0x98, 0x20},
        {0x99, 0x30},
        {0x9a, 0x84},
        {0x9b, 0x29},
        {0x9c, 0x03},
        {0x9d, 0x4c},
        {0x9e, 0x3f},
        {0x78, 0x04},        
        {0x79, 0x01},
        {0xc8, 0xf0},
        {0x79, 0x0f},
        {0xc8, 0x00},
        {0x79, 0x10},
        {0xc8, 0x7e},
        {0x79, 0x0a},
        {0xc8, 0x80},
        {0x79, 0x0b},
        {0xc8, 0x01},
        {0x79, 0x0c},
        {0xc8, 0x0f},
        {0x79, 0x0d},
        {0xc8, 0x20},
        {0x79, 0x09},
        {0xc8, 0x80},
        {0x79, 0x02},
        {0xc8, 0xc0},
        {0x79, 0x03},
        {0xc8, 0x40},
        {0x79, 0x05},
        {0xc8, 0x30},
        {0x79, 0x26},
        {0x09, 0x01},//0x02
        {0x3b, 0x02},//0x82,//0xc0,//0xc2,        //night mode
        
        {0x67, 0x11},
        {0x68, 0x80},
        {0x40, 0x80},//输出模式选择，QVGA
        {0x42, 0x00},//DSP彩条输出使能
        {0x12, 0x10}, //COM7,YUV格式
        {0x15, 0x08},//重要参数
        
};

/////////////////////////////////////////////////////////////////////////
#endif


