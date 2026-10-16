/* The message box of a talk (talk_box.h). */
#include "talk_box.h"

#include "autoload_2/heap.h" /* Heap_AllocCurrentBack, Heap_FreeCurrent */
#include "clean.h"
#include "display_shadow.h"

static_assert(offsetof(TalkBox, arrow) == 0x0c, "TalkBox arrow");
static_assert(offsetof(TalkBox, spinner) == 0x50, "TalkBox spinner");
static_assert(offsetof(TalkBox, x) == 0x74, "TalkBox place");
static_assert(offsetof(TalkBox, spinner_hold) == 0x7c, "TalkBox hold");
static_assert(sizeof(TalkBox) == 0x80, "TalkBox");

extern void FS_InitFile(void *file);
extern int FS_OpenFile(void *file, const char *path);
extern s32 FS_ReadFile(void *file, void *dst, s32 size);
extern int FS_CloseFile(void *file);
extern void DC_FlushRange(const void *start, u32 size);
extern void GX_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void GX_LoadBG2Char(const void *src, u32 offset, u32 size);
extern void GX_LoadBG2Scr(const void *src, u32 offset, u32 size);

/* "/a_mes/a_mes_bg_ncg.bin", "/a_mes/a_mes_bg_ncl.bin", "/a_mes/a_mes0a_bg_nsc.bin" (with
 * the name plate) and "/a_mes/a_mes0b_bg_nsc.bin" (without). */
extern const char data_020df0d0[];
extern const char data_020df0e8[];
extern const char data_020df100[];
extern const char data_020df11c[];
/* The palette of the text area by the talk's kind. */
extern const u8 data_020cce90[];

#define TALK_BOX_FS_FILE_SIZE 0x48
#define TALK_BOX_FS_READ_FAILED (-1)

#define TALK_BOX_SCREEN_SIZE 0x800
#define TALK_BOX_PALETTE_SIZE 0x180
#define TALK_BOX_CHARACTERS_SIZE 0x2800
/* The palette is uploaded from its second colour on: colour 0 of BG palette 0 is the
 * backdrop. */
#define TALK_BOX_PALETTE_SKIP 2

/* The text colour that is drawn as colour 3 (the same as colour 2). */
#define TALK_BOX_COLOUR_ALIAS 9
#define TALK_BOX_COLOUR_ALIASED 2

/* The arrow and the spinner placed from the box's place. */
#define TALK_BOX_ARROW_X 0x55
#define TALK_BOX_ARROW_Y 0x47
#define TALK_BOX_SPINNER_X 0x59
#define TALK_BOX_SPINNER_Y 0x4b

/* The arrow's vtable slots: draw and animate. */
#define TALK_BOX_ARROW_SLOT_DRAW 2
#define TALK_BOX_ARROW_SLOT_UPDATE 3

/* Window 0 of the main screen: from line 60 to the bottom, as wide as the box shows. */
#define TALK_BOX_WINDOW_TOP 60
#define TALK_BOX_WINDOW_BOTTOM 192
#define TALK_BOX_WINDOW_RIGHT 255

/* BG2 and window 0 in the main screen's planes and windows. */
#define TALK_BOX_PLANE_BG2 0x04
#define TALK_BOX_WINDOW_0 0x01
/* Inside window 0: all planes; outside it: all but BG2. */
#define TALK_BOX_WINDOW_0_PLANES 0x1f
#define TALK_BOX_OUTSIDE_PLANES 0x1b

/* BG2's control register: priority 1, screen base 6, no mosaic. */
#define TALK_BOX_REG16(address) (*(volatile u16 *) (address))
#define TALK_BOX_REG_BG2CNT TALK_BOX_REG16(0x0400000c)
#define TALK_BOX_BGCNT_PRIORITY 0x0003
#define TALK_BOX_BGCNT_KEEP 0x0043 /* the priority, the character base and the mosaic */
#define TALK_BOX_BGCNT_MOSAIC 0x0040
#define TALK_BOX_BG2_PRIORITY 1
#define TALK_BOX_BG2_SCREEN_BASE 0x0600

