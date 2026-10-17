/* The room object of /roomObj/obj_tailor1 and obj_tailor2 (tailor_object.h). */
#include "tailor_object.h"

#include <stdint.h>

#include "clean.h"

static_assert(offsetof(TailorObject, part) == 0x290, "part");
static_assert(offsetof(TailorObject, part_model) == 0x348, "part model");
static_assert(offsetof(TailorObject, part_texture) == 0x3ec, "part texture");
static_assert(offsetof(TailorObject, part.frames.frame) == 0x334, "part frame");

#define TAILOR_OBJECT_FRAME_SHIFT 12 /* frames are 20.12 fixed point */

/* The one that exists, NULL for none. */
extern TailorObject *data_ov004_02258558;

/* func_ov004_0222fd38: the frame the second model's animation is at, as a whole frame cut to 16
 * bits; 0 when none exists. */
int TailorObject_PartFrame(void)
{
    TailorObject *self = data_ov004_02258558;
    if (self != NULL) {
        return (u16) ((u32) self->part.frames.frame >> TAILOR_OBJECT_FRAME_SHIFT);
    }
    return 0;
}
CLEAN_AS(func_ov004_0222fd38, TailorObject_PartFrame)

/* func_ov004_0222fd58: the second model's animation put at whole frame `frame`; nothing when
 * none exists. */
void TailorObject_SetPartFrame(int frame)
{
    TailorObject *self = data_ov004_02258558;
    if (self != NULL) {
        self->part.frames.frame = (fx32) ((u32) frame << TAILOR_OBJECT_FRAME_SHIFT);
    }
}
CLEAN_AS(func_ov004_0222fd58, TailorObject_SetPartFrame)

/* func_ov004_0222fd70: whether one exists with its state byte at 0 or 3. */
int TailorObject_InState0Or3(void)
{
    TailorObject *self = data_ov004_02258558;
    if (self != NULL) {
        u8 state = self->base.unk_24c[0];
        if (state == 3 || state == 0) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov004_0222fd70, TailorObject_InState0Or3)
