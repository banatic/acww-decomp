/* The fish of the museum's aquarium (aquarium_fish.h). */
#include "aquarium_fish.h"

#include <string.h>

#include "autoload_2/approach.h"
#include "clean.h"

static_assert(sizeof(AquariumFishInfo) == 17, "fish info");
static_assert(sizeof(AquariumFishBody) == 0x50, "fish body");
static_assert(offsetof(AquariumFish, body.base.body.push) == 0x14, "fish push");
static_assert(offsetof(AquariumFish, body.base.body.touched) == 0x40, "fish touched");
static_assert(offsetof(AquariumFish, anims) == 0x54, "fish anims");
static_assert(offsetof(AquariumFish, model) == 0x64, "fish model");
static_assert(offsetof(AquariumFish, model.frames.speed) == 0x110, "fish anim speed");
static_assert(offsetof(AquariumFish, index) == 0x15c, "fish index");
static_assert(offsetof(AquariumFish, files) == 0x168, "fish files");
static_assert(offsetof(AquariumFish, position) == 0x1a8, "fish position");
static_assert(offsetof(AquariumFish, yaw) == 0x1c0, "fish yaw");
static_assert(offsetof(AquariumFish, level) == 0x1cc, "fish level");
static_assert(offsetof(AquariumFish, focus) == 0x1e8, "fish focus");
static_assert(offsetof(AquariumFish, away_yaw) == 0x1ec, "fish away yaw");
static_assert(offsetof(AquariumFish, met) == 0x1f4, "fish met");
static_assert(offsetof(AquariumFish, swim_204) == 0x204, "fish swim");
static_assert(offsetof(AquariumFish, speed) == 0x20c, "fish speed");
static_assert(offsetof(AquariumFish, turning) == 0x22f, "fish turning");
static_assert(offsetof(AquariumFish, swim_230) == 0x230, "fish swim 230");
static_assert(sizeof(AquariumFish) == 0x258, "fish");

/* What each kind is like, and the fish by kind (museum_aquarium.c). */
extern const AquariumFishInfo data_ov004_02247924[];
extern AquariumFish *data_ov004_022594d4[AQUARIUM_FISH_KINDS];

extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern fx32 FX_MulFunc(fx32 a, fx32 b);

#define ONE 0x1000

/* A body index from this one on is a rock's. */
#define FIRST_ROCK_INDEX AQUARIUM_FISH_KINDS
/* What a fish notes on touching a rock. */
#define MET_ROCK 0x20

/* The part of the room a fish turns back at (x of its position). */
#define ROOM_LEFT_END 0x5000
#define ROOM_RIGHT_END 0x1e000

/* The fastest a fish's animation runs, and the speed it is measured against. */
#define FISH_ANIM_TOP 0x1800

/* The ways it turns from the glass (a sixteenth of a turn either side of a quarter), and how
 * fast; how fast it turns to its target, the big kinds slower. */
#define TURN_FROM_GLASS_FAR 0x471c
#define TURN_FROM_GLASS_NEAR 0x38e4
#define TURN_FROM_GLASS_STEP 0x222
#define TURN_STEP 0x16c
#define TURN_STEP_BIG 0x88
#define BIG_SIZE 4
#define SLOW_SPEED 0x99a

/* The word of `met` that holds the bit of `kind`, at its place in the fish (a kind of 64 or
 * more reaches the fields after it, as the game's code does). */
static u8 *AquariumFish_met_word(AquariumFish *fish, int kind)
{
    return (u8 *) fish + offsetof(AquariumFish, met) + (kind >> 5) * 4;
}

static int AquariumFish_has_met(AquariumFish *fish, int kind)
{
    u32 word;
    memcpy(&word, AquariumFish_met_word(fish, kind), sizeof word);
    return (word & (1u << (kind & 31))) != 0;
}

static void AquariumFish_note_met(AquariumFish *fish, int kind)
{
    u32 word;
    u8 *at = AquariumFish_met_word(fish, kind);
    memcpy(&word, at, sizeof word);
    word |= 1u << (kind & 31);
    memcpy(at, &word, sizeof word);
}

/* func_ov004_022354e0: the fish's swimming values from its kind's table entry (the
 * fixed-point ones scaled up from bytes). */
void AquariumFish_SetSwim(AquariumFish *fish)
{
    const u8 *swim = data_ov004_02247924[fish->index].swim;
    fish->top_speed = (fx32) swim[2] << 2;
    fish->swim_214 = swim[0];
    fish->swim_218 = swim[1] >> 1;
    fish->swim_204[0] = swim[3];
    fish->swim_204[1] = swim[4];
    fish->swim_204[2] = swim[5];
    fish->swim_204[3] = swim[6];
    fish->swim_230 = swim[7];
    fish->swim_224 = swim[8] << 2;
    fish->level = ((fx32) swim[9] << 7) - ONE;
    fish->swim_228 = ((fx32) swim[10] << 6) - ONE;
}
CLEAN_AS(func_ov004_022354e0, AquariumFish_SetSwim)

/* func_ov004_022355f4: a fish that is touching nothing, not turning and kept off the glass this
 * frame turns its yaw further round: one facing right of straight on (yaw from 0) to 0x471c
 * once past a quarter turn, else to 0x38e4; one facing left to -0x38e4.
 * BUG: the left side never turns to -0x471c: the size of the yaw is compared with
 * -0x4000. */
