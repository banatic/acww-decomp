/* Overlay 9's town object actor: its sound emitter, what it tells of itself, its stand point and
 * its entry machine (town_object_actor.h). */
#include "town_object_actor.h"

#include <stdint.h>

#include "autoload_2/approach.h" /* Math_AbsDiff16 */
#include "autoload_2/fx_math.h"  /* Math_Atan2 */
#include "clean.h"
#include "itcm/vector.h" /* Vec_Add */
#include "ov004/member_pointer.h"
#include "town_object_actor_files.h" /* TownObjectActor_DrawShadows */
#include "town_object_actor_life.h"  /* TownObjectActor_Kind, TownObjectActor_UpdateModelMatrix, TownObjectActor_ViewRange* */
#include "main/animated_model.h"
#include "main/block_020b220c.h"
#include "main/building_lights.h"
#include "main/camera_control.h"
#include "main/collision_area.h"
#include "main/collision_query.h"
#include "main/event_queue.h"
#include "main/item_code.h"
#include "main/message_receiver.h"
#include "main/player_actor_ops.h"
#include "main/scene_exit.h"
#include "main/scene_object_base.h"
#include "main/scene_place.h"
#include "main/scene_query.h"
#include "main/scene_tables.h"
#include "main/talk_object.h"
#include "main/town_objects.h"

static_assert(offsetof(TownObjectActorSound, state.on) == 0x40, "sound on flag");
static_assert(sizeof(TownObjectActorSound) == 0x44, "sound size");
static_assert(offsetof(TownObjectActorLink, unk_10) == 0x10, "link word 0x10");
static_assert(offsetof(TownObjectActorArea, facing_x) == 0x28, "area facing x");
static_assert(offsetof(TownObjectActorArea, facing_z) == 0x30, "area facing z");
static_assert(offsetof(TownObjectActorArea, origin) == 0x3c, "area origin");
static_assert(sizeof(TownObjectActorArea) == 0x54, "area size");
static_assert(sizeof(TownObjectActorRecord) == 10, "record size");
static_assert(offsetof(TownObjectActor, position) == 0x5c, "position");
static_assert(offsetof(TownObjectActor, yaw) == 0x8e, "yaw");
static_assert(offsetof(TownObjectActor, receiver_vtable) == 0xec, "receiver");
static_assert(offsetof(TownObjectActor, message) == 0x10a, "receiver byte 0x1e");
static_assert(offsetof(TownObjectActor, link) == 0x12c, "link");
static_assert(offsetof(TownObjectActor, mode) == 0x134, "mode");
static_assert(offsetof(TownObjectActor, code) == 0x136, "code");
static_assert(offsetof(TownObjectActor, model_object) == 0x13c, "model object");
static_assert(offsetof(TownObjectActor, model) == 0x198, "model");
static_assert(offsetof(TownObjectActor, model_matrix) == 0x1a0, "model matrix");
static_assert(offsetof(TownObjectActor, lights) == 0x1f4, "member 0x1f4");
static_assert(offsetof(TownObjectActor, tile_x) == 0x22c, "tile x");
static_assert(offsetof(TownObjectActor, tile_z) == 0x230, "tile z");
static_assert(offsetof(TownObjectActor, exit_step) == 0x234, "exit step");
static_assert(offsetof(TownObjectActor, flags_235) == 0x235, "flags 0x235");
static_assert(offsetof(TownObjectActor, flags) == 0x236, "flags");
static_assert(offsetof(TownObjectActor, villager_asleep) == 0x237, "villager asleep");
static_assert(offsetof(TownObjectActor, sound) == 0x238, "sound");
static_assert(offsetof(TownObjectActor, state) == 0x27c, "state");
static_assert(offsetof(TownObjectActor, skip_visit) == 0x280, "skip visit");
static_assert(offsetof(TownObjectActor, frames) == 0x282, "frames");
static_assert(offsetof(TownObjectActor, areas) == 0x28c, "areas");
static_assert(offsetof(TownObjectActor, area_count) == 0x290, "area count");
static_assert(offsetof(TownObjectActor, talk_point) == 0x2a8, "talk point");
static_assert(sizeof(TownObjectActor) == 0x2b4, "size");

#define TOWN_OBJECT_ACTOR_RECEIVER_OFFSET 0xec

/* The town objects' codes (main/town_objects.h). */
#define TOWN_OBJECT_ACTOR_CODE_FIRST 0x5000
#define TOWN_OBJECT_ACTOR_CODE_LAST 0x5021

/* The codes the actor treats apart: 0x500a is a free villager plot (main/villager_plots.h). */
#define TOWN_OBJECT_ACTOR_CODE_NO_WAIT 0x500a /* no wait is set on the link when its message ends */

/* The scene events of vtable slot 0x4c. */
#define TOWN_OBJECT_ACTOR_EVENT_TALK 0
#define TOWN_OBJECT_ACTOR_EVENT_CALLED 1
#define TOWN_OBJECT_ACTOR_EVENT_6 6
#define TOWN_OBJECT_ACTOR_EVENT_ENDED 8

/* Sounds play at this volume. */
#define TOWN_OBJECT_ACTOR_SOUND_VOLUME 0x7f

/* Vtable slots it calls. */
#define SLOT_TALK_POINT 0x50   /* TownObjectActor_TalkPointAddress */
#define SLOT_SET_MODE 0x6c     /* TownObjectActor_SetMode */
#define SLOT_PREPARE_TALK 0x78 /* TownObjectActor_PrepareTalk */
#define SLOT_TALK_OPEN 0x7c    /* TownObjectActor_OnTalkOpen */
#define SLOT_TALK_WAIT 0x80    /* TownObjectActor_OnTalkWait */
#define SLOT_TALK_CLOSED 0x84  /* TownObjectActor_OnTalkClosed */
#define SLOT_IS_OPEN 0x8c      /* TownObjectActor_IsOpen */
#define SLOT_STATE_38 0x90     /* TownObjectActor_WalksWithState38 */
#define SLOT_KEEP_X 0x94       /* TownObjectActor_KeepsPointX */

