/* Moves of the town's insects held by overlay 68 (insect_paths.h). */
#include "insect_paths.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/approach.h" /* Approach_S16Wrapped */
#include "clean.h"
#include "main/actor.h" /* Vec_YawTo */
#include "main/acre_map.h"
#include "main/acre_tile.h"
#include "main/actor_table.h" /* Position_Tile */
#include "main/frame_ctrl.h"
#include "main/main_random.h"
#include "main/model_pool.h"
#include "main/session_players.h"
#include "main/tile_requests.h"
#include "main/town_family.h"
#include "ov003/field_actor.h"

static_assert(offsetof(TownInsect, position) == 0x204, "position");
static_assert(offsetof(TownInsect, model) == 0x50, "model");
static_assert(offsetof(TownInsect, files) == 0x130, "files");
static_assert(offsetof(TownInsect, action) == 0x251, "action");
static_assert(offsetof(TownInsect, unk_257) == 0x257, "byte 0x257");

#define INSECT_PATH_PLAYER 4
#define INSECT_PATH_OPAQUE 0x1f      /* a model's full alpha */
#define INSECT_PATH_CALM 0x13        /* TOWN_INSECT_ACTION_SHOWN: its usual behaviour */
#define INSECT_PATH_ALARMED 0x14     /* TownInsect.unk_254 from which kinds 0x36 and 0x37 act */
#define INSECT_PATH_TURN_LIMIT 0x38e /* the most a spot turns it in a frame (5 degrees) */

/* The kinds named here. */
#define INSECT_PATH_KIND_0A 0x0a
#define INSECT_PATH_KIND_33 0x33
#define INSECT_PATH_KIND_HOPS 0x36   /* hops after going for the player */
#define INSECT_PATH_KIND_FRAMES 0x37 /* plays frames 0xb-0xe while going for the player */

/* The sounds of the kinds (func_ov003_022353a4's second argument). */
#define INSECT_PATH_SOUND_IDLE 0
#define INSECT_PATH_SOUND_ACTIVE 1

/* The town's map. */
extern AcreMap *data_021c80bc;

extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern int NNS_G3dMdlGetMdlAlpha(void *model, int material);
extern void NNS_G3dMdlSetMdlAlpha(void *model, int material, int alpha);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *ab);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *ab);
/* Whether a session runs (its flag and its state). */
extern int func_02070070(void);

/* Overlay 3's helpers of the insects. */
/* Kind 0x33's point to settle on, when it has one (within reach of `from`). */
extern int func_ov003_02224718(Vec3 *spot, const Vec3 *from);
/* A flower within reach of `from` whose code passes `mask`, when there is one. */
extern int func_ov003_02224768(Vec3 *spot, const Vec3 *from, int mask);
/* The mask of the flowers a kind settles on: 0xf for kinds 2 and 3, else 0x3f. */
extern int func_ov003_0223482c(int kind);
/* Whether the flower `code` suits kind 2 or 3. */
extern int func_ov003_02235518(int kind, const u16 *code);
/* TownInsect.unk_244 counted down; 1 once it is 0. */
extern int func_ov003_02234984(TownInsect *insect);
/* Kind 0x33's (or other kinds') box around its spot (0x1b0 and 0x1bc). */
extern void func_ov003_02230f88(TownInsect *insect);
/* `src` with its y 0 and its x and z each kept within `t` / 64. */
extern void func_ov003_022321b8(Vec3 *dst, const Vec3 *src, int t);
/* Each frame: it falls (or lands) and keeps clear of what is around. */
extern int func_ov003_02232414(TownInsect *insect);
/* Its kind's sound `which` played (`play`) or stopped. */
extern void func_ov003_022353a4(TownInsect *insect, int which, int play);
/* Its model faded by `by`; 1 once its alpha is 7 or less. */
extern int func_ov003_02232598(TownInsect *insect, int by);
/* It leaves (TOWN_INSECT_STATE_LEAVING) with its model's alpha 0. */
extern void func_ov003_02230f60(TownInsect *insect);
/* The player point it watches (`*point`) and how it sees the player. */
extern int func_ov003_02233e4c(TownInsect *insect, Vec3 *point);
/* Whether the tile of a point is of a kind func_02031b5c accepts. */
extern int func_ov003_02235950(const Vec3 *point);
/* The step of length 0x29 (along z) turned by `angle`. */
extern void func_ov003_0223597c(Vec3 *step, int angle);
/* The z of its scale stretched (by 0x52, 1.0 to 2.0) or squeezed. */
extern void func_ov068_02270d24(Vec3 *scale, int stretch);

