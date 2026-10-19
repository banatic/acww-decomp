/* The mole of overlay 77 (mole.h): his object's vtable slots and his states. */
#include "mole.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/process.h"
#include "autoload_2/sound_emitter_class.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "main/acre_map.h"
#include "main/acre_tile.h"
#include "main/act_effects.h"
#include "main/actor_table.h"
#include "main/block_021d27ac.h"
#include "main/block_021d27ac_parts.h"
#include "main/effect_system.h"
#include "main/event_queue.h"
#include "main/field_body.h"
#include "main/field_collision.h"
#include "main/footsteps.h"
#include "main/layered_model.h"
#include "main/music_queue.h"
#include "main/pool_link.h"
#include "main/scene_action.h"
#include "main/scene_face.h"
#include "main/scene_look.h"
#include "main/scene_motion_request.h"
#include "main/scene_mover.h"
#include "main/scene_object.h"
#include "main/scene_object_base.h"
#include "main/scene_probe.h"
#include "main/scene_standard_anims.h"
#include "main/scene_talk_state.h"
#include "main/scene_value_3aa.h"
#include "main/session_players.h"
#include "main/sound_emitter.h"
#include "main/special_scene_object.h"
#include "main/speaker_anim.h"
#include "mole_talk.h"

static_assert(offsetof(Mole, state) == 0x654 && offsetof(Mole, talk) == 0x658, "Mole");
static_assert(offsetof(Mole, phrase) == 0x718 && offsetof(Mole, building_x) == 0x71c, "Mole");
static_assert(offsetof(Mole, building_z) == 0x720 && offsetof(Mole, effect) == 0x724, "Mole");
static_assert(sizeof(Mole) == 0x728, "the size Mole_Create allocates");
static_assert(sizeof(MoleStep) == 0x10, "a state's functions");

/* The parts of the special character's scene object used here, by place (main's
 * scene_object.h and speaker_anim.h). */
#define MOLE_POSITION 0x5c        /* Vec3: where he is */
#define MOLE_ANGLE 0x8e           /* s16: where he faces */
#define MOLE_WALK_ANGLE 0x94      /* s16: where he walks */
#define MOLE_PERSON 0xea          /* u16: his person code */
#define MOLE_MODEL 0xec           /* LayeredModel */
#define MOLE_MODEL_FRAME 0x190    /* fx32: his model's animation frame, 20.12 */
#define MOLE_MODEL_SPEED 0x198    /* fx32: its speed (1.0: on, 0: held) */
#define MOLE_STANDARD_ANIMS 0x2a0 /* SceneStandardAnims */
#define MOLE_FACE 0x2ac           /* SceneFace */
#define MOLE_ANIM 0x334           /* SpeakerAnim */
#define MOLE_MOVER 0x350          /* SceneMover */
#define MOLE_PROBE 0x3a8          /* the probe */
#define MOLE_VALUE_3AA 0x3aa      /* SceneValue3aa */
#define MOLE_LOOK 0x3b0           /* SceneLook */
#define MOLE_TALK_STATE 0x418     /* SceneTalkState */
#define MOLE_EFFECTS 0x420        /* ActEffects */
#define MOLE_COLLIDER 0x49c       /* CollisionContacts */
#define MOLE_CARRIER 0x4cc        /* FieldOwnedBody */
#define MOLE_HELD_FLAGS 0x4e8     /* u32: the scene object's flags (2: held) */
#define MOLE_SOLID 0x510          /* u8: it collides and moves with its carrier */
#define MOLE_SHADOW 0x511         /* u8: its shadow is drawn */
#define MOLE_EMITTER 0x514        /* SoundEmitterObject */
#define MOLE_FOOTSTEPS 0x558      /* Footsteps */
#define MOLE_MOTION 0x564         /* SceneMotion */
#define MOLE_ACTION 0x618         /* SceneAction */
#define MOLE_HEAP 0x640           /* PoolLink */

#define MOLE_NO_PERSON 0xfff1
#define MOLE_HELD 2
#define MOLE_NO_EFFECT (-1)