/* What TownObjectActor_GetStandPoint gives: a point 1.0 ahead of the first area, at height 0x200
 * and 0x200 back along z. */
#define TOWN_OBJECT_ACTOR_STAND_HEIGHT 0x200
#define TOWN_OBJECT_ACTOR_STAND_BACK 0x200

/* What TownObjectActor_CanTalkTo allows: a facing within 0x1000 of the actor's turned half round,
 * and for kind 0 a distance under 3.0. */
#define TOWN_OBJECT_ACTOR_TALK_ANGLE 0x1000
#define TOWN_OBJECT_ACTOR_TALK_DISTANCE 0x3000

/* The player kind of player state 0x39 TOWN_OBJECT_ACTOR_WALK_AGAIN asks for. */
#define TOWN_OBJECT_ACTOR_PLAYER_KIND 2
/* The player whose x TownObjectActor_KeepsPointX can ask for. */
#define TOWN_OBJECT_ACTOR_PLAYER 4

/* TOWN_OBJECT_ACTOR_GONE: the frames it waits, more for kind 1; what it registers. */
#define TOWN_OBJECT_ACTOR_GONE_WAIT 20
#define TOWN_OBJECT_ACTOR_GONE_WAIT_KIND_1 12
#define TOWN_OBJECT_ACTOR_GONE_AHEAD 0x1000
#define TOWN_OBJECT_ACTOR_GONE_ARG 0x0f000000

/* The sound emitter's vtable (kind 2). */
extern const u8 data_0213f090[];
/* "obj_etc_error": the receiver's name until a derived class gives it another. */
extern const char data_ov009_02265a18[];
/* The town objects' records, one per code from 0x5000. */
extern const TownObjectActorRecord data_020d1f24[];
/* The camera, while it exists, and its position. */
extern int data_021c67a4;
extern const Vec3 data_021c67d0;

/* The entry machine's tables (member_pointer.h): their guards, the tables and their
 * constants. */
extern u32 data_ov009_02265b28;
extern MemberPointer data_ov009_02265c6c[TOWN_OBJECT_ACTOR_STATE_COUNT];
extern const MemberPointer data_ov009_02265810, data_ov009_022657c8, data_ov009_022657d8, data_ov009_022657e0,
    data_ov009_02265840, data_ov009_02265850, data_ov009_022657b8, data_ov009_022657a8, data_ov009_022657d0;
extern u32 data_ov009_02265b2c;
extern MemberPointer data_ov009_02265c24[TOWN_OBJECT_ACTOR_STATE_COUNT];
extern const MemberPointer data_ov009_022657c0, data_ov009_022657f8, data_ov009_022657f0, data_ov009_02265898,
    data_ov009_02265808, data_ov009_02265820, data_ov009_02265828, data_ov009_02265848, data_ov009_02265888;

/* The field actor asking a player to stand at a point (overlay 3, field_actor.h). */
int FieldActor_PlayerRequestState39(u32 kind, int *x, int *z, int yaw);
int FieldActor_PlayerRequestState38(int *x, int *z, short *yaw);
extern fx32 FX_MulFunc(fx32 a, fx32 b);

/* The receiver part as C++ converts a pointer to the actor to it: NULL stays NULL. */
static void *town_object_actor_receiver(TownObjectActor *actor)
{
    return actor != NULL ? (u8 *) actor + TOWN_OBJECT_ACTOR_RECEIVER_OFFSET : NULL;
}

/* The address of the function in vtable slot `offset`. */
static uintptr_t town_object_actor_slot(const TownObjectActor *actor, u32 offset)
{
    return *(const u32 *) ((const u8 *) actor->vtable + offset);
}

typedef int (*TownObjectActorIntSlotFn)(TownObjectActor *actor);
typedef void (*TownObjectActorVoidSlotFn)(TownObjectActor *actor);
typedef int (*TownObjectActorModeSlotFn)(TownObjectActor *actor, int mode);

static int town_object_actor_call_int(TownObjectActor *actor, u32 offset)
{
    return ((TownObjectActorIntSlotFn) town_object_actor_slot(actor, offset))(actor);
}

static void town_object_actor_call_void(TownObjectActor *actor, u32 offset)
{
    ((TownObjectActorVoidSlotFn) town_object_actor_slot(actor, offset))(actor);
}

static int town_object_actor_set_mode(TownObjectActor *actor, int mode)
{
    return ((TownObjectActorModeSlotFn) town_object_actor_slot(actor, SLOT_SET_MODE))(actor, mode);
}

/* The object's record: the code's, or the first for a code out of range. */
static const TownObjectActorRecord *town_object_actor_record(const TownObjectActor *actor)
{
    u32 code = actor->code;
    if (code >= TOWN_OBJECT_ACTOR_CODE_FIRST && code <= TOWN_OBJECT_ACTOR_CODE_LAST) {
        return &data_020d1f24[code - TOWN_OBJECT_ACTOR_CODE_FIRST];
    }
    return &data_020d1f24[0];
}

/* Whether `*code` is `value`, through func_0204bc64 when func_0204bcdc says it converts. */
static int town_object_actor_code_is(u16 *code, u16 value)
{
    if (ItemCode_IsFurniture(code) != 0) {
        u16 other = value;
        int converted = ItemCode_FurnitureNumber(code);
        return converted == ItemCode_FurnitureNumber(&other);
    }
    return *code == value;
}

/* func_ov009_02262ec0 (vtable slot 0xb8): always 0. */
int TownObjectActor_SlotB8(TownObjectActor *actor)
{
    (void) actor;
    return 0;
}
CLEAN_AS(func_ov009_02262ec0, TownObjectActor_SlotB8)

/* func_ov009_02262ec4 (vtable slot 0xb4, returning a Vec3): its position. */
void TownObjectActor_Position(Vec3 *out, TownObjectActor *actor)
{
    out->x = actor->position.x;
    out->y = actor->position.y;
    out->z = actor->position.z;
}
CLEAN_AS(func_ov009_02262ec4, TownObjectActor_Position)

/* func_ov009_02262ed4: while the emitter is on, plays sound `number` through the sound
 * layer's other entry, at volume 0x7f. */
