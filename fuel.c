/*
 * Copyright (c) 2026 Michael Randrianantenaina
 * SPDX-License-Identifier: MIT
 *
 * Part of "Fuel Dashboard using Motorola C123" - see LICENSE and README.md.
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "util.h"
#include "memory.h"
#include "font.h"


/** I2C register mapping **/
#define DEVICE_REG				(void *)0xFFFE2800
#define ADDRESS_REG				(void *)0xFFFE2801
#define DATA_WR_REG 			(void *)0xFFFE2802
#define DATA_RD_REG 			(void *)0xFFFE2803
#define CMD_REG					(void *)0xFFFE2804
#define CONF_FIFO_REG			(void *)0xFFFE2805
#define CONF_CLK_REG			(void *)0xFFFE2806
#define CONF_CLK_FUNC_REF 		(void *)0xFFFE2807
#define STATUS_FIFO_REG 		(void *)0xFFFE2808
#define I2C_STATUS          	(void *)0xFFFE2809

/** PWL Register **/
#define PWL_LEVEL_REG 			(void *)0xFFFE8000
#define PWL_CTRL_REG  			(void *)0xFFFE8001

#define ASIC_REG 				(void *)0xFFFEF008

#define IO_CONF_REG  			(void *)0xFFFEF00A
#define CNTL_RST_2 				(void *)0xFFFFFD04
#define IO_SELECTION_16 		(void *)0xFFFEF00A
#define IO_CNTL_16 				(void *)0xFFFE4804
#define ARMIO_LATCH_OUT_16      (void *)0xFFFE4802

#define LVL_BRIGTHER 			0xff
#define LVL_MEDIUM 	 			0x7f
#define LVL_LOW      			0x55
#define LVL_DARKER    			0x0


#define SPI_REG_SET1 		(void *) 0xFFFE3000
#define SPI_REG_SET2 		(void *) 0xFFFE3002
#define SPI_REG_STATUS 		(void *) 0xFFFE3006
#define SPI_REG_CTRL 		(void *) 0xFFFE3004

#define SPI_REG_TX_LSB 		(void *) 0xFFFE3008
#define SPI_REG_TX_MSB 		(void *) 0xFFFE300A

#define SPI_REG_RX_LSB 		(void *) 0xFFFE300C
#define SPI_REG_RX_MSB 		(void *) 0xFFFE300E

#define PAGE_0 				0b01
#define PAGE_1 				0b10

#define RST_EN              0x1

#define VRPC_STATUS__ 		31
#define TOGGLE_REG_1__ 		4
#define TOGGLE_REG_2__ 		5
#define POWERDOWN_REG 		9
#define MADC_STATUS__ 		24
#define MADC_CTRL__ 		13
#define BCI_CTL1__ 			28
#define VBAT_REG__ 			15
#define VCHG_REG__ 			16
#define INTERRUPT_STS__ 	27

#include "i2c.h"


 void backligth_on(uint8_t level) 
{
		uint16_t reg = 0x0;

		read16(ASIC_REG, &reg);
		/* Bit 4 in ASIC reg enable the PWL (Ligth) */
		write16(ASIC_REG, reg |= 1 << 4);
		writeb(PWL_LEVEL_REG, level);
		/** Enable blacklight **/
		writeb(PWL_CTRL_REG, 0x1);
}

static void backligth_off()
{
		uint16_t reg = 0x0;

		read16(ASIC_REG, &reg);
		/* Bit 4 in ASIC reg enable the PWL (Ligth) */
		write16(ASIC_REG, reg &= ~(1 << 4));
		/** Disable the clock **/
		writeb(PWL_CTRL_REG, 0x0);
		writeb(PWL_LEVEL_REG, LVL_DARKER);
}

 void backlight_blink(uint8_t count)
{
		for (int i = 0; i < count; i++) {
			backligth_on(LVL_BRIGTHER);
			sleep(600);
			backligth_on(LVL_DARKER);
			sleep(600);
		}	
}

static  void buzzer_off()
{
		uint16_t reg = 0x0;
		read16(ASIC_REG, &reg);
		write16(ASIC_REG, reg &= ~(1 << 5));
}

