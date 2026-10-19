/* The screen shown after an exception or a fatal error (debug_screen.h). */
#include "debug_screen.h"

#include <assert.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#include "clean.h"
#include "autoload_2/heap.h"
#include "autoload_2/process.h"
#include "debug_text.h"
#include "display_frame.h"
#include "main/game_halt.h"

static_assert(offsetof(ExceptionContext, spsr) == 0x64, "ExceptionContext layout");

#define REG16(address) (*(volatile u16 *) (address))
#define REG32(address) (*(volatile u32 *) (address))
#define REG_DISPCNT REG32(0x04000000)
#define REG_VCOUNT REG16(0x04000006)
#define REG_BG1CNT REG16(0x0400000a)
#define REG_BLDCNT REG16(0x04000050)
#define REG_KEYINPUT REG16(0x04000130)
#define REG_IME REG16(0x04000208)
#define REG_POWCNT1 REG16(0x04000304)
#define REG_DB_DISPCNT REG32(0x04001000)
#define REG_DB_BG1CNT REG16(0x0400100a)
#define REG_DB_BLDCNT REG16(0x04001050)
#define BG_PALETTE ((volatile u16 *) 0x05000000)
#define DB_BG_PALETTE ((volatile u16 *) 0x05000400)
/* X, Y, the debug button and the hinge, as the ARM7 leaves them; bits set when released */
#define EXTRA_BUTTONS (*(const u16 *) 0x027fffa8)

enum Buttons {
    PAD_A = 0x001,
    PAD_B = 0x002,
    PAD_SELECT = 0x004,
    PAD_START = 0x008,
    PAD_RIGHT = 0x010,
    PAD_LEFT = 0x020,
    PAD_UP = 0x040,
    PAD_DOWN = 0x080,
    PAD_R = 0x100,
    PAD_L = 0x200,
    PAD_DEBUG = 0x2000,
    PAD_ALL = 0x2fff,    /* every button the SDK reads */
    PAD_KEYINPUT = 0x3ff /* the ten of KEYINPUT */
};

/* The states of the key sequence that unlocks the screen. */
enum DebugScreenState {
    WAIT_FIRST_CHORD, /* L+R+Left+A */
    WAIT_FIRST_RELEASE,
    WAIT_SECOND_CHORD, /* Down+B */
    WAIT_SECOND_RELEASE,
    WAIT_THIRD_CHORD, /* Select+Start */
    SHOW_FIRST,       /* set the display up, then as SHOWING */
    SHOWING
};

#define OS_PROCMODE_SYS 0x1f
#define ROW 32                /* characters per row of a screen */
#define PALETTE_13 0xd000     /* the text colours: palettes 13-15 are loaded from the font's */
#define BLANK_PAIR 0x007f007f /* two blank characters */

/* NitroSDK's OSThread, as far as the screen reads it. */
typedef struct OSThread {
    u8 context[0x68];
    struct OSThread *next; /* 0x68: in the list of all threads */
    u32 id;                /* 0x6c */
    u8 unk_70[0x20];
    u32 stack_top;     /* 0x90 */
    u32 stack_bottom;  /* 0x94 */
    u32 stack_warning; /* 0x98: the offset the stack check looks at */
} OSThread;

typedef struct OSThreadInfo {
    u16 need_reschedule;
    u16 irq_depth;
    OSThread *current;
    OSThread *list;
} OSThreadInfo;

static_assert(offsetof(OSThread, stack_warning) == 0x98, "OSThread layout");

/* What data_021fcff4 points at, as far as the screen reads it. */
typedef struct ProfileStep {
    u8 unk_00[0xc];
    u16 profile;
} ProfileStep;

typedef struct ProfileOwner {
    u8 unk_00[8];
    ProfileStep *step;
} ProfileOwner;

struct Heap;

