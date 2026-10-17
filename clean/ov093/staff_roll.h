/* Overlay 93: the staff roll ("st_staffroll"), the object the cafe's music show makes through
 * overlay 4 (ov004/music_show_overlay.h; 0x2520 bytes from the scenes' heap).
 *
 * The roll's text is message archive "st_staffroll": its line n is line n % 6 of message n / 6,
 * 0xcc lines in all. It is laid out on two background layers (0 and 4), each with a map of 32
 * rows of 32 cells kept in the object (StaffRollScreen) and uploaded by a layer load task when a
 * row was added. A row is a copy of a row of the template map "menu/staff/bg.bsc" (read into
 * `template_map` at the start): template row n shows the tiles of text slot n (tiles
 * 0x11 + n * 16, 16 cells wide), into which a label draws the line's text. A line after a blank
 * line (a heading) takes one row, left-aligned; another line takes two rows, against the right
 * edge; a blank line two empty rows. The labels are closed again at the start of every update.
 *
 * The roll scrolls up by `speed` (1/4096 pixels a frame) on both layers, layer 4 0xc0 pixels
 * behind layer 0. Once the show switches to its logo (StaffRoll_ShowLogo), layer 0 shows
 * "menu/staff/logo.bsc", slid down from 0x78 pixels above behind window 0, held, and faded out
 * by the main screen's alpha blend; then the roll stops and says it has ended (flag 8). */
#ifndef CLEAN_OV093_STAFF_ROLL_H
#define CLEAN_OV093_STAFF_ROLL_H

#include "clean.h"
#include "main/layer_load_task.h"
#include "main/text_label.h"
#include "types.h"

/* The text the roll's messages are loaded into (vtable data_ov093_022998b8): main's 8-bit text
 * base with 422 characters of its own. */
#define STAFF_ROLL_TEXT_CAPACITY 422

typedef struct StaffRollText {
    const TextVtable *vtable;             /* 0x00: data_ov093_022998b8 */
    u8 base_04[0xe];                      /* the text base's */
    char chars[STAFF_ROLL_TEXT_CAPACITY]; /* 0x12 */
} StaffRollText;

/* In StaffRollScreen.flags. */
enum StaffRollScreenFlag {
    STAFF_ROLL_SCREEN_HEADING = 0x01, /* the next line is a heading (after a blank line) */
    STAFF_ROLL_SCREEN_DIRTY = 0x02,   /* the map changed and is to be uploaded */
    STAFF_ROLL_SCREEN_DONE = 0x04     /* 13 rows were laid out without text in a row */
};

#define STAFF_ROLL_MAP_ROWS 32
#define STAFF_ROLL_MAP_COLUMNS 32

/* What is laid out on one layer. */
typedef struct StaffRollScreen {
    s16 rows;       /* 0x00: the rows laid out so far (the map's row is this modulo 32) */
    s16 line;       /* 0x02: the next line of the text; -1 before the first */
    u8 slot;        /* 0x04: the next text slot (template row) */
    u8 flags;       /* 0x05: StaffRollScreenFlag */
    u8 blank_count; /* 0x06: rows laid out without text since the last line of text */
    u8 pad_07;
    u16 map[STAFF_ROLL_MAP_ROWS * STAFF_ROLL_MAP_COLUMNS]; /* 0x08 */
} StaffRollScreen;

/* In StaffRoll.flags. */
#define STAFF_ROLL_FLAG_ENDED 0x0008

/* StaffRoll.state. */
enum StaffRollState {
    STAFF_ROLL_STATE_IDLE = 0,
    STAFF_ROLL_STATE_BEGIN = 1,       /* set by StaffRoll_Restart: the layers set up next frame */
    STAFF_ROLL_STATE_ROLL = 2,        /* the text scrolls on both layers */
    STAFF_ROLL_STATE_LOGO_BLEND = 3,  /* the logo loaded with the blend set (no code of this
                                       * overlay sets this state) */
    STAFF_ROLL_STATE_LOGO_WINDOW = 4, /* set by StaffRoll_ShowLogo: the logo loaded next frame */
    STAFF_ROLL_STATE_LOGO_FADE = 5,   /* the logo held, then faded out */
    STAFF_ROLL_STATE_LOGO_SLIDE = 6   /* the logo slides down behind window 0 */
};

#define STAFF_ROLL_LABELS 26
#define STAFF_ROLL_SCREENS 2

