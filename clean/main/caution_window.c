/* The caution window of a wireless session (caution_window.h). */
#include "caution_window.h"

#include "autoload_2/heap.h"    /* Heap_AllocCurrentBack, Heap_FreeCurrent */
#include "autoload_2/input.h"   /* PadState */
#include "autoload_2/network.h" /* Net_GetMode, Net_GetError */
#include "autoload_2/vector.h"  /* Vec3 */
#include "backup_card.h"        /* BackupCard_Shutdown */
#include "clean.h"
#include "display_shadow.h" /* the planes and windows of both screens */
#include "lid_sleep.h"      /* LidSleep_KeepSoundOff */
#include "main/session.h"   /* Session_GetConnectMode, Session_GetErrorFlags, ... */
#include "ov004/member_pointer.h"
#include "session_link.h" /* Session_Close */
#include "sound.h"        /* SoundSys_MasterVolumeOff */
#include "text_draw.h"    /* TextDrawBox, TextDraw_Center, TextDraw_RequestDraw */
#include "tile_convert.h" /* TileConvert_CharsToBitmap */

static_assert(offsetof(CautionWindow, model_resource) == 0x060, "model resource");
static_assert(offsetof(CautionWindow, matrix) == 0x068, "matrix");
static_assert(offsetof(CautionWindow, transfer) == 0x0a0, "transfer");
static_assert(offsetof(CautionWindow, state) == 0x0bc, "state");
static_assert(offsetof(CautionWindow, shown) == 0x0c8, "shown");
static_assert(offsetof(CautionWindow, blend_main) == 0x0cc, "blend");
static_assert(offsetof(CautionWindow, main_planes) == 0x0d0, "planes");
static_assert(offsetof(CautionWindow, text_width) == 0x0e0, "text width");
static_assert(offsetof(CautionWindow, message) == 0x0e8, "message");
static_assert(offsetof(CautionWindow, unit) == 0x1fc, "unit");
static_assert(offsetof(CautionWindow, line_text) == 0x250, "line text");
static_assert(offsetof(CautionWindow, bitmap) == 0x2e4, "bitmap");

#define REG16(address) (*(volatile u16 *) (address))
#define REG_BLDCNT REG16(0x04000050)
#define REG_DB_BLDCNT REG16(0x04001050)

#define PAD_A 0x0001

/* The window's tag and model file. */
#define CAUTION_WINDOW_TAG 0x43617557 /* 'CauW' */
extern const char data_020da570[];    /* "caution/caution_window.nsbmd" */

/* The countdown: 300 frames (15 seconds of 20 frames), and 20 frames past its end. */
#define CAUTION_WINDOW_FRAMES_PER_SECOND 20
#define CAUTION_WINDOW_COUNTDOWN_FRAMES 300
#define CAUTION_WINDOW_COUNTDOWN_SECONDS 15
/* The session's error flags that shut down at once (all but 0x01 and 0x02). */
#define CAUTION_WINDOW_SERIOUS_ERRORS 0x7c
/* The error flag the network's own errors raise. */
#define CAUTION_WINDOW_NET_ERROR 0x10
/* The line the seconds follow. */
#define CAUTION_WINDOW_SECONDS_LINE 3

/* The object. */
extern CautionWindow data_021c5c4c;
/* The session (main/session.h). */
extern NetSession *data_020ccf94;

/* The three labels its messages are loaded into at start-up and copied from: the message
 * (0xe3), the seconds' unit (0xe4) and the last message (0xe5). */
extern u8 data_021c5a24[];
extern u8 data_021c59d0[];
extern u8 data_021c5b38[];
/* Whether the session's network mode was 3 or 4 when it shut down (func_02038bfc), and the
 * network's error code then. */
extern u8 data_021c5934;
/* The two characters put between the last line and its seconds, ended by 0. */
extern const u16 data_020da4d0[3];
/* The font a text box starts with. */
extern TextFont data_021c8230;
/* The kind of field (0 the town, 1 the rooms), and an object whose halfword at 0xc may be 5:
 * the window is only used with one of them. */
