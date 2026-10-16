/* The scene object class with vtable 0x020da088 (special_scene_object.h). */
#include "special_scene_object.h"

#include "actor_table.h"
#include "autoload_2/heap.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "footsteps.h"
#include "link_global.h"
#include "lookups.h"
#include "model_object.h"
#include "npc_lookup.h"
#include "pool_link.h"
#include "resource_pools.h"
#include "scene_object.h"
#include "scene_object_members.h"
#include "scene_share.h"
#include "session.h"

/* The object's parts, by place. */
#define SSO_POSITION 0x05c     /* Vec3 */
#define SSO_ANGLE 0x08e        /* s16: where it faces */
#define SSO_WALK_ANGLE 0x094   /* s16: where it walks */
#define SSO_PERSON 0x0ea       /* ItemCode: the person (kind 0xd) */
#define SSO_MODEL 0x0ec        /* LayeredModel (a ModelObject first) */
#define SSO_FACE 0x2ac         /* SceneFace */
#define SSO_ANIM 0x334         /* SpeakerAnim */
#define SSO_BODY 0x4cc         /* FieldOwnedBody */
#define SSO_FOOTSTEPS 0x558    /* Footsteps */
#define SSO_LOCAL 0x563        /* u8: nonzero: not shared (scene_share.h) */
#define SSO_MOTION 0x564       /* SceneMotion */
#define SSO_HEAP 0x640         /* PoolLink to a heap4 slot */
#define SSO_RADIUS 0x648       /* fx32 */
#define SSO_HEIGHT 0x64c       /* fx32 */
#define SSO_SOUND_PLAYED 0x650 /* u8 */

/* The kind of the person codes of special characters (the code's top four bits), and the
 * first sound of theirs. */
#define SSO_KIND_SPECIAL 0xd
#define SSO_SOUND_FIRST 0xc8
#define SSO_NO_SOUND 0xffff
/* The vtable slot that gives the animation player's speed scale. */
#define SSO_SLOT_ANIM_SPEED 0xa8
/* data_020e54a8's value for the rooms' field. */
#define SSO_FIELD_ROOMS 1

/* The class's vtable. */
extern const u8 data_020da088[];
/* The speed scale of these objects' animation players (data_020c8120 less 0x8000, set when the
 * program starts). */
extern s32 data_021c30ac;
/* The kind of field: 0 the town, 1 the rooms. */
extern u8 data_020e54a8;
extern NetSession *data_020ccf94;
/* The point a shared place is compared with. */
extern Vec3 data_021fbee8;

static u8 *sso_at(void *object, u32 offset)
{
    return (u8 *) object + offset;
}

static PoolLink *sso_heap(void *object)
{
    return (PoolLink *) (void *) sso_at(object, SSO_HEAP);
}

/* func_0202eb88 (slot 0xa8): the speed scale of the animation player.
 * QUIRK: the result is declared a pointer; it holds the scale's value. */
u32 *SpecialSceneObject_AnimSpeed(void *object)
{
    (void) object;
    return (u32 *) (uintptr_t) (u32) data_021c30ac;
}
CLEAN_AS(func_0202eb88, SpecialSceneObject_AnimSpeed)

/* func_0202eb94 (slot 0x84): the sound of an action's start: 0xc8 plus the index (the code's
 * low twelve bits) for a person of kind 0xd, else none (0xffff). */
u16 SpecialSceneObject_ActionSound(const void *object)
{
    u16 person = *(const u16 *) (const void *) ((const u8 *) object + SSO_PERSON);
    if ((person & 0xf000) >> 12 == SSO_KIND_SPECIAL) {
        return (u16) ((person & 0xfff) + SSO_SOUND_FIRST);
    }
    return SSO_NO_SOUND;
}
CLEAN_AS(func_0202eb94, SpecialSceneObject_ActionSound)

/* func_0202ebc0 (slot 0x80): the sound noted as played. */
void SpecialSceneObject_ActionSoundPlayed(u8 *object)
{
    object[SSO_SOUND_PLAYED] = 1;
}
CLEAN_AS(func_0202ebc0, SpecialSceneObject_ActionSoundPlayed)

