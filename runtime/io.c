/* The hardware behind the I/O callbacks; see io.h. Register semantics follow GBATEK unless a
 * comment says where this model is simpler than the hardware. */
#include "io.h"

#include <stdlib.h>
#include <string.h>

#include "gpu2d.h"
#include "gpu3d.h"
#include "input.h"
#include "memory.h"

/* Register addresses used below (offsets from 0x04000000). */
#define REG_DISPSTAT 0x004
#define REG_VCOUNT 0x006
#define REG_DMA0SAD 0x0b0
#define REG_DMA3CNT 0x0dc
#define REG_TM0CNT 0x100
#define REG_KEYINPUT 0x130
#define REG_IPCSYNC 0x180
#define REG_IPCFIFOCNT 0x184
#define REG_IPCFIFOSEND 0x188
#define REG_AUXSPICNT 0x1a0
#define REG_ROMCTRL 0x1a4
#define REG_CARDCMD 0x1a8
#define REG_EXMEMCNT 0x204
#define REG_IME 0x208
#define REG_IE 0x210
#define REG_IF 0x214
#define REG_VRAMCNT_A 0x240
#define REG_VRAMCNT_I 0x249
#define REG_DIVCNT 0x280
#define REG_DIV_NUMER 0x290
#define REG_DIV_DENOM 0x298
#define REG_DIV_RESULT 0x2a0
#define REG_DIVREM_RESULT 0x2a8
#define REG_SQRTCNT 0x2b0
#define REG_SQRT_RESULT 0x2b4
#define REG_SQRT_PARAM 0x2b8
#define REG_DISP3DCNT 0x060
#define REG_GXFIFO 0x400
#define REG_GXSTAT 0x600
#define REG_RAM_COUNT 0x604
#define REG_POS_RESULT 0x620
#define REG_VECMTX_RESULT_END 0x6a4

#define IO_BASE 0x04000000u
#define IO_SIZE 0x2000u
#define IPC_RECV 0x04100000u
#define CARD_DATA 0x04100010u

static ArmCpu *the_cpu;
static uint8_t regs[IO_SIZE];
static int trace_card, trace_pxi, trace_irq;

/* The clock ------------------------------------------------------------------------------ */

static uint64_t clock_cycles;
static uint64_t steps_synced; /* the CPU's step count when the clock was last advanced */
static uint32_t line_cycle, vcount, frame_count;
static int in_hblank;

uint64_t io_cycles(void)
{
    return clock_cycles;
}

/* The time now: the clock is advanced once per slice of instructions, so an event inside a
 * slice (a DMA start) is placed by the instructions executed since. */
static uint64_t clock_now(void)
{
    if (the_cpu == NULL) {
        return clock_cycles;
    }
    return clock_cycles + (the_cpu->steps - steps_synced) * IO_CYCLES_PER_INSTRUCTION;
}

uint64_t io_clock(void)
{
    return clock_now();
}

uint32_t io_frame(void)
{
    return frame_count;
}

/* Register file helpers -------------------------------------------------------------------- */

static uint32_t rd32(uint32_t offset)
{
    uint32_t v;
    memcpy(&v, regs + offset, 4);
    return v;
}

static uint16_t rd16(uint32_t offset)
{
    uint16_t v;
    memcpy(&v, regs + offset, 2);
    return v;
}

static void st32(uint32_t offset, uint32_t v)
{
    memcpy(regs + offset, &v, 4);
}

static void st16(uint32_t offset, uint16_t v)
{
    memcpy(regs + offset, &v, 2);
}

static uint64_t rd64(uint32_t offset)
{
    return (uint64_t) rd32(offset) | ((uint64_t) rd32(offset + 4) << 32);
}

static void st64(uint32_t offset, uint64_t v)
{
    st32(offset, (uint32_t) v);
    st32(offset + 4, (uint32_t) (v >> 32));
}

uint32_t io_reg(uint32_t address)
{
    return (address - IO_BASE) < IO_SIZE ? rd32((address - IO_BASE) & ~3u) : 0;
}

/* The access log --------------------------------------------------------------------------- */

#define LOG_SLOTS 8192
static IoAccess log_slots[LOG_SLOTS];
static int log_order[LOG_SLOTS];
static int log_count;

static uint32_t current_pc(void)
{
    if (the_cpu == NULL) {
        return 0;
    }
    return the_cpu->r[15] - ((the_cpu->cpsr & ARM_CPSR_T) ? 2 : 4);
}

static void log_access(uint32_t address, int size, int write)
{
    uint32_t key = (address * 2654435761u) ^ ((uint32_t) size << 8) ^ (write ? 0x5a5au : 0);
    uint32_t h = key % LOG_SLOTS;
    for (int probe = 0; probe < LOG_SLOTS; probe++) {
        IoAccess *a = &log_slots[(h + probe) % LOG_SLOTS];
        if (a->count == 0) {
            if (log_count == LOG_SLOTS - 1) {
                return; /* full: the report says so through the count */
            }
            a->address = address;
            a->size = (uint8_t) size;
            a->write = (uint8_t) write;
            a->first_pc = current_pc();
            a->count = 1;
            log_order[log_count++] = (int) ((h + probe) % LOG_SLOTS);
            return;
        }
        if (a->address == address && a->size == size && a->write == write) {
            a->count++;
            return;
        }
    }
}

static int compare_access(const void *x, const void *y)
{
    const IoAccess *a = &log_slots[*(const int *) x], *b = &log_slots[*(const int *) y];
    if (a->address != b->address) {
        return a->address < b->address ? -1 : 1;
    }
    if (a->write != b->write) {
        return a->write - b->write;
    }
    return a->size - b->size;
}

int io_access_count(void)
{
    qsort(log_order, (size_t) log_count, sizeof(log_order[0]), compare_access);
    return log_count;
}

const IoAccess *io_access(int index)
{
    return &log_slots[log_order[index]];
}

/* Interrupts ------------------------------------------------------------------------------- */

uint32_t io_irq_pending(void)
{
    if ((rd32(REG_IME) & 1) == 0) {
        return 0;
    }
    return rd32(REG_IE) & rd32(REG_IF);
}

/* The CPU's interrupt line (ArmCpu.irq_line) follows IME, IE and IF: re-evaluated after a
 * request and after every register write. */
static void sync_irq_line(void)
{
    if (the_cpu != NULL) {
        the_cpu->irq_line = io_irq_pending() != 0;
    }
}

void io_raise_irq(uint32_t bits)
{
    if (trace_irq && the_cpu) {
        fprintf(stderr,
                "irq: raise %08x at step %llu pc %08x (IF %08x IE %08x IME %x I %d)"
                "\n",
                bits, (unsigned long long) the_cpu->steps, current_pc(), rd32(REG_IF), rd32(REG_IE), rd32(REG_IME) & 1,
                (the_cpu->cpsr >> 7) & 1);
    }
    st32(REG_IF, rd32(REG_IF) | bits);
    sync_irq_line();
}

/* VRAM ------------------------------------------------------------------------------------- */

/* The nine banks, stored back to back in LCDC order, and the CPU's view of them as the
 * VRAMCNT registers map it: a page table over 0x06000000-0x06ffffff in 16 KiB pages. A page
 * no bank covers reads zero and drops writes (and is counted). Bank modes that map a bank to
 * the 3D engine, the ARM7 or the extended palettes have no CPU address; they are kept in the
 * bank's storage only. (GBATEK, "DS Video Memory".) */
