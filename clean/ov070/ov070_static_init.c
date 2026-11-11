/* Overlay 70's static initializer, run when the overlay is loaded: six colors a source file
 * of the overlay defines for itself, and the giraffe's table of states (giraffe.h), copied
 * from the overlay's constants (the compiler cannot place member pointers in initialized
 * data). */
#include "clean.h"
#include "giraffe.h"
#include "ov004/member_pointer.h"
#include "types.h"

/* A color of four 5-bit components (the fourth always 31). */
typedef struct GiraffeInitColor {
    u8 c0;
    u8 c1;
    u8 c2;
    u8 c3;
} GiraffeInitColor;

extern GiraffeInitColor data_ov070_02279f00, data_ov070_02279f04, data_ov070_02279f08, data_ov070_02279f0c,
    data_ov070_02279f14, data_ov070_02279f18;

/* Her states: each one's entry, then its update (state 2 has no entry: the null member
 * pointer). */
extern const MemberPointer data_ov070_02279d50, data_ov070_02279d48, data_ov070_02279d28, data_ov070_02279d30,
    data_ov070_02279d38;
extern const MemberPointer __ptmf_null;
extern GiraffeStep data_ov070_02279f24[GIRAFFE_STATE_COUNT];

static void giraffe_init_color(GiraffeInitColor *color, u8 c0, u8 c1, u8 c2, u8 c3)
{
    color->c0 = c0;
    color->c1 = c1;
    color->c2 = c2;
    color->c3 = c3;
}

/* __sinit_ov070_02279c50: the colors red, blue, yellow, green, cyan and gray, then the
 * entries and updates of the three states, in order. */
void GiraffeInit_Tables(void)
{
    static const MemberPointer *const states[2 * GIRAFFE_STATE_COUNT] = {
        &data_ov070_02279d50, &data_ov070_02279d48, /* 0: stand */
        &data_ov070_02279d28, &data_ov070_02279d30, /* 1: talk */
        &__ptmf_null,         &data_ov070_02279d38, /* 2: talked */
    };
    giraffe_init_color(&data_ov070_02279f00, 31, 20, 20, 31);
    giraffe_init_color(&data_ov070_02279f08, 20, 20, 31, 31);
    giraffe_init_color(&data_ov070_02279f18, 31, 31, 20, 31);
    giraffe_init_color(&data_ov070_02279f14, 20, 31, 20, 31);
    giraffe_init_color(&data_ov070_02279f0c, 20, 31, 31, 31);
    giraffe_init_color(&data_ov070_02279f04, 20, 24, 24, 31);
    for (int i = 0; i < GIRAFFE_STATE_COUNT; i++) {
        data_ov070_02279f24[i].enter = *states[2 * i];
        data_ov070_02279f24[i].update = *states[2 * i + 1];
    }
}
CLEAN_AS(__sinit_ov070_02279c50, GiraffeInit_Tables)