static  void i2c_pins_enable()
{
		uint16_t reg = 0x0;

		read16(ASIC_REG, &reg);
		reg |= 1 << 7; /* clock of I2C (SCL) */
		reg |= 1 << 12; /* data of I2C (SDA) */
		write16(ASIC_REG, reg);
}

static inline bool i2c_busy(void)
{
		uint8_t status = 0x0;
		readb(I2C_STATUS, &status);
		return ((status & (1 << 2)) != 0);
}

static  void lcd_reset_disable(void)
{
		uint8_t reg = 0x0;

		readb(CNTL_RST_2, &reg);
		reg = reg & ~(1 << 2);
		writeb(CNTL_RST_2, reg);
}

static  void lcd_reset_enable(void)
{
		uint8_t reg = 0x0;
		readb(CNTL_RST_2, &reg);
		writeb(CNTL_RST_2, reg |= (1 << 2));
}

static void arm_gpio_out_set(uint8_t pos, uint8_t value)
{
		uint16_t reg = 0x0;

		/* SET ASIC MUX PIN to I/O 3 */
		read16(ASIC_REG, &reg);
		write16(ASIC_REG, reg & ~(1 << 10));

		/* Configure GPIO N DIRECTION as OUTPUT */
		read16(IO_CNTL_16, &reg);
		/* Clear [1], 0 mean OUTPUT */
		write16(IO_CNTL_16, reg & ~(1 << pos));

		/* SET GPIO N to HIGH [1] or LOW [0] */
		read16(ARMIO_LATCH_OUT_16, &reg);
		if (value == 1)
			reg  = reg | (1 << pos);
		else
			reg  = reg & ~(1 << pos);
		write16(ARMIO_LATCH_OUT_16, reg);
}

static void lcd_reset_gpio_ctrl(uint8_t MODE)
{	
		uint16_t reg = 0x0;

		read16(IO_SELECTION_16, &reg);
		write16(IO_SELECTION_16, reg | (1 << 3)); /* 1 = I/O(7) */

		/* Configure GPIO 7 DIRECTION as OUTPUT */
		read16(IO_CNTL_16, &reg);
		/* Clear [1], 0 mean OUTPUT */
		write16(IO_CNTL_16, reg & ~(1 << 7));
		
		if (MODE == RST_EN) {
			/* SET GPIO 7 to HIGH [1] to take LCD out of reset */
			read16(ARMIO_LATCH_OUT_16, &reg);
			write16(ARMIO_LATCH_OUT_16, reg & ~(1 << 7));
		} else {
			/* SET GPIO 7 to HIGH [1] to take LCD out of reset */
			read16(ARMIO_LATCH_OUT_16, &reg);
			write16(ARMIO_LATCH_OUT_16, reg | (1 << 7));
		}
}

static  void i2c_freq_change(void)
{
		writeb(CONF_CLK_REG, 0x4);
		writeb(CONF_CLK_FUNC_REF, 0xA);
}

static inline void i2c_devaddr_set(uint8_t address)
{
		writeb(DEVICE_REG, address);
}

#define SITRONIX_DEVICE_ADDRESS 0x3C
#define SITRONIX_PAGE_NB 		0x09
#define SITRONIX_WIDTH 			102

