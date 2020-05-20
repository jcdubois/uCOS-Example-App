# General Makefile for linux
# Created by: Jean-Christophe Dubois

ARCH = ARM-Cortex-A
SUBARCH = ARMv7-A
TOOLCHAIN = GNU
CROSS_COMPILE = arm-linux-gnueabi-

###############################################################################
##  Standard commands
###############################################################################

CC=$(CROSS_COMPILE)gcc
AS=$(CROSS_COMPILE)gcc
AR=$(CROSS_COMPILE)ar
LD=$(CROSS_COMPILE)ld
NM=$(CROSS_COMPILE)nm
OBJDUMP=$(CROSS_COMPILE)@objdump
OBJCOPY=$(CROSS_COMPILE)@objcopy
ECHO=@echo
MKDIR=@mkdir -p
RMDIR=@rmdir --ignore-fail-on-non-empty
DEL=@/bin/rm -f
CP=@cp

###############################################################################
##  Source paths
###############################################################################

PROJ_ROOT = .
APP_ROOT = $(PROJ_ROOT)/NXP/MCIMX6UL-EVK/Ping/OS3
APP2_ROOT = $(PROJ_ROOT)/NXP/MCIMX6UL-EVK/Ping
BSP_ROOT = $(PROJ_ROOT)/NXP/BSP
OS_ROOT = $(PROJ_ROOT)/Micrium/Software/uCOS-III/Source
OS_PORT_ROOT = $(OS_ROOT)/../Ports/$(ARCH)/$(SUBARCH)
CPU_ROOT = $(PROJ_ROOT)/Micrium/Software/uC-CPU
LIB_ROOT = $(PROJ_ROOT)/Micrium/Software/uC-LIB
IP_ROOT = $(PROJ_ROOT)/Micrium/Software/uC-TCP-IP
IPv4_ROOT = $(PROJ_ROOT)/Micrium/Software/uC-TCP-IP/IP/IPv4
IPv6_ROOT = $(PROJ_ROOT)/Micrium/Software/uC-TCP-IP/IP/IPv6
IF_ROOT = $(PROJ_ROOT)/Micrium/Software/uC-TCP-IP/IF
COMMON_ROOT = $(PROJ_ROOT)/Micrium/Software/uC-Common
CPU_ROOT = $(PROJ_ROOT)/Micrium/Software/uC-CPU
DHCP_ROOT = $(PROJ_ROOT)/Micrium/Software/uC-DHCPc
OUTPUT = $(PROJ_ROOT)/output

###############################################################################
##  Commands Parameters
###############################################################################

PROJ_NAME =OS

CFLAGS    = -Os -Wall -Werror -mcpu=cortex-a7
CINCLUDES = -I$(APP_ROOT) -I$(OS_ROOT) -I$(OS_PORT_ROOT)/$(TOOLCHAIN)
CINCLUDES += -I$(CPU_ROOT) -I$(CPU_ROOT)/$(ARCH)/$(SUBARCH)/$(TOOLCHAIN)
CINCLUDES += -I$(APP_ROOT)/.. -I$(LIB_ROOT) -I$(IP_ROOT) -I$(OS_ROOT)/..
CINCLUDES += -I$(COMMON_ROOT) -I$(COMMON_ROOT)/KAL -I$(BSP_ROOT)/MCIMX6UL-EVK
CINCLUDES += -I$(DHCP_ROOT)
AINCLUDES = -I$(APP_ROOT),-I$(OS_ROOT),-I$(OS_PORT_ROOT)/$(TOOLCHAIN)
ASFLAGS   = -g -mcpu=cortex-a7
LDFLAGS   =