void AquariumFish_TurnFromGlass(AquariumFish *fish)
{
    if (fish->body.base.body.touched || fish->turning || !fish->hit_glass) {
        return;
    }
    int yaw = fish->yaw;
    if (yaw >= 0) {
        Approach_S16(&fish->yaw, yaw >= 0x4000 ? TURN_FROM_GLASS_FAR : TURN_FROM_GLASS_NEAR, TURN_FROM_GLASS_STEP);
    } else {
#ifdef BUGFIX
        int far = -yaw >= 0x4000;
#else
        int far = 0;
#endif
        Approach_S16(&fish->yaw, far ? -TURN_FROM_GLASS_FAR : -TURN_FROM_GLASS_NEAR, TURN_FROM_GLASS_STEP);
    }
}
CLEAN_AS(func_ov004_022355f4, AquariumFish_TurnFromGlass)

/* func_ov004_02235698 (at the end of the fish's frame): a fish it pays attention to or makes
 * way for that it did not meet this frame is forgotten (its own kind again; making way ends);
 * then this frame's meetings and glass are forgotten. */
void AquariumFish_ClearMeetings(AquariumFish *fish)
{
    int own = fish->index;
    int focus = fish->focus;
    if (focus != own) {
        if (!AquariumFish_has_met(fish, focus)) {
            fish->focus = (u8) own;
        }
        if (!AquariumFish_has_met(fish, fish->yield_to)) {
            fish->yield_to = (u8) fish->index;
            fish->yielding = 0;
        }
    }
    fish->met[0] = 0;
    fish->met[1] = 0;
    fish->meetings = 0;
    fish->hit_glass = 0;
}
CLEAN_AS(func_ov004_02235698, AquariumFish_ClearMeetings)

/* func_ov004_02235728: the fish in `slot` meets the one in `other`: it counts the meeting and
 * notes the other's kind; it turns its attention to the other when it paid attention to none,
 * when the other is bigger, or as big and met in a way of higher flags than its own (the
 * flags then add up). */
void AquariumFish_Meet(void *body, AquariumFish **slot, AquariumFish **other)
{
    (void) body;
    AquariumFish *fish = *slot;
    fish->meetings++;
    int own = fish->index;
    int focus = fish->focus;
    int next = (*other)->index;
    int way = AquariumFish_MeetingWay(fish, other);
    int flags = fish->meeting;
    AquariumFish_note_met(fish, next);
    int focus_size = data_ov004_02247924[focus].size;
    int next_size = data_ov004_02247924[next].size;
    if (focus == own || focus_size < next_size || (focus_size == next_size && flags < way)) {
        fish->meeting = (u8) (way | flags);
        fish->focus = (u8) next;
        fish->yielding = 0;
    }
}
CLEAN_AS(func_ov004_02235728, AquariumFish_Meet)

/* func_ov004_02235810 (the body's slot 2, on touching the body of `kind` and `index`): a rock
 * is noted in the fish's meeting flags; a fish of the river room, or a sea fish of a size
 * above 0, is met both ways. */
void AquariumFishBody_Touched(AquariumFishBody *body, int kind, unsigned int index)
{
    (void) kind;
    if (body->owner == NULL) {
        return;
    }
    AquariumFish *owner = body->owner;
    if (index >= FIRST_ROCK_INDEX) {
        owner->meeting |= MET_ROCK;
    } else if (data_ov004_02247924[index].size != 0 || index < AQUARIUM_RIVER_FISH) {
        AquariumFish **other = &data_ov004_022594d4[index];
        AquariumFish_Meet(body, &owner, other);
        AquariumFish_Meet(body, other, &owner);
    }
}
CLEAN_AS(func_ov004_02235810, AquariumFishBody_Touched)

/* func_ov004_02235870: unless in mode 1, a fish at either end of the room has its yaw kept
 * off the room's length; in mode 6 it goes on in mode 2. */
void AquariumFish_KeepOffRoomEnds(AquariumFish *fish)
{
    if (fish->mode == AQUARIUM_FISH_MODE_1) {
        return;
    }
    if (fish->position.x <= ROOM_LEFT_END || fish->position.x >= ROOM_RIGHT_END) {
        AquariumFish_KeepYawAcross(fish);
        if (fish->mode == AQUARIUM_FISH_MODE_6) {
            fish->mode = AQUARIUM_FISH_MODE_2;
        }
    }
}
CLEAN_AS(func_ov004_02235870, AquariumFish_KeepOffRoomEnds)

/* func_ov004_022358b8 (slot 1 of two classes): nothing to do. */
void AquariumFish_UpdateNothing(void) {}
CLEAN_AS(func_ov004_022358b8, AquariumFish_UpdateNothing)

/* func_ov004_022358bc (slot 0 of a class): nothing to do. */
void AquariumFish_SetUpNothing(void) {}
CLEAN_AS(func_ov004_022358bc, AquariumFish_SetUpNothing)

/* func_ov004_022358c0: the fish's animation speed: 1.5 in mode 1, else 1.5 times its speed's
 * share of its top speed (counted three times in mode 3, a third in mode 5), kept from `least`
 * to 1.5. */
void AquariumFish_SetAnimSpeed(AquariumFish *fish, fx32 least)
{
    u8 mode = fish->mode;
    fx32 speed;
    if (mode == AQUARIUM_FISH_MODE_1) {
        speed = FISH_ANIM_TOP;
    } else {
        speed = fish->speed;
        if (mode == AQUARIUM_FISH_MODE_3) {
            speed = (fx32) ((u32) speed * 3u);
        } else if (mode == AQUARIUM_FISH_MODE_5) {
            speed = speed / 3;
        }
        speed = FX_MulFunc(FX_Div(speed, fish->top_speed), FISH_ANIM_TOP);
        if (speed < least) {
            speed = least;
        } else if (speed > FISH_ANIM_TOP) {
            speed = FISH_ANIM_TOP;
        }
    }
    fish->model.frames.speed = speed;
}
CLEAN_AS(func_ov004_022358c0, AquariumFish_SetAnimSpeed)

