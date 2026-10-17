/* A cockroach of the player's house (house_roach.h). */
#include "house_roach.h"

#include "autoload_2/heap.h"
#include "autoload_2/links.h"
#include "autoload_2/matrix.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "house_roaches.h"
#include "main/actor_table.h"
#include "main/animated_model.h"
#include "main/collision_box.h"
#include "main/collision_query.h"
#include "main/effect_system.h"
#include "main/globe.h"
#include "main/main_random.h"
#include "main/model_object.h"
#include "main/rom_file.h"
#include "main/scene_kinds.h"
#include "main/session_players.h"
#include "main/shadow.h"

static_assert(offsetof(HouseRoachActor, walk_speed) == 0x0d4, "roach walk speed");
static_assert(offsetof(HouseRoachActor, contacts) == 0x0dc, "roach contacts");
static_assert(offsetof(HouseRoachActor, state) == 0x10c, "roach state");
static_assert(offsetof(HouseRoachActor, sound) == 0x114, "roach sound");
static_assert(offsetof(HouseRoachActor, model) == 0x120, "roach model");
static_assert(offsetof(HouseRoachActor, body) == 0x1d8, "roach body");
static_assert(offsetof(HouseRoachActor, body.base.body.touched) == 0x214, "roach body touched");
static_assert(offsetof(HouseRoachActor, start_angle) == 0x228, "roach start angle");
static_assert(offsetof(HouseRoachActor, timer) == 0x22c, "roach timer");
static_assert(offsetof(HouseRoachActor, feelers) == 0x230, "roach feelers");
static_assert(offsetof(HouseRoachActor, feelers_last) == 0x248, "roach feelers before");
static_assert(offsetof(HouseRoachActor, blocked) == 0x260, "roach blocked");
static_assert(offsetof(HouseRoachActor, turn) == 0x262, "roach turn");
static_assert(offsetof(HouseRoachActor, sound_state) == 0x264, "roach sound state");
static_assert(sizeof(HouseRoachActor) == 0x268, "roach");
static_assert(offsetof(AnimatedModel, object.unk_64) == 0x64, "model matrix");
static_assert(offsetof(Process, param) == 0x08, "process param");

#define HOUSE_ROACH_PLAYER 4 /* the own player's actor (SessionPlayers_ActorOf) */
#define HOUSE_ROACH_ALPHA_FULL 0x1f
#define HOUSE_ROACH_GONE_PARAM 0xffff
#define HOUSE_ROACH_ONE 0x1000
/* How near the player or a villager makes it jump (in the ground plane, and within this
 * angle of its heading on the same side), and how near makes it run while standing. */
#define HOUSE_ROACH_JUMP_NEAR 0x1800
#define HOUSE_ROACH_JUMP_ANGLE 0x2aaa
/* Its turn when blocked, and the shared wiggle's. */
#define HOUSE_ROACH_TURN 0xaaa
/* The feelers: 60/100 of a unit ahead, 0xe38 to each side, 0x200 up. */
#define HOUSE_ROACH_FEELER_DISTANCE 60
#define HOUSE_ROACH_FEELER_SPREAD 0xe38
#define HOUSE_ROACH_FEELER_HEIGHT 0x200
/* A feeler is blocked above this ground height or height. */
#define HOUSE_ROACH_FEELER_STEP 0x200
#define HOUSE_ROACH_FEELER_TOO_HIGH 0x1000
#define HOUSE_ROACH_RADIUS 0x19a
#define HOUSE_ROACH_BODY_HEIGHT 0x333
#define HOUSE_ROACH_MOVE_RADIUS 0x666
#define HOUSE_ROACH_COLLISION_FLAGS 15
/* Found this high, it is up on something. */
#define HOUSE_ROACH_RAISED 0xc00
#define HOUSE_ROACH_GRAVITY (-0x333)
#define HOUSE_ROACH_LANDED 3 /* a jump ends below this height */
#define HOUSE_ROACH_VANISH_EFFECT 0x50
#define HOUSE_ROACH_SOUND_RUSTLE_NUMBER 0x225
#define HOUSE_ROACH_SOUND_JUMP_NUMBER 0x226
#define HOUSE_ROACH_SOUND_VANISH_NUMBER 0x227
#define HOUSE_ROACH_MODEL_NAME 0x474f4b49 /* "GOKI" */
#define HOUSE_ROACH_HEAP_SIZE 0x5000
#define HOUSE_ROACH_POLYGON_ID 3
#define HOUSE_ROACH_ALPHA_MASK 0x1f0000 /* the alpha bits of the polygon attributes */
#define HOUSE_ROACH_BODY_FLAGS 0x81
#define HOUSE_ROACH_BODY_TOUCHES 0xc
#define HOUSE_ROACH_TOUCH_PLAYER 4
#define HOUSE_ROACH_TOUCH_VILLAGER 8
#define HOUSE_ROACH_KEEP_OUT_BOXES 4
#define HOUSE_ROACH_FRAMES 20 /* the timer counts in units of this */
#define HOUSE_ROACH_VILLAGER_ENTRIES 8

