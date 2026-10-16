/* The scene object class with vtable 0x020dd33c and its one instance (obj_020dd33c.h). */
#include "obj_020dd33c.h"

#include "autoload_2/heap.h"
#include "autoload_2/sound_emitter_class.h"
#include "clean.h"
#include "main/fish_disp.h"
#include "main/item_code.h"
#include "main/scene_query.h"
#include <string.h>
#include "autoload_2/approach.h"
#include "main/sound_emitter.h"
#include "main/villager_data.h"
#include "main/villager_roster.h"
#include "ov004/member_pointer.h"

static_assert(sizeof(Process) == 0x50, "Process size");
static_assert(offsetof(Obj020dd33c, stage) == 0x58, "Obj020dd33c stage");
static_assert(offsetof(Obj020dd33c, point) == 0x60, "Obj020dd33c point");
static_assert(offsetof(Obj020dd33c, reach) == 0xbc, "Obj020dd33c reach");
static_assert(offsetof(Obj020dd33c, mode) == 0xc8, "Obj020dd33c mode");
static_assert(offsetof(Obj020dd33c, actors) == 0xcc, "Obj020dd33c actors");
static_assert(offsetof(Obj020dd33c, actor_mode) == 0xda, "Obj020dd33c actor_mode");
static_assert(sizeof(Obj020dd33c) == 0x11c, "Obj020dd33c size");

/* The class's vtable and the scene objects' root class's. */
extern const u32 data_020dd33c[];
extern const u32 data_020da13c[];

/* The instance, NULL when there is none. */
extern Obj020dd33c *data_021c9350;

/* The instance's reset. */
extern void func_02059ac4(Obj020dd33c *obj);

/* func_02057b34: the destructor: the sound emitter base's, then the root class's. */
void *Obj020dd33c_Destruct(Obj020dd33c *obj)
{
    obj->base.vtable = data_020dd33c;
    SoundEmitterClass_DestructBaseB((SoundEmitterObject *) (void *) obj->emitter);
    obj->base.vtable = data_020da13c;
    Process_Destruct(&obj->base);
    return obj;
}
CLEAN_AS(func_02057b34, Obj020dd33c_Destruct)

/* func_02057b60: the deleting destructor: the object freed to the auxiliary heap. */
void *Obj020dd33c_Delete(Obj020dd33c *obj)
{
    obj->base.vtable = data_020dd33c;
    SoundEmitterClass_DestructBaseB((SoundEmitterObject *) (void *) obj->emitter);
    obj->base.vtable = data_020da13c;
    Process_Destruct(&obj->base);
    Heap_FreeAux(obj);
    return obj;
}
CLEAN_AS(func_02057b60, Obj020dd33c_Delete)

/* func_02057b90: the instance's stage set to `stage` when it is busy and `actor` is its first
 * actor; whether it was. */
int Obj020dd33c_SetStage(int stage, void *actor)
{
    if (data_021c9350 == NULL) {
        return 0;
    }
    return Obj020dd33c_SetStageIfLead(data_021c9350, stage, actor);
}
CLEAN_AS(func_02057b90, Obj020dd33c_SetStage)

/* func_02057bb8: the instance's item, OBJ_020DD33C_NO_ITEM without the instance. */
void Obj020dd33c_Item(u16 *item)
{
    *item = OBJ_020DD33C_NO_ITEM;
    if (data_021c9350 != NULL) {
        *item = data_021c9350->item;
    }
}
CLEAN_AS(func_02057bb8, Obj020dd33c_Item)

/* func_02057bd4: whether the instance is busy (its mode is not 0). */
int Obj020dd33c_IsBusy(void)
{
    return data_021c9350 != NULL && data_021c9350->mode != 0;
}
CLEAN_AS(func_02057bd4, Obj020dd33c_IsBusy)

/* func_02057bf0: whether the instance is in mode `mode` with its byte 0xd9 at 1, or its first
 * actor last set that mode. */
int Obj020dd33c_InMode(int mode)
{
    const Obj020dd33c *obj = data_021c9350;
    if (obj == NULL) {
        return 0;
    }
    return (obj->mode == mode && obj->unk_d9 == 1) || obj->actor_mode == mode;
}
CLEAN_AS(func_02057bf0, Obj020dd33c_InMode)

