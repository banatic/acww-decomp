/* The body of the destructor of the scene object class 0x020d8c64 (obj_020d8c64.h), which the
 * destructors of its derived classes run inline after their own members: the class's vtable,
 * then its members from the last to the first (the sound emitter at 0x514 getting its own
 * class's vtable first) and the base (SceneObjectBase_DestructBase). */
#ifndef CLEAN_MAIN_SCENE_OBJECT_MEMBERS_H
#define CLEAN_MAIN_SCENE_OBJECT_MEMBERS_H

#include "act_effects.h"
#include "autoload_2/sound_emitter_class.h"
#include "field_body.h"
#include "field_collision.h"
#include "footsteps.h"
#include "layered_model.h"
#include "scene_action.h"
#include "scene_face.h"
#include "scene_look.h"
#include "scene_motion_request.h"
#include "scene_mover.h"
#include "scene_object_base.h"
#include "scene_standard_anims.h"
#include "scene_talk_state.h"
#include "speaker_anim.h"
#include "types.h"

/* The vtables of the class and of its sound emitter's class. */
extern const u8 data_020d8c64[];
extern const u8 data_020d8414[];

static inline void SceneObjectMembers_Destruct(u8 *object)
{
    *(const u8 **) (void *) object = data_020d8c64;
    SceneAction_Destruct((SceneAction *) (void *) (object + 0x618));
    SceneMotion_Destruct((SceneMotion *) (void *) (object + 0x564));
    Footsteps_Destruct((Footsteps *) (void *) (object + 0x558));
    *(const u8 **) (void *) (object + 0x514) = data_020d8414;
    SoundEmitterClass_DestructBase((SoundEmitterObject *) (void *) (object + 0x514));
    FieldOwnedBody_Destruct2((FieldOwnedBody *) (void *) (object + 0x4cc));
    CollisionContacts_Destroy((CollisionContacts *) (void *) (object + 0x49c));
    ActEffects_Destruct((ActEffects *) (void *) (object + 0x420));
    SceneTalkState_Destruct((SceneTalkState *) (void *) (object + 0x418));
    SceneLook_Destruct((SceneLook *) (void *) (object + 0x3b0));
    SceneMover_Destruct((SceneMover *) (void *) (object + 0x350));
    SpeakerAnim_Destruct((SpeakerAnim *) (void *) (object + 0x334));
    SceneFace_Destruct((SceneFace *) (void *) (object + 0x2ac));
    SceneStandardAnims_Destruct((SceneStandardAnims *) (void *) (object + 0x2a0));
    LayeredModel_DestructB((LayeredModel *) (void *) (object + 0xec));
    SceneObjectBase_DestructBase((SceneObjectBase *) (void *) object);
}

#endif