/* func_0202ebcc (slot 0x7c): whether an action's start has a sound: always, except in the
 * rooms' field once it has played. */
int SpecialSceneObject_HasActionSound(u8 *object)
{
    return data_020e54a8 != SSO_FIELD_ROOMS || object[SSO_SOUND_PLAYED] == 0;
}
CLEAN_AS(func_0202ebcc, SpecialSceneObject_HasActionSound)

/* func_0202ebf8 (slot 0x78): the sort: Lookups_KindDFirst of the person. */
int SpecialSceneObject_Sort(u8 *object)
{
    return Lookups_KindDFirst((const ItemCode *) (const void *) sso_at(object, SSO_PERSON));
}
CLEAN_AS(func_0202ebf8, SpecialSceneObject_Sort)

/* func_0202ec04 (slot 0x74): the person's name into `name` (NpcLookup_FormatPersonName). */
void SpecialSceneObject_NameInto(char *object, char *name)
{
    NpcLookup_FormatPersonName(name, (ItemCode *) (void *) sso_at(object, SSO_PERSON));
}
CLEAN_AS(func_0202ec04, SpecialSceneObject_NameInto)

/* func_0202ec14 (slot 0x0c): the base's leave (SceneObject_Leave), then the heap slot given
 * back; 0 when the base's leave is not done. */
int SpecialSceneObject_Leave(void *object)
{
    if (SceneObject_Leave(object) == 0) {
        return 0;
    }
    PoolLink_Release(sso_heap(object));
    return 1;
}
CLEAN_AS(func_0202ec14, SpecialSceneObject_Leave)

/* func_0202ec38 (slot 0x10): when the base may be deleted, the person's entry of the actor
 * table is removed (Actors_RemoveD); whether it may. */
int SpecialSceneObject_CanDelete(void *object)
{
    if (SceneObjectBase_CanDelete((SceneObjectBase *) object) == 0) {
        return 0;
    }
    Actors_RemoveD((const ItemCode *) (const void *) sso_at(object, SSO_PERSON));
    return 1;
}
CLEAN_AS(func_0202ec38, SpecialSceneObject_CanDelete)

/* func_0202ec58 (slot 0x00): the start. After the base's (SceneObject_Start): while linked
 * with others (and no link scene held, LinkGlobal_HoldsScene) a shared object takes the place
 * and angle the session gives it (SceneShare_ReadPlace) unless that place is data_021fbee8;
 * then a heap slot is taken and the model loaded into it when the object holds none, the face
 * loaded, the animation player set up with the object's speed scale (its slot 0xa8), the motion
 * of kind 0 started, the body set with the object's radius and height, the person added to the
 * actor table and the footsteps enabled. 0 as soon as a step fails (the steps done stay done),
 * else 1. */
int SpecialSceneObject_Start(void *object)
{
    if (SceneObject_Start(object) == 0) {
        return 0;
    }
    if (LinkGlobal_HoldsScene() == 0 && Session_IsLinked(data_020ccf94) != 0 && *sso_at(object, SSO_LOCAL) == 0) {
        Vec3 place = {0, 0, 0};
        s16 angle = 0;
        if (SceneShare_ReadPlace(object, &place, &angle) != 0 && Vec_Differ(&place, &data_021fbee8) != 0) {
            *(Vec3 *) (void *) sso_at(object, SSO_POSITION) = place;
            *(s16 *) (void *) sso_at(object, SSO_ANGLE) = angle;
            *(s16 *) (void *) sso_at(object, SSO_WALK_ANGLE) = angle;
        }
    }
    if (PoolLink_Heap4(sso_heap(object)) == 0) {
        if (PoolLink_Take(sso_heap(object)) == 0) {
            return 0;
        }
        if (SpecialSceneObject_LoadModel(object) == 0) {
            return 0;
        }
    }
    if (SceneFace_Load((SceneFace *) (void *) sso_at(object, SSO_FACE), object) == 0) {
        return 0;
    }
    const u8 *vtable = *(const u8 *const *) object;
    u32 slot = *(const u32 *) (const void *) (vtable + SSO_SLOT_ANIM_SPEED);
    s32 speed = ((s32 (*)(void *))(uintptr_t) slot)(object);
    if (SpeakerAnim_Init((SpeakerAnim *) (void *) sso_at(object, SSO_ANIM), object, speed) == 0) {
        return 0;
    }
    SceneMotion_StartNow((SceneMotion *) (void *) sso_at(object, SSO_MOTION), object, 0, 1, 0, 0, 0, 0, 0);
    FieldOwnedBody_Set((FieldOwnedBody *) (void *) sso_at(object, SSO_BODY), (Actor *) object,
                       *(const fx32 *) (const void *) sso_at(object, SSO_RADIUS),
                       *(const fx32 *) (const void *) sso_at(object, SSO_HEIGHT), 8, 0x2fc, 3,
                       (u8) SceneObject_PersonIndex(object), 0x1000);
    if (Actors_AddD(object, (const ItemCode *) (const void *) sso_at(object, SSO_PERSON)) == 0) {
        return 0;
    }
    Footsteps_Enable((Footsteps *) (void *) sso_at(object, SSO_FOOTSTEPS));
    return 1;
}
CLEAN_AS(func_0202ec58, SpecialSceneObject_Start)

