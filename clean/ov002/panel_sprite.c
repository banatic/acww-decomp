/* The button panel's sprites (panel_sprite.h). */
#include "panel_sprite.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/oam_buffer.h"

static_assert(offsetof(PanelSprite, cells) == 0x70 && offsetof(PanelSprite, message) == 0x77, "panel sprite");
static_assert(offsetof(PanelSprite, flags) == 0x78 && sizeof(PanelSprite) == 0x7c, "panel sprite");

extern const u8 data_ov002_0220bd18[]; /* the sprite's vtable */
extern const u8 data_ov002_0220ba54[]; /* by press step: how far the button has sunk, 0, 2, 3 */
/* Draws one cell (main's sprite drawing, the first argument 1 as for the sub screen). */
extern void func_02088df8(int a0, const PanelCell *cell, int x, int y, int palette, int priority, int scale_x, int scale_y,
                          int rotation, int a9, int a10, int a11);

/* The screen's centre, where (0, 0) of PanelSprite_Draw is. */
#define CENTER_X 0x80
#define CENTER_Y 0x60
/* How far the shadow lies under the button. */
#define SHADOW_OFFSET 3
/* The style of the text box. */
#define TEXT_STYLE 8
#define SCALE_ONE 0x1000

static TextLabel *label_of(PanelSprite *sprite)
{
    return &sprite->label;
}

/* func_ov002_0220b12c */
int PanelSprite_HasFlag4(PanelSprite *sprite)
{
    return PanelSprite_HasFlags(sprite, PANEL_SPRITE_PALETTE2);
}
CLEAN_AS(func_ov002_0220b12c, PanelSprite_HasFlag4)

/* func_ov002_0220b138 */
void PanelSprite_ClearFlag4(PanelSprite *sprite)
{
    PanelSprite_ClearFlags(sprite, PANEL_SPRITE_PALETTE2);
}
CLEAN_AS(func_ov002_0220b138, PanelSprite_ClearFlag4)

/* func_ov002_0220b144 */
void PanelSprite_SetFlag4(PanelSprite *sprite)
{
    PanelSprite_SetFlags(sprite, PANEL_SPRITE_PALETTE2);
}
CLEAN_AS(func_ov002_0220b144, PanelSprite_SetFlag4)

/* func_ov002_0220b150 */
void PanelSprite_ClearFlag2(PanelSprite *sprite)
{
    PanelSprite_ClearFlags(sprite, PANEL_SPRITE_FLAG2);
}
CLEAN_AS(func_ov002_0220b150, PanelSprite_ClearFlag2)

/* func_ov002_0220b15c */
void PanelSprite_SetFlag2(PanelSprite *sprite)
{
    PanelSprite_SetFlags(sprite, PANEL_SPRITE_FLAG2);
}
CLEAN_AS(func_ov002_0220b15c, PanelSprite_SetFlag2)

/* func_ov002_0220b168: one step of a press: the first turns the text to its pressed colour;
 * each moves the button one step down. Returns 1 while it moved, 0 once it is down. */