/* func_ov004_0223592c: a turning fish turns to its target yaw (big kinds slower), and stops
 * turning once there; not in mode 1, nor slow (0.6 or less) in mode 5. */
void AquariumFish_Turn(AquariumFish *fish)
{
    if ((fish->speed <= SLOW_SPEED && fish->mode == AQUARIUM_FISH_MODE_5) || fish->mode == AQUARIUM_FISH_MODE_1 ||
        !fish->turning) {
        return;
    }
    s16 step = data_ov004_02247924[fish->index].size >= BIG_SIZE ? TURN_STEP_BIG : TURN_STEP;
    if (Approach_S16(&fish->yaw, fish->target_yaw, step) != 0) {
        fish->turning = 0;
    }
}
CLEAN_AS(func_ov004_0223592c, AquariumFish_Turn)

/* func_ov004_022359c8: two fish passing each other: the one of lower level goes down and the
 * other up (on a tie the first goes up); the other takes its way only while it is not making
 * way for someone. */
void AquariumFish_SetPassingWays(AquariumFish *fish, AquariumFish **other)
{
    if (fish->level < (*other)->level) {
        fish->vertical = -1;
        if (!(*other)->yielding) {
            (*other)->vertical = 1;
        }
    } else {
        fish->vertical = 1;
        if (!(*other)->yielding) {
            (*other)->vertical = -1;
        }
    }
}
CLEAN_AS(func_ov004_022359c8, AquariumFish_SetPassingWays)

/* How the fish swim: their modes, their meetings and the stylus on the glass. */

#include <stdint.h>

#include "main/actor.h"
#include "main/model_object.h"
#include "main/scene_query.h"
#include "main/touch_pick_shapes.h"
#include "member_pointer.h"
#include "aquarium_swim.h"

static_assert(offsetof(AquariumFish, timer) == 0x158, "fish timer");
static_assert(offsetof(AquariumFish, turnbacks) == 0x1eb, "fish turnbacks");
static_assert(offsetof(AquariumFish, glass_turning) == 0x1fc, "fish glass turning");
static_assert(offsetof(AquariumFish, glass_step) == 0x200, "fish glass step");
static_assert(offsetof(AquariumFish, cruise_frames) == 0x202, "fish cruise frames");
static_assert(offsetof(AquariumFish, pitch_steps) == 0x23c, "fish pitch steps");
static_assert(offsetof(AquariumFish, flee_yaw) == 0x24c, "fish flee yaw");
static_assert(offsetof(AquariumFish, levelling) == 0x24e, "fish levelling");
static_assert(offsetof(AquariumFish, last_focus) == 0x252, "fish last focus");
static_assert(offsetof(AquariumFish, unk_255) == 0x255, "fish class bytes");
static_assert(offsetof(AquariumFishHookState, hook_timings) == 0x8c, "hook timings");

/* The member functions of the modes; and those of the room shown (data_ov004_022593a0): a
 * plain fish's set-up and frame in each. */
extern const MemberPointer data_ov004_0225949c[7];
extern const MemberPointer data_ov004_02259424[4];
extern u8 data_ov004_022593a0;
/* With data_021f6c34: the pen came down this frame. */
extern u8 data_021f6c38;
extern u8 data_021f6c34;

/* The model hooks handed to the game. */
extern void func_ov004_0223653c(AquariumFishHookState *state);
extern void func_ov004_0223655c(AnimatedModelNodeState *state);
extern void func_ov004_02236578(AnimatedModelNodeState *state);

/* NitroSystem's node description command, and when its hook runs (timings A and B). */
#define G3D_COMMAND_NODE_DESC 6
#define G3D_TIMING_BEFORE 1
#define G3D_TIMING_AFTER 2

#define QUARTER_TURN 0x4000
#define HALF_TURN 0x8000

/* The kinds with a way of their own in the plain fish's frames. */
#define KIND_FISH_29 29
#define KIND_FISH_41 41
#define KIND_FISH_43 43
#define KIND_FISH_45 45
#define KIND_FISH_46 46
#define KIND_FISH_55 55

/* What a tank's glass is to the stylus (museum_aquarium.c). */
#define GLASS_KIND 0x13

/* How long a fish keeps paying attention to the same one before it is startled away from it:
 * when it is no wider than the other, and else. */
#define FOCUS_STARTLE_FRAMES 125
#define FOCUS_STARTLE_FRAMES_WIDER 145

/* The sizes that flee a random way rather than straight from what startled them. */
static int AquariumFish_is_mid_size(u8 size)
{
    return size == 4 || size == 5;
}

/* The fish's position, by address (the fish may be missing, as the game's code allows). */
static const Vec3 *AquariumFish_position_of(AquariumFish *fish)
{
    return (const Vec3 *) ((uintptr_t) fish + offsetof(AquariumFish, position));
}

static int AquariumFish_abs(int value)
{
    return value < 0 ? -value : value;
}

static int AquariumFish_mul(int a, int b)
{
    return (int) ((u32) a * (u32) b);
}

/* The member function of the fish's mode. */
static void AquariumFish_run_mode(AquariumFish *fish)
{
    MemberPointer_CallVoid(&data_ov004_0225949c[fish->mode], fish);
}

/* A fish's way up or down when it sets off: down from its top (level), up from its bottom
 * (swim_228), else either at random; not while it pays attention to another. */
