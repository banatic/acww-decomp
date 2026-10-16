/* The name tags of overlay 004 (name_tag.h). */
#include "name_tag.h"

#include "autoload_2/heap.h" /* Heap_OperatorDeleteB */
#include "cell_anim.h"
#include "clean.h"
#include "oam_buffer.h"    /* OamBuffer_DrawCell */
#include "quick_message.h" /* QuickMessage_TextConstruct, QuickMessage_TextDestruct */
#include "text_draw.h"     /* TextDraw_RequestDraw */

#include "ov004/member_pointer.h" /* MemberPointer */

static_assert(offsetof(NameTag, kind) == 0x0c && offsetof(NameTag, anim) == 0x14, "NameTag");
static_assert(offsetof(NameTag, x) == 0x28 && offsetof(NameTag, shift_x) == 0x34, "NameTag");
static_assert(offsetof(NameTag, text) == 0x38 && offsetof(NameTag, box) == 0x6c, "NameTag");
static_assert(offsetof(NameTag, state) == 0x70 && offsetof(NameTag, visible) == 0x7c, "NameTag");
static_assert(sizeof(NameTagText) == 0x34 && sizeof(NameTag) == 0x80, "NameTag");

/* The class's vtable, and the member function table of NameTag_Update (a function-local static
 * of the game): its guard, the table, and the constants it is filled from. */
extern const u32 data_020e22f8[];
extern u32 data_021d35a4;
extern MemberPointer data_021d35a8[4];
extern const MemberPointer data_020e22d8, data_020e22e8, data_020e22d0, data_020e22e0;

/* The animations of main's sprites, and the entry of each kind's: 10-13, and 0x28 for kind 4. */
extern const CellAnimData data_020d5b3c[];
extern const int data_020d0ac8[];
#define NAME_TAG_DEFAULT_ANIM 10

/* The colour kind 4 loads into the OBJ palettes: colour 14 of palette 5. */
extern const u16 data_020d0adc;
extern void GX_LoadOBJPltt(const void *src, u32 offset, u32 size);
#define NAME_TAG_FIXED_COLOUR_OFFSET 0xbc
#define NAME_TAG_FIXED_COLOUR_SIZE 2

/* The text box: 20 tiles by 2 on OBJs of the main screen, at VRAM tile 0xc0 + 0x40 * kind (kind 4
 * at 0x1c8), in colour 0xd on background 0xf (0xe for kind 4). */
#define NAME_TAG_BOX_CELLS 0x14
#define NAME_TAG_BOX_ROWS 2
#define NAME_TAG_BOX_TILE 0xc0
#define NAME_TAG_BOX_TILES_PER_KIND 0x40
#define NAME_TAG_BOX_TILE_FIXED 0x1c8
#define NAME_TAG_BOX_LAYER_OBJECTS 4
#define NAME_TAG_BOX_COLOR 0xd
#define NAME_TAG_BOX_BACKGROUND 0xf
#define NAME_TAG_BOX_BACKGROUND_FIXED 0xe

/* The box's vtable slot that measures its text, in pixels. */
#define NAME_TAG_BOX_SLOT_MEASURE 3

/* The tag's shift: 0x24 pixels right of its place, 4 fewer for each wider frame; none for kind 0. */
#define NAME_TAG_SHIFT 0x24
#define NAME_TAG_SHIFT_PER_FRAME 4

/* The pop when appearing and the drop when hiding. */
#define NAME_TAG_APPEAR_FRAMES 3
#define NAME_TAG_APPEAR_BOUNCE 5
#define NAME_TAG_APPEAR_RISE 6
#define NAME_TAG_APPEAR_FALL 2
#define NAME_TAG_HIDE_FRAMES 2
#define NAME_TAG_HIDE_DROP 0xb

#define NAME_TAG_ASKED 2
#define NAME_TAG_FX_ONE 0x1000

/* func_0208e044: the text box freed, if there is one. */
void NameTag_FreeBox(NameTag *tag)
{
    LabelBox *box = tag->box;
    if (box != NULL) {
        LabelBox_Free(box);
        tag->box = NULL;
    }
}
CLEAN_AS(func_0208e044, NameTag_FreeBox)

