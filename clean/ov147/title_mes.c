/* The title's message (title_scene.h, TitleMes): one of two screens of "/a_mes/" on the main
 * screen's background 3, blended over the 3D and the backdrop. Asked for by TitleMes_Request
 * and taken away by TitleMes_Withdraw, it waits 5 frames, is loaded and shown, then pulses:
 * 10 frames in (the blend following a quarter of a sine), held for 6, 10 frames out, and again,
 * until it is taken away or another screen is asked for; it then goes once it has faded out. */
#include "title_scene.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/display_shadow.h"

static_assert(sizeof(TitleMes) == 0x20, "TitleMes");

#define REG16(addr) (*(volatile u16 *) (uintptr_t) (addr))
#define REG32(addr) (*(volatile u32 *) (uintptr_t) (addr))
#define REG_DISPCNT 0x04000000u
#define REG_BG3CNT 0x0400000eu
#define REG_BLDCNT 0x04000050u

/* The main screen's planes: background 3 (DISPCNT bits 8-12 hold them). */
#define TITLE_MES_PLANE_BG3 0x08
#define DISPCNT_PLANES 0x1f00u
/* The blend's planes: background 3 over background 0 (the 3D) and the backdrop. */
#define TITLE_MES_BLEND_TOP 0x08
#define TITLE_MES_BLEND_BOTTOM 0x21

#define TITLE_MES_LEVELS 10 /* steps of the blend in or out */
#define TITLE_MES_HOLD 5    /* the frames held at the top are those above this */
#define TITLE_MES_WAIT 5    /* frames before the message is shown */
#define TITLE_MES_CHARS_SIZE 0x9e0
#define TITLE_MES_PALETTE_SIZE 0x20
#define TITLE_MES_SCREEN_SIZE 0x800
#define TITLE_MES_PALETTE_OFFSET 0x20 /* background palette 1 */
#define TITLE_MES_SCREENS 2

/* The vtable. */
extern const u8 data_ov147_0229ac1c[];

/* The files: the characters, the palette, and the two screens ("a0" and "b0"). */
extern const char data_ov147_0229ac24[]; /* "/a_mes/a_mes_ttl_bg_ncg.bin" */
extern const char data_ov147_0229ac40[]; /* "/a_mes/a_mes_ttl_bg_ncl.bin" */
extern const char *const data_ov147_0229ac0c[TITLE_MES_SCREENS];

/* The table of the steps' member functions (the overlay's .bss, filled once from the constants
 * after it) and its guard. */
extern u32 data_ov147_022a2aac;
extern MemberPointer data_ov147_022a2ab0[TITLE_MES_STATES];
extern const MemberPointer data_ov147_0229ac04, data_ov147_0229abfc, data_ov147_0229abf4;

extern const s16 FX_SinCosTable_[];

extern void DC_FlushRange(const void *start, u32 size);
extern void GX_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void G2x_SetBlendAlpha_(u32 reg, int plane1, int plane2, int ev1, int ev2);
extern void FS_InitFile(void *file);
extern int FS_OpenFile(void *file, const char *path);
extern s32 FS_ReadFile(void *file, void *dst, s32 size);
extern int FS_CloseFile(void *file);
/* The main screen's background 3: its characters and its screen (display_layers.c). */
extern void func_02112ba8(const void *src, u32 offset, u32 size);
extern void func_02112ee8(const void *src, u32 offset, u32 size);

/* func_ov147_0229a250 (TITLE_MES_SHOWN): a step of the pulse and the blend set by it; once it
 * has faded out to be taken away or changed, the blend cleared, background 3 hidden and
 * nothing shown. */
void TitleMes_RunShown(TitleMes *self)
{
    int gone = TitleMes_Pulse(self);
    TitleMes_ApplyBlend(self);
    if (gone != 0) {
        TitleMes_ClearBlend(self);
        TitleMes_HideLayer();
        TitleMes_SetIdle(self);
    }
}
CLEAN_AS(func_ov147_0229a250, TitleMes_RunShown)

