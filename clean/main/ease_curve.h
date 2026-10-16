/* The share of a move done at a time, for a move whose speed rises evenly from 0 over its first
 * part, stays even, then falls evenly to 0 over its last part (the camera's moves,
 * camera_view.h). */
#ifndef CLEAN_MAIN_EASE_CURVE_H
#define CLEAN_MAIN_EASE_CURVE_H

#include "types.h"

fx32 EaseCurve_Share(fx32 time, fx32 start, fx32 end, fx32 rise, fx32 fall);

#endif