/* The screen: 32 entries a row; an entry's palette in its top four bits. */
#define TALK_BOX_SCREEN_WIDTH 32
#define TALK_BOX_PALETTE_BITS 0xf000
#define TALK_BOX_PALETTE_SHIFT 12
/* The text area: rows 15 to 24, columns 1 to 30. */
#define TALK_BOX_TEXT_TOP 15
#define TALK_BOX_TEXT_BOTTOM 24
#define TALK_BOX_TEXT_LEFT 1
#define TALK_BOX_TEXT_RIGHT 30
/* The name plate: rows 13 to 16, columns 3 to 14; its entries of palette 1 take another. */
#define TALK_BOX_PLATE_TOP 13
#define TALK_BOX_PLATE_BOTTOM 16
#define TALK_BOX_PLATE_LEFT 3
#define TALK_BOX_PLATE_RIGHT 14
#define TALK_BOX_PLATE_PALETTE 0x1000
#define TALK_BOX_PLATE_NO_VILLAGER 0xb000
#define TALK_BOX_PLATE_STYLED 0x2000

typedef void TalkBoxArrowSlot(CellPairSprite *arrow);

static void talk_box_call_arrow(TalkBox *box, int slot)
{
    ((TalkBoxArrowSlot *) (uintptr_t) box->arrow.vtable[slot])(&box->arrow);
}

/* func_02068bc8: the colour a text of colour `colour` is drawn with: one more, colour 9
 * drawn as colour 2 is.
 * QUIRK: the result is truncated to a byte. */
u8 TalkBox_TextColour(int colour)
{
    if (colour == TALK_BOX_COLOUR_ALIAS) {
        colour = TALK_BOX_COLOUR_ALIASED;
    }
    return (u8) (colour + 1);
}
CLEAN_AS(func_02068bc8, TalkBox_TextColour)

/* func_02068bd8: the spinner drawn. */
int TalkBox_DrawSpinner(TalkBox *box)
{
    return TalkSpinner_CallDraw(&box->spinner);
}
CLEAN_AS(func_02068bd8, TalkBox_DrawSpinner)

/* func_02068be4: the spinner placed by the box and stepped; one frame less of the hold after
 * it stopped. */
void TalkBox_UpdateSpinner(TalkBox *box)
{
    TalkSpinner_SetOffset(&box->spinner, box->x + TALK_BOX_SPINNER_X, box->y + TALK_BOX_SPINNER_Y);
    TalkSpinner_CallUpdate(&box->spinner);
    if (box->spinner_hold > 0) {
        box->spinner_hold--;
    }
}
CLEAN_AS(func_02068be4, TalkBox_UpdateSpinner)

/* func_02068c10: the spinner stopped; the arrow waits a few frames more. */
void TalkBox_StopSpinner(TalkBox *box)
{
    TalkSpinner_Stop(&box->spinner);
    box->spinner_hold = TALK_BOX_SPINNER_HOLD;
}
CLEAN_AS(func_02068c10, TalkBox_StopSpinner)

/* func_02068c24: the spinner started with `sound`; the arrow waits until it stops. */
void TalkBox_StartSpinner(TalkBox *box, int sound)
{
    TalkSpinner_Start(&box->spinner, sound);
    box->spinner_hold = TALK_BOX_SPINNING;
}
CLEAN_AS(func_02068c24, TalkBox_StartSpinner)

/* func_02068c3c: whether the spinner is done and the arrow played pose 3 to its end. */
int TalkBox_ArrowPose3Done(TalkBox *box)
{
    return box->spinner_hold == 0 && CellPairSprite_Pose(&box->arrow) == TALK_BOX_ARROW_POSE_3 &&
           CellPairSprite_AnimsDone(&box->arrow) != 0;
}
CLEAN_AS(func_02068c3c, TalkBox_ArrowPose3Done)