static void *insect_model(TownInsect *insect)
{
    return (void *) (uintptr_t) ModelPoolFiles_Model(&insect->files);
}

static int insect_opaque(TownInsect *insect)
{
    return NNS_G3dMdlGetMdlAlpha(insect_model(insect), 0) == INSECT_PATH_OPAQUE;
}

static u16 frame_number(fx32 frame)
{
    return (u16) (((u32) frame << 4) >> 16);
}

/* A hop of kind 0x36 at its frame `t`: up by t * 4/9 less 10 * t * t (in 20.12). */
static fx32 hop_rise(int t)
{
    fx32 rate = FX_Div(0x1000, 0x12000);
    return FX_MulFunc(rate, t << 12) + -10 * (t * t);
}

/* func_ov068_0226fe00: an event insect shown (its model fully opaque, action 0x12). */
void InsectPath_Show(TownInsect *insect)
{
    NNS_G3dMdlSetMdlAlpha(insect_model(insect), 0, INSECT_PATH_OPAQUE);
    insect->action = INSECT_PATH_SHOWN;
}
CLEAN_AS(func_ov068_0226fe00, InsectPath_Show)

/* func_ov068_0226fe28: when there is a point (its x above 0), and the insect is not fleeing
 * already and is alarmed (unk_254 at least unk_255), it flees: heading away from the point
 * (unk_240), for 20 times 7-10 frames (unk_244), at the height unk_228. */
void InsectPath_FleeFrom(TownInsect *insect, const Vec3 *point)
{
    if (point->x <= 0) {
        return;
    }
    if (insect->unk_24a != 0) {
        return;
    }
    if (insect->unk_254 < insect->unk_255) {
        return;
    }
    insect->unk_240 = Vec_YawTo(point, &insect->position);
    insect->unk_244 = (s16) (0x14 * (MainRandom_Below(4) + 7));
    insect->action = INSECT_PATH_FLEE;
    insect->unk_24a = 1;
    insect->unk_220 = insect->unk_228;
}
CLEAN_AS(func_ov068_0226fe28, InsectPath_FleeFrom)

/* func_ov068_0226fea4: a frame of wandering. A random number below 100 is drawn; every
 * `period`th frame (by its counter) a number above `limit` turns it the other way (unk_24b);
 * a number above unk_252 turns `*heading` by `step` that way. It faces the heading and moves
 * `scale` times the step of length 0x29 along it, 1.25 times that while fleeing (unk_24a),
 * 1.5 times for kinds 0xa and 0x33 (factors the ROM converts from floating point).
 * REQUIRES: `period` is above 0 (the callers pass 0x14 and 0x1e). */
void InsectPath_Wander(TownInsect *insect, s16 *heading, int step, int period, u8 limit, int scale)
{
    int turn_up = insect->unk_24b;
    u32 draw = (u8) MainRandom_Below(100);
    if (insect->counter % period == 0 && draw > limit) {
        turn_up = turn_up == 0;
        insect->unk_24b = (u8) turn_up;
    }
    if (draw > insect->unk_252) {
        if (turn_up != 0) {
            *heading = (s16) (*heading + step);
        } else {
            *heading = (s16) (*heading - step);
        }
    }
    Vec3 way;
    func_ov003_0223597c(&way, *heading);
    insect->angle_y = *heading;
    if (insect->unk_24a != 0) {
        fx32 factor = 0x1400;
        if (insect->kind == INSECT_PATH_KIND_0A || insect->kind == INSECT_PATH_KIND_33) {
            factor = 0x1800;
        }
        insect->position.x += FX_MulFunc(FX_MulFunc(factor, scale), way.x);
        insect->position.z += FX_MulFunc(FX_MulFunc(factor, scale), way.z);
    } else {
        insect->position.x += FX_MulFunc(scale, way.x);
        insect->position.z += FX_MulFunc(scale, way.z);
    }
}
CLEAN_AS(func_ov068_0226fea4, InsectPath_Wander)

