/* How the fish shadows swim (fish_shadow.h): free in the water by their swimming state
 * (FishShadow.behaviour), and on a fishing float by their hook state (FishShadow.hook_state),
 * from the tables of member functions data_ov003_0225f160 and data_ov003_0225f190. Which of
 * the two runs is picked by FishShadow.hooked from the pairs in data_ov003_0225f118: the first
 * of a pair while the shadow is being placed (FishShadow_StepPlacing), the second once it is
 * shown (FishShadow_StepShown). */
#include "fish_shadow.h"

#include "clean.h"
#include "main/actor.h"       /* Vec_YawTo */
#include "main/actor_table.h" /* Position_Tile */
#include "main/creature_table.h"
#include "main/effect_system.h"
#include "main/player_actor_ops.h"
#include "main/tile_requests.h"
#include "main/unit_type_info.h"
#include "ov004/member_pointer.h"

/* A size class's numbers (data_ov003_0223c014, eight rows of 0x14 bytes); those read here. */
typedef struct FishSwimSize {
    u8 reach;          /* 0x00: the box around the float it must be in, in hundredths */
    u8 near;           /* 0x01: the box it circles the float in while biting, in hundredths */
    u8 pull_min;       /* 0x02: the frames it pulls before it can be landed: at least */
    u8 pull_max;       /* 0x03: and less than */
    u8 unk_04[6];      /* 0x04 */
    u16 pull_distance; /* 0x0a: how far ahead of the float it pulls, in hundredths */
    u16 retreat;       /* 0x0c: the box it backs away from the float in, in hundredths */
    u8 unk_0e[6];      /* 0x0e */
} FishSwimSize;
static_assert(sizeof(FishSwimSize) == 0x14, "FishSwimSize");

/* The two rods' tables (data_ov003_0223bf00): the second word is, by the third number of a
 * fish's kind (CreatureTableInfo.unk_02), how many frames it keeps the float under. */
typedef struct FishSwimRodTables {
    const void *ranges;
    const u8 *bite_frames;
} FishSwimRodTables;

/* A pair of data_ov003_0225f118. */
typedef struct FishSwimStepPair {
    MemberPointer placing;
    MemberPointer shown;
} FishSwimStepPair;

#define FISH_SWIM_SIZES 8
#define FISH_SWIM_ROD 0x1374
#define FISH_SWIM_GOLDEN_ROD 0x1375
#define FISH_SWIM_THIS_CONSOLE 4     /* main's player number for the player at this console */
#define FISH_SWIM_NIBBLE_SOUND 0x84f /* the float pulled under */
#define FISH_SWIM_VOLUME 0x7f
#define FISH_SWIM_JUNK_FIRST 0x38 /* the kinds that are not fish (fish_disp.h) */
#define FISH_SWIM_JUNK_LAST 0x3a
#define FISH_SWIM_JUNK_DROP_KIND 0x10 /* TileRequests_FindDropTile's kind for them */
#define FISH_SWIM_TURN 0x222          /* a turn away from what blocks it */
#define FISH_SWIM_EDGE_TURN 0x555     /* a turn back from the town's edge */
#define FISH_SWIM_SPEED 0x19a         /* its cruising speed, 0.1 a frame */
#define FISH_SWIM_KIND_WITH_SENSE 0xb /* the only kind that hears the player (FishShadowSense) */

/* FishShadow.behaviour: the swimming states. */
#define FISH_SWIM_START 0
#define FISH_SWIM_SPEED_UP 1
#define FISH_SWIM_CRUISE 2 /* FISH_SHADOW_STARTLED */
#define FISH_SWIM_SLOW_DOWN 3
#define FISH_SWIM_DRIFT 4
#define FISH_SWIM_FLEE 5 /* FISH_SHADOW_FLEEING */

/* FishShadow.hook_state */
#define FISH_HOOK_WAIT 0
#define FISH_HOOK_APPROACH 1
#define FISH_HOOK_HESITATE 2
#define FISH_HOOK_NIBBLE 3
#define FISH_HOOK_BITE 4
#define FISH_HOOK_PULL 5
#define FISH_HOOK_FLEE 6 /* FISH_SHADOW_HOOK_FLEEING */

/* FishShadow.hook_step: the hesitation's steps (0-2), the nibble's (3-5), the bite's (6-9) and
 * the pull's (10). */
#define FISH_HOOK_HESITATE_CLOSE 0
#define FISH_HOOK_HESITATE_DITHER 1
#define FISH_HOOK_HESITATE_LEAVE 2
#define FISH_HOOK_NIBBLE_CLOSE 3
#define FISH_HOOK_NIBBLE_PECK 4
#define FISH_HOOK_NIBBLE_BACK 5
#define FISH_HOOK_BITE_RIGHT 6
#define FISH_HOOK_BITE_LEFT 7
#define FISH_HOOK_BITE_AWAY 8
#define FISH_HOOK_BITE_REST 9
#define FISH_HOOK_PULL_STEP 10

extern const FishSwimSize data_ov003_0223c014[FISH_SWIM_SIZES];
extern const FishSwimRodTables data_ov003_0223bf00[2];
extern const CreatureTableInfo data_020cb784[];
extern PlayerFish data_ov003_0225f4dc[PLAYER_FISH_COUNT];
/* The tables: swimming states, hook states, and the pairs by FishShadow.hooked. */
extern MemberPointer data_ov003_0225f160[6];
extern MemberPointer data_ov003_0225f190[7];
extern FishSwimStepPair data_ov003_0225f118[2];
/* How far the fish pulls beyond its row's distance, shared by all shadows: -12 to 20. */
extern int data_ov003_0225f0c0;
extern u8 data_021fbdd8;  /* the pen is down */
extern s32 data_020c904c; /* the water's surface height */
extern const fx16 FX_SinCosTable_[4096 * 2];

