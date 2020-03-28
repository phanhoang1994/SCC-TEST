######################################################################################
# GNU GCC ARM Embeded Toolchain base directories and binaries
######################################################################################
GCC_BASE = E:/Toolchains/GNU_GCC_ARM/4.7/
GCC_BIN = $(GCC_BASE)bin/
GCC_LIB = $(GCC_BASE)arm-none-eabi/lib/
GCC_INC = $(GCC_BASE)arm-none-eabi/include/
AS = $(GCC_BIN)arm-none-eabi-as
CC = $(GCC_BIN)arm-none-eabi-gcc
CPP = $(GCC_BIN)arm-none-eabi-g++
LD = $(GCC_BIN)arm-none-eabi-gcc
OBJCOPY = $(GCC_BIN)arm-none-eabi-objcopy
 
#******************************************************************************
#
# Makefile - Rules for building the scc210 example.
#
# Copyright (c) 2007-2011 Texas Instruments Incorporated.  All rights reserved.
# Software License Agreement
# 
# Texas Instruments (TI) is supplying this software for use solely and
# exclusively on TI's microcontroller products. The software is owned by
# TI and/or its suppliers, and is protected under applicable copyright
# laws. You may not combine this software with "viral" open-source
# software in order to form a larger program.
# 
# THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
# NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
# NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
# CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
# DAMAGES, FOR ANY REASON WHATSOEVER.
# 
# This is part of revision 6852 of the EK-LM3S2965 Firmware Package.
#
#******************************************************************************

#
# Defines the part type that this project uses.
#
PART=LM3S2965

#
# The base directory for StellarisWare.
#
ROOT=../..

#
# Include the common make definitions.
#
include ${ROOT}/makedefs

#
# Where to find source files that do not live in this directory.
#
VPATH=../drivers

#
# Where to find header files that do not live in the source directory.
#
IPATH=..
IPATH+=../..

#
# The default rule, which causes the scc210 example to be built.
#
all: ${COMPILER}
all: ${COMPILER}/scc210.axf

#
# The rule to clean out all the build products.
#
clean:
	@rm -rf ${COMPILER} ${wildcard *~}

#
# The rule to create the target directory.
#
${COMPILER}:
	@mkdir ${COMPILER}

#
# Rules for building the scc210 example.
#
#${COMPILER}/scc210.axf: ${COMPILER}/uart1.o
${COMPILER}/scc210.axf: ${COMPILER}/can.o
${COMPILER}/scc210.axf: ${COMPILER}/function.o
${COMPILER}/scc210.axf: ${COMPILER}/sysclock.o
${COMPILER}/scc210.axf: ${COMPILER}/main.o
${COMPILER}/scc210.axf: ${COMPILER}/startup_${COMPILER}.o
${COMPILER}/scc210.axf: ${ROOT}/driverlib/${COMPILER}/libdriver.a
${COMPILER}/scc210.axf: scc210.ld
SCATTERgcc_scc210=scc210.ld
ENTRY_scc210=ResetISR

#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif
