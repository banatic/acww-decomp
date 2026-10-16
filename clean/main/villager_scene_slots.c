/* The town villager scene object's own constructor, destructors and vtable slots
 * (villager_scene_slots.h). */
#include "villager_scene_slots.h"

#include "actor_table.h"
#include "autoload_2/heap.h"
#include "clean.h"
#include "model_object.h"
#include "npc_id.h"
#include "pool_link.h"
#include "resource_pools.h"
#include "scene_object.h"
#include "scene_object_members.h"
#include "scene_probe.h"
#include "scene_value_3aa.h"
#include "session_villager.h"
#include "town_villager.h"
#include "villager_clothes.h"
#include "villager_mood.h"
#include "villager_roster.h"
#include "villager_scene_object.h"
#include "villager_state.h"
#include "villager_status.h"
#include "villager_talk_scene.h"

/* The object's parts, by place. */
#define VSO_PERSON 0x0ea   /* ItemCode: the person (kind 0xe) */
#define VSO_MODEL 0x0ec    /* LayeredModel (a ModelObject first) */
#define VSO_FACE 0x2ac     /* SceneFace */
#define VSO_ANIM 0x334     /* SpeakerAnim */
#define VSO_BODY 0x4cc     /* FieldOwnedBody */
#define VSO_MOTION 0x564   /* SceneMotion */
#define VSO_WORD_644 0x644 /* u32 */
#define VSO_CLOTHES 0x64c  /* VillagerClothes */
#define VSO_TALK 0x680     /* VillagerTalk */
#define VSO_COIN 0x824     /* u8: 0 or 1, drawn at init */
#define VSO_HEAP 0x828     /* PoolLink to a heap8 slot */
#define VSO_RECORD 0x830   /* u8 *: the town record, or NULL */
#define VSO_STATE 0x834    /* the record's state entry */
#define VSO_MOOD 0x83c     /* VillagerMood */

/* The kind of the person codes of town villagers (the code's top four bits). */
#define VSO_KIND_VILLAGER 0xe
/* The vtable slot that gives the town record. */
#define VSO_SLOT_RECORD 0x64
/* The clothes items: those with a texture of their own, and the eight that follow. */
#define VSO_CLOTHES_FIRST 0x11a8
#define VSO_CLOTHES_LAST 0x12a7
#define VSO_CLOTHES_EXTRA_FIRST 0x12a8
#define VSO_CLOTHES_EXTRA_LAST 0x12af
/* What the slots answer without a record. */
#define VSO_NO_SOUND 0xffff
#define VSO_NO_NUMBER (-1)
#define VSO_DEFAULT_GROUP 2

/* The class's vtable. */
extern const u8 data_020d9e88[];
/* The speed scale of the villagers' animation players. */
extern s32 data_020c8120;
/* The town's villagers. */
extern VillagerTown data_021e5a2c;
/* The file names built here, and their formats ("npc/model/%d/%d.nsbmd" and ".nsbtx"). */
extern char data_021c1da4[];
extern char data_021c1d84[];
extern const char data_020d9fc0[];
extern const char data_020d9fd8[];

/* sprintf */
extern int func_02064328(char *buffer, const char *format, ...);
/* A random number below `bound`. */
extern int func_020644cc(int bound);

static u8 *vso_at(void *object, u32 offset)
{
    return (u8 *) object + offset;
}

static u8 *vso_record(void *object)
{
    return *(u8 **) (void *) vso_at(object, VSO_RECORD);
}

static int vso_kind(void *object)
{
    return (*(const u16 *) (const void *) vso_at(object, VSO_PERSON) & 0xf000) >> 12;
}

static ResourceSlot *vso_heap_slot(void *object)
{
    return (ResourceSlot *) (uintptr_t) PoolLink_Heap8((PoolLink *) (void *) vso_at(object, VSO_HEAP));
}

/* func_0202e1a0 (slot 0x0c): the base's leave (SceneObject_Leave), then the heap slot given
 * back, the clothes ended and the mood stopped; 0 when the base's leave is not done. */
