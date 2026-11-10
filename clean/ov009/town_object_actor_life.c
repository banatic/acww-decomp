/* The town object actor as a process (town_object_actor_life.h). */
#include "town_object_actor_life.h"

#include <stdint.h>

#include "autoload_2/heap.h" /* Heap_AllocAuxZeroed, Heap_FreeAux */
#include "clean.h"
#include "main/actor.h"              /* Actor_CanDraw, Actor_Run */
#include "main/animated_model.h"     /* AnimatedModel */
#include "main/building_lights.h"    /* BuildingLights */
#include "main/calendar.h"           /* Calendar_Now */
#include "main/camera_control.h"     /* CameraControl_IsPastGoalZ */
#include "main/globe.h"              /* Globe_Bend, Globe_BendFar */
#include "main/item_code.h"          /* ItemCode_IsFurniture, ItemCode_FurnitureNumber */
#include "main/map_code.h"           /* MapCode_IsStore */
#include "main/model_object.h"       /* ModelObject_ReleaseRender, ModelObject_SetInitHook */
#include "main/model_pool.h"         /* ModelPoolSlot_Construct, ModelPoolSlot_Destruct */
#include "main/music_queue.h"        /* Music2d0_SetDelay */
#include "main/object_claim.h"       /* ObjectClaim_Release */
#include "main/player_actor_ops.h"   /* PlayerActorOps_QueueBelow6 */
#include "main/scene_object_base.h"  /* SceneObjectBase */
#include "main/scene_query.h"        /* SceneQuery_Current */
#include "main/shops.h"              /* Shops_SetPendingState */
#include "main/talk_receiver.h"      /* TalkReceiver_ConstructBase, TalkReceiver_Destruct */
#include "main/town_objects.h"       /* TownObjects_* */
#include "ov003/object_actors.h"     /* ObjectActors_Add, ObjectActors_Remove, ObjectActors_SetPoseFlag */
#include "town_object_actor_area.h"  /* TownObjectActor_AddPickFaces, TownObjectActor_BuildAreas, ... */
#include "town_object_actor_files.h" /* TownObjectActorFiles_Of, TownObjectActor_LoadModel, ... */

static_assert(offsetof(TownObjectActor, pivot) == 0xc4, "pivot");
static_assert(offsetof(TownObjectActor, pitch) == 0xd0, "pitch");
static_assert(offsetof(TownObjectActor, exit_step) == 0x234, "exit step");
static_assert(offsetof(TownObjectActor, model_slot) == 0x292, "model slot");
static_assert(offsetof(TownObjectActor, bounds_centre) == 0x294, "bounds centre");
static_assert(offsetof(TownObjectActor, bounds_width) == 0x2a0, "bounds width");
static_assert(offsetof(TownObjectActor, bounds_depth) == 0x2a4, "bounds depth");
static_assert(sizeof(AnimatedModel) >= 0xb4 && offsetof(AnimatedModel, object) == 0, "animated model");
static_assert(sizeof(BuildingLights) == 0x38, "building lights");

#define TOWN_OBJECT_ACTOR_SIZE 0x2b4
#define TOWN_OBJECT_ACTOR_RECEIVER 0xec

/* What it is made with: the code no building has. */
#define TOWN_OBJECT_ACTOR_NO_CODE 0xfff1

