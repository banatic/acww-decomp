/* Drawing on a second thread (render.h). */
#include "render.h"

#include <stdlib.h>
#include <string.h>

#include "gpu2d.h"
#include "gpu3d.h"
#include "io.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <pthread.h>
#endif

/* The registers the renderers read (offsets from 0x04000000): both 2D engines' display
 * registers, VRAMCNT (the banks' mapping), POWCNT1 (the screens' order), the 3D rendering
 * registers (DISP3DCNT is among the first) and DISP_1DOT_DEPTH. */
static const struct {
    uint32_t start, end;
} SHIPPED[] = {{0x000, 0x070}, {0x240, 0x24c}, {0x304, 0x308}, {0x330, 0x3c0}, {0x610, 0x614}, {0x1000, 0x1070}};
#define SHIPPED_BYTES (0x70u + 0xcu + 0x4u + 0x90u + 0x4u + 0x70u)

#define R_DISPCAPCNT 0x064u

enum Kind { M_LINE, M_FRAME, M_WRITE, M_3D, M_DATA, M_WRAP };

/* A message: what changed (the registers when `regs` is set, then `chunks` pieces of video
 * memory), then the request. */
typedef struct Message {
    uint32_t kind, a, b;
    uint16_t regs, chunks;
} Message;

#define RING (32u << 20)
#define ALIGN 16u

static int threaded;   /* the thread runs */
static int direct = 1; /* this frame is drawn where it is asked for (no thread, or a capture) */
static uint8_t *ring;
static uint64_t head, tail; /* bytes written and consumed, under the lock */
static int waiting;         /* the thread waits for messages */
static uint64_t frames_queued, frames_drawn, renders_queued, renders_done, frames_here;

static IoVideo copy;                   /* the thread's state */
static uint8_t shipped[SHIPPED_BYTES]; /* the registers as last sent */
static int shipped_valid;
static uint32_t *dirty;

#ifdef _WIN32
static SRWLOCK lock = SRWLOCK_INIT;
static CONDITION_VARIABLE to_thread = CONDITION_VARIABLE_INIT, to_main = CONDITION_VARIABLE_INIT;
#define LOCK() AcquireSRWLockExclusive(&lock)
#define UNLOCK() ReleaseSRWLockExclusive(&lock)
#define WAIT(cv) SleepConditionVariableSRW(&(cv), &lock, INFINITE, 0)
#define WAKE(cv) WakeAllConditionVariable(&(cv))
#else
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t to_thread = PTHREAD_COND_INITIALIZER, to_main = PTHREAD_COND_INITIALIZER;
#define LOCK() pthread_mutex_lock(&lock)
#define UNLOCK() pthread_mutex_unlock(&lock)
#define WAIT(cv) pthread_cond_wait(&(cv), &lock)
#define WAKE(cv) pthread_cond_broadcast(&(cv))
#endif

/* The thread ------------------------------------------------------------------------------ */

static void apply_regs(const uint8_t *p)
{
    uint8_t before[0xc];
    memcpy(before, copy.regs + 0x240, sizeof(before));
    for (size_t i = 0; i < sizeof(SHIPPED) / sizeof(SHIPPED[0]); i++) {
        uint32_t n = SHIPPED[i].end - SHIPPED[i].start;
        memcpy(copy.regs + SHIPPED[i].start, p, n);
        p += n;
    }
    if (memcmp(before, copy.regs + 0x240, sizeof(before)) != 0) {
        io_video_map(&copy); /* VRAMCNT: the banks are mapped elsewhere */
    }
}

static void handle(const Message *m)
{
    const uint8_t *p = (const uint8_t *) (m + 1);
    if (m->regs) {
        apply_regs(p);
        p += SHIPPED_BYTES;
    }
    for (uint32_t i = 0; i < m->chunks; i++) {
        uint32_t chunk;
        memcpy(&chunk, p, 4);
        memcpy(copy.mem + chunk * IO_VIDEO_CHUNK, p + 4, IO_VIDEO_CHUNK);
        p += 4 + IO_VIDEO_CHUNK;
    }
    switch (m->kind) {
        case M_LINE:
            gpu2d_line(m->a);
            break;
        case M_FRAME:
            gpu2d_frame_output(m->a);
            break;
        case M_WRITE:
            gpu2d_register_written(m->a, m->b);
            break;
        case M_3D:
            gpu3d_render((int) m->a);
            break;
        default:
            break;
    }
}