int VillagerSceneObject_Leave(u8 *object)
{
    if (SceneObject_Leave(object) == 0) {
        return 0;
    }
    PoolLink_Release((PoolLink *) (void *) vso_at(object, VSO_HEAP));
    VillagerClothes_End((VillagerClothes *) (void *) vso_at(object, VSO_CLOTHES));
    VillagerMood_Stop((VillagerMood *) (void *) vso_at(object, VSO_MOOD));
    return 1;
}
CLEAN_AS(func_0202e1a0, VillagerSceneObject_Leave)

/* func_0202e1dc (slot 0x10): when the base may be deleted, the person's entry of the actor
 * table is removed (Actors_RemoveE); whether it may. */
int VillagerSceneObject_CanDelete(u8 *object)
{
    if (SceneObjectBase_CanDelete((SceneObjectBase *) (void *) object) == 0) {
        return 0;
    }
    Actors_RemoveE((const ItemCode *) (const void *) vso_at(object, VSO_PERSON));
    return 1;
}
CLEAN_AS(func_0202e1dc, VillagerSceneObject_CanDelete)

/* func_0202e1fc (slot 0x00): the start. After the base's (SceneObject_Start): a heap slot taken
 * and the model loaded into it when the object holds none, the face loaded, the animation
 * player set up, the motion of kind 0 started, the clothes put on (the record's, or item
 * 0x11a8 without a record), the body set (radius 1.0, height 2.0) and the person added to the
 * actor table. 0 as soon as a step fails (the steps done stay done), else 1. */
int VillagerSceneObject_Start(u8 *object)
{
    u16 clothes = VSO_CLOTHES_FIRST;

    if (SceneObject_Start(object) == 0) {
        return 0;
    }
    if (PoolLink_Heap8((PoolLink *) (void *) vso_at(object, VSO_HEAP)) == 0) {
        if (PoolLink_Take((PoolLink *) (void *) vso_at(object, VSO_HEAP)) == 0) {
            return 0;
        }
        if (VillagerSceneObject_LoadModel(object) == 0) {
            return 0;
        }
    }
    if (SceneFace_Load((SceneFace *) (void *) vso_at(object, VSO_FACE), object) == 0) {
        return 0;
    }
    if (SpeakerAnim_Init((SpeakerAnim *) (void *) vso_at(object, VSO_ANIM), object, data_020c8120) == 0) {
        return 0;
    }
    SceneMotion_StartNow((SceneMotion *) (void *) vso_at(object, VSO_MOTION), object, 0, 1, 0, 0, 0, 0, 0);
    u8 *record = vso_record(object);
    if (record != NULL) {
        clothes = *TownVillager_Clothes(record);
    }
    if (VillagerClothes_Start((VillagerClothes *) (void *) vso_at(object, VSO_CLOTHES), object, &clothes) == 0) {
        return 0;
    }
    FieldOwnedBody_Set((FieldOwnedBody *) (void *) vso_at(object, VSO_BODY), (Actor *) (void *) object, 0x1000, 0x2000, 8,
                       0x2fc, 2, (u8) SceneObject_PersonIndex(object), 0x1000);
    return Actors_AddE(object, (const ItemCode *) (const void *) vso_at(object, VSO_PERSON)) != 0;
}
CLEAN_AS(func_0202e1fc, VillagerSceneObject_Start)

/* func_0202e318: the model's joint results allocated and its second layer loaded, both on the
 * heap of the object's heap8 slot; whether both succeeded. */
int VillagerSceneObject_LoadModel(u8 *object)
{
    ResourceSlot *slot = vso_heap_slot(object);
    u32 heap = ResourcePools_Heap8SlotHeap(slot);
    if (ModelObject_AllocJointResults((ModelObject *) (void *) vso_at(object, VSO_MODEL), (Heap *) (uintptr_t) heap) == 0) {
        return 0;
    }
    heap = ResourcePools_Heap8SlotHeap(slot);
    return LayeredModel_LoadB((LayeredModel *) (void *) vso_at(object, VSO_MODEL), (int) heap) != 0;
}
CLEAN_AS(func_0202e318, VillagerSceneObject_LoadModel)