#define VRAM_TOTAL 0xa4000u
#define VRAM_PAGE 0x4000u
#define VRAM_PAGES (0x1000000u / VRAM_PAGE)
static uint8_t vram[VRAM_TOTAL];
static uint8_t *vram_page[VRAM_PAGES];
static uint64_t vram_unmapped_reads, vram_unmapped_writes;

/* The views the renderers take of banks that have no CPU address: the extended palette
 * slots per engine (BG: four 8 KiB slots, OBJ: one), the texture image slots (four of
 * 128 KiB) and the texture palette slots (six of 16 KiB), each the bank storage mapped there
 * or NULL (GBATEK, "DS Video Memory", the mode tables). */
static const uint8_t *bg_ext_palette[2][4], *obj_ext_palette[2], *texture_slot[4], *texture_palette_slot[6];

static const struct {
    uint32_t offset, size, lcdc;
} vram_bank[9] = {
    {0x00000, 0x20000, 0x06800000}, {0x20000, 0x20000, 0x06820000}, {0x40000, 0x20000, 0x06840000},
    {0x60000, 0x20000, 0x06860000}, {0x80000, 0x10000, 0x06880000}, {0x90000, 0x04000, 0x06890000},
    {0x94000, 0x04000, 0x06894000}, {0x98000, 0x08000, 0x06898000}, {0xa0000, 0x04000, 0x068a0000},
};

/* Maps `size` bytes of bank storage at `address`, repeated every `mirror` bytes within a
 * region of `region_size` bytes starting at `region`. */
static void map_bank(uint8_t *storage, uint32_t size, uint32_t address, uint32_t region, uint32_t region_size, uint32_t mirror)
{
    for (uint32_t base = address; base < region + region_size; base += mirror) {
        for (uint32_t off = 0; off < size; off += VRAM_PAGE) {
            uint32_t a = base + off;
            if (a >= region + region_size) {
                break;
            }
            vram_page[(a - 0x06000000u) / VRAM_PAGE] = storage + off;
        }
    }
}

static void rebuild_vram(void)
{
    memset(vram_page, 0, sizeof(vram_page));
    memset(bg_ext_palette, 0, sizeof(bg_ext_palette));
    memset(obj_ext_palette, 0, sizeof(obj_ext_palette));
    memset(texture_slot, 0, sizeof(texture_slot));
    memset(texture_palette_slot, 0, sizeof(texture_palette_slot));
    for (int bank = 0; bank < 9; bank++) {
        uint32_t cnt = regs[REG_VRAMCNT_A + bank + (bank >= 7 ? 1 : 0)]; /* 0x247 is WRAMCNT */
        if ((cnt & 0x80) == 0) {
            continue;
        }
        uint32_t mst = cnt & 7, ofs = (cnt >> 3) & 3;
        uint8_t *s = vram + vram_bank[bank].offset;
        uint32_t size = vram_bank[bank].size;
        if (mst == 0) {
            map_bank(s, size, vram_bank[bank].lcdc, 0x06800000u, 0x100000u, 0x100000u);
            continue;
        }
        switch (bank) {
            case 0:
            case 1:
            case 2:
            case 3: /* A-D: BG-A by OFS, OBJ-A (A, B), ARM7 (C, D), BG-B (C), OBJ-B (D) */
                if (mst == 1) {
                    map_bank(s, size, 0x06000000u + 0x20000u * ofs, 0x06000000u, 0x200000u, 0x80000u);
                } else if (mst == 2 && bank < 2) {
                    map_bank(s, size, 0x06400000u + 0x20000u * (ofs & 1), 0x06400000u, 0x200000u, 0x40000u);
                } else if (mst == 4 && bank == 2) {
                    map_bank(s, size, 0x06200000u, 0x06200000u, 0x200000u, 0x20000u);
                } else if (mst == 4 && bank == 3) {
                    map_bank(s, size, 0x06600000u, 0x06600000u, 0x200000u, 0x20000u);
                } else if (mst == 3) {
                    texture_slot[ofs] = s;
                }
                break;
            case 4: /* E: BG-A, OBJ-A at the region start; 3, 4 are palettes */
                if (mst == 1) {
                    map_bank(s, size, 0x06000000u, 0x06000000u, 0x200000u, 0x80000u);
                } else if (mst == 2) {
                    map_bank(s, size, 0x06400000u, 0x06400000u, 0x200000u, 0x40000u);
                } else if (mst == 3) {
                    for (int i = 0; i < 4; i++) {
                        texture_palette_slot[i] = s + 0x4000 * i;
                    }
                } else if (mst == 4) {
                    for (int i = 0; i < 4; i++) {
                        bg_ext_palette[0][i] = s + 0x2000 * i; /* the first 32 KiB of E */
                    }
                }
                break;
            case 5:
            case 6: { /* F, G: 16 KiB slots by OFS */
                uint32_t slot = 0x4000u * (ofs & 1) + 0x10000u * (ofs >> 1);
                if (mst == 1) {
                    map_bank(s, size, 0x06000000u + slot, 0x06000000u, 0x200000u, 0x80000u);
                } else if (mst == 2) {
                    map_bank(s, size, 0x06400000u + slot, 0x06400000u, 0x200000u, 0x40000u);
                } else if (mst == 3) {
                    /* texture palette slot 0, 1, 4 or 5 by OFS */
                    texture_palette_slot[(ofs & 1) + 4 * (ofs >> 1)] = s;
                } else if (mst == 4) {
                    /* BG extended palette slots 0-1 (OFS bit 0 clear) or 2-3 (set) */
                    bg_ext_palette[0][2 * (ofs & 1)] = s;
                    bg_ext_palette[0][2 * (ofs & 1) + 1] = s + 0x2000;
                } else if (mst == 5) {
                    obj_ext_palette[0] = s; /* the first 8 KiB */
                }
                break;
            }
            case 7: /* H: BG-B */
                if (mst == 1) {
                    map_bank(s, size, 0x06200000u, 0x06200000u, 0x200000u, 0x20000u);
                } else if (mst == 2) {
                    for (int i = 0; i < 4; i++) {
                        bg_ext_palette[1][i] = s + 0x2000 * i;
                    }
                }
                break;
            case 8: /* I: BG-B upper half, OBJ-B */
                if (mst == 1) {
                    map_bank(s, size, 0x06208000u, 0x06200000u, 0x200000u, 0x20000u);
                } else if (mst == 2) {
                    map_bank(s, size, 0x06600000u, 0x06600000u, 0x200000u, 0x20000u);
                } else if (mst == 3) {
                    obj_ext_palette[1] = s; /* the first 8 KiB */
                }
                break;
            default:
                break;
        }
    }
}

static uint8_t *vram_host(uint32_t address, int size)
{
    uint32_t page = (address - 0x06000000u) / VRAM_PAGE;
    if (page >= VRAM_PAGES || vram_page[page] == NULL) {
        return NULL;
    }
    if ((address & (VRAM_PAGE - 1)) + (uint32_t) size > VRAM_PAGE) {
        return NULL; /* an access straddling pages: not something aligned code does */
    }
    return vram_page[page] + (address & (VRAM_PAGE - 1));
}

/* Palettes and OAM: 2 KiB each, repeated through their regions. */
static uint8_t palette[0x800], oam[0x800];

