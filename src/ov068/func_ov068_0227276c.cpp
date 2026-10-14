/* func_ov068_0227276c @ 0x0227276c, 0x64 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov068_0227775019func_ov068_0227276cEv
 */

#include "cpp/ov068/Obj_ov068_02277750.h"

extern "C" int func_02056f94(void *);
extern "C" void func_02095ec4(void);
extern "C" void *func_ov068_02272cd4(void *);
extern "C" void func_02095a8c(void *, int);
extern "C" void func_02055124(void *);

void Obj_ov068_02277750::func_ov068_0227276c()
{
    unsigned char *self = (unsigned char *) this;
    if (func_02056f94(self + 0x1d8)) {
        unsigned char b = self[0x2dd];
        switch (b) {
            case 0x12:
                func_02095ec4();
                func_02095a8c(func_ov068_02272cd4(self), 4);
                break;
            case 0x1c:
                ((Obj_ov068_02277750 *) self)->func_ov068_02272a7c(4);
                // fall through
        }
        if (self[0x2dd] < 200) {
            self[0x2dd]++;
        }
    } else {
        func_02055124(self + 0x13c);
    }
}
