/* func_ov009_022637bc @ 0x022637bc, 0x30 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov009_022658dc19func_ov009_022637bcEv
 */

#include "cpp/ov009/Obj_ov009_022658dc.h"

extern "C" void func_0203ee14(void *a, void *b);

struct UnkStruct_022637bc {
    char pad[8];
    int unk_08;
};

int Obj_ov009_022658dc::func_ov009_022637bc()
{
    void *arg1 = this;
    if (this) {
        arg1 = (char *) this + 0xEC;
    }
    func_0203ee14(this, arg1);
    ((UnkStruct_022637bc *) unk_40)->unk_08 = 1;
    vfunc_78();
    return 1;
}