/* The renderers' views (io.h). */
const uint8_t *io_vram_page(uint32_t address)
{
    uint32_t page = (address - 0x06000000u) / VRAM_PAGE;
    return page < VRAM_PAGES ? vram_page[page] : NULL;
}

uint8_t *io_vram_bank(int bank)
{
    return vram + vram_bank[bank & 3].offset; /* A-D: the banks a display or capture names */
}

const uint8_t *io_vram_bg_ext_palette(int engine, int slot)
{
    return bg_ext_palette[engine & 1][slot & 3];
}

const uint8_t *io_vram_obj_ext_palette(int engine)
{
    return obj_ext_palette[engine & 1];
}

const uint8_t *io_vram_texture(int slot)
{
    return texture_slot[slot & 3];
}

const uint8_t *io_vram_texture_palette(int slot)
{
    return slot >= 0 && slot < 6 ? texture_palette_slot[slot] : NULL;
}

const uint8_t *io_palette_ram(void)
{
    return palette;
}

const uint8_t *io_oam_ram(void)
{
    return oam;
}

void io_reg_store(uint32_t offset, uint32_t value)
{
    if (offset < IO_SIZE) {
        st32(offset & ~3u, value);
    }
}

/* The cartridge ---------------------------------------------------------------------------- */

/* The ROM image, served through the cartridge bus registers: a command is written to
 * 0x040001a8 (first byte lowest), ROMCTRL bit 31 starts it, and the data comes out of
 * 0x04100010 one word at a time, ready (bit 23) until the block is drained. Only the
 * commands of normal (unencrypted) mode are modelled; the firmware already took the card
 * through KEY1 before the game's entry point runs. */
static uint8_t *rom;
static uint32_t rom_size;
static uint8_t card_buf[0x4000];
static uint32_t card_len, card_pos;
static uint64_t card_reads;
static uint32_t card_unknown_commands;

/* The chip ID the hardware would report: Macronix, (ROM size in MiB) - 1, no special flags.
 * boot.c stores the same value where the firmware leaves it. */
uint32_t io_card_chip_id(void)
{
    return 0xc2u | (((rom_size >> 20) - 1) & 0xffu) << 8;
}

static void card_start(uint32_t romctrl)
{
    /* Block size code: 0 none, 7 four bytes, else 0x100 << code: the SDK reads its 512-byte
       pages with code 1 (CARDi_ReadCard, 0x0211f8b0), as libnds does. */
    uint32_t block = (romctrl >> 24) & 7;
    card_len = block == 0 ? 0 : block == 7 ? 4 : 0x100u << block;
    card_pos = 0;
    uint8_t cmd = regs[REG_CARDCMD];
    uint32_t address = ((uint32_t) regs[REG_CARDCMD + 1] << 24) | ((uint32_t) regs[REG_CARDCMD + 2] << 16) |
                       ((uint32_t) regs[REG_CARDCMD + 3] << 8) | regs[REG_CARDCMD + 4];
    if (trace_card) {
        fprintf(stderr, "card: romctrl %08x cmd %02x address %08x block %u bytes at pc %08x\n", romctrl, cmd, address,
                card_len, current_pc());
    }
    switch (cmd) {
        case 0xb7: /* read: the secure area is not readable this way; the hardware serves its
                      first 512 bytes repeated instead (GBATEK, "Gamecard Protocol") */
            if (address < 0x8000) {
                address = 0x8000 + (address & 0x1ff);
            }
            for (uint32_t i = 0; i < card_len; i++) {
                uint32_t a = address + i;
                card_buf[i] = a < rom_size ? rom[a] : 0xff;
            }
            card_reads++;
            break;
        case 0xb8: { /* chip ID, repeated */
            uint32_t id = io_card_chip_id();
            for (uint32_t i = 0; i < card_len; i++) {
                card_buf[i] = (uint8_t) (id >> (8 * (i & 3)));
            }
            break;
        }
        case 0x00: /* header */
            for (uint32_t i = 0; i < card_len; i++) {
                card_buf[i] = (address + i) < rom_size ? rom[(address + i) & 0xfff] : 0xff;
            }
            break;
        case 0x9f: /* dummy: the bus idles high */
            memset(card_buf, 0xff, card_len);
            break;
        default:
            card_unknown_commands++;
            memset(card_buf, 0xff, card_len);
            break;
    }
}

static void card_finish(void);

static uint32_t card_read_word(void)
{
    uint32_t v = 0xffffffffu;
    if (card_pos < card_len) {
        memcpy(&v, card_buf + card_pos, 4);
        card_pos += 4;
        if (card_pos >= card_len) {
            card_finish();
        }
    }
    return v;
}

static uint32_t card_romctrl(void)
{
    uint32_t v = rd32(REG_ROMCTRL) & ~((1u << 23) | (1u << 31));
    if (card_pos < card_len) {
        v |= (1u << 23) | (1u << 31);
    }
    return v;
}

/* DMA -------------------------------------------------------------------------------------- */

typedef struct Dma {
    uint32_t src, dst, count; /* the internal registers, latched when the channel starts */
    int armed;                /* enabled and waiting for its start event */
    int pending;              /* started; runs once the clock reaches `due`: the transfer
                                 takes its time in the background while the CPU goes on, as
                                 on the hardware, where the SDK clears the geometry FIFO
                                 interrupt right after starting a transfer and expects the
                                 one the transfer raises to come later (MIi_FIFOCallback) */
    uint64_t due;
} Dma;
static Dma dma[4];
static uint64_t dma_runs[8]; /* by start timing, for the report */

static uint32_t dma_cnt(int ch)
{
    return rd32(REG_DMA0SAD + 12 * ch + 8);
}

/* One transfer of `count` units; returns nonzero when the channel stays enabled (repeat). */
static void dma_transfer(int ch)
{
    Dma *d = &dma[ch];
    uint32_t cnt = dma_cnt(ch);
    uint32_t count = cnt & 0x1fffffu;
    if (count == 0) {
        count = 0x200000u;
    }
    int width = (cnt & (1u << 26)) ? 4 : 2;
    uint32_t dst_mode = (cnt >> 21) & 3, src_mode = (cnt >> 23) & 3;
    d->src &= ~(uint32_t) (width - 1);
    d->dst &= ~(uint32_t) (width - 1);
    for (uint32_t i = 0; i < count; i++) {
        uint32_t v = 0;
        bus_read(d->src, width, &v);
        bus_write(d->dst, width, v);
        if (src_mode == 0) {
            d->src += (uint32_t) width;
        } else if (src_mode == 1) {
            d->src -= (uint32_t) width;
        }
        if (dst_mode == 0 || dst_mode == 3) {
            d->dst += (uint32_t) width;
        } else if (dst_mode == 1) {
            d->dst -= (uint32_t) width;
        }
    }
    dma_runs[(cnt >> 27) & 7]++;
    if (trace_irq && the_cpu) {
        fprintf(stderr,
                "dma: ch %d ran %u units to %08x at step %llu"
                "\n",
                ch, count, d->dst, (unsigned long long) the_cpu->steps);
    }
    if (cnt & (1u << 30)) {
        io_raise_irq(IRQ_DMA0 << ch);
    }
    if (cnt & (1u << 25)) {
        if (dst_mode == 3) {
            d->dst = rd32(REG_DMA0SAD + 12 * ch + 4);
        }
        d->armed = 1; /* repeat: wait for the next start event */
    } else {
        st32(REG_DMA0SAD + 12 * ch + 8, cnt & ~(1u << 31));
        d->armed = 0;
    }
}