/* The field actor of this console's player. */
#define MOLE_PLAYER_ACTOR 4

/* The codes of his vtable slot 0x4c he answers: event 1 (he comes up), the act ended. */
#define MOLE_EVENT_1 1
#define MOLE_EVENT_ENDED 8

/* The vtable slot of his talk scene that resets it. */
#define MOLE_TALK_SLOT_RESET 2

/* His animations: coming up (0xfd) and going down (0xfe), played once (mode 1) at priority 1;
 * his standard animations (both 0xfc). */
#define MOLE_ANIM_RISE 0xfd
#define MOLE_ANIM_SINK 0xfe
#define MOLE_ANIM_STANDARD 0xfc
#define MOLE_ANIM_PRIORITY 1
#define MOLE_ANIM_ONCE 1

/* His effect (kind 0x30), started and ended at the whole frames 2 and 12 of his animations. */
#define MOLE_EFFECT_KIND 0x30
#define MOLE_FRAME_EFFECT_START 2
#define MOLE_FRAME_EFFECT_END 12

/* His sounds and their volume; the music queue's value when he comes up. */
#define MOLE_SOUND_RISE 0x7e6
#define MOLE_SOUND_SINK 0x7e7
#define MOLE_SOUND_VOLUME 0x7f
#define MOLE_MUSIC_PRIORITY 0x17
#define MOLE_MUSIC_VALUE_RISE 0xf

/* His model's animation speed while it runs (1.0). */
#define MOLE_SPEED_ON 0x1000

/* The building he waits by (AcreTile_FindItemAllFlags: codes 0x5014-0x501a in a tile with
 * flag 1). */
#define MOLE_BUILDING_FIRST 0x5014
#define MOLE_BUILDING_LAST 0x501a
#define MOLE_BUILDING_TILE_FLAGS 1

/* The tiles before the building the player comes to, and the tiles beside it he comes up on,
 * from the building's tile (x, z). */
#define MOLE_APPROACH_TILES 5
#define MOLE_LAST_LEFT_APPROACH 2 /* tiles 0-2 put him to the right, 3-4 to the left */
#define MOLE_SIDE_TILES 2

typedef struct MoleTile {
    s32 x;
    s32 z;
} MoleTile;

/* The two tables of tiles: function-local statics of Mole_UpdateWait, constructed the first
 * time it runs (bit 0 of each guard word says they were). */
extern u32 data_ov077_02279964;
extern MoleTile data_ov077_02279978[MOLE_APPROACH_TILES];
extern u32 data_ov077_02279960;
extern MoleTile data_ov077_02279968[MOLE_SIDE_TILES];

/* The vtables of his class and of the classes he derives from. */
extern const u8 data_ov077_0227988c[];
extern const u8 data_020d8c64[];
extern const u8 data_020da088[];
/* His model and texture file names: "npc_sp/model/mol.nsbmd", "npc_sp/model/mol_tex.nsbtx". */
extern const char data_ov077_02279784[];
extern const char data_ov077_022797b4[];
/* The word motion requests carry; whether the scene is in a room (0 outdoors); the map of the
 * scene. */
extern u16 data_020c80f8;
extern u8 data_020e54a8;
extern AcreMap *data_021c80bc;

static u8 *mole_part(Mole *mole, u32 offset)
{
    return mole->base + offset;
}

static SceneMotion *mole_motion(Mole *mole)
{
    return (SceneMotion *) (void *) mole_part(mole, MOLE_MOTION);
}

static SceneAction *mole_action(Mole *mole)
{
    return (SceneAction *) (void *) mole_part(mole, MOLE_ACTION);
}

static SoundEmitter *mole_emitter(Mole *mole)
{
    return (SoundEmitter *) (void *) mole_part(mole, MOLE_EMITTER);
}

static Vec3 *mole_position(Mole *mole)
{
    return (Vec3 *) (void *) mole_part(mole, MOLE_POSITION);
}

static s32 *mole_word(Mole *mole, u32 offset)
{
    return (s32 *) (void *) mole_part(mole, offset);
}