/* A villager in the room: the last of the actor table's kind 0xe entries found
 * (HouseRoach_FindVillager), NULL until one is. */
extern Actor *data_ov004_02259a14;
/* A wiggle all the cockroaches share, counted -1 to 4 by those running free. */
extern s8 data_ov004_02259a04;

/* The class's vtable, the actor's and the process base's; the actors' list. */
extern const u32 data_ov004_0225622c[];
extern const u32 data_020d7244[];
extern const u32 data_020da13c[];
extern List data_0213ff78;
/* A sound source's class, set over its base's. */
extern const u32 data_0213efe8[];
extern const u32 data_0213f020[];
extern Heap *data_021fbe94; /* the current heap */
/* "/insect/51/bug52.nsbmd" and "/insect/51/bug52.nsbva". */
extern const char data_ov004_022561a4[];
extern const char data_ov004_02256274[];

extern const fx16 FX_SinCosTable_[4096 * 2];
extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern fx32 FX_Div(fx32 a, fx32 b);
extern void *NNS_G3dGetVisAnmSet(void *file);
extern u8 *func_02107cf0(void *set, u32 index);
extern void NNSi_G3dModifyPolygonAttrMask(u8 *model, int on, u32 mask);

/* The feelers' constructor and destructor handed to __cxa_vec_ctor and __cxa_vec_cleanup: the
 * game's (TrivialObject_Construct and TrivialObject_Destruct in Clean). */
extern void func_020012e8(void *object);
extern void func_020012dc(void *object);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

static AnimatedModel *roach_model(HouseRoachActor *roach)
{
    return (AnimatedModel *) (void *) roach->model;
}

/* Its process's param, which is its alpha. */
static u32 *roach_alpha(HouseRoachActor *roach)
{
    return &((Process *) (void *) roach)->param;
}

static Actor *roach_player(void)
{
    return SessionPlayers_ActorOf(HOUSE_ROACH_PLAYER);
}

/* A random time of `extra` plus 0 to `range` - 1, in units of 20 frames, cut to 16 bits. */
static s16 random_time(int range, unsigned int extra)
{
    return (s16) (HOUSE_ROACH_FRAMES * (MainRandom_Below(range) + extra));
}

/* func_ov004_0223d608 (vtable slot 3): HouseRoach_Release.
 * QUIRK: nothing is returned in C; the ROM's code leaves HouseRoach_Release's 1 as its
 * result. */
void HouseRoach_Remove(HouseRoachActor *roach)
{
    HouseRoach_Release(roach);
}
CLEAN_AS(func_ov004_0223d608, HouseRoach_Remove)

/* func_ov004_0223d610 (vtable slot 6): HouseRoach_Update (its result is left as the ROM's). */
void HouseRoach_Execute(HouseRoachActor *roach)
{
    HouseRoach_Update(roach);
}
CLEAN_AS(func_ov004_0223d610, HouseRoach_Execute)

/* func_ov004_0223d618 (vtable slot 0): loaded in a room of the house; 1 elsewhere. */
int HouseRoach_Create(HouseRoachActor *roach)
{
    if (SceneKinds_CurrentIsHouseRoom() != 0) {
        return HouseRoach_Load(roach);
    }
    return 1;
}
CLEAN_AS(func_ov004_0223d618, HouseRoach_Create)

/* func_ov004_0223d634 (vtable slot 9): HouseRoach_Draw (its result is left as the ROM's). */
void HouseRoach_DrawPhase(HouseRoachActor *roach)
{
    HouseRoach_Draw(roach);
}
CLEAN_AS(func_ov004_0223d634, HouseRoach_DrawPhase)

/* Turns `heading` by one turn: by -HOUSE_ROACH_TURN for `left`, else by +HOUSE_ROACH_TURN. */
static s16 turned(s16 heading, int left)
{
    return (s16) (left ? heading - HOUSE_ROACH_TURN : heading + HOUSE_ROACH_TURN);
}

/* func_ov004_0223d63c: a running frame (HouseRoach_Move, while not standing): the feelers are
 * set and tested; the player, then a villager, near enough in front of it on the same side of
 * angle 0 makes it jump (at its run speed). A jump follows a parabola in its frames until it
 * comes down below 3, where it ends and the animation goes back to frame 0. Not jumping, it
 * turns away from a blocked feeler (with both blocked, on in the way it turned last, the
 * first way being -), and else wiggles by the shared counter; and it asks for its rustle.
 * Its heading is set to the result; 1.
 * QUIRK: the angles are compared only when both are on the same side of 0 (or one is 0). */