static uint32_t message_size(const Message *m)
{
    uint32_t n = (uint32_t) sizeof(Message) + (m->regs ? SHIPPED_BYTES : 0) + m->chunks * (4 + IO_VIDEO_CHUNK);
    return (n + ALIGN - 1) & ~(ALIGN - 1);
}

static void run_thread(void)
{
    LOCK();
    for (;;) {
        while (tail == head) {
            waiting = 1;
            WAIT(to_thread);
            waiting = 0;
        }
        uint64_t end = head;
        UNLOCK();
        uint64_t at = tail;
        uint64_t frames = 0, renders = 0;
        while (at < end) {
            const Message *m = (const Message *) (ring + at % RING);
            if (m->kind == M_WRAP) {
                at += RING - at % RING;
                continue;
            }
            handle(m);
            frames += m->kind == M_FRAME;
            renders += m->kind == M_3D;
            at += message_size(m);
        }
        LOCK();
        tail = at;
        frames_drawn += frames;
        renders_done += renders;
        WAKE(to_main);
    }
}

#ifdef _WIN32
static DWORD WINAPI thread_main(LPVOID unused)
{
    (void) unused;
    run_thread();
    return 0;
}
#else
static void *thread_main(void *unused)
{
    (void) unused;
    run_thread();
    return NULL;
}
#endif

/* The emulation's side --------------------------------------------------------------------- */

/* Under the lock: lets the thread go on with what it has been sent, and waits for it to
 * report progress. */
static void wait_for_thread(void)
{
    if (waiting) {
        WAKE(to_thread);
    }
    WAIT(to_main);
}

/* Room for `size` contiguous bytes, the thread having consumed enough. */
static uint8_t *reserve(uint32_t size)
{
    LOCK();
    if (head % RING + size > RING) {
        while (RING - (head - tail) < RING - head % RING) {
            wait_for_thread();
        }
        Message *wrap = (Message *) (ring + head % RING);
        wrap->kind = M_WRAP;
        head += RING - head % RING;
    }
    while (RING - (head - tail) < size) {
        wait_for_thread();
    }
    UNLOCK();
    return ring + head % RING;
}

/* The message is complete. The thread is woken for some of them only (`wake`): it draws a
 * batch of lines at a time, and every wait for it wakes it first. */
static void publish(uint32_t size, int wake)
{
    LOCK();
    head += size;
    if (waiting && wake) {
        WAKE(to_thread);
    }
    UNLOCK();
}

/* A request, with the registers if they changed and every piece of video memory written
 * since the last one. */
static void post_request(uint32_t kind, uint32_t a, uint32_t b, int wake)
{
    const IoVideo *live = io_video_live();
    uint8_t regs[SHIPPED_BYTES], *r = regs;
    for (size_t i = 0; i < sizeof(SHIPPED) / sizeof(SHIPPED[0]); i++) {
        uint32_t n = SHIPPED[i].end - SHIPPED[i].start;
        memcpy(r, live->regs + SHIPPED[i].start, n);
        r += n;
    }
    int changed = !shipped_valid || memcmp(regs, shipped, SHIPPED_BYTES) != 0;
    uint32_t chunks = io_video_take_dirty(dirty);
    /* (a message's chunk count is 16 bits: more go in messages of their own first) */
    uint32_t done = 0;
    while (chunks - done > 0xffffu) {
        Message m = {M_DATA, 0, 0, 0, 0xffff};
        uint8_t *at = reserve(message_size(&m));
        memcpy(at, &m, sizeof(m));
        uint8_t *p = at + sizeof(m);
        for (uint32_t i = 0; i < 0xffffu; i++, done++) {
            memcpy(p, &dirty[done], 4);
            memcpy(p + 4, live->mem + dirty[done] * IO_VIDEO_CHUNK, IO_VIDEO_CHUNK);
            p += 4 + IO_VIDEO_CHUNK;
        }
        publish(message_size(&m), 0);
    }
    Message m = {kind, a, b, (uint16_t) changed, (uint16_t) (chunks - done)};
    uint32_t size = message_size(&m);
    uint8_t *at = reserve(size);
    memcpy(at, &m, sizeof(m));
    uint8_t *p = at + sizeof(m);
    if (changed) {
        memcpy(p, regs, SHIPPED_BYTES);
        memcpy(shipped, regs, SHIPPED_BYTES);
        shipped_valid = 1;
        p += SHIPPED_BYTES;
    }
    for (; done < chunks; done++) {
        memcpy(p, &dirty[done], 4);
        memcpy(p + 4, live->mem + dirty[done] * IO_VIDEO_CHUNK, IO_VIDEO_CHUNK);
        p += 4 + IO_VIDEO_CHUNK;
    }
    publish(size, wake);
}