extern fx32 FX_MulFunc(fx32 a, fx32 b);
/* The overlay's: the shadow's animation speed set to `speed` sixteenths of a frame
 * (func_ov003_022277fc), a random number in [lo, hi) and one of either sign
 * (func_ov003_0222793c, func_ov003_0222791c), whether `b` is in the box around `a`
 * (func_ov003_0222799c), a point drifted by the water's current (func_ov003_0222803c), and the
 * shadow escaping over ground of its group (func_ov003_022282b8). */
extern void func_ov003_022277fc(FishShadow *fish, int speed);
extern int func_ov003_0222793c(int lo, int hi);
extern int func_ov003_0222791c(int lo, int hi);
extern int func_ov003_0222799c(const Vec3 *a, const Vec3 *b, int dx, int dz_ahead, int dz_behind);
extern void func_ov003_0222803c(Vec3 *position, int amount);
extern int func_ov003_022282b8(FishShadow *fish, Vec3 *last_position);

/* Entry `index` of a table of member pointers, the address computed without a bound. */
static const MemberPointer *fish_swim_member(const MemberPointer *table, unsigned int index)
{
    return (const MemberPointer *) (uintptr_t) ((u32) (uintptr_t) table + index * (u32) sizeof(MemberPointer));
}

static const FishSwimStepPair *fish_swim_pair(unsigned int index)
{
    return (const FishSwimStepPair *) (uintptr_t) ((u32) (uintptr_t) data_ov003_0225f118 +
                                                   index * (u32) sizeof(FishSwimStepPair));
}

/* Kind `kind`'s details, without a bound (a kind of -1 reads the row before the table). */
static const CreatureTableInfo *fish_swim_creature(int kind)
{
    return (const CreatureTableInfo *) (uintptr_t) ((u32) (uintptr_t) data_020cb784 + (u32) kind * sizeof(CreatureTableInfo));
}

/* Size class `size`'s row, without a bound. */
static const FishSwimSize *fish_swim_size(int size)
{
    return (const FishSwimSize *) (uintptr_t) ((u32) (uintptr_t) data_ov003_0223c014 + (u32) size * sizeof(FishSwimSize));
}

/* A percentage of 1.0 (hundredths of a unit). */
static fx32 fish_swim_hundredths(int value)
{
    return value * 0x1000 / 100;
}

/* Which rod the player holds: 0 or 1, -1 for neither. */
static int fish_swim_rod(int player)
{
    u16 held;
    PlayerActorOps_HeldItem(&held, player);
    if (held == FISH_SWIM_ROD) {
        return 0;
    }
    if (held == FISH_SWIM_GOLDEN_ROD) {
        return 1;
    }
    return -1;
}

/* How many frames the shadow keeps the float of `rod` under. */
static int fish_swim_bite_frames(const FishShadow *fish, int rod)
{
    return data_ov003_0223bf00[rod].bite_frames[fish_swim_creature(fish->kind)->unk_02];
}

static int fish_swim_in_box(const FishShadow *fish, const Vec3 *point, fx32 size)
{
    return func_ov003_0222799c(&fish->position, point, size, size, size);
}

/* The first part of a stepped approach: 1/16 more a frame, at most 1/16 of a unit. */
static int fish_swim_ramp(const FishShadow *fish)
{
    int step = fish->unk_23d << 4;
    return step >= 0x100 ? 0x100 : step;
}

/* The effect following the shadow, on the surface. */
static void fish_swim_move_effect(const FishShadow *fish)
{
    Vec3 at = fish->position;
    at.y = data_020c904c;
    EffectSystem_MoveHandle(fish->effect, &at, NULL, NULL);
}

/* The fin's animation speed by how long it has swum. */
static void fish_swim_fin_speed(FishShadow *fish, int frames, int fast, int middle)
{
    if (frames >= fast) {
        func_ov003_022277fc(fish, 3);
    } else if (frames >= middle) {
        func_ov003_022277fc(fish, 0x10);
    } else {
        func_ov003_022277fc(fish, 0x20);
    }
}

/* func_ov003_0222ab4c: while the fish pulls (FISH_HOOK_PULL) and has pulled its frames, it is
 * landed (FishShadow_Catch: 2) or, when that fails, flees (1); else 0. 0 without a shadow. */
int FishShadowHook_TryLand(FishShadow *fish)
{
    if (fish == NULL || fish->hook_state != FISH_HOOK_PULL) {
        return 0;
    }
    if (fish->unk_13c < fish->pull_frames) {
        return 0;
    }
    if (FishShadow_Catch(fish, fish->index)) {
        return 2;
    }
    FishShadow_FleeFromPlayer(fish);
    return 1;
}
CLEAN_AS(func_ov003_0222ab4c, FishShadowHook_TryLand)

/* func_ov003_0222aba4: the player strikes (the float's FishingFloat_FishPull). Biting
 * (FISH_HOOK_BITE) with a rod in hand and in time (unless the pen is down), the fish is hooked:
 * it pulls (FISH_HOOK_PULL) to a random side for its size's frames from where the float is,
 * the float rippling and the fish turned a quarter that way; 1. Biting out of time or without
 * a rod, or nibbling, it flees; fleeing it stays; in any other hook state (pulling too) it lets
 * go of the line, or flees without one. Without a shadow 0; without a float it flees. */
