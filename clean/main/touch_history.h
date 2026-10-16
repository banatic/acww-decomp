/* The touch screen as the game reads it each frame, with what it needs of the frames before
 * (on top of autoload_2/input.h's Touch_Update): where the pen went down, how many frames ago it
 * went down or up (counted up to 200), and a copy of each value as it was in the frame before.
 * While the lid is closed the pen counts as lifted. */
#ifndef CLEAN_MAIN_TOUCH_HISTORY_H
#define CLEAN_MAIN_TOUCH_HISTORY_H

#include "types.h"

/* The frame counts stop here. */
#define TOUCH_HISTORY_MAX_FRAMES 200

void TouchHistory_Update(void);
void TouchHistory_Init(void);

#endif