/* The vtable slots called here. */
#define TOWN_OBJECT_ACTOR_LIFE_SLOT_NODE 0x60       /* TownObjectActor_Slot60: told of each node drawn */
#define TOWN_OBJECT_ACTOR_LIFE_SLOT_ANIM_0 0x64     /* TownObjectActor_JointAnim0 */
#define TOWN_OBJECT_ACTOR_LIFE_SLOT_ANIM_1 0x68     /* TownObjectActor_JointAnim1 */
#define TOWN_OBJECT_ACTOR_LIFE_SLOT_SET_MODE 0x6c   /* TownObjectActor_SetMode */
#define TOWN_OBJECT_ACTOR_LIFE_SLOT_INIT_END 0x70   /* TownObjectActor_Slot70: what TownObjectActor_Init returns */
#define TOWN_OBJECT_ACTOR_LIFE_SLOT_RUN_MODE 0x74   /* TownObjectActor_RunMode */
#define TOWN_OBJECT_ACTOR_LIFE_SLOT_IS_OPEN 0x8c    /* TownObjectActor_IsOpen */
#define TOWN_OBJECT_ACTOR_LIFE_SLOT_LIGHTS_ON 0x9c  /* TownObjectActor_LightsOn */
#define TOWN_OBJECT_ACTOR_LIFE_SLOT_FLASH 0xa0      /* TownObjectActor_RecordByte5 */
#define TOWN_OBJECT_ACTOR_LIFE_SLOT_ARCHIVE 0xa4    /* TownObjectActor_ArchivePath */
#define TOWN_OBJECT_ACTOR_LIFE_SLOT_TEXTURE 0xa8    /* TownObjectActor_TexturePath */
#define TOWN_OBJECT_ACTOR_LIFE_SLOT_LIT 0xac        /* TownObjectActor_LitTexturePath */
#define TOWN_OBJECT_ACTOR_LIFE_SLOT_DRAWS 0xb0      /* TownObjectActor_DrawsModel */
#define TOWN_OBJECT_ACTOR_LIFE_SLOT_POSITION 0xb4   /* TownObjectActor_Position */
#define TOWN_OBJECT_ACTOR_LIFE_SLOT_OWN_MATRIX 0xb8 /* TownObjectActor_SlotB8: a matrix of its own */

/* The buildings treated apart (what they are is not known yet): 0x501d keeps the mode main
 * has recorded for it, 0x500b is drawn whatever the camera's box says, and 0x5012 and 0x5013
 * let the player out with music delay 4. */
#define TOWN_OBJECT_ACTOR_CODE_RECORDED_MODE 0x501d
#define TOWN_OBJECT_ACTOR_CODE_ALWAYS_DRAWN 0x500b
#define TOWN_OBJECT_ACTOR_CODE_EXIT_A 0x5012
#define TOWN_OBJECT_ACTOR_CODE_EXIT_B 0x5013

/* The scene in which neither the entry machine nor the pen's faces run. */
#define TOWN_OBJECT_ACTOR_SCENE_STILL 0x2c

/* Night: before 6:00 or from 18:00. */
#define TOWN_OBJECT_ACTOR_DAY_START 6
#define TOWN_OBJECT_ACTOR_DAY_END 18

/* The record's lengths, in tiles, and a tile's width. */
#define TOWN_OBJECT_ACTOR_TILE_SHIFT 13

/* TownObjectActor_UpdateExit counts up to this step, then lets the player out. */
#define TOWN_OBJECT_ACTOR_EXIT_READY 3

/* The talk point is the stand point moved back by 4.0 along z. */
#define TOWN_OBJECT_ACTOR_TALK_BACK 0x4000

/* The animations start at normal speed. */
#define TOWN_OBJECT_ACTOR_LIFE_ANIM_SPEED 0x1000
/* The class's vtables. */
extern const u8 data_ov009_022658dc[];
extern const u8 data_ov009_022659a0[];
/* The town objects' records, one per code from 0x5000. */
extern const TownObjectActorRecord data_020d1f24[];
/* The scene's heap the animations are loaded on. */
extern Heap *data_021c9b1c;
/* Main's music object; the queue at 0x2d0 (music_queue.h). */
extern u8 *data_021c526c;
/* The node hook and its callback, as the game is handed them: the game's functions. */
extern void func_ov009_022655c4(void *state);
extern void func_ov009_022655d4(void *state);
/* Overlay 3's field actor: this console's player asked for state 0x3b. */
int FieldActor_PlayerRequestState3b(void);

/* The address of the function in vtable slot `offset`. */
static uintptr_t life_slot(const TownObjectActor *actor, u32 offset)
{
    return *(const u32 *) ((const u8 *) actor->vtable + offset);
}

static int life_call_int(TownObjectActor *actor, u32 offset)
{
    return ((int (*)(TownObjectActor *)) life_slot(actor, offset))(actor);
}

static void life_call_void(TownObjectActor *actor, u32 offset)
{
    ((void (*)(TownObjectActor *)) life_slot(actor, offset))(actor);
}

static int life_set_mode(TownObjectActor *actor, int mode)
{
    return ((int (*)(TownObjectActor *, int)) life_slot(actor, TOWN_OBJECT_ACTOR_LIFE_SLOT_SET_MODE))(actor, mode);
}

