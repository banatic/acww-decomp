/* Overlay 74's static initializer, run when the overlay is loaded: colors its source files
 * define for themselves, the table of member functions the faceless cat (mystery_cat.h)
 * dispatch her states through, copied from the overlay's constants (the compiler cannot place
 * member pointers in initialized data), and the two points beside her way she steps to,
 * registered for destruction like static C++ objects. */
#include "autoload_2/vector.h"
#include "clean.h"
#include "mystery_cat.h"
#include "types.h"

/* A color of four 5-bit components (the fourth always 31). */
typedef struct MysteryCatInitColor {
    u8 c0;
    u8 c1;
    u8 c2;
    u8 c3;
} MysteryCatInitColor;

/* The record __register_global_object links an object into, so that its destructor runs when
 * the overlay goes. */
typedef struct MysteryCatInitRecord {
    struct MysteryCatInitRecord *next;
    void *destruct;
    void *object;
} MysteryCatInitRecord;

/* The six colors: red, blue, yellow, green, cyan and gray. */
extern MysteryCatInitColor data_ov074_02279d44, data_ov074_02279d54, data_ov074_02279d40, data_ov074_02279d58,
    data_ov074_02279d48, data_ov074_02279d50;
/* The null member pointer (the C++ runtime's) and her states' functions: each one's entry, then
 * its update. */
extern const MemberPointer __ptmf_null;
extern const MemberPointer data_ov074_02279b98, data_ov074_02279b58, data_ov074_02279b60, data_ov074_02279b68,
    data_ov074_02279b70, data_ov074_02279b78, data_ov074_02279b80, data_ov074_02279b88, data_ov074_02279b48;
extern MysteryCatStep data_ov074_02279d9c[MYSTERY_CAT_STATE_COUNT];
/* The points beside her way, and their records. */
extern Vec3 data_ov074_02279d84[2];
extern MysteryCatInitRecord data_ov074_02279d5c, data_ov074_02279d68;

extern void __register_global_object(void *object, void *destruct, void *record);
/* The destructor of a point: nothing (the game's function is handed on). */
extern void func_020012dc(void *object);

static void mcat_init_color(MysteryCatInitColor *color, u8 c0, u8 c1, u8 c2, u8 c3)
{
    color->c0 = c0;
    color->c1 = c1;
    color->c2 = c2;
    color->c3 = c3;
}

static void mcat_init_point(Vec3 *point, fx32 x, MysteryCatInitRecord *record)
{
    point->x = x;
    point->y = 0;
    point->z = 0x1000;
    __register_global_object(point, (void *) (uintptr_t) func_020012dc, record);
}

/* __sinit_ov074_022799d8: the colors; the five states' entries and updates, in order (state 1
 * has no entry); the points (0.5, 0, 1.0) and (-0.5, 0, 1.0), each registered. */
void MysteryCatInit_Tables(void)
{
    static const MemberPointer *const states[2 * MYSTERY_CAT_STATE_COUNT] = {
        &data_ov074_02279b98, &data_ov074_02279b58, /* 0: talk end */
        &__ptmf_null,         &data_ov074_02279b60, /* 1: talked */
        &data_ov074_02279b68, &data_ov074_02279b70, /* 2: wander */
        &data_ov074_02279b78, &data_ov074_02279b80, /* 3: wait */
        &data_ov074_02279b88, &data_ov074_02279b48, /* 4: talk */
    };

    mcat_init_color(&data_ov074_02279d44, 31, 20, 20, 31);
    mcat_init_color(&data_ov074_02279d54, 20, 20, 31, 31);
    mcat_init_color(&data_ov074_02279d40, 31, 31, 20, 31);
    mcat_init_color(&data_ov074_02279d58, 20, 31, 20, 31);
    mcat_init_color(&data_ov074_02279d48, 20, 31, 31, 31);
    mcat_init_color(&data_ov074_02279d50, 20, 24, 24, 31);
    for (int i = 0; i < MYSTERY_CAT_STATE_COUNT; i++) {
        data_ov074_02279d9c[i].enter = *states[2 * i];
        data_ov074_02279d9c[i].update = *states[2 * i + 1];
    }
    mcat_init_point(&data_ov074_02279d84[0], 0x800, &data_ov074_02279d5c);
    mcat_init_point(&data_ov074_02279d84[1], -0x800, &data_ov074_02279d68);
}
CLEAN_AS(__sinit_ov074_022799d8, MysteryCatInit_Tables)
