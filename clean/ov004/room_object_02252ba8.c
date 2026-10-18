/* The room objects of vtable 0x02252ba8 (room_object_02252ba8.h). */
#include "room_object_02252ba8.h"

#include <stdint.h>

#include "clean.h"
#include "furniture_model.h"
#include "main/session.h"
#include "main/sound.h"
#include "member_pointer.h"
#include "room_object_anims.h"
#include "room_object_body.h"
#include "room_object_life.h"
#include "room_object_parts.h"
#include "furniture_mover.h"
#include "furniture_sounds.h"
#include "main/actor_table.h"
#include "main/animated_model.h"
#include "main/model_object.h"
#include "main/model_pool.h"
#include "main/room_cells.h"
#include "main/room_sync.h"
#include "main/scene_query.h"
#include "room_manager.h"

static_assert(offsetof(RoomObject02252ba8, cue) == 0x844, "cue");
static_assert(offsetof(RoomObject02252ba8, cue_ready) == 0x858, "cue ready");
static_assert(offsetof(RoomObject02252ba8, frames) == 0x85c, "frames");
static_assert(offsetof(RoomObject02252ba8, countdown) == 0x860, "countdown");
static_assert(offsetof(RoomObject02252ba8, state) == 0x862, "state");
static_assert(sizeof(RoomObject02252ba8) == 0x864, "the size RoomObject02252ba8_Create allocates");

#define ROOM_OBJECT_02252BA8_SIZE 0x864
#define ONE 0x1000         /* normal speed, 20.12 fixed point */
#define ANIM_MODE_LOOP 0   /* start again at the end */
#define ANIM_MODE_ONCE 1   /* stop at the end */
#define SLOT_70_VALUE 0xff /* the second argument given with a state (vtable slot 0x70) */
#define NO_STEP 0xff       /* RoomObject.unk_77C without a step */
#define STEP_MASK 0xf      /* the steps of the cue: 0-15 */
#define CUE_OFF 0          /* SoundCue_SetMode: off */
#define CUE_PLAY 1         /* start playing */
#define CUE_WAIT 2         /* wait for the step SoundCue_SetTarget gives */
#define BLEND_FRAMES 0x20  /* func_02054cac's value for the model's 0xb8 when OFF is entered */

/* The state tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov004_02257094;
extern MemberPointer data_ov004_022572ac[ROOM_OBJECT_02252BA8_STATE_COUNT];
extern const MemberPointer data_ov004_02250330, data_ov004_02250328, data_ov004_02250320;
extern u32 data_ov004_02257038;
extern MemberPointer data_ov004_02257294[ROOM_OBJECT_02252BA8_STATE_COUNT];
extern const MemberPointer data_ov004_02250260, data_ov004_02250350, data_ov004_02250500;

/* Whether each state shows the object on (for vtable slot 0x74): STARTING and PLAYING do. */
extern const u8 data_ov004_02247678[ROOM_OBJECT_02252BA8_STATE_COUNT];

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_02252ba8[];
extern const u8 data_ov004_02252c54[];

extern NetSession *data_020ccf94; /* the session */

/* The mover's animation for the joints. */
static const AnimFile *RoomObject02252ba8_mover_anim(void *mover)
{
    return (const AnimFile *) (uintptr_t) (u32) FurnitureMover_IdleAnim(mover);
}

/* The joint animation of variant 0 of the furniture's archive. */
static const AnimFile *RoomObject02252ba8_joint_anim(RoomObject02252ba8 *object)
{
    return (const AnimFile *) (uintptr_t) (u32) AnimSet_Anim00(FurnitureModel_Anims(&object->base.model_files), 0);
}

/* Hands a change of the switch on, from the object's position. */
static void RoomObject02252ba8_hand_on(RoomObject02252ba8 *object)
{
    int scene = SceneQuery_Current();
    RoomSync_ToggleSwitchAtPoint(scene, &object->base.position, RoomObject_Layer(&object->base));
}