extern u64 OS_GetTick(void);
extern int OS_GetProcMode(void);
extern int OS_GetIrqStackStatus(void);
extern int OS_GetStackStatus(const OSThread *thread);
extern void *OS_GetDTCMAddress(void);
extern u32 OS_DisableInterrupts(void);
extern int OS_VSNPrintf(char *dest, u32 size, const char *format, const void *args);
extern void MIi_CpuClearFast(u32 data, void *dest, u32 size);
extern void GX_SetBankForBG(u32 banks);
extern void GX_SetBankForSubBG(u32 banks);
extern void GX_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void GXS_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void *G2_GetBG1ScrPtr(void);
extern void *G2S_GetBG1ScrPtr(void);
extern void GX_DispOn(void);
extern void func_02112d48(const void *src, u32 offset, u32 size); /* main background 1's characters */
extern void func_02112ce0(const void *src, u32 offset, u32 size); /* sub background 1's characters */

extern u8 data_0213fdc4;                /* DebugScreenState */
extern u32 data_0213fdc8;               /* the buttons held on the last frame */
extern u32 data_0213fdcc;               /* PC+4 shown without an exception context */
extern short *data_0213fdd0;            /* the main screen's background 1 map */
extern u32 data_0213fdd4;               /* milliseconds since start-up, when the screen took over */
extern u32 data_0213fdd8;               /* SP shown without an exception context */
extern short *data_0213fddc;            /* the sub screen's background 1 map */
extern ExceptionContext *data_0213fde0; /* the exception's context, or NULL */
extern const char *data_0213fde4;       /* the fatal error's message */
extern int data_0213fde8;               /* its line */
extern const char *data_0213fdec;       /* its file, or NULL when there was none */
extern int data_0213e7fc;               /* which of the game's loops runs (1-5) */
extern ProfileOwner *data_021fcff4;
extern u16 data_021fcfdc;    /* the profile when data_021fcff4 is NULL */
extern u8 data_021fcfd4;     /* the profile's step */
extern char data_021c5914[]; /* a 32-byte label read from a file at start-up */
extern OSThreadInfo OSi_ThreadInfo;
extern int OSi_MainExArenaEnabled;
extern struct Heap *sSubOBJExtPltt; /* at 0x021fbe80: a heap pointer (the symbol's name is not its use) */
extern struct Heap *data_021fbe8c;
extern struct Heap *data_021fbe94;
extern const u8 data_020df71c[];   /* the font: 0x1000 bytes of characters */
extern const u8 data_020e171c[];   /* its palettes */
extern const char data_020c7538[]; /* the registers' names, three characters each */
extern char FX_SinCosTable_[];     /* at 0x0213959c: where the fatal error's message is written */
extern const char data_020d3420[]; /* "%10ums" */
extern const char data_020d3428[]; /* "LoopProc %1u:%s" */
extern const char data_020d3438[]; /* "ProfName[%d]Step[%u]" */
extern const char data_020d3450[]; /* "%.3s:%08X" */
extern const char data_020d345c[]; /* "SPSR%08X" */
extern const char data_020d3468[]; /* "CP15%08X" */
extern const char data_020d3474[]; /* "SP  %08X" */
extern const char data_020d3480[]; /* "PC4 %08X" */
extern const char data_020d348c[]; /* "%s:%u" */
extern const char data_020d3494[]; /* "ID:%u mode:%02x" */
extern const char data_020d34a4[]; /* "S:%08x-%08x" */
extern const char data_020d34b0[]; /* "IrqStkErr%u" */
extern const char data_020d34bc[]; /* "StkErr%u:%u:%x" */
extern const char data_020d34cc[]; /* "SP = %08X" */
extern const char data_020d34d8[]; /* "%08x" */
extern const char data_020d34e0[]; /* "" */

static short *at(short *screen, int row, int column)
{
    return screen + row * ROW + column;
}

/* func_020012ec: take over after an exception: disable interrupts, note the time and run the
 * screen's frames for ever.
 * HW: the master interrupt enable is read (the value is dropped) and then cleared. */
void DebugScreen_Run(void)
{
    u16 previous = REG_IME;
    (void) previous;
    REG_IME = 0;
    /* OS_TicksToMilliSeconds: the tick runs at 33.514 MHz / 64 */
    data_0213fdd4 = (u32) ((OS_GetTick() << 6) / 33514);
    for (;;) {
        DebugScreen_Frame();
    }
}
CLEAN_AS(func_020012ec, DebugScreen_Run)

