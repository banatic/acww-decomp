/* func_ov110_0229dba4 @ 0x0229dba4, 0x50 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov110_0229ecb819func_ov110_0229dba4Ev
 */

#include "cpp/ov110/Obj_ov110_0229ecb8.h"

extern "C" int func_ov002_02209f64(void *p);
extern "C" unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern "C" void func_ov110_0229cff8(void *p, unsigned char b);
extern "C" void func_ov110_0229cdb4(void *p);

void Obj_ov110_0229ecb8::func_ov110_0229dba4()
{
    char *self = (char *) this;
    if (func_ov002_02209f64(self + 0x22e0) == 0) {
        func_ov002_02208098((void *) (self), *(unsigned char *) (self + 0xf8));
        if (((unsigned char) (*(unsigned char *) (self + 0xf8) + 0xfc)) <= 1) {
            func_ov110_0229cff8(self, *(unsigned char *) (self + 0xf5));
        }
        ((Obj_ov110_0229ecb8 *) self)->func_ov110_0229e7cc();
    }
    func_ov110_0229cdb4(self);
}