static void dma_write_cnt(int ch, uint32_t old, uint32_t value)
{
    Dma *d = &dma[ch];
    if ((value & (1u << 31)) == 0) {
        d->armed = 0;
        d->pending = 0;
        return;
    }
    if (old & (1u << 31)) {
        return; /* already running; the hardware ignores the rewrite */
    }
    d->src = rd32(REG_DMA0SAD + 12 * ch);
    d->dst = rd32(REG_DMA0SAD + 12 * ch + 4);
    uint32_t timing = (value >> 27) & 7;
    switch (timing) {
        case 0: /* immediately */
        case 7: /* geometry command FIFO: it never fills in this model, so at once */
        case 3: /* start of display, 4: main memory display, 6: GBA slot: run once */
        case 4:
        case 6: {
            /* two bus cycles per word, one per halfword, and some setup */
            uint32_t count = value & 0x1fffffu, units = count ? count : 0x200000u;
            d->armed = 0;
            d->pending = 1;
            d->due = clock_now() + 32 + (uint64_t) units * ((value & (1u << 26)) ? 2 : 1);
            break;
        }
        default: /* 1 VBlank, 2 HBlank, 5 DS cartridge: wait for the event */
            d->armed = 1;
            break;
    }
}

int io_dma_pending(void)
{
    return dma[0].pending | dma[1].pending | dma[2].pending | dma[3].pending;
}

static void dma_run_pending(void)
{
    for (int ch = 0; ch < 4; ch++) {
        if (dma[ch].pending && dma[ch].due <= clock_cycles) {
            dma[ch].pending = 0;
            if (dma_cnt(ch) & (1u << 31)) {
                dma_transfer(ch);
            }
        }
    }
}

static void dma_event(uint32_t timing)
{
    for (int ch = 0; ch < 4; ch++) {
        if (dma[ch].armed && (dma_cnt(ch) & (1u << 31)) && ((dma_cnt(ch) >> 27) & 7) == timing) {
            dma_transfer(ch);
        }
    }
}

/* The cartridge transfer feeds one DMA unit per ready word on a channel with timing 5. A
 * channel so armed drains the block at once; CPU reads of 0x04100010 drain it otherwise. */
static void card_feed_dma(void)
{
    for (int ch = 0; ch < 4; ch++) {
        while (dma[ch].armed && (dma_cnt(ch) & (1u << 31)) && ((dma_cnt(ch) >> 27) & 7) == 5 && card_pos < card_len) {
            dma_transfer(ch);
        }
    }
}

static void card_finish(void)
{
    card_len = card_pos = 0;
    if (rd16(REG_AUXSPICNT) & (1u << 14)) {
        io_raise_irq(IRQ_CARD_DATA);
    }
}

/* Timers ----------------------------------------------------------------------------------- */

typedef struct Timer {
    uint32_t counter;   /* 16 bits */
    uint32_t remainder; /* bus cycles not yet counted at this prescale */
} Timer;
static Timer timers[4];

static const uint32_t prescale[4] = {1, 64, 256, 1024};

static void timer_overflow(int t);

static void timer_tick(int t, uint32_t ticks)
{
    uint32_t reload = rd16(REG_TM0CNT + 4 * t);
    while (ticks > 0) {
        uint32_t room = 0x10000u - timers[t].counter;
        if (ticks < room) {
            timers[t].counter += ticks;
            return;
        }
        ticks -= room;
        timers[t].counter = reload;
        timer_overflow(t);
    }
}

static void timer_overflow(int t)
{
    uint32_t ctl = rd16(REG_TM0CNT + 4 * t + 2);
    if (ctl & (1u << 6)) {
        io_raise_irq(IRQ_TIMER0 << t);
    }
    if (t < 3) {
        uint32_t next = rd16(REG_TM0CNT + 4 * (t + 1) + 2);
        if ((next & 0x84) == 0x84) { /* count-up: the next timer ticks once per overflow */
            timer_tick(t + 1, 1);
        }
    }
}

static void timers_advance(uint32_t cycles)
{
    for (int t = 0; t < 4; t++) {
        uint32_t ctl = rd16(REG_TM0CNT + 4 * t + 2);
        if ((ctl & 0x80) == 0 || (ctl & 4)) {
            continue;
        }
        uint32_t p = prescale[ctl & 3];
        uint32_t total = timers[t].remainder + cycles;
        timers[t].remainder = total % p;
        timer_tick(t, total / p);
    }
}

static void timer_write_control(int t, uint32_t old, uint32_t value)
{
    if ((value & 0x80) && !(old & 0x80)) {
        timers[t].counter = rd16(REG_TM0CNT + 4 * t);
        timers[t].remainder = 0;
    }
}

static void io_gx_fifo_irq_update(void); /* the geometry FIFO interrupt, below */

/* The display clock ------------------------------------------------------------------------ */

static void display_advance(uint32_t cycles)
{
    while (cycles > 0) {
        uint32_t next = in_hblank ? IO_CYCLES_PER_LINE : IO_HBLANK_START;
        uint32_t step = next - line_cycle;
        if (step > cycles) {
            line_cycle += cycles;
            return;
        }
        cycles -= step;
        line_cycle = next;
        uint32_t stat = rd16(REG_DISPSTAT);
        if (!in_hblank) {
            in_hblank = 1;
            if (vcount < 192) {
                /* the line is drawn from the registers as they were while it was displayed,
                   before the HBlank interrupt handler and HBlank DMAs change them for the
                   next line */
                gpu2d_line(vcount);
            }
            if (stat & (1u << 4)) {
                io_raise_irq(IRQ_HBLANK);
            }
            if (vcount < 192) {
                dma_event(2);
            }
        } else {
            in_hblank = 0;
            line_cycle = 0;
            vcount++;
            if (vcount == IO_LINES_PER_FRAME) {
                vcount = 0;
                frame_count++;
            }
            if (vcount == 192) {
                gpu2d_frame_end();
                /* a pending SWAP_BUFFERS takes effect: the list it closed is rendered and
                   shown from the next frame on, and the stalled geometry commands run */
                gpu3d_vblank();
                io_gx_fifo_irq_update();
                if (stat & (1u << 3)) {
                    io_raise_irq(IRQ_VBLANK);
                }
                dma_event(1);
            }
            uint32_t lyc = ((stat >> 8) & 0xff) | ((stat & 0x80) << 1);
            if (vcount == lyc && (stat & (1u << 5))) {
                io_raise_irq(IRQ_VCOUNT);
            }
        }
    }
}

void io_advance(uint32_t cycles)
{
    clock_cycles += cycles;
    if (the_cpu != NULL) {
        steps_synced = the_cpu->steps;
    }
    dma_run_pending();
    timers_advance(cycles);
    display_advance(cycles);
}

static uint32_t dispstat_read(void)
{
    uint32_t stat = rd16(REG_DISPSTAT) & 0xffb8u;
    if (vcount >= 192 && vcount != 262) {
        stat |= 1; /* VBlank flag: lines 192..261, not the last line (GBATEK) */
    }
    if (in_hblank) {
        stat |= 2;
    }
    uint32_t lyc = ((stat >> 8) & 0xff) | ((stat & 0x80) << 1);
    if (vcount == lyc) {
        stat |= 4;
    }
    return stat | (vcount << 16);
}

