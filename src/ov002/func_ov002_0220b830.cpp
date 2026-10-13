/* func_ov002_0220b830 @ 0x0220b830, 0x7c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

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
extern "C" void func_ov002_0220b6b8(char *self);
extern const char data_ov002_0220bea0[];

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
