/* The motions the museum's insects share (museum_insect_motions.h). */
#include "museum_insect_motions.h"

#include "autoload_2/approach.h"
#include "clean.h"
#include "etc_museum.h"
#include "main/actor.h"
#include "main/animated_model.h"
#include "main/effect_system.h"
#include "main/field_collision.h"
#include "main/frame_ctrl.h"
#include "main/main_random.h"
#include "main/model_pool.h"
#include "main/player_actor_ops.h"
#include "main/session_players.h"

static_assert(offsetof(MuseumInsect, kept) == 0x34, "insect kept");
static_assert(offsetof(MuseumInsect, anchor) == 0x40, "insect anchor");
static_assert(offsetof(MuseumInsect, unk_98) == 0x98, "insect 0x98");
static_assert(offsetof(MuseumInsect, unk_a0) == 0xa0, "insect 0xa0");
static_assert(offsetof(MuseumInsect, distance) == 0xa4, "insect 0xa4");
static_assert(offsetof(MuseumInsect, unk_ac) == 0xac, "insect 0xac");
static_assert(offsetof(MuseumInsect, model.frames) == 0x14c, "insect frames");
static_assert(offsetof(MuseumInsect, unk_168) == 0x168, "insect 0x168");
static_assert(offsetof(MuseumInsect, unk_170) == 0x170, "insect 0x170");
static_assert(offsetof(MuseumInsect, mode) == 0x172, "insect mode");
static_assert(offsetof(MuseumInsect, pitch) == 0x190, "insect pitch");
static_assert(offsetof(MuseumInsect, roll) == 0x194, "insect roll");
static_assert(offsetof(MuseumInsect, kind) == 0x196, "insect kind");
static_assert(sizeof(InsectSighting) == 0x1c, "sighting");

/* The frames the rooms have run (museum_insects.c). */
extern u8 data_ov004_02259a24;
extern void *data_020e25d4; /* the effect sets' default set-up functions */
extern const s16 data_02139d9c[];
extern const s16 FX_SinCosTable_[];

extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *sum);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *difference);
extern void NNS_G3dMdlSetMdlAlpha(int model, int material, int alpha);

/* The insects' helpers after these: */
/* the player seen: the alarm moved, INSECT_MOTION_ALARM_* */
extern int func_ov004_02244658(MuseumInsect *insect, InsectSighting *sighting);
/* the same, the sighting not wanted */
extern int func_ov004_02244764(MuseumInsect *insect);
/* the insect's sound (InsectRoom_UpdateInsect's emitter): 1 starts one way, others another;
 * 0 when its kind has none */
extern int func_ov004_02244be0(MuseumInsect *insect, int mode);
/* MuseumInsect.timer (as 16 bits) counted down: 1 once it is 0 */
extern int func_ov004_02244c20(MuseumInsect *insect);
/* a facing step: (0, 0, 0x29) turned to `yaw` (Vec_RotateY) */
extern void func_ov004_02244fb8(Vec3 *out, int yaw);
/* `point` kept within the insect's bounds: bits 1 (low x), 2 (high x), 4 (low z), 8 (high z) */
extern int func_ov004_02244e38(MuseumInsect *insect, Vec3 *point);
/* the two feelers (unk_178) set ahead of the insect and tried against the ground and the
 * bounds: bit 1 the left one is blocked, bit 2 the right one; 02245174 for kind 52 */
extern int func_ov004_02245188(MuseumInsect *insect);
extern int func_ov004_02245174(MuseumInsect *insect);
/* a yaw away from a wall the feelers met (`blocked` as 02245188 gives it) */
extern short func_ov004_022447c0(short yaw, int blocked);
/* `out` at `distance` from `base` along `yaw`, at height 0 */
extern void func_ov004_02244f48(Vec3 *out, const Vec3 *base, int yaw, fx32 distance);
/* the animation switched between frames 1 and 2 */
extern void func_ov004_02244f20(MuseumInsect *insect);
/* `position` put back on x or z towards `previous` where it went off the floor */
extern int func_ov004_02244e94(Vec3 *position, const Vec3 *previous);
/* the flying motions' helpers */
extern int func_ov004_02244904(MuseumInsect *insect);
extern void func_ov004_02244d58(MuseumInsect *insect);
extern void func_ov004_022449ec(MuseumInsect *insect, int step, int period, unsigned int threshold);
extern void func_ov004_0224497c(MuseumInsect *insect, int phase, int range, int divisor);
extern void func_ov004_02244c40(MuseumInsect *insect);
/* a turn to unk_ac: once there, the mode `mode` and unk_170 `flag` */
extern void func_ov004_02244774(MuseumInsect *insect, int flag, int mode);

/* A whole number of units in 20.12 fixed point. */
static fx32 InsectMotion_fx(int whole)
{
    return (fx32) ((u32) whole << 12);
}

/* The whole frame an insect's animation is at, and its frame count. */
static unsigned int InsectMotion_frame(const MuseumInsect *insect)
{
    return ((u32) insect->model.frames.frame >> 12) & 0xffff;
}

static unsigned int InsectMotion_end(const MuseumInsect *insect)
{
    return ((u32) insect->model.frames.end >> 12) & 0xffff;
}

static void InsectMotion_play(MuseumInsect *insect, u32 frames, u8 flags, u32 speed, u16 start)
{
    FrameCtrl_Init(&insect->model.frames, frames, flags, speed, start);
}

static void InsectMotion_set_frame(MuseumInsect *insect, int frame)
{
    AnimatedModel_SetFrame((AnimatedModel *) (void *) &insect->model, frame);
}

static void InsectMotion_set_alpha(MuseumInsect *insect, int alpha)
{
    NNS_G3dMdlSetMdlAlpha(ModelPoolFiles_Model(&insect->files), 0, alpha);
}

static int InsectMotion_random(int bound)
{
    return (int) MainRandom_Below(bound);
}

/* func_ov004_02240f2c: a motion started: the position kept, at rest, the given pitch and yaw,
 * the alarm at 0 with `threshold` to reach, the player seen within `sight` sixteenths, the
 * speed, and a height `height` sixteenths above the position. */
int InsectMotion_Start(MuseumInsect *insect, short threshold, int sight, short pitch, short yaw, int height, int speed)
{
    insect->kept = insect->position;
    insect->mode = MUSEUM_INSECT_MODE_REST;
    insect->yaw = yaw;
    insect->pitch = pitch;
    insect->unk_9e = threshold;
    insect->unk_a0 = FX_MulFunc(InsectMotion_fx(sight), 0x100);
    insect->unk_4c = 0;
    insect->unk_16c = speed;
    /* a halfword at 0x30 cleared */
    insect->unk_30[0] = 0;
    insect->unk_30[1] = 0;
    insect->unk_9c = 0;
    insect->unk_a8 = insect->position.y + FX_MulFunc(InsectMotion_fx(height), 0x100);
    insect->unk_54 = insect->unk_a8;
    insect->unk_9a = 0;
    return 0;
}
CLEAN_AS(func_ov004_02240f2c, InsectMotion_Start)

/* func_ov004_02240fc0: the bounds 0x900 either way of the position's x, and from 0x200 below to
 * 0x500 above its z. */
void InsectMotion_BoundAroundPosition(MuseumInsect *insect)
{
    insect->low[0] = insect->position.x - 0x900;
    insect->low[1] = insect->position.z - 0x200;
    insect->high[0] = insect->position.x + 0x900;
    insect->high[1] = insect->position.z + 0x500;
}
CLEAN_AS(func_ov004_02240fc0, InsectMotion_BoundAroundPosition)

/* func_ov004_02241008: the bounds from two corners in sixteenths of a unit, x then z. */
void InsectMotion_SetBounds(MuseumInsect *insect, const int *low, const int *high)
{
    fx32 z = FX_MulFunc(InsectMotion_fx(low[1]), 0x100);
    fx32 x = FX_MulFunc(InsectMotion_fx(low[0]), 0x100);
    insect->low[0] = x;
    insect->low[1] = z;
    z = FX_MulFunc(InsectMotion_fx(high[1]), 0x100);
    x = FX_MulFunc(InsectMotion_fx(high[0]), 0x100);
    insect->high[0] = x;
    insect->high[1] = z;
}
CLEAN_AS(func_ov004_02241008, InsectMotion_SetBounds)

/* func_ov004_0224105c: a turn of a random number of steps of 0x38e (5 degrees), from -steps to
 * steps. */
short InsectMotion_RandomTurn(int steps)
{
    return (short) FX_MulFunc(0x38e, InsectMotion_fx(InsectMotion_random(steps * 2 + 1) - steps));
}
CLEAN_AS(func_ov004_0224105c, InsectMotion_RandomTurn)

/* func_ov004_02241084: a drift along the yaw at the insect's speed, the yaw turned by unk_4c
 * one way or the other one time in five (the way changed every 20th frame of those). Out of
 * the bounds, x or z goes back; a change of z moves y the other way by as much. */
void InsectMotion_Drift(MuseumInsect *insect)
{
    s16 yaw = insect->yaw;
    u8 way = insect->unk_ae;
    Vec3 *position = &insect->position;
    Vec3 old = *position;
    Vec3 unit;
    if (InsectMotion_random(100) > 80) {
        if ((int) data_ov004_02259a24 % 20 == 0) {
            way = !way;
            insect->unk_ae = way;
        }
        if (way) {
            yaw = (s16) (yaw + (s16) insect->unk_4c);
        } else {
            yaw = (s16) (yaw - (s16) insect->unk_4c);
        }
    }
    func_ov004_02244fb8(&unit, yaw);
    insect->yaw = yaw;
    position->z += FX_MulFunc(FX_MulFunc(InsectMotion_fx(insect->unk_16c), unit.z), 128);
    position->x += FX_MulFunc(FX_MulFunc(InsectMotion_fx(insect->unk_16c), unit.x), 128);
    if (position->x < insect->low[0] || position->x > insect->high[0]) {
        position->x = old.x;
    }
    if (position->z < insect->low[1] || position->z > insect->high[1]) {
        position->z = old.z;
    }
    if (position->z != old.z) {
        position->y -= position->z - old.z;
    }
    /* QUIRK: the game then puts y back when it is below 0x900 and above 0x1000, which it never
     * is: y is not limited. */
}
CLEAN_AS(func_ov004_02241084, InsectMotion_Drift)

/* func_ov004_022411a4: the animation of kinds 14, 15 and 26 played as the player comes near
 * (unk_50 a wait between two). Within 0xccd of the player, *frames is cleared and nothing else
 * happens. Kinds 14 and 15 face the player while waiting, play animation 9 when much alarmed,
 * and otherwise animation 4 (forwards from the start, or backwards from where it is) while the
 * player is in sight and animation 0 backwards when not; kind 26 goes from frame 0 to 1 to 2
 * while calm and awake and back to 0, then rest, when alarmed or asleep. */