/* func_ov068_02270008: where on a flower of `line` it settles: for lines 1 and 4, 1/16 west, at
 * height 1.0 and 1/4 north of the tile's middle, else at height 0.5625 and 3/16 south (each
 * computed with FX_Div). */
void InsectPath_SpotOffset(int line, Vec3 *spot)
{
    if (line == 1 || line == 4) {
        spot->x += FX_Div((fx32) 0xfffff000, 0x10000);
        spot->y = FX_Div(0x10000, 0x10000);
        spot->z += FX_Div((fx32) 0xffffc000, 0x10000);
    } else {
        spot->y = FX_Div(0x9000, 0x10000);
        spot->z += FX_Div(0x3000, 0x10000);
    }
}
CLEAN_AS(func_ov068_02270008, InsectPath_SpotOffset)

/* func_ov068_02270070: a spot to settle on, when there is one: kind 0x33's point (moved 1.0
 * east and south, at height 0.6875), else a flower of the kind's mask (which must suit kinds 2
 * and 3), at its place on the flower by its line. Gives the turn towards it from the insect's
 * facing, at most INSECT_PATH_TURN_LIMIT either way, and its distance across the ground.
 * REQUIRES: there is a town map when a spot is found. */
int InsectPath_FindSpot(TownInsect *insect, s16 *turn, int *distance, Vec3 *spot)
{
    Vec3 *position = &insect->position;
    u8 kind = (u8) insect->kind;
    int found;
    if (kind == INSECT_PATH_KIND_33) {
        found = func_ov003_02224718(spot, position) != 0;
    } else {
        found = func_ov003_02224768(spot, position, func_ov003_0223482c((s8) kind)) != 0;
    }
    if (!found) {
        return 0;
    }
    int x = 0, z = 0;
    Position_Tile(&x, &z, (const Position *) (const void *) spot);
    int acre_x = x >> 4;
    int acre_z = z >> 4;
    u16 *code = AcreTile_ItemInAcre(data_021c80bc, (u32) acre_x, (u32) acre_z, x - acre_x * 16, z - acre_z * 16, 0);
    if (kind == 2 || kind == 3) {
        if (func_ov003_02235518((s8) kind, code) == 0) {
            return 0;
        }
    }
    if (kind != INSECT_PATH_KIND_33) {
        InsectPath_SpotOffset((s8) TownFamily_Line(code), spot);
    } else {
        spot->x += 0x1000;
        spot->y = FX_Div(0xb000, 0x10000);
        spot->z += 0x1000;
    }
    s16 to = (s16) (Vec_YawTo(position, spot) - insect->angle_y);
    if (to > INSECT_PATH_TURN_LIMIT) {
        to = INSECT_PATH_TURN_LIMIT;
    } else if (to < -INSECT_PATH_TURN_LIMIT) {
        to = -INSECT_PATH_TURN_LIMIT;
    }
    *turn = to;
    *distance = Vec_DistanceXZ(spot, position);
    return 1;
}
CLEAN_AS(func_ov068_02270070, InsectPath_FindSpot)

/* func_ov068_022701b0: a frame of going to a spot (InsectPath_FindSpot); 0 when there is
 * none. Its wait (unk_244) is counted down first; until it ends it only keeps its height
 * (unk_220 from unk_228). Then, within 0.25 across and 0.125 up or down of the spot (FX_Div), it
 * settles (INSECT_PATH_SETTLED, a wait of 20 times 16-20 frames); kind 0x33 then marks its
 * box when unk_21c is 1, else takes action 0. Farther, when a random number below 100 is above
 * unk_252 less 20, it notes the spot (and where it started) when the spot changed, aims at the
 * spot's height within 3.0 of it, turns towards it, and moves towards it by at most 1/64 along
 * x and z. */
