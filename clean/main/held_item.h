/* An item held in the hand (a field actor's at 0x5a0, FieldActor.held points at it; the slot
 * pool's item entries, slot_pool.h): the number of its entry in the held items' pool at
 * data_021ca16c (HELD_ITEM_NONE for none), its scale, an animation of its model's materials
 * and its line (the fishing line of the rods, held_line in overlay 3's field actor code).
 *
 * The pool keeps for each entry the item's code (0xfff1 for none), its model (an animated
 * model, AnimatedModel) with the model file, VRAM region and upload task, its heaps, and its
 * animation files. Items whose model kind (func_0205f64c) is HELD_ITEM_NO_MODEL have no
 * model; those of kind HELD_ITEM_TEXTURE_ANIMATED play a texture SRT animation as well. The
 * first eight bytes are the HeldItem of held_item_link.h. */
#ifndef CLEAN_MAIN_HELD_ITEM_H
#define CLEAN_MAIN_HELD_ITEM_H

#include "autoload_2/matrix.h"
#include "main/lookups.h"
#include "main/model_anim.h"
#include "types.h"

/* The number of the pool's entries, also an item's number for none. */
#define HELD_ITEM_NONE 9

/* The line's first words (the class of func_020606c0, its pool at data_021cad80). */
typedef struct HeldItemLine {
    u8 index;     /* 0x00: its number in its pool, 9 for none */
    u8 unk_01[3]; /* 0x01 */
    int state;    /* 0x04 */
} HeldItemLine;

typedef struct HeldItemObject {
    u8 index;          /* 0x00: its entry in the pool */
    u8 unk_01[3];      /* 0x01 */
    fx32 scale;        /* 0x04: on all three axes */
    ModelAnim anim;    /* 0x08: a HeldItemAnim (vtable data_020dd754) */
    HeldItemLine line; /* 0x28 */
} HeldItemObject;

int HeldItem_LineState4Or5(HeldItemObject *held);
int HeldItem_Model(const unsigned char *held);
void HeldItem_JointMatrix(Mtx43 *out, const u8 *held, u32 joint);
void HeldItem_Draw(HeldItemObject *held, const Mtx43 *matrix);
void HeldItem_Update(HeldItemObject *held);
void HeldItem_SetAnimSpeed(unsigned char *held, int speed);
void HeldItem_Act(u8 *held, int action, int blend, int flags);
void HeldItem_Take(HeldItemObject *held, ItemCode *item, u8 *record);
void HeldItem_Clear(HeldItemObject *held);
void HeldItem_Setup(HeldItemObject *held, int index, void *owner, ItemCode *item, u8 *record, int plain);
void HeldItem_AfterNode(void *state);
void HeldItem_BeforeNode(void *state);
HeldItemObject *HeldItem_Destruct(HeldItemObject *held);
HeldItemObject *HeldItem_Construct(HeldItemObject *held);
ModelAnim *HeldItemAnim_Delete(ModelAnim *anim);
ModelAnim *HeldItemAnim_Destruct(ModelAnim *anim);
ModelAnim *HeldItemAnim_Construct(ModelAnim *anim);
int HeldItem_PollUpload(u8 *pool, int index);

#endif
