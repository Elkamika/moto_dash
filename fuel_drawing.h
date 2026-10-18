/*
 * Copyright (c) 2026 Michael Randrianantenaina
 * SPDX-License-Identifier: MIT
 *
 * Part of "Fuel Dashboard using Motorola C123" - see LICENSE and README.md.
 */



static void fuel_logo_temp_drawing(void) {
        int x = 0;

        /*--------------FUEL LOGO PART1------------*/
        for (int w = 0; w < 32; w++) {

                stronix_position_set(0 + w, 0);
                sitronix_print_raw(fuel_logo_final_part1[x++]);

                stronix_position_set(0 + w, 1);
                sitronix_print_raw(fuel_logo_final_part1[x++]);

                stronix_position_set(0 + w, 2);
                sitronix_print_raw(fuel_logo_final_part1[x++]);

                stronix_position_set(0 + w, 3);
                sitronix_print_raw(fuel_logo_final_part1[x++]);

        }

        /*--------------FUEL LOGO PART2------------*/
        x = 0;
        for (int w = 0; w < 32; w++) {

                stronix_position_set(32 + w, 0);
                sitronix_print_raw(fuel_logo_final_part2[x++]);

                stronix_position_set(32 + w, 1);
                sitronix_print_raw(fuel_logo_final_part2[x++]);

                stronix_position_set(32 + w, 2);
                sitronix_print_raw(fuel_logo_final_part2[x++]);

                stronix_position_set(32 + w, 3);
                sitronix_print_raw(fuel_logo_final_part2[x++]);

        }

        /*--------------ENGINE LOGO PART2------------*/
        x = 0;
        for (int w = 0; w < 24; w++) {

                stronix_position_set(5 + w, 4);
                sitronix_print_raw(engine_temp_logo[x++]);

                stronix_position_set(5 + w, 5);
                sitronix_print_raw(engine_temp_logo[x++]);

                stronix_position_set(5 + w, 6);
                sitronix_print_raw(engine_temp_logo[x++]);

                stronix_position_set(5 + w, 7);
                sitronix_print_raw(engine_temp_logo[x++]);

        }

}
static void fuel_tank_1litre_drawing(void) {

        int x = 0;

        for (int w = 0; w < 24; w++) {

                stronix_position_set(71 + w, 4);
                sitronix_print_raw(fuel_tank_final_part2_1litre[x++]);

                stronix_position_set(71 + w, 5);
                sitronix_print_raw(fuel_tank_final_part2_1litre[x++]);

                stronix_position_set(71 + w, 6);
                sitronix_print_raw(fuel_tank_final_part2_1litre[x++]);

                stronix_position_set(71 + w, 7);
                sitronix_print_raw(fuel_tank_final_part2_1litre[x++]);

        }

        x = 0;
        for (int w = 0; w < 24; w++) {

                stronix_position_set(71 + w, 0);
                sitronix_print_raw(fuel_tank_final[x++]);

                stronix_position_set(71 + w, 1);
                sitronix_print_raw(fuel_tank_final[x++]);

                stronix_position_set(71 + w, 2);
                sitronix_print_raw(fuel_tank_final[x++]);

                stronix_position_set(71 + w, 3);
                sitronix_print_raw(fuel_tank_final[x++]);

        }
}

static void fuel_tank_1litre_5_drawing(void) {

        int x = 0;

        for (int w = 0; w < 24; w++) {

                stronix_position_set(71 + w, 4);
                sitronix_print_raw(fuel_tank_final_part2_1_5litre[x++]);

                stronix_position_set(71 + w, 5);
                sitronix_print_raw(fuel_tank_final_part2_1_5litre[x++]);

                stronix_position_set(71 + w, 6);
                sitronix_print_raw(fuel_tank_final_part2_1_5litre[x++]);

                stronix_position_set(71 + w, 7);
                sitronix_print_raw(fuel_tank_final_part2_1_5litre[x++]);

        }

        x = 0;
        for (int w = 0; w < 24; w++) {

                stronix_position_set(71 + w, 0);
                sitronix_print_raw(fuel_tank_final[x++]);

                stronix_position_set(71 + w, 1);
                sitronix_print_raw(fuel_tank_final[x++]);

                stronix_position_set(71 + w, 2);
                sitronix_print_raw(fuel_tank_final[x++]);

                stronix_position_set(71 + w, 3);
                sitronix_print_raw(fuel_tank_final[x++]);

        }
}