int FishShadowHook_Strike(FishShadow *fish)
{
    if (fish == NULL) {
        return 0;
    }
    FishingFloat *fishing_float = fish->fishing_float;
    if (fishing_float == NULL) {
        FishShadow_FleeFromPlayer(fish);
        return 0;
    }
    switch (fish->hook_state) {
        case FISH_HOOK_BITE: {
            int rod = fish_swim_rod(fish->player);
            if (rod < 0) {
                FishShadow_FleeFromPlayer(fish);
                return 0;
            }
            if (data_021fbdd8 == 0 && fish->unk_13c > fish_swim_bite_frames(fish, rod) - 1) {
                FishShadow_FleeFromPlayer(fish);
                return 0;
            }
            fish->hook_state = FISH_HOOK_PULL;
            fish->hook_step = FISH_HOOK_PULL_STEP;
            fish->unk_13c = 0;
            FishingFloat_SetState(fishing_float, FISHING_FLOAT_RIPPLING);
            fish->pull_left = func_ov003_0222793c(0, 2) != 0;
            const FishSwimSize *size = fish_swim_size(fish->size);
            fish->pull_frames = (u8) func_ov003_0222793c(size->pull_min, size->pull_max);
            fish->pull_point = fishing_float->position;
            fish->yaw = (s16) (fish->pull_left ? fish->yaw - 0x4000 : fish->yaw + 0x4000);
            return 1;
        }
        case FISH_HOOK_FLEE:
            break;
        case FISH_HOOK_NIBBLE:
            FishShadow_FleeFromPlayer(fish);
            break;
        default:
            if (FishShadow_DropLine(fish) == 0) {
                FishShadow_FleeFromPlayer(fish);
            }
            break;
    }
    return 0;
}
CLEAN_AS(func_ov003_0222aba4, FishShadowHook_Strike)

/* func_ov003_0222ad2c: a hooked fish whose player stops fishing: one nibbling, biting or pulling
 * flees, a fleeing one stays, any other lets go of the line (or flees without one). */
void FishShadowHook_LetGo(FishShadow *fish)
{
    if (fish->hooked != 1) {
        return;
    }
    switch (fish->hook_state) {
        case FISH_HOOK_NIBBLE:
        case FISH_HOOK_BITE:
        case FISH_HOOK_PULL:
            FishShadow_FleeFromPlayer(fish);
            break;
        case FISH_HOOK_FLEE:
            break;
        default:
            if (FishShadow_DropLine(fish) == 0) {
                FishShadow_FleeFromPlayer(fish);
            }
            break;
    }
}
CLEAN_AS(func_ov003_0222ad2c, FishShadowHook_LetGo)

/* func_ov003_0222ad80: FISH_HOOK_FLEE: it swims straight on, (frames + 10) * 25/4096 a frame up
 * to 0x180 (about 0.09), with its effect on the surface; the fin beats slower the longer it
 * swims. */
int FishShadowHook_StepFlee(FishShadow *fish)
{
    func_ov003_022277fc(fish, 0x1c);
    int frames = fish->unk_13c;
    int distance = 0x19 * (frames + 10);
    if (distance >= 0x180) {
        distance = 0x180;
    }
    if (fish->has_fin) {
        fish_swim_fin_speed(fish, frames, 0x14, 0xf);
    }
    FishShadow_MoveAlong(&fish->position, distance, (u16) fish->yaw);
    fish_swim_move_effect(fish);
    return 1;
}
CLEAN_AS(func_ov003_0222ad80, FishShadowHook_StepFlee)

/* func_ov003_0222ae2c: FISH_HOOK_PULL: the fish circles its side (left: turning one way, its
 * animation sent back to frame 3 once past frame 4; right: the other way, to frame 10 once past
 * 11), faster for the small sizes (0-2). It is put ahead of the float sideways by its size's
 * distance plus a shared drift (moved by 3-9 either way, kept in -12..20) plus 0-14 either way,
 * then 0.625 further from the player at this console. 0 without a float. */
int FishShadowHook_StepPull(FishShadow *fish)
{
    FishingFloat *fishing_float = fish->fishing_float;
    if (fishing_float == NULL) {
        return 0;
    }
    int turn = fish->size >= 3 ? 0x1000 : 0x1249;
    int angle;
    if (fish->pull_left) {
        if (FrameCtrl_Passed(&fish->model.frames, 4)) {
            fish->model.frames.frame = 0x3000;
        }
        fish->yaw = (s16) (fish->yaw + turn);
        angle = (s16) (fish->yaw - 0x4000);
    } else {
        if (FrameCtrl_Passed(&fish->model.frames, 0xb)) {
            fish->model.frames.frame = 0xa000;
        }
        fish->yaw = (s16) (fish->yaw - turn);
        angle = (s16) (fish->yaw + 0x4000);
    }
    int drift = data_ov003_0225f0c0 + func_ov003_0222791c(3, 10);
    data_ov003_0225f0c0 = drift;
    if (drift < -12) {
        data_ov003_0225f0c0 = -12;
    } else if (drift > 20) {
        data_ov003_0225f0c0 = 20;
    }
    int distance = data_ov003_0225f0c0 + func_ov003_0222791c(0, 0xf);
    distance = fish_swim_hundredths(distance + fish_swim_size(fish->size)->pull_distance);
    Vec3 float_at = fishing_float->position;
    fish->position.x = float_at.x;
    fish->position.z = float_at.z;
    FishShadow_MoveAlong(&fish->position, distance, (u16) angle);
    const Vec3 *player = PlayerActorOps_StartPosition(FISH_SWIM_THIS_CONSOLE);
    if (player != NULL) {
        FishShadow_MoveAlong(&fish->position, 0xa00, (u16) Vec_YawTo(player, &float_at));
    }
    return 1;
}
CLEAN_AS(func_ov003_0222ae2c, FishShadowHook_StepPull)