int HouseRoach_Run(HouseRoachActor *roach)
{
    s16 heading = roach->actor.angle[1];
    Vec3 *position = &roach->actor.position;
    int found = 0;
    HouseRoach_SetFeelers(roach, HOUSE_ROACH_FEELER_DISTANCE, HOUSE_ROACH_FEELER_SPREAD);
    roach->blocked = (s8) HouseRoach_FeelersBlocked(roach);
    for (u8 i = 0; i < 2; i++) {
        Actor *other = i == 0 ? roach_player() : data_ov004_02259a14;
        if (other == NULL || found) {
            continue;
        }
        if (Vec_DistanceXZ(position, &other->position) >= HOUSE_ROACH_JUMP_NEAR) {
            continue;
        }
        s16 toward = Vec_YawTo(position, &other->position);
        if ((toward >= 0 && heading >= 0) || (toward <= 0 && heading <= 0)) {
            int off = toward - heading;
            if (off < 0) {
                off = -off;
            }
            if (off < HOUSE_ROACH_JUMP_ANGLE) {
                roach->jump_frame = (s16) (roach->jump_frame + 1);
                roach->jumping = 1;
                found = 1;
                roach->actor.speed = roach->run_speed;
                HouseRoach_PlaySound(roach, HOUSE_ROACH_SOUND_JUMP);
            }
        }
    }
    if (roach->jump_frame > 0) {
        int t = roach->jump_frame << 12;
        position->y = FX_MulFunc(0x99a - FX_MulFunc(0xcd, t), t);
        if (position->y < HOUSE_ROACH_LANDED) {
            position->y = HOUSE_ROACH_LANDED;
            roach->jump_frame = 0;
            roach->jumping = 0;
            AnimatedModel_SetFrame(roach_model(roach), 0);
        } else {
            roach->jump_frame = (s16) (roach->jump_frame + 1);
            AnimatedModel_StepFrames(roach_model(roach));
        }
    } else {
        if (roach->blocked > 0) {
            if (roach->blocked == 3) {
                heading = turned(heading, roach->turn == 1 || roach->turn == 10);
            } else if (roach->blocked == 1 || roach->turn == 1) {
                heading = turned(heading, 1);
                roach->turn = 1;
            } else if (roach->blocked == 2 || roach->turn == 2) {
                heading = turned(heading, 0);
                roach->turn = 2;
            }
        } else {
            if (data_ov004_02259a04 == 4) {
                heading = turned(heading, 0);
                data_ov004_02259a04 = -1;
            } else if (data_ov004_02259a04 == 2) {
                heading = turned(heading, 1);
            }
            data_ov004_02259a04 = (s8) (data_ov004_02259a04 + 1);
            if (roach->turn < 10) {
                roach->turn = (u8) (roach->turn * 10);
            }
        }
        HouseRoach_PlaySound(roach, HOUSE_ROACH_SOUND_RUSTLE);
    }
    roach->actor.move_angle[1] = heading;
    roach->actor.angle[1] = roach->actor.move_angle[1];
    return 1;
}
CLEAN_AS(func_ov004_0223d63c, HouseRoach_Run)

/* func_ov004_0223d82c: its body for this frame, at its position, entered for the touches. */
void HouseRoach_SetBody(HouseRoachActor *roach)
{
    FieldOwnedPointBody_Set(&roach->body, &roach->actor, &roach->actor.position, HOUSE_ROACH_RADIUS, HOUSE_ROACH_BODY_HEIGHT,
                            HOUSE_ROACH_BODY_FLAGS, HOUSE_ROACH_BODY_TOUCHES, 0, 0xff, HOUSE_ROACH_ONE);
    FieldBody_Enter(&roach->body.base.body);
}
CLEAN_AS(func_ov004_0223d82c, HouseRoach_SetBody)

/* func_ov004_0223d87c: a standing frame: with the player (then a villager) there, it stands
 * still and its time runs down; when it is up it runs for 1 to 4 times 20 frames; else the
 * one there moving nearer than 4.0 makes it run for 2 to 5 times 20 frames, turned away from
 * the nearer of the two (HouseRoach_NearestOther).
 * QUIRK: the time runs down once for each of the two there, so twice a frame with both. */
void HouseRoach_Stand(HouseRoachActor *roach)
{
    Vec3 *position = &roach->actor.position;
    int outcome = 0; /* 1: its time was up, 2: one came near */
    for (u8 k = 0; k < 2; k++) {
        Actor *other = k == 0 ? roach_player() : data_ov004_02259a14;
        if (other == NULL || outcome != 0) {
            continue;
        }
        roach->timer = (s16) (roach->timer - 1);
        roach->actor.speed = 0;
        if (roach->timer <= 0) {
            roach->state = HOUSE_ROACH_RUN;
            roach->timer = random_time(4, 1);
            outcome = 1;
        } else if (other->speed > 0) {
            fx32 distance = Vec_DistanceXZ(position, &other->position);
            if (distance < FX_MulFunc(HOUSE_ROACH_ONE, 0x4000)) {
                roach->timer = random_time(4, 2);
                roach->state = HOUSE_ROACH_RUN;
                outcome = 2;
            }
        }
    }
    if (outcome == 2) {
        Actor *from = HouseRoach_NearestOther(roach);
        if (from != NULL) {
            roach->actor.move_angle[1] = Vec_YawTo(&from->position, position);
            roach->actor.angle[1] = roach->actor.move_angle[1];
        }
    }
}
CLEAN_AS(func_ov004_0223d87c, HouseRoach_Stand)