OS_SRC      := $(shell cd $(OS_ROOT); find . -name "os_*.c")
OS_PORT_SRC := $(shell cd $(OS_PORT_ROOT); find . -name "*.c") os_cpu_a_vfp-none.S
APP_SRC     := $(shell cd $(APP_ROOT); find . -name "*.c")
APP2_SRC    := app_tcpip.c net_cfg.c net_dev_cfg.c
IP_SRC      := $(shell cd $(IP_ROOT)/Source; find . -name "*.c")
IPv4_SRC    := $(shell cd $(IPv4_ROOT); find . -name "*.c")
IPv6_SRC    := $(shell cd $(IPv6_ROOT); find . -name "*.c")
IF_SRC      := $(shell cd $(IF_ROOT); find . -name "*.c")
PHY_SRC     := $(shell cd $(IP_ROOT)/Dev/Ether/PHY/KSZ9021r; find . -name "*.c")
MAC_SRC     := $(shell cd $(IP_ROOT)/Dev/Ether/MACNet; find . -name "*.c")
LIB_SRC     := $(shell cd $(LIB_ROOT); find . -name "*.c")
LIB_SRC     := $(shell cd $(LIB_ROOT); find . -name "*.c")
CPU_SRC     := cpu_core.c cpu_a.S
BSP_SRC     := $(shell cd $(BSP_ROOT)/MCIMX6UL-EVK/; find . -name "*.c")
BSP_INT_SRC := bsp_int_armv7a_gicv2.c
DHCP_SRC    := $(shell cd $(DHCP_ROOT)/Source; find . -name "*.c")
DHCP_OS_SRC := $(shell cd $(DHCP_ROOT)/OS/uCOS-III; find . -name "*.c")
COMMON_SRC  := kal.c

OBJS_C      :=$(addprefix $(OS_ROOT)/,  $(patsubst %.c,%.o,$(filter %.c,$(OS_SRC))))   \
              $(addprefix $(OS_PORT_ROOT)/, $(patsubst %.c,%.o,$(filter %.c,$(OS_PORT_SRC))))  \
              $(addprefix $(IP_ROOT)/Source/, $(patsubst %.c,%.o,$(filter %.c,$(IP_SRC))))  \
              $(addprefix $(IP_ROOT)/Dev/Ether/PHY/KSZ9021r/, $(patsubst %.c,%.o,$(filter %.c,$(PHY_SRC))))  \
              $(addprefix $(IP_ROOT)/Dev/Ether/MACNet/, $(patsubst %.c,%.o,$(filter %.c,$(MAC_SRC))))  \
              $(addprefix $(IPv4_ROOT)/, $(patsubst %.c,%.o,$(filter %.c,$(IPv4_SRC))))  \
              $(addprefix $(IPv6_ROOT)/, $(patsubst %.c,%.o,$(filter %.c,$(IPv6_SRC))))  \
              $(addprefix $(IF_ROOT)/, $(patsubst %.c,%.o,$(filter %.c,$(IF_SRC))))  \
              $(addprefix $(LIB_ROOT)/, $(patsubst %.c,%.o,$(filter %.c,$(LIB_SRC))))  \
              $(addprefix $(CPU_ROOT)/, $(patsubst %.c,%.o,$(filter %.c,$(CPU_SRC))))  \
              $(addprefix $(BSP_ROOT)/MCIMX6UL-EVK/, $(patsubst %.c,%.o,$(filter %.c,$(BSP_SRC))))  \
              $(addprefix $(BSP_ROOT)/Interrupts/, $(patsubst %.c,%.o,$(filter %.c,$(BSP_INT_SRC))))  \
              $(addprefix $(COMMON_ROOT)/KAL/uCOS-III/, $(patsubst %.c,%.o,$(filter %.c,$(COMMON_SRC))))  \
              $(addprefix $(APP2_ROOT)/, $(patsubst %.c,%.o,$(filter %.c,$(APP2_SRC))))  \
              $(addprefix $(DHCP_ROOT)/Source/, $(patsubst %.c,%.o,$(filter %.c,$(DHCP_SRC))))  \
              $(addprefix $(DHCP_ROOT)/OS/uCOS-III/, $(patsubst %.c,%.o,$(filter %.c,$(DHCP_OS_SRC))))  \
              $(addprefix $(APP_ROOT)/, $(patsubst %.c,%.o,$(filter %.c,$(APP_SRC))))