/* func_0208e05c: the text box made, unless there is one, and the name handed to it to be drawn;
 * nothing when the boxes' heap is full. */
void NameTag_OpenBox(NameTag *tag)
{
    if (tag->box != NULL) {
        return;
    }
    int fixed = tag->kind == NAME_TAG_KIND_FIXED;
    int tile = fixed ? NAME_TAG_BOX_TILE_FIXED : (int) ((u32) tag->kind * NAME_TAG_BOX_TILES_PER_KIND + NAME_TAG_BOX_TILE);
    u8 background = fixed ? NAME_TAG_BOX_BACKGROUND_FIXED : NAME_TAG_BOX_BACKGROUND;

    tag->box = LabelBox_NewInVram(tile, NAME_TAG_BOX_CELLS, NAME_TAG_BOX_ROWS);
    if (tag->box == NULL) {
        return;
    }
    tag->box->base.layer = NAME_TAG_BOX_LAYER_OBJECTS;
    /* the name's characters, through the text's vtable */
    u32 chars = ((u32 (*)(NameTagText *))(uintptr_t) tag->text.vtable->buffer)(&tag->text);
    tag->box->base.text = (const char *) (uintptr_t) chars;
    tag->box->base.screens = TEXT_DRAW_TO_MAIN;
    tag->box->base.rows_full_width = 1;
    tag->box->base.background = background;
    tag->box->base.color = NAME_TAG_BOX_COLOR;
    TextDraw_RequestDraw(&tag->box->base);
}
CLEAN_AS(func_0208e05c, NameTag_OpenBox)

/* func_0208e0dc: the tag sized to its name: the frame of the animation as many tiles wide as the
 * text (the last frame when the text is wider, the first for an empty text), the text centred in
 * those tiles, and the tag shifted for that frame. */
void NameTag_LayOut(NameTag *tag)
{
    if (tag->box == NULL) {
        return;
    }
    u32 width = ((u32 (*)(LabelBox *))(uintptr_t) tag->box->base.vtable[NAME_TAG_BOX_SLOT_MEASURE])(tag->box);
    u32 tiles = (width + 7) >> 3;
    int frame = CellAnim_Data(&tag->anim)->count - 1;
    int last_fitting = (int) (tiles - 1);
    if (last_fitting < 0) {
        frame = 0;
    } else if (last_fitting <= frame) {
        frame = last_fitting;
    }
    CellAnim_SetFrame(&tag->anim, frame, 0);
    tag->box->base.offset = ((tiles << 3) - width) >> 1;
    if (tag->kind == 0) {
        tag->shift_x = 0;
    } else {
        tag->shift_x = (int) (NAME_TAG_SHIFT - (u32) frame * NAME_TAG_SHIFT_PER_FRAME);
    }
}
CLEAN_AS(func_0208e0dc, NameTag_LayOut)

/* func_0208e144: the kind's animation set, held and still. */
void NameTag_SetAnim(NameTag *tag)
{
    CellAnim_SetData(&tag->anim, &data_020d5b3c[tag->anim_entry]);
    CellAnim_SetHold(&tag->anim, 1);
    CellAnim_SetSpeed(&tag->anim, 0);
}
CLEAN_AS(func_0208e144, NameTag_SetAnim)

/* func_0208e174 (state 3): the tag dropped; once the frames are over, its box freed and hidden.
 * QUIRK: the frames are the timer NameTag_EnterShown set (2); hiding does not set it. */
void NameTag_StepHiding(NameTag *tag)
{
    tag->bounce += NAME_TAG_HIDE_DROP;
    tag->timer -= 1;
    if (tag->timer > 0) {
        return;
    }
    NameTag_FreeBox(tag);
    NameTag_EnterHidden(tag);
}
CLEAN_AS(func_0208e174, NameTag_StepHiding)

/* func_0208e19c */
void NameTag_EnterHiding(NameTag *tag)
{
    tag->state = NAME_TAG_HIDING;
    tag->visible = 1;
}
CLEAN_AS(func_0208e19c, NameTag_EnterHiding)

/* func_0208e1a8 (state 2): hiding once no longer asked to show. */
void NameTag_StepShown(NameTag *tag)
{
    if (tag->wanted == 0) {
        NameTag_EnterHiding(tag);
    }
}
CLEAN_AS(func_0208e1a8, NameTag_StepShown)