void InsectMotion_ReactToPlayer(MuseumInsect *insect, short *frames)
{
    InsectSighting sighting;
    func_ov004_02244658(insect, &sighting);
    if (!sighting.seen) {
        return;
    }
    s16 alarm = insect->unk_9c;
    if (sighting.distance <= 0xccd) {
        *frames = 0;
        return;
    }
    if (insect->kind == 14 || insect->kind == 15) {
        if (insect->unk_50) {
            insect->yaw = Vec_YawTo(&insect->position, &sighting.player);
            insect->mode = MUSEUM_INSECT_MODE_REST;
        }
        if (alarm > 20) {
            InsectMotion_play(insect, 9, FRAME_CTRL_ONCE, 0x1000, (u16) InsectMotion_frame(insect));
            insect->unk_50 = 60;
        } else if (insect->unk_50) {
            insect->unk_50--;
        } else if (sighting.distance < insect->unk_a0) {
            unsigned int frame = InsectMotion_frame(insect);
            if (frame == 0) {
                InsectMotion_play(insect, 4, FRAME_CTRL_ONCE, 0x1000, 0);
                insect->unk_50 = 60;
            } else if (frame > 4) {
                InsectMotion_play(insect, 4, FRAME_CTRL_ONCE | FRAME_CTRL_REVERSE, 0x1000, (u16) frame);
            }
        } else {
            unsigned int frame = InsectMotion_frame(insect);
            if (frame != 0) {
                InsectMotion_play(insect, 0, FRAME_CTRL_ONCE | FRAME_CTRL_REVERSE, 0x1000, (u16) frame);
            }
        }
    } else if (insect->kind == 26) {
        unsigned int frame = InsectMotion_frame(insect);
        if (alarm > 20 || !insect->awake) {
            if (frame == 2) {
                InsectMotion_set_frame(insect, 1);
            } else if (frame == 1) {
                InsectMotion_set_frame(insect, 0);
                insect->mode = MUSEUM_INSECT_MODE_REST;
                insect->unk_50 = 60;
            }
        } else if (frame == 0 && !insect->unk_50) {
            InsectMotion_set_frame(insect, 1);
        } else if (frame == 1) {
            InsectMotion_set_frame(insect, 2);
        } else if (insect->unk_50) {
            insect->unk_50--;
        }
    }
}
CLEAN_AS(func_ov004_022411a4, InsectMotion_ReactToPlayer)

/* True after `limit` frames, or on a 20th frame after `early` frames one time in ten. */
static int InsectMotion_stop_after(int frames, int limit, int early)
{
    return frames > limit || (frames % 20 == 0 && InsectMotion_random(100) > 90 && frames > early);
}

/* func_ov004_02241350 (kinds 14, 15 and 26's frame): the reaction to the player, then a drift
 * (mode 4) of 80-160 frames (160-320 for kind 26) between rests; awake, the rests are short
 * (kind 26 rests on frame 2 of its animation), asleep up to 800 frames. */
void InsectMotion_UpdateDrifter(MuseumInsect *insect)
{
    short *frames = &insect->unk_168;
    InsectMotion_ReactToPlayer(insect, frames);
    ++*frames;
    if (insect->mode == INSECT_MOTION_MOVE) {
        InsectMotion_Drift(insect);
        int stop = insect->kind == 26 ? InsectMotion_stop_after(*frames, 320, 160) : InsectMotion_stop_after(*frames, 160, 80);
        if (stop) {
            insect->mode = MUSEUM_INSECT_MODE_REST;
            *frames = 0;
        }
    } else if (insect->kind == 26) {
        if (insect->awake && InsectMotion_frame(insect) == 2) {
            if (*frames > 160 || (*frames % 20 == 0 && InsectMotion_random(100) > 85 && *frames >= 40)) {
                *frames = 0;
                insect->mode = INSECT_MOTION_MOVE;
            }
        }
    } else if (insect->awake) {
        if (*frames > 80 || (*frames % 20 == 0 && InsectMotion_random(100) > 85)) {
            insect->mode = INSECT_MOTION_MOVE;
            *frames = 0;
        }
    } else if (*frames > 800 || (*frames % 100 == 0 && InsectMotion_random(100) > 90)) {
        insect->mode = INSECT_MOTION_MOVE;
        *frames = 0;
    }
}
CLEAN_AS(func_ov004_02241350, InsectMotion_UpdateDrifter)

/* func_ov004_022414a8 (kind 16's frame, and by its check kind 20's): the alarm followed. Kind 20 plays animation 4 from the
 * start when alarmed (or waiting, unk_50), and back to frame 0 otherwise. Awake and calm, the
 * insect's sound plays each time its wait runs out; alarmed, the wait is 60 frames. */
void InsectMotion_UpdateWatcher(MuseumInsect *insect)
{
    func_ov004_02244764(insect);
    if (insect->kind == 20) {
        if (insect->unk_9c >= insect->unk_9e || insect->unk_50 != 0) {
            if (InsectMotion_frame(insect) == 0) {
                InsectMotion_play(insect, 4, FRAME_CTRL_ONCE, 0x1000, 0);
                insect->unk_50 = 60;
            } else if (insect->unk_50 != 0) {
                insect->unk_50--;
            }
        } else {
            u16 frame = (u16) (insect->model.frames.frame >> 12);
            if (frame != 0 || InsectMotion_end(insect) != 0) {
                InsectMotion_play(insect, 0, FRAME_CTRL_ONCE | FRAME_CTRL_REVERSE, 0x1000, frame);
            }
        }
    }
    if (insect->awake) {
        if (insect->unk_9c < insect->unk_9e) {
            if (insect->unk_50 == 0) {
                func_ov004_02244be0(insect, 0);
            } else {
                insect->unk_50--;
            }
        } else {
            insect->unk_50 = 60;
        }
    }
}
CLEAN_AS(func_ov004_022414a8, InsectMotion_UpdateWatcher)

/* func_ov004_02241588 (mode 3 of a hoverer): a sway, *step counting away from 0 (its sign the
 * way, drawn at the start): the pitch tips 0xb6 each step and the yaw turns 0x16b, one way for
 * steps 1-6 and 19-24 (-7 to -18 going down), the other for steps 7-18 (-1 to -6 and -19 to
 * -24); after that, at rest. */
void InsectMotion_Sway(MuseumInsect *insect, short *step)
{
    s16 yaw = insect->yaw;
    s16 s = *step;
    if (s == 0) {
        if (InsectMotion_random(100) < 50) {
            *step += 1;
        } else {
            *step -= 1;
        }
    } else if ((s > 0 && s <= 6) || (s > 18 && s <= 24) || (s < -6 && s >= -18)) {
        if (s > 0) {
            *step += 1;
            insect->pitch = (s16) (insect->pitch + 0xb6);
        } else {
            *step -= 1;
            insect->pitch = (s16) (insect->pitch - 0xb6);
        }
        yaw = (s16) (yaw + 0x16b);
    } else if ((s > 6 && s <= 18) || (s < 0 && s >= -6) || (s < -18 && s >= -24)) {
        if (s > 0) {
            *step += 1;
            insect->pitch = (s16) (insect->pitch - 0xb6);
        } else {
            *step -= 1;
            insect->pitch = (s16) (insect->pitch + 0xb6);
        }
        yaw = (s16) (yaw - 0x16b);
    } else {
        *step = 0;
        insect->mode = MUSEUM_INSECT_MODE_REST;
    }
    insect->yaw = yaw;
}
CLEAN_AS(func_ov004_02241588, InsectMotion_Sway)

/* A hoverer's wobble up or down: steps 0-1 and 6-7 turn the yaw and pitch one way, 2-5 the
 * other, and each moves y by `dy`; after step 7, three times in ten the mode `next`, else
 * another round. */
static void InsectMotion_bob(MuseumInsect *insect, short *step, int dy, int next)
{
    s16 s = *step;
    if ((s >= 0 && s < 2) || (s >= 6 && s < 8)) {
        *step += 1;
        insect->yaw = (s16) (insect->yaw + 0x2aa);
        insect->pitch = (s16) (insect->pitch + 0xaa);
        insect->position.y += dy;
    } else if (s >= 2 && s < 6) {
        *step += 1;
        insect->yaw = (s16) (insect->yaw - 0x2aa);
        insect->pitch = (s16) (insect->pitch - 0xaa);
        insect->position.y += dy;
    } else if (InsectMotion_random(100) > 70) {
        insect->mode = (s16) next;
        *step = 0;
    } else if (*step >= 8) {
        *step = 0;
    }
}

/* func_ov004_02241680 (mode 1 of a hoverer): down 0x20 a step, to 0x100 below its height, then
 * at rest. */
void InsectMotion_Sink(MuseumInsect *insect, short *step)
{
    fx32 lowest = insect->unk_a8 - 0x100;
    InsectMotion_bob(insect, step, -0x20, MUSEUM_INSECT_MODE_REST);
    if (insect->position.y < lowest) {
        insect->position.y = lowest;
    }
}
CLEAN_AS(func_ov004_02241680, InsectMotion_Sink)

/* func_ov004_0224173c (mode 2 of a hoverer): up 0x20 a step, to 0x400 above its height, then
 * down (mode 1). */
void InsectMotion_Rise(MuseumInsect *insect, short *step)
{
    fx32 highest = insect->unk_a8 + 0x400;
    InsectMotion_bob(insect, step, 0x20, INSECT_MOTION_SINK);
    if (insect->position.y > highest) {
        insect->position.y = highest;
    }
}
CLEAN_AS(func_ov004_0224173c, InsectMotion_Rise)

/* func_ov004_022417f8: kind 9 at rest: its animation held at frame 9 (from frame 13, or before
 * frame 9), and after the rooms' 80th frame sometimes run on to 14 (awake: one time in thirteen
 * a frame; asleep: on every fifth frame). */
void InsectMotion_IdleKind9(MuseumInsect *insect)
{
    unsigned int frame = InsectMotion_frame(insect);
    if (frame == 13 || frame < 9) {
        InsectMotion_play(insect, 9, FRAME_CTRL_ONCE, 0, 9);
    }
    u8 clock = data_ov004_02259a24;
    if (clock > 80 && (insect->awake || clock % 5 == 0)) {
        if (InsectMotion_random(100) > 92 && frame < 10) {
            InsectMotion_play(insect, 14, FRAME_CTRL_ONCE, 0x1000, 9);
        }
    }
}
CLEAN_AS(func_ov004_022417f8, InsectMotion_IdleKind9)

/* func_ov004_02241894 (kinds 9 and 11's frame): a sway, a rise or a sink by the mode; at rest
 * (kind 9 idling), now and then (awake: on a 20th frame, three times in ten; asleep: on a 40th,
 * three times in twenty) a sway or a rise. */
void InsectMotion_UpdateHoverer(MuseumInsect *insect)
{
    switch (insect->mode) {
        case INSECT_MOTION_TURN:
            InsectMotion_Sway(insect, &insect->unk_168);
            return;
        case INSECT_MOTION_RISE:
            InsectMotion_Rise(insect, &insect->unk_168);
            return;
        case INSECT_MOTION_SINK:
            InsectMotion_Sink(insect, &insect->unk_168);
            return;
    }
    if (insect->kind == 9) {
        InsectMotion_IdleKind9(insect);
        return;
    }
    if (insect->awake) {
        if ((int) data_ov004_02259a24 % 20 != 0 || InsectMotion_random(100) < 70) {
            return;
        }
    } else if ((int) data_ov004_02259a24 % 40 != 0 || InsectMotion_random(100) < 85) {
        return;
    }
    if (InsectMotion_random(100) < 50) {
        insect->mode = INSECT_MOTION_TURN;
    } else {
        insect->mode = INSECT_MOTION_RISE;
    }
}
CLEAN_AS(func_ov004_02241894, InsectMotion_UpdateHoverer)

