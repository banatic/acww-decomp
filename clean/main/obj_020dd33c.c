/* The scene object class with vtable 0x020dd33c and its one instance (obj_020dd33c.h). */
#include "obj_020dd33c.h"

#include "autoload_2/heap.h"
#include "autoload_2/sound_emitter_class.h"
#include "clean.h"
#include "main/fish_disp.h"

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

/* The instance's methods: the stage set when `actor` is the first of the actors taking part
 * (0205963c); the first actor made `actor` (0205992c); the mode set when `actor` is the first
 * (020598dc); whether its mode lets an actor away from the point count as near (0205989c);
 * reset (02059ac4). Whether `actor` is the first (func_02057d34). */
extern int func_0205963c(Obj020dd33c *obj, int stage, void *actor); /* the stage kept in a byte */
extern int func_0205992c(Obj020dd33c *obj, void *actor);
extern int func_020598dc(Obj020dd33c *obj, int mode, void *actor);
extern int func_0205989c(Obj020dd33c *obj);
extern void func_02059ac4(Obj020dd33c *obj);
extern int func_02057d34(void *actor);

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
    return func_0205963c(data_021c9350, stage, actor);
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
    return func_0205992c(data_021c9350, actor);
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
    return func_0205989c(obj) != 0 && data_021c9350->unk_d5 == 0;
}
CLEAN_AS(func_02057c68, Obj020dd33c_IsNear)

/* func_02057cb8: when `actor` is the instance's first actor, the item's fish model (if any) is
 * given back and the instance is reset. */
void Obj020dd33c_Finish(void *actor)
{
    if (data_021c9350 == NULL || func_02057d34(actor) != 1) {
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
    return func_020598dc(data_021c9350, mode, actor);
}
CLEAN_AS(func_02057d0c, Obj020dd33c_SetActorMode)
