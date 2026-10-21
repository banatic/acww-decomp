#ifndef _WIN32
#define _GNU_SOURCE /* MAP_ANONYMOUS, MAP_FIXED_NOREPLACE, memfd_create */
#endif

#include "memory.h"

#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/mman.h>
#include <unistd.h>
#endif

#if UINTPTR_MAX != 0xffffffffu
#error "the runtime is a 32-bit program: DS addresses are host pointers"
#endif

/* The regions a snapshot covers. The mirror is the same memory as the end of main RAM. */
static const struct {
    uint32_t base;
    uint32_t size;
} regions[] = {
    {MEM_ITCM_BASE, MEM_ITCM_SIZE},
    {MEM_MAIN_BASE, MEM_MAIN_SIZE},
    {MEM_DTCM_BASE, MEM_DTCM_SIZE},
};
#define REGION_COUNT (sizeof(regions) / sizeof(regions[0]))

#ifndef _WIN32
/* The kernel starts the heap (brk) right after the image, at a random offset of up to 32 MiB:
 * after an image at 0x00400000 that can be the DS's memory (0x01ff8000-0x02800000), taken by
 * the first malloc (an fopen, say) before memory_init maps it. tools/run.py and
 * tools/diffcheck.py link this section at 0x10000000, above every DS address, so the image
 * ends, and the heap starts, there. */
__attribute__((section(".heap_floor"), used)) static char heap_floor = 1;
#endif

/* Private memory at a fixed address. Windows reserves on 64 KiB boundaries. */
static int reserve(uint32_t base, uint32_t size)
{
    uint32_t end = (base + size + 0xffffu) & ~0xffffu;
    base &= ~0xffffu;
    size = end - base;
    void *want = (void *) (uintptr_t) base;
#ifdef _WIN32
    void *got = VirtualAlloc(want, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
#else
    void *got = mmap(want, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0);
    if (got == MAP_FAILED) {
        got = NULL;
    }
#endif
    return got == want ? 0 : -1;
}

/* Main RAM, mapped twice: at its address and, for its last 64 KiB, at the mirror. */
static int map_main(void)
{
    uint32_t offset = MEM_MIRROR_BASE - MEM_MAIN_MIRROR_STEP;
#ifdef _WIN32
    HANDLE h = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, MEM_MAIN_SIZE, NULL);
    if (h == NULL) {
        return -1;
    }
    void *main = MapViewOfFileEx(h, FILE_MAP_ALL_ACCESS, 0, 0, MEM_MAIN_SIZE, (void *) (uintptr_t) MEM_MAIN_BASE);
    void *mirror = MapViewOfFileEx(h, FILE_MAP_ALL_ACCESS, 0, offset - MEM_MAIN_BASE, MEM_MIRROR_SIZE,
                                   (void *) (uintptr_t) MEM_MIRROR_BASE);
#else
    int fd = memfd_create("ds-main-ram", 0);
    if (fd < 0 || ftruncate(fd, MEM_MAIN_SIZE) != 0) {
        return -1;
    }
    void *main = mmap((void *) (uintptr_t) MEM_MAIN_BASE, MEM_MAIN_SIZE, PROT_READ | PROT_WRITE,
                      MAP_SHARED | MAP_FIXED_NOREPLACE, fd, 0);
    void *mirror = mmap((void *) (uintptr_t) MEM_MIRROR_BASE, MEM_MIRROR_SIZE, PROT_READ | PROT_WRITE,
                        MAP_SHARED | MAP_FIXED_NOREPLACE, fd, offset - MEM_MAIN_BASE);
#endif
    if (main != (void *) (uintptr_t) MEM_MAIN_BASE || mirror != (void *) (uintptr_t) MEM_MIRROR_BASE) {
        return -1;
    }
    return 0;
}