typedef struct StaffRoll {
    u16 flags; /* 0x00: STAFF_ROLL_FLAG_ENDED */
    u8 pad_02[2];
    u8 label_count; /* 0x04: the labels in use this frame */
    u8 state;       /* 0x05: StaffRollState */
    u8 counter;     /* 0x06: the frames of the logo's fade */
    u8 pad_07;
    s32 scroll;             /* 0x08: in 1/4096 pixels */
    s32 window;             /* 0x0c: the logo's slide, in 1/4096 pixels (negative while above) */
    s32 speed;              /* 0x10: added to `scroll` each frame */
    s32 window_speed;       /* 0x14: added to `window` each frame */
    StaffRollScreen layer0; /* 0x18 */
    StaffRollScreen layer4; /* 0x820 */
    u16 template_map[STAFF_ROLL_MAP_ROWS * STAFF_ROLL_MAP_COLUMNS]; /* 0x1028: "menu/staff/bg.bsc" */
    StaffRollText text;                                             /* 0x1828: the message of the current lines */
    TextLabel labels[STAFF_ROLL_LABELS];                            /* 0x19e0 */
    LayerTask tasks[STAFF_ROLL_SCREENS];                            /* 0x24d8: layer 4's map, then layer 0's */
} StaffRoll;

static_assert(sizeof(StaffRollText) == 0x1b8, "staff roll text");
static_assert(sizeof(StaffRollScreen) == 0x808, "staff roll screen");
static_assert(offsetof(StaffRoll, layer0) == 0x18 && offsetof(StaffRoll, layer4) == 0x820, "screens");
static_assert(offsetof(StaffRoll, template_map) == 0x1028 && offsetof(StaffRoll, text) == 0x1828, "template");
static_assert(offsetof(StaffRoll, labels) == 0x19e0 && offsetof(StaffRoll, tasks) == 0x24d8, "labels");
static_assert(sizeof(StaffRoll) == 0x2520, "size (ov004's Heap_Alloc)");

int StaffRollText_Chars(StaffRollText *text);
int StaffRollText_Capacity(void);
StaffRollText *StaffRollText_Delete(StaffRollText *text);
StaffRollText *StaffRollText_Destruct(StaffRollText *text);
StaffRollText *StaffRollText_Construct(StaffRollText *text);
void StaffRoll_SetFlags(u16 *flags, int mask);
int StaffRoll_TestFlags(u16 *flags, u16 mask);
void StaffRollScreen_ClearFlags(StaffRollScreen *screen, u8 mask);
void StaffRollScreen_SetFlags(StaffRollScreen *screen, int mask);
int StaffRollScreen_TestFlags(StaffRollScreen *screen, int mask);
void StaffRollScreen_Reset(StaffRollScreen *screen);
void StaffRollScreen_Destruct(StaffRollScreen *screen);
void StaffRollScreen_Construct(StaffRollScreen *screen);
void StaffRoll_LoadLogo(StaffRoll *self);
void StaffRoll_CloseLabels(StaffRoll *self);
TextLabel *StaffRoll_NextLabel(StaffRoll *self);
void StaffRoll_Scroll(StaffRoll *self, int both);
void StaffRoll_LayOutRow(StaffRoll *self, int layer, StaffRollScreen *screen);
int StaffRoll_Line(StaffRoll *self, int line);
void StaffRoll_CopyTemplateRow(StaffRoll *self, u16 *map, int template_row, int map_row);
void StaffRoll_ClearRow(StaffRoll *self, u16 *map, int map_row);
void StaffRoll_Advance(StaffRoll *self, int layer, int y);
int StaffRoll_HasEnded(StaffRoll *self);
void StaffRoll_ShowLogo(StaffRoll *self);
void StaffRoll_Stop(StaffRoll *self);
void StaffRoll_Restart(StaffRoll *self, int speed);
void StaffRoll_LoadRollGraphics(StaffRoll *self);
void StaffRoll_ReadTemplate(StaffRoll *self);
void StaffRoll_Close(StaffRoll *self);
void StaffRoll_Upload(StaffRoll *self);
void StaffRoll_Update(StaffRoll *self);
void StaffRoll_Start(StaffRoll *self);
StaffRoll *StaffRoll_Destruct(StaffRoll *self);
StaffRoll *StaffRoll_Construct(StaffRoll *self);

#endif