/* func_ov003_0222af74: FISH_HOOK_BITE: the float is under; the fish holds it for its rod's
 * frames (FishSwimRodTables.bite_frames), then the float floats again and it lets go (0, so it
 * flees). Meanwhile it zigzags at the float: a step towards it and one sideways, right
 * (step 6) or left (7), turning the other way each time until it is in the size's box (8);
 * then backing off until out of the box, to go on (30%, step 6) or to rest (9), from which it
 * goes on (step 7) at random half of the frames. It faces the float. Without a float, a
 * player or a rod: 0. */
int FishShadowHook_StepBite(FishShadow *fish)
{
    FishingFloat *fishing_float = fish->fishing_float;
    if (fishing_float == NULL || fish->player == FISH_SHADOW_NO_PLAYER) {
        return 0;
    }
    const Vec3 *target = &fishing_float->position;
    func_ov003_022277fc(fish, 0x18);
    int rod = fish_swim_rod(fish->player);
    if (rod < 0) {
        return 0;
    }
    if (fish->unk_13c >= fish_swim_bite_frames(fish, rod)) {
        fish->unk_13c = 0;
        FishingFloat_SetState(fishing_float, FISHING_FLOAT_FLOATING);
        return 0;
    }
    switch (fish->hook_step) {
        case FISH_HOOK_BITE_RIGHT:
        case FISH_HOOK_BITE_LEFT: {
            int right = fish->hook_step == FISH_HOOK_BITE_RIGHT;
            fx32 box = fish_swim_hundredths(fish_swim_size(fish->size)->reach);
            int angle = Vec_YawTo(&fish->position, target);
            FishShadow_MoveAlong(&fish->position, 0x180, (u16) angle);
            FishShadow_MoveAlong(&fish->position, 0xc0, (u16) (right ? angle + 0x4000 : angle - 0x4000));
            if (fish_swim_in_box(fish, target, box)) {
                fish->hook_step = FISH_HOOK_BITE_AWAY;
            } else {
                fish->hook_step = right ? FISH_HOOK_BITE_LEFT : FISH_HOOK_BITE_RIGHT;
            }
            break;
        }
        case FISH_HOOK_BITE_AWAY: {
            fx32 box = fish_swim_hundredths(fish_swim_size(fish->size)->near);
            FishShadow_MoveAlong(&fish->position, 0x180, (u16) Vec_YawTo(target, &fish->position));
            int chance = func_ov003_0222793c(0, 100);
            if (!fish_swim_in_box(fish, target, box)) {
                fish->hook_step = chance >= 70 ? FISH_HOOK_BITE_RIGHT : FISH_HOOK_BITE_REST;
            }
            break;
        }
        case FISH_HOOK_BITE_REST:
            if (func_ov003_0222793c(0, 100) <= 50) {
                fish->hook_step = FISH_HOOK_BITE_LEFT;
            }
            break;
    }
    fish->yaw = Vec_YawTo(&fish->position, target);
    return 1;
}
CLEAN_AS(func_ov003_0222af74, FishShadowHook_StepBite)

/* func_ov003_0222b1b4: FISH_HOOK_NIBBLE. Once it has nibbled its frames (nibble_wait) and is in
 * its size's box at the float, the float is pulled under (with sound 0x84f) and it bites
 * (FISH_HOOK_BITE, step 6; 1). A kind that is not a fish (0x38-0x3a) bites only when the
 * player has a tile to drop it on (TileRequests_FindDropTile); else it stays (0). Otherwise it
 * pecks: closes in (step 3, faster each frame) until within its size's reach, the float
 * bobbing up (step 4); pecks about for 10-19 frames, half the time facing away, now and then
 * bobbing the float; backs off (step 5, slower each frame) out of its retreat box, and closes
 * in again. It faces the float unless very near it. 0 without a float. */
