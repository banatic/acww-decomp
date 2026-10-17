/* The faceless cat of overlay 74: her object, her face, her states and her creation
 * (mystery_cat.h). */
#include "mystery_cat.h"

#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/fx_math.h"
#include "autoload_2/heap.h"
#include "autoload_2/sound_emitter_class.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "main/acre_tile.h"
#include "main/act_effects.h"
#include "main/actor.h"
#include "main/camera_control.h"
#include "main/event_queue.h"
#include "main/field_body.h"
#include "main/field_collision.h"
#include "main/footsteps.h"
#include "main/item_texture.h"
#include "main/layered_model.h"
#include "main/main_random.h"
#include "main/pool_link.h"
#include "main/scene_action.h"
#include "main/scene_base.h"
#include "main/scene_face.h"
#include "main/scene_look.h"
#include "main/scene_motion.h"
#include "main/scene_motion_request.h"
#include "main/scene_mover.h"
#include "main/scene_object.h"
#include "main/scene_object_base.h"
#include "main/scene_probe.h"
#include "main/scene_standard_anims.h"
#include "main/scene_talk_state.h"
#include "main/scene_value_3aa.h"
#include "main/special_scene_object.h"
#include "main/speaker_anim.h"
#include "main/town_tile.h"
#include "main/vram_copy_task.h"
#include "main/wfc_stats.h"
#include "mystery_cat_talk.h"

static_assert(sizeof(SceneBase) == 0x80, "scene base");
static_assert(offsetof(MysteryCatTalk, owner) == 0xb0, "owner");
static_assert(offsetof(MysteryCatTalk, after) == 0xb4, "after the command");
static_assert(sizeof(MysteryCatTalk) == 0xbc, "her talk scene");
static_assert(sizeof(MysteryCatFace) == 0x2c, "her face");
static_assert(sizeof(MysteryCatStep) == 0x10, "a state's functions");
static_assert(offsetof(MysteryCat, state) == 0x654, "state");
static_assert(offsetof(MysteryCat, talk) == 0x658, "talk scene");
static_assert(offsetof(MysteryCat, face) == 0x714, "face");
static_assert(sizeof(MysteryCat) == 0x740, "the size MysteryCat_Create allocates");

/* The parts of the special character's scene object used here, by place (main's
 * scene_object.h). */
#define MCAT_POSITION 0x5c        /* Vec3: where she stands */
#define MCAT_YAW 0x8e             /* s16: where she faces */
#define MCAT_WALK_ANGLE 0x94      /* s16: where she walks */
#define MCAT_SPEED 0x98           /* fx32: her speed (scene_mover.h) */
#define MCAT_PERSON 0xea          /* u16: her person code */
#define MCAT_MODEL 0xec           /* LayeredModel */
#define MCAT_STANDARD_ANIMS 0x2a0 /* SceneStandardAnims */
#define MCAT_FACE_PART 0x2ac      /* SceneFace */
#define MCAT_ANIM 0x334           /* SpeakerAnim */
#define MCAT_MOVER 0x350          /* SceneMover */
#define MCAT_PROBE 0x3a8          /* the probe ahead */
#define MCAT_VALUE_3AA 0x3aa      /* SceneValue3aa */
#define MCAT_LOOK 0x3b0           /* SceneLook */
#define MCAT_TALK_STATE 0x418     /* SceneTalkState */
#define MCAT_EFFECTS 0x420        /* ActEffects */
#define MCAT_COLLIDER 0x49c       /* CollisionContacts */
#define MCAT_CARRIER 0x4cc        /* FieldOwnedBody */
#define MCAT_EMITTER 0x514        /* SoundEmitterObject */
#define MCAT_FOOTSTEPS 0x558      /* Footsteps */
#define MCAT_MOTION 0x564         /* SceneMotion */
#define MCAT_ACTION 0x618         /* SceneAction */
#define MCAT_HEAP 0x640           /* PoolLink */
#define MCAT_WALK_FRAMES 0x651    /* u8: the frames her walk or turn may still go on */

#define MCAT_NO_PERSON 0xfff1

/* The field actor of this console's player. */
#define MCAT_PLAYER_ACTOR 4