/* func_ov004_0223d958: the nearer to it of the player and the villager, by the sum of the
 * distances along X and Z (the player when as near); either when the other is missing. */
Actor *HouseRoach_NearestOther(HouseRoachActor *roach)
{
    Actor *player = roach_player();
    Actor *villager = data_ov004_02259a14;
    if (villager == NULL) {
        return player;
    }
    if (player != NULL) {
        const Vec3 *at = &roach->actor.position;
        int player_x = at->x - player->position.x;
        int player_z = at->z - player->position.z;
        int villager_x = at->x - villager->position.x;
        int villager_z = at->z - villager->position.z;
        if (player_x < 0) {
            player_x = -player_x;
        }
        if (player_z < 0) {
            player_z = -player_z;
        }
        if (villager_x < 0) {
            villager_x = -villager_x;
        }
        if (villager_z < 0) {
            villager_z = -villager_z;
        }
        /* QUIRK: the differences and sums wrap at 32 bits. */
        if (player_x + player_z <= villager_x + villager_z) {
            return player;
        }
    }
    return villager;
}
CLEAN_AS(func_ov004_0223d958, HouseRoach_NearestOther)

/* Moves `feeler` from where it is by `distance` / 100 along the angle `angle`, at the feelers'
 * height. QUIRK: the product is taken in 32 bits and divided rounding towards 0. */
static void place_feeler(Vec3 *feeler, int distance, u16 angle)
{
    int index = (angle >> 4) * 2;
    feeler->x += distance * FX_SinCosTable_[index] / 100;
    feeler->z += distance * FX_SinCosTable_[index + 1] / 100;
    feeler->y = HOUSE_ROACH_FEELER_HEIGHT;
}

/* func_ov004_0223d9c4: both feelers and where they were before start at its position; then
 * the first is put ahead at `spread` to one side of its heading, the second at `spread` to the
 * other. */
void HouseRoach_SetFeelers(HouseRoachActor *roach, int distance, int spread)
{
    const Vec3 *position = &roach->actor.position;
    s16 heading = roach->actor.angle[1];
    roach->feelers[0] = *position;
    roach->feelers[1] = *position;
    roach->feelers_last[0] = roach->feelers[0];
    roach->feelers_last[1] = roach->feelers[1];
    place_feeler(&roach->feelers[0], distance, (u16) (heading + spread));
    place_feeler(&roach->feelers[1], distance, (u16) (heading - spread));
}
CLEAN_AS(func_ov004_0223d9c4, HouseRoach_SetFeelers)

/* One feeler moved by the room's collision from where it was (its own position when that has
 * an X or Z of 0): whether it is blocked, by ground above 0x200 under it, by being above 1.0,
 * or by touching a wall or a post. */
static int feeler_blocked(HouseRoachActor *roach, CollisionContacts *contacts, const CollisionGround *ground, int index,
                          s16 angle)
{
    Vec3 *feeler = &roach->feelers[index];
    Vec3 *last = &roach->feelers_last[index];
    if (last->x == 0 || last->z == 0) {
        *last = *feeler;
    }
    CollisionQuery_Move(contacts, feeler, last, angle, HOUSE_ROACH_RADIUS, roach, HOUSE_ROACH_COLLISION_FLAGS);
    s16 hits = contacts->walls.count;
    return CollisionGround_GetHeight(ground, 1) > HOUSE_ROACH_FEELER_STEP || feeler->y > HOUSE_ROACH_FEELER_TOO_HIGH ||
           hits > 0;
}

/* func_ov004_0223db08: which feelers are blocked: 1 for the first, 2 for the second.
 * QUIRK: the ground under each is the one at its point before the collision moves it, and the
 * contacts are not cleared between the two. */
unsigned char HouseRoach_FeelersBlocked(HouseRoachActor *roach)
{
    unsigned char result = 0;
    CollisionContacts contacts;
    CollisionGround first;
    CollisionGround second;
    CollisionContacts_Construct(&contacts);
    CollisionGround_Init(&first, &roach->feelers[0], 0, 0);
    s16 angle = roach->actor.angle[1];
    if (feeler_blocked(roach, &contacts, &first, 0, angle)) {
        result++;
    }
    CollisionGround_Init(&second, &roach->feelers[1], 0, 0);
    if (feeler_blocked(roach, &contacts, &second, 1, angle)) {
        result += 2;
    }
    CollisionGround_Destroy(&second);
    CollisionGround_Destroy(&first);
    CollisionContacts_Destroy(&contacts);
    return result;
}
CLEAN_AS(func_ov004_0223db08, HouseRoach_FeelersBlocked)