/* func_02057c20: `actor` made the instance's first actor when it is the second; whether it
 * takes part. */
int Obj020dd33c_Lead(void *actor)
{
    if (data_021c9350 == NULL) {
        return 0;
    }
    return Obj020dd33c_MakeLead(data_021c9350, actor);
}
CLEAN_AS(func_02057c20, Obj020dd33c_Lead)

/* func_02057c44: the instance's point copied to `point`; whether there is an instance. */
int Obj020dd33c_Point(Vec3 *point)
{
    if (data_021c9350 == NULL) {
        return 0;
    }
    *point = data_021c9350->point;
    return 1;
}
CLEAN_AS(func_02057c44, Obj020dd33c_Point)

/* func_02057c68: whether `actor` is near the instance: on the ground plane within its reach of
 * its point, or anywhere while the instance's mode allows it and its byte 0xd5 is 0. */
int Obj020dd33c_IsNear(const Actor *actor)
{
    if (actor == NULL || data_021c9350 == NULL) {
        return 0;
    }
    Obj020dd33c *obj = data_021c9350;
    if (Vec_DistanceXZ(&actor->position, &obj->point) <= obj->reach) {
        return 1;
    }
    return Obj020dd33c_ModeAllowsAway(obj) != 0 && data_021c9350->unk_d5 == 0;
}
CLEAN_AS(func_02057c68, Obj020dd33c_IsNear)

/* func_02057cb8: when `actor` is the instance's first actor, the item's fish model (if any) is
 * given back and the instance is reset. */
void Obj020dd33c_Finish(void *actor)
{
    if (data_021c9350 == NULL || Obj020dd33c_IsLead(actor) != 1) {
        return;
    }
    int model = data_021c9350->fish_model;
    if (model != -1) {
        FishDisp_ReleaseModel(model);
    }
    func_02059ac4(data_021c9350);
}
CLEAN_AS(func_02057cb8, Obj020dd33c_Finish)

/* func_02057cf4: the instance's stage, OBJ_020DD33C_NO_STAGE without the instance. */
u8 Obj020dd33c_Stage(void)
{
    if (data_021c9350 != NULL) {
        return data_021c9350->stage;
    }
    return OBJ_020DD33C_NO_STAGE;
}
CLEAN_AS(func_02057cf4, Obj020dd33c_Stage)

/* func_02057d0c: the mode `mode` set by `actor` when it is the instance's first actor; whether
 * it was. */
int Obj020dd33c_SetActorMode(int mode, void *actor)
{
    if (data_021c9350 == NULL) {
        return 0;
    }
    return Obj020dd33c_SetActorModeIfLead(data_021c9350, mode, actor);
}
CLEAN_AS(func_02057d0c, Obj020dd33c_SetActorMode)

/* func_02057d34: whether `actor` is the instance's first actor; 0 without the instance. */
int Obj020dd33c_IsLead(void *actor)
{
    if (data_021c9350 == NULL) {
        return 0;
    }
    return Obj020dd33c_IsActor(data_021c9350, actor, 0);
}
CLEAN_AS(func_02057d34, Obj020dd33c_IsLead)

/* func_02057d58: the instance started with an item and its actors (Obj020dd33c_Begin); 0
 * either way. */
int Obj020dd33c_Start(u16 *item, int look, int stage, int kind, Actor *first, Actor *second)
{
    if (data_021c9350 == NULL) {
        return 0;
    }
    return Obj020dd33c_Begin(data_021c9350, item, look, (u8) stage, kind, first, second);
}
CLEAN_AS(func_02057d58, Obj020dd33c_Start)

/* Hold offsets by the actor's class (Actor.profile): 0x6b, 0x6a, 0x76 and the rest (which
 * also stands for no actor, as class 0xd8). */
extern const Vec3 data_020cbb10; /* (0, -0x1000, 0) */
extern const Vec3 data_020cbb1c; /* (0, -0x1000, 0x200) */
extern const Vec3 data_020cbb28; /* (0, -0x900, 0x300) */
extern const Vec3 data_020cbb04; /* (0, -0x600, 0) */

/* func_02059598: into `out`, the offset from the place beside actor `index` to where the item
 * is held, by the actor's class.
 * REQUIRES: `index` is 0 or 1 (the game passes 0). */