static void stronix_clear_display()
{	
		uint8_t regbyte = 0x0;

		i2c_pins_enable();
		/* Set SCL clock to 100kHz */
		i2c_freq_change();
	
		writeb(CMD_REG, 0b000010);
	
		writeb(DEVICE_REG, SITRONIX_DEVICE_ADDRESS);
		writeb(ADDRESS_REG, 0x0);
		writeb(CONF_FIFO_REG, 0x4);

		/* Function Set */
		writeb(DATA_WR_REG, 0b00100001);
		/* Set bias system */
		writeb(DATA_WR_REG, 0b00010010);
		/* S/W internal register initial */
		writeb(DATA_WR_REG, 0b00001110);
		writeb(DATA_WR_REG, 0b00010010);
		/* Set booster 2X */
		writeb(DATA_WR_REG, 0b00001000);

		/* start the i2c transmission  */
		readb(CMD_REG, &regbyte);
		writeb(CMD_REG, regbyte |= (1 << 2));
		
		while (i2c_busy()) {}

		if (i2c_bus_error_data_present())
			backlight_blink(2);
		if (i2c_bus_error_device_present())
			backlight_blink(2);

		/* Write device address */
		writeb(DEVICE_REG, 0x3C);
		writeb(ADDRESS_REG, 0x0);

		/* Set the FIFO size */
		writeb(CONF_FIFO_REG, 0x5);

		/* Set VOP*/
		writeb(DATA_WR_REG, 0b10110010);
		/* Set booster 4X */
		writeb(DATA_WR_REG, 0b00001010);
		/* Function Set */
		writeb(DATA_WR_REG, 0b00100000);
		/* Extended display control  */
		writeb(DATA_WR_REG, 0b00101000);
		/* Set VLCD range  */
		writeb(DATA_WR_REG, 0b00010001);
		/* Display control. */
		writeb(DATA_WR_REG, 0b00001100);
		
		/* start the i2c transmission  **/
		readb(CMD_REG, &regbyte);
		writeb(CMD_REG, regbyte |= (1 << 2));

		while (i2c_busy()) {}
		
		if (i2c_bus_error_data_present())
			backlight_blink(2);
		if (i2c_bus_error_device_present())
			backlight_blink(2);

		/* Write device address */
		writeb(DEVICE_REG, 0x3C);
		/* Set the FIFO size */
		writeb(CONF_FIFO_REG, 0x0);

		/* Clear the display */
		for (int y = 0; y < SITRONIX_PAGE_NB; y++) {
			for (int x = 0; x < SITRONIX_WIDTH; x++) {

				regbyte = 0;
				writeb(ADDRESS_REG, 0b01000000);
				/* Write data*/
				writeb(DATA_WR_REG, 0x0);

				/* start the i2c transmission  */
				readb(CMD_REG, &regbyte);
				writeb(CMD_REG, regbyte |= (1 << 2));
				
				while (i2c_busy()) {}

				if (i2c_bus_error_data_present())
					backlight_blink(2);
				if (i2c_bus_error_device_present())
					backlight_blink(2);
			}
		}
}


static void stronix_position_set(uint8_t x, uint8_t y)
{
		uint8_t regbyte = 0x0;

		/* Write device address */
		writeb(DEVICE_REG, 0x3C);
		/* Set the FIFO size */
		writeb(CONF_FIFO_REG, 5);

		/* SET Co | INSTRUCTION */
		writeb(ADDRESS_REG, 0b10000000);
		/* X ADRESS */
		writeb(DATA_WR_REG, 0b10000000 | x);
		/* SET Co | INSTRUCTION */
		writeb(DATA_WR_REG, 0b10000000);
		/* Y ADRESS */
		writeb(DATA_WR_REG, 0b01000000 | y);
		/* SET Co | INSTRUCTION */
		writeb(DATA_WR_REG, 0b10000000);
		/* Function Set */
		writeb(DATA_WR_REG, 0b00100000);

		/* CLEARED Co | DATA RAM */
		writeb(DATA_WR_REG, 0b01000000);

		/* start the i2c transmission  */
		readb(CMD_REG, &regbyte);
		writeb(CMD_REG, regbyte |= (1 << 2));
		while (i2c_busy()) {}
}

static void stronix_print(char ascii)
{	
		uint8_t regbyte = 0x0;
		/* Set the FIFO size */
		writeb(CONF_FIFO_REG, 7);
		/* CLEARED Co | DATA RAM */
		writeb(ADDRESS_REG, 0b01000000);

		for (volatile int i = 0; i < 8; i++)
			writeb(DATA_WR_REG, ascii_array_8x8_bold[ascii][i]);
		
		/* start the i2c transmission  */
		readb(CMD_REG, &regbyte);
		writeb(CMD_REG, regbyte |= (1 << 2));
		while (i2c_busy()) {}
}

	
static void sitronix_print_raw(uint8_t byte)
{	
		uint8_t regbyte = 0x0;
		/* Set the FIFO size */
		writeb(CONF_FIFO_REG, 0);
		/* CLEARED Co | DATA RAM */
		writeb(ADDRESS_REG, 0b01000000);
		writeb(DATA_WR_REG, byte);

		readb(CMD_REG, &regbyte);
		writeb(CMD_REG, regbyte |= (1 << 2));
		while (i2c_busy()) {}
}