/* func_ov004_0224193c: the yaw swung 0x222 a step between -0xaaa and 0xaaa (the way, unk_170,
 * drawn at step 0); *step counted. Always 1. */
int InsectMotion_Swing(MuseumInsect *insect, short *step)
{
    s16 yaw = insect->yaw;
    if (*step == 0) {
        insect->unk_170 = InsectMotion_random(100) > 50 ? 0 : 1;
    }
    if (insect->unk_170) {
        if (yaw > 0xaaa) {
            insect->unk_170 = 0;
        }
    } else if (yaw < -0xaaa) {
        insect->unk_170 = 1;
    }
    insect->yaw = (s16) (insect->unk_170 ? yaw + 0x222 : yaw - 0x222);
    *step += 1;
    return 1;
}
CLEAN_AS(func_ov004_0224193c, InsectMotion_Swing)

/* func_ov004_022419c4: there is a player within 0x4800 of the insect in x and z. */
int InsectMotion_PlayerWithin(MuseumInsect *insect)
{
    Actor *player = SessionPlayers_ActorOf(4);
    return player != NULL && Vec_DistanceXZ(&player->position, &insect->position) < 0x4800;
}
CLEAN_AS(func_ov004_022419c4, InsectMotion_PlayerWithin)

/* func_ov004_022419f8 (kind 53's frame): with the player near, after its wait (unk_98) it shows
 * and plays animation 33 (mode 1); at frame 32 it swings (mode 18) for 40-80 frames, then plays
 * animation 57 from frame 32 (mode 2) rolling 91 either way each frame, and at frame 56 it is
 * hidden again at its x (unk_4c) with a wait of 60-120 frames. Without a player near, its
 * animation is set to stop at its end. */
void InsectMotion_UpdateKind53(MuseumInsect *insect)
{
    short *wait = &insect->unk_98;
    switch (insect->mode) {
        case 2:
            if (insect->unk_170) {
                insect->unk_170 = 0;
                insect->roll = 91;
            } else {
                insect->unk_170 = 1;
                insect->roll = -91;
            }
            if (InsectMotion_frame(insect) == 56) {
                insect->mode = MUSEUM_INSECT_MODE_REST;
                insect->roll = 0;
                insect->position.x = insect->unk_4c;
                InsectMotion_set_alpha(insect, 0);
                insect->unk_98 = (s16) ((InsectMotion_random(4) + 3) * 20);
            }
            break;
        case 1:
            if (InsectMotion_frame(insect) == 32) {
                insect->unk_98 = (s16) ((InsectMotion_random(3) + 2) * 20);
                insect->mode = 18;
                insect->unk_168 = 0;
            }
            break;
        case 18:
            if (InsectMotion_Swing(insect, &insect->unk_168) && *wait <= 0) {
                insect->yaw = 0;
                insect->mode = 2;
                InsectMotion_play(insect, 57, FRAME_CTRL_ONCE, 0x1000, 32);
            } else {
                --*wait;
            }
            break;
        default:
            if (InsectMotion_PlayerWithin(insect)) {
                if (*wait > 0) {
                    --*wait;
                } else {
                    insect->mode = 1;
                    insect->unk_9c = 0;
                    InsectMotion_play(insect, 33, FRAME_CTRL_ONCE, 0x1000, 0);
                    InsectMotion_set_alpha(insect, 31);
                }
            } else {
                insect->model.frames.flags = FRAME_CTRL_ONCE;
            }
            break;
    }
}
CLEAN_AS(func_ov004_022419f8, InsectMotion_UpdateKind53)

/* func_ov004_02241b5c: `src` at height 0, its x and z kept within `whole`/64 units either
 * way. */
void InsectMotion_ClampXZ(Vec3 *dst, const Vec3 *src, int whole)
{
    fx32 limit = FX_MulFunc(InsectMotion_fx(whole), 0x40);
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
    dst->y = 0;
    if (src->x > limit) {
        dst->x = limit;
    } else if (src->x < -limit) {
        dst->x = -limit;
    }
    if (src->z > limit) {
        dst->z = limit;
    } else if (src->z < -limit) {
        dst->z = -limit;
    }
}
CLEAN_AS(func_ov004_02241b5c, InsectMotion_ClampXZ)

/* func_ov004_02241ba8: a walk step: the turn from walls (InsectMotion_AvoidWalls), whose result
 * is given back; while turning from one, only kind 52 steps on. A step is 5 units plus the
 * speed (4 for kind 30) along the yaw; kinds 48 and 52 step back where the ground there is above
 * 0x200 (kind 52 then turning 0x38e either way unless it was already turning). The yaw waggles
 * (0x71c for kind 55, else 0xaaa) with the steps, and kinds 54 and 55 make their sound. */
int InsectMotion_Walk(MuseumInsect *insect)
{
    Vec3 *position = &insect->position;
    Vec3 previous = *position;
    Vec3 direction;
    short *steps = &insect->unk_168;
    int length = 5;
    int blocked_by = InsectMotion_AvoidWalls(insect);
    u8 kind = (u8) insect->kind;
    func_ov004_02244fb8(&direction, insect->yaw);
    if (kind == 30) {
        length = 4;
    }
    if (blocked_by && kind != 52) {
        return blocked_by;
    }
    fx32 step = InsectMotion_fx(length + insect->unk_16c);
    position->x += FX_MulFunc(step, direction.x);
    position->z += FX_MulFunc(step, direction.z);
    if (kind == 52 || kind == 48) {
        CollisionGround ground;
        CollisionGround_Init(&ground, position, 0, 0);
        int high = CollisionGround_GetHeight(&ground, 0) > 0x200;
        CollisionGround_Destroy(&ground);
        if (high) {
            if (!blocked_by && kind == 52) {
                if (InsectMotion_random(100) < 50) {
                    insect->yaw = (s16) (insect->yaw + 0x38e);
                } else {
                    insect->yaw = (s16) (insect->yaw - 0x38e);
                }
            }
            *position = previous;
        }
    }
    int waggle = kind == 55 ? 0x71c : 0xaaa;
    int n = *steps;
    if (n == 0) {
        insect->yaw = (s16) (insect->yaw + FX_MulFunc(waggle, 0x800));
    } else if (n % 4 == 0) {
        insect->yaw = (s16) (waggle + insect->yaw);
    } else if (n % 2 == 0) {
        insect->yaw = (s16) (insect->yaw - waggle);
    }
    (*steps)++;
    if (kind == 54 || kind == 55) {
        func_ov004_02244be0(insect, 0);
    }
    return blocked_by;
}
CLEAN_AS(func_ov004_02241ba8, InsectMotion_Walk)

/* func_ov004_02241d20 (mode 4 of a hopper): a walk step; facing a seen player, within 0x1800 it
 * hops (unk_98 counting the hop's frames) when the player lies close to straight ahead, and
 * within 0x2800 it turns towards the player while not turning from a wall. A hop rises and falls
 * as 0x99a t - 0xcd t^2 (t the frames) and ends at height 3; while hopping its animation runs
 * between frames 1 and 2 and its hop sound plays, otherwise its other sound and frame 0. At the
 * end of its walking time, and not hopping, it rests 60-240 frames. */
void InsectMotion_Hop(MuseumInsect *insect, InsectSighting *sighting)
{
    short *hop = &insect->unk_98;
    Vec3 *position = &insect->position;
    Vec3 to_player;
    Vec3 ahead;
    int turning = InsectMotion_Walk(insect);
    s16 yaw = insect->yaw;
    Vec_Subtract(&to_player, &sighting->player, position);
    func_ov004_02244fb8(&ahead, yaw);
    Vec_NormalizeNonZero(&ahead);
    Vec_NormalizeNonZero(&to_player);
    fx32 facing = Vec_DotXZ(&ahead, &to_player);
    if (sighting->seen && facing > 0) {
        if (Vec_DistanceXZ(position, &sighting->player) < 0x1800) {
            if (facing > data_02139d9c[1]) {
                *hop = (short) (*hop + 1);
            }
        } else if (Vec_DistanceXZ(position, &sighting->player) < 0x2800 && turning == 0) {
            Approach_S16Wrapped(&yaw, Vec_YawTo(&sighting->player, position), 0xaaa);
            insect->yaw = yaw;
        }
    }
    if (*hop > 0) {
        fx32 t = InsectMotion_fx(*hop);
        position->y = FX_MulFunc(0x99a - FX_MulFunc(0xcd, t), t);
        if (position->y < 3) {
            position->y = 3;
            *hop = 0;
        } else {
            *hop = (short) (*hop + 1);
        }
        func_ov004_02244f20(insect);
        func_ov004_02244be0(insect, 1);
    } else {
        func_ov004_02244be0(insect, 0);
        if (InsectMotion_frame(insect) != 0) {
            InsectMotion_set_frame(insect, 0);
        }
    }
    if (func_ov004_02244c20(insect) && *hop == 0) {
        insect->timer = 20 * (InsectMotion_random(10) + 3);
        insect->mode = MUSEUM_INSECT_MODE_REST;
    }
}
CLEAN_AS(func_ov004_02241d20, InsectMotion_Hop)

/* func_ov004_02241e88 (kind 52's frame): its alarm held to 80. Alarmed, it turns from the
 * player (mode 3, 40-100 frames) and walks; at the end of a rest it walks 20-80 frames. The
 * first time a moving player comes within 0xe66 while it is not hopping, the museum's lone
 * insect appears (EtcMuseum_SpawnLone). */
void InsectMotion_UpdateHopper(MuseumInsect *insect)
{
    InsectSighting sighting;
    int alarm = func_ov004_02244658(insect, &sighting);
    if (insect->unk_9c > 80) {
        insect->unk_9c = 80;
    }
    switch (insect->mode) {
        case INSECT_MOTION_MOVE:
            InsectMotion_Hop(insect, &sighting);
            break;
        case INSECT_MOTION_TURN: {
            s16 yaw = insect->yaw;
            if (Approach_S16Wrapped(&yaw, insect->unk_ac, 0x2000)) {
                insect->mode = INSECT_MOTION_MOVE;
            }
            insect->yaw = yaw;
            break;
        }
        default:
            if (alarm == INSECT_MOTION_ALARM_ABOVE) {
                insect->unk_ac = Vec_YawTo(&sighting.player, &insect->position);
                insect->timer = 20 * (InsectMotion_random(4) + 2);
                insect->mode = INSECT_MOTION_TURN;
            } else if (func_ov004_02244c20(insect)) {
                insect->mode = INSECT_MOTION_MOVE;
                insect->timer = 20 * (InsectMotion_random(4) + 1);
            }
            break;
    }
    if (insect->unk_4c == 0 && sighting.seen && sighting.player_speed > 0 && insect->unk_98 == 0) {
        if (Vec_DistanceXZ(&sighting.player, &insect->position) < 0xe66) {
            EtcMuseum_SpawnLone();
            insect->unk_4c = 1;
        }
    }
}
CLEAN_AS(func_ov004_02241e88, InsectMotion_UpdateHopper)