/* The math units --------------------------------------------------------------------------- */

/* Both are combinational here: the busy bits read zero, and the result is written the moment
 * an operand or the control register changes. Division edge cases are the hardware's
 * (GBATEK, "DS Maths"): a zero divisor gives +-1 with the remainder the numerator, and the
 * most negative value over -1 wraps. */
static void divide(void)
{
    uint32_t cnt = rd16(REG_DIVCNT) & 3;
    int64_t numer, denom, quot, rem;
    if (cnt == 0) {
        numer = (int32_t) rd32(REG_DIV_NUMER);
    } else {
        numer = (int64_t) rd64(REG_DIV_NUMER);
    }
    if (cnt == 2) {
        denom = (int64_t) rd64(REG_DIV_DENOM);
    } else {
        denom = (int32_t) rd32(REG_DIV_DENOM);
    }
    uint32_t flags = rd16(REG_DIVCNT) & ~0x4000u;
    if (rd64(REG_DIV_DENOM) == 0) {
        flags |= 0x4000; /* the flag looks at all 64 bits of the divisor in every mode */
    }
    if (denom == 0) {
        quot = numer < 0 ? 1 : -1;
        rem = numer;
        if (cnt == 0) { /* 32-bit mode: the upper half of the quotient comes out inverted */
            quot ^= (int64_t) 0xffffffff00000000ull;
        }
    } else if (cnt == 0 && numer == INT32_MIN && denom == -1) {
        quot = 0x80000000ll;
        rem = 0;
    } else if (cnt != 0 && numer == INT64_MIN && denom == -1) {
        quot = INT64_MIN;
        rem = 0;
    } else {
        quot = numer / denom;
        rem = numer % denom;
    }
    st64(REG_DIV_RESULT, (uint64_t) quot);
    st64(REG_DIVREM_RESULT, (uint64_t) rem);
    st16(REG_DIVCNT, (uint16_t) flags);
}

static void square_root(void)
{
    uint64_t v = (rd16(REG_SQRTCNT) & 1) ? rd64(REG_SQRT_PARAM) : rd32(REG_SQRT_PARAM);
    uint64_t res = 0, bit = 1ull << 62;
    while (bit > v) {
        bit >>= 2;
    }
    while (bit) {
        if (v >= res + bit) {
            v -= res + bit;
            res = (res >> 1) + bit;
        } else {
            res >>= 1;
        }
        bit >>= 2;
    }
    st32(REG_SQRT_RESULT, (uint32_t) res);
}

/* IPC -------------------------------------------------------------------------------------- */

/* IPCSYNC: bits 0-3 are the other side's output, 8-11 ours (GBATEC, "DS Inter Process\n * Communication"). The FIFOs hold 16 words each way. */
static uint32_t sync_arm9_out, sync_arm7_out;
static uint32_t fifo_to7[16], fifo_to9[16];
static uint32_t to7_head, to7_count, to9_head, to9_count, recv_last;

static uint32_t fifocnt_read(void)
{
    uint32_t v = rd16(REG_IPCFIFOCNT) & 0xc404u; /* enable, error, irq enables */
    if (to7_count == 0) {
        v |= 1;
    }
    if (to7_count == 16) {
        v |= 2;
    }
    if (to9_count == 0) {
        v |= 0x100;
    }
    if (to9_count == 16) {
        v |= 0x200;
    }
    return v;
}

static void fifocnt_write(uint32_t value)
{
    uint32_t old = rd16(REG_IPCFIFOCNT);
    uint32_t keep = old & 0x4000u; /* the error flag: cleared by writing 1 */
    if (value & 0x4000u) {
        keep = 0;
    }
    if (value & 8) {
        to7_count = 0;
        to7_head = 0;
    }
    st16(REG_IPCFIFOCNT, (uint16_t) ((value & 0x8404u) | keep));
    /* turning the receive interrupt on while words wait raises it at once */
    if ((value & 0x400) && !(old & 0x400) && to9_count > 0) {
        io_raise_irq(IRQ_FIFO_RECV_NOT_EMPTY);
    }
    if ((value & 4) && !(old & 4) && to7_count == 0) {
        io_raise_irq(IRQ_FIFO_SEND_EMPTY);
    }
}

static void fifo_send(uint32_t word)
{
    if (trace_pxi) {
        fprintf(stderr, "pxi: arm9 sends tag %2u err %u data %07x at pc %08x\n", word & 0x1f, (word >> 5) & 1, word >> 6,
                current_pc());
    }
    if ((rd16(REG_IPCFIFOCNT) & 0x8000) == 0) {
        return;
    }
    if (to7_count == 16) {
        st16(REG_IPCFIFOCNT, (uint16_t) (rd16(REG_IPCFIFOCNT) | 0x4000));
        return;
    }
    fifo_to7[(to7_head + to7_count) & 15] = word;
    to7_count++;
}

static uint32_t fifo_recv(void)
{
    if ((rd16(REG_IPCFIFOCNT) & 0x8000) == 0 || to9_count == 0) {
        st16(REG_IPCFIFOCNT, (uint16_t) (rd16(REG_IPCFIFOCNT) | 0x4000));
        return recv_last;
    }
    recv_last = fifo_to9[to9_head];
    to9_head = (to9_head + 1) & 15;
    to9_count--;
    return recv_last;
}

uint32_t io_ipc_arm9_out(void)
{
    return sync_arm9_out;
}

void io_ipc_set_arm7_out(uint32_t nibble)
{
    sync_arm7_out = nibble & 0xf;
}

int io_fifo_pop_from_arm9(uint32_t *word)
{
    if (to7_count == 0) {
        return 0;
    }
    *word = fifo_to7[to7_head];
    to7_head = (to7_head + 1) & 15;
    to7_count--;
    if (to7_count == 0 && (rd16(REG_IPCFIFOCNT) & 4)) {
        io_raise_irq(IRQ_FIFO_SEND_EMPTY);
    }
    return 1;
}

int io_fifo_push_to_arm9(uint32_t word)
{
    if (trace_pxi) {
        fprintf(stderr, "pxi: arm7 sends tag %2u err %u data %07x\n", word & 0x1f, (word >> 5) & 1, word >> 6);
    }
    if (to9_count == 16) {
        return 0;
    }
    fifo_to9[(to9_head + to9_count) & 15] = word;
    to9_count++;
    if (to9_count == 1 && (rd16(REG_IPCFIFOCNT) & 0x400)) {
        io_raise_irq(IRQ_FIFO_RECV_NOT_EMPTY);
    }
    return 1;
}

/* Register reads and writes ---------------------------------------------------------------- */

static uint64_t gxfifo_writes;

/* The geometry FIFO interrupt is level-triggered: while the condition GXSTAT bits 30-31 select
 * holds (1: fewer than 128 entries, 2: empty), the request is raised again. It is re-evaluated
 * whenever the FIFO or the selection changes. */
static void io_gx_fifo_irq_update(void)
{
    uint32_t select = rd32(REG_GXSTAT) >> 30;
    uint32_t stat = gpu3d_read(REG_GXSTAT);
    if ((select == 1 && (stat & (1u << 25))) || (select == 2 && (stat & (1u << 26)))) {
        io_raise_irq(IRQ_GX_FIFO);
    }
}

