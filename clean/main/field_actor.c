/* The main program's part of the field actor's class (field_actor.h). */
#include "field_actor.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "field_actor_parts.h"
#include "main/item_code.h"
#include "main/session.h"
#include "sound_emitter.h"
#include "act_effects.h"
#include "actor_palettes.h"
#include "anim_slots.h"
#include "animated_model.h"
#include "autoload_2/sound_emitter_class.h"
#include "body_anim_heaps.h"
#include "body_look.h"
#include "cloth_slots.h"
#include "effect_system.h"
#include "face_anim_heaps.h"
#include "face_anim_slots.h"
#include "face_anim_timer.h"
#include "face_texture.h"
#include "field_body.h"
#include "field_collision.h"
#include "field_label.h"
#include "fishing_float.h"
#include "glasses_look.h"
#include "head_look.h"
#include "held_item.h"
#include "layered_model.h"
#include "model_object.h"
#include "music_queue.h"
#include "player_actor_ops.h"
#include "player_actors.h"
#include "scene_object_base.h"
#include "session_players.h"
#include "session_record.h"
#include "talk_receiver.h"
#include "tex_pattern_anim.h"
#include "touch_pick_shapes.h"
#include "vram_copy_task.h"

/* The heap the field actors are made on. */
extern Heap *data_021c9ab4;

/* The vtables: the class's, the one of its message receiver (at 0xec), and the one of the
 * sound emitter at 0x880, whose destructor callers inline. */
extern const u8 data_020d82b4[];
extern const u8 data_020d832c[];
extern const u8 data_020d8414[];

/* The destructors of the members and bases, in the order the deleting destructor runs them. */
extern int func_0200e91c(void *request);
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern u32 func_0200e92c(void *request);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));

/* What FieldActor_Shutdown releases. */
extern NetSession *data_020ccf94;

/* The queue of state requests at 0x934: 30 of 0x1c bytes. */
#define REQUEST_QUEUE 0x934
#define REQUEST_COUNT 30
#define REQUEST_SIZE 0x1c

/* The byte `offset` into the actor. */
static u8 *at(struct FieldActor *actor, u32 offset)
{
    return (u8 *) actor + offset;
}

static void set_vtable(struct FieldActor *actor, u32 offset, const u8 *vtable)
{
    *(const u8 **) at(actor, offset) = vtable;
}

/* func_02004ba8: the class's operator delete. */
void FieldActor_Delete(void *actor)
{
    Heap_Free(data_021c9ab4, actor);
}
CLEAN_AS(func_02004ba8, FieldActor_Delete)

/* func_02004bbc: the class's operator new: `size` bytes, zeroed, or NULL. */
void *FieldActor_New(int size)
{
    Heap *heap = data_021c9ab4;
    void *actor = Heap_AllocAligned(heap, size, PlayerActors_FieldActorAlignment());
    if (actor == NULL) {
        return NULL;
    }
    memset(actor, 0, (size_t) size);
    return actor;
}
CLEAN_AS(func_02004bbc, FieldActor_New)

/* func_02004bf4: vtable slot 0x0c, run when the actor goes away (func_020051b4). QUIRK: the
 * original ends in a call to it and so gives back its result; like the matching source, this
 * returns none. */
void FieldActor_Teardown(struct FieldActor *actor)
{
    FieldActor_Shutdown(actor);
}
CLEAN_AS(func_02004bf4, FieldActor_Teardown)

/* func_02004bfc: vtable slot 0x24 (func_02005338), then 1. */
int FieldActor_Vfunc24(struct FieldActor *actor)
{
    FieldActor_PlaceForDraw(actor);
    return 1;
}
CLEAN_AS(func_02004bfc, FieldActor_Vfunc24)

/* func_02004c0c: vtable slot 0x18, the frame's update with the state machine (func_020058e4),
 * then 1. */
int FieldActor_Update(struct FieldActor *actor)
{
    FieldActor_RunFrame(actor);
    return 1;
}
CLEAN_AS(func_02004c0c, FieldActor_Update)

/* func_02004c1c: vtable slot 0x00, the set-up once the actor is made (FieldActor_Init). QUIRK:
 * as FieldActor_Teardown, the original gives back the callee's result and this none. */
void FieldActor_Setup(struct FieldActor *actor)
{
    FieldActor_Init(actor);
}
CLEAN_AS(func_02004c1c, FieldActor_Setup)

/* The members are destroyed in the reverse order of their places, then the message receiver
 * and the base. */