int FishShadowHook_StepNibble(FishShadow *fish)
{
    FishingFloat *fishing_float = fish->fishing_float;
    if (fishing_float == NULL) {
        return 0;
    }
    const Vec3 *target = &fishing_float->position;
    if (fish->unk_13c >= fish->nibble_wait) {
        fx32 box = fish_swim_hundredths(fish_swim_size(fish->size)->reach);
        if (fish_swim_in_box(fish, target, box)) {
            int ret = 0;
            fish->unk_13c = 0;
            FishingFloat_SetState(fishing_float, FISHING_FLOAT_SINKING);
            SoundEmitter_PlayB((SoundEmitter *) fish->emitter, FISH_SWIM_NIBBLE_SOUND, FISH_SWIM_VOLUME, 0);
            int junk = fish->kind >= FISH_SWIM_JUNK_FIRST && fish->kind <= FISH_SWIM_JUNK_LAST;
            TileRequestTile tile = {0, 0};
            if (!junk || TileRequests_FindDropTile(FISH_SWIM_JUNK_DROP_KIND, &tile, NULL) != 0) {
                fish->hook_state = FISH_HOOK_BITE;
                fish->hook_step = FISH_HOOK_BITE_RIGHT;
                ret = 1;
            }
            return ret;
        }
    }
    int reach = fish_swim_size(fish->size)->reach * 0x1000;
    switch (fish->hook_step) {
        case FISH_HOOK_NIBBLE_CLOSE: {
            fx32 near = reach / 100;
            FishShadow_MoveAlong(&fish->position, fish_swim_ramp(fish), (u16) Vec_YawTo(&fish->position, target));
            s64 distance_sq = Vec_DistanceSquaredXZ(&fish->position, target);
            if ((s64) FX_MulFunc(near, near) >= distance_sq) {
                fish->unk_23d = 0;
                FishingFloat_ToSurface(fishing_float);
                fish->hook_step = FISH_HOOK_NIBBLE_PECK;
            }
            func_ov003_022277fc(fish, 0x18);
            break;
        }
        case FISH_HOOK_NIBBLE_PECK: {
            int frames = func_ov003_0222793c(10, 20);
            int angle;
            if (func_ov003_0222793c(0, 100) < 50) {
                angle = Vec_YawTo(target, &fish->position);
            } else {
                angle = Vec_YawTo(&fish->position, target);
                if (func_ov003_0222793c(0, 100) < 5) {
                    FishingFloat_ToSurface(fishing_float);
                }
            }
            FishShadow_MoveAlong(&fish->position, 0x100, (u16) angle);
            if (fish->unk_23d > frames) {
                fish->unk_23d = 0;
                fish->hook_step = FISH_HOOK_NIBBLE_BACK;
            }
            break;
        }
        case FISH_HOOK_NIBBLE_BACK: {
            fx32 box = fish_swim_hundredths(fish_swim_size(fish->size)->retreat);
            int step = 0x100 - (fish->unk_23d << 4);
            if (step < 0) {
                step = 0;
            }
            FishShadow_MoveAlong(&fish->position, step, (u16) Vec_YawTo(target, &fish->position));
            if (step == 0 || !fish_swim_in_box(fish, target, box)) {
                fish->unk_23d = 0;
                fish->hook_step = FISH_HOOK_NIBBLE_CLOSE;
            }
            func_ov003_022277fc(fish, 0x10);
            break;
        }
    }
    int very_near = reach >> 9;
    s64 distance_sq = Vec_DistanceSquaredXZ(&fish->position, target);
    if (distance_sq >= (s64) FX_MulFunc(very_near, very_near)) {
        fish->yaw = Vec_YawTo(&fish->position, target);
    }
    fish->unk_23d++;
    return 1;
}
CLEAN_AS(func_ov003_0222b1b4, FishShadowHook_StepNibble)

/* func_ov003_0222b428: FISH_HOOK_HESITATE: it closes in on the float (step 0, faster each
 * frame) until in its size's box, the float bobbing up; dithers about it for 10-14 frames
 * (step 1); then turns 30 degrees either way and swims off (step 2) until out of its
 * retreat box, where it lets go of the line (or flees without one). 0 without a float. */
int FishShadowHook_StepHesitate(FishShadow *fish)
{
    FishingFloat *fishing_float = fish->fishing_float;
    if (fishing_float == NULL) {
        return 0;
    }
    const Vec3 *target = &fishing_float->position;
    switch (fish->hook_step) {
        case FISH_HOOK_HESITATE_CLOSE: {
            fx32 box = fish_swim_hundredths(fish_swim_size(fish->size)->reach);
            int step = fish_swim_ramp(fish);
            fish->yaw = Vec_YawTo(&fish->position, target);
            FishShadow_MoveAlong(&fish->position, step, (u16) fish->yaw);
            if (fish_swim_in_box(fish, target, box)) {
                fish->unk_23d = 0;
                FishingFloat_ToSurface(fishing_float);
                fish->hook_step = FISH_HOOK_HESITATE_DITHER;
            }
            break;
        }
        case FISH_HOOK_HESITATE_DITHER: {
            int frames = func_ov003_0222793c(10, 15);
            if (func_ov003_0222793c(0, 100) < 50) {
                fish->yaw = Vec_YawTo(target, &fish->position);
            } else {
                fish->yaw = Vec_YawTo(&fish->position, target);
            }
            FishShadow_MoveAlong(&fish->position, 0x100, (u16) fish->yaw);
            fish->yaw = Vec_YawTo(&fish->position, target);
            if (fish->unk_23d > frames) {
                fish->unk_23d = 0;
                int sixths = func_ov003_0222791c(1, 2);
                fish->yaw = (s16) (fish->yaw + (s16) (0x1554 * sixths));
                fish->hook_step = FISH_HOOK_HESITATE_LEAVE;
            }
            break;
        }
        case FISH_HOOK_HESITATE_LEAVE: {
            fx32 box = fish_swim_hundredths(fish_swim_size(fish->size)->retreat);
            FishShadow_MoveAlong(&fish->position, 0x14c, (u16) fish->yaw);
            if (!fish_swim_in_box(fish, target, box) && FishShadow_DropLine(fish) == 0) {
                FishShadow_FleeFromPlayer(fish);
            }
            break;
        }
    }
    func_ov003_022277fc(fish, 0x18);
    fish->unk_23d++;
    return 1;
}
CLEAN_AS(func_ov003_0222b428, FishShadowHook_StepHesitate)

