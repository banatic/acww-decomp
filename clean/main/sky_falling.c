/* The drops of rain and the flakes of snow (sky_falling.h). */
#include "sky_falling.h"

#include "actor.h"
#include "clean.h"
#include "sky.h"

static_assert(sizeof(SkyFallingVars) == 0x14, "the words at 0x60");

#define SKY_FALLING_PLAYER 4 /* the actor func_020961a8 is asked for: this system's player */
#define SKY_FALLING_PRIORITY 2
#define SKY_FALLING_START_Y (-0x14000) /* y -20 */
#define SKY_FALLING_LEFT (-0x14000)    /* wrapped past x -20 */
#define SKY_FALLING_RIGHT 0x114000     /* or x 276 */
#define SKY_FALLING_WRAP 0x11e000      /* by 286 pixels */
#define SKY_SNOW_BOTTOM 0x1d4000       /* y 468 */
#define SKY_RAIN_BOTTOM 0x100000       /* a drop's line is below y 256 */
#define SKY_RAIN_SPEED 0x24
#define SKY_RAIN_LOOKS 3
#define SKY_RAIN_FIRST_ANIMATION 2

extern Sky data_021f75b0;
extern SkyObjects data_021f8b48;
extern s32 data_020e5974;           /* a flake's side: 1 or -1, swapped at each flake */
extern s32 data_020e5978;           /* a drop's */
extern const fx32 data_020d22fc[3]; /* a flake's speed by its layer */
extern const s32 data_020d22f0[3];  /* a flake's animation by its layer */
extern const fx32 data_020d2308[3]; /* how much a flake moves with the player, by layer */
extern const fx32 data_020d22e4[3]; /* a drop's */
extern const fx16 FX_SinCosTable_[4096 * 2];

extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *sum);
extern u32 func_020644cc(int bound); /* a random number below `bound` */
extern Actor *func_020961a8(int player);

static SkyFallingVars *sky_falling_vars(SkyObject *object)
{
    return (SkyFallingVars *) (void *) SkyObject_Body(object)->words;
}

/* How far the player actor moved sideways this frame, against it and by `factor`. */
static fx32 sky_falling_shift(const Actor *player, fx32 factor)
{
    return (-(player->position.x - player->last_position.x) * factor) >> 12;
}

/* x wrapped around the screen's sides. */
static void sky_falling_wrap(fx32 *x)
{
    if (*x < SKY_FALLING_LEFT) {
        *x += SKY_FALLING_WRAP;
    } else if (*x > SKY_FALLING_RIGHT) {
        *x -= SKY_FALLING_WRAP;
    }
}

/* func_020c11c4: a flake taken down. */
void SkySnow_TakeDown(SkyObject *object)
{
    SkyObjectKinds_Remove(object);
}
CLEAN_AS(func_020c11c4, SkySnow_TakeDown)

/* func_020c11cc: a frame of a flake: it falls, its sway's middle moves with the player, and it
 * sways; done below y 468, else wrapped around the sides.
 * QUIRK: the wrap moves only x, which the next frame takes again from the sway's middle. */
void SkySnow_Run(SkyObject *object)
{
    SkyObjectBody *body = SkyObject_Body(object);
    SkyFallingVars *vars = sky_falling_vars(object);
    Vec3 *position = &body->position;
    VEC_Add(position, &body->velocity, position);
    const Actor *player = func_020961a8(SKY_FALLING_PLAYER);
    if (player != NULL) {
        vars->base_x = sky_falling_shift(player, data_020d2308[vars->layer]) + vars->base_x;
    }
    fx32 base_x = vars->base_x;
    s16 phase = (s16) ((s16) vars->phase + vars->speed);
    vars->phase = phase;
    int sway = FX_SinCosTable_[((u16) phase >> 4) * 2] * vars->sway;
    position->x = base_x + (sway >> 12);
    if (position->y > SKY_SNOW_BOTTOM) {
        body->state = SKY_OBJECT_DONE;
    } else {
        sky_falling_wrap(&position->x);
    }
}
CLEAN_AS(func_020c11cc, SkySnow_Run)

/* func_020c1278: a flake set up in a random layer: at x 128 plus or less up to 127 (on the
 * other side from the flake before), at y -20 or with `start` 1 down to 448 pixels lower; its
 * sway's step from 0x180 to 0x47f, its angle at random.
 * QUIRK: its sway is 5.0 plus a random 0 or 1/4096. */