static SceneObjectBase *life_object(TownObjectActor *actor)
{
    return (SceneObjectBase *) (void *) actor;
}

static AnimatedModel *life_model(TownObjectActor *actor)
{
    return (AnimatedModel *) (void *) actor->model_object;
}

static BuildingLights *life_lights(TownObjectActor *actor)
{
    return (BuildingLights *) (void *) actor->lights;
}

/* The object's record: the code's, or the first for a code out of range. */
static const TownObjectActorRecord *life_record(const TownObjectActor *actor)
{
    u32 code = actor->code;
    if (code >= 0x5000 && code <= 0x5021) {
        return &data_020d1f24[code - 0x5000];
    }
    return &data_020d1f24[0];
}

/* Whether `*code` is `value`, through ItemCode_FurnitureNumber when the code is furniture. */
static int life_code_is(u16 *code, u16 value)
{
    if (ItemCode_IsFurniture(code)) {
        u16 other = value;
        int converted = ItemCode_FurnitureNumber(code);
        return converted == ItemCode_FurnitureNumber(&other);
    }
    return *code == value;
}

/* The address of its code, asked of TownObjectActor_CodeAddress. */
static u16 *life_code(TownObjectActor *actor)
{
    return (u16 *) (uintptr_t) TownObjectActor_CodeAddress(actor);
}

/* func_ov009_02264c40: whether it is night (before 6:00 or from 18:00). */
int TownObjectActor_IsNight(TownObjectActor *actor)
{
    (void) actor;
    Time now;
    Calendar_Now(&now);
    return !(now.hour >= TOWN_OBJECT_ACTOR_DAY_START && now.hour < TOWN_OBJECT_ACTOR_DAY_END);
}
CLEAN_AS(func_ov009_02264c40, TownObjectActor_IsNight)

/* func_ov009_02264c64 (vtable slot 0x8c): whether it is open (lit at night, and going in asks
 * for the visit record); always 1 here. Overrides: VillagerHouse_IsOpen, PlayerHouse_IsOpen,
 * SignBoard_IsOpen, StoreFront_LetsIn, Fox_IsAfterSix, Panther_IsAfterSix. */
int TownObjectActor_IsOpen(TownObjectActor *actor)
{
    (void) actor;
    return 1;
}
CLEAN_AS(func_ov009_02264c64, TownObjectActor_IsOpen)

/* func_ov009_02264c68 (vtable slot 0x9c): whether its lights are on: at night, when vtable
 * slot 0x8c says so. */
int TownObjectActor_LightsOn(TownObjectActor *actor)
{
    return TownObjectActor_IsNight(actor) && life_call_int(actor, TOWN_OBJECT_ACTOR_LIFE_SLOT_IS_OPEN) != 0;
}
CLEAN_AS(func_ov009_02264c68, TownObjectActor_LightsOn)

/* func_ov009_02264c90: its kind, byte 2 of its record (0 to 3). */
int TownObjectActor_Kind(TownObjectActor *actor)
{
    TownObjectActorRecord record;
    TownObjects_CopyRecord(&record, life_record(actor));
    int kind = TownObjects_RecordByte2(&record);
    TownObjects_DestroyRecord(&record);
    return kind;
}
CLEAN_AS(func_ov009_02264c90, TownObjectActor_Kind)

/* func_ov009_02264d60: how far ahead of the camera along z it stays in view: byte 7 of its
 * record, in tiles. */
int TownObjectActor_ViewRangeZAhead(const TownObjectActor *actor)
{
    TownObjectActorRecord record;
    TownObjects_CopyRecord(&record, life_record(actor));
    int range = (int) ((u32) TownObjects_RecordLength7(&record) << TOWN_OBJECT_ACTOR_TILE_SHIFT);
    TownObjects_DestroyRecord(&record);
    return range;
}
CLEAN_AS(func_ov009_02264d60, TownObjectActor_ViewRangeZAhead)

/* func_ov009_02264dc8: how far behind the camera along z it stays in view: byte 8 of its
 * record, in tiles. */