/* func_ov004_0223dc68: HOUSE_ROACH_SOUND_RUSTLE notes it asked and plays the rustle when it is
 * the one chosen to make it, else asks to be (HOUSE_ROACH_ASKING); the others play their sound
 * held. */
void HouseRoach_PlaySound(HouseRoachActor *roach, int sound)
{
    switch (sound) {
        case HOUSE_ROACH_SOUND_RUSTLE:
            roach->sound_asked = 1;
            if (HouseRoach_SoundState(roach) == HOUSE_ROACH_SOUNDING) {
                SoundSource_Play(&roach->sound, HOUSE_ROACH_SOUND_RUSTLE_NUMBER);
            } else {
                HouseRoach_SetSoundState(roach, HOUSE_ROACH_ASKING);
            }
            break;
        case HOUSE_ROACH_SOUND_JUMP:
            SoundSource_PlayHeld(&roach->sound, HOUSE_ROACH_SOUND_JUMP_NUMBER);
            break;
        default:
            SoundSource_PlayHeld(&roach->sound, HOUSE_ROACH_SOUND_VANISH_NUMBER);
            break;
    }
}
CLEAN_AS(func_ov004_0223dc68, HouseRoach_PlaySound)

/* func_ov004_0223dccc: its model is released, it is marked released and made away with
 * (param 0xffff), and its sound released; 1. */
int HouseRoach_Release(HouseRoachActor *roach)
{
    ModelObject_Release(&roach_model(roach)->object);
    roach->life = HOUSE_ROACH_RELEASED;
    *roach_alpha(roach) = HOUSE_ROACH_GONE_PARAM;
    SoundSource_Release(&roach->sound);
    return 1;
}
CLEAN_AS(func_ov004_0223dccc, HouseRoach_Release)

/* func_ov004_0223dd04: unless released: its alpha is kept at most 0x1f and its model drawn
 * with it (polygon ID 3, the alpha of every polygon open to change); its shadow too while it is
 * out at full alpha; 1. */
int HouseRoach_Draw(HouseRoachActor *roach)
{
    if (roach->life != HOUSE_ROACH_RELEASED) {
        AnimatedModel *model = roach_model(roach);
        u32 *alpha = roach_alpha(roach);
        if (*alpha > HOUSE_ROACH_ALPHA_FULL) {
            *alpha = HOUSE_ROACH_ALPHA_FULL;
        }
        ModelObject_SetPolygonId(&model->object, HOUSE_ROACH_POLYGON_ID);
        NNSi_G3dModifyPolygonAttrMask(model->object.model, 1, HOUSE_ROACH_ALPHA_MASK);
        ModelObject_SetAlpha(&model->object, (u8) *alpha);
        AnimatedModel_Draw(model, NULL);
        if (*alpha >= HOUSE_ROACH_ALPHA_FULL && roach->life == HOUSE_ROACH_OUT) {
            CharaShadow_Draw(&roach->actor.position, 0x400, 0x4000, HOUSE_ROACH_ONE);
        }
    }
    return 1;
}
CLEAN_AS(func_ov004_0223dd04, HouseRoach_Draw)

/* func_ov004_0223dd90: whether it was stepped on: touched (and not jumping) by the player's
 * body, or else a villager's, while that one moves; it then vanishes. */
