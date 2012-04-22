#+---------------------------------------------------------------------------
#
#  Copyright (c) 2012 Dmitry Lebed
#
#  File:       makefile
#
#  Contents:   makefile to build arm Cortex-M3 software with gcc
#
#----------------------------------------------------------------------------

#############  program name
	TARGET	= main

	# Programming options here
	STM32FLASH_BAUD = 230400

	STM32FLASH_OPTIONS = -v -g 0

	STM32FLASH_PORT = /dev/ttyUSB0
	
	#Path options

	ROOT_DIR			= .
	CONF_DIR 			= $(ROOT_DIR)/config
	PROJECT_DIR			= $(ROOT_DIR)/project
	FREERTOS_DIR 		= $(ROOT_DIR)/freertos
	STM32L_LIB_DIR		= $(ROOT_DIR)/stm32l_lib
	CMSIS_DIR			= $(STM32L_LIB_DIR)/CMSIS
	STDPERIPH_DIR		= $(STM32L_LIB_DIR)/STM32L1xx_StdPeriph_Driver
	
	CMSIS_DRIVER_DIR	= $(CMSIS_DIR)/Include

# program version
	VER_MAJOR	= 0
	VER_MINOR	= 1

	TOOL		= arm-none-eabi-

	OPTIMIZE	= -O2
	USE_LTO		= NO

# compile options 
	MCU			= cortex-m3
	CHIP		= STM32L1XX_MD
	
# Select family 
# STM32F10X_LD    : STM32 Low density devices
# STM32F10X_LD_VL : STM32 Low density Value Line devices
# CHIP		= STM32F10X_MD    #: STM32 Medium density devices
# STM32F10X_MD_VL : STM32 Medium density Value Line devices
# STM32F10X_HD    : STM32 High density devices
# STM32F10X_HD_VL : STM32 XL-density devices
# STM32F10X_CL    : STM32 Connectivity line devices
# STM32F10X_XL    : STM32 XL-density devices

	STARTUP 	= $(CONF_DIR)/startup_$(CHIP).s

#defines
	DEFS		= -D$(CHIP)
	DEFS		+= -DVER_MAJOR=$(VER_MAJOR)
	DEFS		+= -DVER_MINOR=$(VER_MINOR)

###########################################################
#  common part for all my cortex-m3 projects
###########################################################

	BASE		= .
	CC			= $(TOOL)gcc
	CXX			= $(TOOL)g++
	LD			= $(TOOL)g++
	AS			= $(CC) -x assembler-with-cpp
	OBJCOPY		= $(TOOL)objcopy
	OBJDUMP		= $(TOOL)objdump
	SIZE		= $(TOOL)size -d
	FLASHER		= openocd
	RM			= rm -f
	CP			= cp
	MD			= mkdir

	STM32FLASH_BIN = stm32blctl


#  dirs
	SRCDIR		= $(BASE)/src
	OBJDIR		= $(BASE)/obj
	EXEDIR		= $(BASE)/exe
	LSTDIR		= $(BASE)/lst
	PRJDIR		= $(BASE)/prj
	BAKDIR		= $(BASE)/bak

#files
	HEX		= $(EXEDIR)/$(TARGET).hex
	BIN		= $(EXEDIR)/$(TARGET).bin
	AXF		= $(EXEDIR)/$(TARGET).axf
	ELF		= $(EXEDIR)/$(TARGET).elf
	MAP		= $(LSTDIR)/$(TARGET).map
	LSS		= $(LSTDIR)/$(TARGET).lss
	OK		= $(EXEDIR)/$(TARGET).ok

	STM32FLASH_CMDLINE = -w $(HEX) $(STM32FLASH_OPTIONS) -b $(STM32FLASH_BAUD) $(STM32FLASH_PORT)

# linker script (chip dependent)
	LD_SCRIPT	= $(CONF_DIR)/stm32_flash.ld
 
# source directories (all *.c, *.cpp and *.s files included)
	DIRS	:= $(SRCDIR)
	DIRS	+= $(PROJECT_DIR)
	DIRS	+= $(CONF_DIR)
	DIRS	+= $(FREERTOS_DIR)
	DIRS	+= $(FREERTOS_DIR)/portable/GCC/ARM_CM3
	DIRS	+= $(FREERTOS_DIR)/include