static void fuel_tank_2litre_drawing(void) {

        int x = 0;

        for (int w = 0; w < 24; w++) {

                stronix_position_set(71 + w, 4);
                sitronix_print_raw(fuel_tank_final_part2_2litre[x++]);

                stronix_position_set(71 + w, 5);
                sitronix_print_raw(fuel_tank_final_part2_2litre[x++]);

                stronix_position_set(71 + w, 6);
                sitronix_print_raw(fuel_tank_final_part2_2litre[x++]);

                stronix_position_set(71 + w, 7);
                sitronix_print_raw(fuel_tank_final_part2_2litre[x++]);

        }

        x = 0;
        for (int w = 0; w < 24; w++) {

                stronix_position_set(71 + w, 0);
                sitronix_print_raw(fuel_tank_final[x++]);

                stronix_position_set(71 + w, 1);
                sitronix_print_raw(fuel_tank_final[x++]);

                stronix_position_set(71 + w, 2);
                sitronix_print_raw(fuel_tank_final[x++]);

                stronix_position_set(71 + w, 3);
                sitronix_print_raw(fuel_tank_final[x++]);

        }
}

static void fuel_tank_3litre_drawing(void) {

        int x = 0;

        for (int w = 0; w < 24; w++) {

                stronix_position_set(71 + w, 4);
                sitronix_print_raw(fuel_tank_final_part2_3litre[x++]);

                stronix_position_set(71 + w, 5);
                sitronix_print_raw(fuel_tank_final_part2_3litre[x++]);

                stronix_position_set(71 + w, 6);
                sitronix_print_raw(fuel_tank_final_part2_3litre[x++]);

                stronix_position_set(71 + w, 7);
                sitronix_print_raw(fuel_tank_final_part2_3litre[x++]);

        }
        x = 0;
        for (int w = 0; w < 24; w++) {

                stronix_position_set(71 + w, 0);
                sitronix_print_raw(fuel_tank_final_part1_3litre[x++]);

                stronix_position_set(71 + w, 1);
                sitronix_print_raw(fuel_tank_final_part1_3litre[x++]);

                stronix_position_set(71 + w, 2);
                sitronix_print_raw(fuel_tank_final_part1_3litre[x++]);

                stronix_position_set(71 + w, 3);
                sitronix_print_raw(fuel_tank_final_part1_3litre[x++]);

        }
}

static void fuel_tank_3litre5_drawing(void)
{
        int x = 0;
        for (int w = 0; w < 24; w++) {

                stronix_position_set(71 + w, 0);
                sitronix_print_raw(fuel_tank_final_part1_3_5litre[x++]);

                stronix_position_set(71 + w, 1);
                sitronix_print_raw(fuel_tank_final_part1_3_5litre[x++]);

                stronix_position_set(71 + w, 2);
                sitronix_print_raw(fuel_tank_final_part1_3_5litre[x++]);

                stronix_position_set(71 + w, 3);
                sitronix_print_raw(fuel_tank_final_part1_3_5litre[x++]);
        }
}

static void fuel_tank_4litre_drawing(void)
{
        int x = 0;
        for (int w = 0; w < 24; w++) {

                stronix_position_set(71 + w, 0);
                sitronix_print_raw(fuel_tank_final_part1_3_5litre[x++]);

                stronix_position_set(71 + w, 1);
                sitronix_print_raw(fuel_tank_final_part1_3_5litre[x++]);

                stronix_position_set(71 + w, 2);
                sitronix_print_raw(fuel_tank_final_part1_3_5litre[x++]);

                stronix_position_set(71 + w, 3);
                sitronix_print_raw(fuel_tank_final_part1_3_5litre[x++]);
        }
}