extern u8 data_020e54a8;
typedef struct CautionWindowMode {
    u8 unk_00[0xc];
    u16 mode;
} CautionWindowMode;
extern CautionWindowMode *data_021f42f4;
/* The touch screen: the pen is down, and it went down or up this frame. The pad. */
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern PadState data_021fbe40;
/* The matrix CautionWindow_SetMatrix builds. */
extern Mtx43 data_021fbe48;

/* The member function table of CautionWindow_Update (a function-local static): its guard, the
 * table and the constants it is filled from. */
extern u32 data_021c593c;
extern MemberPointer data_021c5990[CAUTION_WINDOW_STATES];
extern const MemberPointer data_020da4e0, data_020da500, data_020da4d8, data_020da4e8, data_020da510, data_020da4f0,
    data_020da4f8, data_020da508;

/* The 3D state of the NITRO System's G3D: its projection and camera matrices, its flags and
 * the camera's vectors. */
typedef struct CautionWindowG3dState {
    u8 unk_00[0x7c];
    u32 flags; /* 0x7c */
} CautionWindowG3dState;
typedef struct CautionWindowG3dCamera {
    u8 unk_00[0x40];
    Vec3 position; /* 0x40 */
    Vec3 up;       /* 0x4c */
    Vec3 target;   /* 0x58 */
} CautionWindowG3dCamera;
extern CautionWindowG3dState data_027e0148;
extern CautionWindowG3dCamera data_027e02c8;
extern u8 data_027e00d0[]; /* the projection matrix */
extern u8 data_027e0114[]; /* the camera matrix */
/* The camera's position. */
extern Vec3 data_021fbee8;

/* A 3D model (the window's): loaded from a file under a tag, freed, scaled. */
extern int func_0205556c(void *model, u32 tag, const char *path);
extern int func_02055454(void *model);
extern void func_02055e7c(void *model, const Vec3 *scale);
/* The address in texture VRAM (in bytes) of a texture's image. */
extern unsigned int func_02057a7c(const u8 *texture);
/* Starts the copy of `size` bytes from `src` into texture VRAM at `dst` (kind 2). */
extern int func_020b9f80(void *transfer, const void *src, unsigned int dst, int size, u8 kind);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void G3i_PerspectiveW_(unsigned int sin, unsigned int cos, unsigned int aspect, unsigned int near, unsigned int far,
                              unsigned int scale_w, unsigned int draw, void *matrix);
extern void G3i_LookAt_(Vec3 *position, Vec3 *up, Vec3 *target, int draw, void *matrix);
extern fx32 FX_MulFunc(fx32 a, fx32 b);

/* Labels (text_label.h): emptied, a line set, measured, characters or another label
 * appended, another's text copied over. */
extern void func_020a8c1c(void *label);
extern const char *func_020a7bf4(const char *text, int line); /* line `line` of a text, or NULL */
extern int func_020a8a34(void *label, const char *line);
extern int func_020a8f74(void *label);
extern int func_020a89f8(void *label, const void *chars);
extern int func_020a89dc(void *label, void *other);
extern void *func_020a8bb8(void *label, const void *from);
/* Queues the loading of message `*number` into a label. */
extern int func_020b4980(void *label, u8 *number, int table);
/* The network's error code as text (" <%d>"). */
extern void *func_02038b80(void);
/* Records the network's error code and whether its mode is 3 or 4 (data_021c5934). */
extern void func_02038bfc(void);
/* The library routine the end of the shutdown calls (also on other fatal errors). */
extern void func_02116a1c(int arg);

/* A number written as text into a 0x40-byte object (built and destroyed). */
typedef struct CautionWindowNumber {
    u32 words[0x40 / 4];
} CautionWindowNumber;
extern void *func_020b5630(void *text);
extern void *func_020b5618(void *text);
extern int func_020b45d0(void *text, int value, int format, int a, int b, int c);