static void destroy(struct FieldActor *actor)
{
    set_vtable(actor, 0x000, data_020d82b4);
    set_vtable(actor, 0x0ec, data_020d832c);
    __cxa_vec_cleanup(at(actor, REQUEST_QUEUE), REQUEST_COUNT, REQUEST_SIZE, (void (*)(void *))(uintptr_t) func_0200e91c);
    ActEffects_Destruct((ActEffects *) (void *) at(actor, 0x90c));
    set_vtable(actor, 0x880, data_020d8414);
    SoundEmitterClass_DestructBase((SoundEmitterObject *) (void *) at(actor, 0x880));
    SoundEmitterClass_Destruct99((SoundEmitterObject *) (void *) at(actor, 0x83c));
    CollisionContacts_Destroy((CollisionContacts *) (void *) at(actor, 0x7a4));
    ActorPalettes_DestructSlot(at(actor, 0x7a0));
    ClothSlots_DestructSlot(at(actor, 0x774));
    FaceAnimTimer_Destruct(at(actor, 0x768));
    TexPatternAnim_Destruct((TexPatternAnim *) (void *) at(actor, 0x73c));
    TexPatternAnim_Destruct((TexPatternAnim *) (void *) at(actor, 0x710));
    FaceAnimHeaps_DestructSlot(at(actor, 0x70f));
    FaceAnimSlots_DestructSlot(at(actor, 0x70e));
    FaceTexture_DestructSlot(at(actor, 0x70d));
    AnimSlots_DestructSlot(at(actor, 0x701));
    AnimSlots_DestructSlot(at(actor, 0x700));
    HeldItem_Destruct((HeldItemObject *) (void *) at(actor, 0x5a0));
    GlassesLook_DestructLook(at(actor, 0x59c));
    ModelObject_DestructComplete((ModelObject *) (void *) at(actor, 0x500));
    ModelObject_DestructComplete((ModelObject *) (void *) at(actor, 0x464));
    HeadLook_DestructLook(at(actor, 0x428));
    ModelObject_DestructComplete((ModelObject *) (void *) at(actor, 0x38c));
    BodyLook_DestructLook(at(actor, 0x389));
    BodyAnimHeaps_DestructSlot(at(actor, 0x388));
    LayeredModel_DestructAComplete((LayeredModel *) (void *) at(actor, 0x234));
    TouchPickCylinder_Destruct((TouchPickCylinder *) (void *) at(actor, 0x214));
    FieldOwnedPointBody_Destruct((FieldOwnedPointBody *) (void *) at(actor, 0x1c4));
    FieldOwnedPointBody_Destruct((FieldOwnedPointBody *) (void *) at(actor, 0x174));
    TalkReceiver_Destruct((TalkReceiver *) (void *) at(actor, 0x0ec));
    SceneObjectBase_DestructBase((SceneObjectBase *) actor);
}

/* func_02004c24: the deleting destructor (vtable slot 0x44): destroys the actor and frees its
 * memory. Returns the actor. */
struct FieldActor *FieldActor_DestructDelete(struct FieldActor *actor)
{
    destroy(actor);
    FieldActor_Delete(actor);
    return actor;
}
CLEAN_AS(func_02004c24, FieldActor_DestructDelete)

/* func_02004db0: the destructor, without freeing the memory. Returns the actor. */
void *FieldActor_Destruct(struct FieldActor *actor)
{
    destroy(actor);
    return actor;
}
CLEAN_AS(func_02004db0, FieldActor_Destruct)

/* func_02004f34: the constructor: the base and the message receiver, the vtables, the members
 * in the order of their places, then the starting values. The memory comes zeroed from
 * FieldActor_New; what is not set here stays 0. */