void Obj020dd33c_HoldOffset(Vec3 *out, Obj020dd33c *obj, int index)
{
    u16 profile = 0xd8;
    const Actor *actor = obj->actors[index];
    if (actor != NULL) {
        profile = actor->profile;
    }
    if (profile == 0x6b) {
        *out = data_020cbb10;
    } else if (profile == 0x6a) {
        *out = data_020cbb1c;
    } else if (profile == 0x76) {
        *out = data_020cbb28;
    } else {
        *out = data_020cbb04;
    }
}
CLEAN_AS(func_02059598, Obj020dd33c_HoldOffset)

extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *sum);

/* func_020595fc: into `out`, `offset` turned to actor `index`'s heading and added to its
 * position; `offset` as it is when there is no such actor. */
void Obj020dd33c_PlaceByActor(Obj020dd33c *obj, Vec3 *out, const Vec3 *offset, unsigned int index)
{
    /* Copied a component at a time, as the original does, so that it reads the same values
     * should `out` overlap `offset`. */
    out->x = offset->x;
    out->y = offset->y;
    out->z = offset->z;
    if (index < 2 && obj->actors[index] != NULL) {
        Vec_RotateY(out, obj->actors[index]->angle[1]);
        VEC_Add(out, &obj->actors[index]->position, out);
    }
}
CLEAN_AS(func_020595fc, Obj020dd33c_PlaceByActor)

/* func_0205963c: the stage set to `stage` when the instance is busy, its movement is not
 * running and `actor` is its first actor; whether it was. */
int Obj020dd33c_SetStageIfLead(Obj020dd33c *obj, u8 stage, void *actor)
{
    if (obj->mode == 0 || obj->unk_d9 == 1) {
        return 0;
    }
    if (Obj020dd33c_IsActor(obj, actor, 0) != 1) {
        return 0;
    }
    obj->stage = stage;
    return 1;
}
CLEAN_AS(func_0205963c, Obj020dd33c_SetStageIfLead)

/* func_02059674: whether the mode's movement runs (1) or is over (0). */
void Obj020dd33c_SetMoving(Obj020dd33c *obj, u8 moving)
{
    obj->unk_d9 = moving;
}
CLEAN_AS(func_02059674, Obj020dd33c_SetMoving)

/* The method at slot 0x5c (word 23) of an actor's vtable: the point it holds things at,
 * written to `out` (for the scene objects, a joint's point; nothing written while that is the
 * origin). */
typedef void (*Obj020dd33cHoldMethod)(Actor *actor, Vec3 *out);
#define OBJ_020DD33C_SLOT_HOLD_POINT 23

/* func_0205967c: into `out`, the first actor's hold point; nothing without a first actor. */
void Obj020dd33c_HoldPoint(Obj020dd33c *obj, Vec3 *out)
{
    Actor *actor = obj->actors[0];
    if (actor != NULL) {
        const u32 *vtable = (const u32 *) actor->vtable;
        ((Obj020dd33cHoldMethod) (uintptr_t) vtable[OBJ_020DD33C_SLOT_HOLD_POINT])(actor, out);
    }
}
CLEAN_AS(func_0205967c, Obj020dd33c_HoldPoint)

/* func_02059694: the item drawn at the point, with the scale and the angles, while a mode
 * runs (below OBJ_020DD33C_MODE_COUNT), there is an item and it is shown. Looked as model 0x27
 * it is drawn as that model, unless it is one of the items 0x155f-0x1564. */
void Obj020dd33c_Draw(Obj020dd33c *obj)
{
    if (obj->mode >= OBJ_020DD33C_MODE_COUNT || obj->item == OBJ_020DD33C_NO_ITEM || obj->shown != 1) {
        return;
    }
    if (obj->look == OBJ_020DD33C_LOOK_MODEL_27 && !(obj->item >= 0x1561 && obj->item <= 0x1564) &&
        !(obj->item >= 0x155f && obj->item <= 0x1560)) {
        Obj020dd33c_DrawModel(obj, 0x27, &obj->point, &obj->scale, obj->rotation);
        return;
    }
    Obj020dd33c_DrawItem(obj, &obj->item, &obj->point, &obj->scale, obj->rotation);
}
CLEAN_AS(func_02059694, Obj020dd33c_Draw)