/* func_0202e364 (slot 0x04): after the base's init (SceneObject_Init): the town record found,
 * the word at 0x644 cleared, the byte at 0x824 drawn (0 or 1), the mood started and the town
 * event noted (VillagerSceneObject_SetEvent). 0 when the base's init fails. */
int VillagerSceneObject_Init(u8 *object)
{
    if (SceneObject_Init(object) == 0) {
        return 0;
    }
    VillagerSceneObject_FindRecord(object);
    *(u32 *) (void *) vso_at(object, VSO_WORD_644) = 0;
    *vso_at(object, VSO_COIN) = (u8) func_020644cc(2);
    VillagerMood_Start((VillagerMood *) (void *) vso_at(object, VSO_MOOD));
    VillagerSceneObject_SetEvent(object);
    return 1;
}
CLEAN_AS(func_0202e364, VillagerSceneObject_Init)

/* func_0202e3ac (slot 0x88, told of frame 8 of an animation with `item`): for a clothes item
 * (0x11a8-0x12af) the clothes are put on (VillagerClothes_Change), and with a town record (its
 * slot 0x64, asked first) the record wears them too, and is shared with the others in the
 * session when `share` is set. */
void VillagerSceneObject_TakeClothes(u8 *object, u16 *item, int share)
{
    u16 code = *item;
    if (!(code >= VSO_CLOTHES_FIRST && code <= VSO_CLOTHES_LAST) &&
        !(code >= VSO_CLOTHES_EXTRA_FIRST && code <= VSO_CLOTHES_EXTRA_LAST)) {
        return;
    }
    const u8 *vtable = *(const u8 *const *) (const void *) object;
    u32 slot = *(const u32 *) (const void *) (vtable + VSO_SLOT_RECORD);
    int record = ((int (*)(void *))(uintptr_t) slot)(object);
    VillagerClothes_Change((VillagerClothes *) (void *) vso_at(object, VSO_CLOTHES), object, item);
    if (record != 0) {
        TownVillager_SetClothes((u8 *) (uintptr_t) record, item);
        if (share) {
            SessionVillager_SendItem7D2((u8 *) (uintptr_t) record, item);
        }
    }
}
CLEAN_AS(func_0202e3ac, VillagerSceneObject_TakeClothes)

/* func_0202e424 (slot 0xb0) */
int VillagerSceneObject_VfuncB0(void *object)
{
    (void) object;
    return 0;
}
CLEAN_AS(func_0202e424, VillagerSceneObject_VfuncB0)

/* func_0202e428 (slot 0xac) */
int VillagerSceneObject_VfuncAc(void *object)
{
    (void) object;
    return 0;
}
CLEAN_AS(func_0202e428, VillagerSceneObject_VfuncAc)

/* func_0202e42c (slot 0xa8) */
int VillagerSceneObject_VfuncA8(void *object)
{
    (void) object;
    return 1;
}
CLEAN_AS(func_0202e42c, VillagerSceneObject_VfuncA8)

/* func_0202e430 (slot 0xa4): mood `which` asked for, for `units` (VillagerMood_Ask), while
 * the mood is on. */
void VillagerSceneObject_AskMood(u8 *object, int which, int units)
{
    VillagerMood *mood = (VillagerMood *) (void *) vso_at(object, VSO_MOOD);
    if (VillagerMood_IsOn(mood)) {
        VillagerMood_Ask(mood, (unsigned int) which, (unsigned int) units);
    }
}
CLEAN_AS(func_0202e430, VillagerSceneObject_AskMood)

/* func_0202e45c (slot 0x64): the town record. */
u32 VillagerSceneObject_Record(u32 *object)
{
    return *(const u32 *) (const void *) vso_at(object, VSO_RECORD);
}
CLEAN_AS(func_0202e45c, VillagerSceneObject_Record)

/* The name of one of the villager's files, from `format` with the villager's number (0 without
 * one) and that number with its low three bits cleared, into `buffer`.
 * QUIRK: the folder is the number rounded down to a multiple of 8, the file the number. */
