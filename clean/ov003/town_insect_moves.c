/* What the town's insects do each frame (town_insect_moves.h). */
#include "town_insect_moves.h"

#include "autoload_2/approach.h"
#include "clean.h"
#include "main/acre_map.h"
#include "main/acre_tile.h"
#include "main/actor.h"
#include "main/actor_table.h"
#include "main/animated_model.h"
#include "main/block_02042200.h"
#include "main/collision_query.h"
#include "main/effect_system.h"
#include "main/field_collision.h"
#include "main/frame_ctrl.h"
#include "main/link_global.h"
#include "main/main_random.h"
#include "main/model_pool.h"
#include "main/overlay_groups.h"
#include "main/session.h"
#include "main/session_players.h"
#include "main/sound_emitter.h"
#include "main/town_family.h"
#include "main/unit_type_info.h"
#include "ov003/field_actor.h"
#include "ov068/insect_paths.h"

static_assert(offsetof(TownInsect, unk_1b0) == 0x1b0, "TownInsect.unk_1b0");
static_assert(offsetof(TownInsect, timer) == 0x232, "TownInsect.timer");
static_assert(offsetof(TownInsect, unk_240) == 0x240, "TownInsect.unk_240");
static_assert(offsetof(TownInsect, unk_24e) == 0x24e, "TownInsect.unk_24e");
static_assert(offsetof(TownInsect, unk_259) == 0x259, "TownInsect.unk_259");

/* The player at this console, for SessionPlayers_ActorOf and the field actor. */
#define TOWN_INSECT_MOVES_THIS_PLAYER 4

/* The session (session.h). */
extern NetSession *data_020ccf94;
extern const s16 FX_SinCosTable_[];
/* The effects' setups handed to EffectSystem_StartSet. */
extern void *data_020e25d4;

extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *sum);
extern int NNS_G3dMdlGetMdlAlpha(void *model, int material);
extern void NNS_G3dMdlSetMdlAlpha(void *model, int material, int alpha);

/* Whether this system has a slot in the session. */
static int town_insect_moves_in_session(void)
{
    return Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot) != 0;
}

static void *town_insect_moves_model(TownInsect *insect)
{
    return (void *) (uintptr_t) ModelPoolFiles_Model(&insect->files);
}

/* The whole frame the model's animation is at, and its frame count, as 16 bits. */
static u16 town_insect_moves_frame(const TownInsect *insect)
{
    return (u16) ((u32) insect->model.frames.frame >> 12);
}

static u16 town_insect_moves_frame_count(const TownInsect *insect)
{
    return (u16) ((u32) insect->model.frames.end >> 12);
}

static void town_insect_moves_play(TownInsect *insect, u32 frames, u8 flags, u32 speed, u16 start)
{
    FrameCtrl_Init(&insect->model.frames, frames, flags, speed, start);
}

static void town_insect_moves_set_frame(TownInsect *insect, int frame)
{
    AnimatedModel_SetFrame((AnimatedModel *) &insect->model, frame);
}

/* The box a kind keeps to (TownInsectMove_SetBox): its low corner, then its high corner. */
static Vec3 *town_insect_moves_box(TownInsect *insect)
{
    return (Vec3 *) (void *) insect->unk_1b0;
}

/* A whole number in 20.12 fixed point. */
static fx32 town_insect_moves_fx(int whole)
{
    return (fx32) ((u32) whole << 12);
}

/* The ROM's signed division (_s32_div_f): a divisor of 0 gives the numerator back. */
static int town_insect_moves_div(int numerator, int divisor)
{
    if (divisor == 0) {
        return numerator;
    }
    if (divisor == -1) {
        return (int) (0u - (u32) numerator);
    }
    return numerator / divisor;
}

/* A point copied a word at a time, as the original does. */
static void town_insect_moves_copy(Vec3 *dst, const Vec3 *src)
{
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
}

/* Kinds 0xe and 0xf. */
static int town_insect_moves_kind_e_or_f(s8 kind)
{
    return (u8) (kind - 0xe) <= 1;
}

/* Kinds 0x36 and 0x37. */
static int town_insect_moves_kind_36_or_37(s8 kind)
{
    return (u8) (kind - 0x36) <= 1;
}

/* The item code of world tile (x, z) of the town map. */
static u16 *town_insect_moves_item_at(AcreMap *map, int x, int z)
{
    int acre_x = x >> 4;
    int acre_z = z >> 4;
    return AcreTile_ItemInAcre(map, (u32) acre_x, (u32) acre_z, x - acre_x * 16, z - acre_z * 16, 0);
}

/* A zigzag: the heading turned by `first` at frame 0, by `step` on the other multiples of 4,
 * back by `step` on the other even frames, and kept on the odd ones. */
static short town_insect_moves_zigzag(short angle, int frames, int step, fx32 first)
{
    if (frames == 0) {
        return (short) (angle + first);
    }
    if (frames % 4 == 0) {
        return (short) (angle + step);
    }
    if (frames % 2 == 0) {
        return (short) (angle - step);
    }
    return angle;
}

/* func_ov003_02230e18: flies up and away along its heading (10.0 steps let go, 15.0 otherwise;
 * none where something stands ahead), rising by 2n(n + 12) at frame n; kinds 0xe and 0xf hold
 * their wings out (frame 9 of an 11-frame animation), the others flap (TownInsectMove_ToggleFrame). It
 * plays its sound 1 on the first frame and leaves once faded. Kind 0x1a flees on the ground
 * instead (TownInsectMove_Flee), going from frame 0 to 1 and from 1 to 2. */
void TownInsectMove_FlyUpAway(TownInsect *insect, short *frames)
{
    if (insect->kind == 0x1a) {
        TownInsectMove_Flee(insect, frames);
        u16 frame = town_insect_moves_frame(insect);
        if (frame == 0) {
            town_insect_moves_set_frame(insect, 1);
        } else if (frame == 1) {
            town_insect_moves_set_frame(insect, 2);
        }
        return;
    }
    Vec3 *position = &insect->position;
    Vec3 step;
    if (TownInsectMove_FeelObstacles(insect, 0x50, 0xe38) == 0) {
        TownInsectMove_StepAlong(&step, insect->angle_y);
        fx32 speed = insect->action == TOWN_INSECT_ACTION_LET_GO ? 0xa000 : 0xf000;
        step.x = FX_MulFunc(step.x, speed);
        step.z = FX_MulFunc(step.z, speed);
    } else {
        step.x = 0;
        step.z = 0;
    }
    short n = *frames;
    step.y = n * (2 * (n + 12));
    if (town_insect_moves_kind_e_or_f(insect->kind)) {
        if (town_insect_moves_frame_count(insect) != 0xb) {
            town_insect_moves_play(insect, 0xb, 0, 0x1000, 9);
        } else if (town_insect_moves_frame(insect) < 9) {
            insect->model.frames.frame = 0x9000;
        }
    } else {
        TownInsectMove_ToggleFrame(insect);
    }
    if (*frames == 0) {
        TownInsectMove_PlaySound(insect, 1, 0);
    }
    if (TownInsectMove_FadeStep(insect, 1) != 0) {
        TownInsectMove_Leave(insect);
    }
    VEC_Add(position, &step, position);
}
CLEAN_AS(func_ov003_02230e18, TownInsectMove_FlyUpAway)

/* func_ov003_02230f60: the insect leaves (TOWN_INSECT_STATE_LEAVING), its model hidden. */
void TownInsectMove_Leave(TownInsect *insect)
{
    insect->state = TOWN_INSECT_STATE_LEAVING;
    NNS_G3dMdlSetMdlAlpha(town_insect_moves_model(insect), 0, 0);
}
CLEAN_AS(func_ov003_02230f60, TownInsectMove_Leave)

/* func_ov003_02230f88: the box the insect keeps to around where it is (low corner at 0x1b0,
 * high corner at 0x1bc), in sixteenths of 1.0: kind 0x33 6 either way in x, 4 in z, between
 * heights 10 and 12; kind 0x19 6.0 either way in x and z, its heights left as they are (and its
 * z corners the other way round); the others from 9 back to 9 ahead in x, 2 back to 5 ahead in
 * z, between heights 9 and 1.0. */
void TownInsectMove_SetBox(TownInsect *insect)
{
    const Vec3 *position = &insect->position;
    Vec3 *low = &town_insect_moves_box(insect)[0];
    Vec3 *high = &town_insect_moves_box(insect)[1];
    if (insect->kind == 0x33) {
        low->x = position->x - FX_Div(0x6000, 0x10000);
        low->y = FX_Div(0xa000, 0x10000);
        low->z = position->z - FX_Div(0x4000, 0x10000);
        high->x = position->x + FX_Div(0x6000, 0x10000);
        high->y = FX_Div(0xc000, 0x10000);
        high->z = position->z + FX_Div(0x4000, 0x10000);
    } else if (insect->kind == 0x19) {
        low->x = position->x - 0x6000;
        low->z = position->z + 0x6000;
        high->x = position->x + 0x6000;
        high->z = position->z - 0x6000;
    } else {
        low->x = position->x - FX_Div(0x9000, 0x10000);
        low->y = FX_Div(0x9000, 0x10000);
        low->z = position->z - FX_Div(0x2000, 0x10000);
        high->x = position->x + FX_Div(0x9000, 0x10000);
        high->y = 0x1000;
        high->z = position->z + FX_Div(0x5000, 0x10000);
    }
}
CLEAN_AS(func_ov003_02230f88, TownInsectMove_SetBox)

/* func_ov003_0223108c: moved 7/16 to one side or the other at random, 3/16 along z, and to a
 * height of 12/16. */
void TownInsectMove_ShiftAside(TownInsect *insect)
{
    Vec3 *position = &insect->position;
    if (MainRandom_Below(2) == 0) {
        position->x += FX_Div(0x7000, 0x10000);
    } else {
        position->x -= FX_Div(0x7000, 0x10000);
    }
    position->y = FX_Div(0xc000, 0x10000);
    position->z += FX_Div(0x3000, 0x10000);
}
CLEAN_AS(func_ov003_0223108c, TownInsectMove_ShiftAside)

/* func_ov003_02231104: a step along its heading at half its byte 0x257, kept in its box: a
 * step that leaves the box in x or z is taken back in that axis. One time in five it turns:
 * every 20th frame of its counter it changes which way, and turns by its word 0x21c or by 0xaaa
 * (kind 0x33 the other way round). But for kind 0x33 it sinks as far as it went along z.
 * QUIRK: its height is only put back when it is both below the box and above it, which never
 * holds for a box set by TownInsectMove_SetBox. */
void TownInsectMove_WanderInBox(TownInsect *insect)
{
    Vec3 *high = &town_insect_moves_box(insect)[1];
    Vec3 *low = &town_insect_moves_box(insect)[0];
    short angle = insect->angle_y;
    u8 turning = insect->unk_24b;
    Vec3 step = {0, 0, 0};
    Vec3 *position = &insect->position;
    Vec3 before = *position;
    if (MainRandom_Below(100) > 0x50) {
        if (insect->counter % 20 == 0) {
            turning = turning == 0 ? 1 : 0;
            insect->unk_24b = turning;
        }
        if (turning != 0) {
            angle = (short) (angle + (insect->kind == 0x33 ? (short) insect->unk_21c : 0xaaa));
        } else {
            angle = insect->kind == 0x33 ? (short) (angle + 0xaaa) : (short) (angle - (short) insect->unk_21c);
        }
    }
    TownInsectMove_StepAlong(&step, angle);
    insect->angle_y = angle;
    position->z += FX_Div(FX_MulFunc(town_insect_moves_fx(insect->unk_257), step.z), 0x20000);
    position->x += FX_Div(FX_MulFunc(town_insect_moves_fx(insect->unk_257), step.x), 0x20000);
    if (position->x < low->x || position->x > high->x) {
        position->x = before.x;
    }
    if (position->z < low->z || position->z > high->z) {
        position->z = before.z;
    }
    if (insect->kind != 0x33) {
        if (position->z != before.z) {
            position->y -= position->z - before.z;
        }
        if (position->y < low->y && position->y > high->y) {
            position->y = before.y;
        }
    }
}
CLEAN_AS(func_ov003_02231104, TownInsectMove_WanderInBox)

/* func_ov003_0223126c: watches this console's player. Off a tile of set B
 * (TownInsectMove_OnSetBTile) its alarm is at its height (TOWN_INSECT_BYTE254_NEAR); then the
 * alarm is counted (TownInsectMove_Sense). A player within 0.8 makes it fly off (action 9).
 * Kinds 0xe and 0xf: alarmed above 20, they close their wings (animation 9 from where it is) for
 * 60 frames; then within reach of the player they open them (animation 4), else close them
 * again (animation 0 from where it is). Kind 0x1a: alarmed above 20, it goes from frame 2 to 1
 * and from 1 to 0 and rests (action 0x13) for 60 frames; else it goes from 0 to 1 (once its byte
 * 0x252 has run down) and from 1 to 2. */
void TownInsectMove_WatchPlayer(TownInsect *insect, u16 *frames)
{
    Actor *player = SessionPlayers_ActorOf(TOWN_INSECT_MOVES_THIS_PLAYER);
    const Vec3 *position = &insect->position;
    if (TownInsectMove_OnSetBTile(position) == 0) {
        insect->unk_254 = TOWN_INSECT_BYTE254_NEAR;
    }
    insect->unk_24a = 0;
    TownInsectMove_Sense(insect);
    if (player == NULL) {
        return;
    }
    fx32 distance = Vec_DistanceXZ(&player->position, position);
    u8 alarm = insect->unk_254;
    if (distance <= 0xccd) {
        insect->action = 9;
        *frames = 0;
        return;
    }
    s8 kind = insect->kind;
    if (town_insect_moves_kind_e_or_f(kind)) {
        if (alarm > 0x14) {
            town_insect_moves_play(insect, 9, FRAME_CTRL_ONCE, 0x1000, town_insect_moves_frame(insect));
            insect->unk_252 = 0x3c;
        } else if (insect->unk_252 != 0) {
            insect->unk_252--;
        } else if (distance < insect->reach) {
            u16 frame = town_insect_moves_frame(insect);
            if (frame == 0) {
                town_insect_moves_play(insect, 4, FRAME_CTRL_ONCE, 0x1000, 0);
            } else if (frame > 4) {
                town_insect_moves_play(insect, 4, FRAME_CTRL_ONCE | FRAME_CTRL_REVERSE, 0x1000, frame);
            }
        } else {
            u16 frame = town_insect_moves_frame(insect);
            if (frame != 0) {
                town_insect_moves_play(insect, 0, FRAME_CTRL_ONCE | FRAME_CTRL_REVERSE, 0x1000, frame);
            }
        }
        return;
    }
    if (kind != 0x1a) {
        return;
    }
    if (alarm > 0x14) {
        u16 frame = town_insect_moves_frame(insect);
        if (frame == 2) {
            town_insect_moves_set_frame(insect, 1);
        } else if (frame == 1) {
            town_insect_moves_set_frame(insect, 0);
            insect->action = 0x13;
            insect->unk_252 = 0x3c;
        }
        return;
    }
    u16 frame = town_insect_moves_frame(insect);
    if (frame == 0 && insect->unk_252 == 0) {
        town_insect_moves_set_frame(insect, 1);
    } else if (frame == 1) {
        town_insect_moves_set_frame(insect, 2);
    } else if (insect->unk_252 != 0) {
        insect->unk_252--;
    }
}
CLEAN_AS(func_ov003_0223126c, TownInsectMove_WatchPlayer)

/* func_ov003_0223141c: whether `point` is on a town tile whose item code is of set B: 0-0x1a,
 * 0x1c, 0x1d or 0x8a-0xa5 (the codes TownInsect_CountTiles counts for places 1 and 2). */
int TownInsectMove_OnSetBTile(const Vec3 *point)
{
    AcreMap *map = (AcreMap *) (uintptr_t) AcreMap_Town();
    if (map == NULL) {
        return 0;
    }
    int x;
    int z;
    Position_Tile(&x, &z, (const Position *) point);
    u16 *code = town_insect_moves_item_at(map, x, z);
    if (code == NULL) {
        return 0;
    }
    u16 item = *code;
    return item <= 0x1a || item == 0x1c || item == 0x1d || (item >= 0x8a && item <= 0xa5);
}
CLEAN_AS(func_ov003_0223141c, TownInsectMove_OnSetBTile)

/* func_ov003_022314fc (kinds 0xe, 0xf, 0x1a and 0x20): wanders in its box (action 4) and rests
 * (action 0x13), watching the player in both, for a while each: kind 0x1a wanders up to 320
 * frames (from 160 on a chance in ten every 20th frame), the others up to 160 (from 80); kind
 * 0x1a rests, when at frame 2, up to 160 frames (from 40 on a chance in seven every 20th frame),
 * the others up to 56 (on a chance in seven every 5th frame). Kinds 0xe and 0xf with wings open
 * face the player and rest. Startled (action 7), it flies off (action 9) along its word 0x240;
 * let go, kind 0x1a hops and the others fly. */