/* func_02001324: one frame: follow the key sequence, or once it is entered draw both screens
 * and serve Select+A (report the heap of Left, Right or Up, in the CPU's system mode only)
 * and Select+B (nothing); then wait for the next VBlank. */
void DebugScreen_Frame(void)
{
    u8 state = data_0213fdc4;
    u32 held = (u16) (((REG_KEYINPUT | EXTRA_BUTTONS) ^ PAD_ALL) & PAD_ALL) & PAD_KEYINPUT;
    u32 pressed = held & (data_0213fdc8 ^ held);

    data_0213fdc8 = held;
    switch (state) {
        case WAIT_FIRST_CHORD:
            /* QUIRK: the debug button would skip the sequence, but `held` keeps only the
             * buttons of KEYINPUT, so it never does. */
            if (pressed & PAD_DEBUG) {
                state = SHOW_FIRST;
            }
            if (held == (PAD_L | PAD_R | PAD_LEFT | PAD_A)) {
                state++;
            }
            break;
        case WAIT_FIRST_RELEASE:
        case WAIT_SECOND_RELEASE:
            if (held == 0) {
                state++;
            }
            break;
        case WAIT_SECOND_CHORD:
            if ((held & ~(PAD_DOWN | PAD_B)) != 0) {
                state = WAIT_FIRST_CHORD;
            } else if (held == (PAD_DOWN | PAD_B)) {
                state++;
            }
            break;
        case WAIT_THIRD_CHORD:
            if ((held & ~(PAD_SELECT | PAD_START)) != 0) {
                state = WAIT_FIRST_CHORD;
            } else if (held == (PAD_SELECT | PAD_START)) {
                state++;
            }
            break;
        case SHOW_FIRST:
            DebugScreen_InitDisplay();
            DebugScreen_DrawStatus();
            state++;
            /* fall through */
        case SHOWING:
            DebugScreen_DrawStatus();
            DebugScreen_DrawStack();
            if (held & PAD_SELECT) {
                if ((pressed & PAD_A) && OS_GetProcMode() == OS_PROCMODE_SYS) {
                    if (held & PAD_LEFT) {
                        Heap_Report(data_021fbe8c);
                    } else if (held & PAD_RIGHT) {
                        Heap_Report(sSubOBJExtPltt);
                    } else if (held & PAD_UP) {
                        Heap_Report(data_021fbe94);
                    }
                }
                if (pressed & PAD_B) {
                    DebugScreen_Nothing();
                }
            }
            break;
    }

    DebugScreen_WaitVBlank();
    data_0213fdc4 = state;
}
CLEAN_AS(func_02001324, DebugScreen_Frame)

/* func_0200149c: wait for the start of the next VBlank (line 192).
 * HW: busy-waits on VCOUNT, first for the end of a VBlank under way. */
void DebugScreen_WaitVBlank(void)
{
    while (REG_VCOUNT >= 192) {
    }
    while (REG_VCOUNT < 192) {
    }
}
CLEAN_AS(func_0200149c, DebugScreen_WaitVBlank)

/* func_020014b4: set both screens up for text: background 1 alone, its map at 0x2000 over
 * the font, palettes 13-15 from the font's, a blue backdrop, and both maps blank.
 * HW: the register writes in this order. */
void DebugScreen_InitDisplay(void)
{
    DisplayFrame_Reset2D();
    REG_POWCNT1 |= 1;
    REG_BLDCNT = 0;
    REG_DB_BLDCNT = 0;
    GX_SetBankForBG(0x40);                          /* VRAM bank G */
    GX_SetBankForSubBG(0x80);                       /* VRAM bank H */
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00u) | 0x200; /* background 1 only */
    REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x1f00u) | 0x200;
    REG_BG1CNT = (u16) ((REG_BG1CNT & 0x43) | 0x400); /* keep priority and mosaic; map base 1 */
    REG_DB_BG1CNT = (u16) ((REG_DB_BG1CNT & 0x43) | 0x400);
    func_02112d48(data_020df71c, 0, 0x1000);
    func_02112ce0(data_020df71c, 0, 0x1000);
    GX_LoadBGPltt(data_020e171c, 13 * 0x20, 3 * 0x20);
    GXS_LoadBGPltt(data_020e171c, 13 * 0x20, 3 * 0x20);
    BG_PALETTE[0] = 0x7c00;
    BG_PALETTE[12] = 0x7c00;
    DB_BG_PALETTE[0] = 0x7c00;
    DB_BG_PALETTE[12] = 0x7c00;
    data_0213fdd0 = G2_GetBG1ScrPtr();
    data_0213fddc = G2S_GetBG1ScrPtr();
    DebugScreen_ClearScreens();
    GX_DispOn();
    REG_DB_DISPCNT |= 0x10000; /* sub screen: display the graphics */
}
CLEAN_AS(func_020014b4, DebugScreen_InitDisplay)

