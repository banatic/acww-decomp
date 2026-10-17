/* The cafe's master (cafe_master.h). */
#include "cafe_master.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/special_scene_object.h"
#include "main/speaker_anim.h"

/* Its parts read here. */
#define CAFE_MASTER_MODEL_FRAME 0x190 /* u32: its model's animation frame, 20.12 */
#define CAFE_MASTER_ANIM 0x334        /* SpeakerAnim */
#define CAFE_MASTER_TALK 0x658        /* its talk scene */
#define CAFE_MASTER_MATRIX_718 0x718  /* Mtx43 */
#define CAFE_MASTER_MATRIX_748 0x748  /* Mtx43 */

/* The vtable of its class. */
extern const u8 data_ov004_022546e0[];
/* The master while one is started. */
extern u8 *data_ov004_022580dc;

/* Its talk scene's destructor (vtable slot 0x00). */
extern void *func_ov004_02224580(void *talk);

/* The address `offset` bytes into the master; with no master the offset itself, as the ROM
 * computes it. */
static uintptr_t cm_at(u32 offset)
{
    return (uintptr_t) data_ov004_022580dc + offset;
}

/* func_ov004_02223654 (vtable slot 0x40): its talk scene's destructor, then the special
 * character's; the object. */
u8 *CafeMaster_Destroy(u8 *master)
{
    *(const u8 **) (void *) master = data_ov004_022546e0;
    func_ov004_02224580(master + CAFE_MASTER_TALK);
    SpecialSceneObject_DestructBody(master);
    return master;
}
CLEAN_AS(func_ov004_02223654, CafeMaster_Destroy)

/* func_ov004_0222367c (vtable slot 0x44): the same, then the object freed. */
u8 *CafeMaster_Delete(u8 *master)
{
    *(const u8 **) (void *) master = data_ov004_022546e0;
    func_ov004_02224580(master + CAFE_MASTER_TALK);
    SpecialSceneObject_DestructBody(master);
    Heap_FreeAux(master);
    return master;
}
CLEAN_AS(func_ov004_0222367c, CafeMaster_Delete)

/* func_ov004_022236a8: the number of the animation the master plays (SpeakerAnim_Number,
 * 0). */
int CafeMaster_AnimNumber(void)
{
    return SpeakerAnim_Number((SpeakerAnim *) cm_at(CAFE_MASTER_ANIM), 0);
}
CLEAN_AS(func_ov004_022236a8, CafeMaster_AnimNumber)

/* func_ov004_022236c4: the whole frame of the master's animation.
 * REQUIRES: a master is started (the ROM reads through the pointer unchecked). */
u16 CafeMaster_AnimFrame(void)
{
    u32 frame = *(const u32 *) cm_at(CAFE_MASTER_MODEL_FRAME);
    return (u16) (frame >> 12);
}
CLEAN_AS(func_ov004_022236c4, CafeMaster_AnimFrame)

/* func_ov004_022236dc: the master's matrix at 0x748. */
Mtx43 *CafeMaster_Matrix748(void)
{
    return (Mtx43 *) cm_at(CAFE_MASTER_MATRIX_748);
}
CLEAN_AS(func_ov004_022236dc, CafeMaster_Matrix748)

/* func_ov004_022236f0: the master's matrix at 0x718. */
Mtx43 *CafeMaster_Matrix718(void)
{
    return (Mtx43 *) cm_at(CAFE_MASTER_MATRIX_718);
}
CLEAN_AS(func_ov004_022236f0, CafeMaster_Matrix718)