/* The codes of her vtable slot 0x4c (main's event_kinds.h). */
#define MCAT_EVENT_0 0
#define MCAT_EVENT_TALK 3
#define MCAT_EVENT_ENDED 8

/* The scene's vtable slot her talks call first. */
#define MCAT_TALK_SLOT_08 0x08

/* The motions she asks for (scene_motion_kinds.h): stand, walk, walk in the second way, turn
 * then walk. */
#define MCAT_MOTION_STAND 0
#define MCAT_MOTION_WALK 1
#define MCAT_MOTION_WALK_2 2
#define MCAT_MOTION_TURN_WALK 4

/* What the probe ahead says (scene_probe.h): its first point blocked, its second, both. */
#define MCAT_PROBE_FIRST 1
#define MCAT_PROBE_SECOND 2
#define MCAT_PROBE_BOTH 3

/* The value of the pair at 0x3aa (SceneValue3aa_Grade) at which she stands. */
#define MCAT_GRADE_STAND 2

/* The frames a walk or a turn toward the point picked may go on. */
#define MCAT_WALK_FRAMES_WALK 100
#define MCAT_WALK_FRAMES_TURN 80

/* The tries at a point to walk to, and how far it is (12.0). */
#define MCAT_WALK_TRIES 6
#define MCAT_WALK_DISTANCE 0xc000

/* The camera's view, around the point it looks at: 16.0 to either side on x, from 26.0 before
 * to 10.0 past it on z. */
#define MCAT_VIEW_X 0x10000
#define MCAT_VIEW_Z_NEAR 0x1a000
#define MCAT_VIEW_Z_FAR 0xa000

/* The vtables: the class's and those of the classes it derives from. */
extern const u8 data_ov074_02279c68[];
extern const u8 data_020d8c64[];
extern const u8 data_020da088[];
/* Her states' functions (filled at start-up by __sinit_ov074_022799d8). */
extern MysteryCatStep data_ov074_02279d9c[MYSTERY_CAT_STATES];
/* The points beside the way ahead she steps to when the probe ahead is blocked: (0.5, 0, 1.0)
 * and (-0.5, 0, 1.0), set at start-up. */
extern Vec3 data_ov074_02279d84[2];
/* Her model's file name, "npc_sp/model/mkab.nsbmd". */
extern const char data_ov074_02279ba0[];
/* The name of her model's material her face is copied over: the address of "f". */
extern const char *const data_ov074_02279b44;
/* The town's statistics record, which keeps her face. */
extern WfcStats data_021f3278;
/* The field camera, or NULL, and the point it looks at. */
extern CameraControl *data_021c67a4;
extern Vec3 data_021c67d0;
/* The game's first random generator. */
extern Random data_021cb5a0;
/* Main's vector her look and her walk points start from, and her look's range. */
extern Vec3 data_021fbee8;
extern fx32 data_020c814c;
/* The word her motion requests carry. */
extern u16 data_020c80f8;
/* The speed scale of her animation player. */
extern s32 data_020c8120;
/* The current heap. */
extern Heap *data_021fbe94;
/* NitroSDK's sine and cosine table and fixed-point product. */
extern const fx16 FX_SinCosTable_[];
extern fx32 FX_MulFunc(fx32 a, fx32 b);

static u8 *mcat_part(MysteryCat *cat, u32 offset)
{
    return cat->base + offset;
}

static Vec3 *mcat_position(MysteryCat *cat)
{
    return (Vec3 *) (void *) mcat_part(cat, MCAT_POSITION);
}

static s16 mcat_s16(MysteryCat *cat, u32 offset)
{
    return *(const s16 *) (const void *) mcat_part(cat, offset);
}

static s32 mcat_speed(MysteryCat *cat)
{
    return *(const s32 *) (const void *) mcat_part(cat, MCAT_SPEED);
}

static SceneMotion *mcat_motion(MysteryCat *cat)
{
    return (SceneMotion *) (void *) mcat_part(cat, MCAT_MOTION);
}

static SceneAction *mcat_action(MysteryCat *cat)
{
    return (SceneAction *) (void *) mcat_part(cat, MCAT_ACTION);
}

static SceneMover *mcat_mover(MysteryCat *cat)
{
    return (SceneMover *) (void *) mcat_part(cat, MCAT_MOVER);
}