static void AquariumFish_choose_vertical(AquariumFish *fish)
{
    if (fish->focus != fish->index) {
        return;
    }
    if (fish->position.y >= fish->level) {
        fish->vertical = -1;
    } else if (fish->position.y <= fish->swim_228) {
        fish->vertical = 1;
    } else {
        fish->vertical = AquariumSwim_Random(0, 2) > 0 ? 1 : -1;
    }
}

/* func_ov004_02235a18: how the fish and the other it met swim from each other
 * (AQUARIUM_MEET_*). Each heading is taken from the line at right angles to the line between
 * them: the pair of flags says on which sides of that line the two headings lie, the second
 * flag of the pair when both are turned to the same side of the line between them. */
int AquariumFish_MeetingWay(AquariumFish *fish, AquariumFish **other)
{
    AquariumFish *them = *other;
    int their_yaw = them->yaw;
    s16 across = (s16) (Vec_YawTo(&fish->position, &them->position) - QUARTER_TURN);
    int mine = (s16) (fish->yaw - across);
    int theirs = (s16) (their_yaw - across);
    int first, second;
    if (mine * theirs < 0) {
        first = AQUARIUM_MEET_FACING;
        second = AQUARIUM_MEET_FACING_SAME;
    } else if (mine < 0) {
        first = AQUARIUM_MEET_CHASED;
        second = AQUARIUM_MEET_CHASED_SAME;
    } else {
        first = AQUARIUM_MEET_CHASING;
        second = AQUARIUM_MEET_CHASING_SAME;
    }
    mine = AquariumFish_abs(mine);
    theirs = AquariumFish_abs(theirs);
    return (mine - QUARTER_TURN) * (theirs - QUARTER_TURN) < 0 ? first : second;
}
CLEAN_AS(func_ov004_02235a18, AquariumFish_MeetingWay)

/* func_ov004_02235ac4: the fish forgets how it met anyone and heads on its own way; the one it
 * paid attention to stops making way, and it pays attention to and makes way for nobody. */
void AquariumFish_ForgetFocus(AquariumFish *fish)
{
    fish->meeting = 0;
    fish->yielding = 0;
    fish->away_yaw = fish->yaw;
    u8 focus = fish->focus;
    if (focus != fish->index) {
        AquariumFish *other = data_ov004_022594d4[focus];
        if (other != NULL) {
            other->yielding = 0;
        }
        fish->focus = (u8) fish->index;
        fish->yield_to = (u8) fish->index;
    }
}
CLEAN_AS(func_ov004_02235ac4, AquariumFish_ForgetFocus)

/* The fish and the other head the same way along z: when this fish is `behind` it heads back
 * from the other's way; else the other, unless it already makes way, makes way for this fish,
 * heading back from it. Then they take their ways up and down to pass. */
static void AquariumFish_give_way_along(AquariumFish *fish, AquariumFish **slot, int behind)
{
    AquariumFish *other = *slot;
    if (behind) {
        fish->away_yaw = (s16) (other->yaw + HALF_TURN);
    } else if (!other->yielding) {
        other->yielding = 1;
        (*slot)->yield_to = (u8) fish->index;
        (*slot)->away_yaw = (s16) (fish->yaw + HALF_TURN);
    }
    AquariumFish_SetPassingWays(fish, slot);
}

/* func_ov004_02235b28: the fish passes the one it pays attention to (when there is one). When
 * both head towards -z (yaw a quarter turn or more either way), this fish is behind when its z
 * is larger; when both head towards +z, when its z is smaller (AquariumFish_give_way_along).
 * Otherwise it heads at right angles to the line from the other, on the side it faces. */
void AquariumFish_GiveWay(AquariumFish *fish)
{
    AquariumFish **slot = &data_ov004_022594d4[fish->focus];
    AquariumFish *other = *slot;
    if (other == NULL) {
        return;
    }
    int own = AquariumFish_abs(fish->yaw);
    int theirs = AquariumFish_abs(other->yaw);
    if (own >= QUARTER_TURN && theirs >= QUARTER_TURN) {
        AquariumFish_give_way_along(fish, slot, fish->position.z > other->position.z);
    } else if (own <= QUARTER_TURN && theirs <= QUARTER_TURN) {
        AquariumFish_give_way_along(fish, slot, fish->position.z < other->position.z);
    } else {
        s16 from = Vec_YawTo(&other->position, &fish->position);
        if ((s16) (from - fish->yaw) < 0) {
            fish->away_yaw = (s16) (from - QUARTER_TURN);
        } else {
            fish->away_yaw = (s16) (from + QUARTER_TURN);
        }
    }
}
CLEAN_AS(func_ov004_02235b28, AquariumFish_GiveWay)

/* The fish is startled away from the one it pays attention to, and counts afresh. */
static void AquariumFish_startle_from(AquariumFish *fish, AquariumFish *other)
{
    AquariumFish_Startle(fish, &other->position);
    fish->focus_frames = 0;
}

/* func_ov004_02235c54 (each frame but in mode 1): a fish that touched nothing forgets whom it
 * paid attention to; one that met no fish forgets too, and goes up. Otherwise it counts the
 * frames it keeps paying attention to the same one, and after FOCUS_STARTLE_FRAMES is startled
 * away from it when the other's body is as wide or wider, else after
 * FOCUS_STARTLE_FRAMES_WIDER. A fish resting (in the sea room also slowing down) sets off
 * again; one chased by a fish no smaller cruises; one facing the other gives way unless it
 * already makes way; one that touched a rock goes up, making way. Then it turns towards its
 * way away. */
