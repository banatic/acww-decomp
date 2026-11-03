/* sequence4: 2 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_02272238 @ 0x02272238, 0x44 bytes, Thumb, emits _ZN18Obj_ov068_0227775019func_ov068_02272238Ev
 * func_ov068_02272208 @ 0x02272208, 0x30 bytes, Thumb, emits _ZN18Obj_ov068_0227775019func_ov068_02272208Ev
 */

#include "cpp/ov068/Obj_ov068_02277750.h"

extern "C" void func_02055060(Obj_020dd05c *, int, int, int, int, int);
extern "C" void func_ov009_02262ef0(Obj_0213f090 *, int);
extern "C" int func_02056f94(void *);
extern "C" void func_02055124(void *);

int Obj_ov068_02277750::func_ov068_02272238()
{
    int ret = vfunc_68();
    func_02055060(&unk_13c, ret, 1, 0x1000, 0, 0);
    func_ov009_02262ef0(&unk_238, 0x088a);
    return 1;
}

void Obj_ov068_02277750::func_ov068_02272208()
{
    if (func_02056f94((char *) this + 0x1d8)) {
        ((Obj_ov068_02277750 *) this)->func_ov068_02272a7c(0xe);
    }
    func_02055124((char *) this + 0x13c);
}