int InsectPath_GoToSpot(TownInsect *insect, s16 *heading)
{
    int waited = func_ov003_02234984(insect);
    Vec3 *position = &insect->position;
    s16 turn;
    int distance;
    Vec3 spot;
    if (InsectPath_FindSpot(insect, &turn, &distance, &spot) == 0) {
        insect->unk_220 = insect->unk_228;
        return 0;
    }
    if (waited == 0) {
        insect->unk_220 = insect->unk_228;
        return 1;
    }
    if (distance <= FX_Div(0x1000, 0x4000) && position->y <= spot.y + FX_Div(0x1000, 0x8000) &&
        position->y >= spot.y - FX_Div(0x1000, 0x8000)) {
        insect->action = INSECT_PATH_SETTLED;
        insect->unk_244 = (s16) (0x14 * (MainRandom_Below(5) + 0x10));
        insect->frames_left = 0;
        if (insect->kind == INSECT_PATH_KIND_33) {
            if (insect->unk_21c != 1) {
                insect->action = 0;
            } else {
                func_ov003_02230f88(insect);
            }
        }
        return 1;
    }
    int bar = insect->unk_252 - 0x14;
    if ((int) MainRandom_Below(100) > bar) {
        if (insect->target.x != spot.x || insect->target.z != spot.z) {
            insect->target = spot;
            insect->start = *position;
        }
        if (distance <= 0x3000) {
            insect->unk_220 = spot.y;
        } else {
            insect->unk_220 = insect->unk_228;
        }
        *heading = (s16) (*heading + turn);
        VEC_Subtract(&spot, position, &spot);
        func_ov003_022321b8(&spot, &spot, 1);
        VEC_Add(position, &spot, position);
    }
    return 1;
}
CLEAN_AS(func_ov068_022701b0, InsectPath_GoToSpot)

/* func_ov068_02270328 (kinds 0x36 and 0x37): going for the player at `player`.
 *
 * Once unk_247 is set, *counter is 0 or above 0x1f and the model is opaque: when the player
 * was seen near (mode 1 or 3) and stands within 1.0, the player is asked to react
 * (FieldActor_PlayerRequestState6D); if the player does, it turns calm (action 0x13), unk_24c is
 * set and its animation restarts (frames 0, flags 2) from the frame it is at; else kind 0x36
 * goes on hopping while unk_23e runs (INSECT_PATH_HOP). That gives 1; out of reach it
 * misses (INSECT_PATH_MISSED) and gives 2. In the other modes a fleeing insect stops
 * (INSECT_PATH_STOPPED, *counter 0) and it gives 0.
 *
 * Otherwise it gives 0 after counting *counter down by one: when the player is near and
 * *counter is 0 it is set to 300 first; below 0x1f the model fades by 1 and once faded it
 * leaves; with unk_24b set it turns away from the player (0x666 a frame, its sound stopped)
 * and flees. */
int InsectPath_GoForPlayer(TownInsect *insect, int mode, const Vec3 *player, s16 *counter)
{
    Vec3 *position = &insect->position;
    int ready = insect->unk_247 != 0 && !(*counter != 0 && *counter <= 0x1f) && insect_opaque(insect);
    if (ready) {
        if (mode == 3 || mode == 1) {
            if (Vec_DistanceXZ(player, position) < 0x1000) {
                s16 *hop = &insect->unk_23e;
                if (FieldActor_PlayerRequestState6D(insect->kind == INSECT_PATH_KIND_FRAMES) != 0) {
                    insect->action = INSECT_PATH_CALM;
                    insect->unk_24c = 1;
                    FrameCtrl_Init(&insect->model.frames, 0, 2, 0x1000, frame_number(insect->model.frames.frame));
                } else {
                    int t = *hop;
                    if (t > 0 && insect->kind == INSECT_PATH_KIND_HOPS) {
                        position->y += hop_rise(t);
                        *hop = (s16) (*hop + 3);
                        if (position->y <= 0) {
                            *hop = 0;
                        }
                    }
                }
                return 1;
            }
            insect->action = INSECT_PATH_MISSED;
            return 2;
        }
        if (insect->action == INSECT_PATH_FLEE) {
            insect->action = INSECT_PATH_STOPPED;
            *counter = 0;
        }
        return 0;
    }
    if ((mode == 1 || mode == 3) && *counter == 0) {
        *counter = 300;
    } else if (*counter < 0x1f) {
        if (func_ov003_02232598(insect, 1) != 0) {
            func_ov003_02230f60(insect);
        }
    } else if (insect->unk_24b != 0) {
        s16 angle = insect->angle_y;
        func_ov003_022353a4(insect, INSECT_PATH_SOUND_IDLE, 1);
        Approach_S16Wrapped(&angle, Vec_YawTo(player, position), 0x666);
        insect->angle_y = angle;
        insect->action = INSECT_PATH_FLEE;
    }
    *counter = (s16) (*counter - 1);
    return 0;
}
CLEAN_AS(func_ov068_02270328, InsectPath_GoForPlayer)