/* The whole frame of his model's animation, cut to 16 bits. */
static u32 mole_whole_frame(Mole *mole)
{
    return (*(const u32 *) (const void *) mole_part(mole, MOLE_MODEL_FRAME) >> 12) & 0xffff;
}

/* He faces, and walks towards, the player's actor. */
static void mole_face_player(Mole *mole)
{
    int player = SessionPlayers_ActorHandle(MOLE_PLAYER_ACTOR);
    s16 yaw = (s16) SceneObject_YawTo(mole->base, (u8 *) (uintptr_t) (u32) player);
    *(s16 *) (void *) mole_part(mole, MOLE_ANGLE) = yaw;
    *(s16 *) (void *) mole_part(mole, MOLE_WALK_ANGLE) = yaw;
}

/* Whether his animation `number` is the one his anim plays and his motion is done. */
static int mole_animation_done(Mole *mole, int number)
{
    return SpeakerAnim_IsBody((SpeakerAnim *) (void *) mole_part(mole, MOLE_ANIM), number,
                              mole_part(mole, MOLE_STANDARD_ANIMS)) != 0 &&
           SceneMotion_IsDone(mole_motion(mole)) != 0;
}

/* His effect ended, when there is one. */
static void mole_end_effect(Mole *mole)
{
    if (mole->effect != MOLE_NO_EFFECT) {
        EffectSystem_EndHandle(mole->effect);
        mole->effect = MOLE_NO_EFFECT;
    }
}

/* ---- His object */

/* func_ov077_02278a00 (vtable slot 0x40): his talk scene's destructor, then the special
 * character's; the object. */
Mole *Mole_Destruct(Mole *mole)
{
    *(const u8 **) (void *) mole->base = data_ov077_0227988c;
    MoleTalk_Destruct(&mole->talk);
    SpecialSceneObject_DestructBody(mole);
    return mole;
}
CLEAN_AS(func_ov077_02278a00, Mole_Destruct)

/* func_ov077_02278a28 (vtable slot 0x44): the same, then the object freed. */
Mole *Mole_DestructDelete(Mole *mole)
{
    *(const u8 **) (void *) mole->base = data_ov077_0227988c;
    MoleTalk_Destruct(&mole->talk);
    SpecialSceneObject_DestructBody(mole);
    Heap_FreeAux(mole);
    return mole;
}
CLEAN_AS(func_ov077_02278a28, Mole_DestructDelete)

/* func_ov077_02278a54 (vtable slot 0x4c, told of an event about him): code 1: his talk reset (its slot 0x08), the talk's partner this console's player's object,
 * and he comes up (MOLE_RISE); code 8, the act ended: MOLE_TALKED. */
