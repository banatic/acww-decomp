/* main's labelled sprite (label_sprite.h). */
#include "label_sprite.h"

#include "autoload_2/heap.h" /* Heap_OperatorDeleteB */
#include "cell_anim.h"
#include "clean.h"
#include "oam_buffer.h" /* OamBuffer_DrawCell */
#include "text_draw.h"  /* TextDraw_Center, TextDraw_RequestDraw */

static_assert(offsetof(LabelSpriteText, chars) == 0x12 && sizeof(LabelSpriteText) == 0x24, "LabelSpriteText");
static_assert(offsetof(LabelSprite, palette) == 0x14 && offsetof(LabelSprite, first) == 0x1c, "LabelSprite");
static_assert(offsetof(LabelSprite, second) == 0x30 && offsetof(LabelSprite, state) == 0x44, "LabelSprite");
static_assert(offsetof(LabelSprite, text) == 0x4c && offsetof(LabelSprite, colour) == 0x70, "LabelSprite");
static_assert(offsetof(LabelSprite, colour_dirty) == 0x75 && sizeof(LabelSprite) == 0x78, "LabelSprite");

/* The vtables of the sprite and of its text. */
extern const u32 data_020e23a0[];
extern const TextVtable data_020e2388;

/* The animations by state: the first's entry of data_020d6fcc is the kind's first entry plus
 * the state's (the second's is the next), and whether they hold their last frame (all do). */
extern const CellAnimData data_020d6fcc[];
extern const u8 data_020d0b74[];  /* by kind */
extern const int data_020d0b94[]; /* by state */
extern const int data_020d0b84[]; /* by state */

/* By kind: the text box's first VRAM tile, and the OBJ colour (of palette 0) its text is drawn
 * in. */
extern const int data_020d0b7c[];
extern const u8 data_020d0b78[];

/* The colour last loaded into each kind's OBJ colour. */
extern u16 data_021d361c[];

extern void DC_FlushRange(const void *start, u32 size);
extern void GX_LoadOBJPltt(const void *src, u32 offset, u32 size);
extern void GXS_LoadOBJPltt(const void *src, u32 offset, u32 size);

/* The text's colour, normally and while pressed. */
#define LABEL_SPRITE_COLOUR 0x50c0
#define LABEL_SPRITE_COLOUR_PRESSED 0x7d5f
#define LABEL_SPRITE_COLOUR_SIZE 2

/* The text box: 6 tiles by 2 of OBJ tiles, its text centred, on a clear background. */
#define LABEL_SPRITE_BOX_CELLS 6
#define LABEL_SPRITE_BOX_ROWS 2
#define LABEL_SPRITE_BOX_LAYER_OBJECTS 4
#define LABEL_SPRITE_BOX_BACKGROUND 0

#define LABEL_SPRITE_FX_ONE 0x1000
#define LABEL_SPRITE_CURRENT_FRAME (-1)
#define LABEL_SPRITE_OBJ_MODE_WINDOW 2

/* The address of the text's characters, through its vtable (slot 3). */
static u32 label_sprite_text_chars(LabelSprite *sprite)
{
    return ((u32 (*)(LabelSpriteText *))(uintptr_t) sprite->text.vtable->buffer)(&sprite->text);
}

/* func_0208ef7c: the text's colour loaded into the OBJ colour of the sprite's kind on both
 * engines, when it changed or differs from what was last loaded there.
 * HW: the colour is flushed from the data cache before it is loaded. */
void LabelSprite_UploadColour(LabelSprite *sprite)
{
    if (sprite->colour_dirty == 0 && sprite->colour != data_021d361c[sprite->kind]) {
        sprite->colour_dirty = 1;
    }
    if (sprite->colour_dirty == 0) {
        return;
    }
    u32 offset = (u32) data_020d0b78[sprite->kind] * LABEL_SPRITE_COLOUR_SIZE;
    DC_FlushRange(&sprite->colour, LABEL_SPRITE_COLOUR_SIZE);
    GX_LoadOBJPltt(&sprite->colour, offset, LABEL_SPRITE_COLOUR_SIZE);
    GXS_LoadOBJPltt(&sprite->colour, offset, LABEL_SPRITE_COLOUR_SIZE);
    data_021d361c[sprite->kind] = sprite->colour;
    sprite->colour_dirty = 0;
}
CLEAN_AS(func_0208ef7c, LabelSprite_UploadColour)

/* func_0208effc: the text box freed, if there is one. */
void LabelSprite_FreeBox(LabelSprite *sprite)
{
    if (sprite->box != NULL) {
        LabelBox_Free(sprite->box);
        sprite->box = NULL;
    }
}
CLEAN_AS(func_0208effc, LabelSprite_FreeBox)