/* Text boxes drawing into a RAM buffer (`cells` x `rows` tiles), freed by func_020a8fb8. */
extern TextDrawBox *func_020a8fe8(void *ram, int cells, int rows);
extern void func_020a8fb8(TextDrawBox *box);

#define CAUTION_WINDOW_CELLS 0x20
#define CAUTION_WINDOW_ROWS 2
#define CAUTION_WINDOW_BOX_STYLE 5
#define CAUTION_WINDOW_SECONDS_WIDTH 0x12 /* the seconds are centred in 18 pixels */

/* The text of a label or of a number text: its vtable slot 0x0c. */
static const char *caution_window_text(void *object)
{
    typedef const char *(*CautionWindowTextMethod)(void *object);
    const u8 *vtable = *(const u8 *const *) object;
    u32 method = *(const u32 *) (vtable + 0x0c);
    return ((CautionWindowTextMethod) (uintptr_t) method)(object);
}

/* A box set up to draw `text` once into its RAM buffer, the text's colour 0 on colour 1. */
static void caution_window_box_text(TextDrawBox *box, void *text_object)
{
    box->layer = CAUTION_WINDOW_BOX_STYLE;
    box->text = caution_window_text(text_object);
    box->update_mode = TEXT_DRAW_AT_ONCE;
    box->screens = TEXT_DRAW_TO_RAM;
    box->font = &data_021c8230;
    box->rows_full_width = 0;
}

/* func_02037fa8: state 7: after its frame, func_02116a1c(0). */
void CautionWindow_EndUpdate(CautionWindow *self)
{
    self->timer--;
    if (self->timer <= 0) {
        func_02116a1c(0);
    }
}
CLEAN_AS(func_02037fa8, CautionWindow_EndUpdate)

/* func_02037fd0 */
void CautionWindow_EnterEnd(CautionWindow *self)
{
    self->state = CAUTION_WINDOW_END;
    self->timer = 1;
    self->shown = 1;
}
CLEAN_AS(func_02037fd0, CautionWindow_EnterEnd)

/* func_02037fe8: state 6: a line of the last message drawn each frame; once 20 frames are over,
 * a touch of the screen or the A button ends it. */
void CautionWindow_LastMessageUpdate(CautionWindow *self)
{
    if (self->line < CAUTION_WINDOW_LINES) {
        CautionWindow_ComposeLine(self, self->line, 1);
        CautionWindow_DrawLine(self);
        CautionWindow_UploadLine(self, self->line);
        self->line++;
    }
    self->timer--;
    if (self->timer <= 0) {
        int touched = data_021fbdd8 != 0 && data_021fbddc != 0;
        if (touched || (data_021fbe40.pressed & PAD_A) != 0) {
            CautionWindow_EnterEnd(self);
        }
    }
}
CLEAN_AS(func_02037fe8, CautionWindow_LastMessageUpdate)

/* func_02038078 */
void CautionWindow_EnterLastMessage(CautionWindow *self)
{
    self->state = CAUTION_WINDOW_LAST_MESSAGE;
    self->line = 0;
    self->shown = 1;
    self->text_width = 0;
    self->seconds = -1;
    self->timer = 20;
}
CLEAN_AS(func_02038078, CautionWindow_EnterLastMessage)

/* func_020380a8: state 5: the last message becomes the window's message. */
void CautionWindow_ShutdownUpdate(CautionWindow *self)
{
    func_020a8bb8(self->message, data_021c5b38);
    CautionWindow_EnterLastMessage(self);
}
CLEAN_AS(func_020380a8, CautionWindow_ShutdownUpdate)

/* func_020380c4: the texture cleared, the sound stopped, the network's error recorded, the
 * backup card and the session shut down. */
void CautionWindow_EnterShutdown(CautionWindow *self)
{
    self->state = CAUTION_WINDOW_SHUTDOWN;
    self->shown = 1;
    CautionWindow_ClearTexture(self);
    CautionWindow_StopSound(self);
    func_02038bfc();
    BackupCard_Shutdown();
    Session_Close();
}
CLEAN_AS(func_020380c4, CautionWindow_EnterShutdown)

