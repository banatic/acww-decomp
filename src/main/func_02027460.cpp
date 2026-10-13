/* func_02027460 @ 0x02027460, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_02027460.h"

typedef void (Base_02027460::*Pmf2)();
extern int data_021c2b9c;
extern "C" void func_0202da88(Base_02027460 *self, void *tbl);
extern "C" void func_02068484(int a, void *b, int c);
extern "C" int func_02081d20(int);
extern "C" void func_02015094(Base_02027460 *);
extern "C" void func_0202dbf0(Base_02027460 *, Pmf2);
extern "C" void func_02027460(Base_02027460 *self)
{
    unsigned char arg;
    Out_02027460 out;
    if (self->unk_12C && func_02081d20(self->unk_12C) >= 0x40) {
        func_0202da88(self, &data_021c2b9c);
        if (self->pmf) {
            (self->*(self->pmf))(&out);
        }
        arg = out.b;
        func_02068484(self->unk_40, &arg, out.n);
    } else {
        func_02015094(self);
        func_0202dbf0(self, &Base_02027460::func_020274e0);
    }
}
