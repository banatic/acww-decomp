/* func_ov003_0221bd90 @ 0x0221bd90, 0xa4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov003_0223863019func_ov003_0221bd90Ev
 */

#include "cpp/ov003/Obj_ov003_02238630.h"

// Local of the talk-start sequence; its inline destructor keeps an 8-byte frame slot.
struct D {
    int a, b;
    ~D() {}
};

struct UnkStruct_0221bd90 {
    char pad[8];
    int unk_08;
};

extern "C" {
extern char data_ov003_02238778[];
void func_0203ee14(Base_0203f080 *self, Base_02066994 *recv);
void func_020a8164(Base_02066994 &recv, const char *name);
void func_02066914(Base_02066994 &recv, int arg);
void func_020b23ec(int a, int b);
int func_020ae2c4(void);
}

int Obj_ov003_02238630::func_ov003_0221bd90()
{
    D t;
    func_0203ee14(this, this);
    func_020a8164(*this, data_ov003_02238778);
    if (vfunc_8c() == 0) {
        unk_1E = 0x34;
        if (!flag_236_1) {
            func_020b23ec(unk_136, 0);
        }
    } else if (flag_236_1) {
        unk_1E = 0x31;
    } else if (func_020ae2c4()) {
        unk_1E = 0x32;
    } else {
        unk_1E = 0;
    }
    ((UnkStruct_0221bd90 *) unk_40)->unk_08 = 1;
    func_02066914(*this, 0);
    return 1;
}