int TownObjectActor_ViewRangeZBehind(TownObjectActor *actor)
{
    TownObjectActorRecord record;
    TownObjects_CopyRecord(&record, life_record(actor));
    int range = (int) ((u32) TownObjects_RecordLength8(&record) << TOWN_OBJECT_ACTOR_TILE_SHIFT);
    TownObjects_DestroyRecord(&record);
    return range;
}
CLEAN_AS(func_ov009_02264dc8, TownObjectActor_ViewRangeZBehind)

/* func_ov009_02264e30: how far from the camera along x it stays in view: byte 6 of its record,
 * in tiles. */
int TownObjectActor_ViewRangeX(TownObjectActor *actor)
{
    TownObjectActorRecord record;
    TownObjects_CopyRecord(&record, life_record(actor));
    int range = (int) ((u32) TownObjects_RecordLength6(&record) << TOWN_OBJECT_ACTOR_TILE_SHIFT);
    TownObjects_DestroyRecord(&record);
    return range;
}
CLEAN_AS(func_ov009_02264e30, TownObjectActor_ViewRangeX)

/* func_ov009_022646b8: the matrix its model is drawn with, kept at 0x1a0 and copied to `out`
 * (unless NULL). It is vtable slot 0xb8's when that slot fills one (says nonzero); else its
 * position bent onto the drawn world, turned about x as the bend asks (TownObjectActor_PivotMatrix). */
void TownObjectActor_UpdateModelMatrix(TownObjectActor *actor, Mtx43 *out)
{
    Mtx43 matrix;
    if (((int (*)(TownObjectActor *, Mtx43 *)) life_slot(actor, TOWN_OBJECT_ACTOR_LIFE_SLOT_OWN_MATRIX))(actor, &matrix) ==
        0) {
        actor->pitch = (s16) Globe_BendFar(&actor->pivot, &actor->position);
        TownObjectActor_PivotMatrix(actor, &matrix);
    }
    actor->model_matrix = matrix;
    if (out != NULL) {
        *out = matrix;
    }
}
CLEAN_AS(func_ov009_022646b8, TownObjectActor_UpdateModelMatrix)

/* func_ov009_022648a4: a translation to its pivot, turned about x by its pitch. */
void TownObjectActor_PivotMatrix(TownObjectActor *actor, Mtx43 *out)
{
    Mtx43 matrix;
    Mtx43_Translation(&matrix, actor->pivot.x, actor->pivot.y, actor->pivot.z);
    Mtx43_RotateX(&matrix, actor->pitch);
    *out = matrix;
}
CLEAN_AS(func_ov009_022648a4, TownObjectActor_PivotMatrix)

/* func_ov009_02264718: once scene event 6 has started the count (exit_step 1), it counts up to
 * 3; from then on, each frame this console's player has nothing of priority 6 or more queued,
 * the player is asked to come out of it (state 0x3b of overlay 3's field actor), with overlay
 * 3's pose flag and the music's delay set by its kind: kind 2 flag 1 and delay 1, kind 3 flag 0
 * and delay 2, kind 1 flag 0 and delay 3 (4 for the buildings 0x5012 and 0x5013). Once the
 * player agrees, or at once for kind 0, the count ends. */
void TownObjectActor_UpdateExit(TownObjectActor *actor)
{
    if (actor->exit_step < 1) {
        return;
    }
    if (actor->exit_step == TOWN_OBJECT_ACTOR_EXIT_READY && PlayerActorOps_QueueBelow6() != 0) {
        Music2d0 *music = (Music2d0 *) (void *) (data_021c526c + 0x2d0);
        switch (TownObjectActor_Kind(actor)) {
            case 2:
                ObjectActors_SetPoseFlag(1);
                Music2d0_SetDelay(music, 1);
                break;
            case 3:
                ObjectActors_SetPoseFlag(0);
                Music2d0_SetDelay(music, 2);
                break;
            case 1:
                ObjectActors_SetPoseFlag(0);
                if (life_code_is(&actor->code, TOWN_OBJECT_ACTOR_CODE_EXIT_A) ||
                    life_code_is(&actor->code, TOWN_OBJECT_ACTOR_CODE_EXIT_B)) {
                    Music2d0_SetDelay(music, 4);
                } else {
                    Music2d0_SetDelay(music, 3);
                }
                break;
            default:
                actor->exit_step = 0;
                return;
        }
        if (FieldActor_PlayerRequestState3b() != 0) {
            actor->exit_step = 0;
            return;
        }
    }
    if (actor->exit_step < TOWN_OBJECT_ACTOR_EXIT_READY) {
        actor->exit_step++;
    }
}
CLEAN_AS(func_ov009_02264718, TownObjectActor_UpdateExit)