/* func_02068c6c: whether the spinner is done and the arrow played pose 2 to its end. */
int TalkBox_ArrowPose2Done(TalkBox *box)
{
    return box->spinner_hold == 0 && CellPairSprite_Pose(&box->arrow) == TALK_BOX_ARROW_POSE_2 &&
           CellPairSprite_AnimsDone(&box->arrow) != 0;
}
CLEAN_AS(func_02068c6c, TalkBox_ArrowPose2Done)

/* func_02068c9c: whether the spinner is done and the arrow waits. */
int TalkBox_ArrowWaiting(TalkBox *box)
{
    return box->spinner_hold == 0 && CellPairSprite_Pose(&box->arrow) == TALK_BOX_ARROW_WAITING;
}
CLEAN_AS(func_02068c9c, TalkBox_ArrowWaiting)

/* func_02068cbc: whether the spinner is done and the arrow is hidden. */
int TalkBox_ArrowHidden(TalkBox *box)
{
    return box->spinner_hold == 0 && CellPairSprite_Pose(&box->arrow) == TALK_BOX_ARROW_HIDDEN;
}
CLEAN_AS(func_02068cbc, TalkBox_ArrowHidden)

/* func_02068cdc: the arrow drawn (its vtable slot 2). */
void TalkBox_DrawArrow(TalkBox *box)
{
    talk_box_call_arrow(box, TALK_BOX_ARROW_SLOT_DRAW);
}
CLEAN_AS(func_02068cdc, TalkBox_DrawArrow)

/* func_02068cf0: the arrow placed by the box and animated (its vtable slot 3). */
void TalkBox_UpdateArrow(TalkBox *box)
{
    CellPairSprite_SetPlace(&box->arrow, (u32) (box->x + TALK_BOX_ARROW_X), (u32) (box->y + TALK_BOX_ARROW_Y));
    talk_box_call_arrow(box, TALK_BOX_ARROW_SLOT_UPDATE);
}
CLEAN_AS(func_02068cf0, TalkBox_UpdateArrow)

/* func_02068d14 */
void TalkBox_SetArrowPose3(TalkBox *box)
{
    CellPairSprite_SetPose(&box->arrow, TALK_BOX_ARROW_POSE_3);
}
CLEAN_AS(func_02068d14, TalkBox_SetArrowPose3)

/* func_02068d20 */
void TalkBox_SetArrowPose2(TalkBox *box)
{
    CellPairSprite_SetPose(&box->arrow, TALK_BOX_ARROW_POSE_2);
}
CLEAN_AS(func_02068d20, TalkBox_SetArrowPose2)

/* func_02068d2c */
void TalkBox_ShowArrow(TalkBox *box)
{
    CellPairSprite_SetPose(&box->arrow, TALK_BOX_ARROW_WAITING);
}
CLEAN_AS(func_02068d2c, TalkBox_ShowArrow)

/* func_02068d38 */
void TalkBox_HideArrow(TalkBox *box)
{
    CellPairSprite_SetPose(&box->arrow, TALK_BOX_ARROW_HIDDEN);
}
CLEAN_AS(func_02068d38, TalkBox_HideArrow)

/* func_02068d44: the box placed at (x, y): BG2 scrolled by it, and window 0 cut to the part
 * of the screen the box covers (from -x to 255 - x, kept within 0 to 255).
 * QUIRK: the window's edges are only clamped on the side a shift can cross; they are passed
 * as bytes. */
