/* The Wi-Fi Connection library's start and the run of overlay 1 (wfc_setup.h). */
#include "wfc_setup.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/library_overlay.h"
#include "main/overlay_slots.h"

#define REG16(address) (*(volatile u16 *) (uintptr_t) (address))
#define REG_IME 0x04000208u
#define IRQ_VBLANK_HBLANK_VCOUNT 0x7

#define INIT_WORK_SIZE 0x700
#define OVERLAY1_WORK_SIZE 0x40000
#define WORK_ALIGN 0x20
/* The two values overlay 1's entry is given after the work area. */
#define OVERLAY1_ARGUMENT_1 6
#define OVERLAY1_ARGUMENT_2 0

extern LibraryOverlaySlot data_021d11c4;
extern u8 data_020df29c; /* the start's result, WFC_SETUP_NO_RESULT once taken */
extern char SDK_OVERLAY_ov065_ID;
extern char SDK_OVERLAY_ov001_ID;

extern u32 OS_DisableInterrupts(void);
extern u32 OS_RestoreInterrupts(u32 enabled);
extern u32 OS_DisableIrqMask(u32 mask);
extern u32 OS_ResetRequestIrqMask(u32 mask);

/* The library's start (in autoload 2) and its setter of the memory functions (overlay 65). */
extern int func_0210172c(void *work);
extern void func_ov065_0227f1f4(void *(*alloc)(int name, unsigned int size, int align),
                                void (*free_block)(int name, void *block, unsigned int size));
/* Overlay 1's entry. */
extern void func_ov001_022141f4(void *work, int a, int b);

/* The memory functions as the game hands them to the library. */
extern void *func_0206e4fc(int name, unsigned int size, int align);
extern void func_0206e4f0(int name, void *block, unsigned int size);

/* The number of an overlay, which the linker gives as the address of its symbol. */
static int overlay_id(const char *symbol)
{
    return (int) (uintptr_t) symbol;
}

/* func_0206e464: with interrupts off and the VBlank, HBlank and VCount interrupts masked and
 * cleared, overlay 65 loaded and its memory functions set, overlay 1 loaded and run with a work
 * area of 256 KiB from the current heap, then both released. HW: IME is cleared around the run
 * and restored after a read of it. QUIRK: the three interrupts stay masked. */
void WfcSetup_RunOverlay1(void)
{
    u32 enabled = OS_DisableInterrupts();
    u16 saved_ime = REG16(REG_IME);
    REG16(REG_IME) = 0;
    OS_DisableIrqMask(IRQ_VBLANK_HBLANK_VCOUNT);
    OS_ResetRequestIrqMask(IRQ_VBLANK_HBLANK_VCOUNT);
    LibraryOverlay_Load(&data_021d11c4, overlay_id(&SDK_OVERLAY_ov065_ID));
    func_ov065_0227f1f4(func_0206e4fc, func_0206e4f0);
    OverlaySlots_Load((u8) overlay_id(&SDK_OVERLAY_ov001_ID));
    void *work = Heap_AllocCurrentAligned(OVERLAY1_WORK_SIZE, WORK_ALIGN);
    func_ov001_022141f4(work, OVERLAY1_ARGUMENT_1, OVERLAY1_ARGUMENT_2);
    Heap_FreeCurrent(work);
    OverlaySlots_Release((u8) overlay_id(&SDK_OVERLAY_ov001_ID));
    LibraryOverlay_End(&data_021d11c4);
    (void) REG16(REG_IME);
    REG16(REG_IME) = saved_ime;
    OS_RestoreInterrupts(enabled);
}
CLEAN_AS(func_0206e464, WfcSetup_RunOverlay1)

/* func_0206e4f0: the library's free: the block back to the current heap. */
void WfcSetup_Free(int name, void *block, unsigned int size)
{
    (void) name;
    (void) size;
    Heap_FreeCurrent(block);
}
CLEAN_AS(func_0206e4f0, WfcSetup_Free)

/* func_0206e4fc: the library's allocation: `size` bytes of the current heap, aligned. */
void *WfcSetup_Alloc(int name, unsigned int size, int align)
{
    (void) name;
    return Heap_AllocCurrentAligned((int) size, align);
}
CLEAN_AS(func_0206e4fc, WfcSetup_Alloc)

/* func_0206e508: the start's result, taken: WFC_SETUP_NO_RESULT is left in its place. */
unsigned char WfcSetup_TakeInitResult(void)
{
    u8 result = data_020df29c;
    data_020df29c = WFC_SETUP_NO_RESULT;
    return result;
}
CLEAN_AS(func_0206e508, WfcSetup_TakeInitResult)

/* func_0206e518: the library started with a work area from the current heap while overlay 65
 * is loaded; its result kept (in its low byte) and returned. */
int WfcSetup_InitLibrary(void)
{
    void *work = Heap_AllocCurrentAligned(INIT_WORK_SIZE, WORK_ALIGN);
    LibraryOverlay_Load(&data_021d11c4, overlay_id(&SDK_OVERLAY_ov065_ID));
    int result = func_0210172c(work);
    data_020df29c = (u8) result;
    LibraryOverlay_End(&data_021d11c4);
    Heap_FreeCurrent(work);
    return result;
}
CLEAN_AS(func_0206e518, WfcSetup_InitLibrary)
