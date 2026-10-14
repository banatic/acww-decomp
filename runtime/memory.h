/* The DS's ARM9 memory, at its own addresses in this process.
 *
 * The program is 32-bit and maps ITCM, main RAM and DTCM where the DS has them, so a DS
 * address is a host pointer and code compiled for the PC (Native, Clean) uses the game's own
 * pointers and structure layouts unchanged.
 */
#ifndef RUNTIME_MEMORY_H
#define RUNTIME_MEMORY_H

#include <stddef.h>
#include <stdint.h>

#define MEM_ITCM_BASE 0x01ff8000u
#define MEM_ITCM_SIZE 0x00008000u
#define MEM_MAIN_BASE 0x02000000u
#define MEM_MAIN_SIZE 0x00400000u
#define MEM_DTCM_BASE 0x027e0000u
#define MEM_DTCM_SIZE 0x00004000u
/* Main RAM repeats every 4 MiB up to 0x02ffffff; the game uses the copy of its last bytes at
 * 0x027ffxxx (the area the ARM7 shares). The last 64 KiB of that copy are mapped. */
#define MEM_MAIN_MIRROR_STEP 0x00400000u
#define MEM_MIRROR_BASE 0x027f0000u
#define MEM_MIRROR_SIZE 0x00010000u

/* Reserve and zero the regions; 0 on success. */
int memory_init(void);

/* The host pointer for [address, address + size) when it lies inside one region, else NULL. */
static inline uint8_t *memory_host(uint32_t address, uint32_t size)
{
    if ((address - MEM_MAIN_BASE) <= MEM_MAIN_SIZE - size || (address - MEM_ITCM_BASE) <= MEM_ITCM_SIZE - size ||
        (address - MEM_DTCM_BASE) <= MEM_DTCM_SIZE - size || (address - MEM_MIRROR_BASE) <= MEM_MIRROR_SIZE - size) {
        return (uint8_t *) (uintptr_t) address;
    }
    return NULL;
}

/* A copy of every region, and putting one back. */
typedef struct MemorySnapshot MemorySnapshot;
MemorySnapshot *memory_snapshot(void);
void memory_restore(const MemorySnapshot *snapshot);
void memory_snapshot_free(MemorySnapshot *snapshot);

/* Calls `found` for every run of bytes that differs between a snapshot and memory now,
 * skipping [skip_lo, skip_hi). */
void memory_diff(const MemorySnapshot *before, uint32_t skip_lo, uint32_t skip_hi,
                 void (*found)(void *user, uint32_t address, const uint8_t *was, const uint8_t *now, size_t size), void *user);

#endif