/* func_020380f4: state 4: the lines drawn one a frame, then the last one again whenever its
 * seconds change. Back to idle when the trouble is over; else the shutdown once the countdown
 * is 20 frames past 0. */
void CautionWindow_CountdownUpdate(CautionWindow *self)
{
    int seconds = (self->timer + CAUTION_WINDOW_FRAMES_PER_SECOND - 1) / CAUTION_WINDOW_FRAMES_PER_SECOND;
    int changed = self->seconds != seconds;
    self->seconds = seconds;

    if (self->line < CAUTION_WINDOW_LINES) {
        CautionWindow_ComposeLine(self, self->line, 0);
        CautionWindow_DrawLine(self);
        CautionWindow_UploadLine(self, self->line);
        self->line++;
    } else if (changed) {
        CautionWindow_ComposeLine(self, CAUTION_WINDOW_SECONDS_LINE, 0);
        CautionWindow_DrawLine(self);
        CautionWindow_UploadLine(self, CAUTION_WINDOW_SECONDS_LINE);
    }

    if (self->trouble == 0) {
        CautionWindow_EnterIdle(self);
    } else {
        self->timer--;
        if (self->timer <= -CAUTION_WINDOW_FRAMES_PER_SECOND) {
            CautionWindow_EnterShutdown(self);
        }
    }
}
CLEAN_AS(func_020380f4, CautionWindow_CountdownUpdate)

/* func_020381a4 */
void CautionWindow_EnterCountdown(CautionWindow *self)
{
    self->state = CAUTION_WINDOW_COUNTDOWN;
    self->timer = CAUTION_WINDOW_COUNTDOWN_FRAMES;
    self->line = 0;
    self->shown = 1;
    self->text_width = 0;
    self->seconds = CAUTION_WINDOW_COUNTDOWN_SECONDS;
}
CLEAN_AS(func_020381a4, CautionWindow_EnterCountdown)

/* func_020381d8: state 3: the message and the seconds' unit copied in. */
void CautionWindow_OpenUpdate(CautionWindow *self)
{
    func_020a8bb8(self->message, data_021c5a24);
    func_020a8bb8(self->unit, data_021c59d0);
    CautionWindow_EnterCountdown(self);
}
CLEAN_AS(func_020381d8, CautionWindow_OpenUpdate)

/* func_02038208: the texture cleared and the screen's planes hidden. */
void CautionWindow_EnterOpen(CautionWindow *self)
{
    self->state = CAUTION_WINDOW_OPEN;
    self->shown = 0;
    CautionWindow_ClearTexture(self);
    CautionWindow_HidePlanes(self);
}
CLEAN_AS(func_02038208, CautionWindow_EnterOpen)

/* func_0203822c: state 2: back to idle when the trouble is over, else open when the delay is. */
void CautionWindow_DelayUpdate(CautionWindow *self)
{
    if (self->trouble == 0) {
        CautionWindow_EnterIdle(self);
    } else {
        self->timer--;
        if (self->timer <= 0) {
            CautionWindow_EnterOpen(self);
        }
    }
}
CLEAN_AS(func_0203822c, CautionWindow_DelayUpdate)

/* func_02038264 */
void CautionWindow_EnterDelay(CautionWindow *self)
{
    self->state = CAUTION_WINDOW_DELAY;
    self->timer = 20;
    self->shown = 0;
}
CLEAN_AS(func_02038264, CautionWindow_EnterDelay)

/* func_0203827c: state 1: on trouble, a serious error shuts down at once (the planes hidden
 * first); any other waits out the delay. */
void CautionWindow_IdleUpdate(CautionWindow *self)
{
    if (self->trouble != 0) {
        if ((Session_GetShownErrorFlags(data_020ccf94) & CAUTION_WINDOW_SERIOUS_ERRORS) != 0) {
            CautionWindow_HidePlanes(self);
            CautionWindow_EnterShutdown(self);
        } else {
            CautionWindow_EnterDelay(self);
        }
    }
}
CLEAN_AS(func_0203827c, CautionWindow_IdleUpdate)