static inline char digit_to_ascii(uint8_t digit)
{
		return '0' + digit;
}

static char ascii_digit[3] = {'0'};

static void nb_to_ascii(uint8_t nb)
{
		uint8_t remainder = 0, quotient = 0;
		uint8_t dividend = 0;

		dividend = nb / 10;
		remainder = nb % 10;
		ascii_digit[2] = digit_to_ascii(remainder);

		remainder = dividend % 10;
		dividend = dividend / 10;
		ascii_digit[1] = digit_to_ascii(remainder);

		remainder = dividend % 10;
		ascii_digit[0] = digit_to_ascii(remainder);
}

static void iota_spi_mcsp_init (void)
{
		uint16_t spi_regset_one = 0, spi_regset_two = 0;
		uint16_t spi_status = 0, spi_reg_ctrl = 0;
		uint16_t spi_reg_rx = 0x0, spi_reg_tx = 0x0;
		uint16_t asic_reg = 0x0, ioconf = 0;

		read16(ASIC_REG, &asic_reg);
		asic_reg |= 1 << 9; /* clock of SPI */
		write16(ASIC_REG, asic_reg);
	
		read16(IO_CONF_REG, &ioconf);
	
		/* Divide only by 1 so 13Mhz */
		read16(SPI_REG_SET1, &spi_regset_one);
		spi_regset_one = spi_regset_one & ~(0b1110);
		spi_regset_one = spi_regset_one | 0b000 << 1;
		write16(SPI_REG_SET1, spi_regset_one);

		/* Enabe the clock */
		read16(SPI_REG_SET1, &spi_regset_one);
		spi_regset_one = spi_regset_one & ~(0b1);
		spi_regset_one = spi_regset_one | 1 << 0;
		write16(SPI_REG_SET1, spi_regset_one);

		/* Clock and Enable signal config */
		write16(SPI_REG_SET2, 0b0 << 10 | 0b0 << 5 | 0b0);
		write16(SPI_REG_CTRL, 0x0);

		read16(SPI_REG_CTRL, &spi_reg_ctrl);
		spi_reg_ctrl = spi_reg_ctrl & ~(0b1111100);
		spi_reg_ctrl = spi_reg_ctrl | 0b01111 << 2;
		spi_reg_ctrl = spi_reg_ctrl & ~(0b1110000000);
		spi_reg_ctrl = spi_reg_ctrl | 0 << 7;
		write16(SPI_REG_CTRL, spi_reg_ctrl);
}

static void iota_spi_mcsp_page_enable (uint8_t PAGE)
{
		uint16_t spi_reg_ctrl = 0;

		/* Enable Page 0 for the MCU */
		read16(SPI_REG_CTRL, &spi_reg_ctrl);
		spi_reg_ctrl = spi_reg_ctrl & ~(0b11);
		spi_reg_ctrl = spi_reg_ctrl | 0b1 << 1;
		
		/* Write 1 to page selec reg */
		write16(SPI_REG_TX_MSB, PAGE << 6 | 0b1 << 1 | 0);
		sleep(10);
		write16(SPI_REG_CTRL, spi_reg_ctrl);
		sleep(10);
}

static void iota_spi_mcsp_write (uint8_t ADDRESS, uint16_t VALUE)
{
		uint16_t spi_reg_ctrl = 0;
		uint16_t spi_reg_rx = 0x0;

		read16(SPI_REG_CTRL, &spi_reg_ctrl);
		spi_reg_ctrl = spi_reg_ctrl & ~(0b11);
		spi_reg_ctrl = spi_reg_ctrl | 0b1 << 1;
		write16(SPI_REG_TX_MSB, VALUE << 6 | ADDRESS << 1 | 0);
		sleep(10);
		write16(SPI_REG_CTRL, spi_reg_ctrl);
		sleep(10);
}