/* func_ov068_022704cc (kinds 0x36 and 0x37, while unk_247 is set): turning to the player at
 * `player`; always 1.
 *
 * While unk_23e is 0 (or always for kind 0x37) and the model is opaque: seen near (mode 1) it
 * counts unk_23e up, and on the first frame its active sound starts and it faces the player.
 * Its timer (0x232) counts down; once out, while the player is not seen (mode 0) it is set to
 * 60 frames and kind 0x37, early in a short animation, starts its active sound. With unk_24b
 * set it turns to the player (0xe38 a frame within 2.0, else 0x71c).
 *
 * Kind 0x37 then keeps its animation: frame 0xd of a 0xe-frame sequence goes back to frame 0xa;
 * before frame 4 of a sequence shorter than 0xb it plays frames 0-0xb once from 4; at frame 0xa
 * of a 0xb-frame sequence frames 0-0xe from 0xa. */
int InsectPath_TurnToPlayer(TownInsect *insect, int mode, const Vec3 *player)
{
    Vec3 *position = &insect->position;
    FrameCtrl *frames = &insect->model.frames;
    int timer = insect->timer;
    s16 angle = insect->angle_y;
    s16 *seen = &insect->unk_23e;
    if ((*seen == 0 || insect->kind == INSECT_PATH_KIND_FRAMES) && insect_opaque(insect)) {
        if (mode == 1) {
            if (*seen == 0) {
                func_ov003_022353a4(insect, INSECT_PATH_SOUND_ACTIVE, 0);
                angle = Vec_YawTo(position, player);
            }
            *seen = (s16) (*seen + 1);
        }
        if (timer > 0) {
            insect->timer = (s16) (timer - 1);
        } else if (mode == 0) {
            insect->timer = 0x3c;
            if (insect->kind == INSECT_PATH_KIND_FRAMES && frame_number(frames->frame) < 4 &&
                frame_number(frames->end) < 0xb) {
                func_ov003_022353a4(insect, INSECT_PATH_SOUND_ACTIVE, 0);
            }
        }
        if (insect->unk_24b != 0) {
            if (Vec_DistanceXZ(position, player) < 0x2000) {
                Approach_S16Wrapped(&angle, Vec_YawTo(position, player), 0xe38);
            } else {
                Approach_S16Wrapped(&angle, Vec_YawTo(position, player), 0x71c);
            }
            insect->angle_y = angle;
        }
    }
    if (insect->kind != INSECT_PATH_KIND_FRAMES) {
        return 1;
    }
    u16 end = frame_number(frames->end);
    if (end == 0xe && frame_number(frames->frame) == 0xd) {
        frames->frame = 0xa000;
        return 1;
    }
    u16 frame = frame_number(frames->frame);
    if (frame < 4 && end < 0xb) {
        FrameCtrl_Init(frames, 0xb, 1, 0x1000, 4);
    } else if (end == 0xb && frame == 0xa) {
        FrameCtrl_Init(frames, 0xe, 0, 0x1000, 0xa);
    }
    return 1;
}
CLEAN_AS(func_ov068_022704cc, InsectPath_TurnToPlayer)

/* func_ov068_02270680 (kinds 0x36 and 0x37): a frame of watching the player (when there is a
 * player). Its alarm (unk_254) drops by 3 (not below 0) while the point it watches
 * (func_ov003_02233e4c) is beyond its reach. Alarmed (unk_254 at least 0x14) or while its timer
 * runs, it turns to the player (InsectPath_TurnToPlayer) when unk_247 is set, else counts
 * the player as near; alarmed without unk_247, at its alarm limit (unk_255) or while *counter
 * runs, it goes for the player (InsectPath_GoForPlayer). Gives the last of their answers,
 * else 0. */
