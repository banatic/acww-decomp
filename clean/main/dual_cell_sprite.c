/* main's sprite of two cell animations played together (dual_cell_sprite.h). */
#include "dual_cell_sprite.h"

#include "autoload_2/heap.h" /* Heap_OperatorDeleteB */
#include "cell_anim.h"
#include "clean.h"
#include "oam_buffer.h" /* OamBuffer_DrawCell */

static_assert(offsetof(DualCellSprite, offset_x) == 0x0c && offsetof(DualCellSprite, first) == 0x14, "DualCellSprite");
static_assert(offsetof(DualCellSprite, second) == 0x28 && offsetof(DualCellSprite, state) == 0x3c, "DualCellSprite");
static_assert(offsetof(DualCellSprite, on_main) == 0x40 && offsetof(DualCellSprite, priority) == 0x44, "DualCellSprite");
static_assert(sizeof(DualCellSprite) == 0x48, "DualCellSprite");

extern const u32 data_020e2330[];

/* The animations by state: the first's entry of data_020d6fcc (the second's is the next), and
 * whether they hold their last frame (all do). */
extern const CellAnimData data_020d6fcc[];
extern const u32 data_020d0b64[];
extern const u32 data_020d0b54[];

#define DUAL_CELL_SPRITE_FX_ONE 0x1000
#define DUAL_CELL_SPRITE_CURRENT_FRAME (-1)

/* func_0208e930: whether both animations have ended. */
int DualCellSprite_IsDone(DualCellSprite *sprite)
{
    if (CellAnim_IsDone(&sprite->first) != 0 && CellAnim_IsDone(&sprite->second) != 0) {
        return 1;
    }
    return 0;
}
CLEAN_AS(func_0208e930, DualCellSprite_IsDone)

/* func_0208e958 */
int DualCellSprite_State(DualCellSprite *sprite)
{
    return sprite->state;
}
CLEAN_AS(func_0208e958, DualCellSprite_State)

/* func_0208e95c: the state's animations started, stopped (speed 0) in the still state; the
 * result is what the last call on the second animation returns (the animation).
 * REQUIRES: `state` is 0-3 (the ROM reads its tables unchecked). */
void *DualCellSprite_SetState(DualCellSprite *sprite, int state)
{
    u32 entry = data_020d0b64[state];
    u32 hold = data_020d0b54[state];

    sprite->state = state;

    CellAnim_SetData(&sprite->first, &data_020d6fcc[entry]);
    CellAnim_SetHold(&sprite->first, (int) hold);
    CellAnim_Restart(&sprite->first);

    CellAnim_SetData(&sprite->second, &data_020d6fcc[entry + 1]);
    CellAnim_SetHold(&sprite->second, (int) hold);
    void *result = CellAnim_Restart(&sprite->second);

    if (state == DUAL_CELL_SPRITE_STILL) {
        CellAnim_SetSpeed(&sprite->first, 0);
        return CellAnim_SetSpeed(&sprite->second, 0);
    }
    return result;
}
CLEAN_AS(func_0208e95c, DualCellSprite_SetState)

/* func_0208e9e0: how far the first animation's offset has moved: from its first frame to the
 * current one in state 2, back from the current one to the first in state 3, else 0. */
void DualCellSprite_Travel(DualCellSprite *sprite, int *dx, int *dy)
{
    int x = 0;
    int y = 0;

    if (sprite->state == DUAL_CELL_SPRITE_PLAY_A) {
        int current_x = CellAnim_FrameX(&sprite->first, DUAL_CELL_SPRITE_CURRENT_FRAME);
        x = current_x - CellAnim_FrameX(&sprite->first, 0);
        int current_y = CellAnim_FrameY(&sprite->first, DUAL_CELL_SPRITE_CURRENT_FRAME);
        y = current_y - CellAnim_FrameY(&sprite->first, 0);
    } else if (sprite->state == DUAL_CELL_SPRITE_PLAY_B) {
        int first_x = CellAnim_FrameX(&sprite->first, 0);
        x = first_x - CellAnim_FrameX(&sprite->first, DUAL_CELL_SPRITE_CURRENT_FRAME);
        int first_y = CellAnim_FrameY(&sprite->first, 0);
        y = first_y - CellAnim_FrameY(&sprite->first, DUAL_CELL_SPRITE_CURRENT_FRAME);
    }
    *dx = x;
    *dy = y;
}
CLEAN_AS(func_0208e9e0, DualCellSprite_Travel)

/* func_0208ea6c */
void DualCellSprite_SetPriority(DualCellSprite *sprite, int priority)
{
    sprite->priority = priority;
}
CLEAN_AS(func_0208ea6c, DualCellSprite_SetPriority)

/* func_0208ea70 */
void DualCellSprite_SetOffset(DualCellSprite *sprite, int x, int y)
{
    sprite->offset_x = x;
    sprite->offset_y = y;
}
CLEAN_AS(func_0208ea70, DualCellSprite_SetOffset)

