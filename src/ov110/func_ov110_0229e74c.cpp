/* func_ov110_0229e74c @ 0x0229e74c, 0x60 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov110_0229ecb819func_ov110_0229e74cEv
 */

#include "cpp/ov110/Obj_ov110_0229ecb8.h"

extern "C" void func_0206f58c(void);
extern "C" int func_ov110_0229e7ac(void *);
extern "C" void func_ov110_0229cbe0(void *);
extern "C" int func_ov002_02207d24(void *, int);
extern "C" void func_ov110_0229c3b8(void *, int);
extern "C" void func_ov110_0229e370(void *);
extern "C" void func_ov110_0229e368(void *);

int Obj_ov110_0229ecb8::func_ov110_0229e74c()
{
    void *obj = (void *) this;
    func_0206f58c();
    if (func_ov110_0229e7ac(obj) != 0 &&
        (((unsigned char *) obj)[0x8d] == 0 || ((unsigned char *) obj)[0x8d] == 1 || ((unsigned char *) obj)[0x8d] == 4)) {
        func_ov110_0229cbe0(obj);
        func_ov002_02207d24((char *) obj + 0x21f8, 0);
        func_ov110_0229c3b8(obj, 0);
        return 1;
    } else {
        func_ov110_0229e370(obj);
        ((Obj_ov110_0229ecb8 *) obj)->func_ov110_0229e7cc();
        func_ov110_0229e368(obj);
        return 1;
    }
}
