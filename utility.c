/*
 * Copyright (c) 2026 Michael Randrianantenaina
 * SPDX-License-Identifier: MIT
 *
 * Part of "Fuel Dashboard using Motorola C123" - see LICENSE and README.md.
 */

#include <stdint.h>

static void function_void(uint16_t count)
{
	int a = 98, b = 8, resultat;

	for (int i = 0; i < count; ++i)
	{
		resultat = a++ + i + b++; 
	}
}

static void function_loop(uint16_t count)
{
	for (int i = 0; i < count; i++)
	{
		function_void(count);
	}
}

void sleep (uint16_t count){
	function_loop(count);
}