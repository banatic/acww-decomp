/* Small pieces of the game's start-up (system.h). */
#include "system.h"

#include "clean.h"

/* The frames drawn: func_0206e63c counts one per frame, and the game times slow updates with
 * it (every 128 frames in func_020c0b30). */
extern int data_021fbdd0;
/* Cleared with the frame count; nothing else in the game is known to use it. */
extern int data_021fbdd4;

/* func_020e906c: the start-up (func_020b1b84) sets the frame count to 0. */
void System_ResetFrameCount(void)
{
    data_021fbdd0 = 0;
    data_021fbdd4 = 0;
}
CLEAN_AS(func_020e906c, System_ResetFrameCount)

/* func_020e95f8: does nothing; the graphics set-up (func_020540e4) calls it first. */
void System_Nothing(void) {}
CLEAN_AS(func_020e95f8, System_Nothing)
