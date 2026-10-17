/* The title's logo (title_scene.h): "menu/title/bg" on the sub screen's background 2, its
 * characters 0x140-0x2ff drawn from a copy in the overlay's .bss (`title_logo_shown`) that the
 * wipes rebuild each frame from the logo's own characters ANDed with a mask:
 *
 * - wiping in, the screen's diagonals (column + row, from the top left) are uncovered one more
 *   each frame, the newest 15 behind the front through the 15 characters of "mask1.bch"
 *   (TitleLogo_StepWipeIn), until every character is whole;
 * - wiping out, every character goes through the 7 characters of "mask0.bch", the last first
 *   (TitleLogo_StepWipeOut), then the layer is hidden. */
#include "title_scene.h"

#include "clean.h"
#include "main/display_layers.h"
#include "main/empty_0203de64.h"
#include "main/rom_file.h"
#include "main/screen_transition.h"

#define TITLE_LOGO_LAYER LAYER_SUB_BG2
#define TITLE_LOGO_FIRST_CHAR 0x140
#define TITLE_LOGO_LAST_CHAR 0x2ff
#define TITLE_LOGO_CHARS (TITLE_LOGO_LAST_CHAR - TITLE_LOGO_FIRST_CHAR + 1) /* 448 */
#define TITLE_LOGO_CHAR_WORDS 8                                             /* a 16-colour character */
#define TITLE_LOGO_CHARS_SIZE 0x3800
#define TITLE_LOGO_SCREEN_SIZE 0x800
#define TITLE_LOGO_BLANK_CHAR 0x10 /* a character of the screen left as it is */
#define TITLE_LOGO_COLUMNS 32
#define TITLE_LOGO_ROWS 21     /* the rows masked */
#define TITLE_LOGO_DIAGONAL 24 /* the rows a diagonal is walked down */
#define TITLE_LOGO_FRONTS 15   /* the characters of mask1, the diagonals behind the front */
#define TITLE_LOGO_WIPE_IN_STEPS 0x36
#define TITLE_LOGO_WIPE_OUT_MASKS 7
#define TITLE_LOGO_SHOW_FRAMES 0x4b0
#define TITLE_LOGO_FINISH_STEP 0x64 /* a step past the wipe in's end */

/* The logo's files. */
extern const char data_ov147_0229ab5c[]; /* "menu/title/bg.bpl" */
extern const char data_ov147_0229ab70[]; /* "menu/title/bg.bsc" */
extern const char data_ov147_0229ab84[]; /* "menu/title/bg.bch" */
extern const char data_ov147_0229ab98[]; /* "menu/title/mask0.bch" */
extern const char data_ov147_0229abb0[]; /* "menu/title/mask1.bch" */
extern const char data_ov147_0229abc8[]; /* "menu/title/mask2.bch" */

/* The overlay's .bss: the masks as read, the screen, the logo's characters and the copy of
 * them drawn. */
extern u32 data_ov147_0229ae0c[TITLE_LOGO_WIPE_OUT_MASKS][TITLE_LOGO_CHAR_WORDS]; /* mask0 */
extern u32 data_ov147_0229aeec[TITLE_LOGO_FRONTS][TITLE_LOGO_CHAR_WORDS];         /* mask2, not used */
extern u32 data_ov147_0229b0cc[TITLE_LOGO_FRONTS][TITLE_LOGO_CHAR_WORDS];         /* mask1 */
extern u16 data_ov147_0229b2ac[TITLE_LOGO_SCREEN_SIZE / 2];
extern u32 data_ov147_0229baac[TITLE_LOGO_CHARS][TITLE_LOGO_CHAR_WORDS];
extern u32 data_ov147_0229f2ac[TITLE_LOGO_CHARS][TITLE_LOGO_CHAR_WORDS];

/* The game's heap; the screen's transition (main/screen_transition.h). */
extern Heap *data_021fbe94;
extern u8 data_021c75b8;

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);

/* The copy of the logo's characters the layer is given. */
static int title_logo_shown(void)
{
    return (int) (uintptr_t) data_ov147_0229f2ac;
}

static void title_logo_queue_chars(TitleScene *self)
{
    LayerTask_QueueChars(&self->chars_task, title_logo_shown(), TITLE_LOGO_LAYER, TITLE_LOGO_FIRST_CHAR, TITLE_LOGO_FIRST_CHAR,
                         TITLE_LOGO_LAST_CHAR);
}

/* func_ov147_02298f20: the character at (`column`, `row`) of the logo's screen, when it is one
 * of the logo's (0x140 or above, not character 0x10), redrawn through `pattern`.
 * REQUIRES: the cell is inside the screen (column + 32 * row below 0x400). */
void TitleLogo_MaskCell(TitleScene *self, const u32 *pattern, int column, int row)
{
    int character = data_ov147_0229b2ac[column + (row << 5)] & 0x3ff;
    if (character != TITLE_LOGO_BLANK_CHAR && character >= TITLE_LOGO_FIRST_CHAR) {
        TitleLogo_MaskChar(self, pattern, character - TITLE_LOGO_FIRST_CHAR);
    }
}
CLEAN_AS(func_ov147_02298f20, TitleLogo_MaskCell)

