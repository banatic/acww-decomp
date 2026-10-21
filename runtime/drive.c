/* Driving a run from another program; see drive.h. */
#include "drive.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "frame.h"
#include "input.h"
#include "io.h"
#include "memory.h"

#if !defined(_WIN32)
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define DRIVE_SNAP 1
#endif

void run_finish(const char *reason, int status);

static int enabled = -1;

/* Function entries: a bit per halfword from ITCM to the end of main RAM marks a start; the
 * entries seen are kept with their first 8 bytes. */
#define STARTS_BASE 0x01ff8000u
#define STARTS_END 0x02400000u
static uint8_t *starts;
typedef struct Entry {
    uint32_t address, w0, w1;
} Entry;
static Entry *seen;
static uint32_t seen_mask, seen_count;

static void starts_load(void)
{
    const char *path = getenv("RUN_DRIVE_STARTS");
    FILE *f = path != NULL && *path ? fopen(path, "r") : NULL;
    if (f == NULL) {
        return;
    }
    starts = calloc((STARTS_END - STARTS_BASE) / 16 + 1, 1);
    unsigned a;
    while (fscanf(f, "%x", &a) == 1) {
        a &= ~1u;
        if (a >= STARTS_BASE && a < STARTS_END) {
            uint32_t i = (a - STARTS_BASE) >> 1;
            starts[i >> 3] |= (uint8_t) (1u << (i & 7));
        }
    }
    fclose(f);
    seen_mask = (1u << 16) - 1;
    seen = calloc(seen_mask + 1, sizeof(Entry));
}

static void seen_insert(uint32_t address, uint32_t w0, uint32_t w1);

static void seen_grow(void)
{
    Entry *old = seen;
    uint32_t n = seen_mask + 1;
    seen_mask = n * 2 - 1;
    seen = calloc(n * 2, sizeof(Entry));
    seen_count = 0;
    for (uint32_t i = 0; i < n; i++) {
        if (old[i].address) {
            seen_insert(old[i].address, old[i].w0, old[i].w1);
        }
    }
    free(old);
}

static void seen_insert(uint32_t address, uint32_t w0, uint32_t w1)
{
    uint32_t h = (address * 2654435761u) ^ (w0 * 40503u) ^ w1;
    for (uint32_t i = h & seen_mask;; i = (i + 1) & seen_mask) {
        Entry *e = &seen[i];
        if (e->address == 0) {
            e->address = address;
            e->w0 = w0;
            e->w1 = w1;
            if (++seen_count * 2 > seen_mask) {
                seen_grow();
            }
            return;
        }
        if (e->address == address && e->w0 == w0 && e->w1 == w1) {
            return;
        }
    }
}

void drive_branch(uint32_t address)
{
    if (starts == NULL || address < STARTS_BASE || address >= STARTS_END) {
        return;
    }
    uint32_t i = (address - STARTS_BASE) >> 1;
    if (!(starts[i >> 3] & (1u << (i & 7)))) {
        return;
    }
    const uint8_t *p = memory_host(address, 8);
    if (p == NULL) {
        return;
    }
    uint32_t w0, w1;
    memcpy(&w0, p, 4);
    memcpy(&w1, p + 4, 4);
    seen_insert(address, w0, w1);
}

static int seen_write(const char *path)
{
    FILE *f = fopen(path, "w");
    if (f == NULL) {
        return -1;
    }
    for (uint32_t i = 0; i <= seen_mask && seen != NULL; i++) {
        if (seen[i].address) {
            fprintf(f, "%08x %08x %08x\n", seen[i].address, seen[i].w0, seen[i].w1);
        }
    }
    return fclose(f);
}
static uint32_t until; /* stop at the first frame >= until */

int drive_enabled(void)
{
    if (enabled < 0) {
        const char *v = getenv("RUN_DRIVE");
        enabled = v != NULL && *v && strcmp(v, "0") != 0;
        if (enabled) {
            starts_load();
        }
    }
    return enabled;
}

