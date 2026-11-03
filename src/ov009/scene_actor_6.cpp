/* scene_actor_6: 2 functions, module ov009
 * mwccarm 1.2/base -O4,s
 * func_ov009_022637bc @ 0x022637bc, 0x30 bytes, Thumb, emits _ZN18Obj_ov009_022658dc19func_ov009_022637bcEv
 * func_ov009_02263790 @ 0x02263790, 0x2c bytes, Thumb, emits _ZN18Obj_ov009_022658dc19func_ov009_02263790Ev
 */

#include "cpp/ov009/Obj_ov009_022658dc.h"

extern "C" void func_0203ee14(void *a, void *b);

struct UnkStruct_022637bc {
    char pad[8];
    int unk_08;
};

struct UnkStruct_02263790 {
    int a;
    int b;
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

void Obj_ov009_022658dc::func_ov009_02263790()
{
    if (unk_40 && ((UnkStruct_02263790 *) unk_40)->b) {
        vfunc_7c();
        func_ov009_022639a0(3);
    }
}