void AquariumFish_ReactToFocus(AquariumFish *fish)
{
    if (fish->mode == AQUARIUM_MODE_FLEE) {
        return;
    }
    if (!fish->body.base.body.touched) {
        AquariumFish_ForgetFocus(fish);
        return;
    }
    if (!fish->meetings) {
        AquariumFish_ForgetFocus(fish);
        fish->vertical = 1;
        return;
    }
    if (fish->last_focus != fish->focus) {
        fish->last_focus = fish->focus;
        fish->focus_frames = 0;
    } else {
        fish->focus_frames++;
        u8 frames = fish->focus_frames;
        if (frames >= FOCUS_STARTLE_FRAMES) {
            AquariumFish *other = data_ov004_022594d4[fish->focus];
            if (other == NULL) {
                return;
            }
            if (data_ov004_02247924[fish->index].body_radius <= data_ov004_02247924[other->index].body_radius) {
                AquariumFish_startle_from(fish, other);
                return;
            }
            if (frames >= FOCUS_STARTLE_FRAMES_WIDER) {
                AquariumFish_startle_from(fish, other);
                return;
            }
        }
    }
    if (fish->mode == AQUARIUM_MODE_REST || (fish->mode == AQUARIUM_MODE_SLOW_DOWN && fish->index >= AQUARIUM_RIVER_FISH)) {
        fish->mode = AQUARIUM_MODE_NEW_COURSE;
    }
    if (fish->meeting & (AQUARIUM_MEET_CHASED | AQUARIUM_MEET_CHASED_SAME)) {
        if (fish->mode != AQUARIUM_MODE_CRUISE &&
            data_ov004_02247924[fish->index].size <= data_ov004_02247924[fish->focus].size) {
            fish->mode = AQUARIUM_MODE_CRUISE;
            fish->timer = 0;
        }
    }
    if (fish->meeting >= AQUARIUM_MEET_FACING) {
        if (!fish->yielding) {
            AquariumFish_GiveWay(fish);
        }
    } else if (fish->meeting & AQUARIUM_MEET_ROCK) {
        fish->vertical = 1;
        fish->yielding = 1;
    }
    Approach_S16(&fish->yaw, fish->away_yaw, 0x38e);
}
CLEAN_AS(func_ov004_02235c54, AquariumFish_ReactToFocus)

/* func_ov004_02235ddc: a fish at either end of the sea room's tank (by whole units of x: 0 or
 * less and 34 or more for the fish of area 1, -2 and 36 for the others) faces back in along x
 * and goes to its height.
 * QUIRK: the height is the table's depth without the 1.0 below that placing a fish takes off
 * (museum_aquarium.c). */
void AquariumFish_TurnAtTankEnds(AquariumFish *fish)
{
    int low, high;
    if (fish->area == 1) {
        low = 0;
        high = 34;
    } else {
        low = -2;
        high = 36;
    }
    int x = fish->position.x >> 12;
    if (x <= low) {
        fish->yaw = QUARTER_TURN;
        fish->position.y = (fx32) data_ov004_02247924[fish->index].depth << 6;
    } else if (x >= high) {
        fish->yaw = -QUARTER_TURN;
        fish->position.y = (fx32) data_ov004_02247924[fish->index].depth << 6;
    }
}
CLEAN_AS(func_ov004_02235ddc, AquariumFish_TurnAtTankEnds)

/* func_ov004_02235e58: the fish's yaw kept 60 to 120 degrees (0x2aac to 0x5554) from yaw 0
 * either way, so it swims across the room's length. */
void AquariumFish_KeepYawAcross(AquariumFish *fish)
{
    s16 yaw = fish->yaw;
    int size = AquariumFish_abs(yaw);
    if (size > 0x5554) {
        fish->yaw = yaw >= 0 ? 0x5554 : -0x5554;
    } else if (size < 0x2aac) {
        fish->yaw = yaw >= 0 ? 0x2aac : -0x2aac;
    }
}
CLEAN_AS(func_ov004_02235e58, AquariumFish_KeepYawAcross)

/* func_ov004_02235eac (mode 5 of the table data_ov004_0225946c): the fish slows down by its
 * deceleration (swim_218) a frame, moving on at its speed; at 0xf6 or less it keeps that speed
 * and sets off again, its timer at 3. */
void AquariumFish_ModeEaseOff(AquariumFish *fish)
{
    fish->speed = (fx32) ((u32) fish->top_speed - (u32) AquariumFish_mul(fish->swim_218, fish->timer));
    AquariumSwim_Move(&fish->position, fish->speed, fish->yaw);
    if (fish->speed <= 0xf6) {
        fish->speed = 0xf6;
        fish->timer = 3;
        fish->mode = AQUARIUM_MODE_NEW_COURSE;
    }
}
CLEAN_AS(func_ov004_02235eac, AquariumFish_ModeEaseOff)

/* func_ov004_02235f10 (mode 2 of the table data_ov004_0225946c): the fish sets off, without
 * stopping: a random time to cruise (swim_204[1] up to swim_204[0]), none to rest, level;
 * after meeting others it turns 15 to 30 degrees either way; it takes its way up or down and
 * speeds up. */
void AquariumFish_ModeSetOff(AquariumFish *fish)
{
    fish->timer = 1;
    fish->cruise_frames = (u8) AquariumSwim_Random(fish->swim_204[1], fish->swim_204[0]);
    fish->rest_frames = 0;
    fish->pitch_steps = 0;
    if (fish->meetings != 0) {
        fish->target_yaw = (s16) (fish->target_yaw + AquariumSwim_RandomAngle(30, 15));
    }
    AquariumFish_choose_vertical(fish);
    fish->mode = AQUARIUM_MODE_SPEED_UP;
}
CLEAN_AS(func_ov004_02235f10, AquariumFish_ModeSetOff)

/* func_ov004_02235fe0 (mode 0): nothing to do. */
void AquariumFish_ModeNone(void) {}
CLEAN_AS(func_ov004_02235fe0, AquariumFish_ModeNone)