void TownInsectMove_UpdateInArea(TownInsect *insect)
{
    short *frames = &insect->frames_left;
    if (town_insect_moves_kind_e_or_f(insect->kind) && town_insect_moves_frame(insect) != 0 &&
        (insect->action == 4 || insect->action == 0x13)) {
        Actor *player = SessionPlayers_ActorOf(TOWN_INSECT_MOVES_THIS_PLAYER);
        if (player != NULL) {
            insect->angle_y = Vec_YawTo(&insect->position, &player->position);
        }
        insect->action = 0x13;
    }
    switch (insect->action) {
        case 4:
            TownInsectMove_WanderInBox(insect);
            if (insect->kind == 0x1a) {
                if (*frames > 0x140 || (*frames % 20 == 0 && MainRandom_Below(100) > 0x5a && *frames > 0xa0)) {
                    insect->action = 0x13;
                    *frames = 0;
                }
            } else if (*frames > 0xa0 || (*frames % 20 == 0 && MainRandom_Below(100) > 0x5a && *frames > 0x50)) {
                insect->action = 0x13;
                *frames = 0;
            }
            TownInsectMove_WatchPlayer(insect, (u16 *) frames);
            break;
        case 7:
            insect->action = 9;
            insect->angle_y = insect->unk_240;
            *frames = 0;
            TownInsectMove_FlyUpAway(insect, frames);
            break;
        case 9:
            TownInsectMove_FlyUpAway(insect, frames);
            break;
        case TOWN_INSECT_ACTION_LET_GO:
            if (insect->kind == 0x1a) {
                TownInsectMove_Hop(insect, frames);
            } else {
                TownInsectMove_FlyUpAway(insect, frames);
            }
            break;
        case 0x13:
            if (insect->kind == 0x1a) {
                if (town_insect_moves_frame(insect) == 2 &&
                    (*frames > 0xa0 || (*frames % 20 == 0 && MainRandom_Below(100) > 0x55 && *frames >= 0x28))) {
                    *frames = 0;
                    insect->action = 4;
                }
            } else if (*frames > 0x38 || (*frames % 5 == 0 && MainRandom_Below(100) > 0x55 && *frames > 0)) {
                insect->action = 4;
                *frames = 0;
            }
            TownInsectMove_WatchPlayer(insect, (u16 *) frames);
            break;
        default:
            break;
    }
    *frames = (short) (*frames + 1);
}
CLEAN_AS(func_ov003_022314fc, TownInsectMove_UpdateInArea)

/* func_ov003_022316e0: a resting insect startled when its alarm reaches its byte 0x255 (and a
 * player was found, and it is not already startled): it turns away from the player's side
 * (0x6aac either way), tilts by 0xd55, plays its sound 1 and flies off (action 7, frame 1;
 * kind 9 also animation 9). Kind 0x14 short of it opens its wings (animation 4) for 60 frames
 * when half way there, else closes them (animation 0 from where it is). */
void TownInsectMove_CheckStartle(TownInsect *insect, short *frames)
{
    Vec3 nearest = {0, 0, 0};
    const Vec3 *position = &insect->position;
    u8 alarm = insect->unk_254;
    TownInsectMove_SensePlayers(insect, &nearest);
    if (nearest.x == 0 || insect->unk_24a != 0) {
        return;
    }
    int reached = insect->unk_255;
    if (alarm >= reached) {
        insect->angle_y = nearest.x > position->x ? -0x6aac : 0x6aac;
        insect->angle_x = 0xd55;
        insect->action = 7;
        insect->unk_24a = 1;
        town_insect_moves_set_frame(insect, 1);
        *frames = 0;
        TownInsectMove_PlaySound(insect, 1, 0);
        if (insect->kind == 9) {
            town_insect_moves_play(insect, 9, 0, 0x1000, 0);
        }
    } else if (insect->kind == 0x14) {
        if (alarm * 2 >= reached || insect->unk_252 != 0) {
            if (town_insect_moves_frame(insect) == 0) {
                town_insect_moves_play(insect, 4, FRAME_CTRL_ONCE, 0x1000, 0);
                insect->unk_252 = 0x3c;
            } else if (insect->unk_252 != 0) {
                insect->unk_252--;
            }
        } else {
            u16 frame = town_insect_moves_frame(insect);
            if (frame != 0 || town_insect_moves_frame_count(insect) != 0) {
                town_insect_moves_play(insect, 0, FRAME_CTRL_ONCE | FRAME_CTRL_REVERSE, 0x1000, frame);
            }
        }
    }
}
CLEAN_AS(func_ov003_022316e0, TownInsectMove_CheckStartle)

/* func_ov003_02231818 (kind 0x1f): fades as its alarm rises, by 31 times what is left to its
 * byte 0x255 over it, and leaves (startled) when nothing is left; near (TOWN_INSECT_BYTE254_NEAR)
 * it fades out (action 8). QUIRK: a byte 0x255 of 0 divides by 0, which the ROM's division
 * answers with the numerator. */
void TownInsectMove_FadeByAlarm(TownInsect *insect, short *frames)
{
    if (insect->unk_254 == TOWN_INSECT_BYTE254_NEAR) {
        insect->action = 8;
        return;
    }
    Vec3 nearest = {0, 0, 0};
    TownInsectMove_SensePlayers(insect, &nearest);
    if (nearest.x == 0) {
        return;
    }
    int alpha = (short) town_insect_moves_div(0x1f * (insect->unk_255 - insect->unk_254), insect->unk_255);
    if (alpha <= 0) {
        TownInsectMove_Leave(insect);
        insect->unk_24a = 1;
        *frames = 0;
    } else {
        if (alpha > 0x1f) {
            alpha = 0x1f;
        }
        NNS_G3dMdlSetMdlAlpha(town_insect_moves_model(insect), 0, alpha);
    }
}
CLEAN_AS(func_ov003_02231818, TownInsectMove_FadeByAlarm)

/* func_ov003_0223189c (action 7 of the leaning kinds): takes off, 1/8 to the side its heading
 * leans to, 1/16 along z (back, let go at a heading of exactly +-0x6001), and rising faster each
 * frame (by (frame / 4) squared over 16). Kinds but 0x10-0x13 play their sound 0;
 * kind 0x14 holds frame 24 of animation 26, the others flap. It leaves once faded. */
void TownInsectMove_TakeOff(TownInsect *insect, short *frames)
{
    Vec3 *position = &insect->position;
    s8 kind = insect->kind;
    if (kind != 0x10 && kind != 0x11 && kind != 0x12 && kind != 0x13) {
        TownInsectMove_PlaySound(insect, 0, 1);
    }
    if (insect->angle_y >= 0) {
        position->x += 0x200;
    } else {
        position->x -= 0x200;
    }
    if (TownInsectMove_FadeStep(insect, 1) != 0) {
        TownInsectMove_Leave(insect);
        return;
    }
    fx32 t = FX_Div(town_insect_moves_fx(*frames), 0x4000);
    position->y += FX_MulFunc(FX_MulFunc(0x100, t), t);
    *frames = (short) (*frames + 1);
    if (insect->action == TOWN_INSECT_ACTION_LET_GO && (insect->angle_y == 0x6001 || insect->angle_y == -0x6001)) {
        position->z -= 0x100;
    } else {
        position->z += 0x100;
    }
    if (kind == 0x14) {
        if (town_insect_moves_frame_count(insect) < 0x18) {
            town_insect_moves_play(insect, 0x1a, 0, 0x1000, 0x18);
        } else if (town_insect_moves_frame(insect) < 0x18) {
            insect->model.frames.frame = 0x18000;
        }
    } else {
        TownInsectMove_ToggleFrame(insect);
    }
}
CLEAN_AS(func_ov003_0223189c, TownInsectMove_TakeOff)

/* func_ov003_022319bc: flies off along its heading (16 steps a frame, none where something
 * stands ahead), rising faster each frame as in TownInsectMove_TakeOff; its sound 1 on the first
 * frame. Kind 0x14 holds frame 24 of animation 26, kind 9 restarts animation 9 while it plays
 * once, the others flap between frames 1 and 2. It leaves once faded. */
void TownInsectMove_FlyOff(TownInsect *insect, short *frames)
{
    Vec3 *position = &insect->position;
    u16 frame = town_insect_moves_frame(insect);
    s8 kind = insect->kind;
    fx32 t = FX_Div(town_insect_moves_fx(*frames), 0x4000);
    Vec3 step;
    TownInsectMove_StepAlong(&step, insect->angle_y);
    if (*frames == 0) {
        TownInsectMove_PlaySound(insect, 1, 0);
    }
    step.y = FX_MulFunc(FX_MulFunc(0x100, t), t);
    if (TownInsectMove_FeelObstacles(insect, 0x50, 0xe38) == 0) {
        step.x = (fx32) ((u32) step.x << 4);
        step.z = (fx32) ((u32) step.z << 4);
    }
    VEC_Add(position, &step, position);
    *frames = (short) (*frames + 1);
    if (kind == 0x14) {
        if (town_insect_moves_frame_count(insect) < 0x18) {
            town_insect_moves_play(insect, 0x1a, 0, 0x1000, 0x18);
        } else if (town_insect_moves_frame(insect) < 0x18) {
            insect->model.frames.frame = 0x18000;
        }
    } else if (insect->kind == 9) {
        if (insect->model.frames.flags != 0) {
            town_insect_moves_play(insect, 9, 0, 0x1000, 0);
        }
    } else {
        town_insect_moves_set_frame(insect, frame == 1 ? 2 : 1);
    }
    if (TownInsectMove_FadeStep(insect, 1) != 0) {
        TownInsectMove_Leave(insect);
    }
}
CLEAN_AS(func_ov003_022319bc, TownInsectMove_FlyOff)

/* func_ov003_02231af0 (action 3 of the leaning kinds): sways for 24 frames, its frame counter
 * going up or down (picked at random at 0): it turns by 0x16b a frame and tilts by 0xb6, one way
 * on frames 1-6 and 19-24 (and -7 to -18), the other way between; then rests (action 0x13). */
void TownInsectMove_Sway(TownInsect *insect, short *frames)
{
    short angle = insect->angle_y;
    short n = *frames;
    if (n == 0) {
        *frames = MainRandom_Below(100) < 0x32 ? 1 : -1;
    } else if ((n > 0 && n <= 6) || (n > 0x12 && n <= 0x18) || (n < -6 && n >= -0x12)) {
        if (n > 0) {
            *frames = (short) (*frames + 1);
            insect->angle_x = (short) (insect->angle_x + 0xb6);
        } else {
            *frames = (short) (*frames - 1);
            insect->angle_x = (short) (insect->angle_x - 0xb6);
        }
        angle = (short) (angle + 0x16b);
    } else if ((n > 6 && n <= 0x12) || (n < 0 && n >= -6) || (n < -0x12 && n >= -0x18)) {
        if (n > 0) {
            *frames = (short) (*frames + 1);
            insect->angle_x = (short) (insect->angle_x - 0xb6);
        } else {
            *frames = (short) (*frames - 1);
            insect->angle_x = (short) (insect->angle_x + 0xb6);
        }
        angle = (short) (angle - 0x16b);
    } else {
        *frames = 0;
        insect->action = 0x13;
    }
    insect->angle_y = angle;
}
CLEAN_AS(func_ov003_02231af0, TownInsectMove_Sway)

/* func_ov003_02231be4 (action 1 of the leaning kinds): for 8 frames it sinks by 1/128 a frame,
 * down to 1/16 below its word 0x228, wobbling (back on frames 2-5); then rests (action 0x13) on a
 * chance in three or starts again. */
void TownInsectMove_Descend(TownInsect *insect, short *frames)
{
    short angle = insect->angle_y;
    fx32 lowest = insect->unk_228 - 0x100;
    Vec3 *position = &insect->position;
    short t = *frames;
    if (t >= 8) {
        if (MainRandom_Below(100) > 0x46) {
            insect->action = 0x13;
        }
        *frames = 0;
    } else {
        if (t >= 2 && t < 6) {
            angle = (short) (angle - 0x16b);
            insect->angle_x = (short) (insect->angle_x - 0xb6);
        } else {
            angle = (short) (angle + 0x16b);
            insect->angle_x = (short) (insect->angle_x + 0xb6);
        }
        position->y -= 0x20;
        *frames = (short) (*frames + 1);
        if (position->y < lowest) {
            position->y = lowest;
        }
    }
    insect->angle_y = angle;
}
CLEAN_AS(func_ov003_02231be4, TownInsectMove_Descend)

/* func_ov003_02231c80 (action 2 of the leaning kinds): as TownInsectMove_Descend, rising up to
 * 1/4 above its word 0x228; then descends (action 1) on a chance in three or starts again. */
void TownInsectMove_Ascend(TownInsect *insect, short *frames)
{
    short angle = insect->angle_y;
    fx32 highest = insect->unk_228 + 0x400;
    Vec3 *position = &insect->position;
    short t = *frames;
    if (t >= 8) {
        if (MainRandom_Below(100) > 0x46) {
            insect->action = 1;
        }
        *frames = 0;
    } else {
        if (t >= 2 && t < 6) {
            angle = (short) (angle - 0x16b);
            insect->angle_x = (short) (insect->angle_x - 0xb6);
        } else {
            angle = (short) (angle + 0x16b);
            insect->angle_x = (short) (insect->angle_x + 0xb6);
        }
        position->y += 0x20;
        *frames = (short) (*frames + 1);
        if (position->y > highest) {
            position->y = highest;
        }
    }
    insect->angle_y = angle;
}
CLEAN_AS(func_ov003_02231c80, TownInsectMove_Ascend)

/* func_ov003_02231d1c (action 0x13 of the leaning kinds): rests. Kinds 0x10-0x14 with their
 * byte 0x246 set and an alarm under 10 play their sound 0 every 60 frames. Kind 9 holds its
 * wings (animation 9 at speed 0 from frame 9) and after 80 frames opens them (animation 14) on a
 * chance in thirteen, counting to 160. The others count frames on chances of three in ten and
 * every 20th sway (action 3) or rise (action 2). */
void TownInsectMove_Rest(TownInsect *insect, short *frames)
{
    s8 kind = insect->kind;
    if ((u8) (kind - 0x10) <= 4) {
        u8 calling = insect->unk_246;
        if (calling != 0 && insect->unk_254 < 0xa) {
            u8 wait = insect->unk_252;
            if (wait == 0) {
                TownInsectMove_PlaySound(insect, 0, 1);
            } else {
                insect->unk_252 = (u8) (wait - 1);
            }
        } else {
            insect->unk_252 = 0x3c;
        }
        return;
    }
    u8 chance = (u8) MainRandom_Below(100);
    if (insect->kind == 9) {
        u32 frame = town_insect_moves_frame(insect);
        if (frame == 0xd || frame < 9) {
            town_insect_moves_play(insect, 9, FRAME_CTRL_ONCE, 0, 9);
        }
        if (*frames > 0x50) {
            if (chance > 0x5c && frame < 0xa) {
                town_insect_moves_play(insect, 0xe, FRAME_CTRL_ONCE, 0x1000, 9);
            }
            if (*frames > 0xa0) {
                *frames = 0;
            }
        }
        *frames = (short) (*frames + 1);
    } else if (chance > 0x46) {
        *frames = (short) (*frames + 1);
        if (*frames % 20 == 0) {
            insect->action = chance < 0x55 ? 3 : 2;
            *frames = 0;
        }
    }
}
CLEAN_AS(func_ov003_02231d1c, TownInsectMove_Rest)

/* func_ov003_02231e24 (kinds 9, 0x10-0x14, 0x1f, 0x21, 0x22, 0x24, 0x26-0x2f, 0x34 and 0x38):
 * rests on something, sways, sinks and rises; startled it takes off (action 7) and flees
 * (action 9); let go, kind 0x1f hops and the others fly off; action 8 fades out by 2 a frame.
 * Unless fleeing, taking off or let go, kind 0x1f fades with its alarm and the others watch for
 * a startle. */