/* func_ov003_0222b5c8: FISH_HOOK_APPROACH: it swims to the float (faster each frame, facing
 * it). In its size's box it nibbles (FISH_HOOK_NIBBLE) for 4-179 frames, 96 times in 100 (always
 * when the float is on its kind of water: group 1 of the unit types for the grounds 0-3, group
 * 2 for 5 and 6), else it hesitates (FISH_HOOK_HESITATE). 0 without a float. */
int FishShadowHook_StepApproach(FishShadow *fish)
{
    FishingFloat *fishing_float = fish->fishing_float;
    if (fishing_float == NULL) {
        return 0;
    }
    const Vec3 *target = &fishing_float->position;
    fx32 box = fish_swim_hundredths(fish_swim_size(fish->size)->reach);
    int step = fish_swim_ramp(fish);
    fish->yaw = Vec_YawTo(&fish->position, target);
    FishShadow_MoveAlong(&fish->position, step, (u16) fish->yaw);
    func_ov003_022277fc(fish, 0x18);
    if (fish_swim_in_box(fish, target, box)) {
        int chance = func_ov003_0222793c(0, 100);
        int limit = 95;
        int x;
        int z;
        Position_Tile(&x, &z, (const Position *) target);
        switch (fish->ground) {
            case 0:
            case 1:
            case 2:
            case 3:
                if (UnitTypeInfo_GroupAt(x, z) == 1) {
                    limit = 100;
                }
                break;
            case 5:
            case 6:
                if (UnitTypeInfo_GroupAt(x, z) == 2) {
                    limit = 100;
                }
                break;
        }
        if (chance <= limit) {
            fish->nibble_wait = (u8) func_ov003_0222793c(4, 0xb4);
            fish->unk_13c = 0;
            fish->unk_23d = 0;
            fish->hook_step = FISH_HOOK_NIBBLE_CLOSE;
            fish->hook_state = FISH_HOOK_NIBBLE;
        } else {
            fish->unk_23d = 0;
            fish->hook_step = FISH_HOOK_HESITATE_CLOSE;
            fish->hook_state = FISH_HOOK_HESITATE;
        }
        fish->yaw = Vec_YawTo(&fish->position, target);
    }
    fish->unk_23d++;
    return 1;
}
CLEAN_AS(func_ov003_0222b5c8, FishShadowHook_StepApproach)

/* func_ov003_0222b724: FISH_HOOK_WAIT: once on a float it approaches it (FISH_HOOK_APPROACH;
 * 1), else 0. */
int FishShadowHook_StepWait(FishShadow *fish)
{
    if (fish->fishing_float == NULL) {
        return 0;
    }
    fish->hook_state = FISH_HOOK_APPROACH;
    return 1;
}
CLEAN_AS(func_ov003_0222b724, FishShadowHook_StepWait)

/* func_ov003_0222b744 (the shown step of a hooked shadow): the step of its hook state
 * (data_ov003_0225f190); when that answers 0 the shadow flees from the player. Its frames are
 * counted. */
void FishShadowHook_Update(FishShadow *fish)
{
    if (MemberPointer_CallInt(fish_swim_member(data_ov003_0225f190, fish->hook_state), fish) == 0) {
        FishShadow_FleeFromPlayer(fish);
    }
    fish->unk_13c++;
}
CLEAN_AS(func_ov003_0222b744, FishShadowHook_Update)

/* func_ov003_0222b794 (the placing step of a hooked shadow): nothing. */
void FishShadowHook_StepPlacing(void) {}
CLEAN_AS(func_ov003_0222b794, FishShadowHook_StepPlacing)

/* The shadow's move by `speed` along its yaw with a swing of `swing` across it, by the sine of
 * its wobble (turned 45 degrees first). */
static void fish_swim_wobble_move(FishShadow *fish, int speed, int swing)
{
    fish->wobble = (s16) (fish->wobble + 0x2000);
    int wobble_sin = FX_SinCosTable_[((u16) fish->wobble >> 4) * 2];
    int yaw_sin = FX_SinCosTable_[((u16) fish->yaw >> 4) * 2];
    fx32 dx = FX_MulFunc(speed, yaw_sin);
    dx += FX_MulFunc(swing, wobble_sin);
    wobble_sin = FX_SinCosTable_[((u16) fish->wobble >> 4) * 2];
    int yaw_cos = FX_SinCosTable_[((u16) fish->yaw >> 4) * 2 + 1];
    fx32 dz = FX_MulFunc(speed, yaw_cos);
    dz += FX_MulFunc(swing, wobble_sin);
    fish->position.x += dx;
    fish->position.z += dz;
}

/* func_ov003_0222b798: FISH_SWIM_FLEE: it swims off, wobbling, faster each frame (0.03 more,
 * up to 0.13); the fin beats slower the longer it swims; its effect follows on the surface. */
void FishShadowSwim_Flee(FishShadow *fish)
{
    int speed = (int) ((u32) fish->unk_13c << 7);
    if (speed > 0x215) {
        speed = 0x215;
    }
    fish_swim_wobble_move(fish, speed, speed >> 5);
    if (fish->has_fin) {
        fish_swim_fin_speed(fish, fish->unk_13c, 10, 5);
    } else {
        func_ov003_022277fc(fish, 0x20);
    }
    fish_swim_move_effect(fish);
}
CLEAN_AS(func_ov003_0222b798, FishShadowSwim_Flee)

/* func_ov003_0222b8bc: FISH_SWIM_DRIFT: slowly animated, it drifts with the water; at random
 * once in 100 frames, or after 100 frames, it starts again (FISH_SWIM_START). */