OBJS_S      :=$(addprefix $(OS_ROOT)/,  $(patsubst %.S,%.o,$(filter %.S,$(OS_SRC))))   \
              $(addprefix $(OS_PORT_ROOT)/$(TOOLCHAIN)/, $(patsubst %.S,%.o,$(filter %.S,$(OS_PORT_SRC))))  \
              $(addprefix $(CPU_ROOT)/$(ARCH)/$(SUBARCH)/$(TOOLCHAIN)/, $(patsubst %.S,%.o,$(filter %.S,$(CPU_SRC))))  \
              $(addprefix $(APP_ROOT)/, $(patsubst %.S,%.o,$(filter %.S,$(APP_SRC))))
OBJS_ALL    :=$(addprefix $(OUTPUT)/obj/,$(notdir $(OBJS_C)) $(notdir $(OBJS_S)))

###############################################################################
##  Pattern Rules
###############################################################################

%.o: %.c
	$(ECHO) '$(PROC)/GNU C Compiler building $(notdir $<)'
	$(MKDIR) $(OUTPUT)
	$(MKDIR) $(OUTPUT)/obj
	$(MKDIR) $(OUTPUT)/lst	
	$(CC) -c $(CFLAGS) $(CINCLUDES) -Wa,-alh="$(OUTPUT)/lst/$(notdir $(patsubst %.c,%.lst,$<))",$(AINCLUDES) -o "$(OUTPUT)/obj/$(notdir $@)" "$<"

%.o: %.asm
	$(ECHO) '$(PROC)/GNU ASM Compiler building $(notdir $<)'
	$(MKDIR) $(OUTPUT)
	$(MKDIR) $(OUTPUT)/obj
	$(AS) $(ASFLAGS) $(AINCLUDES) -o "$(OUTPUT)/obj/$(notdir $@)" "$<"

%.o: %.S
	$(ECHO) '$(PROC)/GNU C (ASM Pre-processing) Compiler building $(notdir $<)'
	$(MKDIR) $(OUTPUT)
	$(MKDIR) $(OUTPUT)/obj
	$(MKDIR) $(OUTPUT)/lst
	$(CC) -c $(CFLAGS) $(CINCLUDES) -Wa,-alh="$(OUTPUT)/lst/$(notdir $(patsubst %.s,%.lst,$<))",-L,$(AINCLUDES) -o "$(OUTPUT)/obj/$(notdir $@)" "$<"

###############################################################################
##  Build Rules
###############################################################################

all: build

build: $(OBJS_C) $(OBJS_ASM) $(OBJS_S)
	$(ECHO) '$(PROC)/GNU C Linker building target $(PROJ_NAME)'
	$(MKDIR) $(OUTPUT)
	$(CC) $(LDFLAGS) -o "$(OUTPUT)/$(PROJ_NAME).elf" $(OBJS_ALL)
	$(CP) "$(OUTPUT)/$(PROJ_NAME).elf" "$(PROJ_ROOT)/$(PROJ_NAME).elf"
	$(ECHO) 'Target $(PROJ_NAME) completed.'

clean:
	-$(DEL) $(OUTPUT)/obj/*.o $(OUTPUT)/lst/*.lst
	-$(DEL) "$(OUTPUT)/$(PROJ_NAME).elf"
	-$(DEL) "$(PROJ_ROOT)/$(PROJ_NAME).elf"
	-$(RMDIR) $(OUTPUT)/obj
	-$(RMDIR) $(OUTPUT)/lst
	-$(RMDIR) $(OUTPUT)
	$(ECHO) 'Target $(PROJ_NAME) clean.'