/* func_ov004_02241f88 (kinds 35 and 56's frame): at the end of a rest its animation speeds up
 * to full (mode 4), then plays until the end of its time (mode 5) and stops for a rest. Kind 35
 * draws the times (rests of 40-80 frames awake, 120-240 asleep; plays of 40-200 frames) and
 * hands each to its partner, kind 56 (unk_98), which takes it from there.
 * REQUIRES: kind 56's entry is in use while kind 35's is (InsectRoom_FindPartner). */
void InsectMotion_UpdatePartners(MuseumInsect *insect)
{
    u8 kind = (u8) insect->kind;
    MuseumInsect *partner = NULL;
    if (kind == MUSEUM_INSECT_WITH_PARTNER) {
        partner = InsectRoom_FindPartner();
    }
    switch (insect->mode) {
        case INSECT_MOTION_MOVE: {
            int speed = insect->model.frames.speed;
            if (!Approach_EaseS32MinMax(&speed, 0x1000, 0x66, 0x1000, 0x29)) {
                insect->mode = 5;
            }
            insect->model.frames.speed = speed;
            break;
        }
        case 5:
            if (func_ov004_02244c20(insect)) {
                insect->mode = MUSEUM_INSECT_MODE_REST;
                insect->model.frames.speed = 0;
                if (kind == MUSEUM_INSECT_WITH_PARTNER) {
                    int rest = (s16) (20 * (InsectMotion_random(3) + 2));
                    if (!insect->awake) {
                        rest = (s16) (3 * rest);
                    }
                    insect->timer = rest;
                    partner->unk_98 = (s16) rest;
                } else {
                    insect->timer = insect->unk_98;
                }
            }
            break;
        default:
            if (func_ov004_02244c20(insect)) {
                insect->mode = INSECT_MOTION_MOVE;
                if (kind == MUSEUM_INSECT_WITH_PARTNER) {
                    int play = (s16) (20 * (InsectMotion_random(9) + 2));
                    insect->timer = play;
                    partner->unk_98 = (s16) play;
                } else if (insect->unk_98 > 0) {
                    insect->timer = insect->unk_98;
                }
            }
            break;
    }
}
CLEAN_AS(func_ov004_02241f88, InsectMotion_UpdatePartners)

/* func_ov004_02242078: while the player is seen and the insect alarmed (or for the 60 frames
 * after), it turns towards the player 0x38e a frame, and kind 55 runs its animation to frame 3
 * of 11, to 10 of 14, or back to 10 from 13; 1 then, else 0. */
int InsectMotion_FacePlayer(MuseumInsect *insect)
{
    InsectSighting sighting;
    short *after = &insect->unk_98;
    int alarm = func_ov004_02244658(insect, &sighting);
    if (!sighting.seen || (alarm != INSECT_MOTION_ALARM_ABOVE && *after == 0)) {
        return 0;
    }
    int to_player = Vec_YawTo(&insect->position, &sighting.player);
    s16 yaw = insect->yaw;
    Approach_S16Wrapped(&yaw, to_player, 0x38e);
    insect->yaw = yaw;
    if (insect->kind == MUSEUM_INSECT_PAIR_SECOND) {
        u16 end = (u16) (insect->model.frames.end >> 12);
        u16 frame = (u16) InsectMotion_frame(insect);
        if (end < 11 && frame <= 2) {
            InsectMotion_play(insect, 11, FRAME_CTRL_ONCE, 0x1000, 3);
        } else if (end < 14 && frame < 10) {
            InsectMotion_play(insect, 14, 0, 0x1000, 10);
        } else if (frame == 13 && end > 10) {
            InsectMotion_set_frame(insect, 10);
        }
    }
    if (*after > 0) {
        *after = (short) (*after - 1);
    } else {
        *after = 60;
    }
    return 1;
}
CLEAN_AS(func_ov004_02242078, InsectMotion_FacePlayer)

/* func_ov004_02242180 (mode 4 of the pair, alone): a walk step, kept in the bounds; at a bound it
 * turns (mode 3), and at the end of its time it rests (20-120 frames awake, 100-680 asleep)
 * with a new yaw to turn to, away from a wall it met or a random turn of up to 16 steps. */
void InsectMotion_PairWalk(MuseumInsect *insect)
{
    int blocked_by = InsectMotion_Walk(insect);
    if (func_ov004_02244e38(insect, &insect->position)) {
        insect->mode = INSECT_MOTION_TURN;
    } else if (func_ov004_02244c20(insect)) {
        if (blocked_by) {
            insect->unk_ac = func_ov004_022447c0(insect->yaw, blocked_by);
        } else {
            insect->unk_ac = InsectMotion_RandomTurn(16);
        }
        insect->unk_9a = 0;
        insect->mode = MUSEUM_INSECT_MODE_REST;
        if (insect->awake) {
            insect->timer = (s16) (20 * (InsectMotion_random(6) + 1));
        } else {
            insect->timer = (s16) (20 * (InsectMotion_random(30) + 5));
        }
    }
}
CLEAN_AS(func_ov004_02242180, InsectMotion_PairWalk)

/* func_ov004_02242228 (mode 23 of the pair): within 0x2000 of each other, the two face each
 * other, waggle, and each steps back four facing steps (func_ov004_02244fb8); apart, at the end
 * of its time the insect rests. */
void InsectMotion_PairBackOff(MuseumInsect *insect)
{
    MuseumInsect *other = InsectRoom_FindPairSecond();
    Vec3 *mine = &insect->position;
    Vec3 *theirs = &other->position;
    short *frames = &insect->unk_168;
    Vec3 their_facing;
    Vec3 my_facing;
    Vec3 step;
    if (Vec_DistanceXZ(mine, theirs) < 0x2000) {
        int their_yaw = Vec_YawTo(theirs, mine);
        other->yaw = (s16) their_yaw;
        func_ov004_02244fb8(&their_facing, their_yaw);
        InsectMotion_Waggle(other, their_yaw, *frames);
        int my_yaw = Vec_YawTo(mine, theirs);
        insect->yaw = (s16) my_yaw;
        func_ov004_02244fb8(&my_facing, my_yaw);
        InsectMotion_Waggle(insect, my_yaw, *frames);
        Vec_ScaleCopy(&step, &my_facing, 0x4000);
        VEC_Subtract(mine, &step, mine);
        Vec_ScaleCopy(&step, &their_facing, 0x4000);
        VEC_Subtract(theirs, &step, theirs);
        *frames = (short) (*frames + 1);
    } else if (func_ov004_02244c20(insect)) {
        insect->mode = MUSEUM_INSECT_MODE_REST;
        *frames = 0;
    }
}
CLEAN_AS(func_ov004_02242228, InsectMotion_PairBackOff)

/* func_ov004_022422fc (mode 24 of the pair): at the end of its time it rests, and the other's
 * animation runs at full speed again. */
void InsectMotion_PairPause(MuseumInsect *insect)
{
    if (func_ov004_02244c20(insect)) {
        insect->mode = MUSEUM_INSECT_MODE_REST;
        InsectRoom_FindPairSecond()->model.frames.speed = 0x1000;
        insect->unk_168 = 0;
    }
}
CLEAN_AS(func_ov004_022422fc, InsectMotion_PairPause)

/* The way round of a circling (unk_170, drawn again every tenth frame) and how far round it has
 * gone (*offset, 0 to 0x1554): `angle` moved 0xb6 that way, or the way turned at an end. */
static int InsectMotion_circle_step(MuseumInsect *insect, int angle, int *offset)
{
    if ((int) data_ov004_02259a24 % 10 == 0) {
        insect->unk_170 = InsectMotion_random(100) > 50 ? 1 : 0;
    }
    u8 way = insect->unk_170;
    if (way && *offset < 0x1554) {
        angle = (s16) (angle + 0xb6);
        *offset += 0xb6;
    } else if (!way && *offset > 0) {
        angle = (s16) (angle - 0xb6);
        *offset -= 0xb6;
    } else if (way) {
        insect->unk_170 = 0;
    } else {
        insect->unk_170 = 1;
    }
    return angle;
}

/* `around` + `distance` along `angle`, in x and z. */
static void InsectMotion_put_around(Vec3 *point, const Vec3 *around, int angle, fx32 distance)
{
    int index = ((u16) angle >> 4) * 2;
    point->x = around->x + FX_MulFunc(FX_SinCosTable_[index], distance);
    point->z = around->z + FX_MulFunc(FX_SinCosTable_[index + 1], distance);
}

/* func_ov004_02242334 (mode 22 of the pair): the insect circles the other at the distance from
 * its kept point, the other turned along; at the end of its time it rests. */
void InsectMotion_PairCircleOther(MuseumInsect *insect)
{
    MuseumInsect *other = InsectRoom_FindPairSecond();
    Vec3 *mine = &insect->position;
    Vec3 *theirs = &other->position;
    int angle = Vec_YawTo(theirs, mine);
    short *frames = &insect->unk_168;
    int offset = insect->unk_4c;
    angle = InsectMotion_circle_step(insect, angle, &offset);
    fx32 distance = Vec_DistanceXZ(&insect->kept, theirs);
    InsectMotion_put_around(mine, theirs, angle, distance);
    other->yaw = (s16) angle;
    int yaw = Vec_YawTo(mine, theirs);
    insect->yaw = (s16) yaw;
    InsectMotion_Waggle(insect, yaw, *frames);
    insect->unk_4c = offset;
    *frames = (short) (*frames + 1);
    if (func_ov004_02244c20(insect)) {
        insect->mode = MUSEUM_INSECT_MODE_REST;
        *frames = 0;
    }
}
CLEAN_AS(func_ov004_02242334, InsectMotion_PairCircleOther)

/* func_ov004_02242470 (mode 21 of the pair): the other circles this insect at the distance from
 * its kept point, waggling; at the end of this one's time it rests. */
void InsectMotion_PairCircledBy(MuseumInsect *insect)
{
    MuseumInsect *other = InsectRoom_FindPairSecond();
    Vec3 *mine = &insect->position;
    Vec3 *theirs = &other->position;
    int angle = Vec_YawTo(mine, theirs);
    short *frames = &insect->unk_168;
    int offset = insect->unk_4c;
    angle = InsectMotion_circle_step(insect, angle, &offset);
    fx32 distance = Vec_DistanceXZ(&other->kept, mine);
    InsectMotion_put_around(theirs, mine, angle, distance);
    insect->yaw = (s16) angle;
    s16 their_yaw = Vec_YawTo(theirs, mine);
    other->yaw = their_yaw;
    InsectMotion_Waggle(other, their_yaw, *frames);
    insect->unk_4c = offset;
    ++*frames;
    if (func_ov004_02244c20(insect)) {
        insect->mode = MUSEUM_INSECT_MODE_REST;
        *frames = 0;
    }
}
CLEAN_AS(func_ov004_02242470, InsectMotion_PairCircledBy)