/* func_0202edc8 (slot 0x04): after the base's init (SceneObject_Init): the body's size 1.0 by
 * 2.0 and the sound not played yet. 0 when the base's init fails. */
int SpecialSceneObject_Init(void *object)
{
    if (SceneObject_Init(object) == 0) {
        return 0;
    }
    SpecialSceneObject_SetBodySize(object, 0x1000, 0x2000);
    *sso_at(object, SSO_SOUND_PLAYED) = 0;
    return 1;
}
CLEAN_AS(func_0202edc8, SpecialSceneObject_Init)

/* func_0202edfc: the radius and height the body is set with at the start. */
void SpecialSceneObject_SetBodySize(u8 *object, u32 radius, u32 height)
{
    *(u32 *) (void *) (object + SSO_RADIUS) = radius;
    *(u32 *) (void *) (object + SSO_HEIGHT) = height;
}
CLEAN_AS(func_0202edfc, SpecialSceneObject_SetBodySize)

/* func_0202ee10: the model's joint results allocated and its second layer loaded, both on the
 * heap of the object's heap4 slot; whether both succeeded. */
int SpecialSceneObject_LoadModel(u8 *object)
{
    const ResourceSlot *slot = (const ResourceSlot *) (uintptr_t) PoolLink_Heap4(sso_heap(object));
    u32 heap = ResourcePools_Heap4SlotHeap(slot);
    if (ModelObject_AllocJointResults((ModelObject *) (void *) sso_at(object, SSO_MODEL), (Heap *) (uintptr_t) heap) == 0) {
        return 0;
    }
    heap = ResourcePools_Heap4SlotHeap(slot);
    return LayeredModel_LoadB((LayeredModel *) (void *) sso_at(object, SSO_MODEL), (int) heap) != 0;
}
CLEAN_AS(func_0202ee10, SpecialSceneObject_LoadModel)

/* The destructor's body: the class's vtable, its heap link, then the base class's destructor
 * inline. */
static void sso_destruct(void *object)
{
    *(const u8 **) object = data_020da088;
    PoolLink_Heap4Destruct(sso_heap(object));
    SceneObjectMembers_Destruct(object);
}

/* func_0202ee5c: the destructor the derived classes' destructors run. Returns the object. */
void *SpecialSceneObject_DestructBody(void *object)
{
    sso_destruct(object);
    return object;
}
CLEAN_AS(func_0202ee5c, SpecialSceneObject_DestructBody)

/* func_0202ef38 (slot 0x44): destructed, then freed to the auxiliary heap. */
void *SpecialSceneObject_DestructDelete(void *object)
{
    sso_destruct(object);
    Heap_FreeAux(object);
    return object;
}
CLEAN_AS(func_0202ef38, SpecialSceneObject_DestructDelete)

/* func_0202f018 (slot 0x40): the destructor. */
void *SpecialSceneObject_Destruct(void *object)
{
    sso_destruct(object);
    return object;
}
CLEAN_AS(func_0202f018, SpecialSceneObject_Destruct)
