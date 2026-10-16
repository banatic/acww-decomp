/* main's sprite of a cell animation with an optional second layer (cell_layer_sprite.h). */
#include "cell_layer_sprite.h"

#include "autoload_2/heap.h" /* Heap_OperatorDeleteB */
#include "cell_anim.h"
#include "clean.h"
#include "oam_buffer.h" /* OamBuffer_DrawCell */
#include "sound.h"      /* SoundSys_ChangePlayerByte */

static_assert(offsetof(CellLayerSprite, anim) == 0x0c && offsetof(CellLayerSprite, offset_x) == 0x20, "CellLayerSprite");
static_assert(offsetof(CellLayerSprite, priority) == 0x28 && offsetof(CellLayerSprite, layer2) == 0x2c, "CellLayerSprite");
static_assert(offsetof(CellLayerSprite, anim_number) == 0x40 && offsetof(CellLayerSprite, on_main) == 0x48, "CellLayerSprite");
static_assert(offsetof(CellLayerSprite, window) == 0x4a && sizeof(CellLayerSprite) == 0x4c, "CellLayerSprite");

extern const u32 data_020e2314[];

/* The animations of main's sprites by number: the first layer's entry of data_020d6fcc (the
 * second layer's is the next), whether the animation loops, whether it has a second layer. */
extern const CellAnimData data_020d6fcc[];
extern const u32 data_020d0b08[];
extern const u8 data_020d0af4[];
extern const u8 data_020d0ae0[];

#define CELL_LAYER_SPRITE_UNK_44 0x16

/* The sound player's byte is set from the sprite's x on the screen, 0 to 255. */
#define CELL_LAYER_SPRITE_X_MAX 0xff

#define CELL_LAYER_SPRITE_FX_ONE 0x1000
#define CELL_LAYER_SPRITE_OBJ_WINDOW 2

/* func_0208e484: whether the animation has ended, and the second layer's too when it is shown. */
int CellLayerSprite_IsDone(CellLayerSprite *sprite)
{
    if (CellAnim_IsDone(&sprite->anim) == 0) {
        return 0;
    }
    if (sprite->has_layer2 != 0) {
        return CellAnim_IsDone(&sprite->layer2) != 0;
    }
    return 1;
}
CLEAN_AS(func_0208e484, CellLayerSprite_IsDone)

/* func_0208e4bc */
int CellLayerSprite_AnimNumber(CellLayerSprite *sprite)
{
    return sprite->anim_number;
}
CLEAN_AS(func_0208e4bc, CellLayerSprite_AnimNumber)

/* func_0208e4c0: animation `number` set at its last frame (both layers when the second is
 * shown). */
void CellLayerSprite_SetAnimAtEnd(CellLayerSprite *sprite, int number)
{
    CellLayerSprite_SetAnim(sprite, number);
    CellAnim_SetFrame(&sprite->anim, CellAnim_Data(&sprite->anim)->count - 1, 0);
    if (sprite->has_layer2 != 0) {
        CellAnim_SetFrame(&sprite->layer2, CellAnim_Data(&sprite->layer2)->count - 1, 0);
    }
}
CLEAN_AS(func_0208e4c0, CellLayerSprite_SetAnimAtEnd)

/* func_0208e508: animation `number` started (the second layer only when it is shown).
 * REQUIRES: `number` is within the tables (the ROM reads them unchecked). */
void CellLayerSprite_SetAnim(CellLayerSprite *sprite, int number)
{
    u32 entry = data_020d0b08[number];
    int hold = data_020d0af4[number] == 0;

    sprite->anim_number = number;
    CellAnim_SetData(&sprite->anim, &data_020d6fcc[entry]);
    CellAnim_SetHold(&sprite->anim, hold);
    CellAnim_Restart(&sprite->anim);

    sprite->has_layer2 = data_020d0ae0[number];
    if (sprite->has_layer2 != 0) {
        CellAnim_SetData(&sprite->layer2, &data_020d6fcc[entry + 1]);
        CellAnim_SetHold(&sprite->layer2, hold);
        CellAnim_Restart(&sprite->layer2);
    }
}
CLEAN_AS(func_0208e508, CellLayerSprite_SetAnim)

