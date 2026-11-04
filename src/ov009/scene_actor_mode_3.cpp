/* scene_actor_mode_3: 3 functions, module ov009
 * mwccarm 1.2/base -O4,s
 * func_ov009_02263c84 @ 0x02263c84, 0x164 bytes, Thumb
 * func_ov009_02263c14 @ 0x02263c14, 0x70 bytes, Thumb, emits _ZN18Obj_ov009_022658dc19func_ov009_02263c14Ev
 * func_ov009_02263ba8 @ 0x02263ba8, 0x6c bytes, Thumb
 */

#include "cpp/ov009/Obj_ov009_022658dc.h"

struct Buf {
    int data[4];
};

class UnkStruct_02263c84 {
  public:
    virtual int d00();
    virtual int d01();
    virtual int d02();
    virtual int d03();
    virtual int d04();
    virtual int d05();
    virtual int d06();
    virtual int d07();
    virtual int d08();
    virtual int d09();
    virtual int d10();
    virtual int d11();
    virtual int d12();
    virtual int d13();
    virtual int d14();
    virtual int d15();
    virtual int d16();
    virtual int d17();
    virtual int d18();
    virtual int d19();
    virtual int d20();
    virtual int d21();
    virtual int d22();
    virtual int d23();
    virtual int d24();
    virtual int d25();
    virtual int Fn68();
    virtual int d27();
    virtual int d28();
    virtual int d29();
    virtual int d30();
    virtual int d31();
    virtual int d32();
    virtual int d33();
    virtual int d34();
    virtual int d35();
    virtual int d36();
    virtual int d37();
    virtual int Fn98();
    virtual int d39();
    virtual int d40();
    virtual int d41();
    virtual int d42();
    virtual int d43();
    virtual int d44();
    virtual Buf Fnb4();

    char pad_04[0x12c - 4];
    int unk_12C;
    char pad_130[6];
    unsigned short unk_136;
};

extern "C" void func_02055060(void *p, int a, int b, int c, int d, int e);
extern "C" void func_ov009_02262ef0(void *self, int arg);
extern "C" int func_0204bcdc(void *);
extern "C" int func_0204bc64(void *);
extern "C" void func_0206e9ec(void *dst, const void *src);
extern "C" void func_02055124(Obj_020dd05c *p);
extern "C" int func_02056f94(Obj_020dd184 *p);
extern "C" int func_02056f28(Obj_020dd184 *p, int n);
extern "C" int func_0204bba8(void *a);

class Vtbl {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4();
    virtual void f5();
    virtual void f6();
    virtual void f7();
    virtual void f8();
    virtual void f9();
    virtual void f10();
    virtual void f11();
    virtual void f12();
    virtual void f13();
    virtual void f14();
    virtual void f15();
    virtual void f16();
    virtual void f17();
    virtual void f18();
    virtual void f19();
    virtual void f20();
    virtual void f21();
    virtual void f22();
    virtual void f23();
    virtual void f24();
    virtual int f25();
};

extern "C" int func_ov009_02263c84(UnkStruct_02263c84 *self)
{
    int v;
    int w;
    int level;

    v = self->Fn68();
    if (v == 0) {
        goto ret0;
    }

    func_02055060((char *) self + 0x13c, v, 1, 0x1000, 0, 0);
    func_ov009_02262ef0((char *) self + 0x238, 0x7d1);
    func_ov009_02262ef0((char *) self + 0x238, 0x7d2);

    w = self->Fn98();
    if (w == 0) {
        goto ret1;
    }

    level = 0;

    {
        int matched;
        if (func_0204bcdc(&self->unk_136) != 0) {
            unsigned short local = 0x500d;
            matched = (func_0204bc64(&self->unk_136) == func_0204bc64(&local));
        } else {
            matched = (self->unk_136 == 0x500d);
        }
        if (matched) {
            level = 1;
            goto final;
        }
    }
    {
        int matched;
        if (func_0204bcdc(&self->unk_136) != 0) {
            unsigned short local = 0x5000;
            matched = (func_0204bc64(&self->unk_136) == func_0204bc64(&local));
        } else {
            matched = (self->unk_136 == 0x5000);
        }
        if (matched) {
            level = 2;
            goto final;
        }
    }
    {
        int matched;
        if (func_0204bcdc(&self->unk_136) != 0) {
            unsigned short local = 0x500c;
            matched = (func_0204bc64(&self->unk_136) == func_0204bc64(&local));
        } else {
            matched = (self->unk_136 == 0x500c);
        }
        if (matched) {
            level = 3;
        }
    }

final: {
    const Buf &buf = self->Fnb4();
    func_0206e9ec((void *) &buf, (const void *) level);
}
ret1:
    return 1;
ret0:
    return 0;
}

void Obj_ov009_022658dc::func_ov009_02263c14()
{
    func_02055124(&unk_13c);
    if (func_02056f94(static_cast<Obj_020dd184 *>(&unk_13c)) != 0) {
        vfunc_6c(0);
    } else {
        if (func_02056f28(static_cast<Obj_020dd184 *>(&unk_13c), 0x12) != 0) {
            func_ov009_02262ef0((void *) (&unk_238), 0x7d3);
        } else if (func_02056f28(static_cast<Obj_020dd184 *>(&unk_13c), 0x18) != 0) {
            func_ov009_02262ef0((void *) (&unk_238), 0x7d4);
        }
    }
}

extern "C" int func_ov009_02263ba8(Vtbl *obj)
{
    int ret = obj->f25();
    if (ret != 0) {
        func_02055060((char *) obj + 0x13c, ret, 1, 0x1000, 0, 0);
        if (func_0204bba8((char *) obj + 0x136) != 0) {
            func_ov009_02262ef0((char *) obj + 0x238, 0x806);
        } else {
            func_ov009_02262ef0((char *) obj + 0x238, 0x808);
        }
        return 1;
    }
    return 0;
}