/* func_0208ea78 (vtable slot 3): both animations advanced, unless hidden. */
void DualCellSprite_Update(DualCellSprite *sprite)
{
    if (sprite->state == DUAL_CELL_SPRITE_HIDDEN) {
        return;
    }
    CellAnim_Advance(&sprite->first);
    CellAnim_Advance(&sprite->second);
}
CLEAN_AS(func_0208ea78, DualCellSprite_Update)

/* func_0208ea98 (vtable slot 2): unless hidden, both cells drawn at the place plus the offset and
 * each frame's own offset, on the main or the sub screen. */
void DualCellSprite_Draw(DualCellSprite *sprite)
{
    if (sprite->state == DUAL_CELL_SPRITE_HIDDEN) {
        return;
    }
    const OamEntry *cell = CellAnim_Cell(&sprite->first);
    const OamEntry *cell2 = CellAnim_Cell(&sprite->second);
    int frame_x = CellAnim_FrameX(&sprite->first, DUAL_CELL_SPRITE_CURRENT_FRAME);
    int frame_y = CellAnim_FrameY(&sprite->first, DUAL_CELL_SPRITE_CURRENT_FRAME);
    int frame2_x = CellAnim_FrameX(&sprite->second, DUAL_CELL_SPRITE_CURRENT_FRAME);
    int frame2_y = CellAnim_FrameY(&sprite->second, DUAL_CELL_SPRITE_CURRENT_FRAME);
    u32 x = (u32) sprite->offset_x + (u32) ScreenSprite_X(&sprite->base);
    u32 y = (u32) sprite->offset_y + (u32) ScreenSprite_Y(&sprite->base);

    int screen = sprite->on_main != 0 ? OAM_BUFFER_SCREEN_MAIN : OAM_BUFFER_SCREEN_SUB;
    OamBuffer_DrawCell(screen, cell, (int) (x + (u32) frame_x), (int) (y + (u32) frame_y), -1, sprite->priority,
                       DUAL_CELL_SPRITE_FX_ONE, DUAL_CELL_SPRITE_FX_ONE, 0, -1, 0, 0);
    OamBuffer_DrawCell(screen, cell2, (int) (x + (u32) frame2_x), (int) (y + (u32) frame2_y), -1, sprite->priority,
                       DUAL_CELL_SPRITE_FX_ONE, DUAL_CELL_SPRITE_FX_ONE, 0, -1, 0, 0);
}
CLEAN_AS(func_0208ea98, DualCellSprite_Draw)

static void dual_cell_sprite_destruct(DualCellSprite *sprite)
{
    sprite->base.vtable = data_020e2330;
    CellAnim_Destruct(&sprite->second);
    CellAnim_Destruct(&sprite->first);
    ScreenSprite_DestructBase(&sprite->base);
}

/* func_0208ebb8: the destructor, a second copy of DualCellSprite_Destruct (the push buttons'). */
DualCellSprite *DualCellSprite_DestructCopy(DualCellSprite *sprite)
{
    dual_cell_sprite_destruct(sprite);
    return sprite;
}
CLEAN_AS(func_0208ebb8, DualCellSprite_DestructCopy)

/* func_0208ebe4 (vtable slot 1): destructed and freed. */
DualCellSprite *DualCellSprite_Delete(DualCellSprite *sprite)
{
    dual_cell_sprite_destruct(sprite);
    Heap_OperatorDeleteB(sprite);
    return sprite;
}
CLEAN_AS(func_0208ebe4, DualCellSprite_Delete)

/* func_0208ec14 (vtable slot 0): the destructor. */
DualCellSprite *DualCellSprite_Destruct(DualCellSprite *sprite)
{
    dual_cell_sprite_destruct(sprite);
    return sprite;
}
CLEAN_AS(func_0208ec14, DualCellSprite_Destruct)

static void dual_cell_sprite_construct(DualCellSprite *sprite, u8 on_main)
{
    ScreenSprite_Construct(&sprite->base);
    sprite->base.vtable = data_020e2330;
    sprite->offset_x = 0;
    sprite->offset_y = 0;
    CellAnim_Construct(&sprite->first);
    CellAnim_Construct(&sprite->second);
    sprite->state = DUAL_CELL_SPRITE_HIDDEN;
    sprite->on_main = on_main;
    sprite->priority = -1;
    DualCellSprite_SetState(sprite, DUAL_CELL_SPRITE_HIDDEN);
}

/* func_0208ec40: the constructor: no offset, the cells' priority, hidden. */
DualCellSprite *DualCellSprite_Construct(DualCellSprite *sprite, char on_main)
{
    dual_cell_sprite_construct(sprite, (u8) on_main);
    return sprite;
}
CLEAN_AS(func_0208ec40, DualCellSprite_Construct)

/* func_0208ec88: the constructor, a second copy (the push buttons'), taking an int. */
void *DualCellSprite_ConstructCopy(DualCellSprite *sprite, int on_main)
{
    dual_cell_sprite_construct(sprite, (u8) on_main);
    return sprite;
}
CLEAN_AS(func_0208ec88, DualCellSprite_ConstructCopy)
