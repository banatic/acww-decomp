/* The timer that lets a face's first animation play again (scene_face.h, and the field actors'
 * at 0x768, field_actor_anim.c): after a pause of 30-119 steps it lets the animation go on one
 * or two times running, then pauses again. */
#ifndef CLEAN_MAIN_FACE_ANIM_TIMER_H
#define CLEAN_MAIN_FACE_ANIM_TIMER_H

#include "types.h"

typedef struct FaceAnimTimer {
    u8 pause;   /* 0x00: steps left before the next go */
    u8 repeats; /* 0x01: goes left after this one, before a new pause */
} FaceAnimTimer;

void FaceAnimTimer_Restart(FaceAnimTimer *timer);
void FaceAnimTimer_Reset(FaceAnimTimer *timer);
int FaceAnimTimer_Step(FaceAnimTimer *timer);
void FaceAnimTimer_NewRepeats(FaceAnimTimer *timer);
void FaceAnimTimer_Destruct(void *timer);
void FaceAnimTimer_Construct(void *timer);

#endif
