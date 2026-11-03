/* outdoor_villager_walks_5: 2 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_0226c910 @ 0x0226c910, 0x54 bytes, Thumb
 * func_ov068_0226c8b0 @ 0x0226c8b0, 0x60 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0226c910_2 {
    virtual int v0();
    virtual int v1();
    virtual int v2();
    virtual int v3();
    virtual int v4();
    virtual int v5();
    virtual int v6();
    virtual int v7();
    virtual int v8();
    virtual int v9();
    virtual int v10();
    virtual int v11();
    virtual int v12();
    virtual int v13();
    virtual int v14();
    virtual int v15();
    virtual int v16();
    virtual int v17();
    virtual int v18();
    virtual int v19();
    virtual int v20();
    virtual int v21();
    virtual int v22();
    virtual int v23();
    virtual int v24();
    virtual int real();
};

struct UnkStruct_0226c910 {
    unsigned char pad_00[0x1d];
    unsigned char b0 : 1;
    unsigned char b1 : 1;
};

extern "C" int func_020984e8(void);
extern "C" int func_02099020(int, int);
extern "C" struct UnkStruct_0226c910 *func_0207f270(int);
extern "C" int func_0207d578(int, int);

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

extern "C" int func_ov068_0226c910(int a0, UnkStruct_0226c910_2 *obj)
{
    int r0;
    int r5;
    int r6;
    int r4;

    r0 = func_020984e8();
    if (r0 != 0) {
        r0 = func_02099020(r0, 1);
    } else {
        r0 = 0;
    }
    r5 = (r0 != 0);

    r6 = obj->real();

    r4 = 1;
    if (func_0207f270(r6)->b1 == 0) {
        if (r5 != 0 || func_0207d578(r6, 0) == 0) {
            r4 = 0;
        }
    }
    return r4;
}

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