/* func_ov147_0229a280: shown (TITLE_MES_SHOWN) from the start of the pulse: background 3 set
 * up, the screen `shown` loaded, background 3 shown and the blend set. */
void TitleMes_Show(TitleMes *self)
{
    self->state = TITLE_MES_SHOWN;
    TitleMes_ResetBlend(self);
    TitleMes_SetUpLayer();
    TitleMes_Load(self->shown);
    TitleMes_ShowLayer();
    TitleMes_ApplyBlend(self);
}
CLEAN_AS(func_ov147_0229a280, TitleMes_Show)

/* func_ov147_0229a2a8 (TITLE_MES_WAITING): back to nothing when another screen is asked for;
 * else shown when the wait runs out. */
void TitleMes_RunWaiting(TitleMes *self)
{
    if (self->shown != self->wanted) {
        TitleMes_SetIdle(self);
        return;
    }
    self->delay--;
    if (self->delay <= 0) {
        TitleMes_Show(self);
    }
}
CLEAN_AS(func_ov147_0229a2a8, TitleMes_RunWaiting)

/* func_ov147_0229a2d0: the wait before the message is shown (TITLE_MES_WAITING). */
void TitleMes_StartWait(TitleMes *self)
{
    self->state = TITLE_MES_WAITING;
    self->delay = TITLE_MES_WAIT;
}
CLEAN_AS(func_ov147_0229a2d0, TitleMes_StartWait)

/* func_ov147_0229a2dc (TITLE_MES_IDLE): a screen asked for is waited for. */
void TitleMes_RunIdle(TitleMes *self)
{
    s32 wanted = self->wanted;
    if (wanted != TITLE_MES_NONE) {
        self->shown = wanted;
        TitleMes_StartWait(self);
    }
}
CLEAN_AS(func_ov147_0229a2dc, TitleMes_RunIdle)

/* func_ov147_0229a2f4: nothing shown (TITLE_MES_IDLE). */
void TitleMes_SetIdle(TitleMes *self)
{
    self->state = TITLE_MES_IDLE;
    self->shown = TITLE_MES_NONE;
}
CLEAN_AS(func_ov147_0229a2f4, TitleMes_SetIdle)

/* func_ov147_0229a300: no blend on the main screen (BLDCNT: no first plane, the backdrop
 * second, the coefficients 16 and 0). */
void TitleMes_ClearBlend(TitleMes *self)
{
    (void) self;
    G2x_SetBlendAlpha_(REG_BLDCNT, 0, 0x20, 0x10, 0);
}
CLEAN_AS(func_ov147_0229a300, TitleMes_ClearBlend)

/* func_ov147_0229a31c: background 3 blended over the 3D and the backdrop by the pulse's step:
 * a weight of 16 times the sine of the step's share of a quarter turn, rounded and kept to
 * 0-16, and the rest for the planes below.
 * QUIRK: the step times 0x1000 is a 32-bit signed value divided by 10 (truncating); the angle's
 * index keeps bits 2-13 of the quotient. */
void TitleMes_ApplyBlend(TitleMes *self)
{
    s32 quotient = (s32) ((u32) self->level << 12) / 10;
    u32 index = (((u32) quotient << 2) & 0xffffu) >> 4;
    s32 weight = ((s32) FX_SinCosTable_[index * 2] * 16 + 0x800) >> 12;
    if (weight < 0) {
        weight = 0;
    } else if (weight > 16) {
        weight = 16;
    }
    G2x_SetBlendAlpha_(REG_BLDCNT, TITLE_MES_BLEND_TOP, TITLE_MES_BLEND_BOTTOM, weight, 16 - weight);
}
CLEAN_AS(func_ov147_0229a31c, TitleMes_ApplyBlend)