static char *vso_file(void *object, char *buffer, const char *format)
{
    int number = VillagerSceneObject_NpcNumber(object);
    if (number == VSO_NO_NUMBER) {
        number = 0;
    }
    func_02064328(buffer, format, number & 0xf8, number);
    return buffer;
}

/* func_0202e468 (slot 0x70): the model's file name ("npc/model/%d/%d.nsbmd"), in a buffer of
 * the game's that the next call overwrites. */
char *VillagerSceneObject_ModelFile(void *object)
{
    return vso_file(object, data_021c1da4, data_020d9fc0);
}
CLEAN_AS(func_0202e468, VillagerSceneObject_ModelFile)

/* func_0202e498 (slot 0x6c): the texture's file name ("npc/model/%d/%d.nsbtx"), the same way. */
char *VillagerSceneObject_TextureFile(void *object)
{
    return vso_file(object, data_021c1d84, data_020d9fd8);
}
CLEAN_AS(func_0202e498, VillagerSceneObject_TextureFile)

/* func_0202e4c8 (slot 0x84): the sound of an action's start: the villager's number
 * (NpcId_Number) when its person is a villager's with a town record, else none (0xffff). */
int VillagerSceneObject_ActionSound(u8 *object)
{
    if (vso_kind(object) == VSO_KIND_VILLAGER && vso_record(object) != NULL) {
        return NpcId_Number(TownVillager_NpcId(vso_record(object)));
    }
    return VSO_NO_SOUND;
}
CLEAN_AS(func_0202e4c8, VillagerSceneObject_ActionSound)

/* func_0202e504 (slot 0x80): nothing to do once the sound is played. */
void VillagerSceneObject_ActionSoundPlayed(void *object)
{
    (void) object;
}
CLEAN_AS(func_0202e504, VillagerSceneObject_ActionSoundPlayed)

/* func_0202e508 (slot 0x7c): an action's start always has a sound. */
int VillagerSceneObject_HasActionSound(void *object)
{
    (void) object;
    return 1;
}
CLEAN_AS(func_0202e508, VillagerSceneObject_HasActionSound)

/* func_0202e50c (slot 0x78): the sort: the villager's personality group, 2 without a record. */
int VillagerSceneObject_Sort(u8 *object)
{
    if (vso_record(object) == NULL) {
        return VSO_DEFAULT_GROUP;
    }
    return (int) NpcId_PersonalityGroup(TownVillager_NpcId(vso_record(object)));
}
CLEAN_AS(func_0202e50c, VillagerSceneObject_Sort)

/* func_0202e530 (slot 0x74): the villager's name into `name` (NpcId_FormatName), nothing
 * without a record. */
void VillagerSceneObject_NameInto(u8 *object, char *name)
{
    if (vso_record(object) != NULL) {
        NpcId_FormatName(TownVillager_NpcId(vso_record(object)), name);
    }
}
CLEAN_AS(func_0202e530, VillagerSceneObject_NameInto)

/* func_0202e550: the villager's number (NpcId_Number) when it has a record of a valid villager,
 * else -1. */
int VillagerSceneObject_NpcNumber(u8 *object)
{
    if (vso_record(object) == NULL) {
        return VSO_NO_NUMBER;
    }
    if (NpcId_IsValid(TownVillager_NpcId(vso_record(object))) != 1) {
        return VSO_NO_NUMBER;
    }
    return NpcId_Number(TownVillager_NpcId(vso_record(object)));
}
CLEAN_AS(func_0202e550, VillagerSceneObject_NpcNumber)

/* func_0202e58c: for a villager's person, the town record is the town's villager at the
 * object's person index (VillagerRoster_At, NULL for none), and with it its state entry is
 * noted (0 without a record). Other persons keep both as they are. */
void VillagerSceneObject_FindRecord(u8 *object)
{
    if (vso_kind(object) != VSO_KIND_VILLAGER) {
        return;
    }
    u8 *record = VillagerRoster_At(&data_021e5a2c, SceneObject_PersonIndex(object));
    *(u8 **) (void *) vso_at(object, VSO_RECORD) = record;
    if (record != NULL) {
        *(VillagerState **) (void *) vso_at(object, VSO_STATE) = VillagerStatus_StateEntry(record);
    } else {
        *(u32 *) (void *) vso_at(object, VSO_STATE) = 0;
    }
}
CLEAN_AS(func_0202e58c, VillagerSceneObject_FindRecord)

