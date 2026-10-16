/* Cell animations (cell_anim.h). */
#include "cell_anim.h"

#include "clean.h"

static_assert(sizeof(CellAnim) == 0x14, "CellAnim");
static_assert(sizeof(CellAnimFrame) == 0xc && offsetof(CellAnimFrame, x) == 8, "CellAnimFrame");
static_assert(sizeof(CellAnimData) == 8, "CellAnimData");

static const CellAnimData *data_of(const CellAnim *anim)
{
    return (const CellAnimData *) anim->data;
}

/* The whole ticks of `time`. */
static int whole_ticks(fx32 time)
{
    return time >> 12;
}

/* func_0208a0c8: one frame's advance by `speed`. A looping animation goes on to the next frame
 * (round to the first) once the frame has shown its ticks, starting it at 0; a held one stops on
 * the last frame, where `time` keeps running. */
void CellAnim_Advance(CellAnim *anim)
{
    const CellAnimData *data = data_of(anim);
    anim->time += anim->speed;
    if (whole_ticks(anim->time) < data->frames[anim->frame].ticks) {
        return;
    }
    if (anim->hold == 0) {
        anim->time = 0;
        int count = data->count;
        anim->frame++;
        if (anim->frame >= count) {
            anim->frame = 0;
        }
    } else {
        int count = data->count;
        anim->frame++;
        if (anim->frame < count) {
            anim->time = 0;
        } else {
            anim->frame = count - 1;
        }
    }
}
CLEAN_AS(func_0208a0c8, CellAnim_Advance)

/* func_0208a144: played again from the first frame at one tick a frame. */
CellAnim *CellAnim_Restart(CellAnim *anim)
{
    anim->speed = CELL_ANIM_SPEED_ONE;
    return CellAnim_SetFrame(anim, 0, 0);
}
CLEAN_AS(func_0208a144, CellAnim_Restart)

/* func_0208a158: held where it is. */
void CellAnim_Stop(CellAnim *anim)
{
    anim->speed = 0;
}
CLEAN_AS(func_0208a158, CellAnim_Stop)

/* func_0208a160: whether a held animation is over: on its last frame, in the last tick of it
 * or later. A looping one is never over. */
int CellAnim_IsDone(CellAnim *anim)
{
    if (anim->hold != 1) {
        return 0;
    }
    const CellAnimData *data = data_of(anim);
    if (anim->frame < data->count - 1) {
        return 0;
    }
    return whole_ticks(anim->time) >= data->frames[anim->frame].ticks - 1;
}
CLEAN_AS(func_0208a160, CellAnim_IsDone)

/* func_0208a198: a frame's y offset; -1 for the current frame's. */
s16 CellAnim_FrameY(CellAnim *anim, int frame)
{
    if (frame < 0) {
        frame = anim->frame;
    }
    return data_of(anim)->frames[frame].y;
}
CLEAN_AS(func_0208a198, CellAnim_FrameY)

/* func_0208a1b0: a frame's x offset; -1 for the current frame's. */
s16 CellAnim_FrameX(CellAnim *anim, int frame)
{
    if (frame < 0) {
        frame = anim->frame;
    }
    return data_of(anim)->frames[frame].x;
}
CLEAN_AS(func_0208a1b0, CellAnim_FrameX)

/* func_0208a1c8 */
const CellAnimData *CellAnim_Data(CellAnim *anim)
{
    return data_of(anim);
}
CLEAN_AS(func_0208a1c8, CellAnim_Data)

/* func_0208a1cc */
int CellAnim_Frame(CellAnim *anim)
{
    return anim->frame;
}
CLEAN_AS(func_0208a1cc, CellAnim_Frame)

/* func_0208a1d0: the current frame's cell. */
const OamEntry *CellAnim_Cell(CellAnim *anim)
{
    return data_of(anim)->frames[anim->frame].cell;
}
CLEAN_AS(func_0208a1d0, CellAnim_Cell)

/* func_0208a1e0 */
CellAnim *CellAnim_SetFrame(CellAnim *anim, int frame, fx32 time)
{
    anim->frame = frame;
    anim->time = time;
    return anim;
}
CLEAN_AS(func_0208a1e0, CellAnim_SetFrame)

/* func_0208a1e8 */
CellAnim *CellAnim_SetSpeed(CellAnim *anim, fx32 speed)
{
    anim->speed = speed;
    return anim;
}
CLEAN_AS(func_0208a1e8, CellAnim_SetSpeed)

/* func_0208a1ec */
void CellAnim_SetHold(CellAnim *anim, int hold)
{
    anim->hold = hold;
}
CLEAN_AS(func_0208a1ec, CellAnim_SetHold)

/* func_0208a1f0 */
void CellAnim_SetData(CellAnim *anim, const CellAnimData *data)
{
    anim->data = data;
}
CLEAN_AS(func_0208a1f0, CellAnim_SetData)

/* func_0208a1f4: the destructor, which has nothing to do. */
void CellAnim_Destruct(CellAnim *anim)
{
    (void) anim;
}
CLEAN_AS(func_0208a1f4, CellAnim_Destruct)

/* func_0208a1f8: the constructor: no animation, at one tick a frame, looping. */
void CellAnim_Construct(CellAnim *anim)
{
    anim->data = NULL;
    anim->frame = 0;
    anim->time = 0;
    anim->speed = CELL_ANIM_SPEED_ONE;
    anim->hold = 0;
}
CLEAN_AS(func_0208a1f8, CellAnim_Construct)