/* func_0208e1bc: shown, with the frames hiding will take. */
void NameTag_EnterShown(NameTag *tag)
{
    tag->state = NAME_TAG_SHOWN;
    tag->visible = 1;
    tag->timer = NAME_TAG_HIDE_FRAMES;
}
CLEAN_AS(func_0208e1bc, NameTag_EnterShown)

/* func_0208e1cc (state 1): the pop: 6 pixels up in the first frame, 2 down in the others, and
 * in place and shown once the frames are over. */
void NameTag_StepAppearing(NameTag *tag)
{
    if (tag->timer > NAME_TAG_APPEAR_FRAMES - 1) {
        tag->bounce -= NAME_TAG_APPEAR_RISE;
    } else {
        tag->bounce += NAME_TAG_APPEAR_FALL;
    }
    tag->timer -= 1;
    if (tag->timer <= 0) {
        tag->bounce = 0;
        NameTag_EnterShown(tag);
    }
}
CLEAN_AS(func_0208e1cc, NameTag_StepAppearing)

/* func_0208e200 */
void NameTag_EnterAppearing(NameTag *tag)
{
    tag->state = NAME_TAG_APPEARING;
    tag->visible = 1;
    tag->timer = NAME_TAG_APPEAR_FRAMES;
    tag->bounce = NAME_TAG_APPEAR_BOUNCE;
}
CLEAN_AS(func_0208e200, NameTag_EnterAppearing)

/* func_0208e214 (state 0): once asked to show, the box made (kind 4 loading its colour first),
 * the tag laid out, and appearing. */
void NameTag_StepHidden(NameTag *tag)
{
    if (tag->wanted == 0) {
        return;
    }
    if (tag->kind == NAME_TAG_KIND_FIXED) {
        NameTag_LoadFixedColour();
    }
    NameTag_OpenBox(tag);
    NameTag_LayOut(tag);
    NameTag_EnterAppearing(tag);
}
CLEAN_AS(func_0208e214, NameTag_StepHidden)

/* func_0208e240 */
void NameTag_EnterHidden(NameTag *tag)
{
    tag->state = NAME_TAG_HIDDEN;
    tag->visible = 0;
}
CLEAN_AS(func_0208e240, NameTag_EnterHidden)

/* func_0208e24c: kind 4's colour loaded into the main screen's OBJ palettes. */
void NameTag_LoadFixedColour(void)
{
    GX_LoadOBJPltt(&data_020d0adc, NAME_TAG_FIXED_COLOUR_OFFSET, NAME_TAG_FIXED_COLOUR_SIZE);
}
CLEAN_AS(func_0208e24c, NameTag_LoadFixedColour)

/* func_0208e260: no longer asked to show, unless hidden; whether it was not hidden.
 * QUIRK: the result is 1 or 0 in a pointer, as the matching source declares it. */
void *NameTag_Hide(NameTag *tag)
{
    int showing = tag->state != NAME_TAG_HIDDEN;
    if (showing) {
        tag->wanted = 0;
    }
    return (void *) (uintptr_t) showing;
}
CLEAN_AS(func_0208e260, NameTag_Hide)

/* func_0208e278: asked to show, when hidden; whether it was hidden. */
int NameTag_Show(NameTag *tag)
{
    int hidden = tag->state == NAME_TAG_HIDDEN;
    if (hidden) {
        tag->wanted = NAME_TAG_ASKED;
    }
    return hidden;
}
CLEAN_AS(func_0208e278, NameTag_Show)

/* func_0208e290: the name copied in (drawn when the box is next made). */
void *NameTag_SetText(NameTag *tag, TextBase *text)
{
    return TextBase_Copy((TextBase *) &tag->text, text);
}
CLEAN_AS(func_0208e290, NameTag_SetText)

/* func_0208e29c */
void NameTag_SetPlace(NameTag *tag, int x, int y)
{
    tag->x = x;
    tag->y = y;
}
CLEAN_AS(func_0208e29c, NameTag_SetPlace)

/* func_0208e2a4 */
void NameTag_Rewind(NameTag *tag)
{
    NameTag_FreeBox(tag);
}
CLEAN_AS(func_0208e2a4, NameTag_Rewind)