void FishShadowSwim_Drift(FishShadow *fish)
{
    func_ov003_022277fc(fish, 10);
    func_ov003_0222803c(&fish->position, 0x40);
    if (func_ov003_0222793c(0, 100) == 1 || fish->unk_13c > 100) {
        fish->behaviour = FISH_SWIM_START;
    }
}
CLEAN_AS(func_ov003_0222b8bc, FishShadowSwim_Drift)

/* func_ov003_0222b8fc: FISH_SWIM_SLOW_DOWN: from 0.1 a frame it slows by 1/512 each frame and
 * drifts once stopped (FISH_SWIM_DRIFT). */
void FishShadowSwim_SlowDown(FishShadow *fish)
{
    int speed = FISH_SWIM_SPEED - (int) ((u32) fish->unk_13c << 3);
    FishShadow_MoveAlong(&fish->position, speed, (u16) fish->yaw);
    if (fish->unk_13c >= 10) {
        func_ov003_022277fc(fish, 3);
    } else {
        func_ov003_022277fc(fish, 0x10);
    }
    if (speed <= 0) {
        fish->unk_13c = 0;
        fish->behaviour = FISH_SWIM_DRIFT;
    }
}
CLEAN_AS(func_ov003_0222b8fc, FishShadowSwim_SlowDown)

/* func_ov003_0222b960: FISH_SWIM_CRUISE: 0.1 a frame along its yaw for unk_140 frames, then it
 * slows down (FISH_SWIM_SLOW_DOWN).
 * QUIRK: the count is 16 bits; one of 0 runs 65536 frames. */
void FishShadowSwim_Cruise(FishShadow *fish)
{
    FishShadow_MoveAlong(&fish->position, FISH_SWIM_SPEED, (u16) fish->yaw);
    func_ov003_022277fc(fish, 0x20);
    fish->unk_140 = (s16) (fish->unk_140 - 1);
    if (fish->unk_140 == 0) {
        fish->unk_13c = 0;
        fish->behaviour = FISH_SWIM_SLOW_DOWN;
    }
}
CLEAN_AS(func_ov003_0222b960, FishShadowSwim_Cruise)

/* func_ov003_0222b9b4: FISH_SWIM_SPEED_UP: it swims on, wobbling, 1/512 faster each frame,
 * and cruises (FISH_SWIM_CRUISE) once past 0.1 a frame. */
void FishShadowSwim_SpeedUp(FishShadow *fish)
{
    int speed = (int) ((u32) fish->unk_13c << 3);
    fish_swim_wobble_move(fish, speed, speed >> 2);
    if (fish->unk_13c >= 10) {
        func_ov003_022277fc(fish, 0x20);
    } else {
        func_ov003_022277fc(fish, 0x10);
    }
    if (speed > FISH_SWIM_SPEED) {
        fish->behaviour = FISH_SWIM_CRUISE;
    }
}
CLEAN_AS(func_ov003_0222b9b4, FishShadowSwim_SpeedUp)

/* func_ov003_0222ba8c: FISH_SWIM_START: a new course: turned by up to 60 degrees either way,
 * to cruise for 1 or 2 frames, a wobble of 15-45 degrees either way and a side to turn to,
 * then it speeds up (FISH_SWIM_SPEED_UP). */
void FishShadowSwim_Start(FishShadow *fish)
{
    fish->yaw = (s16) (fish->yaw + (s16) func_ov003_0222791c(0, 0x2aa8));
    fish->unk_13c = 0;
    fish->unk_140 = (u8) func_ov003_0222793c(1, 3);
    fish->wobble = (s16) func_ov003_0222791c(0xaaa, 0x2000);
    fish->unk_210 = func_ov003_0222791c(0, 2) != 0;
    fish->behaviour = FISH_SWIM_SPEED_UP;
}
CLEAN_AS(func_ov003_0222ba8c, FishShadowSwim_Start)

/* The shadow turned by `amount` towards its side (unk_210), or the other way. */
static void fish_swim_turn(FishShadow *fish, int amount)
{
    fish->yaw = (s16) (fish->unk_210 != 0 ? fish->yaw + amount : fish->yaw - amount);
}

/* func_ov003_0222bb0c (the shown step of a free shadow): the shadow of kind 0xb listens for the
 * player first (FishShadowSense_Step); then the step of its swimming state
 * (data_ov003_0225f160) and the check of where it went (FishShadow_CheckMove, not while
 * fleeing): blocked, it turns towards its side (while speeding up only, for the blocks of
 * grounds 5 and 6); at the edge columns it turns back towards the middle unless drifting; with
 * water behind it, speeding up or cruising, it turns towards its side unless facing nearly
 * straight back. Its frames are counted. Unless its line was dropped or it flees it tries to
 * bite (FishShadow_TryBite; when it does, its frames start again and it waits on the float);
 * otherwise its hook state is cleared and, standing on its kind of water (group 1 for the
 * grounds 0-3, group 2 for 5 and 6), it escapes (func_ov003_022282b8). */