void Mole_OnEvent(Mole *mole, int code)
{
    switch (code) {
        case MOLE_EVENT_1: {
            const u32 *vtable = (const u32 *) (const void *) mole->talk.scene.vtable;
            ((void (*)(MoleTalk *))(uintptr_t) vtable[MOLE_TALK_SLOT_RESET])(&mole->talk);
            SceneBase_SetMotionArg(&mole->talk.scene, SceneObject_ActorObject(mole->base, MOLE_PLAYER_ACTOR));
            Mole_SetState(mole, MOLE_RISE);
            break;
        }
        case MOLE_EVENT_ENDED:
            Mole_SetState(mole, MOLE_TALKED);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov077_02278a54, Mole_OnEvent)

/* func_ov077_02278a98 (vtable slot 0x48): the player may always act on him. */
int Mole_MayAct(void)
{
    return 1;
}
CLEAN_AS(func_ov077_02278a98, Mole_MayAct)

/* func_ov077_02279358: state `state` taken when its entry function, if it has one, answers
 * nonzero.
 * REQUIRES: `state` is below 6 (the table is not bounded). */
void Mole_SetState(Mole *mole, int state)
{
    const MoleStep *step = &data_ov077_022799a0[state];
    int taken = 1;
    if (step->enter.function != 0) {
        taken = MemberPointer_CallInt(&step->enter, mole);
    }
    if (taken != 0) {
        mole->state = state;
    }
}
CLEAN_AS(func_ov077_02279358, Mole_SetState)

/* func_ov077_0227939c (vtable slot 0x68, each frame): his state's run when it has one, and its
 * answer; else 0.
 * REQUIRES: his state is below 6. */
int Mole_Update(Mole *mole)
{
    const MoleStep *step = &data_ov077_022799a0[mole->state];
    if (step->run.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&step->run, mole);
}
CLEAN_AS(func_ov077_0227939c, Mole_Update)

/* func_ov077_022793e8 (vtable slot 0x70): his model's file name, "npc_sp/model/mol.nsbmd". */
int Mole_ModelName(void)
{
    return (int) (u32) (uintptr_t) data_ov077_02279784;
}
CLEAN_AS(func_ov077_022793e8, Mole_ModelName)

/* func_ov077_022793f0 (vtable slot 0x6c): his texture's file name,
 * "npc_sp/model/mol_tex.nsbtx". */
int Mole_TextureName(void)
{
    return (int) (u32) (uintptr_t) data_ov077_022797b4;
}
CLEAN_AS(func_ov077_022793f0, Mole_TextureName)

/* func_ov077_022793f8 (vtable slot 0x24): he is drawn (SceneObject_Draw) unless he waits under
 * the ground (MOLE_WAIT). 1. */
int Mole_Draw(Mole *mole)
{
    if (mole->state != MOLE_WAIT) {
        SceneObject_Draw(mole->base);
    }
    return 1;
}
CLEAN_AS(func_ov077_022793f8, Mole_Draw)

/* func_ov077_02279414 (vtable slot 0x0c): unless the special character refuses to leave, flag 8
 * of the event queue cleared. Whether he left. */
int Mole_Leave(Mole *mole)
{
    if (SpecialSceneObject_Leave(mole) == 0) {
        return 0;
    }
    EventQueue_ClearFlag8();
    return 1;
}
CLEAN_AS(func_ov077_02279414, Mole_Leave)

/* func_ov077_02279430 (vtable slot 0x00, his start): unless the special character refuses to
 * start, he is held (flag 2 at 0x4e8), his reach 0, he waits (MOLE_WAIT), his approach cleared
 * and flag 8 of the event queue set. Whether he started. */
int Mole_Start(Mole *mole)
{
    if (SpecialSceneObject_Start(mole) == 0) {
        return 0;
    }
    *(u32 *) (void *) mole_part(mole, MOLE_HELD_FLAGS) |= MOLE_HELD;
    SceneObjectBase_SetReach((SceneObjectBase *) (void *) mole, 0);
    Mole_SetState(mole, MOLE_WAIT);
    SceneObjectBase_ClearApproach((SceneObjectBase *) (void *) mole);
    EventQueue_SetFlag8();
    return 1;
}
CLEAN_AS(func_ov077_02279430, Mole_Start)

/* func_ov077_02279474 (vtable slot 0x04, his set-up): unless the special character refuses, no
 * phrase picked, his talk scene becomes his scene and gets him as its owner, both his standard
 * animations 0xfc, and he has no shadow and is not solid. Whether he was set up. */
int Mole_Init(Mole *mole)
{
    if (SpecialSceneObject_Init(mole) == 0) {
        return 0;
    }
    mole->phrase = MOLE_NO_PHRASE;
    SceneObject_SetScene(mole->base, &mole->talk.scene);
    MoleTalk_Begin(&mole->talk, mole);
    SceneStandardAnims *anims = (SceneStandardAnims *) (void *) mole_part(mole, MOLE_STANDARD_ANIMS);
    SceneStandardAnims_SetFirst(anims, MOLE_ANIM_STANDARD);
    SceneStandardAnims_SetSecond(anims, MOLE_ANIM_STANDARD);
    *mole_part(mole, MOLE_SHADOW) = 0;
    *mole_part(mole, MOLE_SOLID) = 0;
    return 1;
}
CLEAN_AS(func_ov077_02279474, Mole_Init)

/* func_ov077_022794d8 (the create function his record at 0x0227979c names): a zeroed block of
 * 0x728 bytes from the auxiliary heap, constructed: the scene object base, the class
 * 0x020d8c64's vtable and members in place order (no person yet, 0xfff1), the class
 * 0x020da088's vtable and heap link, then the class's vtable, his talk scene and the building's
 * tile 0, 0. Null when there is no room. */
Mole *Mole_Create(void)
{
    Mole *mole = (Mole *) Heap_AllocAuxZeroed(sizeof(Mole));
    if (mole == NULL) {
        return NULL;
    }
    u8 *object = mole->base;
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) mole_part(mole, MOLE_PERSON) = MOLE_NO_PERSON;
    LayeredModel_ConstructB((LayeredModel *) (void *) mole_part(mole, MOLE_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) mole_part(mole, MOLE_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) mole_part(mole, MOLE_FACE));
    SpeakerAnim_Construct((SpeakerAnim *) (void *) mole_part(mole, MOLE_ANIM));
    SceneMover_Construct((SceneMover *) (void *) mole_part(mole, MOLE_MOVER));
    SceneProbe_Construct(mole_part(mole, MOLE_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) mole_part(mole, MOLE_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) mole_part(mole, MOLE_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) mole_part(mole, MOLE_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) mole_part(mole, MOLE_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) mole_part(mole, MOLE_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) mole_part(mole, MOLE_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) mole_part(mole, MOLE_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) mole_part(mole, MOLE_FOOTSTEPS));
    SceneMotion_Construct(mole_motion(mole));
    SceneAction_Construct(mole_action(mole));
    *(const u8 **) (void *) object = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) mole_part(mole, MOLE_HEAP));
    *(const u8 **) (void *) object = data_ov077_0227988c;
    MoleTalk_Construct(&mole->talk);
    mole->building_x = 0;
    mole->building_z = 0;
    return mole;
}
CLEAN_AS(func_ov077_022794d8, Mole_Create)