/* A 32-bit read of the register at `offset` (aligned); storage unless noted. */
static uint32_t reg_read32(uint32_t offset)
{
    switch (offset) {
        case REG_DISPSTAT:
            return dispstat_read();
        case REG_TM0CNT:
        case REG_TM0CNT + 4:
        case REG_TM0CNT + 8:
        case REG_TM0CNT + 12:
            return timers[(offset - REG_TM0CNT) / 4].counter | ((uint32_t) rd16(offset + 2) << 16);
        case REG_KEYINPUT:
            return (0x03ffu & ~input_keys()) | ((uint32_t) rd16(offset + 2) << 16); /* a held key reads 0 */
        case REG_IPCSYNC:
            return sync_arm7_out | (sync_arm9_out << 8) | (rd32(offset) & 0x4000u);
        case REG_IPCFIFOCNT:
            return fifocnt_read();
        case REG_IPCFIFOSEND:
            return 0;
        case REG_ROMCTRL:
            return card_romctrl();
        case REG_GXSTAT:
            /* the FIFO IRQ selection (bits 30-31) is storage here; the rest is engine state */
            return (rd32(offset) & 0xc0000000u) | gpu3d_read(offset);
        case REG_RAM_COUNT:
            return gpu3d_read(offset);
        default:
            if (offset >= REG_POS_RESULT && offset < REG_VECMTX_RESULT_END) {
                return gpu3d_read(offset); /* the test and matrix results */
            }
            return rd32(offset);
    }
}

/* A write of the bits `mask` of the 32-bit register at `offset`. */
static void reg_write32(uint32_t offset, uint32_t value, uint32_t mask)
{
    uint32_t old = rd32(offset);
    uint32_t merged = (old & ~mask) | (value & mask);
    switch (offset) {
        case REG_DISPSTAT: /* bits 0-2 are status; VCOUNT is read-only */
            st32(offset, (old & 0xffff0007u) | (merged & 0xfff8u));
            return;
        case REG_IF:
            if (trace_irq && the_cpu) {
                fprintf(stderr,
                        "irq: ack %08x at step %llu"
                        "\n",
                        value & mask, (unsigned long long) the_cpu->steps);
            }
            st32(offset, old & ~(value & mask)); /* acknowledge by writing 1 */
            return;
        case REG_IPCSYNC:
            sync_arm9_out = (merged >> 8) & 0xf;
            st32(offset, merged & 0x4000u);
            return;
        case REG_IPCFIFOCNT:
            fifocnt_write(merged & 0xffffu);
            return;
        case REG_IPCFIFOSEND:
            fifo_send(merged);
            return;
        case REG_ROMCTRL:
            /* bits 23 (data ready) and 31 (busy) are state, not storage: card_romctrl */
            st32(offset, merged & ~((1u << 23) | (1u << 31)));
            if ((merged & (1u << 31)) && card_pos >= card_len) {
                card_start(merged);
                card_feed_dma();
                if (card_len == 0) {
                    card_finish();
                }
            }
            return;
        case REG_DIVCNT:
        case REG_DIV_NUMER:
        case REG_DIV_NUMER + 4:
        case REG_DIV_DENOM:
        case REG_DIV_DENOM + 4:
            st32(offset, merged);
            divide();
            return;
        case REG_SQRTCNT:
        case REG_SQRT_PARAM:
        case REG_SQRT_PARAM + 4:
            st32(offset, merged);
            square_root();
            return;
        case REG_GXSTAT:
            st32(offset, (old & ~0x8000u & ~(mask & 0xc0000000u)) | (merged & 0xc0000000u));
            gpu3d_gxstat_write(value & mask); /* bit 15: acknowledge the matrix stack error */
            io_gx_fifo_irq_update();
            return;
        case REG_DISP3DCNT:
            /* bits 12 (colour buffer underflow) and 13 (polygon/vertex RAM overflow) are
               status, acknowledged by writing 1; the rest is storage */
            st32(offset, (merged & ~0x3000u) | (old & 0x3000u & ~(value & mask)));
            gpu2d_register_written(offset, rd32(offset));
            return;
        default:
            break;
    }
    if (offset >= REG_DMA0SAD && offset <= REG_DMA3CNT) {
        st32(offset, merged);
        if ((offset - REG_DMA0SAD) % 12 == 8) {
            dma_write_cnt((int) ((offset - REG_DMA0SAD) / 12), old, merged);
        }
        return;
    }
    if (offset >= REG_TM0CNT && offset < REG_TM0CNT + 16) {
        st32(offset, merged);
        if (mask & 0xffff0000u) {
            timer_write_control((int) ((offset - REG_TM0CNT) / 4), old >> 16, merged >> 16);
        }
        return;
    }
    if (offset >= REG_VRAMCNT_A && offset <= REG_VRAMCNT_I + 2) {
        st32(offset, merged);
        rebuild_vram();
        return;
    }
    if (offset >= REG_GXFIFO && offset < REG_GXSTAT) {
        gxfifo_writes++;
        gpu3d_write(offset, merged); /* the packed FIFO or a command port (gpu3d.c) */
        io_gx_fifo_irq_update();
        return;
    }
    st32(offset, merged);
    if (offset < 0x70 || (offset >= 0x1000 && offset < 0x1070)) {
        gpu2d_register_written(offset, merged); /* display registers with write side effects */
    }
}

static int io_access_inner(uint32_t address, int size, uint32_t *value, int write)
{
    if (address - IO_BASE < IO_SIZE) {
        uint32_t offset = address - IO_BASE;
        uint32_t aligned = offset & ~3u, shift = (offset & 3) * 8;
        uint32_t mask = size == 4 ? 0xffffffffu : size == 2 ? 0xffffu : 0xffu;
        if (write) {
            reg_write32(aligned, *value << shift, mask << shift);
            sync_irq_line(); /* IME, IE, IF, or a register whose write raised a request */
        } else {
            *value = (reg_read32(aligned) >> shift) & mask;
        }
        return 1;
    }
    if (address == IPC_RECV) {
        if (!write) {
            *value = fifo_recv();
        }
        return 1;
    }
    if (address == CARD_DATA) {
        if (!write) {
            *value = card_read_word();
        }
        return 1;
    }
    if ((address >> 24) == 0x06) {
        uint8_t *p = vram_host(address, size);
        if (p == NULL) {
            if (write) {
                vram_unmapped_writes++;
            } else {
                vram_unmapped_reads++;
                *value = 0;
            }
            return 1;
        }
        if (write) {
            memcpy(p, value, (size_t) size);
        } else {
            *value = 0;
            memcpy(value, p, (size_t) size);
        }
        return 1;
    }
    if ((address >> 24) == 0x05 || (address >> 24) == 0x07) {
        uint8_t *p = ((address >> 24) == 0x05 ? palette : oam) + (address & 0x7ffu);
        if (write) {
            memcpy(p, value, (size_t) size);
        } else {
            *value = 0;
            memcpy(value, p, (size_t) size);
        }
        return 1;
    }
    if (address >= 0x08000000u && address < 0x0b000000u) {
        /* the GBA slot: empty, and given to the ARM7 by OS_InitLock. Reads give zero when the
           slot is the ARM7's; an empty slot the ARM9 owns reads as the address bus */
        if (!write) {
            *value = (rd16(REG_EXMEMCNT) & 0x80) ? 0 : (address >> 1) & 0xffffu;
        }
        return 1;
    }
    if (address >= 0xffff0000u && address < 0xffff8000u) {
        if (!write) {
            *value = 0; /* no BIOS image: its calls are handled in bios.c */
        }
        return 1;
    }
    return 0;
}