void FishShadowSwim_Update(FishShadow *fish)
{
    if (fish->kind == FISH_SWIM_KIND_WITH_SENSE) {
        FishShadowSense_Step(&fish->sense, fish);
    }
    MemberPointer_CallVoid(fish_swim_member(data_ov003_0225f160, fish->behaviour), fish);
    int blocked = fish->behaviour == FISH_SWIM_FLEE ? 0 : FishShadow_CheckMove(fish);
    switch (blocked) {
        case 0:
            fish->unk_201 = 0;
            break;
        case 1:
        case 3:
            fish_swim_turn(fish, FISH_SWIM_TURN);
            break;
        case 2:
        case 4:
            if (fish->behaviour == FISH_SWIM_SPEED_UP) {
                fish_swim_turn(fish, FISH_SWIM_TURN);
            }
            break;
        case 6:
            if (fish->behaviour != FISH_SWIM_DRIFT && (fish->yaw < 0x3556 || fish->yaw > 0x4aaa)) {
                fish->yaw = (s16) (fish->yaw - FISH_SWIM_EDGE_TURN);
            }
            break;
        case 7:
            if (fish->behaviour != FISH_SWIM_DRIFT && (fish->yaw > -0x3556 || fish->yaw < -0x4aaa)) {
                fish->yaw = (s16) (fish->yaw + FISH_SWIM_EDGE_TURN);
            }
            break;
        case 5:
            if (fish->behaviour == FISH_SWIM_SPEED_UP || fish->behaviour == FISH_SWIM_CRUISE) {
                int facing = fish->yaw < 0 ? -fish->yaw : fish->yaw;
                if (facing < 0x7556) {
                    fish_swim_turn(fish, FISH_SWIM_EDGE_TURN);
                }
            }
            break;
    }
    fish->unk_13c++;
    if (fish->hook_state != FISH_SHADOW_HOOK_DROPPED && fish->behaviour != FISH_SWIM_FLEE) {
        if (FishShadow_TryBite(fish) != 0) {
            fish->unk_13c = 0;
            fish->hook_state = FISH_HOOK_WAIT;
        }
        return;
    }
    fish->hook_state = FISH_HOOK_WAIT;
    int water_group;
    switch (fish->ground) {
        case 0:
        case 1:
        case 2:
        case 3:
            water_group = 1;
            break;
        case 5:
        case 6:
            water_group = 2;
            break;
        default:
            return;
    }
    int x;
    int z;
    Position_Tile(&x, &z, (const Position *) &fish->position);
    if (UnitTypeInfo_GroupAt(x, z) == water_group) {
        func_ov003_022282b8(fish, &fish->last_position);
    }
}
CLEAN_AS(func_ov003_0222bb0c, FishShadowSwim_Update)

/* func_ov003_0222bd40 (the placing step of a free shadow): from where it was placed (unk_12c),
 * the step of its swimming state and the check of where it went: blocked, it turns (by 60
 * degrees in group 0; a random yaw within 15 degrees either way in group 1) and
 * its count of clear steps (unk_201) starts again; else that count goes up. Its frames go up by
 * 2. */
void FishShadowSwim_Settle(FishShadow *fish)
{
    fish->position = fish->unk_12c;
    MemberPointer_CallVoid(fish_swim_member(data_ov003_0225f160, fish->behaviour), fish);
    int blocked = FishShadow_CheckMove(fish);
    if (blocked != 0 && blocked != 5) {
        if (fish->group_state == FISH_SHADOW_IN_GROUP0) {
            fish->yaw = (s16) (fish->yaw + 0x2aa8);
        } else {
            fish->yaw = (s16) func_ov003_0222791c(0, 0xaaa);
        }
        fish->unk_201 = 0;
    } else {
        fish->unk_201++;
    }
    fish->unk_13c += 2;
}
CLEAN_AS(func_ov003_0222bd40, FishShadowSwim_Settle)

/* func_ov003_0222be08: the shown step by whether the shadow is on a float
 * (data_ov003_0225f118: FishShadowSwim_Update, FishShadowHook_Update). */
void FishShadow_StepShown(FishShadow *fish)
{
    MemberPointer_CallVoid(&fish_swim_pair(fish->hooked)->shown, fish);
}
CLEAN_AS(func_ov003_0222be08, FishShadow_StepShown)

/* func_ov003_0222be40: the placing step by whether the shadow is on a float
 * (FishShadowSwim_Settle, FishShadowHook_StepPlacing). */
void FishShadow_StepPlacing(FishShadow *fish)
{
    MemberPointer_CallVoid(&fish_swim_pair(fish->hooked)->placing, fish);
}
CLEAN_AS(func_ov003_0222be40, FishShadow_StepPlacing)

/* func_ov003_0222be78: `position` moved `distance` along `angle` (x by its sine, z by its
 * cosine). */
void FishShadow_MoveAlong(Vec3 *position, int distance, u16 angle)
{
    FishShadow_MoveSin(&position->x, distance, angle);
    FishShadow_MoveCos(&position->z, distance, angle);
}
CLEAN_AS(func_ov003_0222be78, FishShadow_MoveAlong)

/* func_ov003_0222be98: `value` moved by `distance` times the cosine of `angle`. */
void FishShadow_MoveCos(fx32 *value, int distance, int angle)
{
    *value += FX_MulFunc(distance, FX_SinCosTable_[((u16) angle >> 4) * 2 + 1]);
}
CLEAN_AS(func_ov003_0222be98, FishShadow_MoveCos)

/* func_ov003_0222bec4: `value` moved by `distance` times the sine of `angle`. */
void FishShadow_MoveSin(fx32 *value, int distance, int angle)
{
    *value += FX_MulFunc(distance, FX_SinCosTable_[((u16) angle >> 4) * 2]);
}
CLEAN_AS(func_ov003_0222bec4, FishShadow_MoveSin)