/* func_ov009_02264e98: when it has either animation, the animations' memory taken from the
 * scene's heap and the first one started, looping, and attached. An actor of a nonzero kind
 * then enters mode 0, or for the building 0x501d the mode main has recorded for it. */
void TownObjectActor_StartModel(TownObjectActor *actor)
{
    if (life_call_int(actor, TOWN_OBJECT_ACTOR_LIFE_SLOT_ANIM_0) != 0 ||
        life_call_int(actor, TOWN_OBJECT_ACTOR_LIFE_SLOT_ANIM_1) != 0) {
        AnimatedModel_LoadAnim(life_model(actor), data_021c9b1c);
        const u8 *file = (const u8 *) (uintptr_t) life_call_int(actor, TOWN_OBJECT_ACTOR_LIFE_SLOT_ANIM_0);
        AnimatedModel_Start(life_model(actor), file, 0, TOWN_OBJECT_ACTOR_LIFE_ANIM_SPEED, 0, 0);
        AnimatedModel_Attach(life_model(actor));
    }
    if (TownObjectActor_Kind(actor) == 0) {
        return;
    }
    if (life_code_is(life_code(actor), TOWN_OBJECT_ACTOR_CODE_RECORDED_MODE)) {
        life_set_mode(actor, TownObjects_RecordedMode(actor->code));
    } else {
        life_set_mode(actor, 0);
    }
}
CLEAN_AS(func_ov009_02264e98, TownObjectActor_StartModel)

/* func_ov009_02264f68: its box for the camera, from its building's shape: the shape's centre
 * added to its position in x and z, and the shape's width and depth. Left alone without the
 * building's files. */
void TownObjectActor_SetBounds(TownObjectActor *actor)
{
    TownObjectActorFiles *files = TownObjectActorFiles_Of(actor);
    if (files == NULL) {
        return;
    }
    actor->bounds_centre.x = actor->position.x + files->centre_x;
    actor->bounds_centre.y = actor->position.y;
    actor->bounds_centre.z = actor->position.z + files->centre_z;
    actor->bounds_width = files->width;
    actor->bounds_depth = files->depth;
}
CLEAN_AS(func_ov009_02264f68, TownObjectActor_SetBounds)

/* func_ov009_02264fb8 (vtable slot 0x10, whether it can be deleted): when the base class
 * agrees, its sound off, its shadows and areas taken down, its model's render released and it
 * leaves overlay 3's list; when the player went in (TOWN_OBJECT_ACTOR_FLAG_GONE), main's claim on an
 * object is released and, for a shop, the shops' pending state set to 1. */
int TownObjectActor_CanDelete(TownObjectActor *actor)
{
    if (SceneObjectBase_CanDelete(life_object(actor)) == 0) {
        return 0;
    }
    TownObjectActorSound_TurnOff(&actor->sound);
    TownObjectActor_ReleaseShadows(actor);
    TownObjectActor_ReleaseAreas(actor);
    ModelObject_ReleaseRender(&life_model(actor)->object);
    ObjectActors_Remove(actor);
    if (actor->flags & TOWN_OBJECT_ACTOR_FLAG_GONE) {
        ObjectClaim_Release();
        if (MapCode_IsStore(&actor->code)) {
            Shops_SetPendingState(1);
        }
    }
    return 1;
}
CLEAN_AS(func_ov009_02264fb8, TownObjectActor_CanDelete)

/* func_ov009_02265024 (vtable slot 0x28, asked before drawing): when the actors' check agrees
 * and it is in the camera's box, its model is drawn (when vtable slot 0xb0 says so) unless the
 * camera's goal is past it along z (the building 0x500b is drawn anyway); whether it was in
 * view that way. */