/* func_ov004_02214c50 (update of PLAYING): the cue's update at the position; when it gives a
 * frame (not negative), the joints take the joint animation at that frame, its whole part as the
 * frame and its fraction as the speed, and advance. When the switch was asked to change, it is
 * set on and the change handed on. */
void RoomObject02252ba8_UpdatePlaying(RoomObject02252ba8 *object)
{
    int frame = RoomObject02252ba8_UpdateCue(object, &object->base.position);
    if (frame >= 0) {
        AnimatedModel_Start(&object->base.model, (const u8 *) RoomObject02252ba8_joint_anim(object), ANIM_MODE_LOOP,
                            frame & 0xfff, (u16) (frame >> 12), 0);
        AnimatedModel_Update(&object->base.model);
    }
    if (Switch_IsPending(&object->base.light_switch)) {
        Switch_Set(&object->base.light_switch, 1, 0);
        RoomObject02252ba8_hand_on(object);
    }
}
CLEAN_AS(func_ov004_02214c50, RoomObject02252ba8_UpdatePlaying)

/* func_ov004_02214cd8 (entry of PLAYING): the switch on, at once; the animations of variant 0
 * looped from the start, and the joint animation of variant 0 held (speed 0) at frame 0. */
int RoomObject02252ba8_EnterPlaying(RoomObject02252ba8 *object)
{
    Switch_Set(&object->base.light_switch, 1, 0);
    RoomObject_PlayAnimsFrom(&object->base, 0, ANIM_MODE_LOOP, ONE, 0);
    AnimatedModel_Start(&object->base.model, (const u8 *) RoomObject02252ba8_joint_anim(object), ANIM_MODE_LOOP, 0, 0, 0);
    return 1;
}
CLEAN_AS(func_ov004_02214cd8, RoomObject02252ba8_EnterPlaying)

/* func_ov004_02214d34 (update of STARTING): the cue's update at the position; while the
 * countdown runs the joint animation advances and it counts down; at 0 PLAYING is entered (with
 * vtable slot 0x78's value), else the cue's start, when it gives one, sets the countdown and
 * holds the joints at frame 0 with that value at the model's 0xb8. When the switch was asked
 * to change, it is set on and the change handed on. */
void RoomObject02252ba8_UpdateStarting(RoomObject02252ba8 *object)
{
    RoomObject *base = &object->base;
    RoomObject02252ba8_UpdateCue(object, &base->position);
    if (object->countdown != 0) {
        AnimatedModel_Update(&base->model);
        object->countdown = (u16) (object->countdown - 1);
    }
    if (object->countdown == 0) {
        int value = base->vtable->vfunc_78(base);
        base->vtable->vfunc_70(base, ROOM_OBJECT_02252BA8_PLAYING, value);
    } else {
        int start = RoomObject02252ba8_CueStart(object);
        if (start >= 0) {
            object->countdown = (u16) start;
            AnimatedModel_Play(&base->model, (const u8 *) RoomObject02252ba8_joint_anim(object), (u16) start, 0, 0, 0, 0);
        }
    }
    if (Switch_IsPending(&base->light_switch)) {
        Switch_Set(&base->light_switch, 1, 0);
        RoomObject02252ba8_hand_on(object);
    }
}
CLEAN_AS(func_ov004_02214d34, RoomObject02252ba8_UpdateStarting)

/* The end of each way into STARTING: the joints take `file` at frame 0, held, and advance. */
static void RoomObject02252ba8_hold_joints(RoomObject02252ba8 *object, const AnimFile *file)
{
    AnimatedModel_Start(&object->base.model, (const u8 *) file, ANIM_MODE_LOOP, 0, 0, 0);
    AnimatedModel_Update(&object->base.model);
}

