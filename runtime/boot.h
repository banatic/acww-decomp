/* The state the DS firmware leaves for the game's ARM9 entry point, built from the ROM. */
#ifndef RUNTIME_BOOT_H
#define RUNTIME_BOOT_H

#include <stdint.h>
#include <stdio.h>

#include "arm.h"

/* Where the firmware puts the ROM header and the fields it fills around it (GBATEK, "DS
 * Firmware ... shared memory", "DS Cartridge Header"). */
#define BOOT_HEADER_COPY 0x027ffe00u
#define BOOT_CHIP_ID_1 0x027ff800u
#define BOOT_CHIP_ID_2 0x027ff804u
#define BOOT_SECURE_CRC 0x027ff808u
#define BOOT_HEADER_CRC 0x027ff80au
#define BOOT_CHIP_ID_3 0x027ffc00u
#define BOOT_CHIP_ID_4 0x027ffc04u
#define BOOT_SECURE_CRC_2 0x027ffc08u
#define BOOT_HEADER_CRC_2 0x027ffc0au
#define BOOT_INDICATOR 0x027ffc40u
#define BOOT_USER_SETTINGS 0x027ffc80u

/* Loads the ARM9 program from the ROM at `rom_path` where its header says, fills the shared
 * area, and sets the CPU to the entry point in ARM state. 0 on success. */
int boot_init(const char *rom_path, ArmCpu *cpu);

/* The entry address from the header, and the module the symbols come from. */
uint32_t boot_entry(void);

/* After the crt0 has decompressed and copied the autoloads: compares memory with the
 * modules the manifest lists (one "<module> <base> <path>" line each), as the decomp
 * extracted them. Prints the result; returns 0 when every resident module matches. */
int boot_verify(const char *manifest, FILE *out);

#endif