/* func_ov147_0229a374: background 3 of the main screen hidden, in main's planes and at once in
 * DISPCNT.
 * HW: DISPCNT's planes are rewritten after the shadow is changed. */
void TitleMes_HideLayer(void)
{
    DisplayShadow_HideMainPlanes(TITLE_MES_PLANE_BG3);
    u32 planes = DisplayShadow_GetMainPlanes();
    REG32(REG_DISPCNT) = (REG32(REG_DISPCNT) & ~DISPCNT_PLANES) | planes << 8;
}
CLEAN_AS(func_ov147_0229a374, TitleMes_HideLayer)

/* func_ov147_0229a3a0: background 3 of the main screen shown (main's planes). */
void TitleMes_ShowLayer(void)
{
    DisplayShadow_ShowMainPlanes(TITLE_MES_PLANE_BG3);
}
CLEAN_AS(func_ov147_0229a3a0, TitleMes_ShowLayer)

/* func_ov147_0229a3ac: BG3CNT given priority 1, screen base 7 and character base 0 with the
 * mosaic off; its scroll at 0.
 * HW: three reads and writes of BG3CNT, in this order. */
void TitleMes_SetUpLayer(void)
{
    REG16(REG_BG3CNT) = (u16) ((REG16(REG_BG3CNT) & ~3u) | 1u);
    REG16(REG_BG3CNT) = (u16) ((REG16(REG_BG3CNT) & 0x43u) | 0x700u);
    REG16(REG_BG3CNT) = (u16) (REG16(REG_BG3CNT) & ~0x40u);
    DisplayShadow_SetMainBg3Scroll(0, 0);
}
CLEAN_AS(func_ov147_0229a3ac, TitleMes_SetUpLayer)

/* func_ov147_0229a3e4: a screen to the main screen's background 3. */
void TitleMes_UploadScreen(unsigned int data)
{
    const void *src = (const void *) (uintptr_t) data;
    DC_FlushRange(src, TITLE_MES_SCREEN_SIZE);
    func_02112ee8(src, 0, TITLE_MES_SCREEN_SIZE);
}
CLEAN_AS(func_ov147_0229a3e4, TitleMes_UploadScreen)

/* func_ov147_0229a404: a palette to the main screen's background palette 1. */
void TitleMes_UploadPalette(void *data)
{
    DC_FlushRange(data, TITLE_MES_PALETTE_SIZE);
    GX_LoadBGPltt(data, TITLE_MES_PALETTE_OFFSET, TITLE_MES_PALETTE_SIZE);
}
CLEAN_AS(func_ov147_0229a404, TitleMes_UploadPalette)

/* func_ov147_0229a420: the characters to the start of the main screen's background 3's. */
void TitleMes_UploadChars(void *data)
{
    DC_FlushRange(data, TITLE_MES_CHARS_SIZE);
    func_02112ba8(data, 0, TITLE_MES_CHARS_SIZE);
}
CLEAN_AS(func_ov147_0229a420, TitleMes_UploadChars)

/* func_ov147_0229a440: a screen's 0x800 bytes read from the file at `path`. */
void TitleMes_ReadScreen(void *file, const char *path, void *dst)
{
    FS_OpenFile(file, path);
    FS_ReadFile(file, dst, TITLE_MES_SCREEN_SIZE);
    FS_CloseFile(file);
}
CLEAN_AS(func_ov147_0229a440, TitleMes_ReadScreen)

/* func_ov147_0229a468: a palette's 0x20 bytes read from the file at `path`. */
void TitleMes_ReadPalette(void *file, const char *path, void *dst)
{
    FS_OpenFile(file, path);
    FS_ReadFile(file, dst, TITLE_MES_PALETTE_SIZE);
    FS_CloseFile(file);
}
CLEAN_AS(func_ov147_0229a468, TitleMes_ReadPalette)