/* The destructor's body: the class's vtable, its own members from the last to the first, then
 * the base class's destructor inline. */
static void vso_destruct(u8 *object)
{
    *(const u8 **) (void *) object = data_020d9e88;
    VillagerMood_Destruct((VillagerMood *) (void *) vso_at(object, VSO_MOOD));
    PoolLink_Heap8Destruct((PoolLink *) (void *) vso_at(object, VSO_HEAP));
    VillagerTalkScene_Destruct((VillagerTalk *) (void *) vso_at(object, VSO_TALK));
    VillagerClothes_Destruct((VillagerClothes *) (void *) vso_at(object, VSO_CLOTHES));
    SceneObjectMembers_Destruct(object);
}

/* func_0202e5e0: the destructor the derived classes' destructors run. Returns the object. */
u8 *VillagerSceneObject_DestructBody(u8 *object)
{
    vso_destruct(object);
    return object;
}
CLEAN_AS(func_0202e5e0, VillagerSceneObject_DestructBody)

/* func_0202e6e0 (slot 0x44): destructed, then freed to the auxiliary heap. */
u8 *VillagerSceneObject_DestructDelete(u8 *object)
{
    vso_destruct(object);
    Heap_FreeAux(object);
    return object;
}
CLEAN_AS(func_0202e6e0, VillagerSceneObject_DestructDelete)

/* func_0202e7e4 (slot 0x40): the destructor. */
u8 *VillagerSceneObject_Destruct(u8 *object)
{
    vso_destruct(object);
    return object;
}
CLEAN_AS(func_0202e7e4, VillagerSceneObject_Destruct)

/* func_0202e8e4: the constructor: the base, then the base class's vtable and members in place
 * order (the person none yet, 0xfff1), then the class's vtable and its own members. */
u8 *VillagerSceneObject_Construct(u8 *object)
{
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) vso_at(object, VSO_PERSON) = 0xfff1;
    LayeredModel_ConstructB((LayeredModel *) (void *) vso_at(object, VSO_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) vso_at(object, 0x2a0));
    SceneFace_Construct((SceneFace *) (void *) vso_at(object, VSO_FACE));
    /* func_020169a8, the animation player's constructor (registered under the destructor's
     * name). */
    SpeakerAnim_Destruct((SpeakerAnim *) (void *) vso_at(object, VSO_ANIM));
    SceneMover_Construct((SceneMover *) (void *) vso_at(object, 0x350));
    SceneProbe_Construct(vso_at(object, 0x3a8));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) vso_at(object, 0x3aa));
    SceneLook_Construct((SceneLook *) (void *) vso_at(object, 0x3b0));
    SceneTalkState_Construct((SceneTalkState *) (void *) vso_at(object, 0x418));
    ActEffects_Construct((ActEffects *) (void *) vso_at(object, 0x420));
    CollisionContacts_Construct((CollisionContacts *) (void *) vso_at(object, 0x49c));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) vso_at(object, VSO_BODY));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) vso_at(object, 0x514));
    Footsteps_Construct((Footsteps *) (void *) vso_at(object, 0x558));
    SceneMotion_Construct((SceneMotion *) (void *) vso_at(object, VSO_MOTION));
    SceneAction_Construct((SceneAction *) (void *) vso_at(object, 0x618));
    *(const u8 **) (void *) object = data_020d9e88;
    VillagerClothes_Construct((VillagerClothes *) (void *) vso_at(object, VSO_CLOTHES));
    VillagerTalkScene_Construct((VillagerTalk *) (void *) vso_at(object, VSO_TALK));
    PoolLink_Heap8Construct((PoolLink *) (void *) vso_at(object, VSO_HEAP));
    VillagerMood_Construct((VillagerMood *) (void *) vso_at(object, VSO_MOOD));
    return object;
}
CLEAN_AS(func_0202e8e4, VillagerSceneObject_Construct)