void SkySnow_SetUp(SkyObject *object, int start)
{
    SkyObjectBody *body = SkyObject_Body(object);
    SkyFallingVars *vars = sky_falling_vars(object);
    int layer = (int) func_020644cc(3);
    fx32 x = (fx32) ((u32) ((int) func_020644cc(0x80) * data_020e5974 + 0x80) << 12);
    data_020e5974 = -data_020e5974;
    body->position.x = x;
    body->position.y = SKY_FALLING_START_Y;
    body->position.z = 0;
    body->velocity.x = 0;
    body->velocity.y = data_020d22fc[layer];
    body->velocity.z = 0;
    vars->speed = (s32) func_020644cc(0x300) + 0x180;
    vars->phase = (s32) func_020644cc(0x10000);
    vars->layer = layer;
    vars->base_x = x;
    vars->sway = (fx32) func_020644cc(2) + 0x5000;
    body->animation = data_020d22f0[layer];
    body->priority = SKY_FALLING_PRIORITY;
    if (start == 1) {
        body->position.y += (fx32) (func_020644cc(0x1c1) << 12);
    }
}
CLEAN_AS(func_020c1278, SkySnow_SetUp)

/* func_020c132c: a drop taken down. */
void SkyRain_TakeDown(SkyObject *object)
{
    SkyObjectKinds_Remove(object);
}
CLEAN_AS(func_020c132c, SkyRain_TakeDown)

/* func_020c1334: a frame of a drop: it falls and moves with the player; done past its line,
 * else wrapped around the sides. */
void SkyRain_Run(SkyObject *object)
{
    SkyObjectBody *body = SkyObject_Body(object);
    SkyFallingVars *vars = sky_falling_vars(object);
    fx32 *x = &body->position.x;
    VEC_Add(&body->position, &body->velocity, &body->position);
    const Actor *player = func_020961a8(SKY_FALLING_PLAYER);
    if (player != NULL) {
        *x += sky_falling_shift(player, data_020d22e4[vars->layer]);
    }
    if (body->position.y > (fx32) ((u32) vars->speed << 12) + SKY_RAIN_BOTTOM) {
        body->state = SKY_OBJECT_DONE;
    } else {
        sky_falling_wrap(x);
    }
}
CLEAN_AS(func_020c1334, SkyRain_Run)

/* func_020c13bc: a drop set up: at x 128 plus or less up to 137 (on the other side from the
 * drop before), 20 to 35 pixels above the screen or with `start` 1 lower by up to its line
 * and 256 pixels; falling at the angle of a random spread (up to 0x556 either way) plus
 * Sky.unk_1538 (read as signed), times the wind, turned to match and twice as tall; one of
 * three looks (animations 2 to 4) with its line: 128 to 191 pixels past 256, 64 to 127, or 0
 * to 63. */
void SkyRain_SetUp(SkyObject *object, int start)
{
    SkyObjectBody *body = SkyObject_Body(object);
    SkyFallingVars *vars = sky_falling_vars(object);
    int r = (int) func_020644cc(0x8a);
    fx32 x = (fx32) ((u32) (data_020e5978 * r + 0x80) << 12);
    data_020e5978 = -data_020e5978;
    fx32 y = SKY_FALLING_START_Y - (fx32) (func_020644cc(0x10) << 12);
    body->position.x = x;
    body->position.y = y;
    body->position.z = 0;
    s32 wind = data_021f8b48.unk_2f54;
    int spread = (int) func_020644cc(0xaac) - 0x556;
    int turn = (spread + (s16) data_021f75b0.unk_1538) * wind;
    u16 angle = (u16) ((u32) turn >> 12);
    int index = (angle >> 4) * 2;
    body->velocity.x = -SKY_RAIN_SPEED * FX_SinCosTable_[index];
    body->velocity.y = SKY_RAIN_SPEED * FX_SinCosTable_[index + 1];
    body->velocity.z = 0;
    body->scale_y = 0x800;
    body->rotation = angle;
    int look = (int) func_020644cc(SKY_RAIN_LOOKS);
    body->animation = look + SKY_RAIN_FIRST_ANIMATION;
    int line;
    switch (look) {
        case 0:
            line = (int) func_020644cc(0x40) + 0x80;
            break;
        case 1:
            line = (int) func_020644cc(0x40) + 0x40;
            break;
        default:
            line = (int) func_020644cc(0x40);
            break;
    }
    vars->speed = line;
    if (start == 1) {
        body->position.y += (fx32) (func_020644cc(line + 0x101) << 12);
    }
    body->priority = SKY_FALLING_PRIORITY;
}
CLEAN_AS(func_020c13bc, SkyRain_SetUp)