int InsectPath_WatchPlayer(TownInsect *insect, s16 *counter)
{
    int result = 0;
    u8 *player = (u8 *) SessionPlayers_ActorOf(INSECT_PATH_PLAYER);
    if (player == NULL) {
        return 0;
    }
    const Vec3 *player_position = (const Vec3 *) (const void *) (player + 0x5c);
    Vec3 point;
    s8 mode = (s8) func_ov003_02233e4c(insect, &point);
    s16 alarm = insect->unk_254;
    if (alarm > 0) {
        fx32 reach = insect->reach;
        if (Vec_DistanceXZ(&point, &insect->position) > reach) {
            alarm = (s16) (alarm - 3);
            insect->unk_254 = (u8) (alarm > 0 ? alarm : 0);
        }
    }
    if (alarm >= INSECT_PATH_ALARMED || insect->timer > 0) {
        if (insect->unk_247 != 0) {
            result = InsectPath_TurnToPlayer(insect, (u8) mode, player_position);
        } else {
            mode = 1;
        }
    }
    if ((alarm >= INSECT_PATH_ALARMED && insect->unk_247 == 0) || alarm >= insect->unk_255 || *counter > 0) {
        result = InsectPath_GoForPlayer(insect, (u8) mode, player_position, counter);
    }
    return result;
}
CLEAN_AS(func_ov068_02270680, InsectPath_WatchPlayer)

/* func_ov068_02270750 (kinds 0x36 and 0x37, actions 4, 5 and 7): it lands or keeps clear first
 * (func_ov003_02232414). Stopped (INSECT_PATH_STOPPED) with its sound stopped, once its
 * wait ends it turns calm (action 0x13) with a wait of 20 times 2-10 frames. Having missed
 * (INSECT_PATH_MISSED), kind 0x36 hops (while *hop runs, or on every tenth frame by a
 * chance of 24 in 100): it rises by the hop's frame (its first frame facing the player with its
 * active sound) and lands where its tile allows once below 0; others stop their sound. Kind
 * 0x37, or one whose hop ended, then turns calm unless `result` is 2. */
void InsectPath_CalmDown(TownInsect *insect, s16 *hop, int result)
{
    func_ov003_02232414(insect);
    if (insect->action == INSECT_PATH_STOPPED) {
        func_ov003_022353a4(insect, INSECT_PATH_SOUND_IDLE, 1);
        if (func_ov003_02234984(insect) != 0) {
            insect->action = INSECT_PATH_CALM;
            insect->unk_244 = (s16) (0x14 * (MainRandom_Below(9) + 2));
        }
    } else if (insect->action == INSECT_PATH_MISSED) {
        if (insect->kind == INSECT_PATH_KIND_HOPS &&
            (*hop > 0 || (insect->counter % 10 == 0 && (int) MainRandom_Below(100) > 75))) {
            insect->position.y += hop_rise(*hop);
            if (*hop == 0) {
                u8 *player = (u8 *) SessionPlayers_ActorOf(INSECT_PATH_PLAYER);
                if (player != NULL) {
                    insect->angle_y = Vec_YawTo(&insect->position, (const Vec3 *) (const void *) (player + 0x5c));
                    func_ov003_022353a4(insect, INSECT_PATH_SOUND_ACTIVE, 0);
                }
            }
            *hop = (s16) (*hop + 3);
            if (*hop > 3 && func_ov003_02235950(&insect->position) == 0 && insect->position.y <= 0) {
                *hop = 0;
            }
        } else {
            func_ov003_022353a4(insect, INSECT_PATH_SOUND_IDLE, 1);
        }
        if ((insect->kind == INSECT_PATH_KIND_FRAMES || *hop == 0) && result != 2) {
            insect->action = INSECT_PATH_CALM;
            *hop = 0;
        }
    }
}
CLEAN_AS(func_ov068_02270750, InsectPath_CalmDown)

