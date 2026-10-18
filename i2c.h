/*
 * Copyright (c) 2026 Michael Randrianantenaina
 * SPDX-License-Identifier: MIT
 *
 * Part of "Fuel Dashboard using Motorola C123" - see LICENSE and README.md.
 */

#ifndef CAL_I2C
#define CAL_I2C

static bool i2c_bus_error_data_present(void)
{
	uint8_t i2c_status = 0x0;
	readb((void *)I2C_STATUS, &i2c_status);

	if (i2c_status & (1 << 0))
		return true;
}		


static bool i2c_bus_error_device_present(void)
{
	uint8_t i2c_status = 0x0;
	readb((void *)I2C_STATUS, &i2c_status);

	if (i2c_status & (1 << 1))
		return true;
}		




#endif 
