/* Cell animations of main's sprites (the CellAnim of screen_icon.h): a list of frames, each a
 * cell (a run of OBJs, oam_buffer.h) shown for a number of ticks at an offset of its own.
 *
 * `time` counts in 20.12 fixed point, `speed` added to it on each advance (0x1000 is one tick
 * a frame). Once the whole ticks reach the frame's length the animation moves to the next
 * frame: round to the first after the last, or, held (`hold`), it stays on the last. */
#ifndef CLEAN_MAIN_CELL_ANIM_H
#define CLEAN_MAIN_CELL_ANIM_H

#include "oam_buffer.h"  /* OamEntry */
#include "screen_icon.h" /* CellAnim */
#include "types.h"

#define CELL_ANIM_SPEED_ONE 0x1000

/* A frame (12 bytes). */
typedef struct CellAnimFrame {
    const OamEntry *cell;
    int ticks; /* 0x04: how long it shows */
    s16 x;     /* 0x08: the cell's offset from the sprite's place */
    s16 y;     /* 0x0a */
} CellAnimFrame;

/* An animation (CellAnim.data). */
typedef struct CellAnimData {
    const CellAnimFrame *frames;
    int count;
} CellAnimData;

void CellAnim_Advance(CellAnim *anim);
CellAnim *CellAnim_Restart(CellAnim *anim);
void CellAnim_Stop(CellAnim *anim);
int CellAnim_IsDone(CellAnim *anim);
s16 CellAnim_FrameY(CellAnim *anim, int frame);
s16 CellAnim_FrameX(CellAnim *anim, int frame);
const CellAnimData *CellAnim_Data(CellAnim *anim);
int CellAnim_Frame(CellAnim *anim);
const OamEntry *CellAnim_Cell(CellAnim *anim);
CellAnim *CellAnim_SetFrame(CellAnim *anim, int frame, fx32 time);
CellAnim *CellAnim_SetSpeed(CellAnim *anim, fx32 speed);
void CellAnim_SetHold(CellAnim *anim, int hold);
void CellAnim_SetData(CellAnim *anim, const CellAnimData *data);
void CellAnim_Destruct(CellAnim *anim);
void CellAnim_Construct(CellAnim *anim);

#endif
