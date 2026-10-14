/* func_ov068_022726a0 @ 0x022726a0, 0x22 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov068_0227775019func_ov068_022726a0Ev
 */

#include "cpp/ov068/Obj_ov068_02277750.h"

struct UnkStruct_022726a0 {
    int unk_00;
    int unk_04;
};

extern "C" struct UnkStruct_022726a0 *func_020682e0(int);
extern "C" void func_02068320(struct UnkStruct_022726a0 *);

void Obj_ov068_02277750::func_ov068_022726a0()
{
    void *arg0 = (void *) this;
    struct UnkStruct_022726a0 *p;
    p = func_020682e0(0);
    if (p->unk_04 == 0) {
        func_02068320(p);
        ((Obj_ov068_02277750 *) arg0)->func_ov068_02272a7c(6);
    }
}