/* func_ov004_02235fe4 (mode 1): for 40 frames the fish flees at its top speed, turning to its
 * way to flee (the sizes 4 and 5 by a third of what is left, at most 0xaaa a frame; the others
 * by half); then it is no longer startled and sets off again. */
void AquariumFish_ModeFlee(AquariumFish *fish)
{
    if (fish->timer <= 40) {
        if (AquariumFish_is_mid_size(fish->size)) {
            Approach_DivideS16(&fish->yaw, fish->flee_yaw, 3, 0xaaa);
        } else {
            Approach_DivideS16(&fish->yaw, fish->flee_yaw, 2, QUARTER_TURN);
        }
        fish->speed = fish->top_speed;
        AquariumSwim_Move(&fish->position, fish->speed, fish->yaw);
    } else {
        fish->startled = 0;
        fish->mode = AQUARIUM_MODE_NEW_COURSE;
    }
}
CLEAN_AS(func_ov004_02235fe4, AquariumFish_ModeFlee)

/* func_ov004_02236078 (mode 6): the fish rests (speed 0) for its rest time, then sets off
 * again. The fish. */
AquariumFish *AquariumFish_ModeRest(AquariumFish *fish)
{
    fish->speed = 0;
    if (fish->timer >= fish->rest_frames) {
        fish->timer = 0;
        fish->mode = AQUARIUM_MODE_NEW_COURSE;
    }
    return fish;
}
CLEAN_AS(func_ov004_02236078, AquariumFish_ModeRest)

/* func_ov004_022360ac (mode 5): the fish slows down by its deceleration (swim_218) a frame,
 * moving on at its speed; once stopped it rests. */
void AquariumFish_ModeSlowDown(AquariumFish *fish)
{
    fish->speed = (fx32) ((u32) fish->top_speed - (u32) AquariumFish_mul(fish->swim_218, fish->timer));
    AquariumSwim_Move(&fish->position, fish->speed, fish->yaw);
    if (fish->speed <= 0) {
        fish->speed = 0;
        fish->timer = 0;
        fish->mode = AQUARIUM_MODE_REST;
    }
}
CLEAN_AS(func_ov004_022360ac, AquariumFish_ModeSlowDown)

/* func_ov004_02236110 (mode 4): the fish moves on at its top speed for its cruising time, then
 * slows down. */
void AquariumFish_ModeCruise(AquariumFish *fish)
{
    fish->speed = fish->top_speed;
    AquariumSwim_Move(&fish->position, fish->speed, fish->yaw);
    if (fish->timer >= fish->cruise_frames) {
        fish->timer = 0;
        fish->mode = AQUARIUM_MODE_SLOW_DOWN;
    }
}
CLEAN_AS(func_ov004_02236110, AquariumFish_ModeCruise)

/* func_ov004_02236168 (mode 3): the fish speeds up by its acceleration (swim_214) a frame,
 * moving on at its speed; at its top speed it cruises. */
void AquariumFish_ModeSpeedUp(AquariumFish *fish)
{
    fish->speed = AquariumFish_mul(fish->swim_214, fish->timer);
    AquariumSwim_Move(&fish->position, fish->speed, fish->yaw);
    if (fish->speed >= fish->top_speed) {
        fish->timer = 0;
        fish->mode = AQUARIUM_MODE_CRUISE;
    }
}
CLEAN_AS(func_ov004_02236168, AquariumFish_ModeSpeedUp)

/* func_ov004_022361c4 (mode 2): the fish stops and sets off on a new course: 150 to 180 degrees
 * round either way when the glass is to turn it round (counting the times in a row), else up
 * to swim_230 degrees either way; random times to cruise (swim_204[1] up to swim_204[0]) and
 * to rest (swim_204[3] up to swim_204[2]); it takes its way up or down, tilts afresh, speeds
 * up and turns to its course. */
void AquariumFish_ModeNewCourse(AquariumFish *fish)
{
    fish->speed = 0;
    if (fish->glass_turn == AQUARIUM_GLASS_ROUND) {
        fish->target_yaw = (s16) (fish->target_yaw + AquariumSwim_RandomAngle(180, 150));
        fish->turnbacks++;
    } else {
        fish->target_yaw = (s16) (fish->target_yaw + AquariumSwim_RandomAngle(fish->swim_230, 0));
        fish->turnbacks = 0;
    }
    fish->timer = 0;
    fish->cruise_frames = (u8) AquariumSwim_Random(fish->swim_204[1], fish->swim_204[0]);
    fish->rest_frames = (u8) AquariumSwim_Random(fish->swim_204[3], fish->swim_204[2]);
    fish->pitch_steps = 0;
    AquariumFish_choose_vertical(fish);
    fish->levelling = 0;
    fish->mode = AQUARIUM_MODE_SPEED_UP;
    fish->turning = 1;
}
CLEAN_AS(func_ov004_022361c4, AquariumFish_ModeNewCourse)

/* func_ov004_022362ec (slot 1 of a plain fish's class): its frame in the room shown. */
void AquariumFish_SwimByRoom(AquariumFish *fish)
{
    MemberPointer_CallVoid(&data_ov004_02259424[data_ov004_022593a0 * 2 + 1], fish);
}
CLEAN_AS(func_ov004_022362ec, AquariumFish_SwimByRoom)

/* func_ov004_02236324 (slot 0 of a plain fish's class): its set-up in the room shown. */
void AquariumFish_SetUpByRoom(AquariumFish *fish)
{
    MemberPointer_CallVoid(&data_ov004_02259424[data_ov004_022593a0 * 2], fish);
}
CLEAN_AS(func_ov004_02236324, AquariumFish_SetUpByRoom)