void TownObjectActorSound_PlayEx(TownObjectActorSound *sound, int number)
{
    if (sound->state.on) {
        SoundEmitter_PlayHeld(&sound->emitter, number, TOWN_OBJECT_ACTOR_SOUND_VOLUME, 0);
    }
}
CLEAN_AS(func_ov009_02262ed4, TownObjectActorSound_PlayEx)

/* func_ov009_02262ef0: while the emitter is on, plays sound `number` at volume 0x7f. */
void TownObjectActorSound_Play(TownObjectActorSound *sound, int number)
{
    if (sound->state.on) {
        SoundEmitter_PlayB(&sound->emitter, number, TOWN_OBJECT_ACTOR_SOUND_VOLUME, 0);
    }
}
CLEAN_AS(func_ov009_02262ef0, TownObjectActorSound_Play)

/* func_ov009_02262f0c: turns the emitter off, through its slot 0x10, when it is on. */
void TownObjectActorSound_TurnOff(TownObjectActorSound *sound)
{
    if (sound->state.on) {
        SoundEmitter_FinishB(&sound->emitter);
        sound->state.on = 0;
    }
}
CLEAN_AS(func_ov009_02262f0c, TownObjectActorSound_TurnOff)

/* func_ov009_02262f2c: while the emitter is on, its sounds follow a copy of `pos`. */
void TownObjectActorSound_UpdateAt(TownObjectActorSound *sound, const Vec3 *pos)
{
    if (sound->state.on) {
        Vec3 copy = *pos;
        SoundEmitter_UpdateAtB(&sound->emitter, &copy);
    }
}
CLEAN_AS(func_ov009_02262f2c, TownObjectActorSound_UpdateAt)

/* func_ov009_02262f54: turns the emitter on, through its slot 0x08, when it is off. */
void TownObjectActorSound_TurnOn(TownObjectActorSound *sound)
{
    if (!sound->state.on) {
        SoundEmitter_ResetB(&sound->emitter);
        sound->state.on = 1;
    }
}
CLEAN_AS(func_ov009_02262f54, TownObjectActorSound_TurnOn)

/* func_ov009_02262f74: the destructor of the emitter (overlay 9's copy of func_020f59ec): its
 * vtable set back, then the base class's. */
void *TownObjectActorSound_Destruct(TownObjectActorSound *sound)
{
    sound->object.vtable = data_0213f090;
    SoundEmitterClass_DestructBase(&sound->object);
    return sound;
}
CLEAN_AS(func_ov009_02262f74, TownObjectActorSound_Destruct)

/* func_ov009_02262f8c: the emitter built (kind 2), off. */
void *TownObjectActorSound_Construct(TownObjectActorSound *sound)
{
    SoundEmitterClass_Construct2(&sound->object);
    sound->state.on = 0;
    return sound;
}
CLEAN_AS(func_ov009_02262f8c, TownObjectActorSound_Construct)

/* func_ov009_02262fa4: whether the first word of the member object at 0x1f4 is set (1 or 0). */
int TownObjectActor_LightsLit(TownObjectActor *actor)
{
    return BuildingLights_IsLit((const BuildingLights *) actor->lights);
}
CLEAN_AS(func_ov009_02262fa4, TownObjectActor_LightsLit)

/* func_ov009_02262fb4: the tile's z. */
u32 TownObjectActor_TileZ(TownObjectActor *actor)
{
    return (u32) actor->tile_z;
}
CLEAN_AS(func_ov009_02262fb4, TownObjectActor_TileZ)

/* func_ov009_02262fc0: the tile's x. */
int TownObjectActor_TileX(TownObjectActor *actor)
{
    return actor->tile_x;
}
CLEAN_AS(func_ov009_02262fc0, TownObjectActor_TileX)

/* func_ov009_02262fcc: the address of the object's code. */
int TownObjectActor_CodeAddress(TownObjectActor *actor)
{
    return (int) (uintptr_t) &actor->code;
}
CLEAN_AS(func_ov009_02262fcc, TownObjectActor_CodeAddress)

/* func_ov009_02262fd8: TownObjectActor_SetModeByKindA while idle; else 0. */
int TownObjectActor_IdleSetModeByKindA(TownObjectActor *actor)
{
    if (actor->state == TOWN_OBJECT_ACTOR_IDLE) {
        return TownObjectActor_SetModeByKindA(actor);
    }
    return 0;
}
CLEAN_AS(func_ov009_02262fd8, TownObjectActor_IdleSetModeByKindA)

/* func_ov009_02262ff8: by its kind, sets mode 3 (kind 1), 2 (kind 2) or 6 (kind 3) through
 * vtable slot 0x6c, and gives its answer; 0 for other kinds. */
int TownObjectActor_SetModeByKindA(TownObjectActor *actor)
{
    switch (TownObjectActor_Kind(actor)) {
        case 2:
            return town_object_actor_set_mode(actor, 2);
        case 3:
            return town_object_actor_set_mode(actor, 6);
        case 1:
            return town_object_actor_set_mode(actor, 3);
        default:
            return 0;
    }
}
CLEAN_AS(func_ov009_02262ff8, TownObjectActor_SetModeByKindA)

/* func_ov009_0226303c: TownObjectActor_SetModeByKindB while idle; else 0. */
int TownObjectActor_IdleSetModeByKindB(TownObjectActor *actor)
{
    if (actor->state == TOWN_OBJECT_ACTOR_IDLE) {
        return TownObjectActor_SetModeByKindB(actor);
    }
    return 0;
}
CLEAN_AS(func_ov009_0226303c, TownObjectActor_IdleSetModeByKindB)

/* func_ov009_0226305c: by its kind, sets mode 3 (kind 1), 1 (kind 2) or 5 (kind 3) through
 * vtable slot 0x6c, and gives its answer; 0 for other kinds. */
int TownObjectActor_SetModeByKindB(TownObjectActor *actor)
{
    switch (TownObjectActor_Kind(actor)) {
        case 2:
            return town_object_actor_set_mode(actor, 1);
        case 3:
            return town_object_actor_set_mode(actor, 5);
        case 1:
            return town_object_actor_set_mode(actor, 3);
        default:
            return 0;
    }
}
CLEAN_AS(func_ov009_0226305c, TownObjectActor_SetModeByKindB)