/* ---- His states */

/* func_ov077_02278eb4 (MOLE_SINK's run): he faces the player; at the whole frame 2 of his
 * animation the effect starts at him, at frame 12 it ends; once animation 0xfe is done his
 * event is finished, part 0x30 of the object at data_021d27ac cleared, he is deleted and the
 * effect ended. 1. */
int Mole_UpdateSink(Mole *mole)
{
    mole_face_player(mole);
    u32 frame = mole_whole_frame(mole);
    if (frame == MOLE_FRAME_EFFECT_START) {
        mole->effect = EffectSystem_StartKind(MOLE_EFFECT_KIND, mole_position(mole), NULL, NULL);
    }
    if (frame == MOLE_FRAME_EFFECT_END) {
        mole_end_effect(mole);
    }
    if (mole_animation_done(mole, MOLE_ANIM_SINK)) {
        EventQueue_FinishObjectEvent(mole);
        Block021d27acPart30_Set(Block021d27ac_Part30(Block021d27ac_Get()), 0);
        Process_RequestDelete((Process *) (void *) mole);
        mole_end_effect(mole);
    }
    return 1;
}
CLEAN_AS(func_ov077_02278eb4, Mole_UpdateSink)

/* func_ov077_02278f84 (MOLE_SINK's entry): animation 0xfe asked for, once, and sound 0x7e7.
 * 1. */
int Mole_EnterSink(Mole *mole)
{
    SceneMotion_RequestAnimation(mole_motion(mole), MOLE_ANIM_PRIORITY, MOLE_ANIM_SINK, MOLE_ANIM_ONCE, data_020c80f8, 0);
    SoundEmitter_Play(mole_emitter(mole), MOLE_SOUND_SINK, MOLE_SOUND_VOLUME, 0);
    return 1;
}
CLEAN_AS(func_ov077_02278f84, Mole_EnterSink)