/* func_ov004_022425a8 (mode 20 of the pair): the two jostle. Every 15th frame a choice (unk_4c,
 * 0-99) and a side (unk_98: 5-9 for the other insect, as many negative for this one) are drawn;
 * the side counts towards 0. The one of the side moves, by facing steps (func_ov004_02244fb8)
 * along the line between them: close (within 0xccd), a choice below 30 moves this one 2 steps
 * towards the other or the other 2 steps back, below 60 this one 2 steps back or the other 2
 * towards it; while beyond 0x99a, far (beyond 0x5800) or below 80, 10 steps towards; nearer
 * than 0x5800, below 90 one step back and below 100 5 steps back. After the first case the other
 * only turns to face this one, after the second this one only faces the other; otherwise both
 * waggle. At the end of its time the insect rests. */
void InsectMotion_PairJostle(MuseumInsect *insect)
{
    MuseumInsect *other = InsectRoom_FindPairSecond();
    Vec3 *mine = &insect->position;
    Vec3 *theirs = &other->position;
    int their_yaw = Vec_YawTo(theirs, mine);
    short *frames = &insect->unk_168;
    int choice = insect->unk_4c;
    fx32 distance = Vec_DistanceXZ(mine, theirs);
    int waggle_other = 1;
    int waggle_mine = 1;
    short *side = &insect->unk_98;
    Vec3 their_facing;
    Vec3 my_facing;
    Vec3 step;
    func_ov004_02244fb8(&their_facing, their_yaw);
    func_ov004_02244fb8(&my_facing, Vec_YawTo(mine, theirs));
    if ((int) data_ov004_02259a24 % 15 == 0) {
        choice = InsectMotion_random(100);
        insect->unk_4c = choice;
        *side = (short) (InsectMotion_random(5) + 5);
        if (InsectMotion_random(100) > 50) {
            *side = (short) -*side;
        }
    }
    if (*side > 0) {
        --*side;
    } else if (*side < 0) {
        ++*side;
    }
    if (choice < 30 && distance < 0xccd) {
        waggle_other = 0;
        if (*side <= 0) {
            Vec_ScaleCopy(&step, &my_facing, 0x2000);
            VEC_Add(mine, &step, mine);
        } else {
            Vec_ScaleCopy(&step, &their_facing, 0x2000);
            VEC_Subtract(theirs, &step, theirs);
        }
    } else if (choice < 60 && distance < 0xccd) {
        waggle_mine = 0;
        if (*side <= 0) {
            Vec_ScaleCopy(&step, &my_facing, 0x2000);
            VEC_Subtract(mine, &step, mine);
        } else {
            Vec_ScaleCopy(&step, &their_facing, 0x2000);
            VEC_Add(theirs, &step, theirs);
        }
    } else if ((distance > 0x5800 || choice < 80) && distance > 0x99a) {
        if (*side <= 0) {
            Vec_ScaleCopy(&step, &my_facing, 0xa000);
            VEC_Add(mine, &step, mine);
        } else {
            Vec_ScaleCopy(&step, &their_facing, 0xa000);
            VEC_Add(theirs, &step, theirs);
        }
    } else if (distance < 0x5800) {
        if (choice < 90) {
            if (*side <= 0) {
                VEC_Subtract(mine, &my_facing, mine);
            } else {
                VEC_Subtract(theirs, &their_facing, theirs);
            }
        } else if (choice < 100) {
            if (*side <= 0) {
                Vec_ScaleCopy(&step, &my_facing, 0x5000);
                VEC_Subtract(mine, &step, mine);
            } else {
                Vec_ScaleCopy(&step, &their_facing, 0x5000);
                VEC_Subtract(theirs, &step, theirs);
            }
        }
    }
    if (waggle_mine) {
        InsectMotion_Waggle(insect, Vec_YawTo(mine, theirs), *frames);
    } else {
        insect->yaw = Vec_YawTo(mine, theirs);
    }
    if (waggle_other) {
        InsectMotion_Waggle(other, their_yaw, *frames);
    } else {
        other->yaw = Vec_YawTo(theirs, mine);
    }
    ++*frames;
    if (func_ov004_02244c20(insect)) {
        insect->mode = MUSEUM_INSECT_MODE_REST;
        *frames = 0;
    }
}
CLEAN_AS(func_ov004_022425a8, InsectMotion_PairJostle)

/* The kept point of `insect` set to its position, and a way round drawn for `circler`. */
static void InsectMotion_keep_place(MuseumInsect *insect, MuseumInsect *circler)
{
    insect->kept.x = insect->position.x;
    insect->kept.y = insect->position.y;
    insect->kept.z = insect->position.z;
    circler->unk_170 = InsectMotion_random(100) > 50 ? 0 : 1;
}

/* func_ov004_02242820: kinds 54 and 55 together. Both are kept in their bounds; kind 55 runs its
 * animation as InsectMotion_FacePlayer does (with its own frames) and gives 0. Kind 54, at
 * rest, turns to face the other and, once both face each other, draws what the two do next, for
 * both: a jostle (mode 20, 40-180 frames), the other circling it (21), it circling the other
 * (22), backing off (23) or a pause with the other's animation stopped (24); 0 while turning,
 * else 1. */
int InsectMotion_PairChoose(MuseumInsect *insect)
{
    func_ov004_02244e38(insect, &insect->position);
    if (insect->kind == MUSEUM_INSECT_PAIR_SECOND) {
        u16 end = (u16) (insect->model.frames.end >> 12);
        u16 frame = (u16) InsectMotion_frame(insect);
        if (end < 11 && frame <= 2) {
            InsectMotion_play(insect, 11, FRAME_CTRL_ONCE, 0x1000, 3);
        } else if (end < 14 && frame < 11) {
            InsectMotion_play(insect, 14, 0, 0x1000, 10);
        } else if (end > 11 && frame == 13) {
            InsectMotion_set_frame(insect, 10);
        }
        return 0;
    }
    if (insect->mode == MUSEUM_INSECT_MODE_REST) {
        MuseumInsect *other = InsectRoom_FindPairSecond();
        u8 choice = (u8) InsectMotion_random(100);
        short *side = &insect->unk_98;
        if (!InsectMotion_PairFaceEachOther(insect, other)) {
            return 0;
        }
        if (choice < 20) {
            insect->timer = (InsectMotion_random(8) + 2) * 20;
            insect->mode = 20;
        } else if (choice < 35) {
            insect->timer = (InsectMotion_random(4) + 1) * 20;
            insect->mode = 21;
            InsectMotion_keep_place(other, insect);
        } else if (choice < 50) {
            insect->timer = (InsectMotion_random(4) + 1) * 20;
            insect->mode = 22;
            InsectMotion_keep_place(insect, insect);
        } else if (choice < 70) {
            insect->timer = (InsectMotion_random(4) + 1) * 20;
            insect->mode = 23;
        } else {
            insect->timer = (InsectMotion_random(8) + 1) * 20;
            insect->mode = 24;
            other->model.frames.speed = 0;
        }
        insect->unk_4c = 0;
        *side = (short) (InsectMotion_random(5) + 5);
        if (InsectMotion_random(100) > 50) {
            *side = (short) -*side;
        }
        other->unk_168 = 0;
        other->mode = insect->mode;
        func_ov004_02244e38(other, &other->position);
    }
    return 1;
}
CLEAN_AS(func_ov004_02242820, InsectMotion_PairChoose)

/* func_ov004_02242a28: `a` and `b` turned towards each other 0xaaa; 1 once both face. */
int InsectMotion_PairFaceEachOther(MuseumInsect *a, MuseumInsect *b)
{
    s16 yaw_a = a->yaw;
    s16 yaw_b = b->yaw;
    u8 facing = (u8) Approach_S16Wrapped(&yaw_b, Vec_YawTo(&b->position, &a->position), 0xaaa);
    facing &= Approach_S16Wrapped(&yaw_a, Vec_YawTo(&a->position, &b->position), 0xaaa);
    a->yaw = yaw_a;
    b->yaw = yaw_b;
    return facing != 0;
}
CLEAN_AS(func_ov004_02242a28, InsectMotion_PairFaceEachOther)

/* func_ov004_02242a9c: the yaw set to `yaw` waggled by 0x71c (one way every fourth `frame`, the
 * other on the other even ones, odd frames unchanged), and the insect's sound. */
void InsectMotion_Waggle(MuseumInsect *insect, int yaw, int frame)
{
    if (frame % 4 == 0) {
        insect->yaw = (s16) (yaw + 0x71c);
    } else if (frame % 2 == 0) {
        insect->yaw = (s16) (yaw - 0x71c);
    }
    func_ov004_02244be0(insect, 0);
}
CLEAN_AS(func_ov004_02242a9c, InsectMotion_Waggle)

/* func_ov004_02242ae4 (kinds 54 and 55's frame): together, their shared choice
 * (InsectMotion_PairChoose); alone, facing the player when alarmed (kind 55 running its
 * animation back to frame 3). Then the mode: the pair's (20-24), a walk (4), or a turn (3, or
 * 15 once a wall was met: away from it); at the end of a rest, a turn of up to 16 steps and a
 * walk of 20-60 frames. */
void InsectMotion_UpdatePair(MuseumInsect *insect)
{
    if (insect->paired) {
        if (!InsectMotion_PairChoose(insect)) {
            return;
        }
    } else {
        if (InsectMotion_FacePlayer(insect) == 1) {
            return;
        }
        if (insect->kind == MUSEUM_INSECT_PAIR_SECOND) {
            unsigned int frame = InsectMotion_frame(insect);
            if (frame > 3) {
                InsectMotion_play(insect, 3, FRAME_CTRL_ONCE | FRAME_CTRL_REVERSE, 0x1000, (u16) frame);
            } else if (frame == 3) {
                InsectMotion_play(insect, 3, 0, 0x1000, 0);
            }
        }
    }
    switch (insect->mode) {
        case 20:
            InsectMotion_PairJostle(insect);
            break;
        case 21:
            InsectMotion_PairCircledBy(insect);
            break;
        case 22:
            InsectMotion_PairCircleOther(insect);
            break;
        case 23:
            InsectMotion_PairBackOff(insect);
            break;
        case 24:
            InsectMotion_PairPause(insect);
            break;
        case INSECT_MOTION_MOVE:
            InsectMotion_PairWalk(insect);
            break;
        case INSECT_MOTION_TURN:
        case INSECT_MOTION_TURN_AWAY: {
            int blocked_by = func_ov004_02245188(insect);
            if (blocked_by && insect->mode == INSECT_MOTION_TURN) {
                insect->unk_ac = func_ov004_022447c0(insect->yaw, blocked_by);
                insect->mode = INSECT_MOTION_TURN_AWAY;
            } else {
                s16 yaw = insect->yaw;
                if (Approach_S16Wrapped(&yaw, insect->unk_ac, 0x71c)) {
                    insect->mode = INSECT_MOTION_MOVE;
                }
                insect->yaw = yaw;
            }
            break;
        }
        default:
            if (func_ov004_02244c20(insect)) {
                insect->unk_9a = 0;
                insect->mode = INSECT_MOTION_TURN;
                insect->timer = (s16) ((InsectMotion_random(3) + 1) * 20);
                s16 yaw = insect->yaw;
                insect->unk_ac = (s16) (InsectMotion_RandomTurn(16) + yaw);
            }
            break;
    }
}
CLEAN_AS(func_ov004_02242ae4, InsectMotion_UpdatePair)

/* func_ov004_02242c64 (mode 0 of kind 8): a hover about the anchor, 48 times the speed a frame
 * in x and in y, each one way or the other (unk_ae and unk_170); seven times in ten the way in
 * y is turned every tenth frame, else the way in x every fifth. Beyond 0x1000 in x or 0x800 in
 * y from the anchor, that coordinate goes back and its way turns. */