static Footsteps *mcat_footsteps(MysteryCat *cat)
{
    return (Footsteps *) (void *) mcat_part(cat, MCAT_FOOTSTEPS);
}

/* Her motion of kind `kind` (priority 1) from (x, z) at `angle`. */
static void mcat_move(MysteryCat *cat, int kind, int x, int z, int angle)
{
    SceneMotion_Request(mcat_motion(cat), kind, 1, x, z, 0, (s16) angle, 0, 0, data_020c80f8, 0);
}

/* She stands (motion 0, priority 1). */
static void mcat_stand(MysteryCat *cat)
{
    mcat_move(cat, MCAT_MOTION_STAND, 0, 0, 0);
}

/* Whether her motion is a walk or a turn then walk (kinds 1, 2 and 4), asking its kind once
 * for each until one matches. */
static int mcat_is_walking(MysteryCat *cat)
{
    return SceneMotion_Kind(mcat_motion(cat)) == MCAT_MOTION_WALK ||
           SceneMotion_Kind(mcat_motion(cat)) == MCAT_MOTION_WALK_2 ||
           SceneMotion_Kind(mcat_motion(cat)) == MCAT_MOTION_TURN_WALK;
}

/* Whether the angle from her to `point` is within a quarter turn of where she faces. */
static int mcat_faces(MysteryCat *cat, const Vec3 *point)
{
    int angle = Vec_YawTo(mcat_position(cat), point);
    return SceneObject_IsWithinQuarterTurn((s16) (angle - mcat_s16(cat, MCAT_YAW)));
}

/* ---- The object */

/* func_ov074_02278a00 (vtable slot 0x40): her face's destructor, her talk scene's, then the
 * special character's; the object. */
MysteryCat *MysteryCat_Destroy(MysteryCat *cat)
{
    *(const u8 **) (void *) cat->base = data_ov074_02279c68;
    MysteryCatFace_Destruct(&cat->face);
    MysteryCatTalk_Destroy(&cat->talk);
    SpecialSceneObject_DestructBody(cat);
    return cat;
}
CLEAN_AS(func_ov074_02278a00, MysteryCat_Destroy)

/* func_ov074_02278a34 (vtable slot 0x44): the same, then the object freed. */
void *MysteryCat_Delete(void *object)
{
    MysteryCat *cat = object;
    *(const u8 **) (void *) cat->base = data_ov074_02279c68;
    MysteryCatFace_Destruct(&cat->face);
    MysteryCatTalk_Destroy(&cat->talk);
    SpecialSceneObject_DestructBody(cat);
    Heap_FreeAux(cat);
    return cat;
}
CLEAN_AS(func_ov074_02278a34, MysteryCat_Delete)

/* ---- Her face */

/* func_ov074_02278a6c: the copy taken off the VBlank queue and, when there is one, the texture
 * file given back to `heap`. */
void MysteryCatFace_End(MysteryCatFace *face, const void *heap)
{
    VramCopyMaterial_End(&face->copy);
    if (face->file != NULL) {
        Heap_Free((Heap *) (uintptr_t) heap, face->file);
    }
}
CLEAN_AS(func_ov074_02278a6c, MysteryCatFace_End)

/* func_ov074_02278a90: the design of the town's record put into the texture file and its
 * textures queued to be copied over the material "f" of `model`'s model resource (texture and
 * palette 0). Nothing without the design, when it does not go in, or without textures. */
void MysteryCatFace_Show(MysteryCatFace *face, u8 *model)
{
    Design *design = WfcStats_Design(&data_021f3278);
    if (design == NULL) {
        return;
    }
    if (ClothTexture_PutDesign((DesignModel *) (void *) face->file, design) == 0) {
        return;
    }
    int textures = MysteryCatFace_Textures(face);
    if (textures == 0) {
        return;
    }
    const u8 *resource = ((const LayeredModel *) (const void *) model)->model_resource;
    VramCopyMaterial_Queue(&face->copy, resource, data_ov074_02279b44, (G3dResTex *) (uintptr_t) textures, 0, 0);
}
CLEAN_AS(func_ov074_02278a90, MysteryCatFace_Show)