/* func_ov009_022630a0: whether it is in mode 0. */
int TownObjectActor_IsInMode0(TownObjectActor *actor)
{
    return actor->mode == 0;
}
CLEAN_AS(func_ov009_022630a0, TownObjectActor_IsInMode0)

/* func_ov009_022630b4: TOWN_OBJECT_ACTOR_FLAG_OUT_OF_VIEW cleared, then set again when
 * TownObjectActor_IsOutOfView says so. */
void TownObjectActor_UpdateOutOfView(TownObjectActor *actor)
{
    actor->flags_235 &= ~TOWN_OBJECT_ACTOR_FLAG_OUT_OF_VIEW;
    if (TownObjectActor_IsOutOfView(actor)) {
        actor->flags_235 |= TOWN_OBJECT_ACTOR_FLAG_OUT_OF_VIEW;
    }
}
CLEAN_AS(func_ov009_022630b4, TownObjectActor_UpdateOutOfView)

/* func_ov009_022630e4: whether it is outside the camera's box: there is no camera, or along x
 * it is further from the camera than the record's half-width, or along z further ahead or
 * behind than the record's depths. */
int TownObjectActor_IsOutOfView(TownObjectActor *actor)
{
    if (data_021c67a4 == 0) {
        return 1;
    }
    int dx = actor->position.x - data_021c67d0.x;
    if (dx < 0) {
        dx = -dx;
    }
    int dz = actor->position.z - data_021c67d0.z;
    if (dx > TownObjectActor_ViewRangeX(actor)) {
        return 1;
    }
    if (dz > TownObjectActor_ViewRangeZAhead(actor)) {
        return 1;
    }
    if (dz < -TownObjectActor_ViewRangeZBehind(actor)) {
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov009_022630e4, TownObjectActor_IsOutOfView)

/* func_ov009_0226313c (vtable slot 0x98): always 0. */
int TownObjectActor_Slot98(TownObjectActor *actor)
{
    (void) actor;
    return 0;
}
CLEAN_AS(func_ov009_0226313c, TownObjectActor_Slot98)

/* func_ov009_02263140 (vtable slot 0x94): whether the player is asked to stand at the stand
 * point's x (else at player 4's own x); always 1 here. */
int TownObjectActor_KeepsPointX(TownObjectActor *actor)
{
    (void) actor;
    return 1;
}
CLEAN_AS(func_ov009_02263140, TownObjectActor_KeepsPointX)

/* func_ov009_02263144 (vtable slot 0xb0): whether its drawing draws the model; always 1
 * here. */
int TownObjectActor_DrawsModel(TownObjectActor *actor)
{
    (void) actor;
    return 1;
}
CLEAN_AS(func_ov009_02263144, TownObjectActor_DrawsModel)

/* func_ov009_02263148 (vtable slot 0x90): whether TOWN_OBJECT_ACTOR_WALK asks for player state 0x38
 * (else 0x39); always 0 here. */
int TownObjectActor_WalksWithState38(TownObjectActor *actor)
{
    (void) actor;
    return 0;
}
CLEAN_AS(func_ov009_02263148, TownObjectActor_WalksWithState38)

/* func_ov009_0226314c (vtable slot 0xa0): byte 5 of the object's record. */
int TownObjectActor_RecordByte5(TownObjectActor *actor)
{
    TownObjectActorRecord record;
    TownObjects_CopyRecord(&record, town_object_actor_record(actor));
    int value = TownObjects_RecordByte5(&record);
    TownObjects_DestroyRecord(&record);
    return value;
}
CLEAN_AS(func_ov009_0226314c, TownObjectActor_RecordByte5)

/* func_ov009_022631b4: the object's id in main's table at data_021f69d0 (byte 4 of its
 * record, signed). */
int TownObjectActor_RecordId(TownObjectActor *actor)
{
    TownObjectActorRecord record;
    TownObjects_CopyRecord(&record, town_object_actor_record(actor));
    int value = TownObjects_RecordId(&record);
    TownObjects_DestroyRecord(&record);
    return value;
}
CLEAN_AS(func_ov009_022631b4, TownObjectActor_RecordId)

/* func_ov009_0226321c: where a player stands to talk to it, and whether it has a place for
 * that. With areas, the point is 1.0 ahead of the first area's point along the direction it
 * faces, at height 0x200 and 0x200 back along z, and `angle` (when given) faces the area,
 * turned half round from its direction; each is left alone when NULL. Without, the point is
 * its position and the result 0.
 * QUIRK: without areas `point` is written even when NULL. */
int TownObjectActor_GetStandPoint(TownObjectActor *actor, Vec3 *point, s16 *angle)
{
    if (actor->areas == NULL || actor->area_count == 0) {
        *point = actor->position;
        return 0;
    }
    TownObjectActorArea *area = actor->areas;
    s16 facing = Math_Atan2(area->facing_x, area->facing_z);
    Vec3 ahead;
    ahead.z = FX_MulFunc(FX32_ONE, area->facing_z);
    ahead.x = FX_MulFunc(FX32_ONE, area->facing_x);
    ahead.y = 0;
    if (angle != NULL) {
        *angle = (s16) (facing + 0x8000);
    }
    if (point != NULL) {
        Vec3 sum;
        Vec_Add(&sum, CollisionArea_Center((CollisionArea *) area), &ahead);
        *point = sum;
        point->y = TOWN_OBJECT_ACTOR_STAND_HEIGHT;
        point->z -= TOWN_OBJECT_ACTOR_STAND_BACK;
    }
    return 1;
}
CLEAN_AS(func_ov009_0226321c, TownObjectActor_GetStandPoint)

/* func_ov009_022632c8: while it has a model, draws it with a copy of its matrix. */
void TownObjectActor_DrawModel(TownObjectActor *actor)
{
    if (actor->model == NULL) {
        return;
    }
    TownObjectActor_UpdateModelMatrix(actor, NULL);
    AnimatedModel_Draw((AnimatedModel *) actor->model_object, 0);
    Mtx43 matrix = actor->model_matrix;
    TownObjectActor_DrawShadows(actor, &matrix);
}
CLEAN_AS(func_ov009_022632c8, TownObjectActor_DrawModel)

/* func_ov009_02263314 (vtable slot 0x84, once the link has closed in TOWN_OBJECT_ACTOR_TALK_END):
 * nothing. */
void TownObjectActor_OnTalkClosed(TownObjectActor *actor)
{
    (void) actor;
}
CLEAN_AS(func_ov009_02263314, TownObjectActor_OnTalkClosed)

/* func_ov009_02263318 (vtable slot 0x80, each frame the link stays open in
 * TOWN_OBJECT_ACTOR_TALK_END): nothing. */
void TownObjectActor_OnTalkWait(TownObjectActor *actor)
{
    (void) actor;
}
CLEAN_AS(func_ov009_02263318, TownObjectActor_OnTalkWait)

/* func_ov009_0226331c (vtable slot 0x7c, once the link has opened in TOWN_OBJECT_ACTOR_TALK):
 * nothing. */
void TownObjectActor_OnTalkOpen(TownObjectActor *actor)
{
    (void) actor;
}
CLEAN_AS(func_ov009_0226331c, TownObjectActor_OnTalkOpen)

/* func_ov009_02263320 (vtable slot 0x78, entering TOWN_OBJECT_ACTOR_TALK): names the receiver
 * "obj_etc_error" and clears its message. */
void TownObjectActor_PrepareTalk(TownObjectActor *actor)
{
    MessageReceiver_SetName((MessageReceiver *) &actor->receiver_vtable, data_ov009_02265a18);
    actor->message = 0;
}
CLEAN_AS(func_ov009_02263320, TownObjectActor_PrepareTalk)

/* func_ov009_02263344 (receiver slot 0x14, also vtable slot 0x88: a message ended): sets the
 * link's word at 0x10 to 100, unless the object's code is 0x500a (a free plot).
 * REQUIRES: the receiver has a link when the code is not 0x500a. */
void TownObjectActor_OnMessageEnd(TownObjectActor *actor)
{
    if (!town_object_actor_code_is(&actor->code, TOWN_OBJECT_ACTOR_CODE_NO_WAIT)) {
        TalkObject_SetAutoAdvance((TalkObject *) actor->link, 100);
    }
}
CLEAN_AS(func_ov009_02263344, TownObjectActor_OnMessageEnd)

/* _ZN18Obj_ov009_022658dc19func_ov009_022633acEji (vtable slot 0x4c): the scene's events: 0
 * and 1 start a visit, 8 makes it idle; 6 clears bit 0 of the object's visit record, main's
 * byte at data_021f4b14, asks for main's table at data_021f69d0 (for nothing), resets the one at
 * data_021f69b8 and sets the byte at 0x234 to 1. Others do nothing. */
void TownObjectActor_OnSceneEvent(TownObjectActor *actor, unsigned int event, int arg)
{
    (void) arg;
    switch (event) {
        case TOWN_OBJECT_ACTOR_EVENT_6:
            TownObjects_Leave(actor->code, 0);
            TownObjects_ClearExtraVisitors();
            SceneTables_EntryRecord();
            ScenePlace_ResetMarked();
            actor->exit_step = 1;
            break;
        case TOWN_OBJECT_ACTOR_EVENT_TALK:
        case TOWN_OBJECT_ACTOR_EVENT_CALLED:
            TownObjectActor_SetState(actor, TOWN_OBJECT_ACTOR_VISIT);
            break;
        case TOWN_OBJECT_ACTOR_EVENT_ENDED:
            TownObjectActor_SetState(actor, TOWN_OBJECT_ACTOR_IDLE);
            break;
        default:
            break;
    }
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_022633acEji, TownObjectActor_OnSceneEvent)

/* func_ov009_02263410 (vtable slot 0x48): whether `other` can talk to it. It must face it
 * (within 0x1000 of its direction turned half round). An actor of kind 0 then needs vtable
 * slot 0x8c (TownObjectActor_IsOpen) to say no and `other`'s talk point within 3.0 of its own in the ground plane;
 * any other kind needs TOWN_OBJECT_ACTOR_FLAG_TALKABLE and kind 2, and the talk skips the visit
 * record when it is not open (slot 0x8c). Past those first checks func_0203edd0 runs on it.
 * QUIRK: for kind 0, func_0203edd0 runs and the visit record is skipped even when `other` is
 * too far away. */
int TownObjectActor_CanTalkTo(TownObjectActor *actor, TownObjectActor *other)
{
    if (other == NULL) {
        return 0;
    }
    if (Math_AbsDiff16((s16) (actor->yaw + 0x8000), other->yaw) > TOWN_OBJECT_ACTOR_TALK_ANGLE) {
        return 0;
    }
    if (TownObjectActor_Kind(actor) != 0) {
        if (!(actor->flags_235 & TOWN_OBJECT_ACTOR_FLAG_TALKABLE) || TownObjectActor_Kind(actor) != 2) {
            return 0;
        }
        int is_open = town_object_actor_call_int(actor, SLOT_IS_OPEN);
        SceneObjectBase_ClearApproach((SceneObjectBase *) actor);
        actor->skip_visit = is_open == 0;
        return 1;
    }
    if (town_object_actor_call_int(actor, SLOT_IS_OPEN) != 0) {
        return 0;
    }
    const Vec3 *theirs = (const Vec3 *) (uintptr_t) town_object_actor_call_int(other, SLOT_TALK_POINT);
    const Vec3 *mine = (const Vec3 *) (uintptr_t) town_object_actor_call_int(actor, SLOT_TALK_POINT);
    fx32 distance = Vec_DistanceXZ(theirs, mine);
    SceneObjectBase_ClearApproach((SceneObjectBase *) actor);
    actor->skip_visit = 1;
    return distance < TOWN_OBJECT_ACTOR_TALK_DISTANCE;
}
CLEAN_AS(func_ov009_02263410, TownObjectActor_CanTalkTo)

/* func_ov009_022634e4 (vtable slot 0x50): the address of its talk point. */
int TownObjectActor_TalkPointAddress(TownObjectActor *actor)
{
    return (int) (uintptr_t) &actor->talk_point;
}
CLEAN_AS(func_ov009_022634e4, TownObjectActor_TalkPointAddress)

/* _ZN18Obj_ov009_022658dc19func_ov009_022634f0Ev (update of TOWN_OBJECT_ACTOR_WALK_AGAIN): when it
 * has a stand point, asks the player to stand there (player state 0x39, kind 2), at player
 * 4's own x when vtable slot 0x94 says no and that player exists, and moves to
 * TOWN_OBJECT_ACTOR_GONE when the player agrees. */
void TownObjectActor_UpdateWalkAgain(TownObjectActor *actor)
{
    Vec3 point;
    s16 angle;
    if (!TownObjectActor_GetStandPoint(actor, &point, &angle)) {
        return;
    }
    int x = point.x;
    int z = point.z;
    if (town_object_actor_call_int(actor, SLOT_KEEP_X) == 0) {
        const Vec3 *player = PlayerActorOps_StartPosition(TOWN_OBJECT_ACTOR_PLAYER);
        if (player != NULL) {
            x = player->x;
        }
    }
    if (FieldActor_PlayerRequestState39(TOWN_OBJECT_ACTOR_PLAYER_KIND, &x, &z, angle)) {
        TownObjectActor_SetState(actor, TOWN_OBJECT_ACTOR_GONE);
    }
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_022634f0Ev, TownObjectActor_UpdateWalkAgain)

/* func_ov009_02263548 (entry of TOWN_OBJECT_ACTOR_WALK_AGAIN) */
int TownObjectActor_EnterWalkAgain(TownObjectActor *actor)
{
    (void) actor;
    return 1;
}
CLEAN_AS(func_ov009_02263548, TownObjectActor_EnterWalkAgain)

/* _ZN18Obj_ov009_022658dc19func_ov009_0226354cEv (update of TOWN_OBJECT_ACTOR_LEAVE_AGAIN): on to
 * TOWN_OBJECT_ACTOR_WALK_AGAIN once func_02096174 agrees. */
void TownObjectActor_UpdateLeaveAgain(TownObjectActor *actor)
{
    if (PlayerActorOps_TestOwnFlag1()) {
        TownObjectActor_SetState(actor, TOWN_OBJECT_ACTOR_WALK_AGAIN);
    }
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_0226354cEv, TownObjectActor_UpdateLeaveAgain)

/* func_ov009_02263568 (entry of TOWN_OBJECT_ACTOR_LEAVE_AGAIN) */
int TownObjectActor_EnterLeaveAgain(TownObjectActor *actor)
{
    (void) actor;
    PlayerActorOps_Approach(0);
    return 1;
}
CLEAN_AS(func_ov009_02263568, TownObjectActor_EnterLeaveAgain)

/* func_ov009_0226357c (update of TOWN_OBJECT_ACTOR_GONE): counts the frames. From 20 of them (32 for
 * kind 1) on, when it has a stand point and main's table takes its id, it adds to the table at
 * that point, one unit further along z and at height func_020310c8 (0x200), turned half round,
 * with its tile; then hands its kind to func_020b22ac and sets TOWN_OBJECT_ACTOR_FLAG_GONE.
 * QUIRK: its kind is asked for once more than used; the counter is 16 bits and wraps, and
 * nothing stops the update after the flag is set. */
void TownObjectActor_UpdateGone(TownObjectActor *actor)
{
    actor->frames++;
    TownObjectActor_Kind(actor);
    int wait = TOWN_OBJECT_ACTOR_GONE_WAIT;
    if (TownObjectActor_Kind(actor) == 1) {
        wait += TOWN_OBJECT_ACTOR_GONE_WAIT_KIND_1;
    }
    if (actor->frames < wait) {
        return;
    }
    int id = TownObjectActor_RecordId(actor);
    Vec3 point;
    s16 angle;
    if (!TownObjectActor_GetStandPoint(actor, &point, &angle)) {
        return;
    }
    if (!SceneExit_Take((SceneExit *) (uintptr_t) SceneTables_EntryRecord(), id)) {
        return;
    }
    point.y = CollisionQuery_FloorHeight(0);
    point.z += TOWN_OBJECT_ACTOR_GONE_AHEAD;
    int table = SceneTables_EntryRecord();
    int scene = SceneQuery_Current();
    ScenePlace_SetMarked(table, scene, &point, TOWN_OBJECT_ACTOR_GONE_ARG, (short) (angle + 0x8000), actor->tile_x,
                         actor->tile_z);
    Block020b220c_SetGoneKind(TownObjectActor_Kind(actor));
    actor->flags |= TOWN_OBJECT_ACTOR_FLAG_GONE;
}
CLEAN_AS(func_ov009_0226357c, TownObjectActor_UpdateGone)

/* func_ov009_02263648 (entry of TOWN_OBJECT_ACTOR_GONE): the frame count starts again. */
int TownObjectActor_EnterGone(TownObjectActor *actor)
{
    actor->frames = 0;
    return 1;
}
CLEAN_AS(func_ov009_02263648, TownObjectActor_EnterGone)

/* _ZN18Obj_ov009_022658dc19func_ov009_02263658Ev (update of TOWN_OBJECT_ACTOR_WALK): once
 * func_02096168 agrees, an actor of kind 2 or 3 calls func_0203aec4 and moves to
 * TOWN_OBJECT_ACTOR_GONE.
 * QUIRK: other kinds stay in TOWN_OBJECT_ACTOR_WALK. */
void TownObjectActor_UpdateWalk(TownObjectActor *actor)
{
    if (!PlayerActorOps_TestOwnFlag4()) {
        return;
    }
    switch (TownObjectActor_Kind(actor)) {
        case 2:
        case 3:
            CameraControl_SetMode3();
            TownObjectActor_SetState(actor, TOWN_OBJECT_ACTOR_GONE);
            break;
        default:
            break;
    }
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_02263658Ev, TownObjectActor_UpdateWalk)

/* _ZN18Obj_ov009_022658dc19func_ov009_02263694Ev (entry of TOWN_OBJECT_ACTOR_WALK): whether the
 * player agreed to stand at the stand point: at player 4's own x when vtable slot 0x94 says no
 * and that player exists; through player state 0x38 when slot 0x90 says so, else 0x39 (kind 1
 * when its own kind is 2, else 0). 0 without a stand point. */
int TownObjectActor_EnterWalk(TownObjectActor *actor)
{
    Vec3 point;
    s16 angle;
    if (!TownObjectActor_GetStandPoint(actor, &point, &angle)) {
        return 0;
    }
    int x = point.x;
    int z = point.z;
    if (town_object_actor_call_int(actor, SLOT_KEEP_X) == 0) {
        const Vec3 *player = PlayerActorOps_StartPosition(TOWN_OBJECT_ACTOR_PLAYER);
        if (player != NULL) {
            x = player->x;
        }
    }
    if (town_object_actor_call_int(actor, SLOT_STATE_38) != 0) {
        return FieldActor_PlayerRequestState38(&x, &z, &angle) != 0;
    }
    u32 kind = TownObjectActor_Kind(actor) == 2;
    return FieldActor_PlayerRequestState39(kind, &x, &z, angle) != 0;
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_02263694Ev, TownObjectActor_EnterWalk)

/* _ZN18Obj_ov009_022658dc19func_ov009_02263718Ev (update of TOWN_OBJECT_ACTOR_LEAVE): on to
 * TOWN_OBJECT_ACTOR_WALK once func_02096174 agrees. */
void TownObjectActor_UpdateLeave(TownObjectActor *actor)
{
    if (PlayerActorOps_TestOwnFlag1()) {
        TownObjectActor_SetState(actor, TOWN_OBJECT_ACTOR_WALK);
    }
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_02263718Ev, TownObjectActor_UpdateLeave)

/* func_ov009_02263734 (entry of TOWN_OBJECT_ACTOR_LEAVE) */
int TownObjectActor_EnterLeave(TownObjectActor *actor)
{
    (void) actor;
    PlayerActorOps_Approach(0);
    return 1;
}
CLEAN_AS(func_ov009_02263734, TownObjectActor_EnterLeave)

/* _ZN18Obj_ov009_022658dc19func_ov009_02263748Ev (update of TOWN_OBJECT_ACTOR_TALK_END): once the
 * link has closed, vtable slot 0x84, the receiver handed back and the scene goes on; until
 * then (or without a link) slot 0x80. Its state stays TOWN_OBJECT_ACTOR_TALK_END until the scene
 * sets another. */
void TownObjectActor_UpdateTalkEnd(TownObjectActor *actor)
{
    if (actor->link != NULL && actor->link->status == 0) {
        town_object_actor_call_void(actor, SLOT_TALK_CLOSED);
        SceneObjectBase_ReleaseReceiver((SceneObjectBase *) actor, town_object_actor_receiver(actor));
        EventQueue_FinishObjectEvent(actor);
    } else {
        town_object_actor_call_void(actor, SLOT_TALK_WAIT);
    }
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_02263748Ev, TownObjectActor_UpdateTalkEnd)

/* func_ov009_0226378c (entry of TOWN_OBJECT_ACTOR_TALK_END) */
int TownObjectActor_EnterTalkEnd(TownObjectActor *actor)
{
    (void) actor;
    return 1;
}
CLEAN_AS(func_ov009_0226378c, TownObjectActor_EnterTalkEnd)

/* _ZN18Obj_ov009_022658dc19func_ov009_02263790Ev (update of TOWN_OBJECT_ACTOR_TALK): once the link
 * is open, vtable slot 0x7c and on to TOWN_OBJECT_ACTOR_TALK_END. */
void TownObjectActor_UpdateTalk(TownObjectActor *actor)
{
    if (actor->link != NULL && actor->link->status != 0) {
        town_object_actor_call_void(actor, SLOT_TALK_OPEN);
        TownObjectActor_SetState(actor, TOWN_OBJECT_ACTOR_TALK_END);
    }
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_02263790Ev, TownObjectActor_UpdateTalk)

/* _ZN18Obj_ov009_022658dc19func_ov009_022637bcEv (entry of TOWN_OBJECT_ACTOR_TALK): takes the
 * receiver, raises the link's request and prepares the talk (vtable slot 0x78).
 * REQUIRES: the receiver has a link once SceneObjectBase_TakeReceiver has taken it. */
int TownObjectActor_EnterTalk(TownObjectActor *actor)
{
    SceneObjectBase_TakeReceiver((SceneObjectBase *) actor, town_object_actor_receiver(actor));
    actor->link->requested = 1;
    town_object_actor_call_void(actor, SLOT_PREPARE_TALK);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_022637bcEv, TownObjectActor_EnterTalk)

/* _ZN18Obj_ov009_022658dc19func_ov009_022637ecEv (update of TOWN_OBJECT_ACTOR_VISIT): when the talk
 * skips the visit record, on to TOWN_OBJECT_ACTOR_TALK. Else, once main has an answer (nonzero), it
 * keeps whether it is 2 (TOWN_OBJECT_ACTOR_FLAG_FULL, too many inside) and whether it is 3
 * (villager_asleep, TOWN_OBJECTS_ANSWER_ASLEEP); either starts
 * the talk, else kind 1 moves to TOWN_OBJECT_ACTOR_LEAVE_AGAIN and others to TOWN_OBJECT_ACTOR_LEAVE. */
void TownObjectActor_UpdateVisit(TownObjectActor *actor)
{
    if (actor->skip_visit) {
        TownObjectActor_SetState(actor, TOWN_OBJECT_ACTOR_TALK);
        return;
    }
    int answer = TownObjects_VisitAnswer(actor->code);
    if (answer == 0) {
        return;
    }
    actor->flags = (u8) ((actor->flags & ~TOWN_OBJECT_ACTOR_FLAG_FULL) | (answer == 2 ? TOWN_OBJECT_ACTOR_FLAG_FULL : 0));
    actor->villager_asleep = answer == 3;
    if ((actor->flags & TOWN_OBJECT_ACTOR_FLAG_FULL) || actor->villager_asleep) {
        TownObjectActor_SetState(actor, TOWN_OBJECT_ACTOR_TALK);
    } else if (TownObjectActor_Kind(actor) == 1) {
        TownObjectActor_SetState(actor, TOWN_OBJECT_ACTOR_LEAVE_AGAIN);
    } else {
        TownObjectActor_SetState(actor, TOWN_OBJECT_ACTOR_LEAVE);
    }
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_022637ecEv, TownObjectActor_UpdateVisit)

/* func_ov009_02263888 (entry of TOWN_OBJECT_ACTOR_VISIT): asks main for the visit record unless the
 * talk skips it, and forgets the last answer. */
int TownObjectActor_EnterVisit(TownObjectActor *actor)
{
    if (!actor->skip_visit) {
        TownObjects_RequestVisit(actor->code);
    }
    actor->flags &= ~TOWN_OBJECT_ACTOR_FLAG_FULL;
    actor->villager_asleep = 0;
    return 1;
}
CLEAN_AS(func_ov009_02263888, TownObjectActor_EnterVisit)

/* func_ov009_022638c8 (update of TOWN_OBJECT_ACTOR_IDLE): nothing. */
void TownObjectActor_UpdateIdle(TownObjectActor *actor)
{
    (void) actor;
}
CLEAN_AS(func_ov009_022638c8, TownObjectActor_UpdateIdle)

/* func_ov009_022638cc (entry of TOWN_OBJECT_ACTOR_IDLE) */
int TownObjectActor_EnterIdle(TownObjectActor *actor)
{
    (void) actor;
    return 1;
}
CLEAN_AS(func_ov009_022638cc, TownObjectActor_EnterIdle)

/* _ZN18Obj_ov009_022658dc19func_ov009_022638d0Ev: the state's update, through its table.
 * REQUIRES: the state is not negative (TownObjectActor_SetState only sets 0 to 8). */
void TownObjectActor_UpdateState(TownObjectActor *actor)
{
    static const MemberPointer *const updates[TOWN_OBJECT_ACTOR_STATE_COUNT] = {
        &data_ov009_02265810, /* TownObjectActor_UpdateIdle */
        &data_ov009_022657c8, /* TownObjectActor_UpdateVisit */
        &data_ov009_022657d8, /* TownObjectActor_UpdateTalk */
        &data_ov009_022657e0, /* TownObjectActor_UpdateTalkEnd */
        &data_ov009_02265840, /* TownObjectActor_UpdateLeave */
        &data_ov009_02265850, /* TownObjectActor_UpdateWalk */
        &data_ov009_022657b8, /* TownObjectActor_UpdateGone */
        &data_ov009_022657a8, /* TownObjectActor_UpdateLeaveAgain */
        &data_ov009_022657d0, /* TownObjectActor_UpdateWalkAgain */
    };
    MemberTable_InitOnce(&data_ov009_02265b28, data_ov009_02265c6c, updates, TOWN_OBJECT_ACTOR_STATE_COUNT);
    if (actor->state < TOWN_OBJECT_ACTOR_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov009_02265c6c[actor->state], actor);
    }
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_022638d0Ev, TownObjectActor_UpdateState)