void TownInsectMove_UpdateLeaning(TownInsect *insect)
{
    short *frames = &insect->frames_left;
    u8 action = insect->action;
    if (action != TOWN_INSECT_ACTION_LET_GO && action != 9 && action != 7) {
        if (insect->kind == 0x1f) {
            TownInsectMove_FadeByAlarm(insect, frames);
        } else {
            TownInsectMove_CheckStartle(insect, frames);
            insect->unk_24a = 0;
        }
    }
    switch (action) {
        case 3:
            TownInsectMove_Sway(insect, frames);
            break;
        case 2:
            TownInsectMove_Ascend(insect, frames);
            break;
        case 1:
            TownInsectMove_Descend(insect, frames);
            break;
        case 9:
            TownInsectMove_Flee(insect, frames);
            *frames = (short) (*frames + 1);
            break;
        case TOWN_INSECT_ACTION_LET_GO:
            if (insect->kind != 0x1f) {
                TownInsectMove_FlyOff(insect, frames);
            } else {
                TownInsectMove_Hop(insect, frames);
            }
            break;
        case 7:
            insect->unk_24a = 1;
            TownInsectMove_TakeOff(insect, frames);
            break;
        case 8:
            if (TownInsectMove_FadeStep(insect, 2) != 0) {
                TownInsectMove_Leave(insect);
            }
            break;
        case 0x13:
            TownInsectMove_Rest(insect, frames);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov003_02231e24, TownInsectMove_UpdateLeaning)

/* func_ov003_02231f20 (kind 0x35): unless fleeing or let go, it fades out by 3 a frame and
 * leaves when the tile a little ahead of its place (its x kept in the word 0x21c, 1/4 further
 * along z) has an item code outside set A (0x26-0x2a, 0x2f-0x61 but 0x5c, 0x66-0x6d,
 * 0xc8-0xcf). Hidden (action 0x13) it waits for overlay 68 (func_ov068_022710e4) to show it
 * (action 1, animation 0x21); at frame 32 it waits 20 times 12-15 frames (action 0x12) for
 * func_ov068_02271068, then wiggles about z (action 2, animation 0x39 from frame 32) until frame
 * 56 hides it again at its place. Hidden and not shown, its animation is set to play once. */
void TownInsectMove_Update35(TownInsect *insect)
{
    short *frames = &insect->frames_left;
    NNS_G3dMdlGetMdlAlpha(town_insect_moves_model(insect), 0);
    u8 action = insect->action;
    if (action != TOWN_INSECT_ACTION_LET_GO && action != 9) {
        Vec3 ahead = {insect->unk_21c, 0, insect->position.z + 0x3e8};
        int x;
        int z;
        Position_Tile(&x, &z, (const Position *) &ahead);
        AcreMap *map = (AcreMap *) (uintptr_t) AcreMap_Town();
        if (map != NULL) {
            u16 *code = town_insect_moves_item_at(map, x, z);
            if (code != NULL) {
                u16 item = *code;
                int in_set_a = (item >= 0x26 && item <= 0x2a) || (item >= 0x2f && item <= 0x61 && item != 0x5c) ||
                               (item >= 0x66 && item <= 0x6d) || (item >= 0xc8 && item <= 0xcf);
                if (!in_set_a && TownInsectMove_FadeStep(insect, 3) != 0) {
                    TownInsectMove_Leave(insect);
                    return;
                }
            }
        }
    }
    switch (action) {
        case 2:
            if (insect->unk_24c != 0) {
                insect->unk_24c = 0;
                insect->angle_z = 0x6b;
            } else {
                insect->unk_24c = 1;
                insect->angle_z = -0x6b;
            }
            if (town_insect_moves_frame(insect) == 0x38) {
                insect->action = 0x13;
                insect->angle_z = 0;
                insect->position.x = insect->unk_21c;
                NNS_G3dMdlSetMdlAlpha(town_insect_moves_model(insect), 0, 0);
            }
            break;
        case 1:
            if (town_insect_moves_frame(insect) == 0x20) {
                insect->timer = (short) (20 * (MainRandom_Below(4) + 0xc));
                insect->action = 0x12;
                *frames = 0;
            }
            break;
        case TOWN_INSECT_ACTION_LET_GO:
            TownInsectMove_Hop(insect, frames);
            break;
        case 9:
            TownInsectMove_Flee(insect, frames);
            break;
        case 0x12:
            if (InsectPath_Sway(insect) != 0) {
                insect->angle_y = 0;
                insect->action = 2;
                town_insect_moves_play(insect, 0x39, FRAME_CTRL_ONCE, 0x1000, 0x20);
            }
            break;
        case 0x13:
            if (InsectPath_KnockedAside(insect) != 0) {
                insect->action = 1;
                insect->unk_254 = 0;
                town_insect_moves_play(insect, 0x21, FRAME_CTRL_ONCE, 0x1000, 0);
                NNS_G3dMdlSetMdlAlpha(town_insect_moves_model(insect), 0, 0x1f);
            } else {
                insect->model.frames.flags = FRAME_CTRL_ONCE;
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov003_02231f20, TownInsectMove_Update35)

/* func_ov003_022321b8: `src` without its height, x and z kept within `limit` sixty-fourths of
 * 1.0 either way. */
void TownInsectMove_ClampXZ(Vec3 *dst, const Vec3 *src, int limit)
{
    fx32 most = FX_Div(town_insect_moves_fx(limit), 0x40000);
    town_insect_moves_copy(dst, src);
    dst->y = 0;
    if (src->x >= 0) {
        if (src->x > most) {
            dst->x = most;
        }
    } else if (src->x < -most) {
        dst->x = -most;
    }
    if (src->z >= 0) {
        if (src->z > most) {
            dst->z = most;
        }
    } else if (src->z < -most) {
        dst->z = -most;
    }
}
CLEAN_AS(func_ov003_022321b8, TownInsectMove_ClampXZ)

/* func_ov003_02232210: a step of a walking insect in a session, towards its point. Holding the
 * scene (or at action 0x11) over water it sinks by 1/8 (1 returned), or, below the water's
 * limit, splashes and leaves (2 returned). Something ahead turns it away (a point 12.0 ahead
 * along its zigzag set, 0 returned). Else it moves towards its point (kind 0x1e faster) and
 * heads there, zigzagging as it goes; arrived and holding the scene it sets its point one step
 * on (if TownInsectMove_SetTarget could not) and 0 is returned. The byte 0x24b is set while it walks.
 * BUG: turned away on an even frame from 2 on, the original passes an angle it never set (a word
 * of its stack); this takes its heading. */
int TownInsectMove_WalkLinked(TownInsect *insect)
{
    Vec3 *position = &insect->position;
    short *frames = &insect->frames_left;
    int result = 0;
    CollisionGround ground;
    CollisionGround_Init(&ground, position, 0, 1);
    Vec3 *target = &insect->target;
    Vec3 step;
    TownInsectMove_StepAlong(&step, insect->angle_y);
    if ((LinkGlobal_HoldsScene() != 0 || insect->action == 0x11) && ground.unk_30 != 0) {
        if (CollisionGround_IsBelowLimit(&ground, position->y) != 0) {
            TownInsectMove_Leave(insect);
            TownInsectMove_Splash(insect);
            result = 2;
        } else {
            position->y -= 0x200;
            result = 1;
        }
    }
    if (TownInsectMove_TurnFromObstacle(insect) != 0) {
        insect->unk_24b = 0;
        int n = *frames;
        short angle = insect->angle_y;
        if (n < 2) {
            angle = (short) (angle - 0xaaa);
        } else if ((n + 1) % 4 == 0) {
            angle = (short) (angle + 0xaaa);
        } else if ((n + 1) % 2 == 0) {
            angle = (short) (angle - 0xaaa);
        }
        TownInsectMove_SetTarget(insect, angle, 0xc000);
        CollisionGround_Destroy(&ground);
        return 0;
    }
    int moving;
    if (insect->kind == 0x1e) {
        moving = Approach_PointXZ(position, target, 0x28, 0x1000, 0x19a);
    } else {
        moving = Approach_PointXZ(position, target, 8, 0x1000, 0x52);
    }
    if (moving == 0) {
        if (LinkGlobal_HoldsScene() != 0 && TownInsectMove_SetTarget(insect, insect->angle_y, 0xc000) == 0) {
            int index = ((u16) insect->angle_y >> 4) * 2;
            target->x += FX_SinCosTable_[index];
            target->z += FX_SinCosTable_[index + 1];
            CollisionGround_Destroy(&ground);
            return 0;
        }
    } else {
        insect->angle_y = Vec_YawTo(position, target);
    }
    short angle = insect->angle_y;
    fx32 first = *frames == 0 ? FX_Div(0x2000, 0x6000) : 0;
    insect->angle_y = town_insect_moves_zigzag(angle, *frames, 0xaaa, first);
    *frames = (short) (*frames + 1);
    insect->unk_24b = 1;
    CollisionGround_Destroy(&ground);
    return result;
}
CLEAN_AS(func_ov003_02232210, TownInsectMove_WalkLinked)

/* func_ov003_02232414: a step of a walking insect outside a session. It sinks by 1/8 a frame
 * (over water, below the water's limit, it splashes and leaves: 0 returned; else 1). Something
 * ahead turns it (TownInsectMove_TurnFromObstacle). Else it zigzags (kind 0x37 by 0x71c, the
 * others by 0xaaa) and moves on along its heading at twice its byte 0x257 (kinds 0x36 and 0x37
 * 4 times, at action 5 7 times, kind 0x36 12 times while its word 0x23e is above 0). The byte
 * 0x24b is set while it walks. */
int TownInsectMove_Walk(TownInsect *insect)
{
    Vec3 *position = &insect->position;
    short *frames = &insect->frames_left;
    int speed = 2;
    int result = 1;
    CollisionGround ground;
    CollisionGround_Init(&ground, position, 0, 1);
    s8 kind = insect->kind;
    Vec3 step;
    TownInsectMove_StepAlong(&step, insect->angle_y);
    if (ground.unk_30 != 0 && CollisionGround_IsBelowLimit(&ground, position->y) != 0) {
        TownInsectMove_Leave(insect);
        TownInsectMove_Splash(insect);
        result = 0;
    } else {
        position->y -= 0x200;
    }
    if (TownInsectMove_TurnFromObstacle(insect) != 0) {
        insect->unk_24b = 0;
        CollisionGround_Destroy(&ground);
        return 1;
    }
    if (town_insect_moves_kind_36_or_37(kind)) {
        if (insect->action == 5) {
            speed = insect->unk_23e > 0 && kind != 0x37 ? 0xc : 7;
        } else {
            speed = 4;
        }
    }
    int turn = insect->kind == 0x37 ? 0x71c : 0xaaa;
    int n = *frames;
    if (n == 0) {
        short angle = insect->angle_y;
        insect->angle_y = (short) (angle + FX_Div(turn, 0x2000));
    } else {
        insect->angle_y = town_insect_moves_zigzag(insect->angle_y, n, turn, 0);
    }
    position->x += FX_MulFunc(step.x, town_insect_moves_fx(speed * insect->unk_257));
    position->z += FX_MulFunc(step.z, town_insect_moves_fx(speed * insect->unk_257));
    *frames = (short) (*frames + 1);
    insect->unk_24b = 1;
    CollisionGround_Destroy(&ground);
    return result;
}
CLEAN_AS(func_ov003_02232414, TownInsectMove_Walk)

/* func_ov003_02232598: the model fades by `amount` while its alpha is above 7; 1 once it is not. */
int TownInsectMove_FadeStep(TownInsect *insect, int amount)
{
    int alpha = NNS_G3dMdlGetMdlAlpha(town_insect_moves_model(insect), 0);
    if (alpha > 7) {
        NNS_G3dMdlSetMdlAlpha(town_insect_moves_model(insect), 0, alpha - amount);
        return 0;
    }
    return 1;
}
CLEAN_AS(func_ov003_02232598, TownInsectMove_FadeStep)

/* func_ov003_022325d4 (kind 0x23): overlay 68 runs actions 4 and 5; fleeing or let go it flies
 * off; at rest it starts (action 4) at frame 3. */
void TownInsectMove_Update23(TownInsect *insect)
{
    switch (insect->action) {
        case 4:
            InsectPath_CircleSnowball(insect);
            break;
        case 5:
            InsectPath_Rest(insect);
            break;
        case 9:
        case TOWN_INSECT_ACTION_LET_GO:
            TownInsectMove_FlyOff(insect, &insect->frames_left);
            break;
        case 0x13:
            town_insect_moves_set_frame(insect, 3);
            insect->action = 4;
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov003_022325d4, TownInsectMove_Update23)

/* func_ov003_02232640 (kinds 0x36 and 0x37): its byte 0x247 follows FieldActor_PlayerHolds1376
 * (when func_02070070 says 0). On the ground (byte 0x24c clear), unless fleeing or let go, it
 * listens (func_ov068_02270680 with its word 0x236): out of action 5, a 1 stops it for the frame,
 * and kind 0x37 hearing nothing closes up (animation 3). Actions 4, 5 and 7 walk (overlay 68);
 * let go it hops; fleeing it plays its sound 0 and flees; turning (action 3) it turns by 0x666 a
 * frame to its word 0x240 and then walks. At rest (0x13): when its byte 0x24c is set, unless kind
 * 0x36 is still falling (its word 0x23e counting up by 3 while it is above the ground, gravity
 * -10n^2), it turns (action 3) half a turn and up to 40 degrees more; else once its word 0x244
 * has run out it turns up to 80 degrees for 20 times 0-2 frames. */
void TownInsectMove_Update36(TownInsect *insect)
{
    int heard = 0;
    u8 action = insect->action;
    Vec3 *position = &insect->position;
    s16 *fall = &insect->unk_23e;
    if (OverlayGroups_HasOwner() == 0) {
        insect->unk_247 = FieldActor_PlayerHolds1376() != 0 ? 1 : 0;
    }
    if (insect->unk_24c == 0 && action != TOWN_INSECT_ACTION_LET_GO && action != 9) {
        heard = InsectPath_WatchPlayer(insect, &insect->unk_236);
        if (insect->action != 5) {
            if (heard == 1) {
                return;
            }
            if (insect->kind == 0x37 && heard == 0) {
                u32 frame = town_insect_moves_frame(insect);
                if (frame > 3) {
                    town_insect_moves_play(insect, 3, FRAME_CTRL_ONCE | FRAME_CTRL_REVERSE, 0x1000, (u16) frame);
                } else if (frame == 3) {
                    town_insect_moves_play(insect, 3, 0, 0x1000, 0);
                }
            }
        }
    }
    switch (action) {
        case 4:
        case 5:
        case 7:
            InsectPath_CalmDown(insect, fall, heard);
            break;
        case TOWN_INSECT_ACTION_LET_GO:
            TownInsectMove_Hop(insect, &insect->frames_left);
            break;
        case 9:
            TownInsectMove_PlaySound(insect, 0, 1);
            TownInsectMove_Flee(insect, &insect->frames_left);
            break;
        case 3: {
            s16 angle = insect->angle_y;
            if (Approach_S16Wrapped(&angle, insect->unk_240, 0x666) != 0) {
                insect->action = 4;
            }
            insect->angle_y = angle;
            break;
        }
        case 0x13:
            if (insect->unk_24c != 0) {
                int n = *fall;
                if (n == 0 || insect->kind == 0x37) {
                    insect->action = 3;
                    insect->unk_244 = 0x64;
                    int heading = insect->angle_y;
                    int turn = TownInsectMove_RandomTurn(8, 1);
                    insect->unk_240 = (short) (turn + heading + 0x8000);
                    *fall = 0;
                } else if (position->y > 0 && insect->kind == 0x36) {
                    position->y += FX_MulFunc(FX_Div(0x1000, 0x12000), town_insect_moves_fx(n)) + -10 * (n * n);
                    *fall = (short) (*fall + 3);
                    if (position->y <= 0) {
                        *fall = 0;
                    }
                }
            } else if (TownInsectMove_WaitOver(insect) != 0) {
                insect->action = 3;
                insect->unk_244 = (short) (20 * MainRandom_Below(3));
                int heading = insect->angle_y;
                int turn = TownInsectMove_RandomTurn(0x10, 1);
                insect->unk_240 = (short) (turn + heading);
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov003_02232640, TownInsectMove_Update36)

/* func_ov003_02232874 (kind 0x30): hops. Between hops (action 6) it turns from what stands
 * ahead and waits out its word 0x244. Hopping (action 0xb) at 2.0 scale it moves on along its
 * heading at its byte 0x257 (not where something stands ahead) and follows an arc from its word
 * 0x228 (a higher arc from 1.0 up); a step onto ground over 1.0 higher (and at most 4.0) is taken
 * back. Landed, it waits 4 frames (action 6) with a new base height and a pace of its word 0x21c
 * give or take 0-2 (more on an even chance and when it stays above 0); landed in water below the
 * water's limit, it splashes and leaves. It leaves once faded. */
void TownInsectMove_Update30(TownInsect *insect)
{
    switch (insect->action) {
        case 6:
            TownInsectMove_TurnFromObstacle(insect);
            if (TownInsectMove_WaitOver(insect) != 0) {
                insect->action = TOWN_INSECT_ACTION_LET_GO;
            }
            break;
        case TOWN_INSECT_ACTION_LET_GO: {
            short *frames = &insect->frames_left;
            Vec3 *position = &insect->position;
            Vec3 before;
            town_insect_moves_copy(&before, position);
            fx32 base = insect->unk_228;
            CollisionGround ground;
            CollisionGround_Init(&ground, position, 0, 1);
            TownInsect_SetScale(insect, 0xc8);
            if (TownInsectMove_TurnFromObstacle(insect) == 0) {
                Vec3 step;
                TownInsectMove_StepAlong(&step, insect->angle_y);
                position->x += FX_MulFunc(town_insect_moves_fx(insect->unk_257), step.x);
                position->z += FX_MulFunc(town_insect_moves_fx(insect->unk_257), step.z);
            }
            fx32 t = town_insect_moves_fx(*frames);
            if (base > 0x1000) {
                position->y = base + FX_MulFunc(0x59a - FX_MulFunc(0xcd, t), t);
            } else {
                position->y = base + FX_MulFunc(0x99a - FX_MulFunc(0xcd, t), t);
            }
            fx32 floor;
            if (ground.unk_30 != 0) {
                floor = ground.limit;
            } else {
                floor = CollisionGround_GetHeight(&ground, 1);
                floor += CollisionQuery_FloorHeight(0);
                if (floor > 0x1000) {
                    if (floor > 0x4000) {
                        floor = CollisionQuery_FloorHeight(0);
                    } else {
                        position->x = before.x;
                        position->z = before.z;
                    }
                }
            }
            if (position->y < floor) {
                int change = (int) MainRandom_Below(3);
                *frames = 0;
                position->y = floor;
                if (CollisionGround_IsBelowLimit(&ground, position->y) != 0) {
                    TownInsectMove_Leave(insect);
                    TownInsectMove_Splash(insect);
                } else {
                    insect->action = 6;
                    insect->unk_244 = 4;
                    insect->unk_228 = floor;
                    if (MainRandom_Below(100) > 0x32 && insect->unk_21c - change > 0) {
                        insect->unk_257 = (u8) (insect->unk_21c - change);
                    } else {
                        insect->unk_257 = (u8) (change + insect->unk_21c);
                    }
                }
            } else {
                *frames = (short) (*frames + 1);
            }
            if (TownInsectMove_FadeStep(insect, 1) != 0) {
                TownInsectMove_Leave(insect);
            }
            CollisionGround_Destroy(&ground);
            break;
        }
        default:
            break;
    }
}
CLEAN_AS(func_ov003_02232874, TownInsectMove_Update30)

/* func_ov003_02232a44 (kind 8): overlay 68 runs action 0; fleeing or let go it flies up and
 * away (TownInsectMove_Escape at 1.8); startled (action 7) TownInsectMove_FlyBobbing; at rest it starts
 * (action 0). */
void TownInsectMove_Update08(TownInsect *insect)
{
    switch (insect->action) {
        case 0:
            InsectPath_Hover(insect);
            break;
        case 9:
        case TOWN_INSECT_ACTION_LET_GO:
            TownInsectMove_Escape(insect, 0x1ccd);
            break;
        case 7:
            TownInsectMove_FlyBobbing(insect);
            break;
        case 0x13:
            insect->unk_24a = 0;
            insect->action = 0;
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov003_02232a44, TownInsectMove_Update08)

/* func_ov003_02232aa0 (kind 0x31 hidden): counts down the frames a player stands on its tile
 * (FieldActor_PlayerFramesToActOnTile, the byte 0x24e: in a session the first of players 0-3
 * with some, else this console's player); when they run out it comes out (action 5, shown)
 * heading away from the nearest player, and 1 is returned. */
int TownInsectMove_AppearFromTile(TownInsect *insect, short *frames)
{
    s8 *count = (s8 *) &insect->unk_24e;
    const Vec3 *position = &insect->position;
    if (*count <= 0) {
        if (town_insect_moves_in_session()) {
            for (s8 player = 0; player < 4; player++) {
                *count = (s8) FieldActor_PlayerFramesToActOnTile(position, player);
                if (*count > 0) {
                    break;
                }
            }
        } else {
            *count = (s8) FieldActor_PlayerFramesToActOnTile(position, TOWN_INSECT_MOVES_THIS_PLAYER);
        }
    }
    if (*count > 0) {
        *count = (s8) (*count - 1);
        if (*count == 0) {
            Actor *nearest = TownInsectMove_NearestPlayer(position);
            if (nearest != NULL) {
                int angle = Vec_YawTo(position, &nearest->position);
                insect->action = 5;
                NNS_G3dMdlSetMdlAlpha(town_insect_moves_model(insect), 0, 0x1f);
                insect->angle_y = (short) (angle + 0x8000);
                *frames = 0;
                return 1;
            }
        }
    }
    return 0;
}
CLEAN_AS(func_ov003_02232aa0, TownInsectMove_AppearFromTile)

/* func_ov003_02232b68 (kind 0x31 walking): walks (in a session TownInsectMove_WalkLinked, which
 * stops it unless it returned 0; else TownInsectMove_Walk, which stops it when it returned 0).
 * Alarmed to its byte 0x255 (outside a session, or holding the scene, or at its point) it stops
 * (action 7, frame 0; holding the scene in a session its point becomes where it is). Else it
 * walks its timer down, kept up while a player stands on its tile, and once out fades away. */
void TownInsectMove_Walk31(TownInsect *insect)
{
    Vec3 *position = &insect->position;
    short timer = insect->timer;
    if (town_insect_moves_in_session()) {
        if (TownInsectMove_WalkLinked(insect) != 0) {
            return;
        }
    } else if (TownInsectMove_Walk(insect) == 0) {
        return;
    }
    Vec3 nearest = {0, 0, 0};
    TownInsectMove_SensePlayers(insect, &nearest);
    if (insect->unk_254 >= insect->unk_255 &&
        (!town_insect_moves_in_session() || LinkGlobal_HoldsScene() != 0 ||
         (insect->target.x == insect->position.x && insect->target.z == insect->position.z))) {
        insect->action = 7;
        town_insect_moves_set_frame(insect, 0);
        if (town_insect_moves_in_session() && LinkGlobal_HoldsScene() != 0) {
            town_insect_moves_copy(&insect->target, &insect->position);
        }
    } else if (timer <= 0) {
        if (TownInsectMove_FadeStep(insect, 1) != 0) {
            TownInsectMove_Leave(insect);
        }
    } else {
        if (TownInsectMove_CountStand(insect, position) != 0) {
            timer = 1;
        }
        insect->timer = (short) (timer - 1);
    }
}
CLEAN_AS(func_ov003_02232b68, TownInsectMove_Walk31)

/* func_ov003_02232c70 (kind 0x31 stopped, action 7): its timer runs down while a player is
 * found (kept up while one stands on its tile); once its alarm is under its byte 0x255 it walks
 * again (action 4, frame 1) away from the player (holding the scene in a session, with a point
 * 12.0 ahead). Out of time it fades away. */
void TownInsectMove_Wait31(TownInsect *insect)
{
    short timer = insect->timer;
    Vec3 *position = &insect->position;
    if (TownInsectMove_CountStand(insect, position) != 0) {
        timer = 1;
    }
    if (timer <= 0) {
        if (TownInsectMove_FadeStep(insect, 1) != 0) {
            TownInsectMove_Leave(insect);
        }
        return;
    }
    Vec3 nearest = {0, 0, 0};
    TownInsectMove_SensePlayers(insect, &nearest);
    if (nearest.x == 0) {
        return;
    }
    insect->timer = (short) (timer - 1);
    if (insect->unk_254 < insect->unk_255) {
        insect->action = 4;
        town_insect_moves_set_frame(insect, 1);
        insect->angle_y = (short) (Vec_YawTo(position, &nearest) + 0x8000);
        if (town_insect_moves_in_session() && LinkGlobal_HoldsScene() != 0) {
            TownInsectMove_SetTarget(insect, insect->angle_y, 0xc000);
        }
    }
}
CLEAN_AS(func_ov003_02232c70, TownInsectMove_Wait31)

/* func_ov003_02232d30 (kind 0x31): walks (actions 4 and 0x11), stops (7), comes out (5: hops),
 * flees, hops let go (at frame 0 from frame 1), and hidden (0x13) waits at frame 0 for a player
 * to stand by. */
void TownInsectMove_Update31(TownInsect *insect)
{
    short *frames = &insect->frames_left;
    switch (insect->action) {
        case 4:
        case 0x11:
            TownInsectMove_Walk31(insect);
            break;
        case TOWN_INSECT_ACTION_LET_GO:
            if (town_insect_moves_frame(insect) == 1) {
                town_insect_moves_set_frame(insect, 0);
            }
            TownInsectMove_Hop(insect, frames);
            break;
        case 5:
            TownInsectMove_Hop(insect, frames);
            break;
        case 9:
            TownInsectMove_Flee(insect, frames);
            break;
        case 7:
            TownInsectMove_Wait31(insect);
            break;
        case 0x13:
            TownInsectMove_AppearFromTile(insect, frames);
            if (town_insect_moves_frame(insect) != 0) {
                town_insect_moves_set_frame(insect, 0);
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov003_02232d30, TownInsectMove_Update31)

/* func_ov003_02232dd4: turns from what stands ahead (func_ov003_02235b54), its heading (kind
 * 0x35's about z) by 0xaaa when blocked on both sides (back the way it last turned, byte 0x252 1
 * or 10), else by 0x38e away from the blocked side, or on the way it last turned; 1 when
 * something stands ahead. With nothing ahead, a last turn of 1 or 2 becomes 10 or 20. */
int TownInsectMove_TurnFromObstacle(TownInsect *insect)
{
    int side = TownInsectMove_FeelObstacles(insect, 0x50, 0xe38);
    u8 last = insect->unk_252;
    if (side == 0) {
        if (last < 0xa) {
            last = (u8) (last * 10);
        }
        insect->unk_252 = last;
        return 0;
    }
    int about_z = insect->kind == 0x35;
    short heading = about_z ? insect->angle_z : insect->angle_y;
    if (side == 3) {
        if (last == 1 || last == 0xa) {
            heading = (short) (heading - 0xaaa);
        } else {
            heading = (short) (heading + 0xaaa);
        }
    } else if (side == 1 || last == 1) {
        heading = (short) (heading - 0x38e);
        last = 1;
    } else if (side == 2 || last == 2) {
        heading = (short) (heading + 0x38e);
        last = 2;
    }
    if (about_z) {
        insect->angle_z = heading;
    } else {
        insect->angle_y = heading;
    }
    insect->unk_252 = last;
    return 1;
}
CLEAN_AS(func_ov003_02232dd4, TownInsectMove_TurnFromObstacle)

/* func_ov003_02232e88 (kind 0x1e walking): walks as TownInsectMove_Walk31 does, its timer
 * running down. With 5 frames left, outside a session on a tile without unit byte 9, it starts
 * effect set 0x80 there and goes on; else it flees (action 9). Out of time it turns once more
 * along its zigzag and leaves. */
void TownInsectMove_Walk1E(TownInsect *insect, short *frames)
{
    short timer = insect->timer;
    if (town_insect_moves_in_session()) {
        if (TownInsectMove_WalkLinked(insect) != 0) {
            return;
        }
    } else if (TownInsectMove_Walk(insect) == 0) {
        return;
    }
    insect->timer = (short) (timer - 1);
    if (timer == 5) {
        int x;
        int z;
        Position_Tile(&x, &z, (const Position *) &insect->position);
        if (UnitTypeInfo_Byte09At(x, z) == 0 && !town_insect_moves_in_session()) {
            EffectSystem_StartSet(0x80, &insect->position, NULL, &data_020e25d4);
            return;
        }
        insect->action = 9;
    } else if (timer <= 0) {
        int n = *frames;
        if (n < 2) {
            insect->angle_y = (short) (insect->angle_y - 0xaaa);
        } else if ((n + 1) % 4 == 0) {
            insect->angle_y = (short) (insect->angle_y + 0xaaa);
        } else if ((n + 1) % 2 == 0) {
            insect->angle_y = (short) (insect->angle_y - 0xaaa);
        }
        *frames = 0;
        TownInsectMove_Leave(insect);
    }
}
CLEAN_AS(func_ov003_02232e88, TownInsectMove_Walk1E)

/* func_ov003_02232f78: flees on the ground, fading by 1 a frame (leaving once faded). Something
 * ahead turns it and stops it for the frame. Over water it sinks by 1/16, or below the water's
 * limit splashes and leaves. Else it sinks by 1/8 and zigzags along its heading (kind 0x1f by
 * 0x71c every 8 frames; kind 0x35 about z, its y heading 0), at twice its byte 0x257 (kinds 0x36
 * and 0x37 4 times; kind 0x1a a quarter of its byte 0x257). */
void TownInsectMove_Flee(TownInsect *insect, short *frames)
{
    Vec3 *position = &insect->position;
    int speed = 2;
    s8 kind = insect->kind;
    CollisionGround ground;
    CollisionGround_Init(&ground, position, 0, 1);
    if (TownInsectMove_FadeStep(insect, 1) != 0) {
        TownInsectMove_Leave(insect);
    }
    if (TownInsectMove_TurnFromObstacle(insect) != 0) {
        CollisionGround_Destroy(&ground);
        return;
    }
    if (ground.unk_30 != 0) {
        if (CollisionGround_IsBelowLimit(&ground, position->y) != 0) {
            TownInsectMove_Leave(insect);
            TownInsectMove_Splash(insect);
        } else {
            position->y -= 0x100;
        }
        CollisionGround_Destroy(&ground);
        return;
    }
    position->y -= 0x200;
    short angle;
    Vec3 step;
    if (kind == 0x35) {
        angle = insect->angle_z;
        TownInsectMove_StepAlong(&step, angle);
    } else {
        if (town_insect_moves_kind_36_or_37(kind)) {
            speed = 4;
        }
        angle = insect->angle_y;
        TownInsectMove_StepAlong(&step, angle);
    }
    int n = *frames;
    if (kind == 0x1f) {
        if (n == 0) {
            angle = (short) (angle + FX_Div(0x2000, 0x6000));
        } else if (n % 16 == 0) {
            angle = (short) (angle + 0x71c);
        } else if (n % 8 == 0) {
            angle = (short) (angle - 0x71c);
        }
    } else {
        fx32 first = n == 0 ? FX_Div(0x2000, 0x6000) : 0;
        angle = town_insect_moves_zigzag(angle, n, 0xaaa, first);
    }
    if (kind == 0x35) {
        insect->angle_z = angle;
        insect->angle_y = 0;
    } else {
        insect->angle_y = angle;
    }
    if (kind == 0x1a) {
        position->z += FX_MulFunc(FX_MulFunc(town_insect_moves_fx(insect->unk_257), step.z), 0x400);
        position->x += FX_MulFunc(FX_MulFunc(town_insect_moves_fx(insect->unk_257), step.x), 0x400);
    } else {
        position->x += FX_MulFunc(step.x, town_insect_moves_fx(speed * insect->unk_257));
        position->z += FX_MulFunc(step.z, town_insect_moves_fx(speed * insect->unk_257));
    }
    *frames = (short) (*frames + 1);
    CollisionGround_Destroy(&ground);
}
CLEAN_AS(func_ov003_02232f78, TownInsectMove_Flee)

/* func_ov003_02233178: hops (let go, fleeing, or coming out): along its heading (kind 0x35's
 * about z, its y heading 0) at its byte 0x257 plus 2 (where nothing stands ahead, or at action
 * 5), on an arc of 2 frames a step: let go or fleeing kinds 0x18, 0x1f and 0x35-0x37 drop (-10n^2)
 * and the others arc up from 0.04 (0xa0 - 11n), else up from 0.05 (0xc8 - 11n). A step onto
 * ground more than 4.0 up is taken back in x and z (the ground then taken as 0). Landed (after
 * the first frame): in water below its limit it splashes and leaves; else let go it flees
 * (action 9; kind 0x1f at pace 4, kind 0x31 at frame 1 with its timer cleared), otherwise it
 * walks (action 4; kind 0x31 at frame 1; kinds 0x31 and 0x1e holding the scene in a session with
 * a point 12.0 ahead); its alarm and frames are cleared, it stands on the ground and levels out
 * (but kind 0x35). */
void TownInsectMove_Hop(TownInsect *insect, short *frames)
{
    Vec3 *position = &insect->position;
    Vec3 before;
    town_insect_moves_copy(&before, position);
    CollisionGround ground;
    CollisionGround_Init(&ground, position, 0, 1);
    Vec3 step;
    if (insect->kind == 0x35) {
        insect->angle_y = 0;
        TownInsectMove_StepAlong(&step, insect->angle_z);
    } else {
        TownInsectMove_StepAlong(&step, insect->angle_y);
    }
    if (insect->action == 5 || TownInsectMove_FeelObstacles(insect, 0x50, 0xe38) == 0) {
        position->x += FX_MulFunc(town_insect_moves_fx(insect->unk_257 + 2), step.x);
        position->z += FX_MulFunc(town_insect_moves_fx(insect->unk_257 + 2), step.z);
    }
    u8 action = insect->action;
    int n = *frames;
    if (action == 9 || action == TOWN_INSECT_ACTION_LET_GO) {
        switch (insect->kind) {
            case 0x18:
            case 0x1f:
            case 0x35:
            case 0x36:
            case 0x37:
                position->y -= 10 * n * n;
                break;
            default:
                position->y += (0xa0 - 11 * n) * n;
                break;
        }
    } else {
        position->y += (0xc8 - 11 * n) * n;
    }
    fx32 floor;
    if (ground.unk_30 != 0) {
        floor = ground.limit;
    } else {
        floor = CollisionGround_GetHeight(&ground, 0);
        if (floor > 0x4000) {
            floor = 0;
            position->x = before.x;
            position->z = before.z;
        }
    }
    if (position->y <= floor && *frames > 0) {
        if (CollisionGround_IsBelowLimit(&ground, position->y) != 0) {
            TownInsectMove_Leave(insect);
            TownInsectMove_Splash(insect);
        } else {
            if (insect->action == TOWN_INSECT_ACTION_LET_GO) {
                s8 kind = insect->kind;
                if (kind == 0x1f) {
                    insect->unk_257 = 4;
                } else if (kind == 0x31) {
                    insect->timer = 0;
                    if (town_insect_moves_frame(insect) != 1) {
                        town_insect_moves_set_frame(insect, 1);
                    }
                }
                insect->action = 9;
            } else {
                insect->action = 4;
                if (insect->kind == 0x31) {
                    town_insect_moves_set_frame(insect, 1);
                }
                s8 kind = insect->kind;
                if ((kind == 0x31 || kind == 0x1e) && town_insect_moves_in_session() && LinkGlobal_HoldsScene() != 0) {
                    TownInsectMove_SetTarget(insect, insect->angle_y, 0xc000);
                }
            }
            insect->unk_254 = 0;
            *frames = 0;
            position->y = floor + CollisionQuery_FloorHeight(0);
            if (insect->kind != 0x35) {
                insect->angle_x = 0;
            }
        }
    } else {
        *frames = (short) (*frames + 2);
    }
    CollisionGround_Destroy(&ground);
}
CLEAN_AS(func_ov003_02233178, TownInsectMove_Hop)

/* func_ov003_022333b0 (kind 0x1e hidden): when its tile's count runs out it comes out (action 5,
 * shown) heading away from the nearest player. Else with a player within 5.0 its byte 0x252 is
 * set to 60 frames, during which it plays its sound 0. */
void TownInsectMove_Wait1E(TownInsect *insect, short *frames)
{
    const Vec3 *position = &insect->position;
    Actor *nearest = TownInsectMove_NearestPlayer(position);
    if (TownInsectMove_CountStand(insect, position) != 0) {
        if (nearest != NULL) {
            int angle = Vec_YawTo(position, &nearest->position);
            insect->action = 5;
            NNS_G3dMdlSetMdlAlpha(town_insect_moves_model(insect), 0, 0x1f);
            insect->angle_y = (short) (angle + 0x8000);
            *frames = 0;
        }
        return;
    }
    if (nearest != NULL && Vec_DistanceXZ(position, &nearest->position) < 0x5000) {
        insect->unk_252 = 0x3c;
    }
    int calling = insect->unk_252;
    if (calling > 0) {
        TownInsectMove_PlaySound(insect, 0, 1);
        insect->unk_252 = (u8) (calling - 1);
    }
}
CLEAN_AS(func_ov003_022333b0, TownInsectMove_Wait1E)

/* func_ov003_0223345c (kind 0x1e): walks with its sound 1 (actions 4 and 0x11), hops (5 and
 * let go), flees, and hidden (0x13) waits for a player to stand by. */
void TownInsectMove_Update1E(TownInsect *insect)
{
    short *frames = &insect->frames_left;
    switch (insect->action) {
        case 4:
        case 0x11:
            TownInsectMove_PlaySound(insect, 1, 1);
            TownInsectMove_Walk1E(insect, frames);
            break;
        case 5:
        case TOWN_INSECT_ACTION_LET_GO:
            TownInsectMove_Hop(insect, frames);
            break;
        case 9:
            TownInsectMove_Flee(insect, frames);
            break;
        case 0x13:
            TownInsectMove_Wait1E(insect, frames);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov003_0223345c, TownInsectMove_Update1E)

/* func_ov003_022334d8 (kinds 0x18 and 0x3b): hops let go and flees. Fading (actions 7 and 8) by
 * 4 a frame, once faded it is hidden at rest (action 0x13) at the origin and main's
 * Block02042200_Update runs. At action 0x12 it fades (action 7) when its tile's item code is
 * outside 0x154a-0x1553 or it is on the tile ahead of this console's player.
 * REQUIRES: at action 0x12 the town map exists and the tile has an item code (the original
 * reads it without a test). */
void TownInsectMove_Update18(TownInsect *insect)
{
    switch (insect->action) {
        case TOWN_INSECT_ACTION_LET_GO:
            TownInsectMove_Hop(insect, &insect->frames_left);
            break;
        case 9:
            TownInsectMove_Flee(insect, &insect->frames_left);
            break;
        case 7:
        case 8:
            if (TownInsectMove_FadeStep(insect, 4) != 0) {
                NNS_G3dMdlSetMdlAlpha(town_insect_moves_model(insect), 0, 0);
                insect->action = 0x13;
                insect->position.x = 0;
                insect->position.y = 0;
                insect->position.z = 0;
                Block02042200_Update();
            }
            break;
        case 0x12: {
            AcreMap *map = (AcreMap *) (uintptr_t) AcreMap_Town();
            int x;
            int z;
            Position_Tile(&x, &z, (const Position *) &insect->position);
            u16 item = *town_insect_moves_item_at(map, x, z);
            int on_it = item >= 0x154a && item <= 0x1553;
            if (!on_it || TownInsect_OnPlayersAheadTile(&insect->position) != 0) {
                insect->action = 7;
            }
            break;
        }
        default:
            break;
    }
}
CLEAN_AS(func_ov003_022334d8, TownInsectMove_Update18)

/* func_ov003_022335cc (kinds 0xa and 0x33): overlay 68 runs action 0; action 6 wanders in its box
 * (and TownInsectMove_OnSpot); fleeing or let go it flaps, plays its sound 0 and flies up and away
 * (at 1.8); startled (7) or at rest it starts again (action 0), startled turned by its word
 * 0x240 when its byte 0x24a is set. */
void TownInsectMove_Update0A(TownInsect *insect)
{
    switch (insect->action) {
        case 0:
            InsectPath_Roam(insect);
            break;
        case 6:
            TownInsectMove_WanderInBox(insect);
            TownInsectMove_OnSpot(insect);
            break;
        case 9:
        case TOWN_INSECT_ACTION_LET_GO:
            TownInsectMove_ToggleFrame(insect);
            TownInsectMove_PlaySound(insect, 0, 1);
            TownInsectMove_Escape(insect, 0x1ccd);
            break;
        case 7:
            insect->action = 0;
            if (insect->unk_24a != 0) {
                insect->angle_y = (short) (insect->angle_y + insect->unk_240);
            }
            break;
        case 0x13:
            insect->unk_24a = 0;
            insect->action = 0;
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov003_022335cc, TownInsectMove_Update0A)

/* func_ov003_02233674 (kinds 0xb and 0x3a): overlay 68 runs actions 0, 2 (both with its sound 0),
 * 3, 7 and 8 (its scale first) and 4; let go it plays its sound 0, flaps and flies up and away
 * (at 1.2). It always counts as in view. */
void TownInsectMove_Update0B(TownInsect *insect)
{
    switch (insect->action) {
        case 0:
            TownInsectMove_PlaySound(insect, 0, 1);
            InsectPath_Chase(insect);
            break;
        case 2:
            TownInsectMove_PlaySound(insect, 0, 1);
            InsectPath_Grow(insect);
            break;
        case 3:
        case 7:
        case 8:
            InsectPath_StretchScale(&insect->scale, 0);
            InsectPath_CircleOrLeave(insect);
            break;
        case TOWN_INSECT_ACTION_LET_GO:
            TownInsectMove_PlaySound(insect, 0, 1);
            TownInsectMove_ToggleFrame(insect);
            TownInsectMove_Escape(insect, 0x1333);
            break;
        case 4:
            InsectPath_StartGrow(insect);
            break;
        default:
            break;
    }
    insect->in_view = 1;
}
CLEAN_AS(func_ov003_02233674, TownInsectMove_Update0B)

/* func_ov003_02233720 (kinds 0x25 and 0x39 at action 0): outside a session or holding the scene,
 * alarmed out of reach (TownInsectMove_Sense gives 2) its animation runs at 1.0 again. It moves
 * on (TownInsectMove_Meander at its byte 0x257) and its frame counter steps by 2 over 5-8, which
 * TownInsectMove_Bob takes with a divisor of 10-13.
 * QUIRK: TownInsectMove_Meander is handed a copy of its heading, which is not stored back. */
void TownInsectMove_Crawl25(TownInsect *insect)
{
    short heading = insect->angle_y;
    short *frames = &insect->frames_left;
    if (!town_insect_moves_in_session() || LinkGlobal_HoldsScene() != 0) {
        if (TownInsectMove_Sense(insect) == 2) {
            TownInsect_SetAnimSpeed(insect, 0x1000);
            insect->unk_24a = 0;
        }
    }
    TownInsectMove_Meander(insect, &heading, 0x38e, 0x28, 0x50, town_insect_moves_fx(insect->unk_257));
    *frames = (short) (*frames + (short) FX_Div(0x2000, town_insect_moves_fx((int) MainRandom_Below(4) + 5)));
    TownInsectMove_Bob(insect, *frames, 0x1000, town_insect_moves_fx((int) MainRandom_Below(4) + 0xa));
}
CLEAN_AS(func_ov003_02233720, TownInsectMove_Crawl25)

/* func_ov003_022337d8 (kinds 0x25 and 0x39): crawls (action 0); fleeing or let go it flies off
 * (its sound 1 first); startled (7) it turns by its word 0x240 and crawls on; at rest it starts
 * with a point ahead (TownInsectMove_KindReach far) and its start where it is. */
void TownInsectMove_Update25(TownInsect *insect)
{
    switch (insect->action) {
        case 0:
            TownInsectMove_Crawl25(insect);
            break;
        case 9:
        case TOWN_INSECT_ACTION_LET_GO:
            if (insect->frames_left == 0) {
                TownInsectMove_PlaySound(insect, 1, 0);
            }
            TownInsectMove_FlyOff(insect, &insect->frames_left);
            break;
        case 7:
            insect->action = 0;
            insect->angle_y = (short) (insect->angle_y + insect->unk_240);
            break;
        case 0x13: {
            insect->unk_24a = 0;
            insect->action = 0;
            short heading = insect->angle_y;
            TownInsectMove_SetTarget(insect, heading, TownInsectMove_KindReach(insect));
            town_insect_moves_copy(&insect->start, &insect->position);
            break;
        }
        default:
            break;
    }
}
CLEAN_AS(func_ov003_022337d8, TownInsectMove_Update25)

/* func_ov003_02233890 (kind 0x32): overlay 68 runs action 0; turning (0xf) by 0x5b0 a frame to
 * its word 0x240 with its sound 0, and on (action 0) once there; fleeing or let go it flies up
 * and away; at rest it starts (action 0). */
void TownInsectMove_Update32(TownInsect *insect)
{
    short *frames = &insect->frames_left;
    switch (insect->action) {
        case 0:
            InsectPath_FollowPlayer(insect, frames);
            break;
        case 0xf: {
            s16 heading = insect->angle_y;
            if (Approach_S16Wrapped(&heading, insect->unk_240, 0x5b0) != 0) {
                insect->action = 0;
            }
            TownInsectMove_PlaySound(insect, 0, 1);
            insect->angle_y = heading;
            break;
        }
        case 9:
        case TOWN_INSECT_ACTION_LET_GO:
            TownInsectMove_FlyUpAway(insect, frames);
            *frames = (short) (*frames + 1);
            break;
        case 0x13:
            insect->action = 0;
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov003_02233890, TownInsectMove_Update32)

/* func_ov003_02233930 (kind 0x19): overlay 68 runs actions 3, 0xf and 4; let go it flies up and
 * away; at rest it waits out its timer and starts (action 3). */
void TownInsectMove_Update19(TownInsect *insect)
{
    short *frames = &insect->frames_left;
    switch (insect->action) {
        case 3:
        case 0xf:
            InsectPath_PickHeading(insect, frames);
            break;
        case 4:
            InsectPath_Glide(insect, frames);
            InsectPath_TurnFromObstacle(insect, (u16 *) frames);
            break;
        case TOWN_INSECT_ACTION_LET_GO:
            TownInsectMove_FlyUpAway(insect, frames);
            *frames = (short) (*frames + 1);
            break;
        case 0x13:
            if (insect->timer <= 0) {
                insect->action = 3;
            } else {
                insect->timer = (short) (insect->timer - 1);
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov003_02233930, TownInsectMove_Update19)

/* func_ov003_022339bc: kinds 0x1b-0x1d play their sound 0 while their alarm is under 5. */
void TownInsectMove_Sound1BTo1D(TownInsect *insect)
{
    switch (insect->kind) {
        case 0x1b:
        case 0x1c:
        case 0x1d:
            if (insect->unk_254 < 5) {
                TownInsectMove_PlaySound(insect, 0, 1);
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov003_022339bc, TownInsectMove_Sound1BTo1D)

/* func_ov003_022339f0: kinds 0xc and 0xd play their sound 0. */
void TownInsectMove_SoundCD(TownInsect *insect)
{
    switch (insect->kind) {
        case 0xc:
        case 0xd:
            TownInsectMove_PlaySound(insect, 0, 1);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov003_022339f0, TownInsectMove_SoundCD)

/* func_ov003_02233a14: outside a session or holding the scene, with something ahead it turns
 * (action 0xf) to a heading off it (TownInsectMove_HeadingOff), the bits 0xf00 of its word 0x21c
 * set and the word counted up; returns the side blocked (0 for none, and in a session without
 * the scene). */
int TownInsectMove_TurnAtObstacle(TownInsect *insect, short *frames)
{
    if (town_insect_moves_in_session() && LinkGlobal_HoldsScene() == 0) {
        return 0;
    }
    int side = TownInsectMove_FeelObstacles(insect, 0x50, 0xe38);
    if (side != 0) {
        *frames = 0;
        insect->action = 0xf;
        insect->unk_240 = TownInsectMove_HeadingOff(insect->angle_y, side);
        insect->unk_21c |= 0xf00;
        insect->unk_21c += 1;
    }
    return side;
}
CLEAN_AS(func_ov003_02233a14, TownInsectMove_TurnAtObstacle)

/* func_ov003_02233a94 (the waiting kinds flying): flies to its point (pace 1.0 over its byte
 * 0x257; where something stands ahead it stays, its point where it is). Rising (byte 0x24c) it
 * climbs to 1.25; else it comes down to the ground (or the water's limit; at action 0x11 water
 * makes it splash and leave), and landed at its point it rests (action 0x13, frame 0) for 20
 * times 2-10 frames: below 0 it splashes and leaves, alarmed (byte 0x24a) its alarm drops to 10
 * under its byte 0x255. Alarmed it flaps with its sound; fleeing or let go it fades away. */
void TownInsectMove_FlyWaiting(TownInsect *insect)
{
    Vec3 *target = &insect->target;
    Vec3 *position = &insect->position;
    int pace = town_insect_moves_div(0x1000, insect->unk_257);
    int arrived = 0;
    u8 action = insect->action;
    if (insect->unk_24a != 0) {
        TownInsectMove_ToggleFrame(insect);
        TownInsectMove_SoundCD(insect);
    }
    if (TownInsectMove_FeelObstacles(insect, 0x50, 0xe38) == 0) {
        if (Approach_PointXZ(position, target, pace, 0x14000, 0x333) == 0) {
            arrived = 1;
        } else {
            insect->angle_y = Vec_YawTo(position, target);
        }
    } else {
        arrived = 1;
        town_insect_moves_copy(target, position);
    }
    if (insect->unk_24c != 0) {
        if (Approach_EaseS32MinMax((int *) &position->y, 0x1400, pace, 0x1000, 0xcd) == 0) {
            insect->unk_24c = 0;
        }
    } else {
        CollisionGround ground;
        CollisionGround_Init(&ground, position, 0, 1);
        fx32 floor;
        if (ground.unk_30 != 0) {
            floor = ground.limit;
            if (insect->action == 0x11) {
                TownInsectMove_Splash(insect);
                insect->frames_left = 0;
                TownInsectMove_Leave(insect);
                CollisionGround_Destroy(&ground);
                return;
            }
        } else {
            floor = CollisionGround_GetHeight(&ground, 1);
            if (floor > 0x4000) {
                floor = CollisionQuery_FloorHeight(0);
            } else {
                floor += CollisionQuery_FloorHeight(0);
            }
        }
        if (Approach_EaseS32MinMax((int *) &position->y, floor, pace, 0x1000, 0x266) == 0 && arrived &&
            action != TOWN_INSECT_ACTION_LET_GO && action != 9) {
            int wait = (int) MainRandom_Below(9);
            insect->timer = (short) (20 * (wait + 2));
            insect->action = 0x13;
            town_insect_moves_set_frame(insect, 0);
            if (floor < 0) {
                TownInsectMove_Splash(insect);
                insect->frames_left = 0;
                TownInsectMove_Leave(insect);
            } else if (insect->unk_24a != 0) {
                insect->unk_254 = (u8) (insect->unk_255 - 0xa);
                insect->unk_24a = 0;
            }
        }
        CollisionGround_Destroy(&ground);
    }
    if (action == 9 || action == TOWN_INSECT_ACTION_LET_GO) {
        if (TownInsectMove_FadeStep(insect, 1) != 0) {
            TownInsectMove_Leave(insect);
        }
    }
}
CLEAN_AS(func_ov003_02233a94, TownInsectMove_FlyWaiting)

/* func_ov003_02233c70: a turn of 0 to `steps` - 1 steps of 5 degrees (0x38e) at random, the
 * other way on an even chance when `either_way`. */
short TownInsectMove_RandomTurn(int steps, int either_way)
{
    u8 drawn = (u8) MainRandom_Below(steps);
    if (drawn == 0) {
        return 0;
    }
    if (either_way != 0 && MainRandom_Below(100) > 0x32) {
        return (short) (drawn * -0x38e);
    }
    return (short) (drawn * 0x38e);
}
CLEAN_AS(func_ov003_02233c70, TownInsectMove_RandomTurn)

/* func_ov003_02233cb8 (the waiting kinds at rest): counts its frames. In a session without the
 * scene, moved off its point it flies there (action 4, rising). Else once its timer is reached it
 * turns (action 3) up to 55 degrees, the bits 0xf00 of its word 0x21c set. */
void TownInsectMove_Wait(TownInsect *insect, short *frames)
{
    *frames = (short) (*frames + 1);
    if (town_insect_moves_in_session() && LinkGlobal_HoldsScene() == 0) {
        if (insect->position.x != insect->target.x || insect->position.z != insect->target.z) {
            insect->action = 4;
            *frames = 0;
            insect->unk_24c = 1;
        }
    } else if (*frames >= insect->timer) {
        int heading = insect->angle_y;
        int turn = TownInsectMove_RandomTurn(0xc, 1);
        insect->unk_240 = (short) (turn + heading);
        insect->unk_21c |= 0xf00;
        insect->action = 3;
        *frames = 0;
    }
}
CLEAN_AS(func_ov003_02233cb8, TownInsectMove_Wait)

/* func_ov003_02233d68 (kinds 0xc, 0xd and 0x1b-0x1d): unless flying, fleeing or let go its alarm
 * is counted; more than 4 low bits in its word 0x21c make it flee. Turning (3, 0xf) to its word
 * 0x240 it flies on; startled (7) it turns from what is ahead; fleeing or let go (alarmed) and
 * flying (4, 0x11) it flies to its point. At rest (0x13), at frame 0 with its sound, it turns from
 * what is ahead or else waits (its word 0x21c cleared). */
void TownInsectMove_UpdateWaiting(TownInsect *insect)
{
    short *frames = &insect->frames_left;
    u8 action = insect->action;
    if (action != TOWN_INSECT_ACTION_LET_GO && action != 9 && action != 4) {
        TownInsectMove_Sense(insect);
    }
    TownInsectMove_FleeIfFlagged(insect, 4);
    switch (action) {
        case 3:
        case 0xf:
            TownInsectMove_TurnToHeading(insect, 1);
            break;
        case 7:
            insect->action = 0xf;
            insect->unk_21c |= 0xf00;
            TownInsectMove_TurnAtObstacle(insect, frames);
            break;
        case 9:
        case TOWN_INSECT_ACTION_LET_GO:
            insect->unk_24a = 1;
            TownInsectMove_FlyWaiting(insect);
            break;
        case 4:
        case 0x11:
            TownInsectMove_FlyWaiting(insect);
            break;
        case 0x13:
            TownInsectMove_Sound1BTo1D(insect);
            if (town_insect_moves_frame(insect) != 0) {
                town_insect_moves_set_frame(insect, 0);
            }
            if (TownInsectMove_TurnAtObstacle(insect, frames) == 0) {
                TownInsectMove_Wait(insect, frames);
                insect->unk_21c = 0;
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov003_02233d68, TownInsectMove_UpdateWaiting)

/* func_ov003_02233e4c: the players around the insect. In a session each of players 0-3 is
 * looked at (TownInsectMove_SensePlayer; the alarm counted only while holding the scene) and
 * *nearest becomes the nearest one's position; outside a session overlay 68 does it
 * (func_ov068_02271cec). nearest->x is 0 when none was found. While counting, the alarm falls by
 * one when every player was away; returns 1 when the alarm has risen to its byte 0x255 this
 * frame, 3 when it was there already, 2 when it fell below it this frame, else 0.
 * REQUIRES: in a session player 0 has an actor (the original compares a distance it did not
 * set otherwise). */
int TownInsectMove_SensePlayers(TownInsect *insect, Vec3 *nearest)
{
    int result = 0;
    fx32 best = 0x0fffffff;
    int counting = 1;
    u8 away[2] = {1, 1}; /* every player away; the one just looked at */
    u32 before = insect->unk_254;
    u32 reached = insect->unk_255;
    nearest->x = 0;
    if (town_insect_moves_in_session()) {
        if (LinkGlobal_HoldsScene() == 0) {
            counting = 0;
        }
        Vec3 point = {0, 0, 0};
        fx32 distance = 0x0fffffff;
        u8 player = 0;
        do {
            TownInsectMove_SensePlayer(insect, &point, &distance, &away[1], player, (u8) counting);
            away[0] = (away[0] & away[1]) != 0 ? 1 : 0;
            if (best > distance) {
                town_insect_moves_copy(nearest, &point);
                best = distance;
            }
            player++;
        } while (player < 4);
    } else {
        InsectPath_SensePlayers(insect, away, nearest);
    }
    if (counting) {
        u32 alarm = insect->unk_254;
        if (away[0] != 0 && alarm != 0) {
            alarm = (u8) (alarm - 1);
            insect->unk_254 = (u8) alarm;
        }
        if (reached <= alarm) {
            result = reached > before ? 1 : 3;
        } else if (reached <= before) {
            result = 2;
        }
    }
    return result;
}
CLEAN_AS(func_ov003_02233e4c, TownInsectMove_SensePlayers)

/* func_ov003_02233f48: player `player`, when it has an actor: *point becomes its position and
 * *distance its distance to the insect in x and z. When `counting`, the insect's alarm rises:
 * by 25 within 2.0, else (within its reach and moving) by 1, 3, 5, 8 or 15 as the player's speed
 * is up to 1000, 1100, 1168, exactly 1169 or more; at most to 0xfe. Out of reach or standing
 * still, *away is set. */
void TownInsectMove_SensePlayer(TownInsect *insect, Vec3 *point, fx32 *distance, u8 *away, u8 player, u8 counting)
{
    Actor *actor = SessionPlayers_ActorOf(player);
    if (actor == NULL) {
        return;
    }
    short alarm = insect->unk_254;
    fx32 reach = insect->reach;
    fx32 speed = actor->speed;
    town_insect_moves_copy(point, &actor->position);
    *distance = Vec_DistanceXZ(point, &insect->position);
    if (counting == 0) {
        return;
    }
    *away = 0;
    fx32 d = *distance;
    if (d < 0x2000) {
        alarm += 0x19;
    } else if (d > reach || speed == 0) {
        *away = 1;
    } else if (speed <= 0x3e8) {
        alarm += 1;
    } else if (speed <= 0x44c) {
        alarm += 3;
    } else if (speed <= 0x490) {
        alarm += 5;
    } else if (speed == 0x491) {
        alarm += 8;
    } else {
        alarm += 0xf;
    }
    if (alarm > 0xfe) {
        alarm = 0xfe;
    }
    insect->unk_254 = (u8) alarm;
}
CLEAN_AS(func_ov003_02233f48, TownInsectMove_SensePlayer)

/* func_ov003_02234030: turns towards its word 0x240 by 0xe38 a frame and, there, flies on
 * (action 4, its byte 0x24c `byte24c`, 1 returned). Arrived at its point or told to (the bits
 * 0xf00 of its word 0x21c), it first sets a new point ahead along the word 0x240 (its byte 0x259
 * plus 0-2 steps, 2-3 more when alarmed); when that could be, the word 0x240 heads there. In a
 * session without the scene it only flies on once moved off its point in both x and z. Let go,
 * it sets a point twice its byte 0x259 ahead and its byte 0x24c.
 * QUIRK: clearing the bits 0xf00 (mask 0xf0ff) clears the word's upper 16 bits too. */
int TownInsectMove_TurnToHeading(TownInsect *insect, int byte24c)
{
    int result = 0;
    s16 heading = insect->angle_y;
    if (insect->action == TOWN_INSECT_ACTION_LET_GO) {
        TownInsectMove_SetTarget(insect, insect->angle_y, town_insect_moves_fx((u8) (insect->unk_259 * 2)));
        insect->unk_24c = (u8) byte24c;
        return result;
    }
    if (LinkGlobal_HoldsScene() == 0 && town_insect_moves_in_session()) {
        if (insect->position.x != insect->target.x && insect->position.z != insect->target.z) {
            insect->action = 4;
            insect->unk_24c = (u8) byte24c;
        }
        return result;
    }
    int flags = insect->unk_21c;
    if ((insect->position.x == insect->target.x && insect->position.z == insect->target.z) || (flags & 0xf00) != 0) {
        u8 steps = (u8) (insect->unk_259 + MainRandom_Below(3));
        if (insect->unk_24a != 0) {
            steps = (u8) (steps + (u8) (MainRandom_Below(2) + 2));
        }
        if (TownInsectMove_SetTarget(insect, insect->unk_240, town_insect_moves_fx(steps)) != 0) {
            insect->unk_240 = Vec_YawTo(&insect->position, &insect->target);
        }
        insect->unk_21c = flags & 0xf0ff;
    }
    if (Approach_S16Wrapped(&heading, insect->unk_240, 0xe38) != 0) {
        insect->action = 4;
        insect->unk_24c = (u8) byte24c;
        result = 1;
    }
    insect->angle_y = heading;
    return result;
}
CLEAN_AS(func_ov003_02234030, TownInsectMove_TurnToHeading)

/* func_ov003_0223418c: a heading off what stands on `side` of heading `angle`: blocked on both
 * sides it turns back, 60 degrees off on a chance in ten; else mirrored about the line the
 * blocked side faces (negated, or turned half a turn about it). On a chance in ten, and always
 * when it came out the same, it turns 15 degrees further. */
short TownInsectMove_HeadingOff(short angle, int side)
{
    short original = angle;
    if (side == 3) {
        int chance = (int) MainRandom_Below(100);
        angle = (short) (angle + 0x8000);
        if (chance < 5) {
            angle = (short) (angle + 0x2aaa);
        } else if (chance < 0xa) {
            angle = (short) (angle - 0x2aaa);
        }
    } else if ((side == 1 && (angle < -0x4000 || (angle >= 0 && angle < 0x4000))) ||
               (side == 2 && (angle > 0x4000 || (angle <= 0 && angle > -0x4000)))) {
        angle = (short) -angle;
    } else if (angle >= 0) {
        angle = (short) (0x8000 - angle);
    } else {
        angle = (short) (-0x8000 - angle);
    }
    if ((int) MainRandom_Below(100) < 0xa) {
        angle = (short) (angle >= 0 ? angle + 0xaaa : angle - 0xaaa);
    }
    if (angle == original) {
        angle = (short) (angle >= 0 ? angle + 0xaaa : angle - 0xaaa);
    }
    return angle;
}
CLEAN_AS(func_ov003_0223418c, TownInsectMove_HeadingOff)

/* func_ov003_02234264: with something ahead, it turns off it (action 0xf, the bits 0xf00 of its
 * word 0x21c set, when alarmed; else action 0xd), its word 0x21c counted up, its frames cleared
 * and its point where it is. */
void TownInsectMove_CheckObstacle(TownInsect *insect)
{
    int side = TownInsectMove_FeelObstacles(insect, 0x50, 0xe38);
    if (side == 0) {
        return;
    }
    if (insect->unk_24a != 0) {
        insect->action = 0xf;
        insect->unk_21c |= 0xf00;
    } else {
        insect->action = 0xd;
    }
    insect->unk_240 = TownInsectMove_HeadingOff(insect->angle_y, side);
    insect->unk_21c += 1;
    insect->frames_left = 0;
    town_insect_moves_copy(&insect->target, &insect->position);
}
CLEAN_AS(func_ov003_02234264, TownInsectMove_CheckObstacle)

/* func_ov003_022342f8 (fleeing or let go, kinds 0x15-0x17): rises, by 0x44 times the frame plus
 * the frame squared over 2, over 4096; let go it also moves on along its heading at 16 steps a
 * frame (where nothing stands ahead). It leaves once faded. */
void TownInsectMove_RiseAway(TownInsect *insect, short *frames)
{
    Vec3 *position = &insect->position;
    if (insect->action == TOWN_INSECT_ACTION_LET_GO && TownInsectMove_FeelObstacles(insect, 0x50, 0xe38) == 0) {
        Vec3 step;
        TownInsectMove_StepAlong(&step, insect->angle_y);
        position->x += FX_MulFunc(step.x, 0x10000);
        position->z += FX_MulFunc(step.z, 0x10000);
    }
    fx32 t = town_insect_moves_fx(*frames);
    fx32 linear = FX_MulFunc(0x44000, t);
    position->y += (linear >> 12) + (FX_Div(FX_MulFunc(t, t), 0x2000) >> 12);
    *frames = (short) (*frames + 1);
    if (TownInsectMove_FadeStep(insect, 1) != 0) {
        TownInsectMove_Leave(insect);
    }
}
CLEAN_AS(func_ov003_022342f8, TownInsectMove_RiseAway)

/* func_ov003_022343a8 (kinds 0x15-0x17 flying): flies to its point at 1.0 over its byte 0x257
 * (at least 0xcd, 0x266 or 0x385 a frame for kinds 0x15, 0x16 and the others; double when
 * alarmed) heading there, and hovers (action 0x13) once there, or in a session without the
 * scene once out of tiles 16-79 in x or under 16 in z. It sinks to 1.0 below its word 0x228 and
 * then (byte 0x24c set) eases back up to it. */
void TownInsectMove_FlyToTarget(TownInsect *insect)
{
    Vec3 *target = &insect->target;
    Vec3 *position = &insect->position;
    int pace = town_insect_moves_div(0x1000, insect->unk_257);
    fx32 least;
    switch (insect->kind) {
        case 0x15:
            least = 0xcd;
            break;
        case 0x16:
            least = 0x266;
            break;
        default:
            least = 0x385;
            break;
    }
    if (insect->unk_24a != 0) {
        least = FX_MulFunc(least, 0x2000);
    }
    if (Approach_PointXZ(position, target, pace, 0x1000, least) == 0) {
        insect->action = 0x13;
    } else {
        insect->angle_y = Vec_YawTo(position, target);
        if (town_insect_moves_in_session() && LinkGlobal_HoldsScene() == 0) {
            int x;
            int z;
            Position_Tile(&x, &z, (const Position *) position);
            if (x < 0x10 || x > 0x4f || z < 0x10) {
                insect->action = 0x13;
            }
        }
    }
    if (insect->unk_24c != 0) {
        Approach_EaseS32MinMax((int *) &position->y, insect->unk_228, pace, 0x1ec, 0xcd);
    } else if (Approach_EaseS32MinMax((int *) &position->y, insect->unk_228 - 0x1000, pace, 0x333, 0xcd) == 0) {
        insect->unk_24c = 1;
    }
}
CLEAN_AS(func_ov003_022343a8, TownInsectMove_FlyToTarget)

/* func_ov003_022344c8 (kinds 0x15-0x17 hovering): bobs 1/32 a frame within 1/2 of its word
 * 0x228, 5 frames up and 5 down. In a session without the scene, moved off its point it flies
 * (action 4). Else it turns (action 3, the bits 0xf00 of its word 0x21c set) on chances that grow
 * with the frames (at frame 0, 10, 20 and 30), at frame 40 at the latest; out of actions 0xd and
 * 0xe up to 25 degrees (kind 0x17) or 65 degrees, its point where it is. */
void TownInsectMove_Hover(TownInsect *insect, short *frames)
{
    Vec3 *position = &insect->position;
    int chance = (int) MainRandom_Below(100);
    if (town_insect_moves_in_session() && LinkGlobal_HoldsScene() == 0) {
        if (insect->target.x != position->x || insect->target.z != position->z) {
            insect->action = 4;
            *frames = 0;
            return;
        }
    } else {
        short n = *frames;
        if ((n == 0 && chance > 0x5f) || (n == 0xa && chance > 0x50) || ((n == 0x14 || n == 0x1e) && chance > 0x32) ||
            n >= 0x28) {
            u8 action = insect->action;
            if (action != 0xd && action != 0xe) {
                int steps = insect->kind == 0x17 ? 5 : 0xd;
                int heading = insect->angle_y;
                int turn = TownInsectMove_RandomTurn((u8) steps, 1);
                insect->unk_240 = (short) (turn + heading);
                town_insect_moves_copy(&insect->target, &insect->position);
            }
            insect->action = 3;
            insect->unk_21c |= 0xf00;
            *frames = 0;
            return;
        }
    }
    if (*frames % 10 < 5) {
        if (position->y < insect->unk_228 + 0x800) {
            position->y += 0x80;
        }
    } else if (position->y > insect->unk_228 - 0x800) {
        position->y -= 0x80;
    }
    *frames = (short) (*frames + 1);
}
CLEAN_AS(func_ov003_022344c8, TownInsectMove_Hover)

/* func_ov003_02234600 (kinds 0x15-0x17): with a count in bits 4-7 of its word 0x21c, at rest it
 * flaps now and then (frame 2 or 0 every 20th frame of its counter); else it flaps. Unless
 * fleeing or let go its alarm is counted; more than 5 low bits in its word 0x21c make it flee.
 * Turning (3, and 0xf which then waits at 0x12) to its word 0x240; flying (4) to its point (with
 * a count overlay 68 does it), turning off what is ahead; hovering (0xc-0xe; kind 0x17 from frame
 * 100); startled (7) it turns from where it is; fleeing or let go it rises away. Otherwise, with
 * a count, after 40 frames (on chances every 10th) and at 200 the count is cleared and it hovers
 * for 100 frames; without one, once its word 0x244 runs out outside a session, overlay 68 may
 * take it (func_ov068_02271b30), and it flies on from 0x12 or else hovers, its low four bits
 * cleared.
 * QUIRK: the masks 0xff0f and 0xfff0 also clear the word's upper 16 bits. */
void TownInsectMove_UpdateTurned(TownInsect *insect)
{
    short *frames = &insect->frames_left;
    int count = (insect->unk_21c & 0xf0) >> 4;
    int waits = 0;
    if (count > 0 && insect->action == 0x13) {
        if (insect->counter % 20 == 0) {
            int chance = (int) MainRandom_Below(100);
            if (town_insect_moves_frame(insect) == 0 && chance > 0x5c) {
                town_insect_moves_set_frame(insect, 2);
            } else if (chance > 0x32) {
                town_insect_moves_set_frame(insect, 0);
            }
        } else if (town_insect_moves_frame(insect) != 0) {
            TownInsectMove_ToggleFrame(insect);
        }
    } else {
        TownInsectMove_ToggleFrame(insect);
    }
    if (insect->action != TOWN_INSECT_ACTION_LET_GO && insect->action != 9) {
        TownInsectMove_Sense(insect);
    }
    TownInsectMove_FleeIfFlagged(insect, 5);
    switch (insect->action) {
        case 0xf:
            waits = 1;
            /* fallthrough */
        case 3:
            if (TownInsectMove_TurnToHeading(insect, 0) != 0 && waits) {
                insect->action = 0x12;
            }
            break;
        case 4:
            if (count > 0) {
                InsectPath_GoToPerch(insect);
            } else {
                TownInsectMove_FlyToTarget(insect);
            }
            TownInsectMove_CheckObstacle(insect);
            *frames = 0;
            break;
        case 0xc:
        case 0xd:
        case 0xe:
            if (insect->kind == 0x17) {
                *frames = 0x64;
            }
            TownInsectMove_Hover(insect, frames);
            break;
        case 7:
            insect->action = 3;
            town_insect_moves_copy(&insect->target, &insect->position);
            insect->unk_21c |= 0xf00;
            break;
        case 9:
        case TOWN_INSECT_ACTION_LET_GO:
            TownInsectMove_RiseAway(insect, frames);
            break;
        default:
            if (count > 0) {
                *frames = (short) (*frames + 1);
                if ((*frames > 0x28 && *frames % 10 == 0 && MainRandom_Below(100) > 0x50) || *frames > 0xc8) {
                    insect->unk_21c &= 0xff0f;
                    *frames = 0;
                    insect->action = 0xc;
                    insect->unk_244 = 0x64;
                }
            } else {
                int ran_out = TownInsectMove_WaitOver(insect);
                *frames = 0;
                if (insect->unk_24a == 0 && ran_out != 0 && !town_insect_moves_in_session()) {
                    InsectPath_FindPerch(insect);
                }
                if (insect->action == 0x12) {
                    insect->action = 4;
                } else {
                    insect->unk_24a = 0;
                    insect->action = 0xc;
                    insect->unk_21c &= 0xfff0;
                }
            }
            break;
    }
}
CLEAN_AS(func_ov003_02234600, TownInsectMove_UpdateTurned)

/* func_ov003_0223482c: the flags func_ov003_02224768 tests for `value` (overlay 68's
 * func_ov068_02270070): 0xf for 2 and 3, else 0x3f. */
int TownInsectMove_TestFlags(int value)
{
    return value == 2 || value == 3 ? 0xf : 0x3f;
}
CLEAN_AS(func_ov003_0223482c, TownInsectMove_TestFlags)

/* ---- Kinds 0-7, and the moves the kinds share */

/* The ROM's float-to-integer conversion (the float's bits in, as the soft-float code takes
 * them). */
extern int _ffix(int bits);
/* The SDK's difference of two points: a minus b into the third. */
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *difference);

/* The float 5120.5 as its bits: _ffix makes it 0x1400, 1.25 in 20.12 fixed point. */
#define TOWN_INSECT_MOVES_FLEE_BOOST_BITS 0x45a00400

/* The ARM's ASR by a register: only the shift's low byte counts, and from 32 on every bit is
 * the sign. */
static fx32 town_insect_moves_asr_register(fx32 value, int shift)
{
    int amount = shift & 0xff;
    if (amount >= 32) {
        return value < 0 ? -1 : 0;
    }
    return value >> amount;
}

/* The two feelers ahead of the insect (TownInsectMove_PlaceFeelers): its two points at 0x1ec. */
static Vec3 *town_insect_moves_feelers(TownInsect *insect)
{
    return (Vec3 *) (void *) insect->unk_1ec;
}

/* A new target ahead along the heading, at the kind's reach; the start point moves to where the
 * insect is when there was one. */
static void town_insect_moves_retarget(TownInsect *insect)
{
    fx32 reach = TownInsectMove_KindReach(insect);
    if (TownInsectMove_SetTarget(insect, insect->angle_y, reach) != 0) {
        town_insect_moves_copy(&insect->start, &insect->position);
    }
}

/* func_ov003_02234840: the flap cycle of kinds 0-7 (TownInsectMove_FlyBobbing), run after
 * `frames` (TownInsect.frames_left) was stepped. Once `frames` is past the byte 0x256 the cycle
 * starts again: at 0 for 0x10 frames when the byte 0x24c (down) is set, else at 8 for 0x14. The
 * byte 0x24c is cleared once the insect is more than 0x300 above the word 0x220 (its floor), and
 * set when it is below the floor; within 0x320 below, it is put back on it. */
void TownInsectMove_FlapCycle(TownInsect *insect, short *frames)
{
    u8 down = insect->unk_24c;
    /* QUIRK: the original picks the floor as the word 0x220 when it differs from the word 0x228
     * and as the word 0x228 when they are equal: the word 0x220 either way. */
    int floor = insect->unk_220;
    int top = floor + 0x300;

    if (insect->unk_256 < *frames) {
        if (down != 0) {
            *frames = 0;
            insect->unk_256 = 0x10;
        } else {
            *frames = 8;
            insect->unk_256 = 0x14;
        }
    }
    if (down != 0 && insect->position.y > top) {
        insect->unk_24c = 0;
    }
    if (insect->position.y < floor) {
        if (insect->position.y > floor - 0x320) {
            insect->position.y = floor;
        }
        insect->unk_24c = 1;
    }
}
CLEAN_AS(func_ov003_02234840, TownInsectMove_FlapCycle)

/* func_ov003_022348dc: flown up and away along its heading: a step of 0x29 along it (at 16 times
 * the length when nothing stands ahead), and up by `speed` times 0x44 times TownInsect.frames_left
 * (shifted down 12), which counts up by one a frame. Leaves once it has faded out
 * (TownInsectMove_FadeStep).
 * QUIRK: the rise is shifted right by FX_Div(frames squared, 1.0) + 12 as an ARM register shift,
 * whose low byte is 12 for every frame count; FX_Div is still called. */
void TownInsectMove_Escape(TownInsect *insect, fx32 speed)
{
    Vec3 step;
    TownInsectMove_StepAlong(&step, insect->angle_y);
    if (TownInsectMove_FadeStep(insect, 1) != 0) {
        TownInsectMove_Leave(insect);
    }
    int n = insect->frames_left;
    fx32 rise = FX_MulFunc(speed, (fx32) ((u32) (0x44 * n) << 12));
    int shift = FX_Div((fx32) ((u32) (n * n) << 12), 0x1000) + 12;
    step.y = town_insect_moves_asr_register(rise, shift);
    if (TownInsectMove_FeelObstacles(insect, 0x50, 0xe38) == 0) {
        step.x = FX_MulFunc(step.x, 0x10000);
        step.z = FX_MulFunc(step.z, 0x10000);
    }
    insect->frames_left = (s16) (insect->frames_left + 1);
    VEC_Add(&insect->position, &step, &insect->position);
}
CLEAN_AS(func_ov003_022348dc, TownInsectMove_Escape)

/* func_ov003_02234984: the word 0x244 counted down; 1 once it is 0 (or below). */
int TownInsectMove_WaitOver(TownInsect *insect)
{
    if (insect->unk_244 > 0) {
        insect->unk_244--;
        return 0;
    }
    return 1;
}
CLEAN_AS(func_ov003_02234984, TownInsectMove_WaitOver)

/* func_ov003_022349a0: action 0 of kinds 0-7 (and kind 8): flying with a bob. Its animation is
 * cut to 9 frames (not kind 8) and the players are sensed (TownInsectMove_Sense); when the alarm
 * fell, the animation runs at its speed again and the byte 0x24a (alarmed) is cleared.
 *   alarmed:     the animation runs at 0x1333 times the word 0x21c; kind 8 moves away from this
 *                console's player by up to 3 across;
 *   not alarmed: kind 8 flies as overlay 68 says (func_ov068_022715a0, which may stop the frame
 *                there); the others go to a spot to settle on outside a session
 *                (InsectPath_GoToSpot).
 * Then the bob: up by 0x44 n - 5 n^2 for n = TownInsect.frames_left, at least -0x333 (unless the
 * byte 0x24c is set and the rise is not negative), with n stepped by 4 and the flap cycle run
 * (TownInsectMove_FlapCycle); and the heading wanders (TownInsectMove_Meander, overlay 68's
 * InsectPath_Wander for kind 8) at the byte 0x257 for scale.
 * QUIRK: with the byte 0x24c set and the rise not negative, FX_MulFunc(rise, 2.0) is called and
 * its result dropped. */
void TownInsectMove_FlyBobbing(TownInsect *insect)
{
    s16 heading = insect->angle_y;
    Vec3 *position = &insect->position;
    s16 *frames = &insect->frames_left;
    Vec3 step;

    if (insect->kind != 8 && town_insect_moves_frame_count(insect) > 9) {
        town_insect_moves_play(insect, 9, 0, (u32) insect->unk_21c, 0);
    }
    if (TownInsectMove_Sense(insect) == 2) {
        if (insect->kind != 8) {
            TownInsect_SetAnimSpeed(insect, (unsigned long) insect->unk_21c);
        } else {
            TownInsect_SetAnimSpeed(insect, 0x1000);
        }
        insect->unk_24a = 0;
    }
    if (insect->unk_24a != 0) {
        if (insect->kind != 8) {
            fx32 speed = FX_MulFunc(insect->unk_21c, 0x1333);
            if (speed != insect->model.frames.speed) {
                TownInsect_SetAnimSpeed(insect, (unsigned long) speed);
            }
        } else {
            Actor *player = SessionPlayers_ActorOf(TOWN_INSECT_MOVES_THIS_PLAYER);
            if (player != NULL) {
                Vec3 away;
                Vec_Subtract(&away, position, &player->position);
                town_insect_moves_copy(&step, &away);
                TownInsectMove_ClampXZ(&step, &step, 3);
                VEC_Add(position, &step, position);
            }
        }
    } else if (insect->kind == 8) {
        if (InsectPath_ToBuilding(insect, frames, &step) == 0) {
            return;
        }
    } else {
        if (insect->unk_21c != insect->model.frames.speed) {
            TownInsect_SetAnimSpeed(insect, (unsigned long) insect->unk_21c);
        }
        if (!town_insect_moves_in_session()) {
            InsectPath_GoToSpot(insect, &heading);
        }
    }

    int n = *frames;
    fx32 rise = 0x44 * n + -10 * (n * n) / 2;
    if (insect->unk_24c != 0 && rise >= 0) {
        FX_MulFunc(rise, 0x2000);
    } else if (rise < -0x333) {
        rise = -0x333;
    }
    *frames = (s16) (*frames + 4);
    TownInsectMove_FlapCycle(insect, frames);
    position->y += rise;
    if (insect->kind == 8) {
        InsectPath_Wander(insect, &heading, 0xaaa, 0x14, 0x3c, town_insect_moves_fx(insect->unk_257));
    } else {
        TownInsectMove_Meander(insect, &heading, 0x38e, 0x14, 0x3c, town_insect_moves_fx(insect->unk_257));
    }
}
CLEAN_AS(func_ov003_022349a0, TownInsectMove_FlyBobbing)

/* func_ov003_02234b80: the update of kinds 0-7 (TownInsectKind_Start00To07). A timer (the word
 * 0x232) counts the frames something stands ahead (TownInsectMove_FeelObstacles); past 0x8c the
 * insect flees (action 9). Then by its action:
 *   0         flying (TownInsectMove_FlyBobbing);
 *   6         on its spot (TownInsectMove_OnSpot);
 *   9, 0xb    fleeing or let go: its animation cut to 9 frames, flown up and away at 0x1ccd
 *             (TownInsectMove_Escape);
 *   7         alarmed: the heading turned by the word 0x240 and flying again with a new target;
 *   0x13      started: flying, not alarmed, with a new target. */
void TownInsectMove_Update00To07(TownInsect *insect)
{
    s16 timer = insect->timer;
    if (timer > 0x8c) {
        insect->action = 9;
    } else if (TownInsectMove_FeelObstacles(insect, 0x50, 0xe38) != 0) {
        insect->timer = (s16) (timer + 1);
    } else {
        insect->timer = 0;
    }

    switch (insect->action) {
        case 0:
            TownInsectMove_FlyBobbing(insect);
            break;
        case 6:
            TownInsectMove_OnSpot(insect);
            break;
        case 9:
        case TOWN_INSECT_ACTION_LET_GO:
            if (town_insect_moves_frame_count(insect) > 9) {
                town_insect_moves_play(insect, 9, 0, 0x1000, 0);
            }
            TownInsectMove_Escape(insect, 0x1ccd);
            break;
        case 7:
            insect->action = 0;
            insect->angle_y = (s16) (insect->angle_y + insect->unk_240);
            town_insect_moves_retarget(insect);
            break;
        case TOWN_INSECT_ACTION_SHOWN:
            insect->unk_24a = 0;
            insect->action = 0;
            town_insect_moves_retarget(insect);
            break;
    }
}
CLEAN_AS(func_ov003_02234b80, TownInsectMove_Update00To07)

/* func_ov003_02234cc4: the model's animation set to frame 2 when it is at frame 1, else to frame
 * 1. */
void TownInsectMove_ToggleFrame(TownInsect *insect)
{
    if (town_insect_moves_frame(insect) == 1) {
        town_insect_moves_set_frame(insect, 2);
    } else {
        town_insect_moves_set_frame(insect, 1);
    }
}
CLEAN_AS(func_ov003_02234cc4, TownInsectMove_ToggleFrame)

/* func_ov003_02234cf0: in a session, the insect alarmed (the byte 0x24a set, action 7) once its
 * alarm (the byte 0x254) has reached the kind's byte 0x255. Holding the scene, only when a
 * player was found (nearest->x not 0), and the word 0x240 becomes the heading from that player
 * to the insect. */
void TownInsectMove_AlarmTurn(TownInsect *insect, const Vec3 *nearest)
{
    u32 alarm = insect->unk_254;
    if (LinkGlobal_HoldsScene() != 0) {
        if (nearest->x != 0 && insect->unk_24a == 0 && alarm >= insect->unk_255) {
            insect->unk_240 = Vec_YawTo(nearest, &insect->position);
            insect->action = 7;
            insect->unk_24a = 1;
        }
    } else if (insect->unk_24a == 0 && alarm >= insect->unk_255) {
        insect->unk_24a = 1;
        insect->action = 7;
    }
}
CLEAN_AS(func_ov003_02234cf0, TownInsectMove_AlarmTurn)

/* func_ov003_02234d70: the players sensed (TownInsectMove_SensePlayers) and the insect turned
 * with what it found: in a session by TownInsectMove_AlarmTurn, outside by overlay 68
 * (InsectPath_FleeFrom). Returns what TownInsectMove_SensePlayers did. */
int TownInsectMove_Sense(TownInsect *insect)
{
    /* Only x is always set by TownInsectMove_SensePlayers; the original leaves the rest of the
     * point unset when no player is found. */
    Vec3 nearest = {0, 0, 0};
    int result = TownInsectMove_SensePlayers(insect, &nearest);
    if (town_insect_moves_in_session()) {
        TownInsectMove_AlarmTurn(insect, &nearest);
    } else {
        InsectPath_FleeFrom(insect, &nearest);
    }
    return result;
}
CLEAN_AS(func_ov003_02234d70, TownInsectMove_Sense)

/* func_ov003_02234dac: the height bobbed by the sine of `frame` over `divisor`, kept within
 * `limit` of the word 0x220 (within limit / 2.0 when the words 0x220 and 0x228 differ): a step
 * that would leave that band is not taken. */
void TownInsectMove_Bob(TownInsect *insect, int frame, int limit, fx32 divisor)
{
    fx32 step = FX_Div(FX_SinCosTable_[2 * ((u16) frame >> 4)], divisor);
    if (insect->unk_220 != insect->unk_228) {
        limit = FX_Div(limit, 0x2000);
    }
    fx32 y = insect->position.y;
    if ((step > 0 && y + step < limit + insect->unk_220) || (step < 0 && y + step > insect->unk_220 - limit)) {
        insect->position.y = y + step;
    }
}
CLEAN_AS(func_ov003_02234dac, TownInsectMove_Bob)

/* func_ov003_02234e28: the heading kept wandering while it flies.
 *   Something ahead (TownInsectMove_FeelObstacles): the heading turned from it
 *   (TownInsectMove_HeadingOff), the start point moved to the insect and a new target set; that
 *   is all for the frame.
 *   Else on every `divisor`th count of the byte 0x24f, when a roll of 100 is above `threshold`,
 *   the turning side (the byte 0x24b) changes; when the roll is above the byte 0x252, *heading
 *   turns by `step` to the side it had and becomes the insect's heading. It steps along
 *   *heading by `scale` (1.25 times that while alarmed, the byte 0x24a); farther from its start
 *   point than the kind allows (TownInsectMove_KindLeash) it turns back to it
 *   (TownInsectMove_TurnBack). The start point is brought towards the target
 *   (Approach_PointXZ); once it is there (outside a session or holding the scene), the
 *   byte 0x253 counts down, and at 0 the heading turns at random, the start point moves to the
 *   insect, an alarmed insect heads away from the nearest player (this console's player outside
 *   a session), and a new target is set.
 * QUIRK: the heading turns by the side the byte 0x24b had when the frame began; a change of
 * side shows on the next frame.
 * REQUIRES: `divisor` is not 0 (the callers pass 0x14 and 0x28). */
void TownInsectMove_Meander(TownInsect *insect, short *heading, int step, int divisor, u8 threshold, fx32 scale)
{
    Vec3 *start = &insect->start;
    Vec3 *position = &insect->position;
    int side = TownInsectMove_FeelObstacles(insect, 0x50, 0xe38);
    u8 turning = insect->unk_24b;
    int roll = (int) MainRandom_Below(100);

    if (side != 0) {
        insect->angle_y = TownInsectMove_HeadingOff(insect->angle_y, side);
        town_insect_moves_copy(start, position);
        fx32 reach = TownInsectMove_KindReach(insect);
        TownInsectMove_SetTarget(insect, insect->angle_y, reach);
        return;
    }
    if (insect->counter % divisor == 0 && roll > threshold) {
        insect->unk_24b = turning == 0 ? 1 : 0;
    }
    if (roll > insect->unk_252) {
        if (turning != 0) {
            *heading = (short) (*heading + step);
        } else {
            *heading = (short) (*heading - step);
        }
        insect->angle_y = *heading;
    }

    Vec3 along;
    TownInsectMove_StepAlong(&along, *heading);
    if (insect->unk_24a != 0) {
        fx32 boost = _ffix(TOWN_INSECT_MOVES_FLEE_BOOST_BITS);
        position->x += FX_MulFunc(FX_MulFunc(scale, along.x), boost);
        position->z += FX_MulFunc(FX_MulFunc(scale, along.z), boost);
    } else {
        position->x += FX_MulFunc(scale, along.x);
        position->z += FX_MulFunc(scale, along.z);
    }

    Vec3 offset;
    Vec_Subtract(&offset, start, position);
    if (Vec_LengthXZ(&offset) > TownInsectMove_KindLeash(insect)) {
        TownInsectMove_TurnBack(insect, start, 0xaaa);
    }
    fx32 max_step = TownInsectMove_KindSpeed(insect) + 0x19a;
    fx32 min_step = TownInsectMove_KindSpeed(insect);
    if (Approach_PointXZ(start, &insect->target, 0x28, max_step, min_step) != 0) {
        return;
    }
    if (town_insect_moves_in_session() && LinkGlobal_HoldsScene() == 0) {
        return;
    }

    if (insect->unk_253 != 0) {
        insect->unk_253--;
        return;
    }
    insect->angle_y = (s16) (insect->angle_y + TownInsectMove_RandomTurn(6, 1));
    town_insect_moves_copy(start, position);
    if (insect->unk_24a != 0) {
        Actor *player;
        if (town_insect_moves_in_session()) {
            player = TownInsectMove_NearestPlayer(position);
        } else {
            player = SessionPlayers_ActorOf(TOWN_INSECT_MOVES_THIS_PLAYER);
        }
        if (player != NULL) {
            insect->angle_y = Vec_YawTo(&player->position, position);
        }
    }
    fx32 reach = TownInsectMove_KindReach(insect);
    TownInsectMove_SetTarget(insect, insect->angle_y, reach);
}
CLEAN_AS(func_ov003_02234e28, TownInsectMove_Meander)

/* func_ov003_0223506c: the least step by which the start point is brought towards the target
 * (TownInsectMove_Meander), by kind; 0 for kinds other than 0-7 and 0x25. */
int TownInsectMove_KindSpeed(TownInsect *insect)
{
    switch (insect->kind) {
        case 0:
        case 1:
        case 2:
        case 3:
            return 0xf6;
        case 4:
            return 0x171;
        case 5:
            return 0x1ec;
        case 6:
            return 0x2b8;
        case 7:
            return 0x266;
        case 0x25:
            return 0xcd;
    }
    return 0;
}
CLEAN_AS(func_ov003_0223506c, TownInsectMove_KindSpeed)

/* func_ov003_022350cc: how far ahead a new target is set, by kind; 0 for kinds other than 0-7
 * and 0x25. */
int TownInsectMove_KindReach(TownInsect *insect)
{
    switch (insect->kind) {
        case 0:
        case 1:
            return 0x5000;
        case 2:
        case 3:
            return 0x4600;
        case 4:
            return 0x7800;
        case 5:
        case 6:
            return 0x5000;
        case 7:
            return 0xc800;
        case 0x25:
            return 0x3c00;
    }
    return 0;
}
CLEAN_AS(func_ov003_022350cc, TownInsectMove_KindReach)

/* func_ov003_02235130: how far from its start point an insect goes before it turns back, by
 * kind; 0 for kinds other than 0-7 and 0x25. */
int TownInsectMove_KindLeash(TownInsect *insect)
{
    switch (insect->kind) {
        case 0:
        case 1:
        case 2:
        case 3:
            return 0xccd;
        case 4:
            return 0xb33;
        case 5:
            return 0xccd;
        case 6:
            return 0xb33;
        case 7:
        case 0x25:
            return 0xccd;
    }
    return 0;
}
CLEAN_AS(func_ov003_02235130, TownInsectMove_KindLeash)

/* func_ov003_02235184: kinds 0-7 and 0x25 wait 0x14 counts (the byte 0x253) before their next
 * random turn (TownInsectMove_Meander). */
void TownInsectMove_SetTurnDelay(TownInsect *insect)
{
    switch (insect->kind) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 0x25:
            insect->unk_253 = 0x14;
            break;
    }
}
CLEAN_AS(func_ov003_02235184, TownInsectMove_SetTurnDelay)

/* func_ov003_022351c4: the heading turned towards `point` by up to `step`, and the insect moved
 * towards it by up to 1 across (TownInsectMove_ClampXZ). */
void TownInsectMove_TurnBack(TownInsect *insect, const Vec3 *point, int step)
{
    s16 heading = insect->angle_y;
    Vec3 back;
    town_insect_moves_copy(&back, point);
    Vec3 *position = &insect->position;
    Approach_S16Wrapped(&heading, Vec_YawTo(position, point), (s16) step);
    insect->angle_y = heading;
    VEC_Subtract(&back, position, &back);
    TownInsectMove_ClampXZ(&back, &back, 1);
    VEC_Add(position, &back, position);
}
CLEAN_AS(func_ov003_022351c4, TownInsectMove_TurnBack)

/* func_ov003_0223522c: the sound of kind `kind` for `which` (0 or 1; some kinds have one sound
 * for both), or -1 for none. */
int TownInsectMove_SoundNumber(int kind, int which)
{
    switch (kind) {
        case 51:
            return 0x823;
        case 11:
        case 58:
            return which == 0 ? 0x830 : 0x837;
        case 54:
            return which == 1 ? 0x834 : 0x833;
        case 55:
            return which == 1 ? 0x836 : 0x835;
        case 10:
            return 0x831;
        case 50:
            return 0x828;
        case 29:
            return 0x825;
        case 27:
            return 0x826;
        case 28:
            return 0x82c;
        case 12:
            return 0x82b;
        case 13:
            return 0x82d;
        case 15:
        case 25:
        case 32:
        case 57:
            return 0x812;
        case 14:
        case 33:
        case 34:
        case 35:
        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 52:
            return 0x811;
        case 36:
        case 45:
        case 46:
        case 47:
            return 0x810;
        case 20:
            return which != 0 ? 0x811 : -1;
        case 16:
            return which == 0 ? 0x822 : 0x80f;
        case 17:
            return which == 0 ? 0x827 : 0x80f;
        case 18:
            return which == 0 ? 0x82e : 0x80f;
        case 19:
            return which == 0 ? 0x824 : 0x80f;
        case 30:
            return which == 0 ? 0x829 : 0x82a;
    }
    return -1;
}
CLEAN_AS(func_ov003_0223522c, TownInsectMove_SoundNumber)

/* func_ov003_022353a4: the kind's sound `which` on the insect's sound source, when it has one:
 * SoundSource_Play when `play`, else SoundSource_PlayHeld. */
void TownInsectMove_PlaySound(TownInsect *insect, int which, int play)
{
    int number = TownInsectMove_SoundNumber(insect->kind, which);
    if (number >= 0) {
        if (play != 0) {
            SoundSource_Play(&insect->source, number);
        } else {
            SoundSource_PlayHeld(&insect->source, number);
        }
    }
}
CLEAN_AS(func_ov003_022353a4, TownInsectMove_PlaySound)

/* func_ov003_022353e0: the byte 0x24e (signed) counted down from how long a player has been in
 * state 0x5e at `point` (FieldActor_PlayerFramesToState5E): when it is not above 0 it is
 * refilled, in a session from the first of players 0-3 with a count above 0, else from this
 * console's player. Returns 1 when the count reaches 0. */
int TownInsectMove_CountStand(TownInsect *insect, const Vec3 *point)
{
    if ((s8) insect->unk_24e <= 0) {
        if (town_insect_moves_in_session()) {
            for (s8 player = 0; player < 4; player++) {
                insect->unk_24e = (u8) FieldActor_PlayerFramesToState5E(point, player);
                if ((s8) insect->unk_24e > 0) {
                    break;
                }
            }
        } else {
            insect->unk_24e = (u8) FieldActor_PlayerFramesToState5E(point, TOWN_INSECT_MOVES_THIS_PLAYER);
        }
    }
    if ((s8) insect->unk_24e > 0) {
        insect->unk_24e = (u8) (insect->unk_24e - 1);
        if (insect->unk_24e == 0) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov003_022353e0, TownInsectMove_CountStand)

/* func_ov003_02235454: the splash where it fell into water: when the ground under it says so
 * (CollisionGround.unk_30), sound 0x7e5 and effect 0x13 (kinds 0xc, 0xd, 0x1e, 0x1f), 0x14
 * (kinds 0x36, 0x37) or 0x12 (the others) just above the ground's limit, and 1 is returned. */
int TownInsectMove_Splash(TownInsect *insect)
{
    Vec3 point;
    CollisionGround ground;
    town_insect_moves_copy(&point, &insect->position);
    CollisionGround_Init(&ground, &point, 0, 1);
    if (ground.unk_30 == 0) {
        CollisionGround_Destroy(&ground);
        return 0;
    }
    point.y = ground.limit + 0x100;
    SoundSource_PlayHeld(&insect->source, 0x7e5);
    switch (insect->kind) {
        case 0xc:
        case 0xd:
        case 0x1e:
        case 0x1f:
            EffectSystem_StartKind(0x13, &point, NULL, NULL);
            break;
        case 0x36:
        case 0x37:
            EffectSystem_StartKind(0x14, &point, NULL, NULL);
            break;
        default:
            EffectSystem_StartKind(0x12, &point, NULL, NULL);
            break;
    }
    CollisionGround_Destroy(&ground);
    return 1;
}
CLEAN_AS(func_ov003_02235454, TownInsectMove_Splash)

/* func_ov003_02235518: whether the code on a tile (main/town_family.h: its line and its stage)
 * suits kind 0xf, 3 or 2; 0 for other kinds. */
int TownInsectMove_SuitsCode(int kind, const u16 *code)
{
    int stage = TownFamily_Stage(code);
    int line = TownFamily_Line(code);
    switch (kind) {
        case 0xf:
            if (line == 0 || line == 3) {
                return stage == 2;
            }
            if (line == 5) {
                return 0;
            }
            return line == 4 || stage == 1;
        case 3:
            switch (line) {
                case 0:
                    return stage == 5 || stage == 6;
                case 1:
                    return stage == 4 || stage == 6;
                case 2:
                    return stage == 6;
                case 3:
                    return stage == 6 || stage == 7 || stage == 8;
            }
            return 0;
        case 2:
            switch (line) {
                case 0:
                    return stage == 1 || stage == 4;
                case 1:
                    return stage == 3;
                case 2:
                    return stage == 2 || stage == 4;
                case 3:
                    return stage == 1 || stage == 4;
            }
            return 0;
    }
    return 0;
}
CLEAN_AS(func_ov003_02235518, TownInsectMove_SuitsCode)

/* func_ov003_022355d4: action 6 of kinds 0-7 (and 0xa, 0x33): on its spot, with the players
 * sensed (TownInsectMove_Sense), until the word 0x244 has counted down
 * (TownInsectMove_WaitOver).
 *   Waiting, kinds 0xa and 0x33 stay at frame 0 and wander in their box
 *   (TownInsectMove_WanderInBox); the others are alarmed (byte 0x254 NEAR) off a tile of set B
 *   (TownInsectMove_OnSetBTile) and play their resting animation (0x11 frames from frame 9),
 *   started again now and then (4 times in 100) when at frame 0x10.
 *   Done, the insect starts again (action 0x13) at the floor of the word 0x228, waiting
 *   (7 to 12) times 0x14 frames next time, with its flying animation (frame 1 for kinds 0xa and
 *   0x33). */
void TownInsectMove_OnSpot(TownInsect *insect)
{
    TownInsectMove_Sense(insect);
    if (TownInsectMove_WaitOver(insect) == 0) {
        s8 kind = insect->kind;
        if (kind == 0xa || kind == 0x33) {
            if (town_insect_moves_frame(insect) != 0) {
                town_insect_moves_set_frame(insect, 0);
            }
            TownInsectMove_WanderInBox(insect);
        } else {
            if (TownInsectMove_OnSetBTile(&insect->position) == 0) {
                insect->unk_254 = TOWN_INSECT_BYTE254_NEAR;
            }
            if (town_insect_moves_frame_count(insect) < 0xc) {
                town_insect_moves_play(insect, 0x11, 1, 0x1000, 9);
            } else if (town_insect_moves_frame(insect) == 0x10) {
                if ((int) MainRandom_Below(100) > 0x5f) {
                    town_insect_moves_play(insect, 0x11, 1, 0x1000, 9);
                }
            }
        }
    } else {
        insect->action = TOWN_INSECT_ACTION_SHOWN;
        insect->unk_220 = insect->unk_228;
        insect->unk_244 = (s16) (((int) MainRandom_Below(6) + 7) * 0x14);
        s8 kind = insect->kind;
        if (kind != 0xa && kind != 0x33) {
            town_insect_moves_play(insect, 9, 0, (u32) insect->unk_21c, 0);
        } else {
            town_insect_moves_set_frame(insect, 1);
        }
    }
}
CLEAN_AS(func_ov003_022355d4, TownInsectMove_OnSpot)

/* func_ov003_022356ec: the player (0-3) nearest to `point` in x plus z, or NULL. */
Actor *TownInsectMove_NearestPlayer(const Vec3 *point)
{
    Actor *best = NULL;
    int best_distance = 0x0fffffff;
    u8 player = 0;
    do {
        Actor *actor = SessionPlayers_ActorOf(player);
        if (actor != NULL) {
            int dx = point->x - actor->position.x;
            if (dx < 0) {
                dx = -dx;
            }
            int dz = point->z - actor->position.z;
            if (dz < 0) {
                dz = -dz;
            }
            if (dx + dz < best_distance) {
                best_distance = dx + dz;
                best = actor;
            }
        }
        player++;
    } while (player < 4);
    return best;
}
CLEAN_AS(func_ov003_022356ec, TownInsectMove_NearestPlayer)

/* func_ov003_02235744: the target set as far ahead along `angle` as the ground lets it, in
 * steps of 1.0 up to `steps`: the first step where the ground (with posts) stands above the
 * insect's height (or the floor, CollisionQuery_FloorHeight, when that is higher) stops it, one
 * step short. Returns 1, with the turn delay set (TownInsectMove_SetTurnDelay), when at least
 * one step was free. */
int TownInsectMove_TargetAhead(TownInsect *insect, int angle, int steps)
{
    int index = (u16) angle >> 4;
    fx32 sin = FX_SinCosTable_[2 * index];
    fx32 cos = FX_SinCosTable_[2 * index + 1];
    Vec3 *position = &insect->position;
    fx32 floor = position->y;
    if (floor < CollisionQuery_FloorHeight(0)) {
        floor = CollisionQuery_FloorHeight(0);
    }

    u8 i;
    for (i = 1; i < steps + 1; i++) {
        fx32 t = (fx32) ((u32) i << 12);
        Vec3 probe;
        probe.x = position->x + FX_MulFunc(t, sin);
        /* The original leaves y unset; the ground query does not use it. */
        probe.y = 0;
        probe.z = position->z + FX_MulFunc(t, cos);
        CollisionGround ground;
        CollisionGround_Init(&ground, &probe, 0, 0);
        int blocked = CollisionGround_GetHeight(&ground, 1) > floor;
        CollisionGround_Destroy(&ground);
        if (blocked) {
            break;
        }
    }
    i = (u8) (i - 1);
    if (i == 0) {
        return 0;
    }
    fx32 t = (fx32) ((u32) i << 12);
    insect->target.x = position->x + FX_MulFunc(t, sin);
    insect->target.z = position->z + FX_MulFunc(t, cos);
    TownInsectMove_SetTurnDelay(insect);
    return 1;
}
CLEAN_AS(func_ov003_02235744, TownInsectMove_TargetAhead)

/* func_ov003_02235834: the target set `distance` ahead along `angle`. Kinds 0-7, 0x1e, 0x25 and
 * 0x31 (and in a session kinds 0xc, 0xd and 0x1b-0x1d) go only as far as the ground lets them
 * (TownInsectMove_TargetAhead, in whole steps) and return whether they could; the others are
 * set straight and return 1. */
int TownInsectMove_SetTarget(TownInsect *insect, int angle, fx32 distance)
{
    switch (insect->kind) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 0x25:
        case 0x1e:
        case 0x31:
            return TownInsectMove_TargetAhead(insect, angle, (u8) (distance >> 12));
        case 0xc:
        case 0xd:
        case 0x1b:
        case 0x1c:
        case 0x1d:
            if (town_insect_moves_in_session()) {
                return TownInsectMove_TargetAhead(insect, angle, (u8) (distance >> 12));
            }
            break;
    }
    int index = (u16) angle >> 4;
    insect->target.x = insect->position.x + FX_MulFunc(distance, FX_SinCosTable_[2 * index]);
    insect->target.z = insect->position.z + FX_MulFunc(distance, FX_SinCosTable_[2 * index + 1]);
    return 1;
}
CLEAN_AS(func_ov003_02235834, TownInsectMove_SetTarget)

/* func_ov003_02235934: action 9 (fleeing) when the low four bits of the word 0x21c are above
 * `most`. */
void TownInsectMove_FleeIfFlagged(TownInsect *insect, int most)
{
    if ((insect->unk_21c & 0xf) > most) {
        insect->action = 9;
    }
}
CLEAN_AS(func_ov003_02235934, TownInsectMove_FleeIfFlagged)

/* func_ov003_02235950: whether the unit type of the tile under `point` has a group
 * (UnitTypeInfo_GroupAt). */
int TownInsectMove_OnGroupTile(const Vec3 *point)
{
    int x = 0;
    int z = 0;
    Position_Tile(&x, &z, (const Position *) (const void *) point);
    return UnitTypeInfo_GroupAt(x, z) != 0;
}
CLEAN_AS(func_ov003_02235950, TownInsectMove_OnGroupTile)

/* func_ov003_0223597c: a step of 0x29 along heading `angle`: the vector (0, 0, 0x29) turned by
 * Vec_RotateY. */
void TownInsectMove_StepAlong(Vec3 *step, int angle)
{
    step->x = 0;
    step->y = 0;
    step->z = 0x29;
    Vec_RotateY(step, angle);
}
CLEAN_AS(func_ov003_0223597c, TownInsectMove_StepAlong)

/* func_ov003_02235990: the two feelers placed `percent` percent of 1.0 ahead of the insect, at
 * `spread` either side of its heading (the word 0x23c for kind 0x35, else 0x23a). Returns 1. */
int TownInsectMove_PlaceFeelers(TownInsect *insect, int percent, int spread)
{
    Vec3 *feelers = town_insect_moves_feelers(insect);
    const Vec3 *position = &insect->position;
    s16 heading = insect->kind == 0x35 ? insect->angle_z : insect->angle_y;

    town_insect_moves_copy(&feelers[0], position);
    int left = (u16) (heading + spread) >> 4;
    feelers[0].x += FX_SinCosTable_[2 * left] * percent / 100;
    feelers[0].z += FX_SinCosTable_[2 * left + 1] * percent / 100;

    town_insect_moves_copy(&feelers[1], position);
    int right = (u16) (heading - spread) >> 4;
    feelers[1].x += FX_SinCosTable_[2 * right] * percent / 100;
    feelers[1].z += FX_SinCosTable_[2 * right + 1] * percent / 100;
    return 1;
}
CLEAN_AS(func_ov003_02235990, TownInsectMove_PlaceFeelers)

/* func_ov003_02235a74: which feelers find ground (with posts) above the insect's height or below
 * 0: 1 for the first, 2 for the second, 3 for both. */
int TownInsectMove_FeelersOffGround(TownInsect *insect)
{
    u8 sides = 0;
    Vec3 *feelers = town_insect_moves_feelers(insect);
    fx32 top = insect->position.y;
    CollisionGround first;
    CollisionGround second;

    CollisionGround_Init(&first, &feelers[0], 0, 0);
    fx32 height = CollisionGround_GetHeight(&first, 1);
    if (height < 0 || height > top) {
        sides = (u8) (sides + 1);
    }
    CollisionGround_Init(&second, &feelers[1], 0, 0);
    height = CollisionGround_GetHeight(&second, 1);
    if (height < 0 || height > top) {
        sides = (u8) (sides + 2);
    }
    CollisionGround_Destroy(&second);
    CollisionGround_Destroy(&first);
    return sides;
}
CLEAN_AS(func_ov003_02235a74, TownInsectMove_FeelersOffGround)

/* func_ov003_02235ae8: which feelers find ground (with posts) above the insect's height: 1 for
 * the first, 2 for the second, 3 for both. */
int TownInsectMove_FeelersBlocked(TownInsect *insect)
{
    u8 sides = 0;
    Vec3 *feelers = town_insect_moves_feelers(insect);
    fx32 top = insect->position.y;
    CollisionGround first;
    CollisionGround second;

    CollisionGround_Init(&first, &feelers[0], 0, 0);
    if (CollisionGround_GetHeight(&first, 1) > top) {
        sides = (u8) (sides + 1);
    }
    CollisionGround_Init(&second, &feelers[1], 0, 0);
    if (CollisionGround_GetHeight(&second, 1) > top) {
        sides = (u8) (sides + 2);
    }
    CollisionGround_Destroy(&second);
    CollisionGround_Destroy(&first);
    return sides;
}
CLEAN_AS(func_ov003_02235ae8, TownInsectMove_FeelersBlocked)

/* func_ov003_02235b54: which sides of the heading something stands on, `reach` percent of 1.0
 * ahead and `spread` either side (TownInsectMove_PlaceFeelers): 0 for none, 1 the one side, 2
 * the other, 3 both. Kinds 0x36 and 0x37 in action 4 also count ground below 0
 * (TownInsectMove_FeelersOffGround). Only outside a session, or holding the scene, or fleeing
 * or let go; else 0. */
int TownInsectMove_FeelObstacles(TownInsect *insect, int reach, int spread)
{
    if (!town_insect_moves_in_session() || LinkGlobal_HoldsScene() != 0 || insect->action == 9 ||
        insect->action == TOWN_INSECT_ACTION_LET_GO) {
        TownInsectMove_PlaceFeelers(insect, reach, spread);
        if (town_insect_moves_kind_36_or_37(insect->kind) && insect->action == 4) {
            return TownInsectMove_FeelersOffGround(insect);
        }
        return TownInsectMove_FeelersBlocked(insect);
    }
    return 0;
}
CLEAN_AS(func_ov003_02235b54, TownInsectMove_FeelObstacles)