/* 0 while the field's code is overlay 3's, else overlay 4's is used (the test the pockets
 * scene makes too). */
extern u8 data_020e54a8;
/* Each overlay's drawing of a model by number and of an item by its code, from a position and
 * a scale (copies) and three angles. */
extern void func_ov003_022246c8(int model, Vec3 *position, Vec3 *scale, int x, int y, int z);
extern void func_ov004_02233b5c(int model, Vec3 *position, Vec3 *scale, int x, int y, int z);
extern void func_ov003_02224678(int item, Vec3 *position, Vec3 *scale, int x, int y, int z);
extern void func_ov004_02233b10(int item, Vec3 *position, Vec3 *scale, int x, int y, int z);

/* func_0205971c: model `model` drawn at `position` with `scale` and `rotation`, by overlay 3
 * when data_020e54a8 is 0, else by overlay 4. */
void Obj020dd33c_DrawModel(Obj020dd33c *obj, int model, const Vec3 *position, const Vec3 *scale, const s16 *rotation)
{
    (void) obj;
    Vec3 at = *position;
    Vec3 size = *scale;
    if (data_020e54a8 == 0) {
        func_ov003_022246c8(model, &at, &size, rotation[0], rotation[1], rotation[2]);
    } else {
        func_ov004_02233b5c(model, &at, &size, rotation[0], rotation[1], rotation[2]);
    }
}
CLEAN_AS(func_0205971c, Obj020dd33c_DrawModel)

/* func_020597a8: the item `item` drawn at `position` with `scale` and `rotation`: a fish by
 * the fish display's model the instance took (when it has one), anything else by overlay 3
 * when data_020e54a8 is 0, else by overlay 4. */
void Obj020dd33c_DrawItem(Obj020dd33c *obj, const u16 *item, const Vec3 *position, const Vec3 *scale, const s16 *rotation)
{
    unsigned int code = *item;
    if (code >= 0x12e8 && code <= 0x131f && obj->fish_model != -1) {
        FishDisp_ShowModel(obj->fish_model, (int) (code - 0x12e8), position, scale, rotation[0], rotation[1], rotation[2], 0,
                           0, 0x1f);
        return;
    }
    Vec3 at = *position;
    Vec3 size = *scale;
    if (data_020e54a8 == 0) {
        func_ov003_02224678(*item, &at, &size, rotation[0], rotation[1], rotation[2]);
    } else {
        func_ov004_02233b10(*item, &at, &size, rotation[0], rotation[1], rotation[2]);
    }
}
CLEAN_AS(func_020597a8, Obj020dd33c_DrawItem)

/* func_0205989c: whether the mode lets an actor anywhere count as near: mode 2, or mode 1 or 7
 * while the instance is not in that mode by Obj020dd33c_InMode. */
int Obj020dd33c_ModeAllowsAway(Obj020dd33c *obj)
{
    if (obj->mode == 2) {
        return 1;
    }
    if (obj->mode == 1) {
        return Obj020dd33c_InMode(1) == 0;
    }
    if (obj->mode == 7) {
        return Obj020dd33c_InMode(7) == 0;
    }
    return 0;
}
CLEAN_AS(func_0205989c, Obj020dd33c_ModeAllowsAway)

/* func_020598dc: the actor mode set to `mode` when `actor` is the first actor; whether it
 * was. */
int Obj020dd33c_SetActorModeIfLead(Obj020dd33c *obj, int mode, void *actor)
{
    if (Obj020dd33c_IsActor(obj, actor, 0) != 1) {
        return 0;
    }
    Obj020dd33c_SetActorModeOf(obj, (u8) mode);
    return 1;
}
CLEAN_AS(func_020598dc, Obj020dd33c_SetActorModeIfLead)

/* The countdown modes 1 and 7 start with (40). */
extern const u8 data_020cbae8;

/* func_02059904: the actor mode set to `mode`; modes 1 and 7 also start the countdown at
 * 0xd5. */
void Obj020dd33c_SetActorModeOf(Obj020dd33c *obj, u8 mode)
{
    obj->actor_mode = mode;
    if (mode == 1 || mode == 7) {
        obj->unk_d5 = data_020cbae8;
    }
}
CLEAN_AS(func_02059904, Obj020dd33c_SetActorModeOf)

