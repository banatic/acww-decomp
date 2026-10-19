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
#include "main/overlay_groups.h"
#include "main/session_players.h"
#include "main/tile_requests.h"
#include "main/town_family.h"
#include "ov003/field_actor.h"
#include "ov003/town_insect_moves.h"
#include "ov003/walk_target.h"

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
/* Overlay 3's helpers of the insects. */

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
    TownInsectMove_StepAlong(&way, *heading);
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
        found = WalkTarget_DaySpot(spot, position) != 0;
    } else {
        found = WalkTarget_NearFamily(spot, position, TownInsectMove_TestFlags((s8) kind)) != 0;
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
        if (TownInsectMove_SuitsCode((s8) kind, code) == 0) {
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
    int waited = TownInsectMove_WaitOver(insect);
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
                TownInsectMove_SetBox(insect);
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
        TownInsectMove_ClampXZ(&spot, &spot, 1);
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
        if (TownInsectMove_FadeStep(insect, 1) != 0) {
            TownInsectMove_Leave(insect);
        }
    } else if (insect->unk_24b != 0) {
        s16 angle = insect->angle_y;
        TownInsectMove_PlaySound(insect, INSECT_PATH_SOUND_IDLE, 1);
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
                TownInsectMove_PlaySound(insect, INSECT_PATH_SOUND_ACTIVE, 0);
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
                TownInsectMove_PlaySound(insect, INSECT_PATH_SOUND_ACTIVE, 0);
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
    s8 mode = (s8) TownInsectMove_SensePlayers(insect, &point);
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
    TownInsectMove_Walk(insect);
    if (insect->action == INSECT_PATH_STOPPED) {
        TownInsectMove_PlaySound(insect, INSECT_PATH_SOUND_IDLE, 1);
        if (TownInsectMove_WaitOver(insect) != 0) {
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
                    TownInsectMove_PlaySound(insect, INSECT_PATH_SOUND_ACTIVE, 0);
                }
            }
            *hop = (s16) (*hop + 3);
            if (*hop > 3 && TownInsectMove_OnGroupTile(&insect->position) == 0 && insect->position.y <= 0) {
                *hop = 0;
            }
        } else {
            TownInsectMove_PlaySound(insect, INSECT_PATH_SOUND_IDLE, 1);
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
            TownInsectMove_StepAlong(&way, angle);
            position->x += FX_MulFunc(0x23000, way.x);
            position->z += FX_MulFunc(0x23000, way.z);
            InsectPath_Flap(scale, &insect->model, before - angle);
        }
        s16 frames = insect->frames_left;
        if (frames == 0) {
            if (FieldActor_PlayerRequestState78() != 0) {
                TownInsectMove_PlaySound(insect, INSECT_PATH_SOUND_ACTIVE, 0);
                insect->frames_left = (s16) (insect->frames_left + 1);
            } else {
                TownInsectMove_PlaySound(insect, INSECT_PATH_SOUND_IDLE, 1);
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
    TownInsectMove_StepAlong(&way, insect->angle_y);
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
    if (TownInsectMove_FadeStep(insect, 4) != 0) {
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
        InsectPath_StretchScale(scale, 0);
        if (turned > 0) {
            FrameCtrl_Init(frames, 0, 3, 0x4000, (u16) frame);
        } else {
            FrameCtrl_Init(frames, 0x5a, 1, 0x4000, (u16) frame);
        }
    } else {
        InsectPath_StretchScale(scale, 1);
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
    } else if (OverlayGroups_HasOwner() != 0) {
        angle = (s16) (angle + 0x1554);
        insect->angle_y = angle;
        Vec3 way;
        TownInsectMove_StepAlong(&way, angle);
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
    TownInsectMove_StepAlong(&way, angle);
    fx32 divisor = distance > 0xe000 ? 0x3800 : 0x5000;
    position->x += FX_Div(FX_MulFunc(speed << 12, way.x), divisor);
    position->z += FX_Div(FX_MulFunc(speed << 12, way.z), divisor);
    InsectPath_Flap(&insect->scale, &insect->model, (before - angle) * 5);
}
CLEAN_AS(func_ov068_02270b00, InsectPath_Chase)

/* ---- The behaviours of more kinds (insect_paths.h) */

#include "autoload_2/fx_math.h"
#include "main/actor.h"
#include "main/animated_model.h"
#include "main/building_shapes.h"
#include "main/effect_system.h"
#include "main/map_code.h"
#include "main/music_queue.h"
#include "main/player_actor_ops.h"
#include "main/unit_type_info.h"
#include "ov003/object_actors.h"
#include "ov003/snowman.h"
#include "ov009/scene_actor.h"

static_assert(offsetof(TownInsect, unk_1b0) == 0x1b0, "box");
static_assert(offsetof(TownInsect, unk_1e0) == 0x1e0, "perch");
static_assert(offsetof(TownInsect, scale) == 0x210, "scale");
static_assert(offsetof(TownInsect, reach) == 0x224, "reach");
static_assert(offsetof(TownInsect, timer) == 0x232, "timer");
static_assert(offsetof(TownInsect, angle_x) == 0x238, "angle_x");
static_assert(offsetof(TownInsect, unk_240) == 0x240, "unk_240");
static_assert(offsetof(TownInsect, frames_left) == 0x242, "frames_left");
static_assert(offsetof(TownInsect, unk_254) == 0x254, "byte 0x254");
static_assert(offsetof(Snowman, position) == 0x5c, "snowball position");
static_assert(offsetof(Actor, speed) == 0x98, "actor speed");

/* Actions of the kinds here (their meaning is the kind's). */
#define INSECT_PATH_CHASE 0          /* kinds 0xb and 0x3a: InsectPath_Chase */
#define INSECT_PATH_GLIDE 4          /* kind 0x19 */
#define INSECT_PATH_RESTING 5        /* kind 0x23: InsectPath_Rest */
#define INSECT_PATH_KIND_HOVERS 8    /* InsectPath_Hover, InsectPath_ToBuilding */
#define INSECT_PATH_SCALE_MIN 0x1000 /* InsectPath_StretchScale keeps its z within these */
#define INSECT_PATH_SCALE_MAX 0x2000
#define INSECT_PATH_STRETCH 0x52

/* What InsectPath_StartGrow and InsectPath_Grow ask of the music and the player. */
#define INSECT_PATH_MUSIC_GROW 25 /* the priority given a value of 0 as it starts growing */
#define INSECT_PATH_MUSIC_DROPPED 0x19
#define INSECT_PATH_MUSIC_CHASE_PRIORITY 0x1a
#define INSECT_PATH_MUSIC_CHASE 0x3f
#define INSECT_PATH_PLAYER_FLAG_CHASED 0x1a

/* The tiles a perch may be on: item 0x500a (building 0xa's tile) and items 0xe3-0xe7, with
 * the height the insect perches at on each. */
#define INSECT_PATH_PERCH_BUILDING 0x500a
#define INSECT_PATH_PERCH_FIRST 0xe3
#define INSECT_PATH_PERCH_LAST 0xe7
#define INSECT_PATH_PERCH_BUILDING_HEIGHT 0x27ae
#define INSECT_PATH_PERCH_ITEM_HEIGHT 0x191f
#define INSECT_PATH_PERCH_TILE_FIRST 0x10 /* the tiles searched: within the town's inner acres */
#define INSECT_PATH_PERCH_TILE_LAST 0x50

#define INSECT_PATH_BUILDINGS 0x22 /* the codes 0x5000-0x5021 */

/* Kind 0x23's ring around its snowball (InsectPath_CircleSnowball): the range of the balls'
 * sizes (a function-local static computed once; bit 0 of data_ov068_022786c4 says it was). */
extern fx32 data_ov068_022786c0;
extern u32 data_ov068_022786c4;

/* A shift left by 12 done on the bits, as the ARM does it. */
static int shift_12(int value)
{
    return (int) ((u32) value << 12);
}

static const Vec3 *actor_position(const u8 *actor)
{
    return (const Vec3 *) (const void *) (actor + 0x5c);
}

/* func_ov068_02270d24: the z of `scale` stretched by 0x52 (`stretch` nonzero) or squeezed, kept
 * within 1.0 and 2.0. */
void InsectPath_StretchScale(Vec3 *scale, int stretch)
{
    if (stretch == 0) {
        scale->z -= INSECT_PATH_STRETCH;
    } else {
        scale->z += INSECT_PATH_STRETCH;
    }
    if (scale->z < INSECT_PATH_SCALE_MIN) {
        scale->z = INSECT_PATH_SCALE_MIN;
    } else if (scale->z > INSECT_PATH_SCALE_MAX) {
        scale->z = INSECT_PATH_SCALE_MAX;
    }
}
CLEAN_AS(func_ov068_02270d24, InsectPath_StretchScale)

/* func_ov068_02270d54 (kinds 0xb and 0x3a, INSECT_PATH_GROWING): its scale's x eases towards
 * 1.0 and all three take it; its height eases towards 2.5. Once both are there it chases
 * (INSECT_PATH_CHASE) at scale 1.0, the music of priority 0x19 is dropped for music 0x3f, and
 * this console's player gets flag 0x1a. */
void InsectPath_Grow(TownInsect *insect)
{
    Vec3 *scale = &insect->scale;
    int size = scale->x;
    int grown = Approach_EaseS32MinMax(&size, 0x1000, 0x200, 0x1000, 0x19a) == 0;
    scale->x = size;
    scale->y = size;
    scale->z = size;
    if (Approach_EaseS32MinMax((int *) (void *) &insect->position.y, 0x2800, 0x199, 0x1000, 0x400) == 0 && grown) {
        insect->action = INSECT_PATH_CHASE;
        scale->x = 0x1000;
        scale->y = 0x1000;
        scale->z = 0x1000;
        Music_DropPriority(INSECT_PATH_MUSIC_DROPPED);
        Music_Add(INSECT_PATH_MUSIC_CHASE_PRIORITY, INSECT_PATH_MUSIC_CHASE, 0x7f, 0);
        PlayerActorOps_SetFlag(INSECT_PATH_PLAYER_FLAG_CHASED, INSECT_PATH_PLAYER);
    }
}
CLEAN_AS(func_ov068_02270d54, InsectPath_Grow)

/* func_ov068_02270df8 (kinds 0xb and 0x3a, INSECT_PATH_EMERGING): it faces the player (when
 * there is one), is made opaque and starts growing (INSECT_PATH_GROWING) from the smallest
 * scale, its timer at 40, its animation at frame 0x2d and its speed (unk_21c) 0xf0; the music
 * of priority 25 is given a value of 0. */
void InsectPath_StartGrow(TownInsect *insect)
{
    const u8 *player = (const u8 *) SessionPlayers_ActorOf(INSECT_PATH_PLAYER);
    if (player != NULL) {
        insect->angle_y = Vec_YawTo(&insect->position, actor_position(player));
    }
    NNS_G3dMdlSetMdlAlpha(insect_model(insect), 0, INSECT_PATH_OPAQUE);
    insect->action = INSECT_PATH_GROWING;
    insect->scale.x = 1;
    insect->scale.y = 1;
    insect->scale.z = 1;
    insect->timer = 0x28;
    insect->model.frames.frame = 0x2d000;
    insect->unk_21c = 0xf0;
    Music_AddValue(INSECT_PATH_MUSIC_GROW, 0, 0);
}
CLEAN_AS(func_ov068_02270df8, InsectPath_StartGrow)

/* func_ov068_02270e80 (kind 0x32, action 0): a frame of following the player. *phase (its frame
 * count, 0x242) steps by 0xaaa; its sound is off and it flaps (func_ov003_02234cc4).
 *
 * With a player: while it follows (unk_24a), its alarm (unk_254) counts up to 0xfe; from 60 on,
 * within 1/16 of the player when the player takes state 0x79 (PlayerActorOps_RequestState79),
 * it stops following and leaves (INSECT_PATH_LEAVE, *phase 0). Within 2.0 it starts following
 * within 1/4 (the alarm from 0) and turns towards the player by at most 0x555; farther, beyond
 * 1/2 a follow that has not reached 60 stops (the alarm back to 0), and it turns by at most
 * 0x1554. A turn beyond the limit is the limit by a chance of 84 in 100 (79 in 100 farther),
 * else none.
 *
 * Then it moves 8.0 steps of 0x29 along its facing, and its height follows *phase
 * (func_ov003_02234dac, a divisor of 18-25). */
void InsectPath_FollowPlayer(TownInsect *insect, s16 *phase)
{
    const u8 *player = (const u8 *) SessionPlayers_ActorOf(INSECT_PATH_PLAYER);
    Vec3 *position = &insect->position;
    s16 turn = 0;
    *phase = (s16) (*phase + 0xaaa);
    TownInsectMove_PlaySound(insect, INSECT_PATH_SOUND_IDLE, 1);
    TownInsectMove_ToggleFrame(insect);
    if (player != NULL) {
        const Vec3 *at = actor_position(player);
        fx32 distance = Vec_DistanceXZ(at, position);
        u32 draw = (u8) MainRandom_Below(100);
        s16 alarm = insect->unk_254;
        s16 limit;
        u32 bar;
        turn = (s16) (Vec_YawTo(position, at) - insect->angle_y);
        if (insect->unk_24a != 0) {
            if (alarm < 0xfe) {
                alarm++;
                insect->unk_254 = (u8) alarm;
            }
            if (alarm >= 0x3c && distance < FX_Div(0x1000, 0x10000) && PlayerActorOps_RequestState79() != 0) {
                insect->unk_24a = 0;
                *phase = 0;
                insect->action = INSECT_PATH_LEAVE;
            }
        }
        if (distance < 0x2000) {
            if (distance < FX_Div(0x1000, 0x4000) && insect->unk_24a == 0) {
                insect->unk_24a = 1;
                insect->unk_254 = 0;
            }
            limit = 0x555;
            bar = 0xf;
        } else {
            if (distance > FX_Div(0x1000, 0x2000) && insect->unk_24a != 0 && alarm < 0x3c) {
                insect->unk_24a = 0;
                insect->unk_254 = 0;
            }
            limit = (s16) FX_Div(0x555, 0x4000);
            bar = 0x14;
        }
        if (turn < (s16) -limit || turn > limit) {
            if (turn > 0 && draw > bar) {
                turn = limit;
            } else if (turn < 0 && draw > bar) {
                turn = (s16) -limit;
            } else {
                turn = 0;
            }
        }
    }
    s16 heading = (s16) (turn + insect->angle_y);
    insect->angle_y = heading;
    Vec3 way;
    TownInsectMove_StepAlong(&way, heading);
    position->x += FX_MulFunc(way.x, 0x8000);
    position->z += FX_MulFunc(way.z, 0x8000);
    int divisor = (int) MainRandom_Below(8) + 0x12;
    TownInsectMove_Bob(insect, *phase, 0x2800, shift_12(divisor));
}
CLEAN_AS(func_ov068_02270e80, InsectPath_FollowPlayer)

/* func_ov068_02271068 (kind 0x35, action 0x12): 1 once its timer (0x232) has run out. Before,
 * it sways: its facing swings by 546 a frame between about 15 degrees either side (unk_24c the
 * way it swings), and the timer counts down. QUIRK: the timer is counted in 16 bits, so -0x8000
 * counts on to 0x7fff. */
int InsectPath_Sway(TownInsect *insect)
{
    s16 angle = insect->angle_y;
    s16 left = (s16) (insect->timer - 1);
    if (left < 0) {
        return 1;
    }
    if (insect->unk_24c != 0) {
        if (angle > 2730) {
            insect->unk_24c = 0;
        }
    } else if (angle < -2730) {
        insect->unk_24c = 1;
    }
    if (insect->unk_24c != 0) {
        angle = (s16) (angle + 546);
    } else {
        angle = (s16) (angle - 546);
    }
    insect->angle_y = angle;
    insect->timer = left;
    return 0;
}
CLEAN_AS(func_ov068_02271068, InsectPath_Sway)

/* func_ov068_022710e4 (kind 0x35, action 0x13): when the player strikes its tile
 * (FieldActor_PlayerStrikesTile) and there is a player, it is knocked 1.25 along x away from
 * the player, swings either way (unk_24c) by an even chance, and gives 1; else 0. */
int InsectPath_KnockedAside(TownInsect *insect)
{
    Vec3 *position = &insect->position;
    if (FieldActor_PlayerStrikesTile(position) == 0) {
        return 0;
    }
    const u8 *player = (const u8 *) SessionPlayers_ActorOf(INSECT_PATH_PLAYER);
    if (player == NULL) {
        return 0;
    }
    if (position->x < actor_position(player)->x) {
        position->x -= FX_Div(0x14000, 0x10000);
    } else {
        position->x += FX_Div(0x14000, 0x10000);
    }
    insect->unk_24c = MainRandom_Below(100) > 50 ? 0 : 1;
    return 1;
}
CLEAN_AS(func_ov068_022710e4, InsectPath_KnockedAside)

/* Kind 0x23 comes to rest: action INSECT_PATH_RESTING, its animation at frame 0, and a wait of
 * 40-59 frames. */
static void insect_rest(TownInsect *insect)
{
    insect->action = INSECT_PATH_RESTING;
    AnimatedModel_SetFrame((AnimatedModel *) (void *) &insect->model, 0);
    insect->timer = (s16) (MainRandom_Below(0x14) + 0x28);
}

/* func_ov068_02271160 (kind 0x23, action 4): a frame of circling the loose snowball it was
 * placed by (unk_21c), which must be at rest; without one it rests.
 *
 * It keeps to a ring around the ball: the ball's size less 0.3 times how far its size is above
 * the smallest, over the whole range of sizes (computed once). Every 20th frame (by its
 * counter) the way round turns by a random 10 degrees either way (kept in its timer), on the
 * others by that amount again; it faces the ball 5 degrees off one way on every fourth frame
 * and the other way on the other even frames. The point 2.4 steps of 0x29 back from the ball
 * along the way round is where the ring lies: inside it, the insect moves one step outwards,
 * beyond the ring and 0.2 more three steps, else 2.4. Then the ball is placed there
 * (Snowman_Place); when it refuses, the insect rests. */
void InsectPath_CircleSnowball(TownInsect *insect)
{
    Snowman *ball = Snowman_IdleLooseBall(insect->unk_21c);
    Vec3 *position = &insect->position;
    if (ball == NULL) {
        insect_rest(insect);
        return;
    }
    const Vec3 *centre = &ball->position;
    fx32 ring = Snowman_Size(ball);
    s16 round = Vec_YawTo(centre, position);
    s16 facing = round;
    Vec3 point = *centre;
    if ((data_ov068_022786c4 & 1) == 0) {
        int largest = Snowman_MaxSize();
        data_ov068_022786c0 = largest - Snowman_MinSize();
        data_ov068_022786c4 |= 1;
    }
    ring -= FX_MulFunc(0x4cd, FX_Div(ring - Snowman_MinSize(), data_ov068_022786c0));
    if (insect->counter % 0x14 == 0) {
        s16 swing = (s16) (TownInsectMove_RandomTurn(6, 1) * 2);
        round = (s16) (round + swing);
        insect->timer = swing;
    } else {
        round = (s16) (round + insect->timer);
    }
    int counter = insect->counter;
    if (counter % 4 == 0) {
        facing = (s16) (facing + INSECT_PATH_TURN_LIMIT);
    } else if (counter % 2 == 0) {
        facing = (s16) (facing - INSECT_PATH_TURN_LIMIT);
    }
    insect->angle_y = facing;
    Vec3 way;
    TownInsectMove_StepAlong(&way, round);
    point.x -= FX_MulFunc(way.x, 0x2666);
    point.z -= FX_MulFunc(way.z, 0x2666);
    fx32 distance = Vec_DistanceXZ(&point, position);
    if (distance < ring) {
        position->x -= way.x;
        position->z -= way.z;
    } else if (distance > ring + 0x333) {
        position->x -= FX_MulFunc(way.x, 0x3000);
        position->z -= FX_MulFunc(way.z, 0x3000);
    } else {
        position->x -= FX_MulFunc(way.x, 0x2666);
        position->z -= FX_MulFunc(way.z, 0x2666);
    }
    if (Snowman_Place(ball, &point) == 0) {
        insect_rest(insect);
    }
}
CLEAN_AS(func_ov068_02271160, InsectPath_CircleSnowball)

/* func_ov068_02271358 (kind 0x23, INSECT_PATH_RESTING): while it stands on the ground
 * (func_ov003_02232414), its wait counts down, and once out it leaves (INSECT_PATH_LEAVE). */
void InsectPath_Rest(TownInsect *insect)
{
    s16 left = insect->timer;
    if (TownInsectMove_Walk(insect) == 0) {
        return;
    }
    if (left <= 0) {
        insect->action = INSECT_PATH_LEAVE;
        insect->frames_left = 0;
    } else {
        insect->timer = (s16) (left - 1);
    }
}
CLEAN_AS(func_ov068_02271358, InsectPath_Rest)

/* func_ov068_02271398 (kinds 0xa and 0x33, action 0): it flaps; alarmed out of reach
 * (func_ov003_02234d70 gives 2) it stops fleeing; its sound is off. Unless fleeing it goes to
 * its spot (InsectPath_GoToSpot), and kind 0xa without one leaves (INSECT_PATH_LEAVE). Then it
 * wanders (steps of 0xaaa, every 30th frame by a chance of 29 in 100, at its scale unk_257) and
 * its height follows its timer: for kind 0xa up to 1.125 with a divisor of 10-17 and the timer
 * stepping by 0xaaa, for kind 0x33 up to 0.1 with a divisor of 18-25 and steps of 0x1554. */
void InsectPath_Roam(TownInsect *insect)
{
    s16 heading = insect->angle_y;
    s16 phase = insect->timer;
    TownInsectMove_ToggleFrame(insect);
    if (TownInsectMove_Sense(insect) == 2) {
        insect->unk_24a = 0;
    }
    TownInsectMove_PlaySound(insect, INSECT_PATH_SOUND_IDLE, 1);
    if (insect->unk_24a == 0 && InsectPath_GoToSpot(insect, &heading) == 0 && insect->kind == INSECT_PATH_KIND_0A) {
        insect->frames_left = 0;
        insect->action = INSECT_PATH_LEAVE;
        return;
    }
    InsectPath_Wander(insect, &heading, 0xaaa, 0x1e, 0x46, insect->unk_257 << 12);
    if (insect->kind == INSECT_PATH_KIND_0A) {
        fx32 limit = FX_Div(0x12000, 0x10000);
        int divisor = (int) MainRandom_Below(8) + 0xa;
        TownInsectMove_Bob(insect, phase, limit, shift_12(divisor));
        insect->timer = (s16) (phase + 0xaaa);
    } else {
        int divisor = (int) MainRandom_Below(8) + 0x12;
        TownInsectMove_Bob(insect, phase, 0x19a, shift_12(divisor));
        insect->timer = (s16) (phase + 0x1554);
    }
}
CLEAN_AS(func_ov068_02271398, InsectPath_Roam)

/* func_ov068_02271494: the tile of a town building nearest to the insect's tile: of the 'M'
 * tiles of each building's shape (BuildingShapes_MTile) whose scene actor stands
 * (SceneActor_Member1F4IsSet gives 1), at the actor's tile. Gives its distance in tiles, or -1
 * for none; with one, *tile's x and z are its tile numbers.
 * QUIRK: the first tile found is taken only when it lies no farther north than the insect;
 * after that any nearer one.
 * BUG: the middle of the tile is worked out (AcreTile_TileCentre) and dropped: *tile gets the
 * tile's numbers, which InsectPath_ToBuilding then heads for as a point near the map's corner.
 * BUGFIX gives the middle instead. */
int InsectPath_NearestBuildingTile(TownInsect *insect, Vec3 *tile)
{
    int best = -1;
    int best_x = 0;
    int best_z = 0;
    int x = 0;
    int z = 0;
    Vec3 centre = {-1, 0, -1};
    Position_Tile(&x, &z, (const Position *) (const void *) &insect->position);
    Vec3 here = {x, 0, z};
    for (u32 i = 0; i < INSECT_PATH_BUILDINGS; i++) {
        u16 code = MapCode_Building(i);
        BuildingShapeEntry *shape = (BuildingShapeEntry *) BuildingShapes_Of(&code);
        if (shape == NULL) {
            continue;
        }
        u32 count = (u32) BuildingShapes_MCount(shape);
        int shape_x = 0;
        int shape_z = 0;
        if (count == 0) {
            continue;
        }
        SceneActor *building = ObjectActors_FindByCode(code);
        if (building == NULL) {
            continue;
        }
        for (u32 j = 0; j < count; j++) {
            if (BuildingShapes_MTile((unsigned int) (uintptr_t) shape, (unsigned int) (uintptr_t) &shape_x,
                                     (unsigned int) (uintptr_t) &shape_z, j) == 0) {
                continue;
            }
            if (SceneActor_Member1F4IsSet(building) != 1) {
                continue;
            }
            int tile_x = shape_x + SceneActor_TileX(building);
            int tile_z = shape_z + (int) SceneActor_TileZ(building);
            Vec3 there = {tile_x, 0, tile_z};
            int distance = Vec_DistanceXZ(&here, &there);
            if ((here.z <= tile_z && best < 0) || distance < best) {
                best = distance;
                best_x = tile_x;
                best_z = tile_z;
            }
        }
    }
    if (best >= 0) {
        AcreTile_TileCentre(&centre, (u32) best_x, (u32) best_z);
#ifdef BUGFIX
        tile->x = centre.x;
        tile->z = centre.z;
#else
        tile->x = best_x;
        tile->z = best_z;
#endif
    }
    return best;
}
CLEAN_AS(func_ov068_02271494, InsectPath_NearestBuildingTile)

/* func_ov068_022715a0 (kind 8, action 7 while not fleeing): on the nearest building's tile
 * (InsectPath_NearestBuildingTile gives 0) it turns to angle 0x8000 (angle_x 1) and hovers again
 * (action 0) with its animation at 1.0. Within 5 tiles it moves towards the tile, at most 2/64
 * along x and z (*step the move), and gives 1; farther or without one it leaves
 * (INSECT_PATH_LEAVE, *frames 0). Gives 0 but for a move. */
int InsectPath_ToBuilding(TownInsect *insect, s16 *frames, Vec3 *step)
{
    Vec3 tile = {0, 0, 0};
    Vec3 *position = &insect->position;
    int distance = InsectPath_NearestBuildingTile(insect, &tile);
    if (distance == 0) {
        insect->angle_y = (s16) -0x8000;
        insect->angle_x = 1;
        insect->action = 0;
        TownInsect_SetAnimSpeed(insect, 0x1000);
    } else if (distance > 0 && distance < 5) {
        Vec3 way;
        Vec_Subtract(&way, position, &tile);
        *step = way;
        step->y = 0;
        TownInsectMove_ClampXZ(step, step, 2);
        VEC_Subtract(position, step, position);
        return 1;
    } else {
        insect->action = INSECT_PATH_LEAVE;
        *frames = 0;
    }
    return 0;
}
CLEAN_AS(func_ov068_022715a0, InsectPath_ToBuilding)

/* func_ov068_02271644 (kind 8, action 0): it counts its alarm (func_ov003_02234d70). Fleeing
 * (unk_24a), with a player, kind 8 while angle_x is 1 turns 60 degrees from the player's side
 * (angle_x back to 0) and its animation runs at 1.1.
 *
 * Otherwise it hovers: on every tenth frame (by its counter) by a chance of 69 in 100 it turns
 * up and down the other way (unk_24c), else on every fifth frame across (unk_24b); it moves
 * 0x30 times unk_257 along x and y by the ways it had. A building's tile found
 * (InsectPath_NearestBuildingTile into unk_1e0) turns it back across to the x it had; below
 * 1.3125 or above 3.125 it turns up and down and keeps the height it had.
 * QUIRK: no tile found (-1) turns it back as a tile does; only a distance of 0 does not. */
void InsectPath_Hover(TownInsect *insect)
{
    int across = insect->unk_24b;
    u32 draw = (u8) MainRandom_Below(100);
    Vec3 *position = &insect->position;
    int up = insect->unk_24c;
    Vec3 before = *position;
    TownInsectMove_Sense(insect);
    if (insect->unk_24a != 0) {
        const u8 *player = (const u8 *) SessionPlayers_ActorOf(INSECT_PATH_PLAYER);
        if (player == NULL || insect->angle_x != 1 || insect->kind != INSECT_PATH_KIND_HOVERS) {
            return;
        }
        s16 turn = (s16) (position->x > actor_position(player)->x ? 0x2aaa : -0x2aaa);
        insect->angle_x = 0;
        insect->angle_y = turn;
        TownInsect_SetAnimSpeed(insect, 0x119a);
        return;
    }
    int counter = insect->counter;
    if (counter % 10 == 0 && draw > 0x1e) {
        insect->unk_24c = (u8) (up == 0);
    } else if (counter % 5 == 0 && draw > 0x1e) {
        insect->unk_24b = (u8) (across == 0);
    }
    if (across != 0) {
        position->x += insect->unk_257 * 0x30;
    } else {
        position->x -= insect->unk_257 * 0x30;
    }
    if (up != 0) {
        position->y += insect->unk_257 * 0x30;
    } else {
        position->y -= insect->unk_257 * 0x30;
    }
    if (InsectPath_NearestBuildingTile(insect, &insect->unk_1e0) != 0) {
        insect->unk_24b = (u8) (across == 0);
        position->x = before.x;
    }
    if (FX_Div(0x15000, 0x10000) > position->y || FX_Div(0x32000, 0x10000) < position->y) {
        insect->unk_24c = (u8) (up == 0);
        position->y = before.y;
    }
}
CLEAN_AS(func_ov068_02271644, InsectPath_Hover)

/* The height an insect perches at on what lies at `item`, 0 for nothing to perch on. */
static fx32 perch_height(const u16 *item)
{
    if (item == NULL) {
        return 0;
    }
    if (*item == INSECT_PATH_PERCH_BUILDING) {
        return INSECT_PATH_PERCH_BUILDING_HEIGHT;
    }
    if (*item >= INSECT_PATH_PERCH_FIRST && *item <= INSECT_PATH_PERCH_LAST) {
        return INSECT_PATH_PERCH_ITEM_HEIGHT;
    }
    return 0;
}

static u16 *item_on_tile(AcreMap *map, int x, int z)
{
    int acre_x = x >> 4;
    int acre_z = z >> 4;
    return AcreTile_ItemInAcre(map, (u32) acre_x, (u32) acre_z, x - acre_x * 16, z - acre_z * 16, 0);
}

/* func_ov068_022717e0 (kinds 0x15-0x17, action 4 with a perch): while the perch (unk_1e0) still
 * holds something to perch on and it is not fleeing, it flies at it (10.0 steps a frame,
 * facing it) until within 0.15, and comes down by 0.05 a frame until within 0.1 above the
 * perch's height; there it is calm again (action 0x13). Otherwise it forgets the perch (bits 4-7
 * of unk_21c cleared) and is calm. */
void InsectPath_GoToPerch(TownInsect *insect)
{
    Vec3 *position = &insect->position;
    Vec3 *perch = &insect->unk_1e0;
    AcreMap *map = data_021c80bc;
    int x = 0;
    int z = 0;
    fx32 distance = Vec_DistanceXZ(position, perch);
    u8 there = 0;
    Position_Tile(&x, &z, (const Position *) (const void *) perch);
    fx32 height = perch_height(item_on_tile(map, x, z));
    if (height > 0 && insect->unk_24a == 0) {
        if (distance > 0x266) {
            s16 angle = Vec_YawTo(position, perch);
            Vec3 way;
            TownInsectMove_StepAlong(&way, angle);
            insect->angle_y = angle;
            position->x += FX_MulFunc(way.x, 0xa000);
            position->z += FX_MulFunc(way.z, 0xa000);
        } else {
            there++;
        }
        if (height < position->y - 0x19a) {
            position->y -= 0xcd;
        } else {
            there++;
        }
        if (there >= 2) {
            insect->action = INSECT_PATH_CALM;
        }
    } else {
        insect->unk_21c &= 0xff0f;
        insect->action = INSECT_PATH_CALM;
    }
}
CLEAN_AS(func_ov068_022717e0, InsectPath_GoToPerch)

/* func_ov068_0227191c (kind 0x19, while gliding): something ahead (func_ov003_02235b54, 160
 * percent of a feeler, 20 degrees either side) turns it round within 60 degrees
 * (INSECT_PATH_TURNING to unk_240) and ends the glide (*frames 0). */
void InsectPath_TurnFromObstacle(TownInsect *insect, u16 *frames)
{
    if (TownInsectMove_FeelObstacles(insect, 0xa0, 0xe38) != 0) {
        int back = -0x8000;
        back += TownInsectMove_RandomTurn(0xc, 1);
        insect->unk_240 = (s16) back;
        insect->action = INSECT_PATH_TURNING;
        *frames = 0;
    }
}
CLEAN_AS(func_ov068_0227191c, InsectPath_TurnFromObstacle)

/* func_ov068_02271960 (kind 0x19, actions 3 and INSECT_PATH_TURNING): it takes a new heading:
 * turned by unk_240 after a turn, else by a random number of steps of 15 degrees (a new number
 * below 5 drawn for each step) either way by an even chance. Then it glides
 * (INSECT_PATH_GLIDE) for 8-15 frames, and effect set 0x1f starts 1/16 above it, turned as it
 * faced before. */
void InsectPath_PickHeading(TownInsect *insect, s16 *frames)
{
    s16 facing = insect->angle_y;
    s16 heading = 0;
    if (insect->action == INSECT_PATH_TURNING) {
        heading = (s16) (facing + insect->unk_240);
    } else {
        for (u8 i = 0; i < MainRandom_Below(5); i++) {
            heading = (s16) (heading + 0xaaa);
        }
        if (MainRandom_Below(100) > 0x32) {
            heading = (s16) -heading;
        }
        heading = (s16) (heading + facing);
    }
    insect->action = INSECT_PATH_GLIDE;
    insect->angle_y = heading;
    *frames = (s16) (MainRandom_Below(8) + 8);
    Vec3 at = insect->position;
    at.y += 0x100;
    EffectSystem_StartOneShotSetNumber(0x1f, &at, &facing, NULL);
}
CLEAN_AS(func_ov068_02271960, InsectPath_PickHeading)

/* func_ov068_02271a14 (kind 0x19, INSECT_PATH_GLIDE): it glides along its facing, *frames times
 * unk_257 steps of 0x29 (fewer each frame, *frames counting down). On ground of group 2
 * (UnitTypeInfo_GroupAt) within its box (the south-west corner at 0x1b0, the north-east one at
 * 0x1bc) it goes on until *frames is out, then is calm (action 0x13) with a wait of 3 times a
 * random number below 20. Elsewhere it goes back to where it was and turns round within 60
 * degrees (INSECT_PATH_TURNING, *frames 0). */
void InsectPath_Glide(TownInsect *insect, s16 *frames)
{
    Vec3 *position = &insect->position;
    Vec3 before = *position;
    const Vec3 *north_east = (const Vec3 *) (const void *) (insect->unk_1b0 + 0xc);
    const Vec3 *south_west = (const Vec3 *) (const void *) insect->unk_1b0;
    int x = 0;
    int z = 0;
    Vec3 way = {0, 0, 0x29};
    Vec_RotateY(&way, insect->angle_y);
    position->x += FX_MulFunc(shift_12(*frames * insect->unk_257), way.x);
    position->z += FX_MulFunc(shift_12(*frames * insect->unk_257), way.z);
    *frames = (s16) (*frames - 1);
    Position_Tile(&x, &z, (const Position *) (const void *) position);
    if (UnitTypeInfo_GroupAt(x, z) == 2 && position->x >= south_west->x && position->x <= north_east->x &&
        position->z <= south_west->z && position->z >= north_east->z) {
        if (*frames > 0) {
            return;
        }
        insect->action = INSECT_PATH_CALM;
        insect->timer = (s16) (3 * MainRandom_Below(0x14));
        return;
    }
    *position = before;
    insect->unk_240 = (s16) (TownInsectMove_RandomTurn(0xc, 1) + -0x8000);
    insect->action = INSECT_PATH_TURNING;
    *frames = 0;
}
CLEAN_AS(func_ov068_02271a14, InsectPath_Glide)

/* func_ov068_02271b30 (kinds 0x15-0x17): a perch among the tiles around the insect's (within
 * the tiles 0x10-0x50): the first, by columns west to east, holding something to perch on.
 * Found, it becomes the perch (unk_1e0, the tile's middle, 0.35 farther south on item 0x500a),
 * unk_21c counts one up in bits 4-7, unk_240 is the facing plus the way to it, and the insect
 * takes INSECT_PATH_PERCHING; gives 1, else 0.
 * QUIRK: the tile numbers are kept in bytes; a tile below -1 makes the last row or column 0xff
 * or more, and that loop never ends. */
int InsectPath_FindPerch(TownInsect *insect)
{
    Vec3 *perch = &insect->unk_1e0;
    Vec3 *position = &insect->position;
    int x = 0;
    int z = 0;
    AcreMap *map = data_021c80bc;
    Position_Tile(&x, &z, (const Position *) (const void *) position);
    int first_x = x - 1 < INSECT_PATH_PERCH_TILE_FIRST ? INSECT_PATH_PERCH_TILE_FIRST : x - 1;
    int first_z = z - 1 < INSECT_PATH_PERCH_TILE_FIRST ? INSECT_PATH_PERCH_TILE_FIRST : z - 1;
    int last_x = x + 1 > INSECT_PATH_PERCH_TILE_LAST ? INSECT_PATH_PERCH_TILE_LAST : x + 1;
    int last_z = z + 1 > INSECT_PATH_PERCH_TILE_LAST ? INSECT_PATH_PERCH_TILE_LAST : z + 1;
    u8 z_first = (u8) first_z;
    u8 x_last = (u8) last_x;
    u8 z_last = (u8) last_z;
    for (u8 i = (u8) first_x; i <= x_last; i++) {
        for (u8 j = z_first; j <= z_last; j++) {
            const u16 *item = item_on_tile(map, i, j);
            if (item == NULL) {
                continue;
            }
            int on_building;
            if (*item == INSECT_PATH_PERCH_BUILDING) {
                on_building = 1;
            } else if (*item >= INSECT_PATH_PERCH_FIRST && *item <= INSECT_PATH_PERCH_LAST) {
                on_building = 0;
            } else {
                continue;
            }
            AcreTile_TileCentre(perch, i, j);
            if (on_building) {
                perch->z += 0x59a;
            }
            insect->unk_21c += 0x10;
            s16 facing = insect->angle_y;
            insect->unk_240 = (s16) (Vec_YawTo(position, perch) + facing);
            insect->action = INSECT_PATH_PERCHING;
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov068_02271b30, InsectPath_FindPerch)

/* func_ov068_02271c58: the alarm (unk_254, at most 0xfe) one actor raises, from its `speed`
 * and its `distance`: within 2.0 by 25; beyond the insect's reach, or standing still, not at
 * all and *calm is 1 (else 0); otherwise by 1 at a speed up to 1000, 3 up to 1100, 5 up to
 * 1168, 8 at 1169, else 15. */
void InsectPath_Alarm(TownInsect *insect, u8 *calm, int speed, int distance)
{
    s16 alarm = insect->unk_254;
    fx32 reach = insect->reach;
    *calm = 0;
    if (distance < 0x2000) {
        alarm += 25;
    } else if (distance > reach || speed == 0) {
        *calm = 1;
    } else if (speed <= 1000) {
        alarm += 1;
    } else if (speed <= 1100) {
        alarm += 3;
    } else if (speed <= 1168) {
        alarm += 5;
    } else if (speed == 1169) {
        alarm += 8;
    } else {
        alarm += 15;
    }
    if (alarm > 254) {
        alarm = 254;
    }
    insect->unk_254 = (u8) alarm;
}
CLEAN_AS(func_ov068_02271c58, InsectPath_Alarm)

/* func_ov068_02271cec (outside a session): the alarm from this console's player and from each
 * actor of main's table (InsectPath_Alarm); *calm stays 1 only while none raised it.
 * *nearest is the player's position (when there is a player), then that of any actor
 * nearer. */
void InsectPath_SensePlayers(TownInsect *insect, u8 *calm, Vec3 *nearest)
{
    fx32 least = 0x0fffffff;
    u8 unmoved = 1;
    const Actor *player = (const Actor *) SessionPlayers_ActorOf(INSECT_PATH_PLAYER);
    Vec3 *position = &insect->position;
    if (player != NULL) {
        *nearest = player->position;
        least = Vec_DistanceXZ(nearest, position);
        InsectPath_Alarm(insect, &unmoved, player->speed, least);
        *calm = (*calm & unmoved) ? 1 : 0;
    }
    for (u8 i = 0; i < Actors_SlotCount(); i++) {
        const Actor *actor = (const Actor *) Actors_Slot(i);
        if (actor == NULL) {
            continue;
        }
        Vec3 at = actor->position;
        fx32 distance = Vec_DistanceXZ(&at, position);
        InsectPath_Alarm(insect, &unmoved, actor->speed, distance);
        *calm = (*calm & unmoved) ? 1 : 0;
        if (least > distance) {
            least = distance;
            *nearest = at;
        }
    }
}
CLEAN_AS(func_ov068_02271cec, InsectPath_SensePlayers)