/* func_ov004_02214df8 (entry of STARTING): the sound at 2, the switch on, at once, and the
 * countdown at 0xffff. Then, by the tile it is on:
 * - while its model is being bound (RoomObject.unk_77E) in the mode given (unk_76C not 0) or
 *   where SceneQuery_CurrentIn11 says so: the cue plays (even when it was not set up) and its step goes
 *   to the cell and to unk_77C; the joints take the archive's animation; the countdown at 0;
 * - while its model is being bound otherwise: the cue waits for the step the cell keeps, which
 *   goes to unk_77C; the joints take the mover's animation;
 * - when the session is linked and vtable slot 0x78 gives a step: the cue plays and that step
 *   goes to the cell (unk_77C stays); the joints take the mover's animation;
 * - else: the cue plays and its step goes to the cell and to unk_77C; the joints take the
 *   mover's animation.
 * REQUIRES: but in the first case the mover exists (FurnitureMover_IdleAnim is given its NULL). */
int RoomObject02252ba8_EnterStarting(RoomObject02252ba8 *object)
{
    RoomObject *base = &object->base;
    int x, y;
    int step;
    RoomObject_PlaySound1(base);
    Switch_Set(&base->light_switch, 1, 0);
    object->countdown = 0xffff;
    Position_Tile(&x, &y, (const Position *) (const void *) &base->position);
    if (base->unk_77E != 0) {
        if (base->unk_76C != 0 || SceneQuery_CurrentIn11() != 0) {
            SoundCue_SetMode(object->cue, CUE_PLAY);
            step = SoundCue_ReadVariable((char *) object->cue) & STEP_MASK;
            RoomCells_SetStep(x, y, (u8) step, SceneQuery_Current());
            base->unk_77C = (u8) step;
            RoomObject02252ba8_hold_joints(object, RoomObject02252ba8_joint_anim(object));
            object->countdown = 0;
        } else {
            RoomObject02252ba8_CueSetMode(object, CUE_WAIT);
            step = RoomCells_GetStep(x, y, SceneQuery_Current()) & STEP_MASK;
            RoomObject02252ba8_CueSetTarget(object, (u8) step);
            base->unk_77C = (u8) step;
            RoomObject02252ba8_hold_joints(object, RoomObject02252ba8_mover_anim(RoomManager_Mover()));
        }
    } else if (Session_IsLinked(data_020ccf94) != 0 && base->vtable->vfunc_78(base) != NO_STEP) {
        RoomObject02252ba8_CueSetMode(object, CUE_PLAY);
        step = base->vtable->vfunc_78(base);
        RoomCells_SetStep(x, y, (u8) (step & STEP_MASK), SceneQuery_Current());
        RoomObject02252ba8_hold_joints(object, RoomObject02252ba8_mover_anim(RoomManager_Mover()));
    } else {
        RoomObject02252ba8_CueSetMode(object, CUE_PLAY);
        step = RoomObject02252ba8_CueStep(object) & STEP_MASK;
        RoomCells_SetStep(x, y, (u8) step, SceneQuery_Current());
        base->unk_77C = (u8) step;
        RoomObject02252ba8_hold_joints(object, RoomObject02252ba8_mover_anim(RoomManager_Mover()));
    }
    return 1;
}
CLEAN_AS(func_ov004_02214df8, RoomObject02252ba8_EnterStarting)

/* func_ov004_02214fc8 (update of OFF): the cue's update at the position and the joint
 * animation advanced. When the switch was asked to change, it is set off and the change handed
 * on. */
void RoomObject02252ba8_UpdateOff(RoomObject02252ba8 *object)
{
    RoomObject02252ba8_UpdateCue(object, &object->base.position);
    AnimatedModel_Update(&object->base.model);
    if (Switch_IsPending(&object->base.light_switch)) {
        Switch_Set(&object->base.light_switch, 0, 0);
        RoomObject02252ba8_hand_on(object);
    }
}
CLEAN_AS(func_ov004_02214fc8, RoomObject02252ba8_UpdateOff)

/* func_ov004_02215020 (entry of OFF): no step (unk_77C), RoomCells_ClearStep at its tile, the cue
 * off, the sound at 4 and the switch off, at once. With the mover the joints take its
 * animation, held at frame 0: at once while the model is being bound, else with the value 0x20
 * at the model's 0xb8. */