/* func_020382b8: the screen's planes given back. */
void CautionWindow_EnterIdle(CautionWindow *self)
{
    self->state = CAUTION_WINDOW_IDLE;
    self->shown = 0;
    CautionWindow_RestorePlanes(self);
}
CLEAN_AS(func_020382b8, CautionWindow_EnterIdle)

/* func_020382d0: state 0: nothing. */
void CautionWindow_OffUpdate(CautionWindow *self)
{
    (void) self;
}
CLEAN_AS(func_020382d0, CautionWindow_OffUpdate)

/* func_020382d4 */
void CautionWindow_EnterOff(CautionWindow *self)
{
    self->state = CAUTION_WINDOW_OFF;
}
CLEAN_AS(func_020382d4, CautionWindow_EnterOff)

/* func_020382dc: the network's errors raise the session's error flag 0x10: in connect mode 0
 * every error but 0x800c and 0x400b, in mode 1 every error but 0x80ff, 0x800c, 0x4006, 0x400a
 * and 0x400b; never in network modes 0 and 6. */
void CautionWindow_CheckNetError(void)
{
    int mode = Net_GetMode();
    if (mode == 0 || mode == 6) {
        return;
    }
    u32 connect = Session_GetConnectMode(data_020ccf94);
    int error = Net_GetError();
    int raise;
    if (connect == 0 && error != 0 && error != 0x800c && error != 0x400b) {
        raise = 1;
    } else if (connect != 1) {
        raise = 0;
    } else {
        raise = error != 0 && error != 0x80ff && error != 0x800c && error != 0x4006 && error != 0x400a && error != 0x400b;
    }
    if (raise) {
        NetSession *session = data_020ccf94;
        Session_SetErrorFlags(session, (int) (Session_GetErrorFlags(session) | CAUTION_WINDOW_NET_ERROR));
    }
}
CLEAN_AS(func_020382dc, CautionWindow_CheckNetError)

/* func_02038368: the sound kept off and the master volume turned off. */
void CautionWindow_StopSound(CautionWindow *self)
{
    (void) self;
    LidSleep_KeepSoundOff();
    SoundSys_MasterVolumeOff();
}
CLEAN_AS(func_02038368, CautionWindow_StopSound)

/* func_0203837c: when hidden, the planes and windows saved by CautionWindow_HidePlanes are set
 * again and the blend registers are to be restored. */
void CautionWindow_RestorePlanes(CautionWindow *self)
{
    if (self->planes_hidden) {
        self->planes_hidden = 0;
        DisplayShadow_SetMainPlanes((u8) self->main_planes);
        DisplayShadow_SetSubPlanes((u8) self->sub_planes);
        DisplayShadow_SetMainWindows((u8) self->main_windows);
        DisplayShadow_SetSubWindows((u8) self->sub_windows);
        self->blend_pending = 1;
    }
}
CLEAN_AS(func_0203837c, CautionWindow_RestorePlanes)

/* func_020383c4: unless hidden already, the planes and windows of both screens saved; only the
 * main screen's BG0 (the 3D) stays, without windows, and the blend registers are to be
 * saved and cleared. */
void CautionWindow_HidePlanes(CautionWindow *self)
{
    if (self->planes_hidden == 0) {
        self->planes_hidden = 1;
        self->main_planes = DisplayShadow_GetMainPlanes();
        self->sub_planes = DisplayShadow_GetSubPlanes();
        self->main_windows = DisplayShadow_GetMainWindows();
        self->sub_windows = DisplayShadow_GetSubWindows();
        DisplayShadow_SetMainPlanes(1);
        DisplayShadow_SetSubPlanes(0);
        DisplayShadow_SetMainWindows(0);
        DisplayShadow_SetSubWindows(0);
        self->blend_pending = 1;
    }
}
CLEAN_AS(func_020383c4, CautionWindow_HidePlanes)

