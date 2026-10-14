/* func_ov147_02299d20 @ 0x02299d20, 0x2c bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov147_0229aa2819func_ov147_02299d20Ev
 */

#include "cpp/ov147/Obj_ov147_0229aa28.h"

struct Unk_02299d20 {
    int unk_00;
    int unk_04;
};

extern "C" struct Unk_02299d20 *func_020682e0(int a);
extern "C" void func_02068320(struct Unk_02299d20 *p);
extern "C" void func_ov147_0229a630(char *p, int a);

void Obj_ov147_0229aa28::func_ov147_02299d20()
{
    char *self = (char *) this;
    struct Unk_02299d20 *p;

    p = func_020682e0(0);
    if (p->unk_04 != 0) {
        return;
    }
    func_02068320(p);
    ((Obj_ov147_0229aa28 *) self)->func_ov147_02299fc8(0);
    self += 0xb0;
    func_ov147_0229a630(self, 1);
}
