/* func_ov115_0229e140 @ 0x0229e140, 0x28 bytes, Thumb, module ov115
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov115_0229e8b819func_ov115_0229e140Ev
 */

#include "cpp/ov115/Obj_ov115_0229e8b8.h"

extern "C" int func_ov002_02209f64(void *p);
extern "C" void func_ov002_02208098(void *self, unsigned char b);

struct UnkStruct_0229e140 {
    char pad_00[0x94];
    char unk_94;
    char pad_95[0x142C - 0x94 - 1];
    unsigned char unk_142C;
};

int Obj_ov115_0229e8b8::func_ov115_0229e140()
{
    struct UnkStruct_0229e140 *self = (struct UnkStruct_0229e140 *) this;
    if (func_ov002_02209f64(&self->unk_94) == 0) {
        func_ov002_02208098(self, self->unk_142C);
        ((Obj_ov115_0229e8b8 *) self)->func_ov115_0229e5e8();
    }
}