/* func_02038424: nothing hidden or saved. */
void CautionWindow_Reset(CautionWindow *self)
{
    self->planes_hidden = 0;
    self->main_planes = 0;
    self->sub_planes = 0;
    self->main_windows = 0;
    self->sub_windows = 0;
}
CLEAN_AS(func_02038424, CautionWindow_Reset)

/* func_02038444: line `line` of the message put in line_text. On the seconds' line, while there
 * are seconds, its width is kept and two characters and the unit follow (the seconds are
 * drawn in between); with `with_code` and the network in mode 3 or 4, its error code follows. */
void CautionWindow_ComposeLine(CautionWindow *self, int line, int with_code)
{
    func_020a8c1c(self->line_text);
    self->text_width = 0;
    const char *text = func_020a7bf4(caution_window_text(self->message), line);
    if (text == NULL) {
        return;
    }
    func_020a8a34(self->line_text, text);
    if (self->seconds >= 0 && line == CAUTION_WINDOW_SECONDS_LINE) {
        self->text_width = func_020a8f74(self->line_text);
        u16 gap[3];
        for (int i = 0; i < 3; i++) {
            gap[i] = data_020da4d0[i];
        }
        func_020a89f8(self->line_text, gap);
        func_020a89dc(self->line_text, self->unit);
    }
    if (with_code != 0 && line == CAUTION_WINDOW_SECONDS_LINE && data_021c5934 != 0) {
        func_020a89f8(self->line_text, func_02038b80());
    }
}
CLEAN_AS(func_02038444, CautionWindow_ComposeLine)

/* func_020384f8: the seconds (written in format 2) drawn over the bitmap in `chars`, centred in 18
 * pixels from `x` past the line's text. */
void CautionWindow_DrawSeconds(CautionWindow *self, void *chars, int x)
{
    CautionWindowNumber number;

    func_020b5630(&number);
    func_020b45d0(&number, self->seconds, 2, 0, 0, 0);
    unsigned int width = (unsigned int) func_020a8f74(&number);
    unsigned int margin = width < CAUTION_WINDOW_SECONDS_WIDTH ? (CAUTION_WINDOW_SECONDS_WIDTH - width) / 2 : 0;
    u32 offset = margin + (u32) (x + self->text_width);
    TextDrawBox *box = func_020a8fe8(chars, CAUTION_WINDOW_CELLS, CAUTION_WINDOW_ROWS);
    if (box != NULL) {
        caution_window_box_text(box, &number);
        box->offset = offset;
        box->background = 1;
        box->color = 0;
        box->merge = 1;
        TextDraw_RequestDraw(box);
        func_020a8fb8(box);
    }
    func_020b5618(&number);
}
CLEAN_AS(func_020384f8, CautionWindow_DrawSeconds)

/* func_0203859c: line_text drawn centred into the bitmap (through a buffer from the back of
 * the current heap), with the seconds after it when it has them. */
void CautionWindow_DrawLine(CautionWindow *self)
{
    void *chars = Heap_AllocCurrentBack(CAUTION_WINDOW_BITMAP_SIZE);
    if (chars == NULL) {
        return;
    }
    TextDrawBox *box = func_020a8fe8(chars, CAUTION_WINDOW_CELLS, CAUTION_WINDOW_ROWS);
    if (box != NULL) {
        caution_window_box_text(box, self->line_text);
        TextDraw_Center(box);
        box->background = 1;
        box->color = 0;
        TextDraw_RequestDraw(box);
        int x = (int) box->offset;
        func_020a8fb8(box);
        if (self->seconds >= 0 && self->text_width != 0) {
            CautionWindow_DrawSeconds(self, chars, x);
        }
        TileConvert_CharsToBitmap(chars, (u32 *) self->bitmap, CAUTION_WINDOW_CELLS, CAUTION_WINDOW_ROWS);
    }
    Heap_FreeCurrent(chars);
}
CLEAN_AS(func_0203859c, CautionWindow_DrawLine)

