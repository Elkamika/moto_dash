/*
 * Copyright (c) 2026 Michael Randrianantenaina
 * SPDX-License-Identifier: MIT
 *
 * Part of "Fuel Dashboard using Motorola C123" - see LICENSE and README.md.
 */

#ifndef MEMORY_H
#define MEMORY_H


static inline void read32(volatile uint32_t *reg, 
									uint32_t *ret)
{
	*ret = *reg;
}

static inline void write32(volatile unsigned int *reg, 
									unsigned int val)
{
	*reg = val;
}

static inline void readb(volatile unsigned char *reg, 
						unsigned char *ret)
{

	*ret = *reg;
}

static inline void writeb(volatile unsigned char *reg, 
										unsigned char val)
{
	*reg = val;
}

static inline void read16(volatile unsigned short *reg, 
									unsigned short *ret)
{

	*ret = *reg;
}

static inline void write16(volatile unsigned short *reg, 
									unsigned short val)
{
	*reg = val;
}



static void __memset(void *ptr, int c, uint32_t len)
{
    int i;
    register char *p = (char *) ptr;
    for (i = 0; i < len; i++) {
        p[i] = c;
    }
}

#endif