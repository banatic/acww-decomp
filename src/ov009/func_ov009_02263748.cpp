/* func_ov009_02263748 @ 0x02263748, 0x44 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov009_022658dc19func_ov009_02263748Ev
 */

#include "cpp/ov009/Obj_ov009_022658dc.h"

struct UnkStruct_02263748 {
    void *pad_00;
    void *unk_04;
};

extern "C" void func_0203ee08(void *, void *);
extern "C" void func_0203e020(void *);

void Obj_ov009_022658dc::func_ov009_02263748()
{
    if (unk_40 && ((UnkStruct_02263748 *) unk_40)->unk_04 == 0) {
        vfunc_84();
        void *arg = this;
        if (this) {
            arg = (char *) this + 0xec;
        }
        func_0203ee08(this, arg);
        func_0203e020(this);
    } else {
        vfunc_80();
    }
}