static uint16_t iota_spi_mcsp_read(uint8_t ADDRESS)
{
		uint16_t spi_reg_ctrl = 0;
		uint16_t spi_reg_rx = 0x0;

		read16(SPI_REG_CTRL, &spi_reg_ctrl);
		spi_reg_ctrl = spi_reg_ctrl & ~(0b11);
		spi_reg_ctrl = spi_reg_ctrl | 0b1 << 0;

		write16(SPI_REG_TX_MSB,  ADDRESS << 1 | 1);
		sleep(10);
		write16(SPI_REG_CTRL, spi_reg_ctrl);
		sleep(10);

		/* Dummy write to get the actual response from iota*/
		write16(SPI_REG_TX_MSB,  0);
		sleep(10);
		write16(SPI_REG_CTRL, spi_reg_ctrl);
		sleep(10);

		read16(SPI_REG_RX_LSB, &spi_reg_rx);
		return (spi_reg_rx >> 6);
}

static void iota_spi_mcsp_adc_init (void)
{
		uint16_t iota_reg = 0x0;
		iota_spi_mcsp_page_enable(PAGE_0);

		/* Enable 13Mhz Clock for IOTA */
		iota_spi_mcsp_write(TOGGLE_REG_2__, 0x0);
		iota_reg = iota_spi_mcsp_read(TOGGLE_REG_2__);
		/* Enable 13Mhz and ADC always on even after a conversion */
		iota_reg = iota_reg | 1 << 3;	
		iota_reg = iota_reg | 1 << 1;
		iota_spi_mcsp_write(TOGGLE_REG_2__, iota_reg);

		/* Enable MADC */
		iota_spi_mcsp_write(TOGGLE_REG_1__, 0x0);
		iota_reg = iota_spi_mcsp_read(TOGGLE_REG_1__);
		iota_reg = iota_reg | 1 << 9;
		iota_spi_mcsp_write(TOGGLE_REG_1__, iota_reg);
}

static uint16_t iota_read_battery_voltage (void)
{
		uint16_t iota_reg = 0x0;
		iota_spi_mcsp_page_enable(PAGE_0);

		/* SELECT RESISTIVE DIV FOR BATT */
		iota_spi_mcsp_write(BCI_CTL1__, 0x0);
		iota_reg = iota_spi_mcsp_read(BCI_CTL1__);
		iota_reg = iota_reg | 1 << 0;
		iota_spi_mcsp_write(BCI_CTL1__, iota_reg);

		/* SELECT BATT VOLTAGE FOR THE ADC Conversion */
		iota_spi_mcsp_write(MADC_CTRL__, 0x0);
		iota_reg = iota_spi_mcsp_read(MADC_CTRL__);
		iota_reg = iota_reg | 1 << 0;
		iota_spi_mcsp_write(MADC_CTRL__, iota_reg);

		iota_spi_mcsp_write(VCHG_REG__, 0x0);

		while (iota_spi_mcsp_read(MADC_STATUS__))
		{	
		}

		iota_reg = iota_spi_mcsp_read(VBAT_REG__);
		return iota_reg ? iota_reg : 0;
} 

static uint16_t iota_read_charger_voltage (void)
{
		uint16_t iota_reg = 0x0;
		iota_spi_mcsp_page_enable(PAGE_0);

		/* SELECT BATT VOLTAGE FOR THE ADC Conversion */
		iota_spi_mcsp_write(MADC_CTRL__, 0x0);
		iota_reg = iota_spi_mcsp_read(MADC_CTRL__);
		iota_reg = iota_reg | 1 << 1;
		iota_spi_mcsp_write(MADC_CTRL__, iota_reg);

		iota_spi_mcsp_write(VBAT_REG__, 0x0);
		sleep(5);
		while (iota_spi_mcsp_read(MADC_STATUS__))
		{	
		}

		iota_reg = iota_spi_mcsp_read(VCHG_REG__);
		return iota_reg ? iota_reg : 0;
} 

