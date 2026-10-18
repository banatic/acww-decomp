/* The display's part of the main loop (display_frame.h). */
#include "display_frame.h"

#include "autoload_2/system.h"
#include "clean.h"
#include "main/display_3d.h"
#include "main/display_shadow.h"
#include "oam_buffer.h"
#include "screen_transition.h"
#include "transfer_queue.h"

#define REG16(addr) (*(volatile u16 *) (uintptr_t) (addr))
#define REG32(addr) (*(volatile u32 *) (uintptr_t) (addr))

#define REG_DISPCNT 0x04000000u
#define REG_BG_CONTROLS 0x04000008u /* BG0CNT to MOSAIC: 0x48 bytes */
#define REG_BG2PA 0x04000020u
#define REG_BG2PD 0x04000026u
#define REG_BG3PA 0x04000030u
#define REG_BG3PD 0x04000036u
#define REG_DISP3DCNT 0x04000060u /* with DISPCAPCNT: 8 bytes */
#define REG_MASTER_BRIGHT 0x0400006cu
#define REG_POWCNT1 0x04000304u
#define SUB_ENGINE 0x1000u /* the sub engine's registers are 0x1000 above the main one's */

#define BG_CONTROLS_SIZE 0x48
#define DISP3D_SIZE 8
#define AFFINE_ONE 0x100 /* 1.0 in the affine parameters' 8.8 fixed point */

/* The DISPCNT bits DisplayFrame_Reset2D keeps: the main engine's BG mode and 3D bit, display
 * mode and VRAM block; the sub engine's display mode bit. */
#define DISPCNT_MAIN_KEEP 0x000f000fu
#define DISPCNT_SUB_KEEP 0x00010000u

/* POWCNT1 */
#define POWCNT_2D_A 0x0002u
#define POWCNT_3D_RENDER 0x0004u
#define POWCNT_3D_GEOMETRY 0x0008u
#define POWCNT_2D_B 0x0200u
#define POWCNT_SWAP 0x8000u /* the main engine on the top screen */
#define POWCNT_ENGINES (POWCNT_2D_A | POWCNT_3D_RENDER | POWCNT_3D_GEOMETRY | POWCNT_2D_B)

#define VRAM_LCDC_ALL_BUT_D 0x1f7 /* banks A-C and E-I (D is the ARM7's) */
#define LCDC_VRAM 0x06800000u
#define LCDC_CLEAR_SIZE 0x84000
#define OAM 0x07000000u
#define OAM_SIZE 0x400
#define OAM_HIDDEN 0xc0 /* each OBJ's attribute 0 at y 192, below the screen; attribute 1 0 */
#define PALETTES 0x05000000u
#define PALETTES_SIZE 0x400

extern u32 GXi_DmaId;
extern void MI_DmaFill32(u32 dma, void *dest, u32 data, u32 size);
extern void MIi_CpuClearFast(u32 data, void *dest, u32 size);
extern void GX_SetBankForLCDC(int banks);

/* NitroSDK's VRAM bank releases, in the order DisplayFrame_ReleaseVram runs them. The names
 * some of them carry are not theirs; they are kept as the symbols are. */
extern void func_02110aa0(void);
extern void func_02110b60(void);
extern void func_02110b4c(void);
extern void func_02110ab4(void);
extern void func_02110af0(void);
extern void func_02110adc(void);
extern void func_02110ac8(void);
extern u32 GX_ResetBankForBGExtPltt(void);
extern u32 GX_ResetBankForOBJExtPltt(void);
extern void func_02110a8c(void);
extern void func_02110a78(void);
extern u32 GX_ResetBankForSubBGExtPltt(void);
extern u32 GX_ResetBankForSubOBJExtPltt__autoload_2_02110a28(void);

extern int data_021c8c9c;                /* POWCNT1's swap bit: 1 for the main engine on top */
extern DisplayFrameHooks *data_021c8ca0; /* the running scene's hooks, or NULL */

/* func_02053f20: both engines on, the main engine on the top screen, every VRAM bank
 * released, and the 2D registers of both engines cleared: the backgrounds' controls,
 * scrolling, affine parameters, windows and mosaic, the 3D and capture controls and the
 * brightness, with the affine backgrounds' matrices set to the identity.
 * HW: in this order. */
void DisplayFrame_Reset2D(void)
{
    REG16(REG_POWCNT1) |= POWCNT_SWAP | POWCNT_ENGINES;
    DisplayFrame_ReleaseVram();
    REG32(REG_DISPCNT) &= DISPCNT_MAIN_KEEP;
    MI_DmaFill32(GXi_DmaId, (void *) (uintptr_t) REG_BG_CONTROLS, 0, BG_CONTROLS_SIZE);
    MI_DmaFill32(GXi_DmaId, (void *) (uintptr_t) REG_DISP3DCNT, 0, DISP3D_SIZE);
    REG16(REG_MASTER_BRIGHT) = 0;
    REG32(SUB_ENGINE + REG_DISPCNT) &= DISPCNT_SUB_KEEP;
    MI_DmaFill32(GXi_DmaId, (void *) (uintptr_t) (SUB_ENGINE + REG_BG_CONTROLS), 0, BG_CONTROLS_SIZE);
    REG16(SUB_ENGINE + REG_MASTER_BRIGHT) = 0;
    REG16(REG_BG2PA) = AFFINE_ONE;
    REG16(REG_BG2PD) = AFFINE_ONE;
    REG16(REG_BG3PA) = AFFINE_ONE;
    REG16(REG_BG3PD) = AFFINE_ONE;
    REG16(SUB_ENGINE + REG_BG2PA) = AFFINE_ONE;
    REG16(SUB_ENGINE + REG_BG2PD) = AFFINE_ONE;
    REG16(SUB_ENGINE + REG_BG3PA) = AFFINE_ONE;
    REG16(SUB_ENGINE + REG_BG3PD) = AFFINE_ONE;
}
CLEAN_AS(func_02053f20, DisplayFrame_Reset2D)