struct FieldActor *FieldActor_Construct(struct FieldActor *actor)
{
    SceneObjectBase_Construct((SceneObjectBase *) actor);
    TalkReceiver_ConstructBase((TalkReceiver *) (void *) at(actor, 0x0ec));
    set_vtable(actor, 0x000, data_020d82b4);
    set_vtable(actor, 0x0ec, data_020d832c);
    FieldOwnedPointBody_Construct((FieldOwnedPointBody *) (void *) at(actor, 0x174));
    FieldOwnedPointBody_Construct((FieldOwnedPointBody *) (void *) at(actor, 0x1c4));
    TouchPickCylinder_Construct((TouchPickCylinder *) (void *) at(actor, 0x214));
    LayeredModel_ConstructA((LayeredModel *) (void *) at(actor, 0x234));
    BodyAnimHeaps_ConstructSlot(at(actor, 0x388));
    BodyLook_ConstructLook(at(actor, 0x389));
    ModelObject_Construct((ModelObject *) (void *) at(actor, 0x38c));
    HeadLook_ConstructLook(at(actor, 0x428));
    ModelObject_Construct((ModelObject *) (void *) at(actor, 0x464));
    ModelObject_Construct((ModelObject *) (void *) at(actor, 0x500));
    GlassesLook_ConstructLook(at(actor, 0x59c));
    HeldItem_Construct((HeldItemObject *) (void *) at(actor, 0x5a0));
    AnimSlots_ConstructSlot(at(actor, 0x700));
    AnimSlots_ConstructSlot(at(actor, 0x701));
    FaceTexture_ConstructSlot(at(actor, 0x70d));
    FaceAnimSlots_ConstructSlot(at(actor, 0x70e));
    FaceAnimHeaps_ConstructSlot(at(actor, 0x70f));
    TexPatternAnim_Construct((TexPatternAnim *) (void *) at(actor, 0x710));
    TexPatternAnim_Construct((TexPatternAnim *) (void *) at(actor, 0x73c));
    FaceAnimTimer_Construct(at(actor, 0x768));
    ClothSlots_ConstructSlot(at(actor, 0x774));
    VramCopyMaterial_Construct((VramCopyMaterial *) (void *) at(actor, 0x778));
    ActorPalettes_ConstructSlot(at(actor, 0x7a0));
    CollisionContacts_Construct((CollisionContacts *) (void *) at(actor, 0x7a4));
    actor->item = ITEM_CODE_NONE;
    actor->unk_822 = ITEM_CODE_NONE;
    SoundEmitterClass_Construct99((SoundEmitterObject *) (void *) at(actor, 0x83c));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) at(actor, 0x880));
    for (int i = 0; i < 2; i++) {
        actor->front_tile[i] = 0;
        actor->tile[i] = 0;
        actor->pending_tile[i] = 0;
    }
    FIELD_ACTOR_PENDING_X(actor) = 0;
    FIELD_ACTOR_PENDING_Z(actor) = 0;
    ActEffects_Construct((ActEffects *) (void *) at(actor, 0x90c));
    __cxa_vec_ctor(at(actor, REQUEST_QUEUE), REQUEST_COUNT, REQUEST_SIZE, (void (*)(void *))(uintptr_t) func_0200e92c,
                   (void (*)(void *))(uintptr_t) func_0200e91c);
    actor->player = 4; /* none */
    actor->animation = 0xa1;
    FIELD_ACTOR_FIELD(actor, int, 0x708) = 0x144;
    FIELD_ACTOR_FIELD(actor, int, 0x76c) = 0x16f;
    FIELD_ACTOR_FIELD(actor, int, 0x770) = 0x16f;
    actor->aim_mode = 2;
    FIELD_ACTOR_FIELD(actor, int, 0xc80) = -1;
    FIELD_ACTOR_FIELD(actor, int, 0xc8c) = 2;
    FIELD_ACTOR_FIELD(actor, int, 0xc94) = 2;
    FIELD_ACTOR_REMOTE_STATE(actor) = FIELD_ACTOR_STATES;
    actor->unk_C84 = -1;
    FIELD_ACTOR_ENTERED_STATE(actor) = FIELD_ACTOR_STATES;
    return actor;
}
CLEAN_AS(func_02004f34, FieldActor_Construct)

/* The size of the class. */
#define FIELD_ACTOR_SIZE 0xca0

/* func_020115d0: a new actor (FieldActor_New), constructed; nothing when there is no room. */
void FieldActor_Create(void)
{
    struct FieldActor *actor = FieldActor_New(FIELD_ACTOR_SIZE);
    if (actor != NULL) {
        FieldActor_Construct(actor);
    }
}
CLEAN_AS(func_020115d0, FieldActor_Create)

/* The receiver's vtable (0x020d832c) enters the actor's functions through these: each moves
 * the pointer back from the receiver part (at 0xec) to the actor and goes on with the actor's
 * function. */
#define FIELD_ACTOR_RECEIVER 0xec

static struct FieldActor *actor_of(void *receiver)
{
    return (struct FieldActor *) ((u8 *) receiver - FIELD_ACTOR_RECEIVER);
}

