/* func_ov100_0229ea10 @ 0x0229ea10, 0xa0 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern "C" int func_ov100_0229c2c0(void *self, int mode);
extern "C" int func_0206fe54(void);
extern "C" void func_ov002_02209eb8(void *ptr);
extern "C" void func_ov100_0229ce90(void *self);
extern "C" void func_ov094_0229a7cc(void *ptr, int a, int b);
extern "C" void func_ov094_0229a850(void *ptr, int a, int b);
extern "C" void func_ov094_0229b738(void *ptr, int a, int b);
extern "C" void func_ov094_02299d84(void *ptr, int b);

class VtblClass {
  public:
    virtual int f0();
    virtual int f1();
    virtual int f2();
    virtual int f3();
};

extern "C" int func_ov100_0229ea10(void *self)
{
    if (func_ov100_0229c2c0(self, 1) == 0) {
        return 1;
    }

    if (((void) (((VtblClass *) ((char *) self + 0x218c))->f2()), func_0206fe54()) != 0) {
        func_ov002_02209eb8((char *) self + 0x2274);
    }

    func_ov100_0229ce90(self);

    if (func_ov100_0229c2c0(self, 0x80)) {
        func_ov094_0229a7cc((char *) self + 0xcc, 0, *(u32 *) ((char *) self + 0x28c8));
    }

    if (func_ov100_0229c2c0(self, 2)) {
        func_ov094_0229a850((char *) self + 0xcc, 0, *(u32 *) ((char *) self + 0x28c4));
        func_ov094_0229b738((char *) self + 0xb2c, 0, *(u32 *) ((char *) self + 0x28c4));
        func_ov094_02299d84((char *) self + 0xb54, *(u32 *) ((char *) self + 0x28c4));
    }

    return 1;
}