/* func_0208f014: the text box made, unless there is one, and the text handed to it, centred,
 * to be drawn in the kind's colour (on the main screen's OBJ tiles when the sprite is on the
 * main screen); the colour loaded at the next draw. Nothing when the boxes' heap is full. */
void LabelSprite_OpenBox(LabelSprite *sprite)
{
    if (sprite->box != NULL) {
        return;
    }
    sprite->box = LabelBox_NewInVram(data_020d0b7c[sprite->kind], LABEL_SPRITE_BOX_CELLS, LABEL_SPRITE_BOX_ROWS);
    if (sprite->box == NULL) {
        return;
    }
    sprite->box->base.layer = LABEL_SPRITE_BOX_LAYER_OBJECTS;
    sprite->box->base.text = (const char *) (uintptr_t) label_sprite_text_chars(sprite);
    if (sprite->on_main != 0) {
        sprite->box->base.screens = TEXT_DRAW_TO_MAIN;
    }
    sprite->box->base.rows_full_width = 1;
    TextDraw_Center(&sprite->box->base);
    sprite->box->base.background = LABEL_SPRITE_BOX_BACKGROUND;
    sprite->box->base.color = data_020d0b78[sprite->kind];
    TextDraw_RequestDraw(&sprite->box->base);
    sprite->colour_dirty = 1;
}
CLEAN_AS(func_0208f014, LabelSprite_OpenBox)

/* func_0208f098: whether both animations have ended (the second is asked only when the first
 * has). */
int LabelSprite_IsDone(LabelSprite *sprite)
{
    return CellAnim_IsDone(&sprite->first) != 0 && CellAnim_IsDone(&sprite->second) != 0;
}
CLEAN_AS(func_0208f098, LabelSprite_IsDone)

/* func_0208f0c0 */
int LabelSprite_State(LabelSprite *sprite)
{
    return sprite->state;
}
CLEAN_AS(func_0208f0c0, LabelSprite_State)

/* func_0208f0c4: the state's animations started, stopped (speed 0) in the still state. Hidden,
 * the text box is freed; otherwise it is made and the text's colour set for the state.
 * REQUIRES: `state` is 0-3 and the kind 0 or 1 (the ROM reads its tables unchecked). */
void LabelSprite_SetState(LabelSprite *sprite, int state)
{
    int entry = data_020d0b74[sprite->kind] + data_020d0b94[state];
    int hold = data_020d0b84[state];

    sprite->state = state;

    CellAnim_SetData(&sprite->first, &data_020d6fcc[entry]);
    CellAnim_SetHold(&sprite->first, hold);
    CellAnim_Restart(&sprite->first);

    CellAnim_SetData(&sprite->second, &data_020d6fcc[entry + 1]);
    CellAnim_SetHold(&sprite->second, hold);
    CellAnim_Restart(&sprite->second);

    if (state == LABEL_SPRITE_STILL) {
        CellAnim_SetSpeed(&sprite->first, 0);
        CellAnim_SetSpeed(&sprite->second, 0);
    }
    if (state == LABEL_SPRITE_HIDDEN) {
        LabelSprite_FreeBox(sprite);
        return;
    }
    LabelSprite_OpenBox(sprite);
    sprite->colour = sprite->state == LABEL_SPRITE_PRESSED ? LABEL_SPRITE_COLOUR_PRESSED : LABEL_SPRITE_COLOUR;
    sprite->colour_dirty = 1;
}
CLEAN_AS(func_0208f0c4, LabelSprite_SetState)

/* func_0208f184: how far the first animation's offset has moved: from its first frame to the
 * current one in state 2, back from the current one to the first in state 3, else 0. */
void LabelSprite_Travel(LabelSprite *sprite, int *dx, int *dy)
{
    int x = 0;
    int y = 0;

    if (sprite->state == LABEL_SPRITE_PRESSED) {
        int current_x = CellAnim_FrameX(&sprite->first, LABEL_SPRITE_CURRENT_FRAME);
        x = current_x - CellAnim_FrameX(&sprite->first, 0);
        int current_y = CellAnim_FrameY(&sprite->first, LABEL_SPRITE_CURRENT_FRAME);
        y = current_y - CellAnim_FrameY(&sprite->first, 0);
    } else if (sprite->state == LABEL_SPRITE_PLAY_B) {
        int first_x = CellAnim_FrameX(&sprite->first, 0);
        x = first_x - CellAnim_FrameX(&sprite->first, LABEL_SPRITE_CURRENT_FRAME);
        int first_y = CellAnim_FrameY(&sprite->first, 0);
        y = first_y - CellAnim_FrameY(&sprite->first, LABEL_SPRITE_CURRENT_FRAME);
    }
    *dx = x;
    *dy = y;
}
CLEAN_AS(func_0208f184, LabelSprite_Travel)