/* func_0201160c */
struct FieldActor *FieldActorReceiver_DestructDelete(void *receiver)
{
    return FieldActor_DestructDelete(actor_of(receiver));
}
CLEAN_AS(_ZThn236_N12Obj_020d82b4D0Ev, FieldActorReceiver_DestructDelete)

/* func_02011628 */
void FieldActorReceiver_TalkClosing(void *receiver)
{
    FieldActor_TalkClosing(actor_of(receiver));
}
CLEAN_AS(_ZThn236_N12Obj_020d82b417vfunc_02066994_70Ev, FieldActorReceiver_TalkClosing)

/* func_02011644 */
void FieldActorReceiver_TalkChoice(void *receiver)
{
    FieldActor_TalkChoice(actor_of(receiver));
}
CLEAN_AS(_ZThn236_N12Obj_020d82b417vfunc_02066994_18Ev, FieldActorReceiver_TalkChoice)

/* func_02011660 */
void FieldActorReceiver_TalkMessage(void *receiver)
{
    FieldActor_TalkMessage(actor_of(receiver));
}
CLEAN_AS(_ZThn236_N12Obj_020d82b417vfunc_02066994_14Ev, FieldActorReceiver_TalkMessage)

/* func_0201167c */
void FieldActorReceiver_TalkIgnore(void *receiver)
{
    FieldActor_TalkIgnore(actor_of(receiver));
}
CLEAN_AS(_ZThn236_N12Obj_020d82b417vfunc_02066994_10Ev, FieldActorReceiver_TalkIgnore)

/* func_02011698 */
void *FieldActorReceiver_Destruct(void *receiver)
{
    return FieldActor_Destruct(actor_of(receiver));
}
CLEAN_AS(_ZThn236_N12Obj_020d82b4D1Ev, FieldActorReceiver_Destruct)

/* func_020051b4: run when the actor goes away (FieldActor_Teardown). In state 0x6d its effect
 * is ended; the session's and the members' resources are released; and flags 0x1a
 * (func_02035638 0x3f), 0xa (the sound emitter that plays: 0x83c with flag 0x19, else 0x880)
 * and 0x1b (func_020b8db4) are undone. Returns 1.
 * QUIRK: the player number plus 8 goes to func_020771cc as its first argument. */
int FieldActor_Shutdown(struct FieldActor *actor)
{
    if (actor->state == 0x6d && actor->work.s6d.effect != -1) {
        EffectSystem_EndHandle(actor->work.s6d.effect);
    }
    SessionPlayers_ClearActor(actor->player);
    NetSession *session = data_020ccf94;
    if (Session_IsLinked(session) && Session_IsLocalPlayer(session, actor->player)) {
        SessionRecord_Update(actor->player + 8, NULL, 0, 0);
    }
    VramCopyMaterial_End((VramCopyMaterial *) (void *) at(actor, 0x778));
    TexPatternAnim_Unload((TexPatternAnim *) (void *) at(actor, 0x710));
    TexPatternAnim_Unload((TexPatternAnim *) (void *) at(actor, 0x73c));
    ModelObject_Release((ModelObject *) (void *) at(actor, FIELD_ACTOR_MODEL_C));
    ModelObject_Release((ModelObject *) (void *) at(actor, FIELD_ACTOR_MODEL_A));
    ModelObject_Release((ModelObject *) (void *) at(actor, FIELD_ACTOR_MODEL_B));
    AnimatedModel_DetachJoints((AnimatedModel *) (void *) at(actor, FIELD_ACTOR_BODY));
    ModelObject_Release((ModelObject *) (void *) at(actor, FIELD_ACTOR_BODY));
    HeldItem_Clear((HeldItemObject *) (void *) actor->held);
    GlassesLook_Unload(at(actor, FIELD_ACTOR_PART_C));
    FIELD_ACTOR_FIELD(actor, int, 0xc8c) = 2;
    HeadLook_Unload(at(actor, FIELD_ACTOR_PART_B));
    ClothSlots_ResetSlot(at(actor, 0x774));
    BodyLook_StopUpload(at(actor, 0x389));
    SessionPlayers_ClearLookIndex(actor->player);
    if (FieldActor_TestFlag(actor, 0x1a)) {
        Music_DropMusic(0x3f);
        FieldActor_ClearFlag(actor, 0x1a);
    }
    if (FieldActor_TestFlag(actor, 0xa)) {
        if (FieldActor_TestFlag(actor, 0x19)) {
            SoundEmitter_Vfunc10B((SoundEmitter *) at(actor, FIELD_ACTOR_EMITTER_B));
        } else {
            SoundEmitter_Vfunc10B((SoundEmitter *) at(actor, FIELD_ACTOR_EMITTER));
        }
        FieldActor_ClearFlag(actor, 0xa);
    }
    if (FieldActor_TestFlag(actor, 0x1b)) {
        FieldActor_ClearFlag(actor, 0x1b);
        FieldLabel_ClearMessage();
    }
    return 1;
}
CLEAN_AS(func_020051b4, FieldActor_Shutdown)