/* func_ov068_02270890 (kinds 0xb and 0x3a, actions 3, 7 and 8).
 *
 * Circling (INSECT_PATH_CIRCLE): it turns towards the player (0x1554 a frame) and moves
 * 35 steps of 0x29 along its facing, flapping (InsectPath_Flap). Its frame count (0x242)
 * waits at 0 until the player takes state 0x78 (its active sound on; else its sound off), then
 * counts up, and past 0x42 it flies off (action 7).
 *
 * Otherwise it moves along its facing, 100 steps a frame when flying off (action 7, flapping,
 * growing by 0x266 a frame), else by its speed (unk_21c) over 5 (growing by 0x333), and fades
 * by 4; once faded it is calm again (action 0x13), out of view, at the origin and still, and
 * the player may drop items again (TileRequests_AllowItemDrop); its model's alpha is 0. */
void InsectPath_CircleOrLeave(TownInsect *insect)
{
    Vec3 *position = &insect->position;
    Vec3 *scale = &insect->scale;
    int action = insect->action;
    if (action == INSECT_PATH_CIRCLE) {
        u8 *player = (u8 *) SessionPlayers_ActorOf(INSECT_PATH_PLAYER);
        if (player != NULL) {
            int before = insect->angle_y;
            s16 angle = (s16) before;
            Approach_S16Wrapped(&angle, Vec_YawTo(position, (const Vec3 *) (const void *) (player + 0x5c)), 0x1554);
            insect->angle_y = angle;
            Vec3 way;
            func_ov003_0223597c(&way, angle);
            position->x += FX_MulFunc(0x23000, way.x);
            position->z += FX_MulFunc(0x23000, way.z);
            InsectPath_Flap(scale, &insect->model, before - angle);
        }
        s16 frames = insect->frames_left;
        if (frames == 0) {
            if (FieldActor_PlayerRequestState78() != 0) {
                func_ov003_022353a4(insect, INSECT_PATH_SOUND_ACTIVE, 0);
                insect->frames_left = (s16) (insect->frames_left + 1);
            } else {
                func_ov003_022353a4(insect, INSECT_PATH_SOUND_IDLE, 1);
            }
            return;
        }
        insect->frames_left = (s16) (frames + 1);
        if (insect->frames_left > 0x42) {
            insect->action = INSECT_PATH_FLEE;
            insect->frames_left = 0;
        }
        return;
    }
    Vec3 way;
    func_ov003_0223597c(&way, insect->angle_y);
    if (action == INSECT_PATH_FLEE) {
        position->x += FX_MulFunc(way.x, 0x64000);
        position->z += FX_MulFunc(way.z, 0x64000);
        scale->x += 0x266;
        scale->y += 0x266;
        scale->z += 0x266;
        InsectPath_Flap(scale, &insect->model, 0);
    } else {
        position->x += FX_Div(FX_MulFunc(way.x, insect->unk_21c << 12), 0x5000);
        position->z += FX_Div(FX_MulFunc(way.z, insect->unk_21c << 12), 0x5000);
        scale->x += 0x333;
        scale->y += 0x333;
        scale->z += 0x333;
    }
    if (func_ov003_02232598(insect, 4) != 0) {
        insect->action = INSECT_PATH_CALM;
        insect->in_view = 0;
        position->x = 0;
        position->y = 0;
        position->z = 0;
        insect->unk_21c = 0;
        TileRequests_AllowItemDrop();
        NNS_G3dMdlSetMdlAlpha(insect_model(insect), 0, 0);
    }
}
CLEAN_AS(func_ov068_02270890, InsectPath_CircleOrLeave)

/* func_ov068_02270a64: its wings by how far it turned this frame: a turn of more than 0x38e
 * squeezes its scale (func_ov068_02270d24) and restarts the animation from the frame it is at,
 * with frames 0 and flags 3 when it turned left (a positive turn), else frames 0x5a and flags 1;
 * a smaller turn stretches it and plays frames 0x2e with flags 3 past frame 0x2d, else 1. */