void TalkBox_SetPlace(TalkBox *box, int x, int y)
{
    box->x = x;
    box->y = y;
    DisplayShadow_SetMainBg2Scroll((unsigned int) x, (unsigned int) y);
    int right = TALK_BOX_WINDOW_RIGHT - x;
    int left = -x;
    if (left < 0) {
        left = 0;
    }
    if (right > TALK_BOX_WINDOW_RIGHT) {
        right = TALK_BOX_WINDOW_RIGHT;
    }
    DisplayShadow_SetMainWindow0((u8) left, TALK_BOX_WINDOW_TOP, (u8) right, TALK_BOX_WINDOW_BOTTOM);
}
CLEAN_AS(func_02068d44, TalkBox_SetPlace)

/* func_02068d74: the box placed at (0, y). */
void TalkBox_SetOffset(TalkBox *box, int y)
{
    TalkBox_SetPlace(box, 0, y);
}
CLEAN_AS(func_02068d74, TalkBox_SetOffset)

/* func_02068d80: BG2 and window 0 of the main screen turned off. */
void TalkBox_Hide(TalkBox *box)
{
    (void) box;
    DisplayShadow_HideMainPlanes(TALK_BOX_PLANE_BG2);
    DisplayShadow_DisableMainWindows(TALK_BOX_WINDOW_0);
}
CLEAN_AS(func_02068d80, TalkBox_Hide)

/* func_02068d98: BG2 and window 0 of the main screen turned on. */
void TalkBox_Show(void)
{
    DisplayShadow_ShowMainPlanes(TALK_BOX_PLANE_BG2);
    DisplayShadow_EnableMainWindows(TALK_BOX_WINDOW_0);
}
CLEAN_AS(func_02068d98, TalkBox_Show)

/* func_02068db0: the palette (from its second colour), the characters and the screen
 * uploaded to BG2 of the main screen, each flushed from the cache first. */
void TalkBox_Upload(TalkBox *box)
{
    const u8 *palette = (const u8 *) box->palette;
    DC_FlushRange(palette + TALK_BOX_PALETTE_SKIP, TALK_BOX_PALETTE_SIZE - TALK_BOX_PALETTE_SKIP);
    GX_LoadBGPltt(palette + TALK_BOX_PALETTE_SKIP, TALK_BOX_PALETTE_SKIP, TALK_BOX_PALETTE_SIZE - TALK_BOX_PALETTE_SKIP);
    DC_FlushRange(box->characters, TALK_BOX_CHARACTERS_SIZE);
    GX_LoadBG2Char(box->characters, 0, TALK_BOX_CHARACTERS_SIZE);
    DC_FlushRange(box->screen, TALK_BOX_SCREEN_SIZE);
    GX_LoadBG2Scr(box->screen, 0, TALK_BOX_SCREEN_SIZE);
}
CLEAN_AS(func_02068db0, TalkBox_Upload)

/* func_02068e04: BG2 of the main screen set up for the box (priority 1, screen base 6, no
 * mosaic), and the planes inside and outside window 0.
 * HW: the control register is read and written three times, in this order. */
void TalkBox_SetUpBg2(void)
{
    TALK_BOX_REG_BG2CNT = (u16) ((TALK_BOX_REG_BG2CNT & ~TALK_BOX_BGCNT_PRIORITY) | TALK_BOX_BG2_PRIORITY);
    TALK_BOX_REG_BG2CNT = (u16) ((TALK_BOX_REG_BG2CNT & TALK_BOX_BGCNT_KEEP) | TALK_BOX_BG2_SCREEN_BASE);
    TALK_BOX_REG_BG2CNT = (u16) (TALK_BOX_REG_BG2CNT & ~TALK_BOX_BGCNT_MOSAIC);
    DisplayShadow_SetMainWindow0Planes(TALK_BOX_WINDOW_0_PLANES);
    DisplayShadow_SetMainOutsidePlanes(TALK_BOX_OUTSIDE_PLANES);
}
CLEAN_AS(func_02068e04, TalkBox_SetUpBg2)