/* ---- The set-up once the actor is made (FieldActor_Setup): its player and looks from the
 * word it was made with, its models, and state 0 queued with the state it starts in. */

/* The player's looks by the player's index (func_020961d0): the member at 0x7a0, the parts at
 * 0x70f, 0x70e and 0x70d, the held item, the parts B and C, the looks at 0x389 and 0x774. */
extern const u8 data_020c75c4[];
extern const u8 data_020c75d4[];
extern const u8 data_020c75dc[];
extern const u8 data_020c75cc[];
extern const u8 data_020c75e0[];
extern const u8 data_020c75c8[];
extern const u8 data_020c75e4[];
extern const u8 data_020c75d8[];
extern const u8 data_020c75d0[];
/* Handed by address to FieldActor_CopyTexture and FieldActor_CopyPalette. */
extern int data_020d83e8;
extern int data_020d83f0;
/* The scene: 0 outdoors (overlay 3), else indoors. */
extern u8 data_020e54a8;

extern int func_021077e8(int value);

/* func_0200e42c: the set-up; returns 1. The player is bits 30 and 31 of the word at 8
 * (func_02096188); it is noted at 0xdc (func_0203efb0) and with the session's players
 * (func_020962c8). The looks and models are set up from the player's tables, with the
 * player record's items (FieldActor_SetupLooks, FieldActor_SetupPartB, FieldActor_SetupPartC),
 * and the held item (func_0205ec50). Gravity is -5.0 a step, the vertical speed at least -10.0;
 * state 0 is asked for with the start state (bits 22 to 29, func_02096180; priority 9) and the
 * requests are taken at once. The flags are 1 (and 0 outdoors); the start position is the
 * position; the target and the words at 0x804 and 0x810 are -1, those at 0x808, 0x814 and
 * 0x818 0, and 0x81c 0xf; the byte at 0x8e9 is 0x1f, the counter at 0x8e8 0, and no object is
 * met. */
int FieldActor_Init(struct FieldActor *actor)
{
    Actor *base = FieldActor_Base(actor);
    u32 made_with = FIELD_ACTOR_FIELD(actor, u32, 8);
    actor->player = PlayerActorOps_Player(made_with);
    SceneObjectBase_SetId((SceneObjectBase *) actor, (u16) actor->player);
    SessionPlayers_SetActor(actor->player, actor);
    ActorPalettes_SetSlot(at(actor, 0x7a0), data_020c75c4[SessionPlayers_LookIndex(actor->player)]);
    int index = FieldActor_RecordHairColor(actor);
    FieldActor_SetPalettes(actor, index, FieldActor_SunLevel(actor, 1));
    FieldActor_SetupLooks(actor);
    FaceAnimHeaps_Assign(at(actor, 0x70f), data_020c75d4[SessionPlayers_LookIndex(actor->player)]);
    FaceAnimSlots_Assign(at(actor, 0x70e), data_020c75dc[SessionPlayers_LookIndex(actor->player)]);
    FaceTexture_Assign(at(actor, 0x70d), data_020c75cc[SessionPlayers_LookIndex(actor->player)]);
    FaceTexture_Load(at(actor, 0x70d), FieldActor_RecordFace(actor));
    FieldActor_SetupPartB(actor);
    FieldActor_SetupPartC(actor);
    index = SessionPlayers_LookIndex(actor->player);
    u16 item;
    FieldActor_RecordHeldItem(&item, actor);
    HeldItem_Setup((HeldItemObject *) (void *) actor->held, data_020c75e0[index], actor, &item, FieldActor_Record(actor), 0);
    FishingFloat_SetPlayer((FishingFloat *) (void *) at(actor, 0x5c8), actor->player);
    base->gravity = -0x5000;
    base->min_y_velocity = -0xa000;
    FieldActor_RequestState0(actor, PlayerActorOps_StartState(made_with), 9, -1);
    FIELD_ACTOR_PENDING_BITS(actor) &= (u8) ~PENDING_ACTION_SET;
    FieldActor_TakeRequests(actor);
    actor->flags = 0;
    FieldActor_SetFlag(actor, 1);
    if (data_020e54a8 == 0) {
        FieldActor_SetFlag(actor, 0);
    }
    actor->start_position = actor->position;
    actor->target = -1;
    actor->unk_810 = -1;
    FIELD_ACTOR_FIELD(actor, int, 0x804) = -1;
    FIELD_ACTOR_FIELD(actor, int, 0x808) = 0;
    actor->unk_814 = 0;
    actor->unk_818 = 0;
    actor->unk_81C = 0xf;
    FIELD_ACTOR_BODY_ARG(actor) = 0x1f;
    actor->unk_8E8 = 0;
    actor->other = NULL;
    actor->other_result = 0;
    return 1;
}
CLEAN_AS(func_0200e42c, FieldActor_Init)

