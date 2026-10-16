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
