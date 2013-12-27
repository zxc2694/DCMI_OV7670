#include "main.h"

void delay(u32 time_cnt)
{ 
  u16 i;
  for(i=0;i<time_cnt;i++);
}

void OV7670_HW_Init(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB |
                         RCC_AHB1Periph_GPIOC, ENABLE);

  /* Connect DCMI pins to AF13 */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_DCMI);

  GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_DCMI);
  
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_DCMI);
  
    /* D0..D4(PC6/8/9/11)*/
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  //GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  //GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  /* DCMI GPIO configuration */
  /* D5D6D7(PB6/8/9), VSYNC(PB7) */
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  //GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  //GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* PCLK(PA6) */
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  //GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  //GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
   
}

void Camera_Powerdown(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
   /* Enable GPIOC  clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_ResetBits(GPIOA,GPIO_Pin_8);
  delay(500000);
  GPIO_SetBits(GPIOA,GPIO_Pin_8);
}

void SCCB_GPIO_Config(void)
{
  //配置SCCB SCL和SDA
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC, ENABLE);
   GPIO_InitTypeDef GPIO_InitStructure;
   
   GPIO_InitStructure.GPIO_Pin = SCCB_SDA_PIN ;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_Init(SCCB_SDA_GPIO,&GPIO_InitStructure); 
  
   GPIO_InitStructure.GPIO_Pin = SCCB_SCL_PIN ;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_Init(SCCB_SCL_GPIO,&GPIO_InitStructure); 
   
}

void SDA_IN_Config(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   GPIO_InitStructure.GPIO_Pin =  SCCB_SDA_PIN;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //做输入的时候必须上拉
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
   GPIO_Init(SCCB_SDA_GPIO,&GPIO_InitStructure);
}

void SDA_OUT_Config(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   GPIO_InitStructure.GPIO_Pin =  SCCB_SDA_PIN;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_Init(SCCB_SDA_GPIO,&GPIO_InitStructure);
}

inline void I2C_Stop(void)
{
  delay(200); //结束之前SCL为低
  SCL_High;
  delay(200);
  SDA_Low;
  delay(200);
  SDA_High;
  delay(100);
}

inline void I2C_Start(void)
{
  SDA_High;
  SCL_High;
  delay(200);
  SDA_Low;
  delay(200);
  SCL_Low; //I2C启动后SDA和SCL都为低的情况结束该函数
}

//进入8位传递函数时要保证SCL为低
inline void data_trans(u8 outdata)
{
  u8 i;         
  for(i=0;i<8;i++)
  { 
    //delay(100);   
    if(outdata & 0x80)
       SDA_High;
    else
       SDA_Low; //SDA在SCL为低的时候进行变化
    delay(100);
    SCL_High; //然后SCL变高，SDA保持不变
    delay(200);
    SCL_Low; //SCL变低，等待下一个数据
    outdata=outdata<<1;
  }
    //delay(100);
    SDA_IN_Config();//设置SDA为输入
    delay(100);
    SCL_High;//SCL变高，等待ACK信号
    //delay(100);
}

inline u8 data_receive(void)
{
  u8 indata=0x00; 
  u8 i;
  SDA_IN_Config();
  for(i=0;i<8;i++)
  {
    indata = indata<<1;
    delay(200);
    SCL_High; //SCL为高时接收数据
    if(SCCB_SDA_GPIO->IDR & SCCB_SDA_PIN)
      indata=indata+1;  
    delay(200);
    SCL_Low;
  }
    SDA_OUT_Config();
    SDA_High;
    delay(200);
    SCL_High; //将SCL拉高等待应答
  return indata;  
}

void SCCB_WriteByte(u8 reg_addr,u8 data)
{
   I2C_Stop();
   delay(200);
   I2C_Start();
   data_trans(0x42);//发送从机地址
   while(ACK_STATE);//等待应答信号
   delay(200);
   SDA_OUT_Config(); 
   SCL_Low;
   
   data_trans(reg_addr);//发送寄存器地址
   while(ACK_STATE);//等待应答信号
   delay(200);
   SDA_OUT_Config(); 
   SCL_Low;
   
   data_trans(data);//发送寄存器数据
   while(ACK_STATE);
   delay(200);
   SCL_Low;
   SDA_OUT_Config();
   I2C_Stop();
}

u8 SCCB_ReadByte(u8 reg_addr)
{   
    u8 temp_data;
    I2C_Stop();
    delay(200);
    I2C_Start();
    data_trans(0x43);//发送从机地址,读操作
    while(ACK_STATE);//等待应带信号
    delay(200);
    SCL_Low;
    //SDA_OUT_Config(); 
     
    temp_data=data_receive();
    //while(ACK_STATE);
    delay(200);
    SDA_OUT_Config();
    I2C_Stop();
    return (temp_data);
}