int RoomObject02252ba8_EnterOff(RoomObject02252ba8 *object)
{
    RoomObject *base = &object->base;
    int x, y;
    Position_Tile(&x, &y, (const Position *) (const void *) &base->position);
    base->unk_77C = NO_STEP;
    RoomCells_ClearStep(x, y, SceneQuery_Current());
    RoomObject02252ba8_CueSetMode(object, CUE_OFF);
    RoomObject_PlaySound2(base);
    Switch_Set(&base->light_switch, 0, 0);
    if (RoomManager_Mover() != NULL) {
        const AnimFile *file = RoomObject02252ba8_mover_anim(RoomManager_Mover());
        if (base->unk_77E != 0) {
            AnimatedModel_Start(&base->model, (const u8 *) file, ANIM_MODE_LOOP, 0, 0, 0);
        } else {
            AnimatedModel_Play(&base->model, (const u8 *) file, BLEND_FRAMES, ANIM_MODE_LOOP, 0, 0, 0);
        }
    }
    return 1;
}
CLEAN_AS(func_ov004_02215020, RoomObject02252ba8_EnterOff)

/* _ZN18Obj_ov004_02252ba819func_ov004_022150b8Ev: the state's update, through its table. */
void RoomObject02252ba8_UpdateState(RoomObject02252ba8 *object)
{
    static const MemberPointer *const updates[ROOM_OBJECT_02252BA8_STATE_COUNT] = {
        &data_ov004_02250330, /* RoomObject02252ba8_UpdateOff */
        &data_ov004_02250328, /* RoomObject02252ba8_UpdateStarting */
        &data_ov004_02250320, /* RoomObject02252ba8_UpdatePlaying */
    };
    MemberTable_InitOnce(&data_ov004_02257094, data_ov004_022572ac, updates, ROOM_OBJECT_02252BA8_STATE_COUNT);
    if (object->state < ROOM_OBJECT_02252BA8_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov004_022572ac[object->state], object);
    }
}
CLEAN_AS(_ZN18Obj_ov004_02252ba819func_ov004_022150b8Ev, RoomObject02252ba8_UpdateState)

/* func_ov004_02215134 (vtable slot 0x70): the base class's (RoomObject_SetUnk77C, given
 * `state` and `value`), then enters `state` if its entry (through a table) agrees; whether it
 * did. States 3 and above do not exist. */
