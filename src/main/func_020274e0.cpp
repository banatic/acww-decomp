/* func_020274e0 @ 0x020274e0, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN13Base_0202746013func_020274e0Ev
 */

#include "cpp/main/Base_02027460.h"

struct UnkStruct_020274e0_3 {
    int unk_00, unk_04, unk_08;
};

extern "C" {
extern int data_021c2bb4;
void func_0202da88(Base_02027460 *self, void *tbl);
void func_0206844c(UnkStruct_020274e0_3 *a, void *b, int c);
}

void Base_02027460::func_020274e0()
{
    unsigned char arg;
    Out_02027460 out;
    UnkStruct_020274e0_3 *c = (UnkStruct_020274e0_3 *) unk_40;
    if (c->unk_04 == 5) {
        c->unk_08 = 1;
    }
    func_0202da88(this, &data_021c2bb4);
    if (pmf) {
        (this->*pmf)(&out);
    }
    arg = out.b;
    func_0206844c((UnkStruct_020274e0_3 *) unk_40, &arg, out.n);
}