/* func_0208e594: the offset, and, while an animation is set, the sound player's byte from the
 * sprite's x on the screen (clamped to 0-255). */
void CellLayerSprite_SetOffset(CellLayerSprite *sprite, int x, int y)
{
    sprite->offset_x = x;
    sprite->offset_y = y;
    if (sprite->anim_number == CELL_LAYER_SPRITE_NONE) {
        return;
    }
    int screen_x = (int) ((u32) ScreenSprite_X(&sprite->base) + (u32) sprite->offset_x);
    if (screen_x < 0) {
        screen_x = 0;
    }
    if (screen_x > CELL_LAYER_SPRITE_X_MAX) {
        screen_x = CELL_LAYER_SPRITE_X_MAX;
    }
    SoundSys_ChangePlayerByte(screen_x);
}
CLEAN_AS(func_0208e594, CellLayerSprite_SetOffset)

/* func_0208e5c4 */
void CellLayerSprite_ClearWindow(CellLayerSprite *sprite)
{
    sprite->window = 0;
}
CLEAN_AS(func_0208e5c4, CellLayerSprite_ClearWindow)

/* func_0208e5cc */
void CellLayerSprite_SetWindow(CellLayerSprite *sprite)
{
    sprite->window = 1;
}
CLEAN_AS(func_0208e5cc, CellLayerSprite_SetWindow)

/* func_0208e5d4 (vtable slot 3): the animation advanced (and the second layer when shown), while
 * one is set. */
void CellLayerSprite_Update(CellLayerSprite *sprite)
{
    if (sprite->anim_number == CELL_LAYER_SPRITE_NONE) {
        return;
    }
    CellAnim_Advance(&sprite->anim);
    if (sprite->has_layer2 != 0) {
        CellAnim_Advance(&sprite->layer2);
    }
}
CLEAN_AS(func_0208e5d4, CellLayerSprite_Update)

static void cell_layer_sprite_draw_pass(CellLayerSprite *sprite, int screen, int obj_mode, const OamEntry *cell, int x, int y,
                                        const OamEntry *cell2, int x2, int y2)
{
    OamBuffer_DrawCell(screen, cell, x, y, -1, sprite->priority, CELL_LAYER_SPRITE_FX_ONE, CELL_LAYER_SPRITE_FX_ONE, 0,
                       obj_mode, 0, 0);
    if (cell2 != NULL) {
        OamBuffer_DrawCell(screen, cell2, x2, y2, -1, sprite->priority, CELL_LAYER_SPRITE_FX_ONE, CELL_LAYER_SPRITE_FX_ONE, 0,
                           obj_mode, 0, 0);
    }
}

/* func_0208e600 (vtable slot 2): while an animation is set, its cell (and the second layer's
 * when shown) drawn at the place plus the offset and the frame's own offset, on the main or the
 * sub screen, then again as OBJ window when `window` is set.
 * QUIRK: the second layer's frame offset is read even when that layer is not shown. */
