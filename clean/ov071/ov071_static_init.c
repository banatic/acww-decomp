/* Overlay 71's static initialiser, run when the overlay is loaded: the insurance seller's
 * half-angle of "ahead", copied from main's; his table of states (insurer.h), copied from the
 * overlay's constants (the compiler cannot place member pointers in initialised data); and the
 * two offsets his probe tries (Vec3 objects), each registered for destruction. */
#include "autoload_2/vector.h"
#include "clean.h"
#include "insurer.h"
#include "ov004/member_pointer.h"
#include "types.h"

/* The half-angle, and main's. */
extern s16 data_ov071_0227a340;
extern s16 data_020c80f0;

/* His states: each one's entry, then its update (state 2 has no entry: the null member
 * pointer). */
extern const MemberPointer data_ov071_0227a120, data_ov071_0227a118, data_ov071_0227a100, data_ov071_0227a178,
    data_ov071_0227a108, data_ov071_0227a110, data_ov071_0227a128, data_ov071_0227a160, data_ov071_0227a138,
    data_ov071_0227a140, data_ov071_0227a148;
extern const MemberPointer __ptmf_null;
extern InsurerStep data_ov071_0227a3a4[INSURER_STATES];

/* The record __register_global_object links an object into, so that its destructor runs when
 * the overlay goes. */
typedef struct InsurerInitRecord {
    struct InsurerInitRecord *next;
    void *destruct;
    void *object;
} InsurerInitRecord;

extern void __register_global_object(void *object, void *destruct, void *record);
/* TrivialObject_Destruct, handed on as the game's function. */
extern void func_020012dc(void *object);

/* The offsets he steps aside to (Insurer_StepAside), at +x and at -x, and their records. */
extern Vec3 data_ov071_0227a38c;
extern Vec3 data_ov071_0227a398;
extern InsurerInitRecord data_ov071_0227a34c;
extern InsurerInitRecord data_ov071_0227a358;

static void insurer_init_offset(Vec3 *offset, fx32 x, InsurerInitRecord *record)
{
    offset->x = x;
    offset->y = 0;
    offset->z = 0x1000;
    __register_global_object(offset, (void *) (uintptr_t) func_020012dc, record);
}

/* __sinit_ov071_02279fd4: the half-angle, the entries and updates of the six states in order,
 * then the offsets (0.5, 0, 1.0) and (-0.5, 0, 1.0). */
void InsurerInit_Tables(void)
{
    static const MemberPointer *const states[2 * INSURER_STATES] = {
        &data_ov071_0227a120, &data_ov071_0227a118, /* 0: the talk ends */
        &data_ov071_0227a100, &data_ov071_0227a178, /* 1: chase */
        &__ptmf_null,         &data_ov071_0227a108, /* 2: talked */
        &data_ov071_0227a110, &data_ov071_0227a128, /* 3: wander */
        &data_ov071_0227a160, &data_ov071_0227a138, /* 4: wait */
        &data_ov071_0227a140, &data_ov071_0227a148, /* 5: talk */
    };
    data_ov071_0227a340 = data_020c80f0;
    for (int i = 0; i < INSURER_STATES; i++) {
        data_ov071_0227a3a4[i].enter = *states[2 * i];
        data_ov071_0227a3a4[i].update = *states[2 * i + 1];
    }
    insurer_init_offset(&data_ov071_0227a38c, 0x800, &data_ov071_0227a34c);
    insurer_init_offset(&data_ov071_0227a398, -0x800, &data_ov071_0227a358);
}
CLEAN_AS(__sinit_ov071_02279fd4, InsurerInit_Tables)