/* func_02068e44: the screen, the palette and the characters freed (those that are there). */
void TalkBox_FreeFiles(TalkBox *box)
{
    if (box->screen != NULL) {
        Heap_FreeCurrent(box->screen);
        box->screen = NULL;
    }
    if (box->palette != NULL) {
        Heap_FreeCurrent(box->palette);
        box->palette = NULL;
    }
    if (box->characters != NULL) {
        Heap_FreeCurrent(box->characters);
        box->characters = NULL;
    }
}
CLEAN_AS(func_02068e44, TalkBox_FreeFiles)

/* func_02068e78: the box's files read, stopping at the first that fails (0 then, else 1).
 * A talk of kind 0 with a named speaker gets the screen with the name plate, the plate
 * coloured for the speaker; any other the screen without it, its text area coloured by the
 * kind. */
int TalkBox_Load(TalkBox *box, int kind, int nameless, int style, u8 no_villager)
{
    u8 file[TALK_BOX_FS_FILE_SIZE];
    int with_plate = nameless == 0 && kind == 0;
    FS_InitFile(file);
    if (TalkBox_LoadScreen(box, file, with_plate) == 0) {
        return 0;
    }
    if (TalkBox_LoadPalette(box, file) == 0) {
        return 0;
    }
    if (TalkBox_LoadCharacters(box, file) == 0) {
        return 0;
    }
    if (with_plate) {
        TalkBox_ColourPlate(box, style, no_villager);
    } else {
        TalkBox_ColourText(box, kind);
    }
    return 1;
}
CLEAN_AS(func_02068e78, TalkBox_Load)

/* func_02068ee4: the text area of the screen given the palette data_020cce90 holds for
 * `kind`.
 * REQUIRES: `kind` indexes data_020cce90. */
void TalkBox_ColourText(TalkBox *box, int kind)
{
    for (int row = TALK_BOX_TEXT_TOP; row <= TALK_BOX_TEXT_BOTTOM; row++) {
        for (int column = TALK_BOX_TEXT_LEFT; column <= TALK_BOX_TEXT_RIGHT; column++) {
            u16 *entry = &box->screen[row * TALK_BOX_SCREEN_WIDTH + column];
            u16 palette = (u16) ((data_020cce90[kind] & 0xf) << TALK_BOX_PALETTE_SHIFT);
            *entry = (u16) ((*entry & ~TALK_BOX_PALETTE_BITS) | palette);
        }
    }
}
CLEAN_AS(func_02068ee4, TalkBox_ColourText)

/* func_02068f2c: the name plate's entries of palette 1 given palette 11 when the talk has no
 * villager, else palette 2 when the speaker has a style; left as they are otherwise. */
void TalkBox_ColourPlate(TalkBox *box, int style, int no_villager)
{
    u16 palette;
    if (no_villager) {
        palette = TALK_BOX_PLATE_NO_VILLAGER;
    } else if (style != 0) {
        palette = TALK_BOX_PLATE_STYLED;
    } else {
        return;
    }
    for (int row = TALK_BOX_PLATE_TOP; row <= TALK_BOX_PLATE_BOTTOM; row++) {
        for (int column = TALK_BOX_PLATE_LEFT; column <= TALK_BOX_PLATE_RIGHT; column++) {
            u16 *entry = &box->screen[row * TALK_BOX_SCREEN_WIDTH + column];
            if ((*entry & TALK_BOX_PALETTE_BITS) == TALK_BOX_PLATE_PALETTE) {
                *entry = (u16) ((*entry & ~TALK_BOX_PALETTE_BITS) | palette);
            }
        }
    }
}
CLEAN_AS(func_02068f2c, TalkBox_ColourPlate)

/* func_02068fa0: the first 0x2800 bytes of a_mes_bg_ncg.bin read into a new block of the
 * current heap kept in `characters`. Returns 1 when the file opened, the block was had, the
 * read worked and the file closed.
 * QUIRK: the block is asked for, and the file closed, even when it did not open (so too in
 * the two loaders after this one). */