#ifndef _WIN32
int memory_unshare(void)
{
    /* main RAM and its mirror are one shared mapping, which a fork keeps shared: give this
       process a mapping of its own with the same contents */
    uint32_t offset = MEM_MIRROR_BASE - MEM_MAIN_MIRROR_STEP;
    uint8_t *copy = malloc(MEM_MAIN_SIZE);
    int fd = memfd_create("ds-main-ram", 0);
    if (copy == NULL || fd < 0 || ftruncate(fd, MEM_MAIN_SIZE) != 0) {
        free(copy);
        return -1;
    }
    memcpy(copy, (void *) (uintptr_t) MEM_MAIN_BASE, MEM_MAIN_SIZE);
    void *main =
        mmap((void *) (uintptr_t) MEM_MAIN_BASE, MEM_MAIN_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_FIXED, fd, 0);
    void *mirror = mmap((void *) (uintptr_t) MEM_MIRROR_BASE, MEM_MIRROR_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_FIXED,
                        fd, offset - MEM_MAIN_BASE);
    close(fd);
    if (main != (void *) (uintptr_t) MEM_MAIN_BASE || mirror != (void *) (uintptr_t) MEM_MIRROR_BASE) {
        free(copy);
        return -1;
    }
    memcpy((void *) (uintptr_t) MEM_MAIN_BASE, copy, MEM_MAIN_SIZE);
    free(copy);
    return 0;
}
#endif

int memory_init(void)
{
    static int done;
    if (done) {
        return 0;
    }
    if (reserve(MEM_ITCM_BASE, MEM_ITCM_SIZE) != 0 || map_main() != 0 || reserve(MEM_DTCM_BASE, MEM_DTCM_SIZE) != 0) {
        return -1;
    }
    for (size_t i = 0; i < REGION_COUNT; i++) {
        memset((void *) (uintptr_t) regions[i].base, 0, regions[i].size);
    }
    done = 1;
    return 0;
}

struct MemorySnapshot {
    uint8_t *copy[REGION_COUNT];
};

MemorySnapshot *memory_snapshot(void)
{
    MemorySnapshot *s = calloc(1, sizeof(*s));
    for (size_t i = 0; i < REGION_COUNT; i++) {
        s->copy[i] = malloc(regions[i].size);
        memcpy(s->copy[i], (void *) (uintptr_t) regions[i].base, regions[i].size);
    }
    return s;
}

void memory_restore(const MemorySnapshot *s)
{
    for (size_t i = 0; i < REGION_COUNT; i++) {
        memcpy((void *) (uintptr_t) regions[i].base, s->copy[i], regions[i].size);
    }
}

void memory_snapshot_free(MemorySnapshot *s)
{
    for (size_t i = 0; i < REGION_COUNT; i++) {
        free(s->copy[i]);
    }
    free(s);
}

void memory_diff(const MemorySnapshot *before, uint32_t skip_lo, uint32_t skip_hi,
                 void (*found)(void *user, uint32_t address, const uint8_t *was, const uint8_t *now, size_t size), void *user)
{
    for (size_t i = 0; i < REGION_COUNT; i++) {
        const uint8_t *was = before->copy[i];
        const uint8_t *now = (const uint8_t *) (uintptr_t) regions[i].base;
        uint32_t n = regions[i].size;
        for (uint32_t off = 0; off < n;) {
            /* most of memory is unchanged: skip equal blocks quickly */
            if ((off & 0x3ffu) == 0 && off + 0x400 <= n && memcmp(was + off, now + off, 0x400) == 0) {
                off += 0x400;
                continue;
            }
            uint32_t address = regions[i].base + off;
            if (was[off] == now[off] || (address >= skip_lo && address < skip_hi)) {
                off++;
                continue;
            }
            uint32_t end = off;
            while (end < n && was[end] != now[end]) {
                uint32_t a = regions[i].base + end;
                if (a >= skip_lo && a < skip_hi) {
                    break;
                }
                end++;
            }
            found(user, address, was + off, now + off, end - off);
            off = end;
        }
    }
}