/* func_0203864c: the bitmap filled with colour 1 and copied into all four parts. */
void CautionWindow_ClearTexture(CautionWindow *self)
{
    MI_CpuFill8(self->bitmap, 0x11, CAUTION_WINDOW_BITMAP_SIZE);
    for (int part = 0; part < CAUTION_WINDOW_LINES; part++) {
        CautionWindow_UploadLine(self, part);
    }
}
CLEAN_AS(func_0203864c, CautionWindow_ClearTexture)

/* func_02038680: the bitmap copied into part `part` of the model's first texture: the texture
 * block at the resource's offset 8, its dictionary at the block's halfword 0xa, the texture's
 * entry at the dictionary's offset 8. */
void CautionWindow_UploadLine(CautionWindow *self, int part)
{
    const u8 *resource = self->model_resource;
    const u8 *block = resource + *(const s32 *) (resource + 8);
    const u8 *dictionary = block + *(const u16 *) (block + 0xa);
    const u8 *texture = block + *(const s32 *) (dictionary + 8);
    unsigned int address = func_02057a7c(texture);
    func_020b9f80(self->transfer, self->bitmap, address + (unsigned int) part * CAUTION_WINDOW_BITMAP_SIZE,
                  CAUTION_WINDOW_BITMAP_SIZE, 2);
}
CLEAN_AS(func_02038680, CautionWindow_UploadLine)

/* func_020386c4: the window's matrix, a translation to z -1.0 (built in data_021fbe48). */
void CautionWindow_SetMatrix(CautionWindow *self)
{
    Mtx43_Translation(&data_021fbe48, 0, 0, -0x1000);
    self->matrix = data_021fbe48;
}
CLEAN_AS(func_020386c4, CautionWindow_SetMatrix)

/* func_020386fc: once asked, the blend registers of both screens saved and cleared while the
 * planes are hidden, restored otherwise.
 * HW: BLDCNT of the main screen is read and written before the sub screen's. */
void CautionWindow_ApplyBlend(CautionWindow *self)
{
    if (self->blend_pending == 0) {
        return;
    }
    if (self->planes_hidden != 0) {
        self->blend_main = REG_BLDCNT;
        self->blend_sub = REG_DB_BLDCNT;
        REG_BLDCNT = 0;
        REG_DB_BLDCNT = 0;
    } else {
        REG_BLDCNT = self->blend_main;
        REG_DB_BLDCNT = self->blend_sub;
    }
    self->blend_pending = 0;
}
CLEAN_AS(func_020386fc, CautionWindow_ApplyBlend)

/* func_02038758: while shown, the projection (and the 3D state's flags 0x50 cleared), a camera
 * at data_021fbee8 looking down -z (flags 0xe8 cleared), and the model's scale. */
void CautionWindow_SetCamera(CautionWindow *self)
{
    if (self->shown == 0) {
        return;
    }
    G3i_PerspectiveW_(0x424, 0xf74, 0x1548, 0xf6, 0x3e800, 0x1000, 0, data_027e00d0);
    data_027e0148.flags &= ~0x50u;
    Vec3 position = data_021fbee8;
    Vec3 target = {0, 0, -0x1000};
    Vec3 up = {0, 0x1000, 0};
    data_027e02c8.position = position;
    data_027e02c8.up = up;
    data_027e02c8.target = target;
    G3i_LookAt_(&position, &up, &target, 0, data_027e0114);
    data_027e0148.flags &= ~0xe8u;
    fx32 scale = FX_MulFunc(0xb7, 0xf6d);
    Vec3 scales = {scale, scale, 0x1000};
    func_02055e7c(self->model, &scales);
}
CLEAN_AS(func_02038758, CautionWindow_SetCamera)

/* func_02038828: a frame: whether there is trouble kept, the network's errors checked, and the
 * state's member function called (the table is filled on the first call).
 * REQUIRES: the state is 0-7 (the ROM indexes its table unchecked). */