void InsectMotion_Hover(MuseumInsect *insect)
{
    u8 in_x = insect->unk_ae;
    Vec3 *position = &insect->position;
    const Vec3 *anchor = &insect->anchor;
    u8 in_y = insect->unk_170;
    Vec3 old = *position;
    if (InsectMotion_random(100) > 30) {
        int clock = data_ov004_02259a24;
        if (clock % 10 == 0) {
            insect->unk_170 = !in_y;
        } else if (clock % 5 == 0) {
            insect->unk_ae = !in_x;
        }
    }
    if (in_x) {
        position->x += 48 * insect->unk_16c;
    } else {
        position->x -= 48 * insect->unk_16c;
    }
    if (in_y) {
        position->y += 48 * insect->unk_16c;
    } else {
        position->y -= 48 * insect->unk_16c;
    }
    fx32 off = position->x - anchor->x;
    if (off < 0) {
        off = -off;
    }
    if (off > 0x1000) {
        insect->unk_ae = !in_x;
        position->x = old.x;
    }
    off = position->y - anchor->y;
    if (off < 0) {
        off = -off;
    }
    if (off > 0x800) {
        insect->unk_170 = !in_y;
        position->y = old.y;
    }
}
CLEAN_AS(func_ov004_02242c64, InsectMotion_Hover)

/* func_ov004_02242d84 (kind 8's frame): the hover (mode 0); in any other mode it hovers again
 * once awake, and asleep plays animation 8 now and then (every 40th frame, one time in five). */
void InsectMotion_UpdateHovering(MuseumInsect *insect)
{
    if (insect->mode == 0) {
        InsectMotion_Hover(insect);
    } else if (insect->awake) {
        insect->unk_9a = 0;
        insect->mode = 0;
        insect->unk_168 = 0;
    } else if ((int) data_ov004_02259a24 % 40 == 0) {
        if (InsectMotion_random(100) > 80) {
            InsectMotion_play(insect, 8, FRAME_CTRL_ONCE, 0x1000, 0);
        }
    }
}
CLEAN_AS(func_ov004_02242d84, InsectMotion_UpdateHovering)

/* The five places kind 49 goes between. */
static const Vec3 InsectMotion_places[5] = {
    {0x11e00, 0x800, 0xda00}, {0x12300, 0x800, 0xf400}, {0x13800, 0x800, 0xf600},
    {0x14100, 0x800, 0xe800}, {0x14000, 0x800, 0xd900},
};

/* func_ov004_02242df8: place `place` of kind 49 (the last for any beyond). */
void InsectMotion_PlaceOf(Vec3 *out, unsigned int place)
{
    *out = InsectMotion_places[place < 4 ? place : 4];
}
CLEAN_AS(func_ov004_02242df8, InsectMotion_PlaceOf)

/* func_ov004_02242e84: kind 49's next place (unk_4c) to its kept point: on along its way
 * (unk_170: up the places, or down), turned at the ends, and three times in ten at another
 * place, back the other way. */
void InsectMotion_NextPlace(MuseumInsect *insect)
{
    u8 place = (u8) insect->unk_4c;
    u8 next;
    if (place == 0 && insect->unk_170 == 0) {
        next = 1;
        insect->unk_170 = 1;
    } else if (place == 4 && insect->unk_170 != 0) {
        next = 3;
        insect->unk_170 = 0;
    } else if (InsectMotion_random(100) > 70 && place != 0 && place != 4) {
        if (insect->unk_170 != 0) {
            next = (u8) (place - 1);
            insect->unk_170 = 0;
        } else {
            next = (u8) (place + 1);
            insect->unk_170 = 1;
        }
    } else if (insect->unk_170 != 0) {
        next = (u8) (place + 1);
    } else {
        next = (u8) (place - 1);
    }
    insect->unk_4c = next;
    InsectMotion_PlaceOf(&insect->kept, next);
}
CLEAN_AS(func_ov004_02242e84, InsectMotion_NextPlace)

/* func_ov004_02242f1c (mode 4 of kind 49): while calm, a flight to its kept point weaving
 * 0xaaa either way; there, the next place is drawn and it turns to it (mode 3). At the end of
 * its time it rests 40-80 frames. */
void InsectMotion_FlyToPlace(MuseumInsect *insect)
{
    if (!InsectMotion_Calm(insect)) {
        return;
    }
    Vec3 *position = &insect->position;
    Vec3 *target = &insect->kept;
    if (func_ov004_02244c20(insect)) {
        insect->timer = (InsectMotion_random(3) + 2) * 20;
        insect->mode = MUSEUM_INSECT_MODE_REST;
    } else if (!Approach_PointXZ(position, target, 64, 0x1000, 41)) {
        InsectMotion_NextPlace(insect);
        insect->unk_ac = Vec_YawTo(position, target);
        insect->mode = INSECT_MOTION_TURN;
    } else {
        s16 time = (s16) insect->timer;
        insect->yaw = Vec_YawTo(position, target);
        if (time % 8 == 0) {
            insect->yaw = (s16) (insect->yaw + 0xaaa);
        } else if (time % 4 == 0) {
            insect->yaw = (s16) (insect->yaw - 0xaaa);
        }
    }
}
CLEAN_AS(func_ov004_02242f1c, InsectMotion_FlyToPlace)

/* func_ov004_02242fe8: kind 49 calm (its alarm below the threshold, and unk_50 below 2): its
 * animation at frame 1, and 1. Otherwise frame 0 and a wait counted down from 60 (to 1), and
 * 0. */
int InsectMotion_Calm(MuseumInsect *insect)
{
    int wait = insect->unk_50;
    func_ov004_02244764(insect);
    if (insect->unk_9c < insect->unk_9e && wait < 2) {
        InsectMotion_set_frame(insect, 1);
        return 1;
    }
    if (wait == 0) {
        insect->unk_50 = 60;
    } else if (wait > 1) {
        insect->unk_50 = (u8) (wait - 1);
    }
    InsectMotion_set_frame(insect, 0);
    return 0;
}
CLEAN_AS(func_ov004_02242fe8, InsectMotion_Calm)

/* func_ov004_02243048 (kind 49's frame): a turn to the next place (mode 3) and the flight
 * there (mode 4), while calm; at the end of a rest, a flight of 80-240 frames. */
void InsectMotion_UpdateVisitor(MuseumInsect *insect)
{
    switch (insect->mode) {
        case INSECT_MOTION_TURN:
            if (InsectMotion_Calm(insect)) {
                s16 yaw = insect->yaw;
                if (Approach_S16Wrapped(&yaw, insect->unk_ac, 0x38e)) {
                    insect->mode = INSECT_MOTION_MOVE;
                }
                insect->yaw = yaw;
            }
            break;
        case INSECT_MOTION_MOVE:
            InsectMotion_FlyToPlace(insect);
            break;
        default:
            if (func_ov004_02244c20(insect) && InsectMotion_Calm(insect)) {
                if (InsectMotion_frame(insect) != 1) {
                    InsectMotion_set_frame(insect, 1);
                }
                insect->unk_168 = 0;
                insect->mode = INSECT_MOTION_MOVE;
                insect->timer = (InsectMotion_random(9) + 4) * 20;
            }
            break;
    }
}
CLEAN_AS(func_ov004_02243048, InsectMotion_UpdateVisitor)

/* func_ov004_022430f8: the turn of a walker whose feelers meet a wall (func_ov004_02245188,
 * 02245174 for kind 52), given back: both blocked, 0xaaa (left after a left turn, unk_50 1 or
 * 10, else right); the left one, or still turning left, 0x38e left; the right one, or still
 * turning right, 0x38e right. unk_50 is the way it turns (1 left, 2 right); with nothing in the
 * way it becomes 10 or 20, and 0 after that. */
int InsectMotion_AvoidWalls(MuseumInsect *insect)
{
    u8 turning = insect->unk_50;
    int blocked_by;
    if (insect->kind == 52) {
        blocked_by = func_ov004_02245174(insect);
    } else {
        blocked_by = func_ov004_02245188(insect);
    }
    if (blocked_by != 0) {
        s16 yaw = insect->yaw;
        if (blocked_by == 3) {
            if (turning == 1 || turning == 10) {
                yaw = (s16) (yaw - 0xaaa);
            } else {
                yaw = (s16) (yaw + 0xaaa);
            }
        } else if (blocked_by == 1 || turning == 1) {
            yaw = (s16) (yaw - 0x38e);
            turning = 1;
        } else if (blocked_by == 2 || turning == 2) {
            yaw = (s16) (yaw + 0x38e);
            turning = 2;
        }
        insect->yaw = yaw;
    } else if (turning < 10) {
        turning = (u8) (10 * turning);
    }
    insect->unk_50 = turning;
    return blocked_by;
}
CLEAN_AS(func_ov004_022430f8, InsectMotion_AvoidWalls)

/* func_ov004_02243194 (mode 4 of kind 30): out of the ground for unk_98 frames, walking in its
 * bounds and now and then (every eighth frame, one time in two) turning up to 12 steps (mode
 * 3); 5 frames before the end its dust (effect set 0x80), and at the end it is hidden for 60
 * frames (mode 16), *frames cleared. */
void InsectMotion_WalkOut(MuseumInsect *insect, short *frames)
{
    short *left = &insect->unk_98;
    if (*left > 0) {
        *left = (short) (*left - 1);
        InsectMotion_Walk(insect);
        func_ov004_02244e38(insect, &insect->position);
        if (*left > 5) {
            if ((int) data_ov004_02259a24 % 8 == 0 && InsectMotion_random(100) > 50) {
                s16 yaw = insect->yaw;
                insect->unk_ac = (s16) (yaw + InsectMotion_RandomTurn(12));
                insect->mode = INSECT_MOTION_TURN;
            }
        } else if (*left == 5) {
            EffectSystem_StartSet(0x80, &insect->position, NULL, &data_020e25d4);
        }
    } else {
        insect->mode = 16;
        InsectMotion_set_alpha(insect, 0);
        insect->timer = 60;
        *frames = 0;
    }
}
CLEAN_AS(func_ov004_02243194, InsectMotion_WalkOut)

/* func_ov004_02243248 (mode 5 of kind 30): a leap along the yaw at 2 units plus the speed, y
 * rising by (25 - t) 4t with t (*frames) counting up by 2; once back on the ground it walks
 * (mode 4) with its alarm and pitch cleared. */
void InsectMotion_Leap(MuseumInsect *insect, short *frames)
{
    Vec3 *position = &insect->position;
    Vec3 direction;
    CollisionGround ground;
    fx32 step = InsectMotion_fx(insect->unk_16c + 2);
    func_ov004_02244fb8(&direction, insect->yaw);
    position->x = position->x + FX_MulFunc(step, direction.x);
    position->z = position->z + FX_MulFunc(step, direction.z);
    int t = *frames;
    position->y = position->y + (25 - t) * (t * 4);
    CollisionGround_Init(&ground, position, 0, 1);
    int landed = position->y <= CollisionGround_GetHeight(&ground, 0);
    CollisionGround_Destroy(&ground);
    if (landed && *frames > 0) {
        insect->mode = INSECT_MOTION_MOVE;
        insect->unk_9c = 0;
        *frames = 0;
        insect->pitch = 0;
    } else {
        *frames = (short) (*frames + 2);
    }
}
CLEAN_AS(func_ov004_02243248, InsectMotion_Leap)

