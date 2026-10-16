/* The objects of kinds 3 and 2 (sky_kind3.h). */
#include "sky_kind3.h"

#include "autoload_2/fx_math.h"
#include "cell_anim.h"
#include "clean.h"

static_assert(sizeof(SkyKind2Vars) == 0x14, "the words at 0x60");

#define SKY_KIND3_ANIMATION 0x11
#define SKY_KIND3_PRIORITY 3
#define SKY_KIND3_SPEED 0x7800 /* 7.5 pixels a frame */
#define SKY_KIND3_BACK 0x23    /* it starts 35 pixels back along its way */
#define SKY_KIND3_SOUND_SOURCE 6
#define SKY_KIND3_SOUND 0x801
#define SKY_KIND2_DRAG 0xe66
#define SKY_KIND2_FOLLOW_FRAMES 23
#define SKY_KIND2_TURN 0xe39
#define SKY_KIND2_OTHER_FRAMES 6
#define SKY_KIND2_PRIORITY 2
#define SKY_KIND2_FOLLOW_PRIORITY 3

extern SkyObjects data_021f8b48;
extern const s32 data_020d23ec[];                         /* kind 2's animation by its mode */
extern const fx32 data_020d26f0[SKY_KIND2_FOLLOW_FRAMES]; /* a follower's size by its frame */
extern const fx16 FX_SinCosTable_[4096 * 2];

extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *sum);
extern u32 func_020644cc(int bound); /* a random number below `bound` */

static SkyKind2Vars *sky_kind2_vars(SkyObject *object)
{
    return (SkyKind2Vars *) (void *) SkyObject_Body(object)->words;
}

/* func_020c0f04: kind 3 taken down: the byte that says it is seen cleared. */
void SkyKind3_TakeDown(SkyObject *object)
{
    data_021f8b48.unk_2f50 = 0;
    SkyObjectKinds_Remove(object);
}
CLEAN_AS(func_020c0f04, SkyKind3_TakeDown)

/* func_020c0f18: a frame of kind 3: moved; done once more than 35 pixels off the screen's
 * left, top or right or below line 202; seen (SkyObjects.unk_2f50) while unmarked and inside
 * the screen. */
void SkyKind3_Run(SkyObject *object)
{
    SkyObjectBody *body = SkyObject_Body(object);
    VEC_Add(&body->position, &body->velocity, &body->position);
    int x = body->position.x >> 12;
    int y = body->position.y >> 12;
    int gone = y < -35 || y > 202 || x < -35 || x > 291;
    int seen = sky_kind2_vars(object)->param == 0 && !gone && y > 0 && y < 192 && x > 0 && x < 256;
    data_021f8b48.unk_2f50 = (u8) seen;
    if (gone) {
        body->state = SKY_OBJECT_DONE;
    }
}
CLEAN_AS(func_020c0f18, SkyKind3_Run)

/* func_020c0f8c: kind 3 set up: from a random point of the screen's top edge (x 196 to 255)
 * or of its right edge (y 0 to 47), 35 pixels back, towards a random point of the left edge
 * at y 128 to 150; half as tall as wide and turned along its way; sound 0x801 from source 6. */
void SkyKind3_SetUp(SkyObject *object)
{
    SkyObjectBody *body = SkyObject_Body(object);
    body->scale_x = 0x1000;
    body->scale_y = 0x800;
    fx32 x;
    fx32 y;
    if (func_020644cc(2) == 0) {
        x = (fx32) ((func_020644cc(0x3c) + 0xc4) << 12);
        y = 0;
    } else {
        x = 0x100000;
        y = (fx32) (func_020644cc(0x30) << 12);
    }
    fx32 target_y = (fx32) ((func_020644cc(0x17) + 0x80) << 12);
    int angle = Math_Atan2(target_y - y, -x);
    int index = ((u16) angle >> 4) * 2;
    int sin = FX_SinCosTable_[index];
    int cos = FX_SinCosTable_[index + 1];
    x -= SKY_KIND3_BACK * cos;
    y -= SKY_KIND3_BACK * sin;
    body->position.x = x;
    body->position.y = y;
    body->position.z = 0;
    body->velocity.x = FX_MulFunc(cos, SKY_KIND3_SPEED);
    body->velocity.y = FX_MulFunc(sin, SKY_KIND3_SPEED);
    body->velocity.z = 0;
    body->rotation = (u16) (angle - 0x4000);
    body->animation = SKY_KIND3_ANIMATION;
    body->priority = SKY_KIND3_PRIORITY;
    data_021f8b48.unk_2f50 = 0;
    SkyObjectKinds_PlayHeldAt(object, SKY_KIND3_SOUND_SOURCE, SKY_KIND3_SOUND);
}
CLEAN_AS(func_020c0f8c, SkyKind3_SetUp)

