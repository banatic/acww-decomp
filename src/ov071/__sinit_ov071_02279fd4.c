/* __sinit_ov071_02279fd4 @ 0x02279fd4, 0x114 bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct {
    u32 a, b;
} Pair;
typedef struct {
    s32 unk_00, unk_04, unk_08;
} Timer;

extern s16 data_020c80f0;
extern u16 data_ov071_0227a340;

extern Pair data_ov071_0227a120, data_ov071_0227a118, data_ov071_0227a100, data_ov071_0227a178, __ptmf_null,
    data_ov071_0227a108, data_ov071_0227a110, data_ov071_0227a128, data_ov071_0227a160, data_ov071_0227a138,
    data_ov071_0227a140, data_ov071_0227a148;
extern Pair data_ov071_0227a3a4[12];

extern Timer data_ov071_0227a38c;
extern Timer data_ov071_0227a398;

extern void func_020012dc(void *object);
extern u8 data_ov071_0227a34c[];
extern u8 data_ov071_0227a358[];

extern void __register_global_object(Timer *t, void *destructor, void *name);

#define DisposeGlobal_func_020012dc ((void *) &func_020012dc)

static __inline void InitTimer(Timer *t, s32 period, void *name)
{
    t->unk_00 = period;
    t->unk_04 = 0;
    t->unk_08 = 0x1000;
    __register_global_object(t, DisposeGlobal_func_020012dc, name);
}

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_ov071_02279fd4(void)
{
    data_ov071_0227a340 = (u16) data_020c80f0;

    data_ov071_0227a3a4[0] = data_ov071_0227a120;
    data_ov071_0227a3a4[1] = data_ov071_0227a118;
    data_ov071_0227a3a4[2] = data_ov071_0227a100;
    data_ov071_0227a3a4[3] = data_ov071_0227a178;
    data_ov071_0227a3a4[4] = __ptmf_null;
    data_ov071_0227a3a4[5] = data_ov071_0227a108;
    data_ov071_0227a3a4[6] = data_ov071_0227a110;
    data_ov071_0227a3a4[7] = data_ov071_0227a128;
    data_ov071_0227a3a4[8] = data_ov071_0227a160;
    data_ov071_0227a3a4[9] = data_ov071_0227a138;
    data_ov071_0227a3a4[10] = data_ov071_0227a140;
    data_ov071_0227a3a4[11] = data_ov071_0227a148;

    InitTimer(&data_ov071_0227a38c, 0x800, data_ov071_0227a34c);
    {
        Timer *p = (Timer *) &data_ov071_0227a398;
        p->unk_00 = -0x800;
        p->unk_04 = 0;
        p->unk_08 = 0x1000;
        __register_global_object(p, DisposeGlobal_func_020012dc, data_ov071_0227a358);
    }
}

#undef DisposeGlobal_func_020012dc

#pragma section INIT end