int PanelSprite_StepPress(PanelSprite *sprite)
{
    if (sprite->press_step == 0) {
        PanelSprite_ShowText(sprite, PANEL_TEXT_COLOR_PRESSED, 0);
    }
    if (sprite->press_step + 1 < PANEL_PRESS_STEPS) {
        sprite->press_step++;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov002_0220b168, PanelSprite_StepPress)

/* func_ov002_0220b1a4: draws the button at (x, y) from the screen's centre, sunk as deep as the
 * press has gone: the cells (in palette 2 with PANEL_SPRITE_PALETTE2), once more with
 * PANEL_SPRITE_FLAG2, then the shadow unless the sprite is flat or the button is down. */
void PanelSprite_Draw(PanelSprite *sprite, int x, int y, int priority)
{
    int depth = PanelSprite_PressDepth(sprite);
    int palette = -1;
    if (PanelSprite_HasFlags(sprite, PANEL_SPRITE_PALETTE2)) {
        palette = 2;
    }
    int button_y = y + CENTER_Y + depth;
    int button_x = x + CENTER_X + depth;

    OamBuffer_DrawCell(1, (const OamEntry *) (void *) sprite->cells, button_x, button_y, palette, priority, SCALE_ONE,
                       SCALE_ONE, 0, -1, 0, 0);
    if (PanelSprite_HasFlags(sprite, PANEL_SPRITE_FLAG2)) {
        OamBuffer_DrawCell(1, (const OamEntry *) (void *) sprite->cells, button_x, button_y, -1, priority, SCALE_ONE,
                           SCALE_ONE, 0, 2, 0, 0);
    }
    if (!PanelSprite_HasFlags(sprite, PANEL_SPRITE_NO_SHADOW) && sprite->press_step + 1 != PANEL_PRESS_STEPS) {
        const PanelCell *shadow = &sprite->cells[sprite->shadow_cell];
        OamBuffer_DrawCell(1, (const OamEntry *) (void *) shadow, x + CENTER_X + SHADOW_OFFSET, y + CENTER_Y + SHADOW_OFFSET,
                           1, priority, SCALE_ONE, SCALE_ONE, 0, -1, 0, 0);
    }
}
CLEAN_AS(func_ov002_0220b1a4, PanelSprite_Draw)

/* func_ov002_0220b280: how many pixels the press has sunk the button, from the game's table
 * (read at any step, as the original does). */
int PanelSprite_PressDepth(PanelSprite *sprite)
{
    return data_ov002_0220ba54[sprite->press_step];
}
CLEAN_AS(func_ov002_0220b280, PanelSprite_PressDepth)

/* func_ov002_0220b290: frees the text's box. */
void PanelSprite_CloseText(PanelSprite *sprite)
{
    TextLabel_CloseBox(label_of(sprite));
}
CLEAN_AS(func_ov002_0220b290, PanelSprite_CloseText)

/* func_ov002_0220b29c */
void PanelSprite_ClearFlags(PanelSprite *sprite, int mask)
{
    sprite->flags = (u8) (sprite->flags & ~mask);
}
CLEAN_AS(func_ov002_0220b29c, PanelSprite_ClearFlags)

/* func_ov002_0220b2ac */
void PanelSprite_SetFlags(PanelSprite *sprite, int mask)
{
    sprite->flags = (u8) (sprite->flags | mask);
}
CLEAN_AS(func_ov002_0220b2ac, PanelSprite_SetFlags)

/* func_ov002_0220b2bc: whether any of `mask` is set. */
int PanelSprite_HasFlags(PanelSprite *sprite, int mask)
{
    return (sprite->flags & mask) != 0;
}
CLEAN_AS(func_ov002_0220b2bc, PanelSprite_HasFlags)

/* func_ov002_0220b2d0: writes the message into the first cell's tiles, centred, in the two
 * colours given (the box's colours 0x38 and 0x39). */
void PanelSprite_ShowText(PanelSprite *sprite, int color_38, int color_39)
{
    TextLabel_LoadMenuMessage((int) (uintptr_t) label_of(sprite), (char) sprite->message);
    TextLabel_OpenStyledBox2(label_of(sprite), TEXT_STYLE, sprite->cells[0].attr2 & 0x3ff, sprite->text_cells, (u8) color_38,
                             (u8) color_39, 0);
    TextLabel_Show(label_of(sprite), 1, 0);
}
CLEAN_AS(func_ov002_0220b2d0, PanelSprite_ShowText)

/* func_ov002_0220b318: shows `message` on the button up and without its shadow. */
void PanelSprite_ShowFlat(PanelSprite *sprite, unsigned char message)
{
    PanelSprite_SetMessage(sprite, message);
    sprite->press_step = 0;
    PanelSprite_SetFlags(sprite, PANEL_SPRITE_NO_SHADOW);
}
CLEAN_AS(func_ov002_0220b318, PanelSprite_ShowFlat)

/* func_ov002_0220b338: shows `message` on the button up, with its shadow. */
void PanelSprite_Show(PanelSprite *sprite, int message)
{
    PanelSprite_SetMessage(sprite, message);
    sprite->press_step = 0;
    PanelSprite_ClearFlags(sprite, PANEL_SPRITE_NO_SHADOW);
}
CLEAN_AS(func_ov002_0220b338, PanelSprite_Show)

/* func_ov002_0220b358: the message (kept as a byte), written in the normal colour. */
void PanelSprite_SetMessage(PanelSprite *sprite, int message)
{
    sprite->message = (u8) message;
    PanelSprite_ShowText(sprite, PANEL_TEXT_COLOR, 0);
}
CLEAN_AS(func_ov002_0220b358, PanelSprite_SetMessage)

/* func_ov002_0220b36c: the cells to draw, the text's width and the shadow's cell. */
void PanelSprite_SetCells(PanelSprite *sprite, const PanelCell *cells, u8 text_cells, u8 shadow_cell)
{
    sprite->cells = cells;
    sprite->text_cells = text_cells;
    sprite->shadow_cell = shadow_cell;
}
CLEAN_AS(func_ov002_0220b36c, PanelSprite_SetCells)

/* func_ov002_0220b37c (vtable entry 1): destructs and frees the sprite. */
PanelSprite *PanelSprite_Delete(PanelSprite *sprite)
{
    sprite->vtable = data_ov002_0220bd18;
    TextLabel_CloseBox(label_of(sprite));
    TextLabel_Destruct(label_of(sprite));
    Heap_OperatorDeleteB(sprite);
    return sprite;
}
CLEAN_AS(func_ov002_0220b37c, PanelSprite_Delete)

/* func_ov002_0220b3a4 (vtable entry 0) */
PanelSprite *PanelSprite_Destroy(PanelSprite *sprite)
{
    sprite->vtable = data_ov002_0220bd18;
    TextLabel_CloseBox(label_of(sprite));
    TextLabel_Destruct(label_of(sprite));
    return sprite;
}
CLEAN_AS(func_ov002_0220b3a4, PanelSprite_Destroy)

/* func_ov002_0220b3c4: an empty label, no cells, up, no flags. The other bytes are left as
 * they were. */
PanelSprite *PanelSprite_Construct(PanelSprite *sprite)
{
    sprite->vtable = data_ov002_0220bd18;
    TextLabel_Construct(label_of(sprite));
    sprite->cells = NULL;
    sprite->press_step = 0;
    sprite->flags = 0;
    return sprite;
}
CLEAN_AS(func_ov002_0220b3c4, PanelSprite_Construct)