/* func_ov077_02278fcc (MOLE_RISE's run): he faces the player; at the whole frame 12 of his
 * animation the effect ends; once animation 0xfd is done the effect is ended and he talks
 * (MOLE_TALK). 1.
 * QUIRK: at frame 12 the effect's handle is ended without a test for none, on each frame the
 * animation stays at that whole frame (EffectSystem_EndHandle is then given -1). */
int Mole_UpdateRise(Mole *mole)
{
    mole_face_player(mole);
    if (mole_whole_frame(mole) == MOLE_FRAME_EFFECT_END) {
        EffectSystem_EndHandle(mole->effect);
        mole->effect = MOLE_NO_EFFECT;
    }
    if (mole_animation_done(mole, MOLE_ANIM_RISE)) {
        mole_end_effect(mole);
        Mole_SetState(mole, MOLE_TALK);
    }
    return 1;
}
CLEAN_AS(func_ov077_02278fcc, Mole_UpdateRise)

/* func_ov077_02279068 (MOLE_RISE's entry): his animation runs (speed 1.0), the effect starts at
 * him with sound 0x7e6, he is solid, and the music queue of priority 0x17 gets the value 0xf.
 * 1. */
int Mole_EnterRise(Mole *mole)
{
    *mole_word(mole, MOLE_MODEL_SPEED) = MOLE_SPEED_ON;
    mole->effect = EffectSystem_StartKind(MOLE_EFFECT_KIND, mole_position(mole), NULL, NULL);
    SoundEmitter_Play(mole_emitter(mole), MOLE_SOUND_RISE, MOLE_SOUND_VOLUME, 0);
    *mole_part(mole, MOLE_SOLID) = 1;
    Music_AddValue(MOLE_MUSIC_PRIORITY, MOLE_MUSIC_VALUE_RISE, 0);
    return 1;
}
CLEAN_AS(func_ov077_02279068, Mole_EnterRise)

/* func_ov077_022790c4 (MOLE_WAIT's run): without the player's actor he is deleted. Else his
 * animation is held at frame 0 and he faces the player; when the player's tile, from the
 * building's, is one of (0, 3), (-1, 3), (-1, 2), (1, 3) and (1, 2), he is put on the centre of
 * the tile (2, 2) from the building's for the first three, (-2, 2) for the others, and asks for
 * an event (kind 7, EventQueue_RequestKind7). 1.
 * The two tables of tiles are constructed in the overlay's .bss the first time (each guarded by
 * bit 0 of its word). */
int Mole_UpdateWait(Mole *mole)
{
    int player = SessionPlayers_ActorHandle(MOLE_PLAYER_ACTOR);
    if (player == 0) {
        Process_RequestDelete((Process *) (void *) mole);
        return 1;
    }
    *mole_word(mole, MOLE_MODEL_SPEED) = 0;
    *mole_word(mole, MOLE_MODEL_FRAME) = 0;

    u8 *actor = (u8 *) (uintptr_t) (u32) player;
    Position position = *(const Position *) (const void *) (actor + ACTOR_POSITION_OFFSET);
    int tile_x = 0;
    int tile_z = 0;
    Position_Tile(&tile_x, &tile_z, &position);
    s32 dx = tile_x - mole->building_x;
    s32 dz = tile_z - mole->building_z;
    s16 yaw = (s16) SceneObject_YawTo(mole->base, actor);
    *(s16 *) (void *) mole_part(mole, MOLE_ANGLE) = yaw;
    *(s16 *) (void *) mole_part(mole, MOLE_WALK_ANGLE) = yaw;

    if ((data_ov077_02279964 & 1) == 0) {
        static const MoleTile approach[MOLE_APPROACH_TILES] = {{0, 3}, {-1, 3}, {-1, 2}, {1, 3}, {1, 2}};
        for (int i = 0; i < MOLE_APPROACH_TILES; i++) {
            data_ov077_02279978[i] = approach[i];
        }
        data_ov077_02279964 |= 1;
    }
    if ((data_ov077_02279960 & 1) == 0) {
        data_ov077_02279968[0] = (MoleTile){-2, 2};
        data_ov077_02279968[1] = (MoleTile){2, 2};
        data_ov077_02279960 |= 1;
    }
    const MoleTile right = data_ov077_02279968[1];
    const MoleTile left = data_ov077_02279968[0];

    for (int i = 0; i < MOLE_APPROACH_TILES; i++) {
        if (data_ov077_02279978[i].x != dx || data_ov077_02279978[i].z != dz) {
            continue;
        }
        const MoleTile *side = i <= MOLE_LAST_LEFT_APPROACH ? &right : &left;
        AcreTile_TileCentre(mole_position(mole), (u32) (side->x + mole->building_x), (u32) (side->z + mole->building_z));
        EventQueue_RequestKind7(mole, 0);
    }
    return 1;
}
CLEAN_AS(func_ov077_022790c4, Mole_UpdateWait)

