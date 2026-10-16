/* A level that fades or flashes between 0 and 1.0 (fader.h). */
#include "fader.h"

#include "clean.h"

static_assert(offsetof(Fader, target) == 0x04, "target");
static_assert(offsetof(Fader, flashing) == 0x0c, "flashing");
static_assert(offsetof(Fader, flash_wait) == 0x12, "flash wait");

extern fx32 FX_MulFunc(fx32 a, fx32 b);

/* func_020b3658: the level. */
int Fader_Level(const Fader *fader)
{
    return fader->level;
}
CLEAN_AS(func_020b3658, Fader_Level)

/* func_020b365c: `from` brought towards `to` by `level` (0 to 1.0). */
int Fader_Mix(int level, int from, int to)
{
    return from + FX_MulFunc(level, to - from);
}
CLEAN_AS(func_020b365c, Fader_Mix)

/* func_020b3670: the fader on (target 1.0) or off (target 0) at `speed`; without `fade` the
 * level jumps there at once. Coming on with `fade` and `flash`, it flashes first. Nothing
 * changes but the speed (and, going off, the flashing) when the target is already there.
 * Whether it started to fade. */
int Fader_Switch(Fader *fader, int on, int fade, int flash, int speed)
{
    fader->speed = speed;
    if (on != 0) {
        if (fader->target != 0) {
            return 0;
        }
        fader->target = FADER_FULL;
        if (fade == 0) {
            fader->level = FADER_FULL;
            return 0;
        }
        if (flash != 0) {
            fader->flashing = 1;
            fader->flash_step = 0;
            fader->flash_wait = FADER_FLASH_WAIT;
        }
        return 1;
    }

    fader->flashing = 0;
    if (fader->target == 0) {
        return 0;
    }
    fader->target = 0;
    if (fade == 0) {
        fader->level = 0;
        return 0;
    }
    return 1;
}
CLEAN_AS(func_020b3670, Fader_Switch)

#define FADER_FLASH_STEPS 11
#define FADER_SET_SPEED 0x800 /* the speed Fader_Set leaves */

/* The levels a flash goes through, one a frame (data_020d1e90). */
extern const fx32 data_020d1e90[FADER_FLASH_STEPS];

/* func_020b36c8: a frame of the fader. Flashing, it stays dark (level 0) through the wait,
 * then takes the table's levels one a frame and stops after the last; otherwise the level
 * moves towards the target by the speed (Approach_S32Again), and nothing is called once it is
 * there. */
void Fader_Run(Fader *fader)
{
    if (fader->flashing != 1) {
        if (fader->target != fader->level) {
            Approach_S32Again((int *) &fader->level, fader->target, fader->speed);
        }
        return;
    }

    if (fader->flash_wait != 0) {
        fader->level = 0;
        fader->flash_wait--;
    }
    if (fader->flash_wait != 0) {
        return;
    }
    if (fader->flash_step < FADER_FLASH_STEPS) {
        fader->level = data_020d1e90[fader->flash_step];
        fader->flash_step++;
    } else {
        fader->flashing = 0;
        fader->flash_step = 0;
    }
}
CLEAN_AS(func_020b36c8, Fader_Run)

/* func_020b3720: the fader on or off at once, at speed 0x800 (Fader_Switch without fading). */
void Fader_Set(Fader *fader, int on)
{
    Fader_Switch(fader, on, 0, 0, FADER_SET_SPEED);
}
CLEAN_AS(func_020b3720, Fader_Set)

/* func_020b373c: the fader taken down; nothing to do. */
void Fader_Destruct(Fader *fader)
{
    (void) fader;
}
CLEAN_AS(func_020b373c, Fader_Destruct)

/* func_020b3740: the fader built off: level, target and flashing 0. The speed and the flash's
 * step and wait are left as they were. */
void Fader_Construct(Fader *fader)
{
    fader->level = 0;
    fader->target = 0;
    fader->flashing = 0;
}
CLEAN_AS(func_020b3740, Fader_Construct)