/* func_ov147_02298f54: the logo's character `index` (from 0x140) copied to the one drawn,
 * ANDed with `pattern` word by word. */
void TitleLogo_MaskChar(TitleScene *self, const u32 *pattern, int index)
{
    (void) self;
    const u32 *chars = data_ov147_0229baac[0] + index * TITLE_LOGO_CHAR_WORDS;
    u32 *shown = data_ov147_0229f2ac[0] + index * TITLE_LOGO_CHAR_WORDS;
    for (int i = 0; i < TITLE_LOGO_CHAR_WORDS; i++) {
        shown[i] = chars[i] & pattern[i];
    }
}
CLEAN_AS(func_ov147_02298f54, TitleLogo_MaskChar)

/* func_ov147_02298f88: a frame of the wipe out: with masks left, the next one down (`logo_step`
 * counts them) applied to all 448 characters and those queued for the layer, answering 0;
 * after the last, the layer hidden and 1. */
int TitleLogo_StepWipeOut(TitleScene *self)
{
    if (self->logo_step == 0) {
        DisplayLayer_Hide(TITLE_LOGO_LAYER);
        Empty0203de64_NothingValue68(1);
        return 1;
    }
    self->logo_step--;
    const u32 *mask = data_ov147_0229ae0c[self->logo_step];
    for (int i = 0; i < TITLE_LOGO_CHARS; i++) {
        TitleLogo_MaskChar(self, mask, i);
    }
    title_logo_queue_chars(self);
    return 0;
}
CLEAN_AS(func_ov147_02298f88, TitleLogo_StepWipeOut)

/* func_ov147_02299008: the wipe out from its first mask (TITLE_LOGO_WIPE_OUT). */
void TitleLogo_StartWipeOut(TitleScene *self)
{
    self->logo_step = TITLE_LOGO_WIPE_OUT_MASKS;
    self->logo_state = TITLE_LOGO_WIPE_OUT;
}
CLEAN_AS(func_ov147_02299008, TitleLogo_StartWipeOut)

/* func_ov147_02299018: a frame of the wipe in. Below step 0x36 the 15 diagonals behind the
 * front (diagonal `logo_step` + 9 and down, not below 9) are drawn through the 15 characters of
 * mask1, the front's first: each diagonal walked from its top right cell (column at most 31)
 * down to the left, over 24 rows of which the first 21 are drawn; the characters are queued and
 * the step counted, answering 0. From step 0x36 on the whole logo is drawn and queued, and 1. */
int TitleLogo_StepWipeIn(TitleScene *self)
{
    s32 step = self->logo_step;
    if (step >= TITLE_LOGO_WIPE_IN_STEPS) {
        MI_CpuCopy8(data_ov147_0229baac, data_ov147_0229f2ac, TITLE_LOGO_CHARS_SIZE);
        title_logo_queue_chars(self);
        return 1;
    }

    int diagonal = step + 9;
    for (int i = 0; i < TITLE_LOGO_FRONTS && diagonal >= 9; i++, diagonal--) {
        const u32 *mask = data_ov147_0229b0cc[i];
        int column = diagonal;
        int row = 0;
        if (column > TITLE_LOGO_COLUMNS - 1) {
            row = column - (TITLE_LOGO_COLUMNS - 1);
            column = TITLE_LOGO_COLUMNS - 1;
        }
        for (; column >= 0 && row < TITLE_LOGO_DIAGONAL; column--, row++) {
            if (row < TITLE_LOGO_ROWS) {
                TitleLogo_MaskCell(self, mask, column, row);
            }
        }
    }
    title_logo_queue_chars(self);
    self->logo_step = self->logo_step + 1;
    return 0;
}
CLEAN_AS(func_ov147_02299018, TitleLogo_StepWipeIn)

/* func_ov147_022990dc: the wipe in from its start (TITLE_LOGO_WIPE_IN), the logo then to stay
 * 0x4b0 frames; the characters drawn cleared and the layer shown. */
void TitleLogo_StartWipeIn(TitleScene *self)
{
    self->logo_state = TITLE_LOGO_WIPE_IN;
    self->logo_step = 0;
    self->logo_timer = TITLE_LOGO_SHOW_FRAMES;
    MI_CpuFill8(data_ov147_0229f2ac, 0, TITLE_LOGO_CHARS_SIZE);
    DisplayLayer_Show(TITLE_LOGO_LAYER);
}
CLEAN_AS(func_ov147_022990dc, TitleLogo_StartWipeIn)

/* func_ov147_02299118: the layer hidden at once (TITLE_LOGO_HIDDEN). */
void TitleLogo_Hide(TitleScene *self)
{
    DisplayLayer_Hide(TITLE_LOGO_LAYER);
    Empty0203de64_NothingValue68(1);
    self->logo_state = TITLE_LOGO_HIDDEN;
}
CLEAN_AS(func_ov147_02299118, TitleLogo_Hide)