/* func_020015c8: blank both maps. */
void DebugScreen_ClearScreens(void)
{
    short *sub = data_0213fddc;
    DebugScreen_FillWords(BLANK_PAIR, data_0213fdd0, 0x800);
    DebugScreen_FillWords(BLANK_PAIR, sub, 0x800);
}
CLEAN_AS(func_020015c8, DebugScreen_ClearScreens)

/* func_020015fc: MI_CpuClearFast. */
void DebugScreen_FillWords(u32 data, void *dest, u32 size)
{
    MIi_CpuClearFast(data, dest, size);
}
CLEAN_AS(func_020015fc, DebugScreen_FillWords)

/* func_02001610: the main screen. Row 0 the label, row 1 the uptime, rows 2-4 the current
 * thread, its stack and the first stack overflow, rows 6-7 the running loop and profile;
 * from column 20 the exception's registers (or the saved SP and PC); rows 18-19 the fatal
 * error. */
void DebugScreen_DrawStatus(void)
{
    u16 style[2] = {PALETTE_13, PALETTE_13};
    short *screen = data_0213fdd0;
    int loop;
    u16 profile;
    ExceptionContext *context;
    OSThread *thread;
    int mode;
    int status;
    unsigned int i;

    DebugText_Printf(style, at(screen, 1, 0), data_020d3420, data_0213fdd4);
    DebugText_Print(style, at(screen, 0, 0), data_021c5914);

    loop = data_0213e7fc;
    if (loop != 0 && loop < 6) {
        DebugText_Printf(style, at(screen, 6, 0), data_020d3428, loop, Process_PhaseName(loop));
    }

    profile = 0xffff;
    if (data_021fcff4 != NULL) {
        if (data_021fcff4->step != NULL) {
            profile = data_021fcff4->step->profile;
        }
    } else {
        profile = data_021fcfdc;
    }
    if (profile != 0xffff) {
        DebugText_Printf(style, at(screen, 7, 0), data_020d3438, profile, data_021fcfd4);
    }

    context = data_0213fde0;
    if (context != NULL) {
        for (i = 0; i < 18; i++) {
            DebugText_Printf(style, at(screen, i + 2, 20), data_020d3450, &data_020c7538[i * 3], context->regs[i]);
        }
        DebugText_Printf(style, at(screen, 20, 20), data_020d345c, context->spsr);
        DebugText_Printf(style, at(screen, 21, 20), data_020d3468, context->cp15);
    } else {
        DebugText_Printf(style, at(screen, 16, 20), data_020d3474, data_0213fdd8);
        DebugText_Printf(style, at(screen, 18, 20), data_020d3480, data_0213fdcc);
    }

    if (data_0213fdec != NULL) {
        DebugText_Printf(style, at(screen, 18, 0), data_020d348c, data_0213fdec, data_0213fde8);
        DebugText_Print(style, at(screen, 19, 0), data_0213fde4);
    }

    mode = OS_GetProcMode();
    thread = OSi_ThreadInfo.current;
    DebugText_Printf(style, at(screen, 2, 0), data_020d3494, thread->id, mode);
    DebugText_Printf(style, at(screen, 3, 0), data_020d34a4, thread->stack_top, thread->stack_bottom);

    status = OS_GetIrqStackStatus();
    if (status != 0) {
        DebugText_Printf(style, at(screen, 4, 0), data_020d34b0, status);
    } else {
        for (thread = OSi_ThreadInfo.list; thread != NULL; thread = thread->next) {
            status = OS_GetStackStatus(thread);
            if (status != 0) {
                break;
            }
        }
        if (thread != NULL) {
            DebugText_Printf(style, at(screen, 4, 0), data_020d34bc, status, thread->id, thread->stack_warning);
        }
    }
}
CLEAN_AS(func_02001610, DebugScreen_DrawStatus)