/* func_0208f210 */
void LabelSprite_SetOffset(LabelSprite *sprite, int x, int y)
{
    sprite->offset_x = x;
    sprite->offset_y = y;
}
CLEAN_AS(func_0208f210, LabelSprite_SetOffset)

/* func_0208f218: the text copied in; when the box is made, handed to it again, centred and
 * redrawn, and the colour loaded at the next draw. */
void LabelSprite_SetText(LabelSprite *sprite, TextBase *text)
{
    TextBase_Copy((TextBase *) &sprite->text, text);
    LabelBox *box = sprite->box;
    if (box == NULL) {
        return;
    }
    box->base.text = (const char *) (uintptr_t) label_sprite_text_chars(sprite);
    TextDraw_Center(&sprite->box->base);
    TextDraw_RequestDraw(&sprite->box->base);
    sprite->colour_dirty = 1;
}
CLEAN_AS(func_0208f218, LabelSprite_SetText)

/* func_0208f250 */
void LabelSprite_ShowSecond(LabelSprite *sprite)
{
    sprite->hide_second = 0;
}
CLEAN_AS(func_0208f250, LabelSprite_ShowSecond)

/* func_0208f258 */
void LabelSprite_HideSecond(LabelSprite *sprite)
{
    sprite->hide_second = 1;
}
CLEAN_AS(func_0208f258, LabelSprite_HideSecond)

/* func_0208f260 */
void LabelSprite_SetWindow(LabelSprite *sprite)
{
    sprite->window = 1;
}
CLEAN_AS(func_0208f260, LabelSprite_SetWindow)

/* func_0208f268 (vtable slot 3): both animations advanced, unless hidden. */
void LabelSprite_Update(LabelSprite *sprite)
{
    if (sprite->state == LABEL_SPRITE_HIDDEN) {
        return;
    }
    CellAnim_Advance(&sprite->first);
    CellAnim_Advance(&sprite->second);
}
CLEAN_AS(func_0208f268, LabelSprite_Update)

static void label_sprite_draw_cell(LabelSprite *sprite, const OamEntry *cell, u32 x, u32 y, int palette, int obj_mode)
{
    int screen = sprite->on_main != 0 ? OAM_BUFFER_SCREEN_MAIN : OAM_BUFFER_SCREEN_SUB;
    OamBuffer_DrawCell(screen, cell, (int) x, (int) y, palette, -1, LABEL_SPRITE_FX_ONE, LABEL_SPRITE_FX_ONE, 0, obj_mode, 0,
                       0);
}

/* func_0208f288 (vtable slot 2): unless hidden, both cells drawn at the place plus the offset
 * and each frame's own offset (the second unless hidden by `hide_second`; the first in its
 * palette), on the main or the sub screen, then again as OBJ window when `window` is set.
 * Then, hidden or not, the text's colour loaded when it changed. */
void LabelSprite_Draw(LabelSprite *sprite)
{
    if (sprite->state != LABEL_SPRITE_HIDDEN) {
        const OamEntry *cell = CellAnim_Cell(&sprite->first);
        const OamEntry *cell2 = CellAnim_Cell(&sprite->second);
        int frame_x = CellAnim_FrameX(&sprite->first, LABEL_SPRITE_CURRENT_FRAME);
        int frame_y = CellAnim_FrameY(&sprite->first, LABEL_SPRITE_CURRENT_FRAME);
        int frame2_x = CellAnim_FrameX(&sprite->second, LABEL_SPRITE_CURRENT_FRAME);
        int frame2_y = CellAnim_FrameY(&sprite->second, LABEL_SPRITE_CURRENT_FRAME);
        u32 x = (u32) ScreenSprite_X(&sprite->base) + (u32) sprite->offset_x;
        u32 y = (u32) ScreenSprite_Y(&sprite->base) + (u32) sprite->offset_y;
        u32 x1 = x + (u32) frame_x;
        u32 y1 = y + (u32) frame_y;
        u32 x2 = x + (u32) frame2_x;
        u32 y2 = y + (u32) frame2_y;
        int show_second = sprite->hide_second == 0;

        label_sprite_draw_cell(sprite, cell, x1, y1, sprite->palette, -1);
        if (show_second) {
            label_sprite_draw_cell(sprite, cell2, x2, y2, -1, -1);
        }
        if (sprite->window != 0) {
            label_sprite_draw_cell(sprite, cell, x1, y1, -1, LABEL_SPRITE_OBJ_MODE_WINDOW);
            if (show_second) {
                label_sprite_draw_cell(sprite, cell2, x2, y2, -1, LABEL_SPRITE_OBJ_MODE_WINDOW);
            }
        }
    }
    LabelSprite_UploadColour(sprite);
}
CLEAN_AS(func_0208f288, LabelSprite_Draw)