/* func_0200e654: part C (0x59c) from the player's table data_020c75c8, then its item from the
 * player's record (FieldActor_RecordPartCItem) goes to FieldActor_RequestPartC, and FieldActor_ApplyPartC. */
void FieldActor_SetupPartC(struct FieldActor *actor)
{
    u16 item;
    GlassesLook_SetLook(at(actor, FIELD_ACTOR_PART_C), data_020c75c8[SessionPlayers_LookIndex(actor->player)]);
    FieldActor_RecordPartCItem(&item, actor);
    u16 copy = item;
    FieldActor_RequestPartC(actor, &copy);
    FieldActor_ApplyPartC(actor);
}
CLEAN_AS(func_0200e654, FieldActor_SetupPartC)

/* func_0200e6a4: part B (0x428) from the player's table data_020c75e4, then its item from the
 * player's record (FieldActor_RecordHeadItem, 0xfff1 without a record) goes to FieldActor_RequestHead with
 * FieldActor_RecordHeadKind's and FieldActor_RecordHairColor's values. */
void FieldActor_SetupPartB(struct FieldActor *actor)
{
    u16 item;
    HeadLook_SetLook(at(actor, FIELD_ACTOR_PART_B), data_020c75e4[SessionPlayers_LookIndex(actor->player)]);
    FieldActor_RecordHeadItem(&item, actor);
    u16 copy = item;
    int a = FieldActor_RecordHeadKind(actor);
    int b = FieldActor_RecordHairColor(actor);
    FieldActor_RequestHead(actor, &copy, a, b, 1);
}
CLEAN_AS(func_0200e6a4, FieldActor_SetupPartB)

/* func_0200e704: the looks at 0x389 (from data_020c75d8, then FieldActor_RecordFlag249A's flag) and 0x774
 * (from data_020c75d0), the record's item at FieldActor_RecordCloth to FieldActor_SetCloth, and the pairs of
 * func_021077e8 of the looks handed to FieldActor_CopyTexture and FieldActor_CopyPalette (0x774 with 0x389, with
 * data_020d83e8) and to FieldActor_CopyPalette (0x7a0 with 0x389, with data_020d83f0); then
 * func_0205d034 on 0x389. */
void FieldActor_SetupLooks(struct FieldActor *actor)
{
    u16 item;
    BodyLook_SetLook(at(actor, 0x389), data_020c75d8[SessionPlayers_LookIndex(actor->player)]);
    BodyLook_LoadModel(at(actor, 0x389), FieldActor_RecordFlag249A(actor) != 0);
    ClothSlots_Assign(at(actor, 0x774), data_020c75d0[SessionPlayers_LookIndex(actor->player)]);
    FieldActor_RecordCloth(&item, actor);
    FieldActor_SetCloth(actor, &item);

    int look_389 = func_021077e8(BodyLook_File(at(actor, 0x389)));
    int look_774 = func_021077e8(ClothSlots_SlotFile(at(actor, 0x774)));
    FieldActor_CopyTexture(actor, look_774, look_389, &data_020d83e8, &data_020d83e8);
    FieldActor_CopyPalette(actor, look_774, look_389, &data_020d83e8, &data_020d83e8);
    int look_7a0 = func_021077e8(ActorPalettes_SkinFile(at(actor, 0x7a0)));
    look_389 = func_021077e8(BodyLook_File(at(actor, 0x389)));
    FieldActor_CopyPalette(actor, look_7a0, look_389, &data_020d83f0, &data_020d83f0);
    BodyLook_PlaceTexture(at(actor, 0x389));
}
CLEAN_AS(func_0200e704, FieldActor_SetupLooks)
