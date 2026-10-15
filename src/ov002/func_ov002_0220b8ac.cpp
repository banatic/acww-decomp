/* func_ov002_0220b8ac @ 0x0220b8ac, 0x10c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

class UnkStruct_0220b8ac {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
};

extern "C" int func_ov002_0220b71c(void);
extern "C" void func_ov002_02207d00(char *self);
extern "C" void func_ov002_0220b6b8(void);
extern "C" int func_0206f56c(void);
extern "C" void func_ov002_0220b6f4(char *self);
extern "C" int func_ov002_02207d24(char *self, int a);
extern "C" int func_ov002_0220b6d0(char *self);
extern "C" void func_ov002_0220b6b0(char *self);
extern "C" int func_ov002_02207d5c(char *self);

extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u16 data_021fbe40[];

extern "C" int func_ov002_0220b8ac(char *self, int flag)
{
    int ok;
    u16 v;

    switch (*(u8 *) (self + 0x118)) {
        case 0:
            if (func_ov002_0220b71c()) {
                *(u8 *) (self + 0x118) = 1;
                func_ov002_02207d00(self);
                if (*(u8 *) (self + 0x119) != 0) {
                    asm {
                        mov r0, self
                    }
                    func_ov002_0220b6b8();
                }
            }
            break;
        case 1:
            if (*(u8 *) (self + 0x119) != 0) {
                for (;;) {
                }
            }
            if (flag && func_0206f56c()) {
                goto act;
            }
            if (data_021fbdd8 != 0 && data_021fbddc != 0) {
                ok = 1;
            } else {
                ok = 0;
            }
            if (ok) {
                goto act;
            }
            v = data_021fbe40[1];
            if (v & 1) {
                goto act;
            }
            if (v & 2) {
                goto act;
            }
            if (v & 0x400) {
                goto act;
            }
            if ((v & 0x800) == 0) {
                break;
            }
        act:
            func_ov002_0220b6f4(self);
            *(u8 *) (self + 0x118) = 2;
            func_ov002_02207d24(self, 0);
            break;
        case 2:
            if (func_ov002_0220b6d0(self)) {
                func_ov002_0220b6b0(self);
                *(u8 *) (self + 0x118) = 3;
            }
            break;
        case 3:
            return 1;
    }
    func_ov002_02207d5c(self);
    if (*(u8 *) (self + 0x119) == 0) {
        ((UnkStruct_0220b8ac *) self)->f2();
    }
    return 0;
}
