/* The ARM9 BIOS: the SWI functions the game calls, in C, and the code the BIOS ROM runs for
 * an exception and a wait, as ARM instructions served at 0xffff0000 (see bios.c). The CPU
 * takes its exceptions itself (arm.h); the SDK's own context switching runs from the ROM.
 */
#ifndef RUNTIME_BIOS_H
#define RUNTIME_BIOS_H

#include <stdint.h>
#include <stdio.h>

#include "arm.h"

/* The DTCM words the BIOS shares with the SDK (GBATEK, "DS BIOS RAM usage"). */
#define BIOS_IRQ_CHECK_BITS 0x027e3ff8u
#define BIOS_IRQ_HANDLER 0x027e3ffcu

/* The stacks the game's crt0 (Entry at 0x02000800) sets up: SVC at the top of DTCM below the
 * BIOS words, IRQ 0x40 bytes under it, the system stack 0x1000 under that. */
#define BIOS_SVC_STACK 0x027e3fc0u
#define BIOS_IRQ_STACK 0x027e3f7cu
#define BIOS_SYS_STACK 0x027e2f7cu

/* The BIOS image: the exception vectors at its start, then the IRQ handler, IntrWait and
 * Halt (bios.c lists the code). An IRQ handler returns to BIOS_IRQ_RETURN. */
#define BIOS_BASE 0xffff0000u
#define BIOS_SIZE 0x1000u
#define BIOS_IRQ_VECTOR 0xffff0018u
#define BIOS_IRQ_HANDLER_CODE 0xffff0100u
#define BIOS_IRQ_RETURN 0xffff0120u
#define BIOS_INTR_WAIT 0xffff0200u
#define BIOS_HALT 0xffff0280u

/* Sets the CPU as the firmware hands it to the game: system mode, interrupts disabled, the
 * BIOS stacks in the IRQ and SVC banks. */
void bios_init(ArmCpu *cpu);

/* Handles the SWI the CPU stopped on (cpu->swi). Returns 0 when execution continues at r15
 * (a wait enters SVC mode and continues in the BIOS image), -1 for a call this BIOS lacks. */
int bios_swi(ArmCpu *cpu);

/* The CPU's io_read callback: the BIOS image at BIOS_BASE, everything else from io_read. */
int bios_io_read(void *user, uint32_t address, int size, uint32_t *value);

/* The CPU's hook_at callback: a counting hook at the IRQ vector, for the report. */
ArmHook bios_hook_at(void *user, uint32_t address, void **hook_user);

/* How many times each SWI and each interrupt ran, for the report. */
void bios_report(const ArmCpu *cpu, FILE *out);

#endif