/* func_ov147_02299134: the logo sent away: wiped out when it is shown, else hidden at once. */
void TitleLogo_Dismiss(TitleScene *self)
{
    if (self->logo_state == TITLE_LOGO_SHOWN) {
        TitleLogo_StartWipeOut(self);
    } else {
        TitleLogo_Hide(self);
    }
}
CLEAN_AS(func_ov147_02299134, TitleLogo_Dismiss)

/* func_ov147_02299154: while it wipes in, the wipe in's next frame made its last. */
void TitleLogo_FinishWipeIn(TitleScene *self)
{
    if (self->logo_state == TITLE_LOGO_WIPE_IN) {
        self->logo_step = TITLE_LOGO_FINISH_STEP;
    }
}
CLEAN_AS(func_ov147_02299154, TitleLogo_FinishWipeIn)

/* func_ov147_02299168: the logo's frame (TitleLogoState):
 * - TITLE_LOGO_LOAD: once the screen is shown, loaded and wiping in;
 * - TITLE_LOGO_SKIPPED: once the screen is shown, message 1 asked for, the idle timer set and
 *   the logo counted hidden;
 * - TITLE_LOGO_WIPE_IN: when done, shown, and message 0 asked for unless a press is being
 *   answered (`press_delay`);
 * - TITLE_LOGO_SHOWN: its time counted; when out, wiping out with message 1 asked for;
 * - TITLE_LOGO_WIPE_OUT: when done, gone. */
void TitleLogo_Update(TitleScene *self)
{
    switch (self->logo_state) {
        case TITLE_LOGO_LOAD:
            if (data_021c75b8 == SCREEN_TRANSITION_SHOWN) {
                TitleLogo_Load(self);
                TitleLogo_StartWipeIn(self);
            }
            break;
        case TITLE_LOGO_SKIPPED:
            if (data_021c75b8 == SCREEN_TRANSITION_SHOWN) {
                TitleMes_Request(&self->mes, 1);
                self->idle_timer = 0xe10;
                self->logo_state = TITLE_LOGO_HIDDEN;
            }
            break;
        case TITLE_LOGO_WIPE_IN:
            if (TitleLogo_StepWipeIn(self) != 0) {
                self->logo_state = TITLE_LOGO_SHOWN;
                if (self->press_delay == 0) {
                    TitleMes_Request(&self->mes, 0);
                }
            }
            break;
        case TITLE_LOGO_SHOWN:
            if (self->logo_timer != 0) {
                self->logo_timer--;
            } else {
                TitleLogo_StartWipeOut(self);
                TitleMes_Request(&self->mes, 1);
            }
            break;
        case TITLE_LOGO_WIPE_OUT:
            if (TitleLogo_StepWipeOut(self) != 0) {
                self->logo_state = TITLE_LOGO_GONE;
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov147_02299168, TitleLogo_Update)

/* func_ov147_02299248: the logo's graphics: background 2 of the sub screen set up (priority
 * 1), palettes 8-15, the screen read and loaded, the logo's characters and the three masks
 * read, and the characters drawn cleared and loaded to characters 0x140-0x2ff. */
void TitleLogo_Load(TitleScene *self)
{
    (void) self;
    Empty0203de64_NothingValue6c(1);
    DisplayLayer_SetBgControl(TITLE_LOGO_LAYER, 0, 0, 0);
    DisplayLayer_SetPriority(TITLE_LOGO_LAYER, 1);
    DisplayLayer_LoadPalettesFromFile(data_ov147_0229ab5c, data_021fbe94, TITLE_LOGO_LAYER, 8, 8, 15);
    RomFile_Read(data_ov147_0229ab70, data_ov147_0229b2ac, TITLE_LOGO_SCREEN_SIZE);
    DisplayLayer_LoadScreen(data_ov147_0229b2ac, TITLE_LOGO_LAYER, TITLE_LOGO_SCREEN_SIZE, 0);
    RomFile_Read(data_ov147_0229ab84, data_ov147_0229baac, TITLE_LOGO_CHARS_SIZE);
    MI_CpuFill8(data_ov147_0229f2ac, 0, TITLE_LOGO_CHARS_SIZE);
    RomFile_Read(data_ov147_0229ab98, data_ov147_0229ae0c, sizeof(data_ov147_0229ae0c));
    RomFile_Read(data_ov147_0229abb0, data_ov147_0229b0cc, sizeof(data_ov147_0229b0cc));
    RomFile_Read(data_ov147_0229abc8, data_ov147_0229aeec, sizeof(data_ov147_0229aeec));
    DisplayLayer_LoadChars((u32) (uintptr_t) data_ov147_0229f2ac, TITLE_LOGO_LAYER, TITLE_LOGO_FIRST_CHAR,
                           TITLE_LOGO_FIRST_CHAR, TITLE_LOGO_LAST_CHAR);
}
CLEAN_AS(func_ov147_02299248, TitleLogo_Load)
