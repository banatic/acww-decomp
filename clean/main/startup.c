/* The program's start-up (startup.h). */
#include "startup.h"

#include "autoload_2/heap.h"
#include "autoload_2/system.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "itcm/interrupts.h"
#include "main/backup_card.h"
#include "main/card_pulled.h"
#include "main/game_halt.h"
#include "main/library_overlay.h"
#include "main/overlay_slots.h"
#include "main/scene_sound.h"
#include "main/user_settings.h"
#include "build_time.h"
#include "caution_window.h"
#include "clock.h"
#include "display_frame.h"
#include "line_handlers.h"
#include "main_loop.h"
#include "main_random.h"
#include "resident_process.h"
#include "touch_history.h"
#include "town_day.h"

/* The master interrupt enable. */
#define REG_IME (*(volatile u16 *) 0x04000208)
/* Four words past the DS's documented ARM9 registers that the game's start-up sets. */
#define REG_040004C0 (*(volatile u32 *) 0x040004c0)
#define REG_040004C4 (*(volatile u32 *) 0x040004c4)
#define REG_040004C8 (*(volatile u32 *) 0x040004c8)
#define REG_040004CC (*(volatile u32 *) 0x040004cc)

/* VRAM bank D, as GX_SetBankForLCDC and WVR_StartUpAsync (GX_VRAM_ARM7_128_D) name it, and
 * the LCDC address and size of 128 KiB of VRAM cleared before it is handed over. */
#define STARTUP_VRAM_D 8
#define STARTUP_LCDC_VRAM 0x06800000u
#define STARTUP_VRAM_BANK_SIZE 0x20000u

/* The overlays' memory is filled from overlay 0's address up to here with two Thumb
 * "b ." instructions per word: a jump into code that is not loaded stops where it lands. */
#define STARTUP_OVERLAY_AREA_END 0x022a3300u
#define STARTUP_TRAP_WORD 0xe7fee7feu

/* Protection region 2 over the 4 KiB at 0x023ff000 (base, size code 11, enabled), and the
 * main arena's new top there. */
#define STARTUP_REGION_2 0x023ff017u
#define STARTUP_ARENA_TOP 0x023ff000u
#define STARTUP_ARENA_MAIN 0

/* The size of the auxiliary heap. */
#define STARTUP_AUX_HEAP_SIZE 0x13fc8

/* Raised by Startup_OnWirelessStarted (an interrupt) once the wireless library is up. */
extern volatile u8 data_021f4b10;
/* The options NNS heaps are created with (autoload_2/heap.c); 1 from here on. */
extern u16 data_0213e5a4;
/* The two thread queues of itcm/interrupts.c (OSThreadQueue: head and tail), and a byte set
 * once they are ready. */
extern u32 data_021cfb90[2];
extern u32 data_021cfb98[2];
extern u8 data_021cfb68;
/* The slot of the library overlays, and the overlays loaded into it here. */
extern LibraryOverlaySlot data_021d11c4;
extern char SDK_OVERLAY_ov069_ID;
extern char SDK_OVERLAY_ov068_ID;
extern char SDK_OVERLAY_ov000_ID;
/* The process profiles by class id (autoload_2/process.c), and the game's table of them. */
extern const void *data_021fd044;
extern const u8 data_020e3134[];

/* NitroSDK. */
extern void OS_InitTick(void);
extern void GX_SetBankForLCDC(int banks);
extern void MIi_CpuClearFast(u32 data, void *dest, u32 size);
extern u32 OS_EnableInterrupts(void);
extern u32 OS_RestoreInterrupts(u32 enabled);
extern int WVR_StartUpAsync(int vram, void (*callback)(void *argument, int result), void *argument);
extern void FS_Init(int dma);
extern void DC_FlushRange(const void *start, u32 size);
extern void OS_SetProtectionRegion2(u32 region);
extern void OS_SetArenaHi(int arena, u32 top);
extern void OS_SetIrqFunction(int mask, void (*handler)(void));
extern int OS_EnableIrqMask(int mask);
extern int GX_VBlankIntr(int enable);
extern int GX_HBlankIntr(int enable);

/* The game's handlers handed to NitroSDK: the wireless start's callback and the HBlank and
 * VBlank interrupts (Irq_HBlank, Irq_VBlank). */
extern void func_020b1b68(void *argument, int result);
extern void func_01ffcc30(void);
extern void func_01ffcc60(void);

/* Start-up steps of their own, not named yet. */
extern void func_02110794(void);
extern void func_02110aa0(void);
extern void StartupNoOp_Run(void);

/* NitroStartUp: the start-up NitroSDK runs before main.
 * HW: with the master interrupt enable saved and set to 1 and the CPU's interrupts enabled,
 * it spins until the wireless library's callback (an interrupt) raises data_021f4b10, then
 * restores both in the reverse order; the enable register is read once more before it is
 * written back. The Reference runs it (runtime/native-reference.txt).
 * QUIRK: the 128 KiB cleared are at 0x06800000, bank A's LCDC address, though bank D (at
 * 0x06860000) is the one just mapped to the LCDC and handed to the ARM7. */