/* func_ov004_0223635c: unless already startled, the fish flees from `from`, level, its timer at
 * 0. The sizes 4 and 5 flee a random way 80 to 100 degrees from yaw 0 on the side they face
 * (straight from `from` once they have paid attention to the same fish FOCUS_STARTLE_FRAMES).
 * A fish turning from the glass has its turn made a turn round. */
void AquariumFish_Startle(AquariumFish *fish, const Vec3 *from)
{
    if (fish->startled) {
        return;
    }
    fish->pitch = 0;
    fish->mode = AQUARIUM_MODE_FLEE;
    fish->timer = 0;
    if (AquariumFish_is_mid_size(fish->size)) {
        if (fish->focus_frames >= FOCUS_STARTLE_FRAMES) {
            fish->flee_yaw = Vec_YawTo(from, &fish->position);
        } else if (fish->yaw >= 0) {
            fish->flee_yaw = (s16) AquariumSwim_Random(0x38e4, 0x471c);
        } else {
            fish->flee_yaw = (s16) -AquariumSwim_Random(0x38e4, 0x471c);
        }
    } else {
        fish->flee_yaw = Vec_YawTo(from, &fish->position);
    }
    if (fish->glass_turn == AQUARIUM_GLASS_TURN) {
        AquariumSwim_TurnRound(fish);
    }
}
CLEAN_AS(func_ov004_0223635c, AquariumFish_Startle)

/* func_ov004_02236418: a startled fish stays so while it flees; otherwise a tap on the glass
 * near it startles it. Whether it was startled now. */