#include "fuel_drawing.h"
#define CTRL_CLK 			  (void *)0xFFFFFD02
#define KBC_REG_16            (void *)0xFFFE480C
#define KBD_GPIO_INT_16       (void *)0xFFFE4816

static uint8_t backlight_state = 0x0;

static float CONSTANTE_BATT = 0.006843;
static float CONSTANTE_CHG = 0.008545;
static float CONSTANTE_20V = 0.034221;
static float CONSTANTE_20V_by3 = 0.025664;
static float CONSTANT_BATT20 = 0.027383;
static float CONSTANTE_20V_by3_5 = 0.02933;


void mainloop(void) 
{
        uint16_t battvoltage = 0, chagvoltage = 0;
        uint8_t V_IN_CHG = 0, V_IN_BATT = 0;
        uint8_t counter = 0;
        uint16_t reg = 0x0;
        uint8_t regb = 0;

        float voltage_float = 0, previous_voltage = 0;
        int x = 0;

        /* Put the MCU into 26Mhz Clock speed  */
        readb(CTRL_CLK, &regb);
        regb = regb & ~(1 << 6);
        writeb(CTRL_CLK, regb);

        backligth_on(0x7f);

   		/* Drive Keyboard Column LOW for backlight CTRL*/
		write16(KBC_REG_16, 0);

        lcd_reset_gpio_ctrl(!RST_EN);

        iota_spi_mcsp_init();
        iota_spi_mcsp_page_enable(PAGE_0);

        iota_spi_mcsp_adc_init();
        stronix_clear_display();
        fuel_logo_temp_drawing();
        fuel_tank_full_draw();

       	voltage_initial_draw();
        stronix_position_set(25, 4);

        uint8_t level = 0;

    readvtg:
         
        battvoltage = iota_read_battery_voltage();
        chagvoltage = iota_read_charger_voltage();
        
        V_IN_CHG = (uint8_t)(chagvoltage * CONSTANTE_CHG);
        voltage_float = (chagvoltage * CONSTANTE_CHG);
        V_IN_BATT = (uint8_t)(battvoltage * CONSTANTE_BATT);

        read16(KBD_GPIO_INT_16, &reg);
        if (reg & (1 << 0)) {
        	if (backlight_state) {
        		backlight_state = 0;
        		backligth_on(0x00);
        	} else {
        		backlight_state = 1;
        		backligth_on(0x7f);
        	}
        }
        
        nb_to_ascii(V_IN_CHG);
        draw_battery_digits_16x32(40, 56, ascii_digit[1], ascii_digit[2]);
    	
    	if (voltage_float == previous_voltage)
    		goto readvtg;

    	previous_voltage = voltage_float;

        if (voltage_float < 3.2) {

                fuel_tank_empty_drawing();
                draw_fuel_digits_16x32(40, 56, '0', '0');
                
        } else if (voltage_float >= 3.2 && voltage_float <= 3.6) {

                fuel_tank_1litre_drawing();
                draw_fuel_digits_16x32(40, 56, '0', '1');

        } else if (voltage_float > 3.6 && voltage_float <= 4.0) {

                fuel_tank_1litre_5_drawing();
                draw_fuel_digits_16x32(40, 56, '0', '2');
               
        } else if (voltage_float > 4.0 && voltage_float <= 4.4) {

                fuel_tank_2litre_drawing();
                draw_fuel_digits_16x32(40, 56, '0', '3');
                
        } else if (voltage_float > 4.4 && voltage_float <= 4.8) {

        		fuel_tank_3litre_drawing();
        		draw_fuel_digits_16x32(40, 56, '0', '4');

        } else if (voltage_float > 4.8 && voltage_float <= 5.2) {

        		fuel_tank_3litre5_drawing();
        		draw_fuel_digits_16x32(40, 56, '0', '5');

        } else if (voltage_float > 5.2 && voltage_float <= 5.8) {

        		fuel_tank_5litre_drawing();
        		draw_fuel_digits_16x32(40, 56, '0', '6');
        }

        goto readvtg;
        while (1);
}