#	DIRS	+= $(FREERTOS_DIR)/Demo/Common/include
	
	#STM32F1_DISCOVERY_DRIVER_DIR=../MyARMLib/STM32/STM32F4_discovery
	DIRS	+= $(CMSIS_DRIVER_DIR)
	DIRS	+= $(CMSIS_DIR)/Device/ST/STM32L1xx/Include
	DIRS	+= $(STDPERIPH_DIR)/src
	DIRS	+= $(STDPERIPH_DIR)/inc
	#DIRS	+= ../MyARMLib/STM32/STM32L1xx/include
	#DIRS	+= ../MyARMLib/STM32/STM32L1_discovery
	#DIRS	+= ../MyARMLib/STM32/STM32L1xx_StdPeriph_Driver/src
	#DIRS	+= ../MyARMLib/STM32/STM32L1xx_StdPeriph_Driver/inc
	#DIRS	+= ../MyARMLib/STM32/STM32_TouchSensing_Driver/src
	#DIRS	+= ../MyARMLib/STM32/STM32_TouchSensing_Driver/inc

#	DIRS	+= ../MyARMLib/FreeRTOS

# includes
	INCS	:= $(patsubst %, -I"%", $(DIRS))

# individual source files
	SRCS	:= 

#calc obj files list
	OBJS	:= $(SRCS)
	OBJS	+= $(wildcard $(addsuffix /*.cpp, $(DIRS)))
	OBJS	+= $(wildcard $(addsuffix /*.c, $(DIRS)))
	OBJS	+= $(wildcard $(addsuffix /*.S, $(DIRS)))
	
	#OBJS	+= $(FREERTOS_DIR)/Source/tasks.c
	#/port.c

	OBJS	:= $(notdir $(OBJS))
	OBJS	:= $(OBJS:.cpp=.o)
	OBJS	:= $(OBJS:.c=.o)
	OBJS	:= $(OBJS:.S=.o)
	OBJS	:= $(patsubst %, $(OBJDIR)/%, $(OBJS))

#files to archive
	ARCFILES	= \
		$(SRCDIR) \
		$(PRJDIR) \
		$(SCMDIR) \
		$(BASE)/makefile \
		$(BASE)/.cproject \
		$(BASE)/.project

# flags
	FLAGS	= -mcpu=$(MCU) -mthumb
	FLAGS	+= $(INCS)
	FLAGS	+= -MD 
	#-DGCC_ARMCM3
	FLAGS	+= $(DEFS) -DUSE_STDPERIPH_DRIVER
	FLAGS	+= -Wa,-adhlns=$(addprefix $(LSTDIR)/, $(notdir $(addsuffix .lst, $(basename $<))))

	AFLAGS	= $(FLAGS)

	CFLAGS	= $(FLAGS)
	CFLAGS	+= $(OPTIMIZE)
	CFLAGS	+= -std=gnu99
	CFLAGS	+= -DGCC_ARMCM3
	CFLAGS	+= -g
	CFLAGS	+= -ffunction-sections -fdata-sections
#	CFLAGS	+= -Wall -Wextra
#	CFLAGS	+= -Wimplicit -Wcast-align -Wpointer-arith -Wredundant-decls
#	CFLAGS	+= -Wshadow -Wcast-qual -Wcast-align -Wnested-externs -pedantic

	CXXFLAGS	= $(FLAGS)
	CXXFLAGS	+= $(OPTIMIZE)
	CXXFLAGS	+= -g
	CXXFLAGS	+= -fno-exceptions -fno-rtti
	CXXFLAGS	+= -ffunction-sections -fdata-sections
	CXXFLAGS	+= -fno-threadsafe-statics
	CXXFLAGS	+= -funsigned-bitfields -fshort-enums
	CXXFLAGS	+= -Wall -Wextra
	CXXFLAGS	+= -Winline
	CXXFLAGS	+= -Wpointer-arith -Wredundant-decls
	CXXFLAGS	+= -Wshadow -Wcast-qual -Wcast-align -pedantic

	LD_FLAGS	= -mcpu=$(MCU)
	LD_FLAGS	+= -mthumb
	LD_FLAGS	+= -nostartfiles 
	LD_FLAGS	+= -Wl,-Map="$(MAP)",--cref
	LD_FLAGS	+= -Wl,--gc-sections
	LD_FLAGS	+= -T$(LD_SCRIPT)

ifeq ($(USE_LTO),YES)
	CFLAGS		+= -flto
	CXXFLAGS	+= -flto
	LD_FLAGS	+= -flto $(OPTIMIZE)
endif

#openocd command-line

# debug level (d0..d3)
	oocd_params		= -d0
# interface and board/target settings (using the OOCD target-library here)
#	oocd_params		+= -c "fast enable"
	oocd_params		+= -f interface/arm-usb-ocd.cfg 
	oocd_params		+= -f board/stm32f10x_128k_eval.cfg
	oocd_params		+= -c init -c targets
	oocd_params_program	= $(oocd_params)
# commands to prepare flash-write
	oocd_params_program	+= -c "halt"
# flash-write and -verify
	oocd_params_program	+= -c "flash write_image erase $(ELF)"
	oocd_params_program	+= -c "verify_image $(ELF)"
# reset target
	oocd_params_program	+= -c "reset run"
# terminate OOCD after programming
	oocd_params_program	+= -c shutdown

	oocd_params_reset	= $(oocd_params)
	oocd_params_reset	+= -c "reset run"
	oocd_params_reset	+= -c shutdown

.SILENT :

.PHONY: all start dirs build clean program reset archive

############# targets

all : start dirs $(AXF) $(ELF) $(HEX) $(BIN) $(LSS) $(OK)

build: clean all

start:
	@echo --- building $(TARGET) $(OBJS)

$(LSS): $(ELF) makefile
	@echo --- making asm-lst...
#	@$(OBJDUMP) -dStC $(ELF) > $(LSS)
	@$(OBJDUMP) -dC $(ELF) > $(LSS)

$(OK): $(ELF)
	@$(SIZE) $(ELF)
	@echo "Errors: none"

$(AXF):	$(OBJS) makefile
	@echo --- linking... axf
	$(LD) $(OBJS) $(LIBS) $(LD_FLAGS) -o "$(AXF)"
	
$(ELF):	$(OBJS) makefile
	@echo --- linking... 
	$(LD) $(OBJS) $(LIBS) $(LD_FLAGS) -o "$(ELF)"

$(HEX): $(ELF)
	@echo --- make hex...
	@$(OBJCOPY) -O ihex $(ELF) $(HEX)

$(BIN): $(ELF)
	@echo --- make binary...
	@$(OBJCOPY) -O binary $(ELF) $(BIN)

program: $(ELF)
	@echo "Programming with OPENOCD"
	$(FLASHER) $(oocd_params_program)

serialprogram: $(HEX)
	@echo "Programming with STM32FLASH"
	$(STM32FLASH_BIN) $(STM32FLASH_CMDLINE)

reset:
	@echo Resetting device
	$(FLASHER) $(oocd_params_reset)

VPATH := $(DIRS)

$(OBJDIR)/%.o: %.cpp makefile
	@echo --- compiling $<... 
	@echo $(CXX) -c $(CXXFLAGS) -o $@ $< 
	$(CXX) -c $(CXXFLAGS) -o $@ $< 

$(OBJDIR)/%.o: %.c makefile
	@echo --- compiling $<... 
	@echo $(CC) -c $(CFLAGS) -o $@ $<
	$(CC) -c $(CFLAGS) -o $@ $<

$(OBJDIR)/%.o: %.S makefile
	@echo --- assembling $<...
	@echo $(AS) -c $(AFLAGS) -o $@ $<
	$(AS) -c $(AFLAGS) -o $@ $<

dirs: $(OBJDIR) $(EXEDIR) $(LSTDIR) $(BAKDIR)

$(OBJDIR):
	-@$(MD) $(OBJDIR)

$(EXEDIR):
	-@$(MD) $(EXEDIR)

$(LSTDIR):
	-@$(MD) $(LSTDIR)

$(BAKDIR):
	-@$(MD) $(BAKDIR)

clean:
	-@$(RM) $(OBJDIR)/*.d 2>/dev/null
	-@$(RM) $(OBJDIR)/*.o 2>/dev/null
	-@$(RM) $(LSTDIR)/*.lst 2>/dev/null
	-@$(RM) $(ELF)
	-@$(RM) $(HEX)
	-@$(RM) $(LSS)
	-@$(RM) $(MAP)

archive:
	@echo --- archiving...
	7z a $(BAKDIR)/$(TARGET)_`date +%Y-%m-%d,%H-%M-%S` $(ARCFILES)
	@echo --- done!

# dependencies
ifeq (,$(findstring build,$(MAKECMDGOALS)))
 ifeq (,$(findstring clean,$(MAKECMDGOALS)))
  ifeq (,$(findstring dirs,$(MAKECMDGOALS)))
  -include $(wildcard $(OBJDIR)/*.d) 
  endif
 endif
endif
