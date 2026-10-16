/* The background of a message window kind (class vtable 0x020e3fb4, constructor func_020ac9a4):
 * a BG screen of 0x800 bytes read from /a_mes/a_mes1a_bg_nsc.bin into the current heap, five
 * background palette colours uploaded at colour 0x41 when marked (func_020ac3f8) and the
 * window's scrolling. Two classes derive from it (vtables 0x020e3fe4 and 0x020e3ffc); both hold
 * a MesBgMarker at 0x20, and the first also a MesBgSlider at 0xe4.
 *
 * A MesBgMarker (vtable 0x020e4030) is main's sprite (func_0208e8d4, kind 1) placed by the
 * window next to its choices.
 *
 * A MesBgSlider (vtable 0x020e4014) is a knob on a 32-pixel track, drawn at the slider's place
 * with the first cell of the table data_020d5b3c points to, and an indicator of two cell
 * animations (class vtable 0x020e2330, constructor func_0208ec40) placed at (6, the knob's
 * offset) from it. The indicator's state picks its animations (func_0208e95c): state 0 hides
 * the whole slider, 1 shows it still, 2 and 3 play the animations (func_0208e9e0 measures how
 * far they move, one way in state 2 and the other in state 3). */
#ifndef CLEAN_MAIN_MES_BG_H
#define CLEAN_MAIN_MES_BG_H

#include "types.h"

#define MES_BG_SCREEN_SIZE 0x800
#define MES_BG_COLOURS 5

/* The slider's level runs from 0 (the knob at the bottom of the track) to 0x1000 (the top). */
#define MES_BG_SLIDER_LEVEL_TOP 0x1000
#define MES_BG_SLIDER_TRACK 32 /* pixels */

typedef struct MesBg {
    const void *vtable;          /* data_020e3fb4, or a derived class's */
    u8 *screen;                  /* 0x04: MES_BG_SCREEN_SIZE bytes from the heap, or NULL */
    u16 colours[MES_BG_COLOURS]; /* 0x08 */
    u8 colours_dirty;            /* 0x12: upload `colours` on the next frame */
    u8 pad_13;
    s32 columns;   /* 0x14: the window's width in 8-pixel columns */
    s16 scroll_x;  /* 0x18 */
    s16 scroll_y;  /* 0x1a */
    s16 lines_top; /* 0x1c: where the first 16-pixel line starts */
    s16 lines;     /* 0x1e */
} MesBg;

/* The functions of main's sprite classes, as far as these classes use them. */
typedef struct MesBgSpriteVtable {
    const void *destruct[2];
    void (*draw)(void *sprite);                    /* 0x08 */
    void (*update)(void *sprite);                  /* 0x0c */
    void (*set_place)(void *sprite, int x, int y); /* 0x10 */
} MesBgSpriteVtable;

/* main's sprite with a cell animation (constructor func_0208e8d4, destructor func_0208e7f0) */
typedef struct MesBgMarker {
    const MesBgSpriteVtable *vtable; /* data_020e4030 */
    u8 sprite_04[0x24];
    s32 unk_28; /* 0x28: -1 from main's constructor, 0 here */
    u8 sprite_2c[0x20];
} MesBgMarker;

/* The cell animation pair of main's class 0x020e2330 (func_0208ec40) */
typedef struct MesBgIndicator {
    const MesBgSpriteVtable *vtable; /* data_020e2330 */
    s32 x;                           /* 0x04 */
    s32 y;                           /* 0x08 */
    s32 offset_x;                    /* 0x0c: drawn at the place plus the offset (func_0208ea70) */
    s32 offset_y;                    /* 0x10 */
    u8 anims[2][0x14];               /* 0x14 */
    u32 state;                       /* 0x3c: func_0208e95c, read by func_0208e958 */
    u8 kind;                         /* 0x40 */
    u8 pad_41[3];
    s32 unk_44; /* 0x44: func_0208ea6c */
} MesBgIndicator;

typedef struct MesBgSlider {
    const MesBgSpriteVtable *vtable; /* data_020e4014 */
    s32 x;                           /* 0x04: the place (func_0208aef4, 0x80 + x) */
    s32 y;                           /* 0x08: (0x60 + y) */
    fx32 level;                      /* 0x0c: 0 to MES_BG_SLIDER_LEVEL_TOP */
    MesBgIndicator indicator;        /* 0x10 */
} MesBgSlider;

int MesBg_LoadScreen(MesBg *bg, void *file);
MesBg *MesBg_DestructBase(MesBg *bg);
MesBg *MesBg_DestructDelete(MesBg *bg);
MesBg *MesBg_Destruct(MesBg *bg);
void MesBg_Construct(MesBg *bg);
MesBgMarker *MesBgMarker_DestructDelete(MesBgMarker *marker);
MesBgMarker *MesBgMarker_Destruct(MesBgMarker *marker);
MesBgMarker *MesBgMarker_Construct(MesBgMarker *marker);
void MesBgSlider_PlayIndicatorB(MesBgSlider *slider);
void MesBgSlider_PlayIndicatorA(MesBgSlider *slider);
void MesBgSlider_Hide(MesBgSlider *slider);
void MesBgSlider_ShowStill(MesBgSlider *slider);
int MesBgSlider_IndicatorDone(MesBgSlider *slider);
void MesBgSlider_IndicatorMove(MesBgSlider *slider, int *dx, int *dy);
int MesBgSlider_TrackTop(MesBgSlider *slider);
int MesBgSlider_TrackBottom(MesBgSlider *slider);
int MesBgSlider_KnobY(MesBgSlider *slider);
int MesBgSlider_TrackX(MesBgSlider *slider);
int MesBgSlider_LevelToY(MesBgSlider *slider);
void MesBgSlider_SetLevel(MesBgSlider *slider, fx32 level);
void MesBgSlider_SetPlace(MesBgSlider *slider, int x, int y);
void MesBgSlider_Update(MesBgSlider *slider);
void MesBgSlider_Draw(MesBgSlider *slider);
MesBgSlider *MesBgSlider_DestructDelete(MesBgSlider *slider);
MesBgSlider *MesBgSlider_Destruct(MesBgSlider *slider);
MesBgSlider *MesBgSlider_Construct(MesBgSlider *slider);

#endif