int RoomObject02252ba8_EnterState(RoomObject02252ba8 *object, unsigned int state, int value)
{
    static const MemberPointer *const entries[ROOM_OBJECT_02252BA8_STATE_COUNT] = {
        &data_ov004_02250260, /* RoomObject02252ba8_EnterOff */
        &data_ov004_02250350, /* RoomObject02252ba8_EnterStarting */
        &data_ov004_02250500, /* RoomObject02252ba8_EnterPlaying */
    };
    RoomObject_SetUnk77C(&object->base, (int) state, value);
    MemberTable_InitOnce(&data_ov004_02257038, data_ov004_02257294, entries, ROOM_OBJECT_02252BA8_STATE_COUNT);
    if (state < ROOM_OBJECT_02252BA8_STATE_COUNT && MemberPointer_CallInt(&data_ov004_02257294[state], object) != 0) {
        object->state = (u8) state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_02215134, RoomObject02252ba8_EnterState)

/* func_ov004_022151c4 (vtable slot 0x74): whether `state` shows the object on (STARTING and
 * PLAYING do); 0 for a state that does not exist. */
u8 RoomObject02252ba8_StateIsOn(RoomObject02252ba8 *object, unsigned int state)
{
    (void) object;
    if (state < ROOM_OBJECT_02252BA8_STATE_COUNT) {
        return data_ov004_02247678[state];
    }
    return 0;
}
CLEAN_AS(func_ov004_022151c4, RoomObject02252ba8_StateIsOn)

/* func_ov004_022151d8: the cue's start (SoundCue_TakeStart), -1 when it was not set up. */
int RoomObject02252ba8_CueStart(RoomObject02252ba8 *object)
{
    if (object->cue_ready != 0) {
        return SoundCue_TakeStart(object->cue);
    }
    return -1;
}
CLEAN_AS(func_ov004_022151d8, RoomObject02252ba8_CueStart)

/* func_ov004_02215200: the cue's step (SoundCue_ReadVariable), 0 when it was not set up. */
int RoomObject02252ba8_CueStep(RoomObject02252ba8 *object)
{
    if (object->cue_ready != 0) {
        return SoundCue_ReadVariable((char *) object->cue);
    }
    return 0;
}
CLEAN_AS(func_ov004_02215200, RoomObject02252ba8_CueStep)

/* func_ov004_02215228: the step the cue waits for, when it was set up. */
void RoomObject02252ba8_CueSetTarget(RoomObject02252ba8 *object, int value)
{
    if (object->cue_ready != 0) {
        SoundCue_SetTarget(object->cue, value);
    }
}
CLEAN_AS(func_ov004_02215228, RoomObject02252ba8_CueSetTarget)

/* func_ov004_0221524c: the cue's mode, when it was set up. */
void RoomObject02252ba8_CueSetMode(RoomObject02252ba8 *object, int mode)
{
    if (object->cue_ready != 0) {
        SoundCue_SetMode(object->cue, mode);
    }
}
CLEAN_AS(func_ov004_0221524c, RoomObject02252ba8_CueSetMode)

/* func_ov004_02215270: stops the cue and takes it down, when it was set up.
 * QUIRK: then it gives 0x858 (the offset of cue_ready), else 0. */
int RoomObject02252ba8_StopCue(RoomObject02252ba8 *object)
{
    if (object->cue_ready != 0) {
        SoundCue_Stop(object->cue);
        object->cue_ready = 0;
        return (int) offsetof(RoomObject02252ba8, cue_ready);
    }
    return object->cue_ready;
}
CLEAN_AS(func_ov004_02215270, RoomObject02252ba8_StopCue)

/* func_ov004_02215298: the cue's update at a copy of `point` (SoundCue_UpdateAt), -1 when it
 * was not set up. */
int RoomObject02252ba8_UpdateCue(RoomObject02252ba8 *object, const Vec3 *point)
{
    if (object->cue_ready != 0) {
        Vec3 copy = *point;
        return SoundCue_UpdateAt(object->cue, &copy);
    }
    return -1;
}
CLEAN_AS(func_ov004_02215298, RoomObject02252ba8_UpdateCue)

/* func_ov004_022152d0: sets the cue up for `sound`, when it was not.
 * QUIRK: then it gives 0x858 (the offset of cue_ready), else cue_ready. */
int RoomObject02252ba8_InitCue(RoomObject02252ba8 *object, u16 sound)
{
    if (object->cue_ready == 0) {
        SoundCue_Init(object->cue, sound);
        object->cue_ready = 1;
        return (int) offsetof(RoomObject02252ba8, cue_ready);
    }
    return object->cue_ready;
}
CLEAN_AS(func_ov004_022152d0, RoomObject02252ba8_InitCue)

/* A node of the model's resource (NitroSystem's NNSG3dResNodeData): a head, then its
 * translation. */
typedef struct RoomObject02252ba8NodeData {
    u16 flags;
    u16 unk_02;
    Vec3 translation;
} RoomObject02252ba8NodeData;

/* The joint being drawn (NitroSystem's NNSG3dJntAnmResult): its translation at 0x4c. */
typedef struct RoomObject02252ba8Joint {
    u8 unk_00[0x4c]; /* its flags, scales and rotation */
    Vec3 translation;
} RoomObject02252ba8Joint;

/* The render state seen as far as 0xd4 (NodeHookState runs to 0xbc): the model's node
 * dictionary (NitroSystem's NNSG3dResNodeInfo). */
typedef struct RoomObject02252ba8RenderState {
    u8 unk_00[0xb4];
    RoomObject02252ba8Joint *joint;
    u8 unk_b8[0x1c];
    const u8 *node_info;
} RoomObject02252ba8RenderState;

static_assert(offsetof(RoomObject02252ba8RenderState, node_info) == 0xd4, "node info");
static_assert(offsetof(RoomObject02252ba8Joint, translation) == 0x4c, "joint translation");

/* func_ov004_022152f8 (vtable slot 0x6c, the model's hook after a node's description): the
 * joint's translation set back to that of the node `node` in the model's resource (its entry in
 * the dictionary, offset 6 the entries, their size first and the data after a 4-byte head, each
 * an offset from the dictionary to the node), then the model object's own hook
 * (AnimatedModel_AfterNode).
 * REQUIRES: the node's data carries a translation. */
void RoomObject02252ba8_NodeDescAfterHook(RoomObject02252ba8 *object, int node, NodeHookState *state)
{
    const RoomObject02252ba8RenderState *render = (const RoomObject02252ba8RenderState *) (const void *) state;
    const u8 *info = render->node_info;
    u16 entries = *(const u16 *) (info + 6);
    u16 entry_size = *(const u16 *) (info + entries);
    const u8 *entry = info + entries + entry_size * node;
    const RoomObject02252ba8NodeData *data =
        (const RoomObject02252ba8NodeData *) (const void *) (info + *(const s32 *) (entry + 4));
    render->joint->translation = data->translation;
    AnimatedModel_AfterNode(&object->base.model, (AnimatedModelNodeState *) (void *) state);
}
CLEAN_AS(func_ov004_022152f8, RoomObject02252ba8_NodeDescAfterHook)

/* func_ov004_0221533c (vtable slot 0x68, the model's hook for a node's description): the
 * model object's own hook (AnimatedModel_BeforeNode). */
void RoomObject02252ba8_NodeDescHook(RoomObject02252ba8 *object, int node, NodeHookState *state)
{
    (void) node;
    AnimatedModel_BeforeNode(&object->base.model, (AnimatedModelNodeState *) (void *) state);
}
CLEAN_AS(func_ov004_0221533c, RoomObject02252ba8_NodeDescHook)

/* func_ov004_02215350 (vtable slot 0x0c): stops the cue. */
int RoomObject02252ba8_Vfunc0C(RoomObject02252ba8 *object)
{
    RoomObject02252ba8_StopCue(object);
    return 1;
}
CLEAN_AS(func_ov004_02215350, RoomObject02252ba8_Vfunc0C)

/* func_ov004_02215360 (vtable slot 0x84, each frame while appearing or vanishing): the same as
 * while settled (vtable slot 0x80). */
int RoomObject02252ba8_UpdateUnsettled(RoomObject02252ba8 *object)
{
    object->base.vtable->update_settled(&object->base);
    return 1;
}
CLEAN_AS(func_ov004_02215360, RoomObject02252ba8_UpdateUnsettled)

/* _ZN18Obj_ov004_02252ba819func_ov004_02215374Ev (vtable slot 0x80, each frame while neither
 * appearing nor vanishing): the state's update, and one more frame counted. */
int RoomObject02252ba8_Update(RoomObject02252ba8 *object)
{
    RoomObject02252ba8_UpdateState(object);
    object->frames++;
    return 1;
}
CLEAN_AS(_ZN18Obj_ov004_02252ba819func_ov004_02215374Ev, RoomObject02252ba8_Update)

/* func_ov004_02215394 (vtable slot 0x7c, once the model is bound): no frames counted and no
 * step; the cue set up for the sound at 6 of the furniture's row; the animations of variant 0
 * bound to play once from the start; the model's block from the heap of its pool entry
 * (ModelObject_AllocJointResults). Then, in mode 1 (unk_76C), the switch off at once and handed on without a
 * state; for a preview (unk_76C 2) OFF; else STARTING when the switch is on, OFF when off. Done
 * at once. */
int RoomObject02252ba8_Start(RoomObject02252ba8 *object)
{
    RoomObject *base = &object->base;
    object->frames = 0;
    base->unk_77C = NO_STEP;
    RoomObject02252ba8_InitCue(object, (u16) FurnitureSounds_Sound3(RoomObject_Number(base)));
    RoomObject_LoadAnims(base, 0, ANIM_MODE_ONCE, ONE, 0);
    ModelObject_AllocJointResults(
        &base->model.object, (Heap *) (uintptr_t) ModelPoolEntry_Heap((void *) (uintptr_t) (u32) RoomObject_PoolEntry(base)));
    if (base->unk_76C == 1) {
        Switch_Set(&base->light_switch, 0, 0);
        RoomObject02252ba8_hand_on(object);
    } else if (RoomObject_Unk76CIs2(base)) {
        base->vtable->vfunc_70(base, ROOM_OBJECT_02252BA8_OFF, SLOT_70_VALUE);
    } else if (Switch_Value(&base->light_switch) != 0) {
        base->vtable->vfunc_70(base, ROOM_OBJECT_02252BA8_STARTING, SLOT_70_VALUE);
    } else {
        base->vtable->vfunc_70(base, ROOM_OBJECT_02252BA8_OFF, SLOT_70_VALUE);
    }
    return 1;
}
CLEAN_AS(func_ov004_02215394, RoomObject02252ba8_Start)

static void RoomObject02252ba8_set_vtables(RoomObject02252ba8 *object)
{
    object->base.vtable = (const RoomObjectVtable *) data_ov004_02252ba8;
    object->base.receiver_vtable = data_ov004_02252c54;
}

/* func_ov004_02215468 (the deleting destructor, vtable slot 0x44).
 * QUIRK: the cue is not stopped here (vtable slot 0x0c does that). */
RoomObject02252ba8 *RoomObject02252ba8_Delete(RoomObject02252ba8 *object)
{
    RoomObject02252ba8_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    RoomObject_Free(object);
    return object;
}
CLEAN_AS(func_ov004_02215468, RoomObject02252ba8_Delete)

/* func_ov004_02215494 (the destructor, vtable slot 0x40); the same QUIRK. */
RoomObject02252ba8 *RoomObject02252ba8_Destroy(RoomObject02252ba8 *object)
{
    RoomObject02252ba8_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    return object;
}
CLEAN_AS(func_ov004_02215494, RoomObject02252ba8_Destroy)

/* func_ov004_022154b8 (the constructor): the base, this class's vtables, and no step. The
 * rest is left as the allocation zeroed it (OFF, the cue not set up). */
RoomObject02252ba8 *RoomObject02252ba8_Construct(RoomObject02252ba8 *object)
{
    RoomObject_ConstructBase(&object->base);
    RoomObject02252ba8_set_vtables(object);
    object->base.unk_77C = NO_STEP;
    return object;
}
CLEAN_AS(func_ov004_022154b8, RoomObject02252ba8_Construct)

/* func_ov004_022154e8: a new one from the room's heap; nothing when it has no room. */
void RoomObject02252ba8_Create(void)
{
    RoomObject02252ba8 *object = RoomObject_Alloc(ROOM_OBJECT_02252BA8_SIZE);
    if (object != NULL) {
        RoomObject02252ba8_Construct(object);
    }
}
CLEAN_AS(func_ov004_022154e8, RoomObject02252ba8_Create)

/* The receiver part (at 0xec, RoomObject.receiver_vtable) enters RoomObject02252ba8's functions
 * through its vtable with these: each moves the pointer back to the object and goes on with the
 * object's function. */
static RoomObject02252ba8 *RoomObject02252ba8_from_receiver(void *receiver)
{
    return (RoomObject02252ba8 *) (void *) ((u8 *) receiver - offsetof(RoomObject, receiver_vtable));
}

/* func_ov004_0221a8e4: the deleting destructor, entered from the receiver part. */
RoomObject02252ba8 *RoomObject02252ba8Receiver_Delete(void *receiver)
{
    return RoomObject02252ba8_Delete(RoomObject02252ba8_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02252ba8D0Ev, RoomObject02252ba8Receiver_Delete)

/* func_ov004_0221a900: the destructor, entered from the receiver part. */
RoomObject02252ba8 *RoomObject02252ba8Receiver_Destroy(void *receiver)
{
    return RoomObject02252ba8_Destroy(RoomObject02252ba8_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02252ba8D1Ev, RoomObject02252ba8Receiver_Destroy)
