/* func_ov068_0226c8b0 @ 0x0226c8b0, 0x60 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;

class UnkStruct_0226c8b0 {
  public:
    virtual void o0();
    virtual void o1();
    virtual void o2();
    virtual void o3();
    virtual void o4();
    virtual void o5();
    virtual void o6();
    virtual void o7();
    virtual void o8();
    virtual void o9();
    virtual void o10();
    virtual void o11();
    virtual void o12();
    virtual void o13();
    virtual void o14();
    virtual void o15();
    virtual void o16();
    virtual void o17();
    virtual void o18();
    virtual void o19();
    virtual void o20();
    virtual void o21();
    virtual void o22();
    virtual void o23();
    virtual void o24();
    virtual void *o25();
};

extern "C" int func_02013894(void *);
extern "C" int func_02013300(void *);
extern "C" u8 *func_020800d0(void *);
extern "C" void func_0204f794(Vec *, int, int);
extern "C" int func_020ea990(Vec *, void *);

extern "C" int func_ov068_0226c8b0(char *self, UnkStruct_0226c8b0 *o)
{
    Vec v;
    u8 *q;

    if (func_02013894(self + 0x3c) != 0) {
        if (func_02013300(self + 0x3c) == 3) {
            q = func_020800d0(o->o25());
            func_0204f794(&v, q[0], q[1] + 1);
            if (func_020ea990(&v, (char *) o + 0x5c) < 0x800) {
                return 1;
            }
            return 0;
        }
    }
    return 0;
}