/* func_ov147_0229a48c: the characters' 0x9e0 bytes read from the file at `path`. */
void TitleMes_ReadChars(void *file, const char *path, void *dst)
{
    FS_OpenFile(file, path);
    FS_ReadFile(file, dst, TITLE_MES_CHARS_SIZE);
    FS_CloseFile(file);
}
CLEAN_AS(func_ov147_0229a48c, TitleMes_ReadChars)

/* func_ov147_0229a4b4: the message's characters, its palette and screen `screen` loaded to the
 * main screen's background 3, each through a block of the current heap freed after; a block
 * that cannot be had is skipped. The two first paths are copied to the stack first, as the
 * original does.
 * REQUIRES: `screen` is 0 or 1 (the game reads its table past the two entries otherwise). */
void TitleMes_Load(int screen)
{
    char chars_path[28];
    char palette_path[28];
    u8 file[0x4c]; /* an FSFile */

    for (int i = 0; i < 28; i++) {
        chars_path[i] = data_ov147_0229ac24[i];
    }
    const char *const screens[TITLE_MES_SCREENS] = {data_ov147_0229ac0c[0], data_ov147_0229ac0c[1]};
    for (int i = 0; i < 28; i++) {
        palette_path[i] = data_ov147_0229ac40[i];
    }
    FS_InitFile(file);

    void *data = (void *) (uintptr_t) (u32) TitleMes_Alloc(TITLE_MES_CHARS_SIZE);
    if (data != NULL) {
        TitleMes_ReadChars(file, chars_path, data);
        TitleMes_UploadChars(data);
        TitleMes_Free(data);
    }
    data = (void *) (uintptr_t) (u32) TitleMes_Alloc(TITLE_MES_PALETTE_SIZE);
    if (data != NULL) {
        TitleMes_ReadPalette(file, palette_path, data);
        TitleMes_UploadPalette(data);
        TitleMes_Free(data);
    }
    data = (void *) (uintptr_t) (u32) TitleMes_Alloc(TITLE_MES_SCREEN_SIZE);
    if (data != NULL) {
        TitleMes_ReadScreen(file, screens[screen], data);
        TitleMes_UploadScreen((unsigned int) (uintptr_t) data);
        TitleMes_Free(data);
    }
}
CLEAN_AS(func_ov147_0229a4b4, TitleMes_Load)

/* func_ov147_0229a578: a block of the current heap freed, unless NULL. */
void TitleMes_Free(void *data)
{
    if (data != NULL) {
        Heap_FreeCurrent(data);
    }
}
CLEAN_AS(func_ov147_0229a578, TitleMes_Free)

/* func_ov147_0229a58c: a block of `size` bytes from the back of the current heap (its address,
 * 0 when there is none). */
int TitleMes_Alloc(unsigned int size)
{
    return (int) (uintptr_t) Heap_AllocCurrentBack((int) size);
}
CLEAN_AS(func_ov147_0229a58c, TitleMes_Alloc)

/* func_ov147_0229a594: a frame of the pulse: taken away, it fades out from where it is; fading,
 * the step goes down to 0; else up to 10, where it is held until the frames held pass 5, then
 * fades. Answers 1 once it has faded out (step 0 or below) when it is taken away or another
 * screen was asked for. */
int TitleMes_Pulse(TitleMes *self)
{
    int withdrawn = self->wanted == TITLE_MES_NONE;
    if (withdrawn) {
        self->fading = 1;
        self->held = 0;
    }
    if (self->fading != 0) {
        self->level--;
        if (self->level <= 0) {
            self->fading = 0;
        }
    } else {
        self->level++;
        if (self->level >= TITLE_MES_LEVELS) {
            self->level = TITLE_MES_LEVELS;
            self->held++;
            if (self->held > TITLE_MES_HOLD) {
                self->fading = 1;
                self->held = 0;
            }
        }
    }
    if (self->level > 0) {
        return 0;
    }
    return withdrawn || self->shown != self->wanted;
}
CLEAN_AS(func_ov147_0229a594, TitleMes_Pulse)