/* func_ov074_02278adc: the textures of the texture file (ClothTexture_GetTextures), 0 without
 * a file. */
int MysteryCatFace_Textures(MysteryCatFace *face)
{
    if (face->file == NULL) {
        return 0;
    }
    return (int) (uintptr_t) ClothTexture_GetTextures((DesignModel *) (void *) face->file);
}
CLEAN_AS(func_ov074_02278adc, MysteryCatFace_Textures)

/* func_ov074_02278af8: a texture file allocated from `heap` (ClothTexture_Size bytes), then the
 * face shown on `model`. */
void MysteryCatFace_Start(MysteryCatFace *face, int heap, int model)
{
    int size = ClothTexture_Size();
    face->file = Heap_Alloc((Heap *) (uintptr_t) (u32) heap, size);
    MysteryCatFace_Show(face, (u8 *) (uintptr_t) (u32) model);
}
CLEAN_AS(func_ov074_02278af8, MysteryCatFace_Start)

/* func_ov074_02278b1c: the destructor: nothing (the copy is not ended here). */
void MysteryCatFace_Destruct(MysteryCatFace *face)
{
    (void) face;
}
CLEAN_AS(func_ov074_02278b1c, MysteryCatFace_Destruct)

/* func_ov074_02278b20: the constructor: the copy's (the file is left as the zeroed object
 * has it). */
MysteryCatFace *MysteryCatFace_Construct(MysteryCatFace *face)
{
    VramCopyMaterial_Construct(&face->copy);
    return face;
}
CLEAN_AS(func_ov074_02278b20, MysteryCatFace_Construct)

/* ---- Her events */

/* func_ov074_02278b34 (vtable slot 0x4c, told of an event about her): code 0, state 0 (the
 * talk ends once her action is idle); code 3, her talk scene told through its slot 0x08, the
 * talk's partner this console's player's object, and she talks (state 4); code 8, the event
 * ended: she wanders (state 2). The base class is not told. */
void MysteryCat_OnEvent(MysteryCat *cat, int code)
{
    switch (code) {
        case MCAT_EVENT_0:
            MysteryCat_SetState(cat, MYSTERY_CAT_TALK_END);
            break;
        case MCAT_EVENT_TALK: {
            u32 vtable = *(const u32 *) (const void *) &cat->talk;
            u32 slot = *(const u32 *) (uintptr_t) (vtable + MCAT_TALK_SLOT_08);
            ((void (*)(MysteryCatTalk *))(uintptr_t) slot)(&cat->talk);
            SceneBase_SetMotionArg(&cat->talk.base, SceneObject_ActorObject(cat->base, MCAT_PLAYER_ACTOR));
            MysteryCat_SetState(cat, MYSTERY_CAT_TALK);
            break;
        }
        case MCAT_EVENT_ENDED:
            MysteryCat_SetState(cat, MYSTERY_CAT_WANDER);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov074_02278b34, MysteryCat_OnEvent)

/* func_ov074_02278b84 (vtable slot 0x48): whether the player may talk to her: her action is
 * idle. */
int MysteryCat_MayAct(MysteryCat *cat)
{
    return SceneAction_IsBusy(mcat_action(cat)) == 0;
}
CLEAN_AS(func_ov074_02278b84, MysteryCat_MayAct)

/* ---- Her states */

/* func_ov074_02279150 (state 4's update): nothing. 1. */
int MysteryCat_UpdateTalk(void)
{
    return 1;
}
CLEAN_AS(func_ov074_02279150, MysteryCat_UpdateTalk)

/* func_ov074_02279154 (state 4's entry): she turns to the talk's partner (when it has one,
 * else keeps her angle) and talks (her motion kept, the camera not). 1. */
int MysteryCat_EnterTalk(MysteryCat *cat)
{
    int partner = SceneBase_MotionArg(&cat->talk.base);
    int angle = mcat_s16(cat, MCAT_YAW);
    if (partner != 0) {
        angle = SceneObject_YawTo(cat->base, (u8 *) (uintptr_t) (u32) partner);
    }
    SceneAction_RequestTurnAndTalk(mcat_action(cat), 0, angle, 0);
    return 1;
}
CLEAN_AS(func_ov074_02279154, MysteryCat_EnterTalk)

/* func_ov074_02279190 (state 1's update): nothing. 1. */
int MysteryCat_UpdateTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov074_02279190, MysteryCat_UpdateTalked)

