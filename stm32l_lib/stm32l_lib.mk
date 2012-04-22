# STM32L FWLib files.
STM32SRC = ${ROOTDIR}/stm32l_lib/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_adc.c \
		   ${ROOTDIR}/stm32l_lib/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_aes.c \
		   ${ROOTDIR}/stm32l_lib/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_aes_util.c \
           ${ROOTDIR}/stm32l_lib/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_comp.c \
           ${ROOTDIR}/stm32l_lib/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_crc.c \
           ${ROOTDIR}/stm32l_lib/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_dac.c \
           ${ROOTDIR}/stm32l_lib/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_dbgmcu.c \
           ${ROOTDIR}/stm32l_lib/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_dma.c \
           ${ROOTDIR}/stm32l_lib/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_exti.c \
           ${ROOTDIR}/stm32l_lib/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_flash.c \
           ${ROOTDIR}/stm32l_lib/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_flash_ramfunc.c \
           ${ROOTDIR}/stm32l_lib/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_fsmc.c \
           ${ROOTDIR}/stm32l_lib/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_gpio.c \
           ${ROOTDIR}/stm32l_lib/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_i2c.c \
           ${ROOTDIR}/stm32l_lib/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_iwdg.c \
           ${ROOTDIR}/stm32l_lib/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_lcd.c \
           ${ROOTDIR}/stm32l_lib/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_opamp.c \
           ${ROOTDIR}/stm32l_lib/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_pwr.c \
           ${ROOTDIR}/stm32l_lib/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_rcc.c \
           ${ROOTDIR}/stm32l_lib/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_rtc.c \
           ${ROOTDIR}/stm32l_lib/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_sdio.c \
           ${ROOTDIR}/stm32l_lib/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_spi.c \
           ${ROOTDIR}/stm32l_lib/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_syscfg.c \
           ${ROOTDIR}/stm32l_lib/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_tim.c \
           ${ROOTDIR}/stm32l_lib/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_usart.c \
           ${ROOTDIR}/stm32l_lib/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_wwdg.c \
           ${ROOTDIR}/stm32l_lib/STM32L1xx_StdPeriph_Driver/src/misc.c

STM32INC = ${ROOTDIR}/stm32l_lib
STM32INC += ${ROOTDIR}/stm32l_lib/CMSIS/Include
STM32INC += ${ROOTDIR}/stm32l_lib/CMSIS/Device/ST/STM32L1xx/Include
STM32INC += ${ROOTDIR}/stm32l_lib/STM32L1xx_StdPeriph_Driver/inc