/* Waits until the thread has drawn everything sent. */
static void drain(void)
{
    LOCK();
    while (tail != head) {
        wait_for_thread();
    }
    UNLOCK();
}

void render_init(void)
{
    const char *want = getenv("RUN_RENDER_THREAD");
    const char *trace = getenv("RUN_TRACE");
    if ((want != NULL && atoi(want) == 0) || getenv("RUN_DUMP3D") != NULL || (trace != NULL && strstr(trace, "gx"))) {
        return;
    }
    ring = malloc(RING);
    copy.regs = calloc(1, IO_REG_SIZE);
    copy.mem = calloc(1, IO_VIDEO_SIZE);
    dirty = malloc(sizeof(uint32_t) * (IO_VIDEO_SIZE / IO_VIDEO_CHUNK));
    if (ring == NULL || copy.regs == NULL || copy.mem == NULL || dirty == NULL) {
        fprintf(stderr, "render: no memory for the thread\n");
        return;
    }
    io_video_map(&copy);
#ifdef _WIN32
    HANDLE t = CreateThread(NULL, 0, thread_main, NULL, 0, NULL);
    if (t == NULL) {
        fprintf(stderr, "render: cannot start the thread\n");
        return;
    }
    CloseHandle(t);
#else
    pthread_t t;
    if (pthread_create(&t, NULL, thread_main, NULL) != 0) {
        fprintf(stderr, "render: cannot start the thread\n");
        return;
    }
    pthread_detach(t);
#endif
    threaded = 1;
    atexit(render_finish);
}

void render_line(uint32_t y)
{
    if (threaded && y == 0) {
        /* A display capture writes VRAM, which the CPU may read back: its frame is drawn
           here, from the live state (the capture starts with line 0, gpu2d.c). */
        int capture = (io_video_live()->regs[R_DISPCAPCNT + 3] & 0x80) != 0;
        if (capture && !direct) {
            drain();
            io_view = io_video_live();
            direct = 1;
        } else if (!capture && direct) {
            io_view = &copy; /* the thread idle: the copy catches up from the next message */
            direct = 0;
        }
    }
    if (direct) {
        gpu2d_line(y);
        return;
    }
    post_request(M_LINE, y, 0, y % 32 == 31);
}

void render_frame_end(uint32_t frame)
{
    if (direct) {
        gpu2d_frame_output(frame);
        gpu2d_capture_end();
        frames_here += threaded;
        return;
    }
    post_request(M_FRAME, frame, 0, 1);
    frames_queued++;
    /* at most one frame behind */
    LOCK();
    while (frames_drawn + 1 < frames_queued) {
        wait_for_thread();
    }
    UNLOCK();
}

void render_register_written(uint32_t offset, uint32_t value)
{
    if (direct) {
        gpu2d_register_written(offset, value);
        return;
    }
    post_request(M_WRITE, offset, value, 0);
}

void render_3d(int list)
{
    if (direct) {
        gpu3d_render(list);
        return;
    }
    /* The list the last one drew is the next the geometry engine fills (gpu3d.c). */
    LOCK();
    while (renders_done < renders_queued) {
        wait_for_thread();
    }
    UNLOCK();
    post_request(M_3D, (uint32_t) list, 0, 1);
    renders_queued++;
}

void render_report(FILE *out)
{
    if (threaded) {
        render_finish();
        fprintf(out, "render: %llu frames drawn on the thread, %llu here (display captures)\n",
                (unsigned long long) frames_drawn, (unsigned long long) frames_here);
    }
}

void render_finish(void)
{
    if (threaded) {
        drain();
    }
}