static void fuel_tank_5litre_drawing(void)
{
        int x = 0;
        for (int w = 0; w < 24; w++) {

                stronix_position_set(71 + w, 0);
                sitronix_print_raw(fuel_tank_final_part1_4litre[x++]);

                stronix_position_set(71 + w, 1);
                sitronix_print_raw(fuel_tank_final_part1_4litre[x++]);

                stronix_position_set(71 + w, 2);
                sitronix_print_raw(fuel_tank_final_part1_4litre[x++]);

                stronix_position_set(71 + w, 3);
                sitronix_print_raw(fuel_tank_final_part1_4litre[x++]);

        }

        x = 0;
        for (int w = 0; w < 24; w++) {

                stronix_position_set(71 + w, 0);
                sitronix_print_raw(fuel_tank_final_part1_4_5litre[x++]);

                stronix_position_set(71 + w, 1);
                sitronix_print_raw(fuel_tank_final_part1_4_5litre[x++]);

                stronix_position_set(71 + w, 2);
                sitronix_print_raw(fuel_tank_final_part1_4_5litre[x++]);

                stronix_position_set(71 + w, 3);
                sitronix_print_raw(fuel_tank_final_part1_4_5litre[x++]);
        }


        x = 0;
        for (int w = 0; w < 24; w++) {

                stronix_position_set(71 + w, 0);
                sitronix_print_raw(fuel_tank_final_part1_5litre[x++]);

                stronix_position_set(71 + w, 1);
                sitronix_print_raw(fuel_tank_final_part1_5litre[x++]);

                stronix_position_set(71 + w, 2);
                sitronix_print_raw(fuel_tank_final_part1_5litre[x++]);

                stronix_position_set(71 + w, 3);
                sitronix_print_raw(fuel_tank_final_part1_5litre[x++]);

        }
}

static void fuel_tank_empty_drawing(void) {

        int x = 0;
        for (int w = 0; w < 24; w++) {

                stronix_position_set(71 + w, 0);
                sitronix_print_raw(fuel_tank_final[x++]);

                stronix_position_set(71 + w, 1);
                sitronix_print_raw(fuel_tank_final[x++]);

                stronix_position_set(71 + w, 2);
                sitronix_print_raw(fuel_tank_final[x++]);

                stronix_position_set(71 + w, 3);
                sitronix_print_raw(fuel_tank_final[x++]);

        }
        x = 0;
        for (int w = 0; w < 24; w++) {

                stronix_position_set(71 + w, 4);
                sitronix_print_raw(fuel_tank_final_part2[x++]);

                stronix_position_set(71 + w, 5);
                sitronix_print_raw(fuel_tank_final_part2[x++]);

                stronix_position_set(71 + w, 6);
                sitronix_print_raw(fuel_tank_final_part2[x++]);

                stronix_position_set(71 + w, 7);
                sitronix_print_raw(fuel_tank_final_part2[x++]);

        }
}


static void fuel_tank_full_draw (void)
{
        fuel_tank_empty_drawing();
        fuel_tank_1litre_drawing();
        fuel_tank_1litre_5_drawing();
        fuel_tank_2litre_drawing();
        fuel_tank_3litre_drawing();
        fuel_tank_3litre5_drawing();
        fuel_tank_4litre_drawing();
        fuel_tank_5litre_drawing();
}

/* *VERSION 2 using BAR as Fuel Level */

/* End of version BAR */

