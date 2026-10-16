/* The marks and sounds of a scene object's steps (footsteps.h). */
#include "footsteps.h"

#include "autoload_2/vector.h"
#include "clean.h"
#include "sound_emitter.h"

static_assert(offsetof(Footsteps, ground) == 0x04, "Footsteps layout");

/* The scene object's parts used here. */
#define FOOTSTEPS_OBJECT_POSITION 0x5c /* a Vec3 */
#define FOOTSTEPS_OBJECT_ANGLE 0x8e    /* s16, the angle about y */
#define FOOTSTEPS_OBJECT_FLAGS 0xb0
#define FOOTSTEPS_OBJECT_BODY_ANIM 0x188
#define FOOTSTEPS_OBJECT_GROUND 0x350
#define FOOTSTEPS_OBJECT_FOOT_A 0x490 /* a Vec3, marked on frame 1 */
#define FOOTSTEPS_OBJECT_FOOT_B 0x484 /* a Vec3, marked on frame 9 */
#define FOOTSTEPS_OBJECT_SOUND 0x514  /* a SoundEmitter */

/* The flags at 0xb0 that, both set, keep the steps silent. */
#define FOOTSTEPS_SILENT_FLAGS 6

/* The ground kinds that take marks, and the one that takes effect 0 too. */
#define FOOTSTEPS_GROUND_FIRST 1
#define FOOTSTEPS_GROUND_LAST 3
#define FOOTSTEPS_GROUND_EXTRA 2

#define FOOTSTEPS_EFFECT_MARK 0x28
#define FOOTSTEPS_EFFECT_EXTRA 0

/* The frames of the body's animation that put a foot down. */
#define FOOTSTEPS_FRAME_A 1
#define FOOTSTEPS_FRAME_B 9

#define FOOTSTEPS_INITIAL_GROUND 5

/* What the effects are handed: the mark gets the angle (and what follows), effect 0 the angle
 * turned round (and may change it before the mark reads it), both the point. */
typedef struct FootstepMark {
    s16 angle;
    s16 back_angle;
    Vec3 at;
} FootstepMark;

static_assert(offsetof(FootstepMark, at) == 0x04, "FootstepMark layout");

extern s32 func_0201b1a0(void *ground);
extern int func_02056f28(void *animation, int frame);
extern int func_020912d4(int effect, const void *at, void *angles, int arg);
extern int func_020b1cb0(const void *position);

static u8 *footsteps_part(void *object, u32 offset)
{
    return (u8 *) object + offset;
}

/* func_02013abc: one frame of the steps (footsteps.h); the ground kind is kept for the next.
 * BUG: when marking both feet at once, the original hands effect 0x28 a FootstepMark whose
 * angle alone is set (the rest is what the stack held); here the rest is zero. */
void Footsteps_Update(Footsteps *steps, void *object)
{
    s32 ground = func_0201b1a0(footsteps_part(object, FOOTSTEPS_OBJECT_GROUND));

    if (steps->enabled != 0 && (u32) ground - FOOTSTEPS_GROUND_FIRST <= FOOTSTEPS_GROUND_LAST - FOOTSTEPS_GROUND_FIRST) {
        FootstepMark mark = {0};
        mark.angle = *(const s16 *) footsteps_part(object, FOOTSTEPS_OBJECT_ANGLE);

        if (steps->ground == 0) {
            func_020912d4(FOOTSTEPS_EFFECT_MARK, footsteps_part(object, FOOTSTEPS_OBJECT_FOOT_A), &mark, 0);
            func_020912d4(FOOTSTEPS_EFFECT_MARK, footsteps_part(object, FOOTSTEPS_OBJECT_FOOT_B), &mark, 0);
        } else {
            void *animation = footsteps_part(object, FOOTSTEPS_OBJECT_BODY_ANIM);
            int on_a = func_02056f28(animation, FOOTSTEPS_FRAME_A);
            int on_b = func_02056f28(animation, FOOTSTEPS_FRAME_B);
            if (on_a != 0 || on_b != 0) {
                const Vec3 *foot =
                    (const Vec3 *) footsteps_part(object, on_a != 0 ? FOOTSTEPS_OBJECT_FOOT_A : FOOTSTEPS_OBJECT_FOOT_B);
                mark.at = *foot;
                mark.back_angle = (s16) (mark.angle + 0x8000);
                /* the foot's point at the height of the object */
                mark.at.y = ((const Vec3 *) footsteps_part(object, FOOTSTEPS_OBJECT_POSITION))->y;
                if (ground == FOOTSTEPS_GROUND_EXTRA) {
                    func_020912d4(FOOTSTEPS_EFFECT_EXTRA, &mark.at, &mark.back_angle, 0);
                }
                func_020912d4(FOOTSTEPS_EFFECT_MARK, &mark.at, &mark, 0);
                Footsteps_PlaySound(steps, object);
            }
        }
    }
    steps->ground = ground;
}
CLEAN_AS(func_02013abc, Footsteps_Update)

/* func_02013bb0: the sound of the ground under the object (func_020b1cb0) through its sound
 * emitter, when the steps are enabled and the object's flags at 0xb0 do not have both 4 and 2. */
void Footsteps_PlaySound(Footsteps *steps, void *object)
{
    u32 flags = *(const u32 *) footsteps_part(object, FOOTSTEPS_OBJECT_FLAGS);
    if ((flags & FOOTSTEPS_SILENT_FLAGS) == FOOTSTEPS_SILENT_FLAGS) {
        return;
    }
    if (steps->enabled != 0) {
        int sound = func_020b1cb0(footsteps_part(object, FOOTSTEPS_OBJECT_POSITION));
        SoundEmitter_PlayAlternating((SoundEmitter *) footsteps_part(object, FOOTSTEPS_OBJECT_SOUND), (u32) sound, 0);
    }
}
CLEAN_AS(func_02013bb0, Footsteps_PlaySound)

/* func_02013c04 */
void Footsteps_Disable(Footsteps *steps)
{
    steps->enabled = 0;
}
CLEAN_AS(func_02013c04, Footsteps_Disable)

/* func_02013c0c */
void Footsteps_Enable(Footsteps *steps)
{
    steps->enabled = 1;
}
CLEAN_AS(func_02013c0c, Footsteps_Enable)

/* func_02013c14: disabled, the ground kind 5 (none of those that take marks). */
void Footsteps_Init(Footsteps *steps)
{
    Footsteps_Disable(steps);
    steps->ground = FOOTSTEPS_INITIAL_GROUND;
}
CLEAN_AS(func_02013c14, Footsteps_Init)

/* func_02013c28: the destructor; nothing to release. */
void Footsteps_Destruct(Footsteps *steps)
{
    (void) steps;
}
CLEAN_AS(func_02013c28, Footsteps_Destruct)

/* func_02013c2c: the constructor: disabled. */
void Footsteps_Construct(Footsteps *steps)
{
    steps->enabled = 0;
}
CLEAN_AS(func_02013c2c, Footsteps_Construct)