static void answer(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
static void answer(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
    putchar('\n');
    fflush(stdout);
}

#ifdef DRIVE_SNAP
/* A copy waits stopped; each time it is continued it forks, and the child carries on as the
 * run while the copy waits again. */
static int snapshot(void)
{
    fflush(stdout);
    pid_t pid = fork();
    if (pid < 0) {
        return -1;
    }
    if (pid > 0) {
        return (int) pid; /* the run */
    }
    signal(SIGHUP, SIG_IGN); /* kept when the run that made it ends */
    for (;;) {
        raise(SIGSTOP);
        pid_t live = fork();
        if (live == 0) {
            return 0; /* the run again, from here */
        }
        if (live > 0) {
            int st;
            waitpid(live, &st, 0); /* one run at a time from this copy */
        }
    }
}
#endif

void drive_frame(uint32_t frame)
{
    if (frame < until) {
        return;
    }
    answer("@ok frame %u", frame);
    char line[1024];
    for (;;) {
        if (fgets(line, sizeof(line), stdin) == NULL) {
            exit(0);
        }
        line[strcspn(line, "\r\n")] = 0;
        char cmd[32] = "", a[512] = "", b[256] = "", c[64] = "";
        int n = sscanf(line, "%31s %511s %255s %63s", cmd, a, b, c);
        if (n <= 0) {
            continue;
        }
        if (strcmp(cmd, "run") == 0 && n >= 2) {
            uint32_t frames = (uint32_t) strtoul(a, NULL, 0);
            if (n >= 3 && input_drive_set(frame, b, n >= 4 ? c : "-") != 0) {
                answer("@err bad input '%s %s'", b, n >= 4 ? c : "-");
                continue;
            }
            until = frame + (frames ? frames : 1);
            return;
        } else if (strcmp(cmd, "frame") == 0) {
            answer("@ok frame %u", frame);
        } else if (strcmp(cmd, "png") == 0 && n >= 2) {
            answer(frame_last_png(a) == 0 ? "@ok" : "@err cannot write %s", a);
        } else if (strcmp(cmd, "peek") == 0 && n >= 3) {
            uint32_t addr = (uint32_t) strtoul(a, NULL, 16), len = (uint32_t) strtoul(b, NULL, 0);
            /* memory_host takes sizes up to the smallest region's (DTCM) */
            const uint8_t *p = len && len <= MEM_DTCM_SIZE ? memory_host(addr, len) : NULL;
            if (p == NULL && len && len <= 0x10000 && addr >= 0x04000000u && addr < 0x08000000u) {
                /* the I/O registers as stored (without a read's side effects), and palette
                   RAM, VRAM and OAM through the bus */
                printf("@ok ");
                for (uint32_t i = 0; i < len; i++) {
                    uint32_t v = 0, at = addr + i;
                    if (at < 0x05000000u) {
                        v = io_reg(at & ~3u) >> ((at & 3) * 8);
                    } else {
                        bus_read(at, 1, &v);
                    }
                    printf("%02x", v & 0xff);
                }
                answer("%s", "");
                continue;
            }
            if (p == NULL) {
                answer("@err no memory at %08x+%u", addr, len);
                continue;
            }
            printf("@ok ");
            for (uint32_t i = 0; i < len; i++) {
                printf("%02x", p[i]);
            }
            answer("%s", "");
        } else if (strcmp(cmd, "seen") == 0 && n >= 2) {
            answer(seen_write(a) == 0 ? "@ok %u" : "@err cannot write", seen_count);
        } else if (strcmp(cmd, "log") == 0 && n >= 2) {
            answer(input_write_log(a) == 0 ? "@ok" : "@err cannot write %s", a);
#ifdef DRIVE_SNAP
        } else if (strcmp(cmd, "snap") == 0) {
            int id = snapshot();
            if (id > 0) {
                answer("@ok %d", id);
            } else if (id < 0) {
                answer("@err fork failed");
            } /* id 0: a copy continued by `back`, which waits for the frame line */
            if (id == 0) {
                answer("@ok frame %u", frame);
            }
        } else if (strcmp(cmd, "back") == 0 && n >= 2) {
            fflush(stdout);
            if (kill((pid_t) atoi(a), SIGCONT) != 0) {
                answer("@err no copy %s", a);
                continue;
            }
            _exit(0);
#endif
        } else if (strcmp(cmd, "quit") == 0) {
            run_finish("ended by the driver", 0);
        } else {
            answer("@err unknown command '%s'", line);
        }
    }
}