void InsectPath_Flap(Vec3 *scale, TownInsectModel *model, int turned)
{
    FrameCtrl *frames = &model->frames;
    s16 frame = (s16) frame_number(frames->frame);
    int size = turned < 0 ? -turned : turned;
    if (size > INSECT_PATH_TURN_LIMIT) {
        func_ov068_02270d24(scale, 0);
        if (turned > 0) {
            FrameCtrl_Init(frames, 0, 3, 0x4000, (u16) frame);
        } else {
            FrameCtrl_Init(frames, 0x5a, 1, 0x4000, (u16) frame);
        }
    } else {
        func_ov068_02270d24(scale, 1);
        if (frame > 0x2d) {
            FrameCtrl_Init(frames, 0x2e, 3, 0x4000, (u16) frame);
        } else {
            FrameCtrl_Init(frames, 0x2e, 1, 0x4000, (u16) frame);
        }
    }
}
CLEAN_AS(func_ov068_02270a64, InsectPath_Flap)

/* func_ov068_02270b00 (kinds 0xb and 0x3a, action 0): chasing the player.
 *
 * While its timer (0x232) runs it counts down; once out, during a session it swings round by
 * 0x1554, moves 35 steps along its facing, flaps and sets unk_256 to 9, and that is all.
 *
 * Otherwise (with a player) within 1.0 of the player it starts circling
 * (INSECT_PATH_CIRCLE). Farther, it turns towards the player: 0xe38 a frame while unk_256
 * counts down, else by its speed (unk_21c plus unk_257): 0x93e below 0xfa, 0x7d2 below 0x104,
 * else 0x666. A turn still more than 15 degrees off slows it by 2 (above 0xb4), else it speeds
 * up by 7 (below 0x122), the speed being stored back without unk_257 taken off. It moves its
 * speed over 3.5 along its facing (over 5 within 14.0 of the player), and flaps by five times
 * its turn. */
void InsectPath_Chase(TownInsect *insect)
{
    u8 *player = (u8 *) SessionPlayers_ActorOf(INSECT_PATH_PLAYER);
    Vec3 *position = &insect->position;
    int before = insect->angle_y;
    s16 angle = (s16) before;
    s16 timer = insect->timer;
    if (timer > 0) {
        insect->timer = (s16) (timer - 1);
    } else if (func_02070070() != 0) {
        angle = (s16) (angle + 0x1554);
        insect->angle_y = angle;
        Vec3 way;
        func_ov003_0223597c(&way, angle);
        position->x += FX_MulFunc(0x23000, way.x);
        position->z += FX_MulFunc(0x23000, way.z);
        InsectPath_Flap(&insect->scale, &insect->model, before - angle);
        insect->unk_256 = 9;
        return;
    }
    if (player == NULL) {
        return;
    }
    const Vec3 *player_position = (const Vec3 *) (const void *) (player + 0x5c);
    int towards = Vec_YawTo(position, player_position);
    int speed = insect->unk_257 + insect->unk_21c;
    fx32 distance = Vec_DistanceXZ(position, player_position);
    if (distance < 0x1000) {
        insect->action = INSECT_PATH_CIRCLE;
        insect->frames_left = 0;
        return;
    }
    if (insect->unk_256 != 0) {
        insect->unk_256--;
        Approach_S16Wrapped(&angle, towards, 0xe38);
    } else if (speed < 0xfa) {
        Approach_S16Wrapped(&angle, towards, 0x93e);
    } else if (speed < 0x104) {
        Approach_S16Wrapped(&angle, towards, 0x7d2);
    } else {
        Approach_S16Wrapped(&angle, towards, 0x666);
    }
    int degrees = (towards - angle) / 182;
    if (degrees < 0) {
        degrees = -degrees;
    }
    if ((u8) degrees > 15 && speed > 0xb4) {
        speed -= 2;
        insect->unk_21c = speed;
    } else if (speed < 0x122) {
        speed += 7;
        insect->unk_21c = speed;
    }
    insect->angle_y = angle;
    Vec3 way;
    func_ov003_0223597c(&way, angle);
    fx32 divisor = distance > 0xe000 ? 0x3800 : 0x5000;
    position->x += FX_Div(FX_MulFunc(speed << 12, way.x), divisor);
    position->z += FX_Div(FX_MulFunc(speed << 12, way.z), divisor);
    InsectPath_Flap(&insect->scale, &insect->model, (before - angle) * 5);
}
CLEAN_AS(func_ov068_02270b00, InsectPath_Chase)
