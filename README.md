# Fuel Dashboard using Motorola C123

**Turning an old monochrome Motorola C123 feature phone into a working scooter / motorcycle dashboard.**

The phone's monochrome LCD shows the **fuel level** and the **battery voltage** of a scooter. The phone itself is **completely unmodified**: the only electrical connection is its **charger input**, whose **ADC** is used to read the scooter's fuel sending unit and battery. Everything else is software, written from scratch and loaded into RAM.

This is hardware hacking in the original hacker-culture sense: take something obsolete, understand it down to the registers, and make it do something it was never meant to do.

## How it works

- **Target:** Motorola C123 (TI Calypso digital baseband + Iota analog baseband, ARM7TDMI).
- **Input:** the fuel sending unit (a variable resistor/voltage source) and the scooter battery are brought to the phone's charger input. The Iota MADC reads the voltages through the SPI/McSP interface (`VBAT`, `VCHG` registers).
- **Output:** the phone's monochrome LCD (Sitronix controller), with custom 8x8 font and fuel-gauge bitmaps; backlight via the PWL; buzzer for alerts.
- **Firmware:** bare-metal C, no OS, no libc runtime. Loaded straight into RAM at `0x00800104`.

## Files

| File | Purpose |
|------|---------|
| `fuel.c` | **Main program** - hardware init, ADC reads, LCD driver, gauge logic (`mainloop`) |
| `fuel_drawing.h` | Fuel-gauge and voltage screen drawing routines |
| `font.h` | 8x8 font and fuel icon bitmaps |
| `i2c.h` | I2C helpers |
| `memory.h` | Register read/write helpers |
| `util.h`, `utility.c` | Delay and small helpers |
| `start.s` | ARM entry point |
| `build_fuel.sh` | Build script |

## Building

Requires an `arm-none-eabi` toolchain (binutils + GCC).

```sh
./build_fuel.sh
```

This produces `firmware.elf` and `firmware.bin`, linked at `0x00800104`.
Note: `build_fuel.sh` references `libgcc.a` at a fixed path (`/usr/lib/gcc/arm-none-eabi/13.2.1/`); adjust it to match your toolchain version.

## Loading into the phone

The binary is loaded into the phone's RAM with **`osmocon`** from the [OsmocomBB](https://osmocom.org/projects/baseband) project, over a serial cable (compal/C123 loader). Nothing is written to flash, so the phone's original firmware is never touched; a reboot returns it to stock.

## Not based on OsmocomBB

This project is **not based on OsmocomBB**. It is written **from scratch**, from first principles, using reverse engineering and the leaked register-level documentation of the TI **Calypso** and **Iota** analog baseband chips. No OsmocomBB source code is used.

The **only** thing taken from OsmocomBB is the **`osmocon`** tool, used purely to download the compiled code into the phone's RAM. All source code in this repository is original.

## Safety

This touches a vehicle's electrical system. Protect the phone's charger input from over-voltage (use a proper divider/regulator and fusing), mind the vehicle's electrical noise, and never rely on this as a safety-critical instrument. Use at your own risk.

## License

Released under the [MIT License](LICENSE).

Copyright (c) 2026 Michael Randrianantenaina

## Author

**Michael Randrianantenaina**