static void voltage_initial_draw (void)
{
        int  x = 0;
        for (int w = 0; w < 16; w++) {

                stronix_position_set(40 + w, 0);
                sitronix_print_raw(ascii_array_16x32_bold['0'][x++]);

                stronix_position_set(40 + w, 1);
                sitronix_print_raw(ascii_array_16x32_bold['0'][x++]);

                stronix_position_set(40 + w, 2);
                sitronix_print_raw(ascii_array_16x32_bold['0'][x++]);

                stronix_position_set(40 + w, 3);
                sitronix_print_raw(ascii_array_16x32_bold['0'][x++]);

        }

        x = 0;
        for (int w = 0; w < 16; w++) {

                stronix_position_set(56 + w, 0);
                sitronix_print_raw(ascii_array_16x32_bold['0'][x++]);

                stronix_position_set(56 + w, 1);
                sitronix_print_raw(ascii_array_16x32_bold['0'][x++]);

                stronix_position_set(56 + w, 2);
                sitronix_print_raw(ascii_array_16x32_bold['0'][x++]);

                stronix_position_set(56 + w, 3);
                sitronix_print_raw(ascii_array_16x32_bold['0'][x++]);

        }

        x = 0;
        for (int w = 0; w < 16; w++) {

                stronix_position_set(40 + w, 4);
                sitronix_print_raw(ascii_array_16x32_bold['0'][x++]);

                stronix_position_set(40 + w, 5);
                sitronix_print_raw(ascii_array_16x32_bold['0'][x++]);

                stronix_position_set(40 + w, 6);
                sitronix_print_raw(ascii_array_16x32_bold['0'][x++]);

                stronix_position_set(40 + w, 7);
                sitronix_print_raw(ascii_array_16x32_bold['0'][x++]);

        }

        x = 0;
        for (int w = 0; w < 16; w++) {

                stronix_position_set(56 + w, 4);
                sitronix_print_raw(ascii_array_16x32_bold['0'][x++]);

                stronix_position_set(56 + w, 5);
                sitronix_print_raw(ascii_array_16x32_bold['0'][x++]);

                stronix_position_set(56 + w, 6);
                sitronix_print_raw(ascii_array_16x32_bold['0'][x++]);

                stronix_position_set(56 + w, 7);
                sitronix_print_raw(ascii_array_16x32_bold['0'][x++]);

        }

}

static void draw_fuel_digits_16x32(uint8_t digit_left_x, uint8_t digit_right_x,
                                   uint8_t digit_left_value, uint8_t digit_right_value)
{
        int x = 0;

        for (int w = 0; w < 16; w++) {

                stronix_position_set(digit_left_x + w, 0);
                sitronix_print_raw(ascii_array_16x32_bold[digit_left_value][x++]);

                stronix_position_set(digit_left_x + w, 1);
                sitronix_print_raw(ascii_array_16x32_bold[digit_left_value][x++]);

                stronix_position_set(digit_left_x + w, 2);
                sitronix_print_raw(ascii_array_16x32_bold[digit_left_value][x++]);

                stronix_position_set(digit_left_x + w, 3);
                sitronix_print_raw(ascii_array_16x32_bold[digit_left_value][x++]);

        }

        x = 0;
        for (int w = 0; w < 16; w++) {

                stronix_position_set(digit_right_x + w, 0);
                sitronix_print_raw(ascii_array_16x32_bold[digit_right_value][x++]);

                stronix_position_set(digit_right_x + w, 1);
                sitronix_print_raw(ascii_array_16x32_bold[digit_right_value][x++]);

                stronix_position_set(digit_right_x + w, 2);
                sitronix_print_raw(ascii_array_16x32_bold[digit_right_value][x++]);

                stronix_position_set(digit_right_x + w, 3);
                sitronix_print_raw(ascii_array_16x32_bold[digit_right_value][x++]);
        }
}

static void draw_battery_digits_16x32(uint8_t digit_left_x, uint8_t digit_right_x,
                                      uint8_t digit_left_value, uint8_t digit_right_value)
{
        int x = 0;

        for (int w = 0; w < 16; w++) {

                stronix_position_set(digit_left_x + w, 4);
                sitronix_print_raw(ascii_array_16x32_bold[digit_left_value][x++]);

                stronix_position_set(digit_left_x + w, 5);
                sitronix_print_raw(ascii_array_16x32_bold[digit_left_value][x++]);

                stronix_position_set(digit_left_x + w, 6);
                sitronix_print_raw(ascii_array_16x32_bold[digit_left_value][x++]);

                stronix_position_set(digit_left_x + w, 7);
                sitronix_print_raw(ascii_array_16x32_bold[digit_left_value][x++]);

        }

        x = 0;
        for (int w = 0; w < 16; w++) {

                stronix_position_set(digit_right_x + w, 4);
                sitronix_print_raw(ascii_array_16x32_bold[digit_right_value][x++]);

                stronix_position_set(digit_right_x + w, 5);
                sitronix_print_raw(ascii_array_16x32_bold[digit_right_value][x++]);

                stronix_position_set(digit_right_x + w, 6);
                sitronix_print_raw(ascii_array_16x32_bold[digit_right_value][x++]);

                stronix_position_set(digit_right_x + w, 7);
                sitronix_print_raw(ascii_array_16x32_bold[digit_right_value][x++]);
        }
}

