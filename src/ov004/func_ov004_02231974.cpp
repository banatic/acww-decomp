/* func_ov004_02231974 @ 0x02231974, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/sp2 -O4,s
 * compiler-emitted symbol: _ZThn656_N18Obj_ov004_022558f817vfunc_02066994_10Ev
 */

#include "types.h"
#include "cpp/ov004/Obj_ov004_022558f8.h"

struct UnkStruct_02231974 {
    int a;
    ~UnkStruct_02231974() {}
};

extern "C" {
extern void func_02068bc4(void *, int);
extern void func_02068bb8(void *, int);
}

Obj_ov004_022558f8::~Obj_ov004_022558f8() {}

void Obj_ov004_022558f8::vfunc_02066994_10()
{
    char *self = (char *) this;
    UnkStruct_02231974 t;
    char *p = *(char **) (self + 0x2d0);
    switch (*(u8 *) (self + 0x2ae)) {
        case 0xe:
            func_02068bc4(p + 0x1a2c, 0);
            break;
        case 0x2a:
        case 0x2b:
        case 0x2c:
            func_02068bb8(p + 0x1a2c, 0);
            break;
    }
}
