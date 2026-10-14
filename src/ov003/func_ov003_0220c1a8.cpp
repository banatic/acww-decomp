/* func_ov003_0220c1a8 @ 0x0220c1a8, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov003_0223801019func_ov003_0220c1a8Ev
 */

#include "cpp/ov003/Obj_ov003_02238010.h"

extern "C" {
int func_020b6590(void);
void func_020b7d84(int, void *, void *, int, int, int);
}

int Obj_ov003_02238010::func_ov003_0220c1a8()
{
    int v;

    func_ov003_0220bfe8();
    v = func_020b6590();
    func_020b7d84(v, &unk_138, &unk_5C, 0xc00, 9, (unsigned char) *(unsigned int *) (Base_0203f080::pad_04 + 4));
    return 1;
}
