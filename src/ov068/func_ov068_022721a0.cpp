/* func_ov068_022721a0 @ 0x022721a0, 0x44 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov068_0227775019func_ov068_022721a0Ev
 */

#include "cpp/ov068/Obj_ov068_02277750.h"

extern "C" void func_02095518(int a, int b, int c);
extern "C" void func_02055124(void *p);

void Obj_ov068_02277750::func_ov068_022721a0()
{
    void *self = (void *) this;
    if (*(unsigned char *) ((char *) self + 0x2da) == 0) {
        ((Obj_ov068_02277750 *) self)->func_ov068_02272a7c(0xf);
    }
    if (*(unsigned char *) ((char *) self + 0x2da) != 0) {
        func_02095518(0, 0, 4);
        (*(unsigned char *) ((char *) self + 0x2da))--;
    }
    func_02055124((char *) self + 0x13c);
}