/* The logged address of an access: registers by exact address, large areas by page. */
static uint32_t log_address(uint32_t address)
{
    if (address - IO_BASE < IO_SIZE || address == IPC_RECV || address == CARD_DATA) {
        return address;
    }
    if ((address >> 24) == 0x06) {
        return address & ~0x3fffu;
    }
    if ((address >> 24) == 0x05 || (address >> 24) == 0x07) {
        return address & 0xff000000u;
    }
    if (address >= 0x08000000u && address < 0x0b000000u) {
        return address & 0xff000000u;
    }
    return address & 0xffff0000u;
}

int (*io_unmapped)(uint32_t address, int size, uint32_t *value, int write);

int io_read(void *user, uint32_t address, int size, uint32_t *value)
{
    (void) user;
    if (!io_access_inner(address, size, value, 0)) {
        return io_unmapped != NULL && io_unmapped(address, size, value, 0);
    }
    log_access(log_address(address), size, 0);
    return 1;
}

int io_write(void *user, uint32_t address, int size, uint32_t value)
{
    (void) user;
    if (!io_access_inner(address, size, &value, 1)) {
        return io_unmapped != NULL && io_unmapped(address, size, &value, 1);
    }
    log_access(log_address(address), size, 1);
    return 1;
}

int bus_read(uint32_t address, int size, uint32_t *value)
{
    uint8_t *p = memory_host(address, (uint32_t) size);
    if (p) {
        *value = 0;
        memcpy(value, p, (size_t) size);
        return 1;
    }
    return io_read(NULL, address, size, value);
}

int bus_write(uint32_t address, int size, uint32_t value)
{
    uint8_t *p = memory_host(address, (uint32_t) size);
    if (p) {
        memcpy(p, &value, (size_t) size);
        return 1;
    }
    return io_write(NULL, address, size, value);
}

/* Setup and the report --------------------------------------------------------------------- */

int io_init(const char *rom_path, ArmCpu *cpu)
{
    the_cpu = cpu;
    const char *trace = getenv("RUN_TRACE");
    trace_card = trace && strstr(trace, "card") != NULL;
    trace_pxi = trace && strstr(trace, "pxi") != NULL;
    trace_irq = trace && strstr(trace, "irq") != NULL;
    FILE *f = fopen(rom_path, "rb");
    if (f == NULL) {
        return -1;
    }
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    rom = malloc((size_t) size);
    if (rom == NULL || fread(rom, 1, (size_t) size, f) != (size_t) size) {
        fclose(f);
        return -1;
    }
    fclose(f);
    rom_size = (uint32_t) size;
    memset(regs, 0, sizeof(regs));
    st32(REG_GXSTAT, 0); /* every other register starts at zero, as after a reset */
    rebuild_vram();
    gpu3d_init();
    return 0;
}

typedef struct RegName {
    uint32_t address;
    const char *name;
} RegName;

