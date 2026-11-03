/* error_message_3: 2 functions, module ov002
 * mwccarm 1.2/base -O4,s
 * func_ov002_0220b8ac @ 0x0220b8ac, 0x10c bytes, Thumb
 * func_ov002_0220b830 @ 0x0220b830, 0x7c bytes, Thumb
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
extern "C" void func_ov002_0220b6b8(void *receiver);
extern "C" int func_0206f56c(void);
extern "C" void func_ov002_0220b6f4(char *self);
extern "C" int func_ov002_02207d24(char *self, int a);
extern "C" int func_ov002_0220b6d0(char *self);
extern "C" void func_ov002_0220b6b0(char *self);
extern "C" int func_ov002_02207d5c(char *self);
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u16 data_021fbe40[];

class UnkStruct_0220b830 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
};

extern "C" void *func_020682e0(int which);
extern "C" void func_020a8164(void *p, const void *d);
extern "C" void func_02068340(void *w, void *p);
extern "C" void func_02068314(void *w);
extern "C" void func_02068308(void *w);
extern "C" void func_02068440(void *w);
extern const char data_ov002_0220bea0[];

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
                    func_ov002_0220b6b8(self);
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

extern "C" void func_ov002_0220b830(char *self, u8 *src, int flag)
{
    int *w = (int *) func_020682e0(1);

    ((UnkStruct_0220b830 *) (self + 0xd0))->f2();
    func_020a8164(self + 0xd0, data_ov002_0220bea0);
    *(u8 *) (self + 0xee) = *src;
    func_02068340(w, self + 0xd0);
    func_02068314(w);
    if (flag == 0) {
        func_02068308(w);
    }
    w[2] = 1;
    func_02068440(w);
    *(u8 *) (self + 0x118) = 0;
    if (*(u8 *) (self + 0x119) == 0) {
        func_ov002_0220b6b8(self);
    }
}