/* func_02059920: no actor mode asked for. */
void Obj020dd33c_ClearActorMode(Obj020dd33c *obj)
{
    Obj020dd33c_SetActorModeOf(obj, OBJ_020DD33C_NO_MODE);
}
CLEAN_AS(func_02059920, Obj020dd33c_ClearActorMode)

/* func_0205992c: when `actor` is the second actor, it becomes the first and the first the
 * second; whether `actor` takes part. */
int Obj020dd33c_MakeLead(Obj020dd33c *obj, void *actor)
{
    if (Obj020dd33c_IsActor(obj, actor, 1) == 1) {
        obj->actors[1] = obj->actors[0];
        obj->actors[0] = actor;
        return 1;
    }
    return Obj020dd33c_IsActor(obj, actor, 0) == 1;
}
CLEAN_AS(func_0205992c, Obj020dd33c_MakeLead)

/* The word at 0xdc of a scene object (Base_0203f080): the person it stands for. */
extern unsigned long func_0203efbc(void *object);

/* func_0205996c: whether actor `index` (0 or 1) is there and is the same person as `actor`
 * (their words at 0xdc). */
int Obj020dd33c_IsActor(Obj020dd33c *obj, void *actor, unsigned int index)
{
    if (index >= 2 || obj->actors[index] == NULL) {
        return 0;
    }
    unsigned long person = func_0203efbc(actor);
    return person == func_0203efbc(obj->actors[index]);
}
CLEAN_AS(func_0205996c, Obj020dd33c_IsActor)

/* The reach of the actors' nearness: 0x4000 in scenes 9 and 0x10 for the item 0x1565 (or a
 * variant of it) looked as itself and for the items 0x1492-0x14fd looked as model 0x27; 0x1500
 * otherwise. */
extern const fx32 data_020cbaf8;
extern const fx32 data_020cbafc;

/* func_020599a8: when the instance is idle and there is a first actor: the item, its look, the
 * stage, the kind and the two actors kept, the reach set, and a fish display model taken for a
 * fish. 0 either way. */
int Obj020dd33c_Begin(Obj020dd33c *obj, u16 *item, int look, u8 stage, int kind, Actor *first, Actor *second)
{
    if (obj->mode != 0 || first == NULL) {
        return 0;
    }
    obj->item = *item;
    obj->look = look;
    obj->stage = stage;
    obj->kind = kind;
    obj->actors[0] = first;
    obj->actors[1] = second;

    int is_1565;
    if (ItemCode_HasVariant(&obj->item)) {
        ItemCode other = 0x1565;
        int variant = ItemCode_VariantItem(&obj->item);
        is_1565 = variant == ItemCode_VariantItem(&other);
    } else {
        is_1565 = obj->item == 0x1565;
    }
    int wide =
        (is_1565 && obj->look == 0) || (obj->item >= 0x1492 && obj->item <= 0x14fd && obj->look == OBJ_020DD33C_LOOK_MODEL_27);
    if (wide && (SceneQuery_Current() == 9 || SceneQuery_Current() == 0x10)) {
        obj->reach = data_020cbaf8;
    } else {
        obj->reach = data_020cbafc;
    }
    if (obj->item >= 0x12e8 && obj->item <= 0x131f) {
        obj->fish_model = FishDisp_TakeModel();
    }
    return 0;
}
CLEAN_AS(func_020599a8, Obj020dd33c_Begin)

/* ---- The process's own steps */

/* func_02059ac4: the instance back to idle: no mode and no actors, no item, stage
 * OBJ_020DD33C_NO_STAGE, no actor mode, the offsets and the scale at 0, not shown nor moving,
 * the usual reach and no fish model. */
