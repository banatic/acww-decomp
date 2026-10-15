/* func_ov106_0229ef30 @ 0x0229ef30, 0x5c bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov106_0229f6e019func_ov106_0229ef30Ev
 */

#include "cpp/ov106/Obj_ov106_0229f6e0.h"

extern "C" void func_0206f58c(void);
extern "C" int func_0206f56c(void);
extern "C" void func_ov106_0229cc50(unsigned char *);
extern "C" void func_ov106_0229c378(unsigned char *);
extern "C" int func_ov002_02207d24(unsigned char *, int);
extern "C" void func_ov106_0229e9a4(unsigned char *);
extern "C" void func_ov106_0229e99c(unsigned char *);

int Obj_ov106_0229f6e0::func_ov106_0229ef30()
{
    unsigned char *self = (unsigned char *) this;
    if (((void) (func_0206f58c()), func_0206f56c()) != 0) {
        if (self[0x8d] == 0 || self[0x8d] == 1 || self[0x8d] == 7) {
            func_ov106_0229cc50(self);
            func_ov106_0229c378(self);
            func_ov002_02207d24(self + 0x21b8, 0);
            return 1;
        }
    }
    func_ov106_0229e9a4(self);
    ((Obj_ov106_0229f6e0 *) self)->func_ov106_0229ef8c();
    func_ov106_0229e99c(self);
    return 1;
}