int HouseRoach_CheckStepped(HouseRoachActor *roach)
{
    Actor *player = roach_player();
    if (roach->body.base.body.touched != 0 && roach->jumping == 0) {
        if (player != NULL && player->speed > 0 &&
            FieldBody_TouchedWith(&roach->body.base.body, HOUSE_ROACH_TOUCH_PLAYER) != 0) {
            roach->state = HOUSE_ROACH_VANISH;
            return 1;
        }
        Actor *villager = data_ov004_02259a14;
        if (villager != NULL && villager->speed > 0 &&
            FieldBody_TouchedWith(&roach->body.base.body, HOUSE_ROACH_TOUCH_VILLAGER) != 0) {
            roach->state = HOUSE_ROACH_VANISH;
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov004_0223dd90, HouseRoach_CheckStepped)

/* func_ov004_0223de14: found 0xc00 or higher, it goes back to its height of the frame before;
 * when its move also put it on the ground, it vanishes there, put on the ground's height under
 * it (1). */
int HouseRoach_CheckRaised(HouseRoachActor *roach)
{
    if (roach->actor.position.y >= HOUSE_ROACH_RAISED) {
        roach->actor.position.y = roach->actor.last_position.y;
        if ((roach->contacts.flags & COLLISION_ON_GROUND) != 0) {
            CollisionGround ground;
            roach->state = HOUSE_ROACH_VANISH;
            CollisionGround_Init(&ground, &roach->actor.position, 0, 0);
            roach->actor.position.y = CollisionGround_GetHeight(&ground, 1);
            CollisionGround_Destroy(&ground);
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov004_0223de14, HouseRoach_CheckRaised)

/* func_ov004_0223de70: its frame. At full alpha and out: a villager is looked for while there
 * is none, then it is checked for being stepped on, its body set, it acts and is checked for
 * being up on something; a jump steps its animation. Fading in (out, below full alpha) its
 * alpha goes up by 2 and it moves; else (leaving) it goes down by 1. While its alpha is not 0
 * its pitch follows the globe and its model's matrix is set; at 0 it is released. Its sound
 * state goes back to quiet when it did not ask for its rustle; 1. */
int HouseRoach_Update(HouseRoachActor *roach)
{
    u32 *alpha = roach_alpha(roach);
    roach->sound_asked = 0;
    u32 start = *alpha;
    if (start >= HOUSE_ROACH_ALPHA_FULL) {
        if (roach->life == HOUSE_ROACH_OUT) {
            if (data_ov004_02259a14 == NULL) {
                HouseRoach_FindVillager(roach);
            }
            HouseRoach_CheckStepped(roach);
            HouseRoach_SetBody(roach);
            HouseRoach_Act(roach);
            HouseRoach_CheckRaised(roach);
            if (roach->jumping != 0) {
                AnimatedModel_StepFrames(roach_model(roach));
            }
        } else {
            *alpha = start - 1;
        }
    } else if (roach->life == HOUSE_ROACH_OUT) {
        *alpha = start + 2;
        HouseRoach_StepAppearing(roach);
    } else {
        *alpha = start - 1;
    }
    if (*alpha != 0) {
        Mtx43 matrix;
        roach->actor.pitch = (u16) Globe_BendFar(&roach->actor.pivot, &roach->actor.position);
        Actor_ModelMatrix(&roach->actor, &matrix);
        *(Mtx43 *) (void *) roach_model(roach)->object.unk_64 = matrix;
    } else {
        HouseRoach_Release(roach);
    }
    if (roach->sound_asked == 0) {
        HouseRoach_SetSoundState(roach, HOUSE_ROACH_QUIET);
    }
    return 1;
}
CLEAN_AS(func_ov004_0223de70, HouseRoach_Update)

/* func_ov004_0223df48: a frame while it fades in: it moves at its walk speed but keeps its
 * height of the frame before; its sound follows it. */
void HouseRoach_StepAppearing(HouseRoachActor *roach)
{
    roach->actor.speed = roach->walk_speed;
    HouseRoach_Move(roach);
    roach->actor.position.y = roach->actor.last_position.y;
    Vec3 at = roach->actor.position;
    SoundSource_UpdateAt(&roach->sound, &at);
}
CLEAN_AS(func_ov004_0223df48, HouseRoach_StepAppearing)

/* func_ov004_0223df88: its move: the room's keep-out boxes are put in the collision for the
 * frame (four in room 0 of the house, one in each of rooms 1 to 4: centred at points scaled by
 * one half, 1.0 high, four wide along X or along Z), it runs unless standing
 * (HouseRoach_Run), moves (Actor_Move, by its body's push) and is held by the room's
 * collision; then the boxes are taken out.
 * QUIRK: the collision is given its heading from before HouseRoach_Run turned it.
 * BUG: the boxes' centres have no height in the ROM (whatever the stack held); 0 here.
 * REQUIRES: the scene is a room of the house (else the ROM's code reads one box it never
 * set). */
void HouseRoach_Move(HouseRoachActor *roach)
{
    CollisionBox boxes[HOUSE_ROACH_KEEP_OUT_BOXES];
    Vec3 centres[HOUSE_ROACH_KEEP_OUT_BOXES] = {{0, 0, 0}};
    u8 along_x[HOUSE_ROACH_KEEP_OUT_BOXES] = {0};
    u8 added[HOUSE_ROACH_KEEP_OUT_BOXES];
    for (int i = 0; i < HOUSE_ROACH_KEEP_OUT_BOXES; i++) {
        CollisionBox_Construct(&boxes[i]);
    }
    Vec3 *position = &roach->actor.position;
    u8 count = 1;
    int angle = roach->actor.angle[1];
    fx32 scale = FX_Div(HOUSE_ROACH_ONE, 0x2000);
    switch (SceneKinds_CurrentHouseRoomIndex()) {
        case 1:
        case 4:
            centres[0].x = FX_MulFunc(0x20000, scale);
            centres[0].z = FX_MulFunc(0x39000, scale);
            along_x[0] = 1;
            break;
        case 2:
            centres[0].x = FX_MulFunc(0x13000, scale);
            centres[0].z = FX_MulFunc(0x35000, scale);
            along_x[0] = 0;
            break;
        case 3:
            centres[0].x = FX_MulFunc(0x2c000, scale);
            centres[0].z = FX_MulFunc(0x37000, scale);
            along_x[0] = 0;
            break;
        case 0:
            count = 4;
            centres[0].x = FX_MulFunc(0xf000, scale);
            centres[0].z = FX_MulFunc(0x34000, scale);
            along_x[0] = 0;
            centres[1].x = FX_MulFunc(0x31000, scale);
            centres[1].z = FX_MulFunc(0x34000, scale);
            along_x[1] = 0;
            centres[2].x = FX_MulFunc(0x20000, scale);
            centres[2].z = FX_MulFunc(0x39000, scale);
            along_x[2] = 1;
            centres[3].x = FX_MulFunc(0x20000, scale);
            centres[3].z = FX_MulFunc(0x17000, scale);
            along_x[3] = 1;
            break;
    }
    for (u8 i = 0; i < count; i++) {
        if (along_x[i]) {
            fx32 width = FX_MulFunc(0x4000, HOUSE_ROACH_ONE);
            added[i] = (u8) CollisionBox_Add(&boxes[i], width, HOUSE_ROACH_ONE, FX_MulFunc(0xa000, HOUSE_ROACH_ONE),
                                             &centres[i], 0, NULL);
        } else {
            fx32 depth = FX_MulFunc(0x4000, HOUSE_ROACH_ONE);
            added[i] = (u8) CollisionBox_Add(&boxes[i], HOUSE_ROACH_ONE, depth, FX_MulFunc(0xa000, HOUSE_ROACH_ONE),
                                             &centres[i], 0, NULL);
        }
    }
    if (roach->state != HOUSE_ROACH_STAND) {
        HouseRoach_Run(roach);
    }
    Actor_Move(&roach->actor, (const ActorCarrier *) (const void *) &roach->body);
    CollisionQuery_Move(&roach->contacts, position, &roach->actor.last_position, angle, HOUSE_ROACH_MOVE_RADIUS, roach,
                        HOUSE_ROACH_COLLISION_FLAGS);
    for (u8 i = 0; i < count; i++) {
        if (added[i]) {
            CollisionBox_Remove(&boxes[i]);
        }
    }
    for (int i = HOUSE_ROACH_KEEP_OUT_BOXES - 1; i >= 0; i--) {
        CollisionBox_Destruct(&boxes[i]);
    }
}
CLEAN_AS(func_ov004_0223df88, HouseRoach_Move)

/* func_ov004_0223e1f0: its acts at full alpha: it moves unless vanishing, then by its state:
 * standing (HouseRoach_Stand); running at its walk speed until its time is up and it is not
 * jumping, then standing for 3 to 12 times 20 frames; vanishing (an effect at it, its alpha
 * starts down, it is leaving and plays its sound); or, just made, standing (3 to 12) or running
 * (3 to 6 times 20 frames) at even odds. Its sound follows it. */
void HouseRoach_Act(HouseRoachActor *roach)
{
    if (roach->state != HOUSE_ROACH_VANISH) {
        HouseRoach_Move(roach);
    }
    switch (roach->state) {
        case HOUSE_ROACH_STAND:
            HouseRoach_Stand(roach);
            break;
        case HOUSE_ROACH_RUN: {
            roach->actor.speed = roach->walk_speed;
            int left = roach->timer;
            roach->timer = (s16) (left - 1);
            if (left <= 0 && roach->jumping == 0) {
                roach->state = HOUSE_ROACH_STAND;
                roach->timer = random_time(10, 3);
            }
            break;
        }
        case HOUSE_ROACH_VANISH:
            EffectSystem_StartOneShotSetNumberCopy(HOUSE_ROACH_VANISH_EFFECT, &roach->actor.position, NULL, NULL);
            *roach_alpha(roach) -= 1;
            roach->life = HOUSE_ROACH_LEAVING;
            HouseRoach_PlaySound(roach, HOUSE_ROACH_SOUND_VANISH);
            break;
        case HOUSE_ROACH_DECIDE:
            if (MainRandom_Below(100) > 50) {
                roach->state = HOUSE_ROACH_STAND;
                roach->timer = random_time(10, 3);
            } else {
                roach->state = HOUSE_ROACH_RUN;
                roach->timer = random_time(4, 3);
            }
            break;
    }
    Vec3 at = roach->actor.position;
    SoundSource_UpdateAt(&roach->sound, &at);
}
CLEAN_AS(func_ov004_0223e1f0, HouseRoach_Act)

/* func_ov004_0223e2f0: its model (shared as "GOKI"), a frame heap of 0x5000 bytes for its
 * files, its visibility animation started and attached, its sound; its heading kept, its
 * gravity, its walk speed, not jumping, quiet; 1. */
int HouseRoach_Load(HouseRoachActor *roach)
{
    AnimatedModel *model = roach_model(roach);
    ModelObject_LoadShared(&model->object, HOUSE_ROACH_MODEL_NAME, data_ov004_022561a4);
    Heap *heap = Heap_PushFrameHeap(HOUSE_ROACH_HEAP_SIZE, data_021fbe94);
    Process_SetHeap((Process *) (void *) roach, heap);
    AnimatedModel_LoadAnim(model, NULL);
    void *file = RomFile_LoadDefault(data_ov004_02256274);
    Heap_Adjust(heap);
    Heap_PopThreadHeap();
    AnimatedModel_Start(model, func_02107cf0(NNS_G3dGetVisAnmSet(file), 0), 0, HOUSE_ROACH_ONE, 0, 0);
    AnimatedModel_Attach(model);
    SoundSource_Init(&roach->sound);
    roach->actor.move_angle[1] = roach->actor.angle[1];
    roach->start_angle = roach->actor.move_angle[1];
    roach->actor.gravity = HOUSE_ROACH_GRAVITY;
    roach->actor.speed = roach->walk_speed;
    roach->jumping = 0;
    roach->sound_asked = 0;
    roach->sound_state = HOUSE_ROACH_QUIET;
    return 1;
}
CLEAN_AS(func_ov004_0223e2f0, HouseRoach_Load)

/* func_ov004_0223e3d4 */
void HouseRoach_SetSoundState(HouseRoachActor *roach, int state)
{
    roach->sound_state = state;
}
CLEAN_AS(func_ov004_0223e3d4, HouseRoach_SetSoundState)

/* func_ov004_0223e3e0 */
int HouseRoach_SoundState(HouseRoachActor *roach)
{
    return roach->sound_state;
}
CLEAN_AS(func_ov004_0223e3e0, HouseRoach_SoundState)

/* func_ov004_0223e3ec: the villager is the last actor found in the actor table's eight kind
 * 0xe entries; one found before stays when none is. */
void HouseRoach_FindVillager(HouseRoachActor *roach)
{
    (void) roach;
    for (u8 i = 0; i < HOUSE_ROACH_VILLAGER_ENTRIES; i++) {
        Actor *actor = Actors_GetEByIndex(i);
        if (actor != NULL) {
            data_ov004_02259a14 = actor;
        }
    }
}
CLEAN_AS(func_ov004_0223e3ec, HouseRoach_FindVillager)

/* The destructor: its members in the reverse order, then the actor's part (out of the actors'
 * list) and the process. */
static void HouseRoach_destruct(HouseRoachActor *roach)
{
    roach->actor.vtable = data_ov004_0225622c;
    __cxa_vec_cleanup(roach->feelers_last, HOUSE_ROACH_FEELERS, sizeof(Vec3), func_020012dc);
    __cxa_vec_cleanup(roach->feelers, HOUSE_ROACH_FEELERS, sizeof(Vec3), func_020012dc);
    FieldOwnedPointBody_Destruct(&roach->body);
    AnimatedModel_DestructComplete(roach_model(roach));
    CollisionContacts_Destroy(&roach->contacts);
    roach->actor.vtable = data_020d7244;
    List_Remove(&data_0213ff78, &roach->actor.link.node);
    roach->actor.vtable = data_020da13c;
    Process_Destruct((Process *) (void *) roach);
}

/* func_ov004_0223e418: the destructor that frees it. */
HouseRoachActor *HouseRoach_Delete(HouseRoachActor *roach)
{
    HouseRoach_destruct(roach);
    Heap_FreeAux(roach);
    return roach;
}
CLEAN_AS(func_ov004_0223e418, HouseRoach_Delete)

/* func_ov004_0223e4a0 */
HouseRoachActor *HouseRoach_Destruct(HouseRoachActor *roach)
{
    HouseRoach_destruct(roach);
    return roach;
}
CLEAN_AS(func_ov004_0223e4a0, HouseRoach_Destruct)

/* func_ov004_0223e520: the constructor: the actor, its speeds, contacts, sound, model, body
 * and feelers; out, not blocked, not jumping, to decide what it does. */
HouseRoachActor *HouseRoach_Construct(HouseRoachActor *roach)
{
    Actor_Construct(&roach->actor);
    roach->actor.vtable = data_ov004_0225622c;
    roach->walk_speed = 0x614;
    roach->run_speed = 0x6b8;
    CollisionContacts_Construct(&roach->contacts);
    roach->sound.vtable = (const SoundSourceVtable *) (const void *) data_0213efe8;
    roach->sound.vtable = (const SoundSourceVtable *) (const void *) data_0213f020;
    AnimatedModel_Construct(roach_model(roach));
    FieldOwnedPointBody_Construct(&roach->body);
    __cxa_vec_ctor(roach->feelers, HOUSE_ROACH_FEELERS, sizeof(Vec3), func_020012e8, func_020012dc);
    __cxa_vec_ctor(roach->feelers_last, HOUSE_ROACH_FEELERS, sizeof(Vec3), func_020012e8, func_020012dc);
    roach->life = HOUSE_ROACH_OUT;
    roach->blocked = 0;
    roach->turn = 0;
    roach->jump_frame = 0;
    roach->state = HOUSE_ROACH_DECIDE;
    return roach;
}
CLEAN_AS(func_ov004_0223e520, HouseRoach_Construct)
