/* The scene object class with vtable 0x020d8c64 (obj_020d8c64.h). */
#include "obj_020d8c64.h"

#include "autoload_2/heap.h"
#include "autoload_2/sound_emitter_class.h"
#include "clean.h"
#include "scene_action.h"
#include "act_effects.h"
#include "field_body.h"
#include "field_collision.h"
#include "footsteps.h"
#include "layered_model.h"
#include "motion_slots.h"
#include "scene_base.h"
#include "scene_face.h"
#include "scene_look.h"
#include "scene_motion_request.h"
#include "scene_mover.h"
#include "scene_object.h"
#include "scene_object_base.h"
#include "scene_standard_anims.h"
#include "scene_talk_state.h"
#include "speaker_anim.h"

/* The class's vtable and that of the sound emitter at 0x514, whose destructor is inlined. */
extern const u8 data_020d8c64[];
extern const u8 data_020d8414[];

#define SOUND_EMITTER 0x514

static u8 *at(void *object, u32 offset)
{
    return (u8 *) object + offset;
}

/* func_020120e0: the destructor: as Obj020d8c64_DestructDelete without freeing the memory.
 * Returns the object. */
void *Obj020d8c64_Destruct(void *object)
{
    *(const u8 **) object = data_020d8c64;
    SceneAction_Destruct((SceneAction *) (void *) at(object, 0x618));
    SceneMotion_Destruct((SceneMotion *) (void *) at(object, 0x564));
    Footsteps_Destruct((Footsteps *) (void *) at(object, 0x558));
    *(const u8 **) at(object, SOUND_EMITTER) = data_020d8414;
    SoundEmitterClass_DestructBase((SoundEmitterObject *) at(object, SOUND_EMITTER));
    FieldOwnedBody_Destruct2((FieldOwnedBody *) (void *) at(object, 0x4cc));
    CollisionContacts_Destroy((CollisionContacts *) (void *) at(object, 0x49c));
    ActEffects_Destruct((ActEffects *) (void *) at(object, 0x420));
    SceneTalkState_Destruct((SceneTalkState *) (void *) at(object, 0x418));
    SceneLook_Destruct((SceneLook *) (void *) at(object, 0x3b0));
    SceneMover_Destruct((SceneMover *) (void *) at(object, 0x350));
    SpeakerAnim_Construct((SpeakerAnim *) (void *) at(object, 0x334));
    SceneFace_Destruct((SceneFace *) (void *) at(object, 0x2ac));
    SceneStandardAnims_Destruct((SceneStandardAnims *) (void *) at(object, 0x2a0));
    LayeredModel_DestructB((LayeredModel *) (void *) at(object, 0x0ec));
    SceneObjectBase_DestructBase(object);
    return object;
}
CLEAN_AS(func_020120e0, Obj020d8c64_Destruct)

/* func_02012014: the deleting destructor (vtable slot 0x44): the class's vtable, the members in
 * the reverse order of their places (the emitter at 0x514 gets its own vtable first), the
 * base, then the memory freed to the auxiliary heap. Returns the object. */
void *Obj020d8c64_DestructDelete(void *object)
{
    *(const u8 **) object = data_020d8c64;
    SceneAction_Destruct((SceneAction *) (void *) at(object, 0x618));
    SceneMotion_Destruct((SceneMotion *) (void *) at(object, 0x564));
    Footsteps_Destruct((Footsteps *) (void *) at(object, 0x558));
    *(const u8 **) at(object, SOUND_EMITTER) = data_020d8414;
    SoundEmitterClass_DestructBase((SoundEmitterObject *) at(object, SOUND_EMITTER));
    FieldOwnedBody_Destruct2((FieldOwnedBody *) (void *) at(object, 0x4cc));
    CollisionContacts_Destroy((CollisionContacts *) (void *) at(object, 0x49c));
    ActEffects_Destruct((ActEffects *) (void *) at(object, 0x420));
    SceneTalkState_Destruct((SceneTalkState *) (void *) at(object, 0x418));
    SceneLook_Destruct((SceneLook *) (void *) at(object, 0x3b0));
    SceneMover_Destruct((SceneMover *) (void *) at(object, 0x350));
    SpeakerAnim_Construct((SpeakerAnim *) (void *) at(object, 0x334));
    SceneFace_Destruct((SceneFace *) (void *) at(object, 0x2ac));
    SceneStandardAnims_Destruct((SceneStandardAnims *) (void *) at(object, 0x2a0));
    LayeredModel_DestructB((LayeredModel *) (void *) at(object, 0x0ec));
    SceneObjectBase_DestructBase(object);
    Heap_FreeAux(object);
    return object;
}
CLEAN_AS(func_02012014, Obj020d8c64_DestructDelete)

