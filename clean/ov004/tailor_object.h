/* A room object of the RMO family (rmo_object.h) built from /roomObj/obj_tailor1, with a second
 * animated model built from /roomObj/obj_tailor2 (func_ov004_022300fc loads both). Only one
 * exists at a time: data_ov004_02258558 points to it from its start to its release. Overlay 4's
 * code outside it reads and sets the second model's frame through these functions, and asks
 * whether its state byte is 0 or 3. */
#ifndef CLEAN_OV004_TAILOR_OBJECT_H
#define CLEAN_OV004_TAILOR_OBJECT_H

#include "rmo_object.h"
#include "types.h"

typedef struct TailorObject {
    RmoObject base;          /* 0x000: base.unk_24c[0] is its state byte */
    RmoAnimatedModel part;   /* 0x290: obj_tailor2's model */
    RmoModel part_model;     /* 0x348 */
    RmoTexture part_texture; /* 0x3ec */
} TailorObject;

int TailorObject_PartFrame(void);
void TailorObject_SetPartFrame(int frame);
int TailorObject_InState0Or3(void);

#endif
