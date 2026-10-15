/* func_0201e21c @ 0x0201e21c, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0201e21c {
    u8 pad_00[0x5c];
    u32 unk_5C;
    u32 unk_60;
    u32 unk_64;
};

struct Ls {
    u32 a;
    u32 b;
    u32 c;
};

struct UnkStruct_0201e21c_2 {
    u8 a;
    u32 b;
    u8 c;
};

extern "C" int func_02019e00(void *);
extern "C" int func_02019de8(void *);
extern "C" int func_0203af80(Ls *);
extern "C" void func_0202da88(void *, void *);
extern "C" void func_0206844c(u32, UnkStruct_0201e21c_2 *, u32);
extern "C" int func_020155cc(void *);

extern char data_021c222c;
struct Ptmf {
    u32 a;
    u32 b;
};

extern Ptmf __ptmf_null;

class UnkStruct_0201e21c_3 {
  public:
    u8 pad_00[0x40];
    u32 unk_40;
    u8 pad_44[0x6c];
    void (UnkStruct_0201e21c_3::*pmf)(u32 *);
    u8 pad_B8[0x38];
    u32 unk_F0;
    u32 unk_F4;
    u8 pad_F8[8];
    UnkStruct_0201e21c *unk_100;
};

extern "C" void func_0201e21c(UnkStruct_0201e21c_3 *self)
{
    UnkStruct_0201e21c_2 local;
    Ls ls;
    UnkStruct_0201e21c *b;
    u32 *q;

    if (func_02019e00((char *) self->unk_100 + 0x564) == 0 && func_02019de8((char *) self->unk_100 + 0x564) != 0) {
        b = self->unk_100;
        q = &b->unk_5C;
        ls.a = b->unk_5C;
        ls.b = q[1];
        ls.c = q[2];
        ls.b += 0x2000;
        func_0203af80(&ls);

        func_0202da88(self, &data_021c222c);

        if (self->pmf) {
            (self->*self->pmf)(&local.b);
        }

        local.a = local.c;
        func_0206844c(self->unk_40, &local, local.b);

        func_020155cc(self);

        {
            volatile u32 *vp = (volatile u32 *) &__ptmf_null;
            u32 ga = vp[0];
            u32 gb = vp[1];
            self->unk_F0 = ga;
            self->unk_F4 = gb;
        }
    }
}