/* func_0208e2ac: the kind, and its animation. */
void NameTag_SetKind(NameTag *tag, int kind)
{
    tag->kind = kind;
    tag->anim_entry = data_020d0ac8[kind];
    NameTag_SetAnim(tag);
}
CLEAN_AS(func_0208e2ac, NameTag_SetKind)

/* func_0208e2c4 (vtable slot 3): the state's step (through the game's table, filled on the first
 * call) and, unless hidden, the animation advanced.
 * REQUIRES: the state is 0-3 (the ROM indexes its table unchecked). */
void NameTag_Update(NameTag *tag)
{
    static const MemberPointer *const constants[4] = {
        &data_020e22d8, /* NameTag_StepHidden */
        &data_020e22e8, /* NameTag_StepAppearing */
        &data_020e22d0, /* NameTag_StepShown */
        &data_020e22e0, /* NameTag_StepHiding */
    };
    MemberTable_InitOnce(&data_021d35a4, data_021d35a8, constants, 4);
    MemberPointer_CallVoid(&data_021d35a8[tag->state], tag);
    if (tag->state != NAME_TAG_HIDDEN) {
        CellAnim_Advance(&tag->anim);
    }
}
CLEAN_AS(func_0208e2c4, NameTag_Update)

/* func_0208e354 (vtable slot 2): the cell drawn on the main screen while visible, at the place
 * plus the base class's, the frame's offset, the shift and the bounce. */
void NameTag_Draw(NameTag *tag)
{
    if (tag->visible == 0) {
        return;
    }
    const OamEntry *cell = CellAnim_Cell(&tag->anim);
    u32 x = (u32) tag->x + (u32) ScreenSprite_X(&tag->base);
    x += (u32) tag->shift_x + (u32) CellAnim_FrameX(&tag->anim, -1);
    u32 y = (u32) tag->y + (u32) ScreenSprite_Y(&tag->base);
    y += (u32) tag->bounce + (u32) CellAnim_FrameY(&tag->anim, -1);
    OamBuffer_DrawCell(OAM_BUFFER_SCREEN_MAIN, cell, (int) x, (int) y, -1, -1, NAME_TAG_FX_ONE, NAME_TAG_FX_ONE, 0, -1, 0, 0);
}
CLEAN_AS(func_0208e354, NameTag_Draw)

static void name_tag_destruct(NameTag *tag)
{
    tag->base.vtable = data_020e22f8;
    NameTag_Rewind(tag);
    QuickMessage_TextDestruct((struct QuickMessageText *) &tag->text);
    CellAnim_Destruct(&tag->anim);
    ScreenSprite_DestructBase(&tag->base);
}

/* func_0208e3d4 (vtable slot 1): destructed and freed. */
NameTag *NameTag_Delete(NameTag *tag)
{
    name_tag_destruct(tag);
    Heap_OperatorDeleteB(tag);
    return tag;
}
CLEAN_AS(func_0208e3d4, NameTag_Delete)

/* func_0208e408 (vtable slot 0): the destructor. */
NameTag *NameTag_Destruct(NameTag *tag)
{
    name_tag_destruct(tag);
    return tag;
}
CLEAN_AS(func_0208e408, NameTag_Destruct)

/* func_0208e438: the constructor: kind 0 with animation entry 10 (not yet set), no box, an empty
 * name, hidden and not asked to show. */
NameTag *NameTag_Construct(NameTag *tag)
{
    ScreenSprite_Construct(&tag->base);
    tag->base.vtable = data_020e22f8;
    tag->kind = 0;
    tag->anim_entry = NAME_TAG_DEFAULT_ANIM;
    CellAnim_Construct(&tag->anim);
    tag->x = 0;
    tag->y = 0;
    tag->bounce = 0;
    tag->shift_x = 0;
    QuickMessage_TextConstruct((struct QuickMessageText *) &tag->text);
    tag->box = NULL;
    tag->state = NAME_TAG_HIDDEN;
    tag->wanted = 0;
    tag->timer = 0;
    tag->visible = 0;
    return tag;
}
CLEAN_AS(func_0208e438, NameTag_Construct)