int TownObjectActor_CanDraw(TownObjectActor *actor)
{
    if (Actor_CanDraw((Actor *) (void *) actor) == 0) {
        return 0;
    }
    if (actor->flags_235 & TOWN_OBJECT_ACTOR_FLAG_OUT_OF_VIEW) {
        return 0;
    }
    if (life_code_is(life_code(actor), TOWN_OBJECT_ACTOR_CODE_ALWAYS_DRAWN) ||
        CameraControl_IsPastGoalZ(&actor->bounds_centre, actor->bounds_width, actor->bounds_depth) == 0) {
        if (life_call_int(actor, TOWN_OBJECT_ACTOR_LIFE_SLOT_DRAWS) != 0) {
            TownObjectActor_DrawModel(actor);
        }
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov009_02265024, TownObjectActor_CanDraw)

/* func_ov009_022650d0 (vtable slot 0x20, told how its run went): its sound follows its
 * position (vtable slot 0xb4); TOWN_OBJECT_ACTOR_FLAG_TALKABLE becomes what TOWN_OBJECT_ACTOR_FLAG_AT_DOOR
 * was this frame, which is cleared with TOWN_OBJECT_ACTOR_FLAG_RUN_IN for the next; then the
 * actors' own. */
void TownObjectActor_AfterRun(TownObjectActor *actor, int status)
{
    Vec3 position;
    ((void (*)(Vec3 *, TownObjectActor *)) life_slot(actor, TOWN_OBJECT_ACTOR_LIFE_SLOT_POSITION))(&position, actor);
    /* The ROM hands the code to the emitter as a third argument, which it does not take. */
    (void) life_code(actor);
    TownObjectActorSound_UpdateAt(&actor->sound, &position);
    if (actor->flags_235 & TOWN_OBJECT_ACTOR_FLAG_AT_DOOR) {
        actor->flags_235 |= TOWN_OBJECT_ACTOR_FLAG_TALKABLE;
    } else {
        actor->flags_235 &= ~TOWN_OBJECT_ACTOR_FLAG_TALKABLE;
    }
    actor->flags_235 &= ~TOWN_OBJECT_ACTOR_FLAG_AT_DOOR;
    actor->flags_235 &= ~TOWN_OBJECT_ACTOR_FLAG_RUN_IN;
    Actor_Run((Actor *) (void *) actor, status);
}
CLEAN_AS(func_ov009_022650d0, TownObjectActor_AfterRun)

/* _ZN18Obj_ov009_022658dc19func_ov009_02265144Ev (vtable slot 0x1c, asked before it runs):
 * when the base class agrees, the frame's work (town_object_actor_life.h); always 1 then. */
int TownObjectActor_CanRun(TownObjectActor *actor)
{
    if (SceneObjectBase_CanRun(life_object(actor)) == 0) {
        return 0;
    }
    TownObjectActorSound_TurnOn(&actor->sound);
    if (life_code_is(life_code(actor), TOWN_OBJECT_ACTOR_CODE_RECORDED_MODE)) {
        int mode = TownObjects_RecordedMode(actor->code);
        if (actor->mode != mode) {
            life_set_mode(actor, mode);
        }
    }
    TownObjectActor_UpdateOutOfView(actor);
    if (SceneQuery_Current() != TOWN_OBJECT_ACTOR_SCENE_STILL) {
        TownObjectActor_UpdateState(actor);
    }
    life_call_void(actor, TOWN_OBJECT_ACTOR_LIFE_SLOT_RUN_MODE);
    if (SceneQuery_Current() != TOWN_OBJECT_ACTOR_SCENE_STILL) {
        TownObjectActor_AddPickFaces(actor);
    }
    int on = life_call_int(actor, TOWN_OBJECT_ACTOR_LIFE_SLOT_LIGHTS_ON);
    int flash = life_call_int(actor, TOWN_OBJECT_ACTOR_LIFE_SLOT_FLASH);
    BuildingLights_Switch(life_lights(actor), on, 1, flash);
    BuildingLights_Update(life_lights(actor), (BuildingLightsModel *) actor->model);
    TownObjectActor_UpdateExit(actor);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_02265144Ev, TownObjectActor_CanRun)

/* _ZN18Obj_ov009_022658dc19func_ov009_0226523cEv (vtable slot 0x00): the set-up
 * (town_object_actor_life.h); vtable slot 0x70's answer, after the entry machine is made idle. */
int TownObjectActor_Init(TownObjectActor *actor)
{
    ObjectActors_Add(actor);
    actor->tile_x = actor->position.x >> TOWN_OBJECT_ACTOR_TILE_SHIFT;
    actor->tile_z = actor->position.z >> TOWN_OBJECT_ACTOR_TILE_SHIFT;
    SceneObjectBase_SetId(life_object(actor), (u16) (((actor->tile_z & 0xff) << 8) | (actor->tile_x & 0xff)));
    actor->code = (u16) life_object(actor)->process.param;
    actor->index = actor->code & 0xfff;

    const char *archive = (const char *) (uintptr_t) life_call_int(actor, TOWN_OBJECT_ACTOR_LIFE_SLOT_ARCHIVE);
    const char *texture = (const char *) (uintptr_t) life_call_int(actor, TOWN_OBJECT_ACTOR_LIFE_SLOT_TEXTURE);
    const char *lit = (const char *) (uintptr_t) life_call_int(actor, TOWN_OBJECT_ACTOR_LIFE_SLOT_LIT);
    TownObjectActor_LoadModel(actor, archive, texture, lit);
    TownObjectActor_SetBounds(actor);
    TownObjectActor_StartModel(actor);

    Mtx43 matrix;
    TownObjectActor_UpdateModelMatrix(actor, &matrix);
    ModelObject_SetInitHook(&life_model(actor)->object, (void *) (uintptr_t) func_ov009_022655c4, actor);
    TownObjectActor_InitShadows(actor, &matrix);

    Vec3 bent;
    int pitch = Globe_Bend(&bent, &actor->position);
    Mtx43 placed;
    Mtx43_Translation(&placed, bent.x, bent.y, bent.z);
    Mtx43_RotateX(&placed, pitch);
    TownObjectActor_BuildAreas(actor, &placed);

    TownObjectActorFiles *files = TownObjectActorFiles_Of(actor);
    BuildingLights_Bind(life_lights(actor), files != NULL ? (BuildingLightsModel *) files->model : NULL, 1);
    SceneObjectBase_SetReach(life_object(actor), 0);
    if (TownObjectActor_GetStandPoint(actor, &actor->talk_point, NULL)) {
        actor->talk_point.z -= TOWN_OBJECT_ACTOR_TALK_BACK;
    }
    int result = life_call_int(actor, TOWN_OBJECT_ACTOR_LIFE_SLOT_INIT_END);
    TownObjectActor_SetState(actor, TOWN_OBJECT_ACTOR_IDLE);
    return result;
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_0226523cEv, TownObjectActor_Init)

/* func_ov009_02265398 (vtable slot 0x70): always 1. */
int TownObjectActor_Slot70(TownObjectActor *actor)
{
    (void) actor;
    return 1;
}
CLEAN_AS(func_ov009_02265398, TownObjectActor_Slot70)

/* The destructor's work: the vtables set back, then the parts taken down in the reverse order
 * of their construction, the base class last. */
static void life_destruct(TownObjectActor *actor)
{
    actor->vtable = data_ov009_022658dc;
    actor->receiver_vtable = data_ov009_022659a0;
    ModelPoolSlot_Destruct(&actor->model_slot);
    TownObjectActorSound_Destroy(&actor->sound);
    BuildingLights_Destruct(life_lights(actor));
    AnimatedModel_DestructComplete(life_model(actor));
    TalkReceiver_Destruct((TalkReceiver *) (void *) &actor->receiver_vtable);
    SceneObjectBase_DestructBase(life_object(actor));
}

/* func_ov009_0226539c: the destructor the derived classes' call. */
void *TownObjectActor_Destruct(TownObjectActor *actor)
{
    life_destruct(actor);
    return actor;
}
CLEAN_AS(func_ov009_0226539c, TownObjectActor_Destruct)

/* func_ov009_022653fc (vtable slot 0x44): the deleting destructor; the memory goes back to the
 * auxiliary heap. */
TownObjectActor *TownObjectActor_Delete(TownObjectActor *actor)
{
    life_destruct(actor);
    Heap_FreeAux(actor);
    return actor;
}
CLEAN_AS(func_ov009_022653fc, TownObjectActor_Delete)

/* func_ov009_02265460 (vtable slot 0x40): the complete destructor. */
void *TownObjectActor_DestructComplete(TownObjectActor *actor)
{
    life_destruct(actor);
    return actor;
}
CLEAN_AS(func_ov009_02265460, TownObjectActor_DestructComplete)

/* The constructor's work: the base class, the receiver part, the vtables, no code yet, then
 * the model, its lights, the sound and the model pool slot. */
static void life_construct(TownObjectActor *actor)
{
    SceneObjectBase_Construct(life_object(actor));
    TalkReceiver_ConstructBase((TalkReceiver *) (void *) &actor->receiver_vtable);
    actor->vtable = data_ov009_022658dc;
    actor->receiver_vtable = data_ov009_022659a0;
    actor->code = TOWN_OBJECT_ACTOR_NO_CODE;
    AnimatedModel_Construct(life_model(actor));
    BuildingLights_Construct(life_lights(actor));
    TownObjectActorSound_Construct(&actor->sound);
    ModelPoolSlot_Construct(&actor->model_slot);
}

/* func_ov009_022654c0: the constructor (the one TownObjectActor_Create uses). */
void *TownObjectActor_Construct(TownObjectActor *actor)
{
    life_construct(actor);
    return actor;
}
CLEAN_AS(func_ov009_022654c0, TownObjectActor_Construct)

/* func_ov009_0226552c: the constructor the derived classes call. */
void *TownObjectActor_ConstructBase(TownObjectActor *actor)
{
    life_construct(actor);
    return actor;
}
CLEAN_AS(func_ov009_0226552c, TownObjectActor_ConstructBase)

/* func_ov009_022655c4: the model's hook before each draw, given the render state: a callback
 * (func_ov009_022655d4) after each node is placed. */
void TownObjectActor_SetNodeHook(G3dRenderState *state)
{
    state->hooks[G3D_COMMAND_NODE_DESC] = (u32) (uintptr_t) func_ov009_022655d4;
    state->hook_timings[G3D_COMMAND_NODE_DESC] = G3D_TIMING_B;
}
CLEAN_AS(func_ov009_022655c4, TownObjectActor_SetNodeHook)

/* func_ov009_022655d4: after a node is placed, the actor the model object belongs to (its
 * user) is told the node and the state through vtable slot 0x60. */
void TownObjectActor_AfterNode(G3dRenderState *state)
{
    TownObjectActor *actor = state->object->user;
    if (actor != NULL) {
        ((void (*)(TownObjectActor *, int, G3dRenderState *)) life_slot(actor, TOWN_OBJECT_ACTOR_LIFE_SLOT_NODE))(
            actor, state->command[1], state);
    }
}
CLEAN_AS(func_ov009_022655d4, TownObjectActor_AfterNode)

/* func_ov009_022655f4 (vtable slot 0x60, told of each node drawn): nothing. */
void TownObjectActor_Slot60(TownObjectActor *actor)
{
    (void) actor;
}
CLEAN_AS(func_ov009_022655f4, TownObjectActor_Slot60)

/* func_ov009_02265680: the profile's maker: an actor of this class on the auxiliary heap,
 * zeroed, then constructed. */
void TownObjectActor_Create(void)
{
    TownObjectActor *actor = Heap_AllocAuxZeroed(TOWN_OBJECT_ACTOR_SIZE);
    if (actor != NULL) {
        TownObjectActor_Construct(actor);
    }
}
CLEAN_AS(func_ov009_02265680, TownObjectActor_Create)

/* _ZThn236_N18Obj_ov009_022658dcD0Ev (func_ov009_022656bc, receiver slot 0x04): the deleting
 * destructor reached through the receiver part's vtable, with the part's address. */
TownObjectActor *TownObjectActor_ReceiverDelete(void *receiver)
{
    return TownObjectActor_Delete((TownObjectActor *) ((uintptr_t) receiver - TOWN_OBJECT_ACTOR_RECEIVER));
}
CLEAN_AS(_ZThn236_N18Obj_ov009_022658dcD0Ev, TownObjectActor_ReceiverDelete)

/* _ZThn236_N18Obj_ov009_022658dcD1Ev (func_ov009_022656d8, receiver slot 0x00): the complete
 * destructor reached the same way. */
void *TownObjectActor_ReceiverDestructComplete(void *receiver)
{
    return TownObjectActor_DestructComplete((TownObjectActor *) ((uintptr_t) receiver - TOWN_OBJECT_ACTOR_RECEIVER));
}
CLEAN_AS(_ZThn236_N18Obj_ov009_022658dcD1Ev, TownObjectActor_ReceiverDestructComplete)