static const RegName reg_names[] = {
    {0x000, "DISPCNT"},
    {0x004, "DISPSTAT"},
    {0x006, "VCOUNT"},
    {0x008, "BG0CNT"},
    {0x00a, "BG1CNT"},
    {0x00c, "BG2CNT"},
    {0x00e, "BG3CNT"},
    {0x010, "BG0HOFS"},
    {0x012, "BG0VOFS"},
    {0x014, "BG1HOFS"},
    {0x016, "BG1VOFS"},
    {0x018, "BG2HOFS"},
    {0x01a, "BG2VOFS"},
    {0x01c, "BG3HOFS"},
    {0x01e, "BG3VOFS"},
    {0x020, "BG2PA"},
    {0x022, "BG2PB"},
    {0x024, "BG2PC"},
    {0x026, "BG2PD"},
    {0x028, "BG2X"},
    {0x02c, "BG2Y"},
    {0x030, "BG3PA"},
    {0x032, "BG3PB"},
    {0x034, "BG3PC"},
    {0x036, "BG3PD"},
    {0x038, "BG3X"},
    {0x03c, "BG3Y"},
    {0x040, "WIN0H"},
    {0x042, "WIN1H"},
    {0x044, "WIN0V"},
    {0x046, "WIN1V"},
    {0x048, "WININ"},
    {0x04a, "WINOUT"},
    {0x04c, "MOSAIC"},
    {0x050, "BLDCNT"},
    {0x052, "BLDALPHA"},
    {0x054, "BLDY"},
    {0x060, "DISP3DCNT"},
    {0x064, "DISPCAPCNT"},
    {0x068, "DISP_MMEM_FIFO"},
    {0x06c, "MASTER_BRIGHT"},
    {0x0b0, "DMA0SAD"},
    {0x0b4, "DMA0DAD"},
    {0x0b8, "DMA0CNT"},
    {0x0bc, "DMA1SAD"},
    {0x0c0, "DMA1DAD"},
    {0x0c4, "DMA1CNT"},
    {0x0c8, "DMA2SAD"},
    {0x0cc, "DMA2DAD"},
    {0x0d0, "DMA2CNT"},
    {0x0d4, "DMA3SAD"},
    {0x0d8, "DMA3DAD"},
    {0x0dc, "DMA3CNT"},
    {0x0e0, "DMA0FILL"},
    {0x0e4, "DMA1FILL"},
    {0x0e8, "DMA2FILL"},
    {0x0ec, "DMA3FILL"},
    {0x100, "TM0CNT_L"},
    {0x102, "TM0CNT_H"},
    {0x104, "TM1CNT_L"},
    {0x106, "TM1CNT_H"},
    {0x108, "TM2CNT_L"},
    {0x10a, "TM2CNT_H"},
    {0x10c, "TM3CNT_L"},
    {0x10e, "TM3CNT_H"},
    {0x130, "KEYINPUT"},
    {0x132, "KEYCNT"},
    {0x180, "IPCSYNC"},
    {0x184, "IPCFIFOCNT"},
    {0x188, "IPCFIFOSEND"},
    {0x1a0, "AUXSPICNT"},
    {0x1a2, "AUXSPIDATA"},
    {0x1a4, "ROMCTRL"},
    {0x1a8, "CARD_CMD"},
    {0x1ac, "CARD_CMD+4"},
    {0x1b0, "CARD_SEED0_L"},
    {0x1b4, "CARD_SEED1_L"},
    {0x1b8, "CARD_SEED0_H"},
    {0x1ba, "CARD_SEED1_H"},
    {0x204, "EXMEMCNT"},
    {0x208, "IME"},
    {0x210, "IE"},
    {0x214, "IF"},
    {0x240, "VRAMCNT_A"},
    {0x241, "VRAMCNT_B"},
    {0x242, "VRAMCNT_C"},
    {0x243, "VRAMCNT_D"},
    {0x244, "VRAMCNT_E"},
    {0x245, "VRAMCNT_F"},
    {0x246, "VRAMCNT_G"},
    {0x247, "WRAMCNT"},
    {0x248, "VRAMCNT_H"},
    {0x249, "VRAMCNT_I"},
    {0x280, "DIVCNT"},
    {0x290, "DIV_NUMER"},
    {0x294, "DIV_NUMER_H"},
    {0x298, "DIV_DENOM"},
    {0x29c, "DIV_DENOM_H"},
    {0x2a0, "DIV_RESULT"},
    {0x2a4, "DIV_RESULT_H"},
    {0x2a8, "DIVREM_RESULT"},
    {0x2ac, "DIVREM_RESULT_H"},
    {0x2b0, "SQRTCNT"},
    {0x2b4, "SQRT_RESULT"},
    {0x2b8, "SQRT_PARAM"},
    {0x2bc, "SQRT_PARAM_H"},
    {0x300, "POSTFLG"},
    {0x304, "POWCNT1"},
    {0x320, "RDLINES_COUNT"},
    {0x330, "EDGE_COLOR"},
    {0x340, "ALPHA_TEST_REF"},
    {0x350, "CLEAR_COLOR"},
    {0x354, "CLEAR_DEPTH"},
    {0x356, "CLRIMAGE_OFFSET"},
    {0x358, "FOG_COLOR"},
    {0x35c, "FOG_OFFSET"},
    {0x360, "FOG_TABLE"},
    {0x380, "TOON_TABLE"},
    {0x400, "GXFIFO"},
    {0x440, "MTX_MODE"},
    {0x444, "MTX_PUSH"},
    {0x448, "MTX_POP"},
    {0x44c, "MTX_STORE"},
    {0x450, "MTX_RESTORE"},
    {0x454, "MTX_IDENTITY"},
    {0x458, "MTX_LOAD_4x4"},
    {0x45c, "MTX_LOAD_4x3"},
    {0x460, "MTX_MULT_4x4"},
    {0x464, "MTX_MULT_4x3"},
    {0x468, "MTX_MULT_3x3"},
    {0x46c, "MTX_SCALE"},
    {0x470, "MTX_TRANS"},
    {0x480, "COLOR"},
    {0x484, "NORMAL"},
    {0x488, "TEXCOORD"},
    {0x48c, "VTX_16"},
    {0x490, "VTX_10"},
    {0x494, "VTX_XY"},
    {0x498, "VTX_XZ"},
    {0x49c, "VTX_YZ"},
    {0x4a0, "VTX_DIFF"},
    {0x4a4, "POLYGON_ATTR"},
    {0x4a8, "TEXIMAGE_PARAM"},
    {0x4ac, "PLTT_BASE"},
    {0x4c0, "DIF_AMB"},
    {0x4c4, "SPE_EMI"},
    {0x4c8, "LIGHT_VECTOR"},
    {0x4cc, "LIGHT_COLOR"},
    {0x4d0, "SHININESS"},
    {0x500, "BEGIN_VTXS"},
    {0x504, "END_VTXS"},
    {0x540, "SWAP_BUFFERS"},
    {0x580, "VIEWPORT"},
    {0x5c0, "BOX_TEST"},
    {0x5c4, "POS_TEST"},
    {0x5c8, "VEC_TEST"},
    {0x600, "GXSTAT"},
    {0x604, "RAM_COUNT"},
    {0x610, "DISP_1DOT_DEPTH"},
    {0x620, "POS_RESULT"},
    {0x630, "VEC_RESULT"},
    {0x640, "CLIPMTX_RESULT"},
    {0x680, "VECMTX_RESULT"},
    {0x1000, "DISPCNT_B"},
    {0x1008, "BG0CNT_B"},
    {0x100a, "BG1CNT_B"},
    {0x100c, "BG2CNT_B"},
    {0x100e, "BG3CNT_B"},
    {0x1010, "BG0HOFS_B"},
    {0x1012, "BG0VOFS_B"},
    {0x1014, "BG1HOFS_B"},
    {0x1016, "BG1VOFS_B"},
    {0x1018, "BG2HOFS_B"},
    {0x101a, "BG2VOFS_B"},
    {0x101c, "BG3HOFS_B"},
    {0x101e, "BG3VOFS_B"},
    {0x1020, "BG2PA_B"},
    {0x1022, "BG2PB_B"},
    {0x1024, "BG2PC_B"},
    {0x1026, "BG2PD_B"},
    {0x1028, "BG2X_B"},
    {0x102c, "BG2Y_B"},
    {0x1030, "BG3PA_B"},
    {0x1032, "BG3PB_B"},
    {0x1034, "BG3PC_B"},
    {0x1036, "BG3PD_B"},
    {0x1038, "BG3X_B"},
    {0x103c, "BG3Y_B"},
    {0x1040, "WIN0H_B"},
    {0x1042, "WIN1H_B"},
    {0x1044, "WIN0V_B"},
    {0x1046, "WIN1V_B"},
    {0x1048, "WININ_B"},
    {0x104a, "WINOUT_B"},
    {0x104c, "MOSAIC_B"},
    {0x1050, "BLDCNT_B"},
    {0x1052, "BLDALPHA_B"},
    {0x1054, "BLDY_B"},
    {0x106c, "MASTER_BRIGHT_B"},
};

const char *io_register_name(uint32_t address)
{
    static char buf[32];
    if (address == IPC_RECV) {
        return "IPCFIFORECV";
    }
    if (address == CARD_DATA) {
        return "CARD_DATA";
    }
    if ((address >> 24) == 0x06) {
        return "VRAM";
    }
    if ((address >> 24) == 0x05) {
        return "PALETTE";
    }
    if ((address >> 24) == 0x07) {
        return "OAM";
    }
    if (address >= 0x08000000u && address < 0x0b000000u) {
        return "GBA_SLOT";
    }
    if (address >= 0xffff0000u) {
        return "BIOS";
    }
    uint32_t offset = address - IO_BASE;
    const RegName *best = NULL;
    for (size_t i = 0; i < sizeof(reg_names) / sizeof(reg_names[0]); i++) {
        if (reg_names[i].address <= offset && (best == NULL || reg_names[i].address > best->address)) {
            best = &reg_names[i];
        }
    }
    if (best == NULL) {
        return "?";
    }
    if (best->address == offset) {
        return best->name;
    }
    if (offset >= 0x360 && offset < 0x3c0) {
        return offset < 0x380 ? "FOG_TABLE" : "TOON_TABLE";
    }
    snprintf(buf, sizeof(buf), "%s+%u", best->name, offset - best->address);
    return buf;
}

void io_report(FILE *out)
{
    fprintf(out, "clock: %llu bus cycles, frame %u line %u\n", (unsigned long long) clock_cycles, frame_count, vcount);
    fprintf(out, "card: %llu read commands, %u unknown commands; gx fifo writes %llu; vram unmapped r/w %llu/%llu\n",
            (unsigned long long) card_reads, card_unknown_commands, (unsigned long long) gxfifo_writes,
            (unsigned long long) vram_unmapped_reads, (unsigned long long) vram_unmapped_writes);
    fprintf(out, "dma runs by timing: imm %llu vbl %llu hbl %llu disp %llu mmem %llu card %llu gba %llu gx %llu\n",
            (unsigned long long) dma_runs[0], (unsigned long long) dma_runs[1], (unsigned long long) dma_runs[2],
            (unsigned long long) dma_runs[3], (unsigned long long) dma_runs[4], (unsigned long long) dma_runs[5],
            (unsigned long long) dma_runs[6], (unsigned long long) dma_runs[7]);
    fprintf(out, "ipc: sync arm9->%x arm7->%x, fifo to7 %u to9 %u, IME %x IE %08x IF %08x\n", sync_arm9_out, sync_arm7_out,
            to7_count, to9_count, rd32(REG_IME), rd32(REG_IE), rd32(REG_IF));
    gpu3d_report(out);
}
