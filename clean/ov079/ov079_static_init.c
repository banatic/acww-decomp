/* Overlay 79's static initialiser, run when the overlay is loaded: the six colours its source
 * file defines for itself, the table of the walrus's states (walrus.h) filled from the
 * overlay's constants, and the two points beside him he steps aside to (objects
 * registered for destruction with a destructor that does nothing). */
#include "autoload_2/vector.h"
#include "walrus.h"
#include "clean.h"
#include "ov004/member_pointer.h"
#include "types.h"

/* A colour of four 5-bit components (the fourth always 31). */
typedef struct WalrusInitColour {
    u8 c0;
    u8 c1;
    u8 c2;
    u8 c3;
} WalrusInitColour;

static void walrus_init_colour(WalrusInitColour *colour, u8 c0, u8 c1, u8 c2, u8 c3)
{
    colour->c0 = c0;
    colour->c1 = c1;
    colour->c2 = c2;
    colour->c3 = c3;
}

/* Red, blue, yellow, green, cyan and grey. */
extern WalrusInitColour data_ov079_0227a1c0, data_ov079_0227a1cc, data_ov079_0227a1d4, data_ov079_0227a1d8,
    data_ov079_0227a1c8, data_ov079_0227a1d0;

/* The constants of the states' table: each state's entry, then its run; WALRUS_DONE has no
 * entry. */
extern const MemberPointer __ptmf_null;
extern const MemberPointer data_ov079_0227a010, data_ov079_02279fe8, data_ov079_02279ff0, data_ov079_02279ff8,
    data_ov079_0227a000, data_ov079_0227a008, data_ov079_0227a018, data_ov079_02279fd8, data_ov079_02279fd0;

/* The record __register_global_object links an object into, so that its destructor runs when
 * the overlay goes. */
typedef struct WalrusInitRecord {
    struct WalrusInitRecord *next;
    void *destruct;
    void *object;
} WalrusInitRecord;

extern void __register_global_object(void *object, void *destruct, void *record);
/* TrivialObject_Destruct, handed on as the game's function. */
extern void func_020012dc(void *object);

/* The points beside it (0.5 to +x, then to -x, 1.0 ahead) and their records. */
extern Vec3 data_ov079_0227a1f4[2];
extern WalrusInitRecord data_ov079_0227a1dc, data_ov079_0227a1e8;

/* __sinit_ov079_02279e74: the colours, the states' table in order, then each point set and
 * registered. */
void WalrusInit_Tables(void)
{
    static const MemberPointer *const states[2 * WALRUS_STATES] = {
        &data_ov079_0227a010, &data_ov079_02279fe8, /* WALRUS_FINISH: Walrus_EnterFinish, Walrus_UpdateFinish */
        &__ptmf_null,         &data_ov079_02279ff0, /* WALRUS_DONE: no entry, Walrus_UpdateDone */
        &data_ov079_02279ff8, &data_ov079_0227a000, /* WALRUS_WANDER */
        &data_ov079_0227a008, &data_ov079_0227a018, /* WALRUS_STAND */
        &data_ov079_02279fd8, &data_ov079_02279fd0, /* WALRUS_TALK */
    };

    walrus_init_colour(&data_ov079_0227a1c0, 31, 20, 20, 31);
    walrus_init_colour(&data_ov079_0227a1cc, 20, 20, 31, 31);
    walrus_init_colour(&data_ov079_0227a1d4, 31, 31, 20, 31);
    walrus_init_colour(&data_ov079_0227a1d8, 20, 31, 20, 31);
    walrus_init_colour(&data_ov079_0227a1c8, 20, 31, 31, 31);
    walrus_init_colour(&data_ov079_0227a1d0, 20, 24, 24, 31);
    for (int i = 0; i < WALRUS_STATES; i++) {
        data_ov079_0227a224[i].enter = *states[2 * i];
        data_ov079_0227a224[i].run = *states[2 * i + 1];
    }
    data_ov079_0227a1f4[0] = (Vec3){0x800, 0, 0x1000};
    __register_global_object(&data_ov079_0227a1f4[0], (void *) (uintptr_t) func_020012dc, &data_ov079_0227a1dc);
    data_ov079_0227a1f4[1] = (Vec3){-0x800, 0, 0x1000};
    __register_global_object(&data_ov079_0227a1f4[1], (void *) (uintptr_t) func_020012dc, &data_ov079_0227a1e8);
}
CLEAN_AS(__sinit_ov079_02279e74, WalrusInit_Tables)
