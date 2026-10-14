/* func_ov068_0227507c @ 0x0227507c, 0x54 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov068_02277f3c19func_ov068_0227507cEv
 */

#include "cpp/ov068/Obj_ov068_02277f3c.h"

extern "C" void func_020e895c(int *addr, int val, int mode);
extern "C" void NNS_G3dMdlSetMdlAlpha(void *ptr, unsigned int idx, unsigned char byte);

typedef struct InnerStruct {
    unsigned char pad_00[0x18];
    unsigned char count;
} InnerStruct;

typedef struct OuterStruct {
    unsigned char pad_00[0x148];
    InnerStruct *inner;
    unsigned char pad_14C[0x144];
    int unk_290;
    int unk_294;
} OuterStruct;

int Obj_ov068_02277f3c::func_ov068_0227507c()
{
    OuterStruct *self = (OuterStruct *) this;
    unsigned int i;
    unsigned int n;

    ((Obj_ov068_02277f3c *) self)->func_ov068_02274f18();
    if (self->unk_290 != self->unk_294) {
        func_020e895c(&self->unk_290, self->unk_294, 2);
    }

    n = self->inner->count;
    for (i = 0; i < n; i++) {
        NNS_G3dMdlSetMdlAlpha(self->inner, i, (unsigned char) self->unk_290);
    }

    return 1;
}