int AquariumFish_CheckTapped(AquariumFish *fish)
{
    if (fish->startled) {
        if (fish->mode != AQUARIUM_MODE_FLEE) {
            fish->startled = 0;
        }
        return 0;
    }
    Vec3 tap;
    if (AquariumFish_FindTap(fish, &tap)) {
        AquariumFish_Startle(fish, &tap);
        fish->startled = 1;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_02236418, AquariumFish_CheckTapped)

/* func_ov004_02236464: whether the stylus touches the glass of either tank near the fish (not
 * on the frame the pen came down): 0x9000 or less in the ground plane and 3.0 of its height;
 * the point touched in `tap` then.
 * QUIRK: the squared distance is compared with 0x9000 (about 9.6 units squared, 3.1 units). */
int AquariumFish_FindTap(AquariumFish *fish, Vec3 *tap)
{
    Vec3 point;
    u32 kind;
    u8 tank;
    if (!TouchPick_GetPick((TouchPick *) (uintptr_t) SceneQuery_FieldObject(), &point, &kind, &tank)) {
        return 0;
    }
    int pen_came_down = data_021f6c38 != 0 && data_021f6c34 != 0;
    if (pen_came_down || kind != GLASS_KIND || tank > 1) {
        return 0;
    }
    if (Vec_DistanceSquaredXZ(&fish->position, &point) > 0x9000) {
        return 0;
    }
    s32 height = (s32) ((u32) fish->position.y - (u32) point.y);
    if (height < 0) {
        height = (s32) (0u - (u32) height);
    }
    /* QUIRK: a difference of -2^31 counts as near (its size wraps) */
    if (height > 0x3000) {
        return 0;
    }
    *tap = point;
    return 1;
}
CLEAN_AS(func_ov004_02236464, AquariumFish_FindTap)

/* func_ov004_0223653c (run before the model of a fish of three animations is drawn): its node
 * descriptions get the hook after them (the game's AquariumFish_NodeDescAfterHook).
 * QUIRK: the hook before them (AquariumFish_NodeDescBeforeHook) is set first and replaced at once. */
void AquariumFish_SetModelHooks(AquariumFishHookState *state)
{
    state->hooks[G3D_COMMAND_NODE_DESC] = (u32) (uintptr_t) func_ov004_02236578;
    state->hook_timings[G3D_COMMAND_NODE_DESC] = G3D_TIMING_BEFORE;
    state->hooks[G3D_COMMAND_NODE_DESC] = (u32) (uintptr_t) func_ov004_0223655c;
    state->hook_timings[G3D_COMMAND_NODE_DESC] = G3D_TIMING_AFTER;
}
CLEAN_AS(func_ov004_0223653c, AquariumFish_SetModelHooks)

/* The fish a model's hooks run for: the render object's user pointer (at 0x2c, set by
 * ModelObject_SetInitHook). */
static AquariumFish *AquariumFish_hooked(const AnimatedModelNodeState *state)
{
    AquariumFish *fish;
    memcpy(&fish, (const u8 *) state->state.object + 0x2c, sizeof fish);
    return fish;
}

/* func_ov004_0223655c: after a node's description, the fish's model's own hook. */
void AquariumFish_NodeDescAfterHook(AnimatedModelNodeState *state)
{
    if (AquariumFish_hooked(state) != NULL) {
        AnimatedModel_AfterNode(&AquariumFish_hooked(state)->model, state);
    }
}
CLEAN_AS(func_ov004_0223655c, AquariumFish_NodeDescAfterHook)

/* func_ov004_02236578: before a node's description, the fish's model's own hook. */
void AquariumFish_NodeDescBeforeHook(AnimatedModelNodeState *state)
{
    if (AquariumFish_hooked(state) != NULL) {
        AnimatedModel_BeforeNode(&AquariumFish_hooked(state)->model, state);
    }
}
CLEAN_AS(func_ov004_02236578, AquariumFish_NodeDescBeforeHook)

/* func_ov004_02236594 (a plain fish's frame in the river room): its mode runs; a fish of size 0
 * paying attention to a new one is startled away from it (unless it flees already); it turns
 * from the glass; unless resting or slowing down below 0x0cd, it climbs or dives with its
 * pitch (kind 29 within 0xe38, the big kinds within 0x71c, size 0 its own way) and turns to
 * its course; then its animation speed (at least 0.2), its timer, and the stylus. */
void AquariumFish_SwimRiver(AquariumFish *fish)
{
    AquariumFish_run_mode(fish);
    int kind = fish->index;
    if (data_ov004_02247924[kind].size == 0) {
        u8 focus = fish->focus;
        if (fish->last_focus != focus && focus != kind) {
            fish->last_focus = focus;
            if (fish->mode != AQUARIUM_MODE_FLEE) {
                AquariumFish_Startle(fish, AquariumFish_position_of(data_ov004_022594d4[fish->focus]));
            }
        }
    }
    AquariumSwim_WatchGlass(fish);
    if (!(fish->mode == AQUARIUM_MODE_SLOW_DOWN && fish->speed < 205) && fish->mode != AQUARIUM_MODE_REST) {
        AquariumSwim_Climb(fish);
        kind = fish->index;
        if (kind == KIND_FISH_29) {
            AquariumSwim_TiltBySpeed(fish, 0xe38, 0x4b0);
        } else {
            u8 size = data_ov004_02247924[kind].size;
            if (size == 0) {
                AquariumSwim_TiltFixed(fish);
            } else if (size >= BIG_SIZE) {
                AquariumSwim_TiltBySpeed(fish, 0x71c, 0x384);
            } else {
                AquariumSwim_TiltBySpeed(fish, 0x1554, 0x384);
            }
        }
        AquariumFish_Turn(fish);
    }
    AquariumFish_SetAnimSpeed(fish, 0x333);
    fish->timer++;
    AquariumFish_CheckTapped(fish);
}
CLEAN_AS(func_ov004_02236594, AquariumFish_SwimRiver)

/* func_ov004_022366c8 (a plain fish's set-up in the river room): a fish of size 0 is its
 * body's owner (so it meets others); it pays attention to nobody; its swimming values; the
 * kinds of three animations get their model hooks. */
void AquariumFish_SetUpRiver(AquariumFish *fish)
{
    if (data_ov004_02247924[fish->index].size == 0) {
        fish->body.owner = fish;
    }
    fish->focus = (u8) fish->index;
    AquariumFish_SetSwim(fish);
    if (fish->unk_1c6 != 0) {
        ModelObject_SetInitHook(&fish->model.object, (void *) (uintptr_t) func_ov004_0223653c, fish);
    }
}
CLEAN_AS(func_ov004_022366c8, AquariumFish_SetUpRiver)

/* func_ov004_0223671c (a plain fish's frame in the sea room): it turns from the glass, its mode
 * runs; kinds 45 and 46 keep to z 0x13dc2 or less, the others turn back at the tank's ends and
 * react to whom they pay attention to (kinds 41, 43 and 55 keeping their yaw across); unless
 * setting off or resting it climbs or dives with its pitch (kinds 43 and 55 within 0x71c,
 * others 0xe38) and turns to its course; then its animation speed (at least 0.2), the room's
 * ends, its timer, and the stylus. */
void AquariumFish_SwimSea(AquariumFish *fish)
{
    AquariumFish_TurnFromGlass(fish);
    AquariumFish_run_mode(fish);
    int kind = fish->index;
    if (kind != KIND_FISH_46 && kind != KIND_FISH_45) {
        if (kind == KIND_FISH_41 || kind == KIND_FISH_55 || kind == KIND_FISH_43) {
            AquariumFish_KeepYawAcross(fish);
        }
        AquariumFish_TurnAtTankEnds(fish);
        AquariumFish_ReactToFocus(fish);
    } else if (fish->position.z > 0x13dc2) {
        fish->position.z = 0x13dc2;
    }
    if (fish->mode != AQUARIUM_MODE_NEW_COURSE && fish->mode != AQUARIUM_MODE_REST) {
        AquariumSwim_ClimbByFocus(fish);
        if (fish->index == KIND_FISH_43 || fish->index == KIND_FISH_55) {
            AquariumSwim_TiltEased(fish, 0x71c);
        } else {
            AquariumSwim_TiltEased(fish, 0xe38);
        }
        AquariumFish_Turn(fish);
    }
    AquariumFish_SetAnimSpeed(fish, 0x333);
    AquariumFish_KeepOffRoomEnds(fish);
    fish->timer++;
    AquariumFish_CheckTapped(fish);
}
CLEAN_AS(func_ov004_0223671c, AquariumFish_SwimSea)

/* func_ov004_02236808 (a plain fish's set-up in the sea room): it is its body's owner; kinds 45
 * and 46 keep to area 0, kind 55 to area 2, the others to area 1; it pays attention to and
 * makes way for nobody; its swimming values; the kinds of three animations get their model
 * hooks. */
void AquariumFish_SetUpSea(AquariumFish *fish)
{
    fish->body.owner = fish;
    if (fish->index == KIND_FISH_45 || fish->index == KIND_FISH_46) {
        fish->area = 0;
    } else if (fish->index == KIND_FISH_55) {
        fish->area = 2;
    } else {
        fish->area = 1;
    }
    fish->focus = (u8) fish->index;
    fish->yield_to = (u8) fish->index;
    AquariumFish_SetSwim(fish);
    if (fish->unk_1c6 != 0) {
        ModelObject_SetInitHook(&fish->model.object, (void *) (uintptr_t) func_ov004_0223653c, fish);
    }
}
CLEAN_AS(func_ov004_02236808, AquariumFish_SetUpSea)