/* func_0200184c: the sub screen: the stack pointer (the exception's, else the saved one) and,
 * when it points into memory, 88 words of the stack from row 2. */
void DebugScreen_DrawStack(void)
{
    u16 style[2] = {PALETTE_13, PALETTE_13};
    short *screen = data_0213fddc;
    u32 sp = data_0213fde0 != NULL ? data_0213fde0->regs[14] : data_0213fdd8;

    DebugText_Printf(style, at(screen, 1, 0), data_020d34cc, sp);
    if (DebugScreen_IsReadable((void *) (uintptr_t) sp, 4)) {
        DebugScreen_DumpWords(at(screen, 2, 0), (void *) (uintptr_t) sp, 0x160);
    }
}
CLEAN_AS(func_0200184c, DebugScreen_DrawStack)

/* func_020018b4: print the words from `src` (rounded down to a word) up to `src + size`,
 * eight characters each, four to a row, in palettes 13 and 14 by turns; stop at the first
 * word outside memory. */
void DebugScreen_DumpWords(void *dest, void *src, u32 size)
{
    u16 style[2] = {PALETTE_13, PALETTE_13};
    u16 attribute = PALETTE_13;
    short *text = dest;
    u32 end = (u32) (uintptr_t) src + (size & ~3u);
    u32 word;

    for (word = (u32) (uintptr_t) src & ~3u; word < end; word += 4) {
        if (!DebugScreen_IsReadable((void *) (uintptr_t) word, 4)) {
            break;
        }
        style[1] = attribute;
        DebugText_Printf(style, text, data_020d34d8, *(const u32 *) (uintptr_t) word);
        text += 8;
        attribute ^= 0x3000; /* palette 13 <-> 14 */
    }
}
CLEAN_AS(func_020018b4, DebugScreen_DumpWords)

/* func_02001910: whether the `size` bytes at `start` are in main RAM (up to its last 4 KB, or
 * to 0x027e0000 with the 8 MB arena) or in the data TCM. */
int DebugScreen_IsReadable(void *start, u32 size)
{
    u32 first = (u32) (uintptr_t) start;
    u32 end = first + size;
    u32 dtcm = (u32) (uintptr_t) OS_GetDTCMAddress();
    u32 main_end = OSi_MainExArenaEnabled ? 0x027e0000 : 0x023ff000;

    if (first >= 0x02000000 && end <= main_end) {
        return 1;
    }
    return first >= dtcm && end <= dtcm + 0x4000;
}
CLEAN_AS(func_02001910, DebugScreen_IsReadable)

/* func_02001964: stop the game with a message, without a file or line.
 * REQUIRES: a va_list that is the address of the arguments in memory (the ARM's, and the
 * 32-bit x86 one's), as Fatal_Report hands it to OS_VSNPrintf. */
void Fatal_Printf(const char *format, ...)
{
    va_list args;

    va_start(args, format);
    Fatal_Report(data_020d34e0, 0, format, (const void *) args);
    va_end(args);
}
CLEAN_AS(func_02001964, Fatal_Printf)

/* func_02001988: stop the game: note the file, line and message for the debug screen, format
 * the message (at most 0x80 bytes) and terminate.
 * QUIRK: the message is written at 0x0213959c, the address the symbol table names
 * FX_SinCosTable_. */
void Fatal_Report(const char *file, int line, const char *format, const void *args)
{
    OS_DisableInterrupts();
    data_0213fdec = file;
    data_0213fde8 = line;
    data_0213fde4 = FX_SinCosTable_;
    OS_VSNPrintf(FX_SinCosTable_, 0x80, format, args);
    GameHalt_Terminate();
}
CLEAN_AS(func_02001988, Fatal_Report)

/* func_0204f8b8: does nothing (the debug screen calls it on B). */
void DebugScreen_Nothing(void) {}
CLEAN_AS(func_0204f8b8, DebugScreen_Nothing)