/* ---- The motion number kept at 0x63e */

#define OBJ_020D8C64_MOTION 0x564
#define OBJ_020D8C64_ACTION 0x618
#define OBJ_020D8C64_MOTION_NUMBER 0x63e
#define OBJ_020D8C64_NO_NUMBER (-1)
/* The kind of motion of a talk, and the numbers its byte 0xa9 may give. */
#define OBJ_020D8C64_MOTION_TALK 8
#define OBJ_020D8C64_NUMBER_LAST 59

/* func_02013a0c (vtable slot 0xa0 of the class): no number (-1). */
int Obj020d8c64_NoMotionNumber(void *object)
{
    (void) object;
    return OBJ_020D8C64_NO_NUMBER;
}
CLEAN_AS(func_02013a0c, Obj020d8c64_NoMotionNumber)

/* func_02013a14: while an action runs or is requested (SceneAction_IsBusy), the motion is the
 * talk's (kind 8), and the object is in a scene (func_0201c274) without another speaker
 * (func_020160d4): the number its motion shows (byte 0xa9, func_02019df8) when it is 1 to 59,
 * not the one kept, and none of the four bytes of the player's record (func_0203f9e0); it is
 * then kept. Else -1. */
int Obj020d8c64_TakeNewMotionNumber(void *object)
{
    void *motion = at(object, OBJ_020D8C64_MOTION);
    if (SceneAction_IsBusy((const SceneAction *) at(object, OBJ_020D8C64_ACTION)) == 0 ||
        SceneMotion_Kind(motion) != OBJ_020D8C64_MOTION_TALK) {
        return OBJ_020D8C64_NO_NUMBER;
    }
    u32 scene = SceneObject_Scene(object);
    if (scene == 0 || SceneBase_SecondSpeaker((void *) (uintptr_t) scene) != 0) {
        return OBJ_020D8C64_NO_NUMBER;
    }
    int number = SceneMotion_ActNumber(motion);
    if (number > 0 && number <= OBJ_020D8C64_NUMBER_LAST && number != Obj020d8c64_LastMotionNumber((s16 *) object) &&
        MotionSlots_Find((u8) number) == -1) {
        Obj020d8c64_SetLastMotionNumber(object, (u8) number);
        return number;
    }
    return OBJ_020D8C64_NO_NUMBER;
}
CLEAN_AS(func_02013a14, Obj020d8c64_TakeNewMotionNumber)

/* func_02013a94 */
s16 Obj020d8c64_LastMotionNumber(s16 *object)
{
    return *(const s16 *) at(object, OBJ_020D8C64_MOTION_NUMBER);
}
CLEAN_AS(func_02013a94, Obj020d8c64_LastMotionNumber)

/* func_02013aa0 */
void Obj020d8c64_SetLastMotionNumber(void *object, u16 number)
{
    *(u16 *) at(object, OBJ_020D8C64_MOTION_NUMBER) = number;
}
CLEAN_AS(func_02013aa0, Obj020d8c64_SetLastMotionNumber)

/* func_02013aac: none kept (0xffff). */
void Obj020d8c64_ClearLastMotionNumber(void *object)
{
    *(u16 *) at(object, OBJ_020D8C64_MOTION_NUMBER) = 0xffff;
}
CLEAN_AS(func_02013aac, Obj020d8c64_ClearLastMotionNumber)