static void label_sprite_destruct(LabelSprite *sprite)
{
    sprite->base.vtable = data_020e23a0;
    LabelSprite_FreeBox(sprite);
    LabelSprite_TextDestruct(&sprite->text);
    CellAnim_Destruct(&sprite->second);
    CellAnim_Destruct(&sprite->first);
    ScreenSprite_DestructBase(&sprite->base);
}

/* func_0208f46c: the destructor, a second copy of LabelSprite_Destruct (the label buttons'). */
LabelSprite *LabelSprite_DestructCopy(LabelSprite *sprite)
{
    label_sprite_destruct(sprite);
    return sprite;
}
CLEAN_AS(func_0208f46c, LabelSprite_DestructCopy)

/* func_0208f4a4 (vtable slot 1): destructed and freed. */
LabelSprite *LabelSprite_Delete(LabelSprite *sprite)
{
    label_sprite_destruct(sprite);
    Heap_OperatorDeleteB(sprite);
    return sprite;
}
CLEAN_AS(func_0208f4a4, LabelSprite_Delete)

/* func_0208f4e0 (vtable slot 0): the destructor. */
LabelSprite *LabelSprite_Destruct(LabelSprite *sprite)
{
    label_sprite_destruct(sprite);
    return sprite;
}
CLEAN_AS(func_0208f4e0, LabelSprite_Destruct)

static void label_sprite_construct(LabelSprite *sprite, u8 on_main, int kind)
{
    ScreenSprite_Construct(&sprite->base);
    sprite->base.vtable = data_020e23a0;
    sprite->offset_x = 0;
    sprite->offset_y = 0;
    sprite->palette = -1;
    sprite->kind = kind;
    CellAnim_Construct(&sprite->first);
    CellAnim_Construct(&sprite->second);
    sprite->state = LABEL_SPRITE_HIDDEN;
    sprite->box = NULL;
    LabelSprite_TextConstruct(&sprite->text);
    sprite->colour = LABEL_SPRITE_COLOUR;
    sprite->on_main = on_main;
    sprite->window = 0;
    sprite->hide_second = 0;
    sprite->colour_dirty = 0;
    LabelSprite_SetState(sprite, LABEL_SPRITE_HIDDEN);
}

/* func_0208f518: the constructor: no offset, the cells' palette, an empty text, hidden. */
LabelSprite *LabelSprite_Construct(LabelSprite *sprite, int on_main, int kind)
{
    label_sprite_construct(sprite, (u8) on_main, kind);
    return sprite;
}
CLEAN_AS(func_0208f518, LabelSprite_Construct)

/* func_0208f58c: the constructor, a second copy (the label buttons'), taking a char. */
LabelSprite *LabelSprite_ConstructCopy(LabelSprite *sprite, char on_main, int kind)
{
    label_sprite_construct(sprite, (u8) on_main, kind);
    return sprite;
}
CLEAN_AS(func_0208f58c, LabelSprite_ConstructCopy)

/* func_0208f600 (the text's vtable slot 3): the address of its characters. */
int LabelSprite_TextChars(LabelSpriteText *text)
{
    return (int) (uintptr_t) text->chars;
}
CLEAN_AS(func_0208f600, LabelSprite_TextChars)

/* func_0208f604 (the text's vtable slot 2): its capacity in characters. */
int LabelSprite_TextCapacity(void)
{
    return LABEL_SPRITE_TEXT_CAPACITY;
}
CLEAN_AS(func_0208f604, LabelSprite_TextCapacity)

static void label_sprite_text_destruct(LabelSpriteText *text)
{
    text->vtable = &data_020e2388;
    TextBase_Destruct((TextBase *) text);
}

/* func_0208f608 (the text's vtable slot 1): destructed and freed. */
LabelSpriteText *LabelSprite_TextDelete(LabelSpriteText *text)
{
    label_sprite_text_destruct(text);
    Heap_OperatorDeleteB(text);
    return text;
}
CLEAN_AS(func_0208f608, LabelSprite_TextDelete)

/* func_0208f628 (the text's vtable slot 0): the destructor. */
LabelSpriteText *LabelSprite_TextDestruct(LabelSpriteText *text)
{
    label_sprite_text_destruct(text);
    return text;
}
CLEAN_AS(func_0208f628, LabelSprite_TextDestruct)

/* func_0208f640: the constructor: an empty text. */
LabelSpriteText *LabelSprite_TextConstruct(LabelSpriteText *text)
{
    TextBase_Construct(text);
    text->vtable = &data_020e2388;
    TextBase_Clear(text);
    return text;
}
CLEAN_AS(func_0208f640, LabelSprite_TextConstruct)
