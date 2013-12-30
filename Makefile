#======================================================================#
#Output files
EXECUTABLE=DCMI_OV7670.elf
BIN_IMAGE=DCMI_OV7670.bin

#======================================================================#
#Cross Compiler
CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

#======================================================================#
#Flags
CFLAGS=-g -mlittle-endian -mthumb
CFLAGS+=-mcpu=cortex-m4
CFLAGS+=-mfpu=fpv4-sp-d16 -mfloat-abi=softfp
#CFLAGS+=-Wall

CFLAGS+=-D USE_STDPERIPH_DRIVER\
        -D STM32F40XX \
        -D __FPU_PRESENT=1 \
        -D ARM_MATH_CM4

CFLAGS+=-I./
CFLAGS+=-I./program/
CFLAGS+=-I./Libraries/STM3240_EVAL/

#Flash
CFLAGS+=-Wl,-T,stm32_flash.ld

#======================================================================#
#Libraries

#Stm32 libraries
ST_LIB=./Libraries/STM32F4xx_StdPeriph_Driver

#STM3240_EVAL
EVAL=./Libraries/STM3240_EVAL

#CMSIS libraries
CFLAGS+=-I./Libraries/CMSIS/

#StdPeriph includes
CFLAGS+=-I$(ST_LIB)/inc


#======================================================================#
#Source code
SRC=./Libraries/CMSIS/system_stm32f4xx.c

#STM3240_EVAL
SRC+=$(EVAL)/fonts.c \
		$(EVAL)/lcd_log.c \
		$(EVAL)/stm324xg_eval.c \
		$(EVAL)/stm324xg_eval_audio_codec.c \
		$(EVAL)/stm324xg_eval_lcd.c 


#StdPeriph
SRC+=$(ST_LIB)/src/misc.c \
        $(ST_LIB)/src/stm32f4xx_rcc.c \
        $(ST_LIB)/src/stm32f4xx_dma.c \
        $(ST_LIB)/src/stm32f4xx_flash.c \
        $(ST_LIB)/src/stm32f4xx_gpio.c \
        $(ST_LIB)/src/stm32f4xx_usart.c \
        $(ST_LIB)/src/stm32f4xx_tim.c \
        $(ST_LIB)/src/stm32f4xx_spi.c \
        $(ST_LIB)/src/stm32f4xx_i2c.c \
        $(ST_LIB)/src/stm32f4xx_sdio.c \
        $(ST_LIB)/src/stm32f4xx_dcmi.c 

#Major programs
SRC+=./program/Camera_OV7670.c \
        ./program/SCCB_OV7670.c \
        ./program/Sensor.c \
        ./program/camera_api.c \
        ./program/ov7670_config.c \
        ./program/sccb_config.c \
	./program/stm32f4xx_it.c \
	./program/main.c

LDFLAGS+=-lm -lc -lgcc

#======================================================================#
#STM32 startup file
STARTUP=./Libraries/CMSIS/startup_stm32f4xx.s

#======================================================================#
#Make rules

#Make all
all:$(BIN_IMAGE)

$(BIN_IMAGE):$(EXECUTABLE)
	$(OBJCOPY) -O binary $^ $@

STARTUP_OBJ = startup_stm32f4xx.o 

$(STARTUP_OBJ): $(STARTUP) 
	$(CC) $(CFLAGS) $^ -c $(STARTUP)

$(EXECUTABLE):$(SRC) $(STARTUP_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

#Make clean
clean:
	rm -rf $(EXECUTABLE)
	rm -rf $(BIN_IMAGE)
#Make flash
flash:
	st-flash write $(BIN_IMAGE) 0x8000000

#======================================================================
.PHONY:all clean flash
