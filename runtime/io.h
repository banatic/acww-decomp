/* The ARM9's view of the DS hardware outside RAM: the I/O registers at 0x04000000, VRAM,
 * palettes and OAM, the cartridge, and the clock that drives the display, the timers and the
 * interrupt lines.
 *
 * Every register is plain storage unless something here gives it behaviour; every access is
 * logged by address so a run can say which registers the game actually touched (io_report).
 * Time is counted in bus cycles (33.513982 MHz, the clock of the timers and the display).
 */
#ifndef RUNTIME_IO_H
#define RUNTIME_IO_H

#include <stdint.h>
#include <stdio.h>

#include "arm.h"

/* Bus cycles the clock advances per executed instruction. The ARM9 runs at twice the bus
 * clock and averages a little over one cycle per instruction from cache, less from main
 * RAM; 2 keeps frames at about 280000 instructions, which is the order the game sees. */
#define IO_CYCLES_PER_INSTRUCTION 2

/* One scanline is 355 dots of 6 bus cycles; a frame is 263 lines, 192 of them visible.
 * HBlank begins after the 256 visible dots (GBATEK, "LCD I/O Display Status"). */
#define IO_CYCLES_PER_LINE 2130u
#define IO_LINES_PER_FRAME 263u
#define IO_HBLANK_START 1536u

/* Interrupt bits of IE / IF (GBATEK, "DS Interrupts"). */
#define IRQ_VBLANK (1u << 0)
#define IRQ_HBLANK (1u << 1)
#define IRQ_VCOUNT (1u << 2)
#define IRQ_TIMER0 (1u << 3)
#define IRQ_DMA0 (1u << 8)
#define IRQ_KEYPAD (1u << 12)
#define IRQ_GBA_SLOT (1u << 13)
#define IRQ_IPC_SYNC (1u << 16)
#define IRQ_FIFO_SEND_EMPTY (1u << 17)
#define IRQ_FIFO_RECV_NOT_EMPTY (1u << 18)
#define IRQ_CARD_DATA (1u << 19)
#define IRQ_CARD_IREQ (1u << 20)
#define IRQ_GX_FIFO (1u << 21)

/* Loads the ROM image the cartridge serves and clears every register. 0 on success. The
 * CPU is the one whose program counter the access log records. The environment variable
 * RUN_TRACE may list "card", "pxi" and "irq" (requests, acknowledgements and DMA runs) to
 * print those events as they happen. */
int io_init(const char *rom_path, ArmCpu *cpu);

/* The CPU's I/O callbacks (ArmCpu.io_read / io_write). */
int io_read(void *user, uint32_t address, int size, uint32_t *value);
int io_write(void *user, uint32_t address, int size, uint32_t value);

/* Asked for an address nothing above serves, when set: in a Native run, the ROM's code may be
 * handed the PC's own memory by Native code (a string, a variable on the host stack), and
 * native_run.c serves it. Returns nonzero when it did. */
extern int (*io_unmapped)(uint32_t address, int size, uint32_t *value, int write);

/* The whole bus as the CPU and the DMA units see it: RAM through memory_host, the rest
 * through the register file. Nonzero on success. */
int bus_read(uint32_t address, int size, uint32_t *value);
int bus_write(uint32_t address, int size, uint32_t value);

/* Advances the clock: the display position, the timers, and the interrupt requests they
 * raise. Started DMAs that wait for VBlank or HBlank run when their moment comes. */
void io_advance(uint32_t cycles);
uint64_t io_cycles(void);
/* The time now, to the instruction: io_cycles plus the instructions run since the last
 * io_advance. */
uint64_t io_clock(void);
/* A started DMA has not run yet: it runs on the next io_advance, so the caller keeps its
 * slices short until then (the transfer takes a few hundred cycles on the hardware). */
int io_dma_pending(void);
uint32_t io_frame(void);

/* The renderers' views of video memory (GBATEK, "DS Video Memory"). The 2D engines read
 * their BG and OBJ regions through the CPU's page table, so a bank shows wherever VRAMCNT
 * maps it: io_vram_page gives the 16 KiB page behind `address` (0x06000000-0x06ffffff) or
 * NULL where no bank is mapped. io_vram_bank is the storage of bank A-D (0-3), which the
 * display's VRAM mode and the capture name directly. The slot views are the banks mapped as
 * extended palettes (BG: four 8 KiB slots per engine; OBJ: one per engine), texture images
 * (four 128 KiB slots) and texture palettes (six 16 KiB slots), or NULL. */
const uint8_t *io_vram_page(uint32_t address);
uint8_t *io_vram_bank(int bank);
const uint8_t *io_vram_bg_ext_palette(int engine, int slot);
const uint8_t *io_vram_obj_ext_palette(int engine);
const uint8_t *io_vram_texture(int slot);
const uint8_t *io_vram_texture_palette(int slot);

/* Palette RAM and OAM, 2 KiB each: engine A's first, engine B's from 0x400. */
const uint8_t *io_palette_ram(void);
const uint8_t *io_oam_ram(void);

/* Stores a register without side effects (a capture's self-clearing enable bit). */
void io_reg_store(uint32_t offset, uint32_t value);

/* IF |= bits; the IME/IE gate is io_irq_pending. */
void io_raise_irq(uint32_t bits);
uint32_t io_irq_pending(void);
uint32_t io_reg(uint32_t address); /* a 32-bit register read without logging (reports) */

/* The cartridge's chip ID (command 0xb8), which boot.c also stores where the firmware does. */
uint32_t io_card_chip_id(void);

/* The IPC registers from the ARM7's side (runtime/arm7.c): the ARM9's SYNC output nibble,
 * the ARM7's SYNC input nibble, and the two FIFO directions. */
uint32_t io_ipc_arm9_out(void);
void io_ipc_set_arm7_out(uint32_t nibble);
int io_fifo_pop_from_arm9(uint32_t *word);
int io_fifo_push_to_arm9(uint32_t word);

/* The access log: every distinct (register, size) accessed, in address order. */
typedef struct IoAccess {
    uint32_t address;
    uint8_t size;
    uint8_t write;
    uint32_t first_pc;
    uint64_t count;
} IoAccess;
int io_access_count(void);
const IoAccess *io_access(int index);
const char *io_register_name(uint32_t address);
void io_report(FILE *out);

#endif