/* func_ov074_02279194 (state 0's update): once her action is idle, the object's event ends and
 * state 1 follows. 1. */
int MysteryCat_UpdateTalkEnd(MysteryCat *cat)
{
    if (!SceneAction_IsBusy(mcat_action(cat))) {
        EventQueue_FinishObjectEvent(cat);
        MysteryCat_SetState(cat, MYSTERY_CAT_TALKED);
    }
    return 1;
}
CLEAN_AS(func_ov074_02279194, MysteryCat_UpdateTalkEnd)

/* func_ov074_022791c0 (state 0's entry): 1. */
int MysteryCat_EnterTalkEnd(void)
{
    return 1;
}
CLEAN_AS(func_ov074_022791c0, MysteryCat_EnterTalkEnd)

/* func_ov074_022791c4 (state 3's update): once she is in the camera's view, she wanders
 * (state 2). 1. */
int MysteryCat_UpdateWait(MysteryCat *cat)
{
    if (MysteryCat_InView(cat)) {
        MysteryCat_SetState(cat, MYSTERY_CAT_WANDER);
    }
    return 1;
}
CLEAN_AS(func_ov074_022791c4, MysteryCat_UpdateWait)

/* func_ov074_022791e0 (state 3's entry): she stands, with no walk frames left and her
 * footsteps off. 1. */
int MysteryCat_EnterWait(MysteryCat *cat)
{
    mcat_stand(cat);
    *mcat_part(cat, MCAT_WALK_FRAMES) = 0;
    Footsteps_Disable(mcat_footsteps(cat));
    return 1;
}
CLEAN_AS(func_ov074_022791e0, MysteryCat_EnterWait)

/* func_ov074_02279230 (state 2's update): her walk frames counted down, then:
 * - out of the camera's view: while she moves, state 3;
 * - in view, unless she is steering aside (MysteryCat_IsSteeringAside):
 *   - once her motion is done: she stands when the pair at 0x3aa says 2; else on one frame in
 *     eight (the game's first random generator) a free point 12.0 away is picked: within a
 *     quarter turn of where she faces she walks to it (kind 1, or 2 on one in four) unless
 *     she walks so already, for up to 100 frames; else she turns and walks (kind 4) unless she
 *     does so already, for up to 80 frames; without a point, or on the other frames, she
 *     stands;
 *   - while her motion goes on, she moves and walks or turns (kinds 1, 2 or 4): she stands
 *     when her walk frames ran out, or when the end point of her mover is more than a quarter
 *     turn from where she faces.
 * 0. */
int MysteryCat_UpdateWander(MysteryCat *cat)
{
    SceneMotion *motion = mcat_motion(cat);
    int in_view = MysteryCat_InView(cat);
    u8 *frames = mcat_part(cat, MCAT_WALK_FRAMES);

    Countdown_Tick8(frames);
    if (!in_view) {
        if (mcat_speed(cat) != 0) {
            MysteryCat_SetState(cat, MYSTERY_CAT_WAIT);
        }
        return 0;
    }
    if (MysteryCat_IsSteeringAside(cat)) {
        return 0;
    }
    if (SceneMotion_IsDone(motion)) {
        if (SceneValue3aa_Grade((SceneValue3aa *) (void *) mcat_part(cat, MCAT_VALUE_3AA)) == MCAT_GRADE_STAND) {
            mcat_stand(cat);
            return 0;
        }
        if ((Random_Next(&data_021cb5a0) & 7) != 0) {
            mcat_stand(cat);
            return 0;
        }
        Vec3 point = data_021fbee8;
        if (!MysteryCat_PickWalkPoint(cat, &point.x, &point.z)) {
            mcat_stand(cat);
            return 0;
        }
        int angle = Vec_YawTo(mcat_position(cat), &point);
        if (SceneObject_IsWithinQuarterTurn((s16) (angle - mcat_s16(cat, MCAT_YAW)))) {
            int kind = MCAT_MOTION_WALK;
            if (MainRandom_Below(4) == 0) {
                kind = MCAT_MOTION_WALK_2;
            }
            if (kind != SceneMotion_Kind(motion)) {
                mcat_move(cat, kind, point.x, point.z, 0);
                *frames = MCAT_WALK_FRAMES_WALK;
            }
        } else if (SceneMotion_Kind(motion) != MCAT_MOTION_TURN_WALK) {
            mcat_move(cat, MCAT_MOTION_TURN_WALK, point.x, point.z, angle);
            *frames = MCAT_WALK_FRAMES_TURN;
        }
        return 0;
    }
    if (mcat_speed(cat) != 0 && mcat_is_walking(cat)) {
        if (*frames == 0) {
            mcat_stand(cat);
        } else {
            Vec3 end = *SceneMover_End(mcat_mover(cat));
            if (!mcat_faces(cat, &end)) {
                mcat_stand(cat);
            }
        }
    }
    return 0;
}
CLEAN_AS(func_ov074_02279230, MysteryCat_UpdateWander)