int TalkBox_LoadCharacters(TalkBox *box, void *file)
{
    int opened = FS_OpenFile(file, data_020df0d0);
    box->characters = Heap_AllocCurrentBack(TALK_BOX_CHARACTERS_SIZE);
    int read = 0;
    if (box->characters != NULL) {
        read = FS_ReadFile(file, box->characters, TALK_BOX_CHARACTERS_SIZE) != TALK_BOX_FS_READ_FAILED;
    }
    int closed = FS_CloseFile(file);
    return opened && read && closed && box->characters != NULL;
}
CLEAN_AS(func_02068fa0, TalkBox_LoadCharacters)

/* func_02069004: the first 0x180 bytes of a_mes_bg_ncl.bin read into `palette`, likewise. */
int TalkBox_LoadPalette(TalkBox *box, void *file)
{
    int opened = FS_OpenFile(file, data_020df0e8);
    box->palette = Heap_AllocCurrentBack(TALK_BOX_PALETTE_SIZE);
    int read = 0;
    if (box->palette != NULL) {
        read = FS_ReadFile(file, box->palette, TALK_BOX_PALETTE_SIZE) != TALK_BOX_FS_READ_FAILED;
    }
    int closed = FS_CloseFile(file);
    return opened && read && closed && box->palette != NULL;
}
CLEAN_AS(func_02069004, TalkBox_LoadPalette)

/* func_02069068: the first 0x800 bytes of the screen with the name plate (a_mes0a_bg_nsc.bin)
 * or without it (a_mes0b_bg_nsc.bin) read into `screen`, likewise. */
int TalkBox_LoadScreen(TalkBox *box, void *file, int with_plate)
{
    const char *path = with_plate ? data_020df100 : data_020df11c;
    int opened = FS_OpenFile(file, path);
    box->screen = Heap_AllocCurrentBack(TALK_BOX_SCREEN_SIZE);
    int read = 0;
    if (box->screen != NULL) {
        read = FS_ReadFile(file, box->screen, TALK_BOX_SCREEN_SIZE) != TALK_BOX_FS_READ_FAILED;
    }
    int closed = FS_CloseFile(file);
    return opened && read && closed && box->screen != NULL;
}
CLEAN_AS(func_02069068, TalkBox_LoadScreen)

/* func_020690d8: the arrow drawn, then the spinner. */
void TalkBox_Draw(TalkBox *box)
{
    TalkBox_DrawArrow(box);
    TalkBox_DrawSpinner(box);
}
CLEAN_AS(func_020690d8, TalkBox_Draw)

/* func_020690ec: the arrow stepped, then the spinner. */
void TalkBox_Update(TalkBox *box)
{
    TalkBox_UpdateArrow(box);
    TalkBox_UpdateSpinner(box);
}
CLEAN_AS(func_020690ec, TalkBox_Update)

/* func_02069100: the destructor: the spinner finished, the files freed, then the spinner's and
 * the arrow's destructors. */
TalkBox *TalkBox_Destruct(TalkBox *box)
{
    TalkSpinner_Finish(&box->spinner);
    TalkBox_FreeFiles(box);
    TalkSpinner_Destruct(&box->spinner);
    CellPairSprite_Destruct(&box->arrow);
    return box;
}
CLEAN_AS(func_02069100, TalkBox_Destruct)

/* func_02069128: the constructor: no files, the arrow on the main screen in its alternate
 * set of animations, the spinner made, the box at (0, 0). */
TalkBox *TalkBox_Construct(TalkBox *box)
{
    box->screen = NULL;
    box->palette = NULL;
    box->characters = NULL;
    CellPairSprite_Construct(&box->arrow, 1);
    TalkSpinner_Construct(&box->spinner);
    box->x = 0;
    box->y = 0;
    box->spinner_hold = 0;
    CellPairSprite_UseAlternate(&box->arrow);
    TalkSpinner_Init(&box->spinner);
    return box;
}
CLEAN_AS(func_02069128, TalkBox_Construct)
