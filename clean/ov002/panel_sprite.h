/* A button sprite of the menu scenes' button panel (button_panel.h): a class of ov002's
 * (vtable 0x0220bd18, constructor func_ov002_0220b3c4, destructor func_ov002_0220b3a4) that
 * draws a few sprite cells on the sub screen with a message of "2d_menu" written into their
 * tiles by a text label.
 *
 * The cells form the button; one of them, `shadow_cell`, is drawn again 3 pixels lower and to
 * the right in palette 1, under the button. Pressing the button sinks it by 2, then 3 pixels
 * (the table data_ov002_0220ba54) until it lies on its shadow, which is then no longer drawn;
 * the text turns from colour 15 to colour 14 as the press starts. */
#ifndef CLEAN_OV002_PANEL_SPRITE_H
#define CLEAN_OV002_PANEL_SPRITE_H

#include "main/text_label.h"
#include "types.h"

/* One sprite cell: the three OAM attributes main's func_02088df8 draws from. */
typedef struct PanelCell {
    u16 attr0;
    u16 attr1;
    u16 attr2; /* bits 0-9: the first tile */
    u16 pad;
} PanelCell;

/* The bits of `flags`. */
enum PanelSpriteFlag {
    PANEL_SPRITE_NO_SHADOW = 1, /* set by PanelSprite_ShowFlat, cleared by PanelSprite_Show */
    PANEL_SPRITE_FLAG2 = 2,     /* the cells are drawn a second time, func_02088df8's 10th argument 2 */
    PANEL_SPRITE_PALETTE2 = 4   /* the cells are drawn in palette 2 */
};

/* The text's colours, the two entries func_ov002_0220af94 loads. */
#define PANEL_TEXT_COLOR 0xf
#define PANEL_TEXT_COLOR_PRESSED 0xe

/* The press's steps: up, sinking, down. */
#define PANEL_PRESS_STEPS 3

typedef struct PanelSprite {
    const void *vtable;     /* data_ov002_0220bd18 */
    TextLabel label;        /* 0x04 */
    const PanelCell *cells; /* 0x70 */
    u8 text_cells;          /* 0x74: the width of the text, in 8-pixel cells */
    u8 press_step;          /* 0x75: 0 up, 1 sinking, 2 down */
    u8 shadow_cell;         /* 0x76: the cell drawn as the shadow */
    u8 message;             /* 0x77: of "2d_menu" */
    u8 flags;               /* 0x78: PanelSpriteFlag */
    u8 pad_79[3];
} PanelSprite;

int PanelSprite_HasFlag4(PanelSprite *sprite);
void PanelSprite_ClearFlag4(PanelSprite *sprite);
void PanelSprite_SetFlag4(PanelSprite *sprite);
void PanelSprite_ClearFlag2(PanelSprite *sprite);
void PanelSprite_SetFlag2(PanelSprite *sprite);
int PanelSprite_StepPress(PanelSprite *sprite);
void PanelSprite_Draw(PanelSprite *sprite, int x, int y, int priority);
int PanelSprite_PressDepth(PanelSprite *sprite);
void PanelSprite_CloseText(PanelSprite *sprite);
void PanelSprite_ClearFlags(PanelSprite *sprite, int mask);
void PanelSprite_SetFlags(PanelSprite *sprite, int mask);
int PanelSprite_HasFlags(PanelSprite *sprite, int mask);
void PanelSprite_ShowText(PanelSprite *sprite, int color_38, int color_39);
void PanelSprite_ShowFlat(PanelSprite *sprite, unsigned char message);
void PanelSprite_Show(PanelSprite *sprite, int message);
void PanelSprite_SetMessage(PanelSprite *sprite, int message);
void PanelSprite_SetCells(PanelSprite *sprite, const PanelCell *cells, u8 text_cells, u8 shadow_cell);
PanelSprite *PanelSprite_Delete(PanelSprite *sprite);
PanelSprite *PanelSprite_Destroy(PanelSprite *sprite);
PanelSprite *PanelSprite_Construct(PanelSprite *sprite);

#endif