void CautionWindow_Update(CautionWindow *self, unsigned char trouble)
{
    static const MemberPointer *const constants[CAUTION_WINDOW_STATES] = {
        &data_020da4e0, /* CautionWindow_OffUpdate */
        &data_020da500, /* CautionWindow_IdleUpdate */
        &data_020da4d8, /* CautionWindow_DelayUpdate */
        &data_020da4e8, /* CautionWindow_OpenUpdate */
        &data_020da510, /* CautionWindow_CountdownUpdate */
        &data_020da4f0, /* CautionWindow_ShutdownUpdate */
        &data_020da4f8, /* CautionWindow_LastMessageUpdate */
        &data_020da508, /* CautionWindow_EndUpdate */
    };

    self->trouble = trouble;
    CautionWindow_CheckNetError();
    MemberTable_InitOnce(&data_021c593c, data_021c5990, constants, CAUTION_WINDOW_STATES);
    MemberPointer_CallVoid(&data_021c5990[self->state], self);
}
CLEAN_AS(func_02038828, CautionWindow_Update)

/* func_020388f0: unless off, the model freed and the window off. */
void CautionWindow_Close(CautionWindow *self)
{
    if (self->state != CAUTION_WINDOW_OFF) {
        func_02055454(self->model);
        self->state = CAUTION_WINDOW_OFF;
    }
}
CLEAN_AS(func_020388f0, CautionWindow_Close)

/* func_02038910: in the town, the rooms, or with data_021f42f4's mode 5, the model loaded and
 * the window idle; otherwise off. */
void CautionWindow_Start(CautionWindow *self)
{
    int field = data_020e54a8 == 0 || data_020e54a8 == 1;
    int mode_5 = data_021f42f4->mode == 5;
    CautionWindow_Reset(self);
    if (field || mode_5) {
        func_0205556c(self->model, CAUTION_WINDOW_TAG, data_020da570);
        CautionWindow_SetMatrix(self);
        self->line = 0;
        self->shown = 0;
        CautionWindow_EnterIdle(self);
    } else {
        CautionWindow_EnterOff(self);
    }
}
CLEAN_AS(func_02038910, CautionWindow_Start)

/* func_02038998: the loading of the three messages queued; the last request's result. */
int CautionWindow_LoadMessages(void)
{
    u8 numbers[3] = {0xe3, 0xe4, 0xe5};
    func_020b4980(data_021c5a24, &numbers[0], 0);
    func_020b4980(data_021c59d0, &numbers[1], 0);
    return func_020b4980(data_021c5b38, &numbers[2], 0);
}
CLEAN_AS(func_02038998, CautionWindow_LoadMessages)

/* func_020389e0 */
void CautionWindow_ApplyBlendGlobal(void)
{
    CautionWindow_ApplyBlend(&data_021c5c4c);
}
CLEAN_AS(func_020389e0, CautionWindow_ApplyBlendGlobal)

/* func_020389f0 */
void CautionWindow_SetCameraGlobal(void)
{
    CautionWindow_SetCamera(&data_021c5c4c);
}
CLEAN_AS(func_020389f0, CautionWindow_SetCameraGlobal)

/* func_02038a00 */
void CautionWindow_UpdateGlobal(int trouble)
{
    CautionWindow_Update(&data_021c5c4c, (unsigned char) trouble);
}
CLEAN_AS(func_02038a00, CautionWindow_UpdateGlobal)

/* func_02038a10 */
void CautionWindow_CloseGlobal(void)
{
    CautionWindow_Close(&data_021c5c4c);
}
CLEAN_AS(func_02038a10, CautionWindow_CloseGlobal)

/* func_02038a20 */
void CautionWindow_StartGlobal(void)
{
    CautionWindow_Start(&data_021c5c4c);
}
CLEAN_AS(func_02038a20, CautionWindow_StartGlobal)

/* func_02038a30: whether the window is shutting down (state 5 or later). */
int CautionWindow_IsShuttingDown(void)
{
    return data_021c5c4c.state >= CAUTION_WINDOW_SHUTDOWN;
}
CLEAN_AS(func_02038a30, CautionWindow_IsShuttingDown)
