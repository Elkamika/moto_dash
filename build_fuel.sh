#!/bin/sh
# Copyright (c) 2026 Michael Randrianantenaina
# SPDX-License-Identifier: MIT

arm-none-eabi-as -mcpu=arm7tdmi -o start.o start.s
arm-none-eabi-gcc -mcpu=arm7tdmi -c  utility.c
arm-none-eabi-gcc -mcpu=arm7tdmi -c  fuel.c
arm-none-eabi-ld -Ttext=0x00800104 start.o  fuel.o utility.o /usr/lib/gcc/arm-none-eabi/13.2.1/libgcc.a -o firmware.elf
arm-none-eabi-objcopy -O binary firmware.elf firmware.bin