/* func_ov004_02243300 (kind 30 hidden): with the player within 0x5000 its sound plays (for 60
 * frames after). Once its alarm stood above the threshold at the start of the frame, it leaps
 * out (mode 5) away from the player with its dust, shown, for 100-300 frames, its position
 * kept to come back to. */
void InsectMotion_WaitHidden(MuseumInsect *insect)
{
    Vec3 *position = &insect->position;
    InsectSighting sighting;
    /* QUIRK: the alarm before the sighting, cut to 8 bits */
    u8 before = (u8) insect->unk_9c;
    func_ov004_02244658(insect, &sighting);
    if (!sighting.seen) {
        return;
    }
    if (sighting.distance < 0x5000) {
        insect->unk_50 = 60;
    }
    int countdown = insect->unk_50;
    if (countdown > 0) {
        func_ov004_02244be0(insect, 0);
        insect->unk_50 = (u8) (countdown - 1);
    }
    if (before > insect->unk_9e) {
        insect->mode = 5;
        EffectSystem_StartSet(128, position, NULL, &data_020e25d4);
        insect->unk_98 = (s16) ((InsectMotion_random(11) + 5) * 20);
        insect->yaw = Vec_YawTo(&sighting.player, position);
        InsectMotion_set_alpha(insect, 31);
        insect->kept = insect->position;
    }
}
CLEAN_AS(func_ov004_02243300, InsectMotion_WaitHidden)

/* func_ov004_022433c8 (kind 30's frame): hidden (the rest), its leap (5), its walk (4) and turns
 * (3) with its sound, and once hidden again (16) after 60 frames, back at its kept point. */
void InsectMotion_UpdateBurrower(MuseumInsect *insect)
{
    switch (insect->mode) {
        case INSECT_MOTION_MOVE:
            func_ov004_02244be0(insect, 2);
            InsectMotion_WalkOut(insect, &insect->unk_168);
            break;
        case 5:
            InsectMotion_Leap(insect, &insect->unk_168);
            break;
        case INSECT_MOTION_TURN: {
            s16 yaw = insect->yaw;
            if (Approach_S16Wrapped(&yaw, insect->unk_ac, 0x38e)) {
                insect->mode = INSECT_MOTION_MOVE;
            }
            func_ov004_02244be0(insect, 2);
            insect->yaw = yaw;
            break;
        }
        case 16:
            if (func_ov004_02244c20(insect)) {
                insect->mode = MUSEUM_INSECT_MODE_REST;
                insect->position = insect->kept;
            }
            break;
        default:
            InsectMotion_WaitHidden(insect);
            break;
    }
}
CLEAN_AS(func_ov004_022433c8, InsectMotion_UpdateBurrower)

/* func_ov004_02243484 (mode 4 of kind 48): a hop to its kept point, y rising and falling as
 * 0x99a t - 123 t^2 (t, unk_98, the hop's frames); landing, it rests 10-29 frames (10-49 with
 * the player within 0x6000). Its position stays on the floor (func_ov004_02244e94). */
void InsectMotion_HopToKept(MuseumInsect *insect)
{
    short *hop = &insect->unk_98;
    Vec3 *position = &insect->position;
    Vec3 previous = *position;
    Approach_PointXZ(position, &insect->kept, 0xaa, 0x1000, 0x333);
    if (insect->unk_98 > 0) {
        fx32 t = InsectMotion_fx(insect->unk_98);
        position->y = FX_MulFunc(0x99a - FX_MulFunc(123, t), t);
        if (position->y < 0) {
            Actor *player = SessionPlayers_ActorOf(4);
            int spread = 20;
            if (player != NULL && Vec_DistanceXZ(&player->position, position) > 0x6000) {
                spread = 0;
            }
            insect->timer = (s16) (InsectMotion_random(spread * 2 + 20) + 20) >> 1;
            insect->mode = MUSEUM_INSECT_MODE_REST;
            *hop = 0;
        } else {
            ++*hop;
        }
    }
    func_ov004_02244e94(position, &previous);
}
CLEAN_AS(func_ov004_02243484, InsectMotion_HopToKept)

/* func_ov004_02243544 (kind 48's frame): at the end of a rest, with a player, a hop (mode 4)
 * towards the player of 1-3 units (2-4 beyond 0x6000). */
void InsectMotion_UpdateJumper(MuseumInsect *insect)
{
    if (insect->mode == INSECT_MOTION_MOVE) {
        InsectMotion_HopToKept(insect);
    } else if (func_ov004_02244c20(insect)) {
        Actor *player = SessionPlayers_ActorOf(4);
        if (player != NULL) {
            u8 length = (u8) (InsectMotion_random(33) + 16);
            Vec3 *position = &insect->position;
            Vec3 *target = &player->position;
            if (Vec_DistanceXZ(target, position) > 0x6000) {
                length = (u8) (length + 16);
            }
            insect->yaw = Vec_YawTo(position, target);
            func_ov004_02244f48(&insect->kept, position, insect->yaw, FX_MulFunc(InsectMotion_fx(length), 0x100));
            insect->unk_98 = 1;
            insect->mode = INSECT_MOTION_MOVE;
        }
    }
}
CLEAN_AS(func_ov004_02243544, InsectMotion_UpdateJumper)

/* func_ov004_022435e0 (mode 0 of kinds 10 and 51): a flight, faster while startled; its
 * animation flaps; y bobs by the phase in unk_98 (kind 51 a little, twice as fast). */
void InsectMotion_Fly(MuseumInsect *insect)
{
    short *phase = &insect->unk_98;
    func_ov004_02244f20(insect);
    if (func_ov004_02244904(insect) == INSECT_MOTION_ALARM_FELL) {
        insect->unk_9a = 0;
    }
    if (insect->unk_9a) {
        func_ov004_022449ec(insect, 0xaaa, 10, 70);
    } else {
        func_ov004_02244d58(insect);
        func_ov004_022449ec(insect, 0xaaa, 20, 80);
    }
    if (insect->kind == 51) {
        func_ov004_0224497c(insect, *phase, 0x19a, InsectMotion_fx(InsectMotion_random(8) + 18));
        *phase = (short) (*phase + 0x1554);
    } else {
        func_ov004_0224497c(insect, *phase, 0x1200, InsectMotion_fx(InsectMotion_random(8) + 10));
        *phase = (short) (*phase + 0xaaa);
    }
}
CLEAN_AS(func_ov004_022435e0, InsectMotion_Fly)

/* func_ov004_02243694 (kinds 10 and 51's frame): the flight (mode 0) with its sound; resting
 * (6, kind 10 drifting), func_ov004_02244c40; startled (7), back to flight turned by unk_ac;
 * in any other mode, back to flight, kind 51 then hovering about one of two points. */
void InsectMotion_UpdateFlier(MuseumInsect *insect)
{
    switch (insect->mode) {
        case 0:
            func_ov004_02244be0(insect, 0);
            InsectMotion_Fly(insect);
            break;
        case 6:
            if (insect->kind == 10) {
                InsectMotion_Drift(insect);
            }
            func_ov004_02244c40(insect);
            break;
        case 7:
            insect->mode = 0;
            if (insect->unk_9a != 0) {
                insect->yaw = (s16) (insect->yaw + insect->unk_ac);
            }
            break;
        default:
            insect->unk_9a = 0;
            insect->mode = 0;
            if (insect->kind == 51) {
                Vec3 *anchor = &insect->anchor;
                if (InsectMotion_random(100) > 50) {
                    anchor->x = 0xef00;
                    anchor->z = 0xc900;
                } else {
                    anchor->x = 0xf700;
                    anchor->z = 0x15200;
                }
                anchor->y = 0x1300;
            }
            break;
    }
}
CLEAN_AS(func_ov004_02243694, InsectMotion_UpdateFlier)

/* func_ov004_02243740: a flutter: the flight's turns, and y bobbing by the phase (unk_168),
 * stepped by 2/5 to 2/8 of a unit. */
void InsectMotion_Flutter(MuseumInsect *insect)
{
    func_ov004_022449ec(insect, 0x38e, 40, 80);
    insect->unk_168 = (s16) (insect->unk_168 + (s16) FX_Div(0x2000, InsectMotion_fx(InsectMotion_random(4) + 5)));
    func_ov004_0224497c(insect, insect->unk_168, 0x1000, InsectMotion_fx(InsectMotion_random(4) + 10));
}
CLEAN_AS(func_ov004_02243740, InsectMotion_Flutter)

/* func_ov004_0224379c (kind 37's frame): asleep, a hoverer's motion; awake, a flutter in its
 * bounds (mode 0, any other mode going back to it). */
void InsectMotion_UpdateFlutterer(MuseumInsect *insect)
{
    if (!insect->awake) {
        InsectMotion_UpdateHoverer(insect);
    } else if (insect->mode == 0) {
        InsectMotion_Flutter(insect);
        func_ov004_02244e38(insect, &insect->position);
    } else {
        insect->unk_9a = 0;
        insect->mode = 0;
    }
}
CLEAN_AS(func_ov004_0224379c, InsectMotion_UpdateFlutterer)

/* func_ov004_022437e0 (mode 0 of kind 50): with a player, it flies after the player at 8 units
 * a frame, turning 0x38e a frame, and within 0x2000 seven times in ten swerves 0x5b0 more.
 * Within 0x1000 it starts to circle (unk_9a), counting frames in unk_9c (to 60); past 0x3000
 * it stops. After 60 frames circling within 0x1000, the first time the player can take state 79
 * (PlayerActorOps_RequestState79) it stops and notes it (unk_4c), its phase cleared. y bobs by
 * the phase, stepped 0xaaa a frame. */
void InsectMotion_FollowPlayer(MuseumInsect *insect, short *phase)
{
    Actor *player = SessionPlayers_ActorOf(4);
    if (player == NULL) {
        return;
    }
    Vec3 *position = &insect->position;
    Vec3 *target = &player->position;
    Vec3 unit;
    fx32 distance = Vec_DistanceXZ(target, position);
    s16 yaw = insect->yaw;
    Approach_S16Wrapped(&yaw, Vec_YawTo(position, target), 0x38e);
    *phase = (short) (*phase + 0xaaa);
    if (insect->unk_9a) {
        s16 circled = insect->unk_9c;
        if (distance > 0x3000) {
            insect->unk_9a = 0;
        } else if (circled < 60) {
            ++circled;
            insect->unk_9c = (u8) circled;
        } else if (insect->unk_4c == 0 && distance < 0x1000 && PlayerActorOps_RequestState79()) {
            insect->unk_9a = 0;
            insect->mode = 0;
            insect->unk_4c = 1;
            *phase = 0;
        }
    }
    if (distance < 0x2000) {
        if (distance < 0x1000 && !insect->unk_9a) {
            insect->unk_9a = 1;
            insect->unk_9c = 0;
        }
        if (InsectMotion_random(100) > 30) {
            if (yaw > 0) {
                yaw = (s16) (yaw + 0x5b0);
            } else if (yaw < 0) {
                yaw = (s16) (yaw - 0x5b0);
            }
        }
    }
    insect->yaw = yaw;
    func_ov004_02244fb8(&unit, yaw);
    position->x += FX_MulFunc(unit.x, 0x8000);
    position->z += FX_MulFunc(unit.z, 0x8000);
    func_ov004_0224497c(insect, *phase, 0x2800, InsectMotion_fx(InsectMotion_random(4) + 18));
}
CLEAN_AS(func_ov004_022437e0, InsectMotion_FollowPlayer)