void Obj020dd33c_Reset(Obj020dd33c *obj)
{
    obj->mode = 0;
    for (int i = 0; i < 2; i++) {
        obj->actors[i] = NULL;
    }
    obj->item = OBJ_020DD33C_NO_ITEM;
    obj->stage = OBJ_020DD33C_NO_STAGE;
    obj->frames = 0;
    obj->phase = 0;
    Obj020dd33c_ClearActorMode(obj);
    obj->velocity.x = 0;
    obj->velocity.y = 0;
    obj->velocity.z = 0;
    obj->offset.x = 0;
    obj->offset.y = 0;
    obj->offset.z = 0;
    obj->scale.x = 0;
    obj->scale.y = 0;
    obj->scale.z = 0;
    obj->shown = 0;
    Obj020dd33c_SetMoving(obj, 0);
    obj->reach = data_020cbafc;
    obj->fish_model = -1;
}
CLEAN_AS(func_02059ac4, Obj020dd33c_Reset)

/* func_02059b5c: the draw step: the item drawn (Obj020dd33c_Draw); always 1. */
int Obj020dd33c_DrawStep(Obj020dd33c *obj)
{
    Obj020dd33c_Draw(obj);
    return 1;
}
CLEAN_AS(func_02059b5c, Obj020dd33c_DrawStep)

/* The mode handlers by mode, kind, and Enter or Update (obj_020dd33c_modes.c); a handler
 * whose function word is 0 is not there. */
#define OBJ_020DD33C_ENTER 0
#define OBJ_020DD33C_UPDATE 1
extern MemberPointer data_021c9460[OBJ_020DD33C_MODE_COUNT][2][2];

/* func_02059b6c: the execute step, for a kind of 0 or 1 (nothing for another). A mode the
 * first actor asked for (actor_mode below OBJ_020DD33C_MODE_COUNT) becomes the mode, from
 * frame 0, its Enter handler runs and the request is cleared. Then, in a mode below
 * OBJ_020DD33C_MODE_COUNT, its Update handler runs and the sound emitter is moved to the
 * point. While the mode lets an actor anywhere count as near, the countdown at 0xd5 ticks.
 * Always 1. */
int Obj020dd33c_ExecuteStep(Obj020dd33c *obj)
{
    if (obj->kind < 0 || obj->kind >= 2) {
        return 1;
    }
    if (obj->actor_mode < OBJ_020DD33C_MODE_COUNT) {
        obj->mode = obj->actor_mode;
        obj->frames = 0;
        const MemberPointer *enter = &data_021c9460[obj->mode][obj->kind][OBJ_020DD33C_ENTER];
        if (enter->function != 0) {
            MemberPointer_CallVoid(enter, obj);
        }
        Obj020dd33c_ClearActorMode(obj);
    }
    if (obj->mode < OBJ_020DD33C_MODE_COUNT) {
        const MemberPointer *update = &data_021c9460[obj->mode][obj->kind][OBJ_020DD33C_UPDATE];
        if (update->function != 0) {
            MemberPointer_CallVoid(update, obj);
            Vec3 at = obj->point;
            SoundEmitter_UpdateAtB((SoundEmitter *) (void *) obj->emitter, &at);
        }
    }
    if (Obj020dd33c_ModeAllowsAway(obj) != 0) {
        Countdown_Tick8(&obj->unk_d5);
    }
    return 1;
}
CLEAN_AS(func_02059b6c, Obj020dd33c_ExecuteStep)

/* func_02059c40: the delete step: the instance's sound emitter's slot 0x10 called, and there
 * is no instance any more. Always 1.
 * REQUIRES: there is an instance (it is the object being deleted). */
int Obj020dd33c_DeleteStep(void)
{
    SoundEmitter_Vfunc10B((SoundEmitter *) (void *) data_021c9350->emitter);
    data_021c9350 = NULL;
    return 1;
}
CLEAN_AS(func_02059c40, Obj020dd33c_DeleteStep)

/* func_02059c60: the create step: the object reset, its sound emitter stopped, and it is the
 * instance. Always 1. */
int Obj020dd33c_CreateStep(Obj020dd33c *obj)
{
    Obj020dd33c_Reset(obj);
    SoundEmitter_StopB((SoundEmitter *) (void *) obj->emitter);
    data_021c9350 = obj;
    return 1;
}
CLEAN_AS(func_02059c60, Obj020dd33c_CreateStep)

/* func_02059c80: a new object from the auxiliary heap (zeroed): a process, given the scene
 * objects' root vtable and then the class's, with no item and its sound emitter base made;
 * NULL when there was no room. */
