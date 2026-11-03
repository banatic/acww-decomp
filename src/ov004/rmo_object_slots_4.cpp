/* rmo_object_slots_4: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222c734 @ 0x0222c734, 0x40 bytes, Thumb
 * func_ov004_0222c704 @ 0x0222c704, 0x30 bytes, Thumb
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

struct UnkStruct_0222c704 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual int v25(void *);
};

extern "C" {
extern void func_02003420(void *, int);
extern void func_ov004_0222c2f8(void *, void *);
}

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

extern "C" void func_ov004_0222c704(char *self, int a1)
{
    // DECLS
    char frame[0xc];
    // ENDDECLS
    ((UnkStruct_0222c704 *) self)->v25(frame);
    func_ov004_0222c2f8(self + 0x250, frame);
    func_02003420(self, a1);
}
