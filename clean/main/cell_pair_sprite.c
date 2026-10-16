/* A sprite of two cell animations (cell_pair_sprite.h). */
#include "cell_pair_sprite.h"

#include "autoload_2/heap.h" /* Heap_OperatorDeleteB */
#include "cell_anim.h"
#include "clean.h"
#include "oam_buffer.h"

static_assert(offsetof(CellPairSprite, first) == 0x0c && offsetof(CellPairSprite, pose) == 0x34, "CellPairSprite");
static_assert(offsetof(CellPairSprite, alternate) == 0x40 && sizeof(CellPairSprite) == 0x44, "CellPairSprite");

/* The alternate set's animations are this many entries after the normal ones. */
#define ALTERNATE_OFFSET 6

extern const u32 data_020e2058[];          /* the class's vtable */
extern const u32 data_020d0a44[];          /* by pose: the first animation's entry */
extern const u32 data_020d0a34[];          /* by pose: hold the animations on their last frame */
extern const CellAnimData data_020d6fcc[]; /* the animations */

extern void func_0208af30(CellPairSprite *sprite); /* the base class's constructor */
extern void func_0208af00(CellPairSprite *sprite); /* the base class's destructor */
extern int func_0208aef0(CellPairSprite *sprite);  /* the base class's x */
extern int func_0208aeec(CellPairSprite *sprite);  /* the base class's y */

/* func_0208a20c: whether both animations are over (CellAnim_IsDone). */
int CellPairSprite_AnimsDone(CellPairSprite *sprite)
{
    return CellAnim_IsDone(&sprite->first) && CellAnim_IsDone(&sprite->second);
}
CLEAN_AS(func_0208a20c, CellPairSprite_AnimsDone)

/* func_0208a234 */
int CellPairSprite_Pose(CellPairSprite *sprite)
{
    return sprite->pose;
}
CLEAN_AS(func_0208a234, CellPairSprite_Pose)

/* func_0208a238: the pose set and its two animations started from their first frame. */
void CellPairSprite_SetPose(CellPairSprite *sprite, int pose)
{
    u32 entry = data_020d0a44[pose];
    if (sprite->alternate != 0) {
        entry += ALTERNATE_OFFSET;
    }
    u32 hold = data_020d0a34[pose];
    sprite->pose = pose;

    CellAnim_SetData(&sprite->first, &data_020d6fcc[entry]);
    CellAnim_SetHold(&sprite->first, (int) hold);
    CellAnim_Restart(&sprite->first);

    CellAnim_SetData(&sprite->second, &data_020d6fcc[entry + 1]);
    CellAnim_SetHold(&sprite->second, (int) hold);
    CellAnim_Restart(&sprite->second);
}
CLEAN_AS(func_0208a238, CellPairSprite_SetPose)

/* func_0208a2a8 */
void CellPairSprite_SetPlace(CellPairSprite *sprite, u32 x, u32 y)
{
    sprite->x = (int) x;
    sprite->y = (int) y;
}
CLEAN_AS(func_0208a2a8, CellPairSprite_SetPlace)

/* func_0208a2b0: the alternate set used from the next pose set. */
void CellPairSprite_UseAlternate(CellPairSprite *sprite)
{
    sprite->alternate = 1;
}
CLEAN_AS(func_0208a2b0, CellPairSprite_UseAlternate)

/* func_0208a2b8: vtable slot 3: both animations advanced, unless hidden. */
void CellPairSprite_Update(CellPairSprite *sprite)
{
    if (sprite->pose != CELL_PAIR_SPRITE_HIDDEN) {
        CellAnim_Advance(&sprite->first);
        CellAnim_Advance(&sprite->second);
    }
}
CLEAN_AS(func_0208a2b8, CellPairSprite_Update)

/* func_0208a2d8: vtable slot 2: both animations' cells drawn at their offsets, unless hidden. */
void CellPairSprite_Draw(CellPairSprite *sprite)
{
    if (sprite->pose == CELL_PAIR_SPRITE_HIDDEN) {
        return;
    }
    const OamEntry *first_cell = CellAnim_Cell(&sprite->first);
    const OamEntry *second_cell = CellAnim_Cell(&sprite->second);
    int first_x = CellAnim_FrameX(&sprite->first, -1);
    int first_y = CellAnim_FrameY(&sprite->first, -1);
    int second_x = CellAnim_FrameX(&sprite->second, -1);
    int second_y = CellAnim_FrameY(&sprite->second, -1);
    int x = sprite->x + func_0208aef0(sprite);
    int y = sprite->y + func_0208aeec(sprite);
    int screen = sprite->on_main != 0 ? OAM_BUFFER_SCREEN_MAIN : OAM_BUFFER_SCREEN_SUB;

    OamBuffer_DrawCell(screen, first_cell, x + first_x, y + first_y, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
    OamBuffer_DrawCell(screen, second_cell, x + second_x, y + second_y, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
}
CLEAN_AS(func_0208a2d8, CellPairSprite_Draw)

/* func_0208a3ec: vtable slot 1: destructed and freed. */
CellPairSprite *CellPairSprite_Delete(CellPairSprite *sprite)
{
    sprite->vtable = data_020e2058;
    CellAnim_Destruct(&sprite->second);
    CellAnim_Destruct(&sprite->first);
    func_0208af00(sprite);
    Heap_OperatorDeleteB(sprite);
    return sprite;
}
CLEAN_AS(func_0208a3ec, CellPairSprite_Delete)

/* func_0208a41c: vtable slot 0, the destructor. */
CellPairSprite *CellPairSprite_Destruct(CellPairSprite *sprite)
{
    sprite->vtable = data_020e2058;
    CellAnim_Destruct(&sprite->second);
    CellAnim_Destruct(&sprite->first);
    func_0208af00(sprite);
    return sprite;
}
CLEAN_AS(func_0208a41c, CellPairSprite_Destruct)

/* func_0208a448: the constructor: at the base class's place, in pose 0 of the normal set. */
CellPairSprite *CellPairSprite_Construct(CellPairSprite *sprite, int on_main)
{
    func_0208af30(sprite);
    sprite->vtable = data_020e2058;
    CellAnim_Construct(&sprite->first);
    CellAnim_Construct(&sprite->second);
    sprite->pose = CELL_PAIR_SPRITE_HIDDEN;
    sprite->x = 0;
    sprite->y = 0;
    sprite->alternate = 0;
    sprite->on_main = (u8) on_main;
    CellPairSprite_SetPose(sprite, 0);
    return sprite;
}
CLEAN_AS(func_0208a448, CellPairSprite_Construct)