/* _ZN18Obj_ov009_022658dc19func_ov009_022639a0Ei: enters state `state` if its entry (through a
 * table) agrees; whether it did. States 9 and above do not exist.
 * REQUIRES: `state` is not negative. */
int TownObjectActor_SetState(TownObjectActor *actor, int state)
{
    static const MemberPointer *const entries[TOWN_OBJECT_ACTOR_STATE_COUNT] = {
        &data_ov009_022657c0, /* TownObjectActor_EnterIdle */
        &data_ov009_022657f8, /* TownObjectActor_EnterVisit */
        &data_ov009_022657f0, /* TownObjectActor_EnterTalk */
        &data_ov009_02265898, /* TownObjectActor_EnterTalkEnd */
        &data_ov009_02265808, /* TownObjectActor_EnterLeave */
        &data_ov009_02265820, /* TownObjectActor_EnterWalk */
        &data_ov009_02265828, /* TownObjectActor_EnterGone */
        &data_ov009_02265848, /* TownObjectActor_EnterLeaveAgain */
        &data_ov009_02265888, /* TownObjectActor_EnterWalkAgain */
    };
    MemberTable_InitOnce(&data_ov009_02265b2c, data_ov009_02265c24, entries, TOWN_OBJECT_ACTOR_STATE_COUNT);
    if (state < TOWN_OBJECT_ACTOR_STATE_COUNT && MemberPointer_CallInt(&data_ov009_02265c24[state], actor) != 0) {
        actor->state = state;
        return 1;
    }
    return 0;
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_022639a0Ei, TownObjectActor_SetState)

/* _ZN18Obj_ov009_022658dc19func_ov009_02263a80Ev (run of mode 6): back to mode 0, through
 * vtable slot 0x6c. */
void TownObjectActor_RunMode6(TownObjectActor *actor)
{
    town_object_actor_set_mode(actor, 0);
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_02263a80Ev, TownObjectActor_RunMode6)

/* func_ov009_02263a94 (entry of mode 6) */
int TownObjectActor_EnterMode6(void)
{
    return 1;
}
CLEAN_AS(func_ov009_02263a94, TownObjectActor_EnterMode6)

/* _ZN18Obj_ov009_022658dc19func_ov009_02263a98Ev (run of mode 5): back to mode 0, through
 * vtable slot 0x6c. */
void TownObjectActor_RunMode5(TownObjectActor *actor)
{
    town_object_actor_set_mode(actor, 0);
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_02263a98Ev, TownObjectActor_RunMode5)

/* func_ov009_02263aac (entry of mode 5) */
int TownObjectActor_EnterMode5(void)
{
    return 1;
}
CLEAN_AS(func_ov009_02263aac, TownObjectActor_EnterMode5)
