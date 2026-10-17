/* Overlay 73's static initialiser, run when the overlay is loaded: the six colours its source
 * file defines for itself, the table of its character's states (boar.h) filled from the
 * overlay's constants, and the two points beside the character it steps aside to (objects
 * registered for destruction with a destructor that does nothing). */
#include "autoload_2/vector.h"
#include "boar.h"
#include "clean.h"
#include "ov004/member_pointer.h"
#include "types.h"

/* A colour of four 5-bit components (the fourth always 31). */
typedef struct BoarInitColour {
    u8 c0;
    u8 c1;
    u8 c2;
    u8 c3;
} BoarInitColour;

static void boar_init_colour(BoarInitColour *colour, u8 c0, u8 c1, u8 c2, u8 c3)
{
    colour->c0 = c0;
    colour->c1 = c1;
    colour->c2 = c2;
    colour->c3 = c3;
}

/* Red, blue, yellow, green, cyan and grey. */
extern BoarInitColour data_ov073_02279bc4, data_ov073_02279bd8, data_ov073_02279bcc, data_ov073_02279bd4, data_ov073_02279bc0,
    data_ov073_02279bc8;

/* The constants of the states' table: each state's entry, then its run; BOAR_DONE has no
 * entry. */
extern const MemberPointer __ptmf_null;
extern const MemberPointer data_ov073_022799c8, data_ov073_022799e0, data_ov073_022799e8, data_ov073_022799f0,
    data_ov073_022799f8, data_ov073_02279a00, data_ov073_02279a08, data_ov073_022799d8, data_ov073_022799d0;

/* The record __register_global_object links an object into, so that its destructor runs when
 * the overlay goes. */
typedef struct BoarInitRecord {
    struct BoarInitRecord *next;
    void *destruct;
    void *object;
} BoarInitRecord;

extern void __register_global_object(void *object, void *destruct, void *record);
/* TrivialObject_Destruct, handed on as the game's function. */
extern void func_020012dc(void *object);

/* The points beside it (0.5 to +x, then to -x, 1.0 ahead) and their records. */
extern Vec3 data_ov073_02279bfc[2];
extern BoarInitRecord data_ov073_02279be4, data_ov073_02279bf0;

/* __sinit_ov073_0227985c: the colours, the states' table in order, then each point set and
 * registered. */
void BoarInit_Tables(void)
{
    static const MemberPointer *const states[2 * BOAR_STATES] = {
        &data_ov073_022799c8, &data_ov073_022799e0, /* BOAR_FINISH: Boar_EnterFinish, Boar_UpdateFinish */
        &__ptmf_null,         &data_ov073_022799e8, /* BOAR_DONE: no entry, Boar_UpdateDone */
        &data_ov073_022799f0, &data_ov073_022799f8, /* BOAR_WANDER */
        &data_ov073_02279a00, &data_ov073_02279a08, /* BOAR_STAND */
        &data_ov073_022799d8, &data_ov073_022799d0, /* BOAR_TALK */
    };

    boar_init_colour(&data_ov073_02279bc4, 31, 20, 20, 31);
    boar_init_colour(&data_ov073_02279bd8, 20, 20, 31, 31);
    boar_init_colour(&data_ov073_02279bcc, 31, 31, 20, 31);
    boar_init_colour(&data_ov073_02279bd4, 20, 31, 20, 31);
    boar_init_colour(&data_ov073_02279bc0, 20, 31, 31, 31);
    boar_init_colour(&data_ov073_02279bc8, 20, 24, 24, 31);
    for (int i = 0; i < BOAR_STATES; i++) {
        data_ov073_02279c14[i].enter = *states[2 * i];
        data_ov073_02279c14[i].run = *states[2 * i + 1];
    }
    data_ov073_02279bfc[0] = (Vec3){0x800, 0, 0x1000};
    __register_global_object(&data_ov073_02279bfc[0], (void *) (uintptr_t) func_020012dc, &data_ov073_02279be4);
    data_ov073_02279bfc[1] = (Vec3){-0x800, 0, 0x1000};
    __register_global_object(&data_ov073_02279bfc[1], (void *) (uintptr_t) func_020012dc, &data_ov073_02279bf0);
}
CLEAN_AS(__sinit_ov073_0227985c, BoarInit_Tables)