/* func_ov074_02279478: whether she moves and steps aside of what blocks her way
 * (MysteryCat_SteerAside). */
int MysteryCat_IsSteeringAside(MysteryCat *cat)
{
    if (mcat_speed(cat) == 0) {
        return 0;
    }
    return MysteryCat_SteerAside(cat) != 0;
}
CLEAN_AS(func_ov074_02279478, MysteryCat_IsSteeringAside)

/* func_ov074_0227949c: what the probe ahead says, acted on while she is not yet within her
 * mover's reach of its start point: its first point blocked, the mover's end becomes the free
 * point beside the way at (-0.5, 0, 1.0); its second, the one at (0.5, 0, 1.0); with no free
 * point there, or with both blocked, she stands; whether it acted (1 for those). Within reach,
 * the mover's end goes back to its start when they differ; 0. */
int MysteryCat_SteerAside(MysteryCat *cat)
{
    SceneMover *mover = mcat_mover(cat);
    int blocked = SceneProbe_Bits(mcat_part(cat, MCAT_PROBE));

    if (SceneMover_Reached(mover, cat->base, 1) != 0) {
        if (SceneMover_PointsDiffer(mover)) {
            SceneMover_EndAtStart(mover);
        }
        return 0;
    }

    const Vec3 *offset;
    switch (blocked) {
        case MCAT_PROBE_FIRST:
            offset = &data_ov074_02279d84[1];
            break;
        case MCAT_PROBE_SECOND:
            offset = &data_ov074_02279d84[0];
            break;
        case MCAT_PROBE_BOTH:
            mcat_stand(cat);
            return 1;
        default:
            return 0;
    }
    Vec3 point;
    if (MysteryCat_SidePoint(cat, &point, offset)) {
        SceneMover_SetEnd(mover, &point);
    } else {
        mcat_stand(cat);
    }
    return 1;
}
CLEAN_AS(func_ov074_0227949c, MysteryCat_SteerAside)

/* func_ov074_0227959c: the point `offset` from her, turned by her walking angle; kept in `out`
 * when it is not blocked (SceneProbe_IsBlocked other than 1). Whether it was. */
int MysteryCat_SidePoint(MysteryCat *cat, Vec3 *out, const Vec3 *offset)
{
    Vec3 point;
    SceneProbe_PointAt(&point, mcat_position(cat), offset, mcat_s16(cat, MCAT_WALK_ANGLE));
    if (SceneProbe_IsBlocked(&point) == 1) {
        return 0;
    }
    *out = point;
    return 1;
}
CLEAN_AS(func_ov074_0227959c, MysteryCat_SidePoint)

/* func_ov074_022795d8: up to six tries at a point 12.0 from her in a random direction (the
 * game's first random generator), put at its tile's centre: the first whose tile is clear
 * (TownTile_IsClearAt) gives `*x` and `*z`. Whether one did. */