/* func_020c105c: kind 2 taken down. */
void SkyKind2_TakeDown(SkyObject *object)
{
    SkyObjectKinds_Remove(object);
}
CLEAN_AS(func_020c105c, SkyKind2_TakeDown)

/* func_020c1064: a frame of kind 2, counted, by its mode (sky_kind3.h). */
void SkyKind2_Run(SkyObject *object)
{
    SkyObjectBody *body = SkyObject_Body(object);
    SkyKind2Vars *vars = sky_kind2_vars(object);
    u32 mode = vars->param & 0xf;
    vars->timer++;
    if (mode == SKY_KIND2_DRIFT) {
        Vec_Scale(&body->velocity, SKY_KIND2_DRAG);
        VEC_Add(&body->position, &body->velocity, &body->position);
        if (CellAnim_IsDone(&body->anim)) {
            body->state = SKY_OBJECT_DONE;
        }
    } else if (mode == SKY_KIND2_FOLLOW) {
        int frame = vars->timer;
        if (frame >= SKY_KIND2_FOLLOW_FRAMES) {
            body->state = SKY_OBJECT_DONE;
        } else {
            fx32 size = data_020d26f0[frame];
            body->scale_x = size;
            body->scale_y = size;
            body->rotation = (u16) (body->rotation + SKY_KIND2_TURN);
            if (!SkyKind2_Follow(object)) {
                body->state = SKY_OBJECT_DONE;
            }
        }
    } else if (vars->timer >= SKY_KIND2_OTHER_FRAMES) {
        body->state = SKY_OBJECT_DONE;
    }
}
CLEAN_AS(func_020c1064, SkyKind2_Run)

/* func_020c10f4: kind 2 set up: its animation by its mode; a follower is drawn in front, at its
 * first size, and done at once without a kind 3 to follow. */
void SkyKind2_SetUp(SkyObject *object, int param)
{
    SkyObjectBody *body = SkyObject_Body(object);
    SkyKind2Vars *vars = sky_kind2_vars(object);
    int mode = param & 0xf;
    body->animation = data_020d23ec[mode];
    body->priority = mode == SKY_KIND2_FOLLOW ? SKY_KIND2_FOLLOW_PRIORITY : SKY_KIND2_PRIORITY;
    vars->param = (u32) param;
    vars->timer = 0;
    if (mode == SKY_KIND2_FOLLOW) {
        fx32 size = data_020d26f0[0];
        body->scale_x = size;
        body->scale_y = size;
        if (!SkyKind2_Follow(object)) {
            body->state = SKY_OBJECT_DONE;
        }
    }
}
CLEAN_AS(func_020c10f4, SkyKind2_SetUp)

/* func_020c1144: the object placed behind the first running object of kind 3, back along its
 * way by 16 pixels over that object's height scale; 0 when there is none.
 * QUIRK: with no object of kind 3 the entry looked at is the one past the last (the slots). */
int SkyKind2_Follow(SkyObject *object)
{
    int index = SkyObjects_FindKind(&data_021f8b48, SKY_OBJECT_KIND_3);
    const SkyObjectBody *led =
        (const SkyObjectBody *) ((uintptr_t) data_021f8b48.entries + (u32) index * (u32) sizeof(SkyObject));
    if (led->state != SKY_OBJECT_RUNNING) {
        return 0;
    }
    int angle = (led->rotation >> 4) * 2;
    fx32 back = FX_Div(0x10000, led->scale_y);
    fx32 y = led->position.y + FX_MulFunc(FX_SinCosTable_[angle + 1], back);
    fx32 x = led->position.x - FX_MulFunc(FX_SinCosTable_[angle], back);
    SkyObjectBody *body = SkyObject_Body(object);
    body->position.x = x;
    body->position.y = y;
    body->position.z = 0;
    return 1;
}
CLEAN_AS(func_020c1144, SkyKind2_Follow)