void Startup_Begin(void)
{
    UserSettings_StartUp();
    OS_InitTick();
    func_02110794();
    GX_SetBankForLCDC(STARTUP_VRAM_D);
    MIi_CpuClearFast(0, (void *) (uintptr_t) STARTUP_LCDC_VRAM, STARTUP_VRAM_BANK_SIZE);
    func_02110aa0();

    u16 saved_ime = REG_IME;
    REG_IME = 1;
    u32 enabled = OS_EnableInterrupts();

    data_021f4b10 = 0;
    WVR_StartUpAsync(STARTUP_VRAM_D, func_020b1b68, NULL);
    while (data_021f4b10 == 0) {
    }

    OS_RestoreInterrupts(enabled);
    (void) REG_IME;
    REG_IME = saved_ime;

    Startup_SetArenaTop();
    CardPulled_Install();
    FS_Init(2);
    Startup_TrapOverlayArea();
    OverlaySlots_Clear();

    data_0213e5a4 = 1;
    Heap_InitRoot();
}
CLEAN_AS(NitroStartUp, Startup_Begin)

/* func_020b1b0c: fills the memory from overlay 0's address up to STARTUP_OVERLAY_AREA_END
 * with traps, and flushes it from the data cache. */
void Startup_TrapOverlayArea(void)
{
    OverlaySlotsInfo info;
    OverlaySlots_ReadInfo(&info, (int) (uintptr_t) &SDK_OVERLAY_ov000_ID);
    u32 start = info.ram_address;
    u32 size = STARTUP_OVERLAY_AREA_END - start;
    MIi_CpuClearFast(STARTUP_TRAP_WORD, (void *) (uintptr_t) start, size);
    DC_FlushRange((const void *) (uintptr_t) start, size);
}
CLEAN_AS(func_020b1b0c, Startup_TrapOverlayArea)

/* func_020b1b48: protection region 2 over the top 4 KiB of main memory, and the main arena
 * ending below it. */
void Startup_SetArenaTop(void)
{
    OS_SetProtectionRegion2(STARTUP_REGION_2);
    OS_SetArenaHi(STARTUP_ARENA_MAIN, STARTUP_ARENA_TOP);
}
CLEAN_AS(func_020b1b48, Startup_SetArenaTop)

/* func_020b1b68: the wireless library's start callback: the program stops when it failed,
 * else Startup_Begin may go on. */
void Startup_OnWirelessStarted(void *argument, int result)
{
    (void) argument;
    if (result != 0) {
        GameHalt_Terminate();
    }
    data_021f4b10 = 1;
}
CLEAN_AS(func_020b1b68, Startup_OnWirelessStarted)

/* func_020b1b84: the game's start-up.
 * HW: the master interrupt enable is read (the value is dropped) and set to 1 between enabling
 * the HBlank and VBlank interrupts and enabling the CPU's; the four words at 0x040004c8,
 * 0x040004cc, 0x040004c0 and 0x040004c4 are written in that order. The Reference runs it
 * (runtime/native-reference.txt). */
void Startup_InitGame(void)
{
    Startup_FirstStep();
    Irq_InitNothing();
    Math_InitSqrt();
    LineHandlers_Init();
    Startup_InitFrameWait();

    OS_SetIrqFunction(STARTUP_IRQ_HBLANK, func_01ffcc30);
    OS_EnableIrqMask(STARTUP_IRQ_VBLANK | STARTUP_IRQ_HBLANK);
    (void) REG_IME;
    REG_IME = 1;
    OS_EnableInterrupts();
    GX_VBlankIntr(1);
    GX_HBlankIntr(1);

    BackupCard_InitGame();
    BuildTime_Load();
    LibraryOverlay_Load(&data_021d11c4, (int) (uintptr_t) &SDK_OVERLAY_ov069_ID);
    LibraryOverlay_End(&data_021d11c4);
    TouchHistory_Init();
    System_InitTick();
    Heap_CreateAuxHeap(STARTUP_AUX_HEAP_SIZE, NULL);
    DisplayFrame_Init();
    SoundLayer_Init();
    System_ResetFrameCount();
    Clock_Init();
    TownDay_Init();
    CautionWindow_LoadMessages();
    data_021fd044 = data_020e3134;
    StartupNoOp_Run();
    MainRandom_SeedFromClock();

    REG_040004C8 = 0x296a5800;
    REG_040004CC = 0x7fff;
    REG_040004C0 = 0x7fff;
    REG_040004C4 = 0;

    MainLoop_StartupNothing();
    ResidentProcess_SpawnAll();
    LibraryOverlay_Load(&data_021d11c4, (int) (uintptr_t) &SDK_OVERLAY_ov068_ID);
}
CLEAN_AS(func_020b1b84, Startup_InitGame)

/* func_020b1c74: the first step of Startup_InitGame; does nothing. */
void Startup_FirstStep(void) {}
CLEAN_AS(func_020b1c74, Startup_FirstStep)

/* func_020b1c78: empties the two thread queues the interrupt handlers wake, installs the
 * VBlank handler and sets data_021cfb68. */
void Startup_InitFrameWait(void)
{
    data_021cfb90[1] = 0;
    data_021cfb90[0] = 0;
    data_021cfb98[1] = 0;
    data_021cfb98[0] = 0;
    OS_SetIrqFunction(STARTUP_IRQ_VBLANK, func_01ffcc60);
    data_021cfb68 = 1;
}
CLEAN_AS(func_020b1c78, Startup_InitFrameWait)