int MysteryCat_PickWalkPoint(MysteryCat *cat, fx32 *x, fx32 *z)
{
    Vec3 point = {0, 0, 0};
    for (int i = 0; i < MCAT_WALK_TRIES; i++) {
        u16 angle = (u16) (s16) Random_Next(&data_021cb5a0);
        int index = (angle >> 4) * 2;
        point.x = FX_MulFunc(MCAT_WALK_DISTANCE, FX_SinCosTable_[index]) + mcat_position(cat)->x;
        point.z = FX_MulFunc(MCAT_WALK_DISTANCE, FX_SinCosTable_[index + 1]) + mcat_position(cat)->z;
        AcreTile_SnapToTileCentre(&point, &point);
        if (TownTile_IsClearAt(&point, NULL)) {
            *x = point.x;
            *z = point.z;
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov074_022795d8, MysteryCat_PickWalkPoint)

/* func_ov074_02279668: whether there is a field camera and she is in its view around the
 * point it looks at (MysteryCat_IsInViewOf). */
int MysteryCat_InView(MysteryCat *cat)
{
    if (data_021c67a4 == NULL) {
        return 0;
    }
    Vec3 focus = data_021c67d0;
    return MysteryCat_IsInViewOf((int) (u32) (uintptr_t) cat, &focus, mcat_position(cat));
}
CLEAN_AS(func_ov074_02279668, MysteryCat_InView)

/* func_ov074_022796a0: whether `at` is strictly within 16.0 of `focus` on x and strictly between
 * 26.0 before and 10.0 past it on z. */
int MysteryCat_IsInViewOf(int unused, const Vec3 *focus, const Vec3 *at)
{
    (void) unused;
    return at->x > focus->x - MCAT_VIEW_X && at->x < focus->x + MCAT_VIEW_X && at->z > focus->z - MCAT_VIEW_Z_NEAR &&
           at->z < focus->z + MCAT_VIEW_Z_FAR;
}
CLEAN_AS(func_ov074_022796a0, MysteryCat_IsInViewOf)

/* func_ov074_022796f8 (state 2's entry): no walk frames left; she stands; her footsteps on
 * (twice); she looks at the player (priority 0, within her look's range, only in view). 1. */
int MysteryCat_EnterWander(MysteryCat *cat)
{
    *mcat_part(cat, MCAT_WALK_FRAMES) = 0;
    mcat_stand(cat);
    Footsteps_Enable(mcat_footsteps(cat));
    Footsteps_Enable(mcat_footsteps(cat));
    SceneLook_Request((SceneLook *) (void *) mcat_part(cat, MCAT_LOOK), SCENE_LOOK_PLAYER, 0, 0, &data_021fbee8,
                      MCAT_PLAYER_ACTOR, data_020c814c, 1);
    return 1;
}
CLEAN_AS(func_ov074_022796f8, MysteryCat_EnterWander)

/* func_ov074_02279778: state `state` taken when its entry function, if it has one, answers
 * nonzero.
 * REQUIRES: `state` is 0 to 4 (the table is not bounded). */
void MysteryCat_SetState(MysteryCat *cat, int state)
{
    const MysteryCatStep *step = &data_ov074_02279d9c[state];
    int taken = 1;
    if (step->enter.function != 0) {
        taken = MemberPointer_CallInt(&step->enter, cat);
    }
    if (taken != 0) {
        cat->state = state;
    }
}
CLEAN_AS(func_ov074_02279778, MysteryCat_SetState)

/* func_ov074_022797bc (vtable slot 0x68, each frame): her state's update when it has one, and
 * its answer; else 0.
 * REQUIRES: her state is 0 to 4. */
int MysteryCat_Update(MysteryCat *cat)
{
    const MysteryCatStep *step = &data_ov074_02279d9c[cat->state];
    if (step->update.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&step->update, cat);
}
CLEAN_AS(func_ov074_022797bc, MysteryCat_Update)

/* func_ov074_02279808 (vtable slot 0x70): her model's file name, "npc_sp/model/mkab.nsbmd". */
int MysteryCat_ModelName(void)
{
    return (int) (u32) (uintptr_t) data_ov074_02279ba0;
}
CLEAN_AS(func_ov074_02279808, MysteryCat_ModelName)

/* func_ov074_02279810 (vtable slot 0x6c): her texture's file name: none (her face is the
 * town's design). */
int MysteryCat_TextureName(void)
{
    return 0;
}
CLEAN_AS(func_ov074_02279810, MysteryCat_TextureName)

/* func_ov074_02279814 (vtable slot 0x0c, her leaving): unless the special character refuses,
 * her face ends (its file given back to the current heap). Whether she left. */
int MysteryCat_Leave(MysteryCat *cat)
{
    if (SpecialSceneObject_Leave(cat) == 0) {
        return 0;
    }
    MysteryCatFace_End(&cat->face, data_021fbe94);
    return 1;
}
CLEAN_AS(func_ov074_02279814, MysteryCat_Leave)

/* func_ov074_02279840 (vtable slot 0x00, her start): unless the special character refuses to
 * start, her face starts (its file from the current heap, shown on her model) and she waits
 * (state 3). Whether she started. */
int MysteryCat_Start(MysteryCat *cat)
{
    if (SpecialSceneObject_Start(cat) == 0) {
        return 0;
    }
    MysteryCatFace_Start(&cat->face, (int) (u32) (uintptr_t) data_021fbe94,
                         (int) (u32) (uintptr_t) mcat_part(cat, MCAT_MODEL));
    MysteryCat_SetState(cat, MYSTERY_CAT_WAIT);
    return 1;
}
CLEAN_AS(func_ov074_02279840, MysteryCat_Start)

/* func_ov074_02279878 (vtable slot 0x04, her set-up): unless the special character refuses,
 * her talk scene becomes her scene and gets her as its owner. Whether she was set up. */
int MysteryCat_Init(MysteryCat *cat)
{
    if (SpecialSceneObject_Init(cat) == 0) {
        return 0;
    }
    SceneObject_SetScene(cat->base, &cat->talk.base);
    MysteryCatTalk_Begin(&cat->talk, cat);
    return 1;
}
CLEAN_AS(func_ov074_02279878, MysteryCat_Init)

/* func_ov074_022798a8 (vtable slot 0xa8): the speed scale of her animation player, main's
 * data_020c8120 as it is (the special character's own slot gives data_021c30ac). */
int MysteryCat_AnimSpeed(void)
{
    return data_020c8120;
}
CLEAN_AS(func_ov074_022798a8, MysteryCat_AnimSpeed)

/* func_ov074_022798b4 (the create function her record at 0x02279bb8 names): a zeroed block of
 * 0x740 bytes from the auxiliary heap, constructed: the scene object base, the class
 * 0x020d8c64's vtable and members in place order (no person yet, 0xfff1), the class
 * 0x020da088's vtable and heap link, then the class's vtable, its talk scene and her face.
 * Null when there is no room. */
void *MysteryCat_Create(void)
{
    MysteryCat *cat = (MysteryCat *) Heap_AllocAuxZeroed(sizeof(MysteryCat));
    if (cat == NULL) {
        return NULL;
    }
    u8 *object = cat->base;
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) mcat_part(cat, MCAT_PERSON) = MCAT_NO_PERSON;
    LayeredModel_ConstructB((LayeredModel *) (void *) mcat_part(cat, MCAT_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) mcat_part(cat, MCAT_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) mcat_part(cat, MCAT_FACE_PART));
    /* func_020169a8, the animation player's constructor (registered under the destructor's
     * name). */
    SpeakerAnim_Destruct((SpeakerAnim *) (void *) mcat_part(cat, MCAT_ANIM));
    SceneMover_Construct(mcat_mover(cat));
    SceneProbe_Construct(mcat_part(cat, MCAT_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) mcat_part(cat, MCAT_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) mcat_part(cat, MCAT_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) mcat_part(cat, MCAT_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) mcat_part(cat, MCAT_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) mcat_part(cat, MCAT_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) mcat_part(cat, MCAT_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) mcat_part(cat, MCAT_EMITTER));
    Footsteps_Construct(mcat_footsteps(cat));
    SceneMotion_Construct(mcat_motion(cat));
    SceneAction_Construct(mcat_action(cat));
    *(const u8 **) (void *) object = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) mcat_part(cat, MCAT_HEAP));
    *(const u8 **) (void *) object = data_ov074_02279c68;
    MysteryCatTalk_Construct(&cat->talk);
    MysteryCatFace_Construct(&cat->face);
    return cat;
}
CLEAN_AS(func_ov074_022798b4, MysteryCat_Create)
