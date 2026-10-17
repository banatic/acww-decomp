/* Overlay 78's static initialiser, run when the overlay is loaded: the six colours its source
 * file defines for itself, the table of the camel's states (camel.h) filled from the overlay's
 * constants, and the two points beside her she steps aside to (objects registered for
 * destruction with a destructor that does nothing). */
#include <stdint.h>

#include "autoload_2/vector.h"
#include "camel.h"
#include "clean.h"
#include "ov004/member_pointer.h"
#include "types.h"

/* A colour of four 5-bit components (the fourth always 31). */
typedef struct CamelInitColour {
    u8 c0;
    u8 c1;
    u8 c2;
    u8 c3;
} CamelInitColour;

static void camel_init_colour(CamelInitColour *colour, u8 c0, u8 c1, u8 c2, u8 c3)
{
    colour->c0 = c0;
    colour->c1 = c1;
    colour->c2 = c2;
    colour->c3 = c3;
}

/* Red, blue, yellow, green, cyan and grey. */
extern CamelInitColour data_ov078_02279c04, data_ov078_02279c10, data_ov078_02279c14, data_ov078_02279c08, data_ov078_02279c0c,
    data_ov078_02279c00;

/* The constants of the states' table: each state's entry, then its run; CAMEL_DONE has no
 * entry. */
extern const MemberPointer __ptmf_null;
extern const MemberPointer data_ov078_02279a38, data_ov078_02279a40, data_ov078_02279a20, data_ov078_02279a00,
    data_ov078_02279a08, data_ov078_02279a10, data_ov078_02279a18, data_ov078_02279a28, data_ov078_02279a30;

/* The record __register_global_object links an object into, so that its destructor runs when
 * the overlay goes. */
typedef struct CamelInitRecord {
    struct CamelInitRecord *next;
    void *destruct;
    void *object;
} CamelInitRecord;

extern void __register_global_object(void *object, void *destruct, void *record);
/* TrivialObject_Destruct, handed on as the game's function. */
extern void func_020012dc(void *object);

/* The points beside her (0.5 to +x, then to -x, 1.0 ahead) and their records. */
extern Vec3 data_ov078_02279c30, data_ov078_02279c3c;
extern CamelInitRecord data_ov078_02279c18, data_ov078_02279c24;

/* __sinit_ov078_022798ac: the colours, the states' table in order, then each point set and
 * registered. */
void CamelInit_Tables(void)
{
    static const MemberPointer *const states[2 * CAMEL_STATES] = {
        &data_ov078_02279a38, &data_ov078_02279a40, /* CAMEL_FINISH: Camel_EnterFinish, Camel_UpdateFinish */
        &__ptmf_null,         &data_ov078_02279a20, /* CAMEL_DONE: no entry, Camel_UpdateDone */
        &data_ov078_02279a00, &data_ov078_02279a08, /* CAMEL_WANDER */
        &data_ov078_02279a10, &data_ov078_02279a18, /* CAMEL_STAND */
        &data_ov078_02279a28, &data_ov078_02279a30, /* CAMEL_TALK */
    };

    camel_init_colour(&data_ov078_02279c04, 31, 20, 20, 31);
    camel_init_colour(&data_ov078_02279c10, 20, 20, 31, 31);
    camel_init_colour(&data_ov078_02279c14, 31, 31, 20, 31);
    camel_init_colour(&data_ov078_02279c08, 20, 31, 20, 31);
    camel_init_colour(&data_ov078_02279c0c, 20, 31, 31, 31);
    camel_init_colour(&data_ov078_02279c00, 20, 24, 24, 31);
    for (int i = 0; i < CAMEL_STATES; i++) {
        data_ov078_02279c48[i].enter = *states[2 * i];
        data_ov078_02279c48[i].run = *states[2 * i + 1];
    }
    data_ov078_02279c30 = (Vec3){0x800, 0, 0x1000};
    __register_global_object(&data_ov078_02279c30, (void *) (uintptr_t) func_020012dc, &data_ov078_02279c18);
    data_ov078_02279c3c = (Vec3){-0x800, 0, 0x1000};
    __register_global_object(&data_ov078_02279c3c, (void *) (uintptr_t) func_020012dc, &data_ov078_02279c24);
}
CLEAN_AS(__sinit_ov078_022798ac, CamelInit_Tables)