/* func_02053fdc: release every VRAM bank from what it is mapped to. */
void DisplayFrame_ReleaseVram(void)
{
    func_02110aa0();
    func_02110b60();
    func_02110b4c();
    func_02110ab4();
    func_02110af0();
    func_02110adc();
    func_02110ac8();
    GX_ResetBankForBGExtPltt();
    GX_ResetBankForOBJExtPltt();
    func_02110a8c();
    func_02110a78();
    GX_ResetBankForSubBGExtPltt();
    GX_ResetBankForSubOBJExtPltt__autoload_2_02110a28();
}
CLEAN_AS(func_02053fdc, DisplayFrame_ReleaseVram)

/* func_0205401c: the display's work right after the VBlank: which engine is on top, the OBJ
 * attributes into the OAM, the screen transition, the 3D clear colour, the 2D registers, the
 * scene's hook, then the 2D registers marked as changed.
 * QUIRK: the swap flag is shifted into bit 15 and cut to 16 bits, so only its bit 0 counts.
 * HW: POWCNT1 is read once and written once, before the rest. */
void DisplayFrame_AfterVBlank(void)
{
    u32 swap = (u32) data_021c8c9c;
    REG16(REG_POWCNT1) = (u16) ((REG16(REG_POWCNT1) & ~POWCNT_SWAP) | swap << 15);

    OamBuffer_Flush();
    OamBuffer_Load();
    ScreenTransition_AfterVBlank();
    Display3D_ApplyClearColor();
    DisplayShadow_WriteModes();
    if (data_021c8ca0 != NULL) {
        data_021c8ca0->vtable->after_vblank(data_021c8ca0);
    }
    DisplayShadow_Flush();
}
CLEAN_AS(func_0205401c, DisplayFrame_AfterVBlank)

/* func_02054070: the display's work after the frame's drawing: the scene's hook, then the
 * screen transition. */
void DisplayFrame_EndDraw(void)
{
    DisplayFrameHooks *hooks = data_021c8ca0;
    if (hooks != NULL) {
        hooks->vtable->end_draw(hooks);
    }
    ScreenTransition_AfterDraw();
}
CLEAN_AS(func_02054070, DisplayFrame_EndDraw)

/* func_02054090: the end_draw hook of data_020e550c, which does nothing. */
void DisplayFrame_NoEndDraw(void) {}
CLEAN_AS(func_02054090, DisplayFrame_NoEndDraw)

/* func_02054094: the display's work before the frame's: the OBJ attribute copies reset, the
 * scene's hook, the 3D engine reset, and an empty hook. */
void DisplayFrame_Begin(void)
{
    OamBuffer_Reset();
    if (data_021c8ca0 != NULL) {
        data_021c8ca0->vtable->begin(data_021c8ca0);
    }
    Display3D_Reset();
    Display_EmptyHook();
}
CLEAN_AS(func_02054094, DisplayFrame_Begin)

/* func_020540bc: the begin hook of data_020e550c, which does nothing. */
void DisplayFrame_NoBegin(void) {}
CLEAN_AS(func_020540bc, DisplayFrame_NoBegin)

/* func_020540c0: no scene hooks, the main engine on the bottom screen, the 2D register copies
 * reset and the 3D engine set up. */
void DisplayFrame_ResetState(void)
{
    data_021c8ca0 = NULL;
    data_021c8c9c = 0;
    DisplayShadow_Reset();
    Display3D_InitEngine();
}
CLEAN_AS(func_020540c0, DisplayFrame_ResetState)

/* func_020540e4: the display's set-up at start-up: its state, the screen transition, both 2D
 * engines and the 3D engine on, VRAM cleared through the LCDC, every OBJ hidden, the main
 * engine's palettes black, the 3D set-up and the backdrop colour.
 * QUIRK: the clear covers the LCDC addresses of banks A-D and the first 16 KiB of E's, though
 * D is not mapped there; F-I are mapped and not cleared.
 * HW: in this order. */
void DisplayFrame_Init(void)
{
    System_Nothing();
    DisplayFrame_ResetState();
    ScreenTransition_Reset();
    REG16(REG_POWCNT1) = (u16) ((REG16(REG_POWCNT1) & ~POWCNT_ENGINES) | POWCNT_ENGINES);
    GX_SetBankForLCDC(VRAM_LCDC_ALL_BUT_D);
    MIi_CpuClearFast(0, (void *) (uintptr_t) LCDC_VRAM, LCDC_CLEAR_SIZE);
    func_02110aa0();
    MIi_CpuClearFast(OAM_HIDDEN, (void *) (uintptr_t) OAM, OAM_SIZE);
    MIi_CpuClearFast(0, (void *) (uintptr_t) PALETTES, PALETTES_SIZE);
    Display3D_Init();
    Display_LoadBackdropColor();
    TransferQueue_ClearMain();
    TransferQueue_ClearVBlank();
}
CLEAN_AS(func_020540e4, DisplayFrame_Init)
