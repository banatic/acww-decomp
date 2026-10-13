/* func_ov004_0222c734 @ 0x0222c734, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

class UnkStruct_0222c734 {
  public:
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24(int a);
};

extern "C" int func_0203efc4(UnkStruct_0222c734 *self);
extern "C" int func_ov004_0222c574(UnkStruct_0222c734 *self);

extern "C" int func_ov004_0222c734(UnkStruct_0222c734 *self)
{
    if (!func_0203efc4(self)) {
        return 0;
    }
    if (*((u8 *) self + 0xea) != 0xff) {
        int t = func_ov004_0222c574(self);
        if (*((u8 *) self + 0x24c) != t) {
            self->s24(t);
        }
    }
    return 1;
}