/* func_ov004_02243948 (kind 50's frame): its animation flapping and its sound, and the chase
 * of the player (mode 0, any other mode going back to it). */
void InsectMotion_UpdateFollower(MuseumInsect *insect)
{
    func_ov004_02244f20(insect);
    func_ov004_02244be0(insect, 0);
    if (insect->mode == 0) {
        InsectMotion_FollowPlayer(insect, &insect->unk_168);
    } else {
        insect->mode = 0;
    }
}
CLEAN_AS(func_ov004_02243948, InsectMotion_UpdateFollower)

/* The turns InsectMotion_RandomSideTurn draws from: 15 to 60 degrees either way. */
static const s16 InsectMotion_side_turns[7] = {0xaaa, 0x1554, 0x2000, 0x2aaa, -0xaaa, -0x1554, -0x2000};

/* func_ov004_02243980: a turn drawn from `bound` values: the first seven 15, 30, 45 and 60
 * degrees one way and 15, 30, 45 the other, any beyond -60. */
int InsectMotion_RandomSideTurn(int bound)
{
    unsigned int pick = MainRandom_Below(bound);
    return pick < 7 ? InsectMotion_side_turns[pick] : -0x2aaa;
}
CLEAN_AS(func_ov004_02243980, InsectMotion_RandomSideTurn)

/* func_ov004_022439ec (mode 4 of kind 25): a dash along the yaw at height 0x200, slowing with
 * *frames (each frame *frames times the speed, *frames counting down). Out of the bounds it
 * goes back and turns about with a side turn (mode 15); at the end it rests up to 59 frames
 * awake, up to 299 asleep (unk_98). */
void InsectMotion_Dash(MuseumInsect *insect, short *frames)
{
    Vec3 *position = &insect->position;
    Vec3 save = *position;
    Vec3 direction;
    func_ov004_02244fb8(&direction, insect->yaw);
    position->x += FX_MulFunc(InsectMotion_fx(*frames * insect->unk_16c), direction.x);
    position->z += FX_MulFunc(InsectMotion_fx(*frames * insect->unk_16c), direction.z);
    position->y = 0x200;
    *frames = (short) (*frames - 1);
    if (position->x < insect->low[0] || position->x > insect->high[0] || position->z < insect->low[1] ||
        position->z > insect->high[1]) {
        *position = save;
        insect->unk_ac = (s16) (-0x8000 + InsectMotion_RandomSideTurn(8));
        insect->mode = INSECT_MOTION_TURN_AWAY;
        *frames = 0;
    } else if (*frames <= 0) {
        insect->mode = MUSEUM_INSECT_MODE_REST;
        if (insect->awake) {
            insect->unk_98 = (s16) InsectMotion_random(60);
        } else {
            insect->unk_98 = (s16) InsectMotion_random(300);
        }
    }
}
CLEAN_AS(func_ov004_022439ec, InsectMotion_Dash)

/* func_ov004_02243af4 (modes 3 and 15 of kind 25): a dash started (mode 4) of 8-15 frames
 * (*frames), turned by unk_ac after a wall (15), else by 0-4 steps of 0xaaa either way, with
 * the effect set 0x1f where it starts. */
void InsectMotion_StartDash(MuseumInsect *insect, short *frames)
{
    s16 yaw = insect->yaw;
    s16 turned;
    if (insect->mode == INSECT_MOTION_TURN_AWAY) {
        turned = (s16) (yaw + insect->unk_ac);
        insect->mode = INSECT_MOTION_MOVE;
    } else {
        u8 steps = (u8) InsectMotion_random(5);
        turned = (s16) (steps * 0xaaa);
        if (InsectMotion_random(100) > 50) {
            turned = (s16) -turned;
        }
        turned = (s16) (turned + yaw);
        insect->mode = INSECT_MOTION_MOVE;
    }
    insect->yaw = turned;
    *frames = (short) (InsectMotion_random(8) + 8);
    Vec3 at = insect->position;
    s16 angle = 0;
    EffectSystem_StartOneShotSetNumber(0x1f, &at, &angle, NULL);
}
CLEAN_AS(func_ov004_02243af4, InsectMotion_StartDash)

/* func_ov004_02243bb0 (kind 25's frame): dashes (InsectMotion_StartDash, InsectMotion_Dash)
 * after rests of unk_98 frames. */
void InsectMotion_UpdateDasher(MuseumInsect *insect)
{
    switch (insect->mode) {
        case INSECT_MOTION_TURN:
        case INSECT_MOTION_TURN_AWAY:
            InsectMotion_StartDash(insect, &insect->unk_168);
            break;
        case INSECT_MOTION_MOVE:
            InsectMotion_Dash(insect, &insect->unk_168);
            break;
        default: {
            s16 left = insect->unk_98;
            if (left <= 0) {
                insect->mode = INSECT_MOTION_TURN;
            } else {
                insect->unk_98 = (s16) (left - 1);
            }
            insect->unk_9a = 0;
            break;
        }
    }
}
CLEAN_AS(func_ov004_02243bb0, InsectMotion_UpdateDasher)

/* func_ov004_02243c04: kinds 27-29 make their sound while their alarm is below 5. */
void InsectMotion_SingWhenCalm(MuseumInsect *insect)
{
    switch (insect->kind) {
        case 27:
        case 28:
        case 29:
            if (insect->unk_9c < 5) {
                func_ov004_02244be0(insect, 0);
            }
            break;
    }
}
CLEAN_AS(func_ov004_02243c04, InsectMotion_SingWhenCalm)

/* func_ov004_02243c30: where the feelers meet a wall, a glide away from it (mode 15) to a point
 * `distance` (0xa4) plus 0-2 units off, counted in unk_4c, *frames cleared. Gives back what
 * func_ov004_02245188 found (a bit set, not a pointer: the game declares it so). */
void *InsectMotion_TurnFromWall(MuseumInsect *insect, short *frames)
{
    int blocked_by = func_ov004_02245188(insect);
    if (blocked_by != 0) {
        insect->unk_ac = func_ov004_022447c0(insect->yaw, blocked_by);
        s16 away = insect->unk_ac;
        int more = InsectMotion_random(3);
        func_ov004_02244f48(&insect->kept, &insect->position, away, InsectMotion_fx(insect->distance + more));
        insect->unk_ac = Vec_YawTo(&insect->position, &insect->kept);
        insect->mode = INSECT_MOTION_TURN_AWAY;
        insect->unk_4c += 1;
        *frames = 0;
    }
    return (void *) (intptr_t) blocked_by;
}
CLEAN_AS(func_ov004_02243c30, InsectMotion_TurnFromWall)

/* func_ov004_02243cb0 (mode 4 of kind 12): a glide to its kept point at its speed (while the
 * feelers are clear, unless it touched something, unk_20; else it stays), kept in its bounds;
 * rising to 0x1400 (unk_170) or settling to the ground. Settled, it rests 60-200 frames
 * (unk_98) at frame 0, the kept point there, and if it had been startled its alarm is set 10
 * below the threshold. */
void InsectMotion_Glide(MuseumInsect *insect)
{
    Vec3 *target = &insect->kept;
    Vec3 *position = &insect->position;
    Vec3 old = *position;
    int speed = insect->unk_16c;
    if (!func_ov004_02245188(insect) || insect->unk_20) {
        if (Approach_PointXZ(position, target, speed, 0x1000, 0x333)) {
            if (func_ov004_02244e38(insect, position)) {
                *position = old;
                *target = *position;
            } else {
                insect->yaw = Vec_YawTo(position, target);
            }
        }
    } else {
        *target = *position;
    }
    /* the height eased as a 32-bit int; fx32 is one */
    int *height = (int *) &position->y;
    if (insect->unk_170) {
        if (!Approach_EaseS32MinMax(height, 0x1400, speed, 0x1000, 0xcd)) {
            insect->unk_170 = 0;
        }
    } else {
        CollisionGround ground;
        CollisionGround_Init(&ground, position, 0, 1);
        int floor = CollisionGround_GetHeight(&ground, 0);
        CollisionGround_Destroy(&ground);
        if (!Approach_EaseS32MinMax(height, floor, speed, 0x1000, 0x266)) {
            insect->unk_98 = (s16) ((InsectMotion_random(9) + 2) * 20);
            insect->mode = MUSEUM_INSECT_MODE_REST;
            InsectMotion_set_frame(insect, 0);
            *target = *position;
            if (insect->unk_9a) {
                insect->unk_9c = (u8) (insect->unk_9e - 10);
                insect->unk_9a = 0;
            }
        }
    }
}
CLEAN_AS(func_ov004_02243cb0, InsectMotion_Glide)

/* func_ov004_02243e04 (kind 12's frame): turns (3 and 15, then up to the glide: mode 4 with
 * unk_170 set), the glide, and at rest (awake, its sound while calm) a turn from a wall, or
 * after the rest's time (unk_98, five times as long once alarmed or asleep) or a touch, a
 * glide up to a point `distance` plus 0-2 units off along a turn of up to 12 steps, its alarm
 * cleared. The touch (unk_20) is cleared each frame. */
void InsectMotion_UpdateGlider(MuseumInsect *insect)
{
    switch (insect->mode) {
        case INSECT_MOTION_TURN:
        case INSECT_MOTION_TURN_AWAY:
            func_ov004_02244774(insect, 1, INSECT_MOTION_MOVE);
            break;
        case INSECT_MOTION_MOVE:
            InsectMotion_Glide(insect);
            break;
        default: {
            short *frames = &insect->unk_168;
            short *rest = &insect->unk_98;
            if (insect->awake) {
                InsectMotion_SingWhenCalm(insect);
            }
            if (InsectMotion_TurnFromWall(insect, frames) != NULL) {
                break;
            }
            if (func_ov004_02244764(insect) == INSECT_MOTION_ALARM_ROSE) {
                *frames = (short) (5 * *rest);
            } else if (!insect->awake && *frames == 0) {
                *rest = (short) (5 * *rest);
            }
            *frames = (short) (*frames + 1);
            if (*frames >= *rest || insect->unk_20) {
                int yaw = insect->yaw;
                insect->unk_ac = (s16) (InsectMotion_RandomTurn(12) + yaw);
                func_ov004_02244f48(&insect->kept, &insect->position, insect->unk_ac,
                                    InsectMotion_fx(insect->distance + InsectMotion_random(3)));
                insect->unk_ac = Vec_YawTo(&insect->position, &insect->kept);
                insect->mode = INSECT_MOTION_TURN;
                *frames = 0;
                insect->unk_9c = 0;
            }
            break;
        }
    }
    insect->unk_20 = 0;
}
CLEAN_AS(func_ov004_02243e04, InsectMotion_UpdateGlider)