/* func_ov147_0229a608: the pulse from its start (out, rising). */
void TitleMes_ResetBlend(TitleMes *self)
{
    self->level = 0;
    self->held = 0;
    self->fading = 0;
}
CLEAN_AS(func_ov147_0229a608, TitleMes_ResetBlend)

/* func_ov147_0229a614: whether nothing is shown and nothing is waited for. */
int TitleMes_IsIdle(TitleMes *self)
{
    return self->shown == TITLE_MES_NONE && self->state == TITLE_MES_IDLE;
}
CLEAN_AS(func_ov147_0229a614, TitleMes_IsIdle)

/* func_ov147_0229a628: the message taken away. */
void TitleMes_Withdraw(TitleMes *self)
{
    self->wanted = TITLE_MES_NONE;
}
CLEAN_AS(func_ov147_0229a628, TitleMes_Withdraw)

/* func_ov147_0229a630: screen `screen` asked for. */
void TitleMes_Request(TitleMes *self, int screen)
{
    self->wanted = screen;
}
CLEAN_AS(func_ov147_0229a630, TitleMes_Request)

/* func_ov147_0229a634 (_ZN18Obj_ov147_0229ac1c19func_ov147_0229a634Ev): the frame of the
 * step `state` (TitleMesState) through the table of member functions, filled once from its
 * constants.
 * REQUIRES: the state is below 3; the game reads past the table for others. */
void TitleMes_Update(TitleMes *self)
{
    static const MemberPointer *const steps[TITLE_MES_STATES] = {
        &data_ov147_0229ac04, /* TitleMes_RunIdle */
        &data_ov147_0229abfc, /* TitleMes_RunWaiting */
        &data_ov147_0229abf4, /* TitleMes_RunShown */
    };
    MemberTable_InitOnce(&data_ov147_022a2aac, data_ov147_022a2ab0, steps, TITLE_MES_STATES);
    MemberPointer_CallVoid(&data_ov147_022a2ab0[self->state], self);
}
CLEAN_AS(_ZN18Obj_ov147_0229ac1c19func_ov147_0229a634Ev, TitleMes_Update)

/* func_ov147_0229a6a8: nothing to let go. */
void TitleMes_Release(TitleMes *self)
{
    (void) self;
}
CLEAN_AS(func_ov147_0229a6a8, TitleMes_Release)

/* func_ov147_0229a6ac: nothing shown nor asked for, the pulse from its start. */
void TitleMes_Init(TitleMes *self)
{
    self->state = TITLE_MES_IDLE;
    self->shown = TITLE_MES_NONE;
    self->delay = 0;
    self->wanted = TITLE_MES_NONE;
    TitleMes_ResetBlend(self);
    TitleMes_SetIdle(self);
}
CLEAN_AS(func_ov147_0229a6ac, TitleMes_Init)

/* func_ov147_0229a6cc (vtable slot 1): destructed and freed. */
TitleMes *TitleMes_Delete(TitleMes *self)
{
    self->vtable = data_ov147_0229ac1c;
    Heap_OperatorDeleteB(self);
    return self;
}
CLEAN_AS(func_ov147_0229a6cc, TitleMes_Delete)

/* func_ov147_0229a6e4 (vtable slot 0): the destructor, the class's vtable set. */
void TitleMes_Destruct(TitleMes *self)
{
    self->vtable = data_ov147_0229ac1c;
}
CLEAN_AS(func_ov147_0229a6e4, TitleMes_Destruct)

/* func_ov147_0229a6f0: the constructor, the class's vtable set. */
void TitleMes_Construct(TitleMes *self)
{
    self->vtable = data_ov147_0229ac1c;
}
CLEAN_AS(func_ov147_0229a6f0, TitleMes_Construct)