Obj020dd33c *Obj020dd33c_New(void)
{
    Obj020dd33c *obj = Heap_AllocAuxZeroed(sizeof(Obj020dd33c));
    if (obj != NULL) {
        Process_Construct(&obj->base);
        obj->base.vtable = data_020da13c;
        obj->base.vtable = data_020dd33c;
        obj->item = OBJ_020DD33C_NO_ITEM;
        SoundEmitterClass_ConstructBaseB((SoundEmitterObject *) (void *) obj->emitter);
    }
    return obj;
}
CLEAN_AS(func_02059c80, Obj020dd33c_New)

/* ---- Where a held fish goes */

/* The offsets of a held fish by holder shape, each an array by offset class. */
extern Obj020dd33cFishOffsets *const data_020dd31c[];
/* The size factor (20.12) of a held fish by offset class. */
extern const u32 data_020cbb44[];

/* The actor class (Actor.profile) whose holders always take the default shape. */
#define OBJ_020DD33C_DEFAULT_SHAPE_PROFILE 9

static int holder_shape(Actor *holder)
{
    if (holder->profile == OBJ_020DD33C_DEFAULT_SHAPE_PROFILE) {
        return OBJ_020DD33C_SHAPE_DEFAULT;
    }
    return Obj020dd33c_HolderShape(holder);
}

/* func_02059cc4: the second offset of offset class `offset_class` for `holder`'s shape. */
Vec3 *Obj020dd33c_FishSecondOffset(Actor *holder, int offset_class)
{
    return &data_020dd31c[holder_shape(holder)][offset_class].second;
}
CLEAN_AS(func_02059cc4, Obj020dd33c_FishSecondOffset)

/* func_02059cf8: the first offset of offset class `offset_class` for `holder`'s shape. */
Vec3 *Obj020dd33c_FishFirstOffset(Actor *holder, int offset_class)
{
    return &data_020dd31c[holder_shape(holder)][offset_class].first;
}
CLEAN_AS(func_02059cf8, Obj020dd33c_FishFirstOffset)

/* The town's villagers. */
extern VillagerTown data_021e5a2c;

/* func_02059d28: the shape of `holder`, by the code in the low halfword of its word at 0x08:
 * for 0xe000 + a villager's place, by the species of the villager there; three special
 * characters (0xd00c, 0xd013, and 0xd012 or 0xd025) have their own; anything else the
 * default.
 * QUIRK: an empty villager place is asked for its species all the same. */
int Obj020dd33c_HolderShape(Actor *holder)
{
    u32 word;
    memcpy(&word, holder->unk_08, sizeof(word));
    u16 code = (u16) word;
    int shape = OBJ_020DD33C_SHAPE_DEFAULT;

    switch (code >> 12) {
        case 0xe:
            switch (VillagerData_Species(VillagerRoster_At(&data_021e5a2c, code & 0x0fff))) {
                case 0:
                case 5:
                case 6:
                case 10:
                case 12:
                case 15:
                case 16:
                case 21:
                case 25:
                case 31:
                case 32:
                    shape = OBJ_020DD33C_SHAPE_SPECIES_A;
                    break;
                case 1:
                case 2:
                case 4:
                case 7:
                case 9:
                case 13:
                case 14:
                case 17:
                case 19:
                case 20:
                case 22:
                case 23:
                case 26:
                case 27:
                case 29:
                    shape = OBJ_020DD33C_SHAPE_SPECIES_B;
                    break;
                default:
                    break;
            }
            break;
        case 0xd:
            switch (code) {
                case 0xd00c:
                    shape = OBJ_020DD33C_SHAPE_D00C;
                    break;
                case 0xd013:
                    shape = OBJ_020DD33C_SHAPE_D013;
                    break;
                case 0xd012:
                case 0xd025:
                    shape = OBJ_020DD33C_SHAPE_D012;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return shape;
}
CLEAN_AS(func_02059d28, Obj020dd33c_HolderShape)

/* func_02059e10: the size factor of a held fish of offset class `offset_class`.
 * REQUIRES: offset_class is one of the creature table's (0-6). */
u32 Obj020dd33c_FishScale(u32 offset_class)
{
    return data_020cbb44[offset_class];
}
CLEAN_AS(func_02059e10, Obj020dd33c_FishScale)