void CellLayerSprite_Draw(CellLayerSprite *sprite)
{
    if (sprite->anim_number == CELL_LAYER_SPRITE_NONE) {
        return;
    }
    const OamEntry *cell = CellAnim_Cell(&sprite->anim);
    const OamEntry *cell2 = sprite->has_layer2 != 0 ? CellAnim_Cell(&sprite->layer2) : NULL;
    int frame_x = CellAnim_FrameX(&sprite->anim, -1);
    int frame_y = CellAnim_FrameY(&sprite->anim, -1);
    int frame2_x = CellAnim_FrameX(&sprite->layer2, -1);
    int frame2_y = CellAnim_FrameY(&sprite->layer2, -1);
    u32 x = (u32) sprite->offset_x + (u32) ScreenSprite_X(&sprite->base);
    u32 y = (u32) sprite->offset_y + (u32) ScreenSprite_Y(&sprite->base);

    int screen = sprite->on_main != 0 ? OAM_BUFFER_SCREEN_MAIN : OAM_BUFFER_SCREEN_SUB;
    int x1 = (int) (x + (u32) frame_x);
    int y1 = (int) (y + (u32) frame_y);
    int x2 = (int) (x + (u32) frame2_x);
    int y2 = (int) (y + (u32) frame2_y);
    cell_layer_sprite_draw_pass(sprite, screen, -1, cell, x1, y1, cell2, x2, y2);
    if (sprite->window != 0) {
        cell_layer_sprite_draw_pass(sprite, screen, CELL_LAYER_SPRITE_OBJ_WINDOW, cell, x1, y1, cell2, x2, y2);
    }
}
CLEAN_AS(func_0208e600, CellLayerSprite_Draw)

static void cell_layer_sprite_destruct(CellLayerSprite *sprite)
{
    sprite->base.vtable = data_020e2314;
    CellAnim_Destruct(&sprite->layer2);
    CellAnim_Destruct(&sprite->anim);
    ScreenSprite_DestructBase(&sprite->base);
}

/* func_0208e7f0: the destructor, a second copy of CellLayerSprite_Destruct (the one derived
 * classes call). */
CellLayerSprite *CellLayerSprite_DestructCopy(CellLayerSprite *sprite)
{
    cell_layer_sprite_destruct(sprite);
    return sprite;
}
CLEAN_AS(func_0208e7f0, CellLayerSprite_DestructCopy)

/* func_0208e81c (vtable slot 1): destructed and freed. */
CellLayerSprite *CellLayerSprite_Delete(CellLayerSprite *sprite)
{
    cell_layer_sprite_destruct(sprite);
    Heap_OperatorDeleteB(sprite);
    return sprite;
}
CLEAN_AS(func_0208e81c, CellLayerSprite_Delete)

/* func_0208e84c (vtable slot 0): the destructor. */
CellLayerSprite *CellLayerSprite_Destruct(CellLayerSprite *sprite)
{
    cell_layer_sprite_destruct(sprite);
    return sprite;
}
CLEAN_AS(func_0208e84c, CellLayerSprite_Destruct)

static void cell_layer_sprite_construct(CellLayerSprite *sprite, u8 on_main)
{
    ScreenSprite_Construct(&sprite->base);
    sprite->base.vtable = data_020e2314;
    CellAnim_Construct(&sprite->anim);
    sprite->offset_x = 0;
    sprite->offset_y = 0;
    sprite->priority = -1;
    CellAnim_Construct(&sprite->layer2);
    sprite->anim_number = CELL_LAYER_SPRITE_NONE;
    sprite->unk_44 = CELL_LAYER_SPRITE_UNK_44;
    sprite->on_main = on_main;
    sprite->has_layer2 = 1;
    sprite->window = 0;
    CellLayerSprite_SetAnim(sprite, CELL_LAYER_SPRITE_NONE);
}

/* func_0208e878: the constructor, a second copy of CellLayerSprite_Construct (overlay 004's). */
void *CellLayerSprite_ConstructCopy(CellLayerSprite *sprite, u8 on_main)
{
    cell_layer_sprite_construct(sprite, on_main);
    return sprite;
}
CLEAN_AS(func_0208e878, CellLayerSprite_ConstructCopy)

/* func_0208e8d4: the constructor: no offset, the cells' priority, no window, animation 0. */
void *CellLayerSprite_Construct(CellLayerSprite *sprite, u8 on_main)
{
    cell_layer_sprite_construct(sprite, on_main);
    return sprite;
}
CLEAN_AS(func_0208e8d4, CellLayerSprite_Construct)