/* func_ov077_02279234 (MOLE_WAIT's entry): animation 0xfd asked for, once (the word 0); outdoors
 * with a map, the tile of the first building of the codes 0x5014-0x501a (in a tile with flag 1)
 * noted as the building's when there is one. 1. */
int Mole_EnterWait(Mole *mole)
{
    SceneMotion_RequestAnimation(mole_motion(mole), MOLE_ANIM_PRIORITY, MOLE_ANIM_RISE, MOLE_ANIM_ONCE, 0, 0);
    if (data_020e54a8 != 0) {
        return 1;
    }
    AcreMap *map = data_021c80bc;
    int acre_x = 0, acre_z = 0, x = 0, z = 0;
    if (map != NULL) {
        u16 first = MOLE_BUILDING_FIRST;
        u16 last = MOLE_BUILDING_LAST;
        if (AcreTile_FindItemAllFlags(map, &acre_x, &acre_z, &x, &z, &first, &last, MOLE_BUILDING_TILE_FLAGS, 0) != 0) {
            AcreTile_TileOfAcre(&mole->building_x, &mole->building_z, acre_x, acre_z, x, z);
        }
    }
    return 1;
}
CLEAN_AS(func_ov077_02279234, Mole_EnterWait)

/* func_ov077_022792dc (MOLE_TALKED's run): nothing. 1. */
int Mole_UpdateTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov077_022792dc, Mole_UpdateTalked)

/* func_ov077_022792e0 (MOLE_TALKED's entry): nothing. 1. */
int Mole_EnterTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov077_022792e0, Mole_EnterTalked)

/* func_ov077_022792e4 (MOLE_TALK's run): once his action is idle he goes down (MOLE_SINK). 1.
 * QUIRK: whether the action is busy is asked twice. */
int Mole_UpdateTalk(Mole *mole)
{
    if (SceneAction_IsBusy(mole_action(mole)) != 0) {
        return 1;
    }
    if (SceneAction_IsBusy(mole_action(mole)) == 0) {
        Mole_SetState(mole, MOLE_SINK);
    }
    return 1;
}
CLEAN_AS(func_ov077_022792e4, Mole_UpdateTalk)

/* func_ov077_02279318 (MOLE_TALK's entry): he turns to the talk's partner (to angle 0 without
 * one) and talks. 1. */
int Mole_EnterTalk(Mole *mole)
{
    int partner = SceneBase_MotionArg(&mole->talk.scene);
    int angle = 0;
    if (partner != 0) {
        angle = SceneObject_YawTo(mole->base, (u8 *) (uintptr_t) (u32) partner);
    }
    SceneAction_RequestTurnAndTalk(mole_action(mole), 0, angle, 0);
    return 1;
}
CLEAN_AS(func_ov077_02279318, Mole_EnterTalk)

/* func_ov077_02279350 (state 0's run): nothing. 1. */
int Mole_UpdateState0(void)
{
    return 1;
}
CLEAN_AS(func_ov077_02279350, Mole_UpdateState0)

/* func_ov077_02279354 (state 0's entry): nothing. 1. */
int Mole_EnterState0(void)
{
    return 1;
}
CLEAN_AS(func_ov077_02279354, Mole_EnterState0)
