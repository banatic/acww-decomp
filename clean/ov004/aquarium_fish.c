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

/* Flags for how the fish and the other it met lie and face each other. */
extern int func_ov004_02235a18(AquariumFish *fish, AquariumFish **other);
/* The fish's yaw kept from 0x2aac to 0x5554 either way. */
extern void func_ov004_02235e58(AquariumFish *fish);

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
    int way = func_ov004_02235a18(fish, other);
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
        func_ov004_02235e58(fish);
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
