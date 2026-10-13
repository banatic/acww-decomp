/* func_ov068_0226b4f8 @ 0x0226b4f8, 0x148 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

class UnkStruct_0226b4f8 {
  public:
    virtual void f00();
    virtual void f01();
    virtual void f02();
    virtual void f03();
    virtual void f04();
    virtual void f05();
    virtual void f06();
    virtual void f07();
    virtual void f08();
    virtual void f09();
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
    virtual void *f25();
};

struct Vec {
    int x, y, z;
};

extern "C" {
extern int func_0207f1d8(void *p);
extern int func_0207d578(void *p, int a);
extern void *func_0207f270(void *p);
extern void func_020794d4(void *p, int a);
extern int func_020644cc(int a);
extern int func_ov068_0226ca74(void *self, UnkStruct_0226b4f8 *obj);
extern void *func_02096190(int a);
extern int func_0201c350(UnkStruct_0226b4f8 *obj, void *p, int c);
extern void func_020139bc(void *p);
extern void func_ov068_0226cce8(void *self, UnkStruct_0226b4f8 *obj, int c);
extern u8 *func_020800d0(void *p);
extern void func_02079540(void *p, int a);
extern void func_0204f794(void *p, int a, int b);
extern void func_0202e118(u16 *out, UnkStruct_0226b4f8 *obj);
extern void func_ov068_0226d5f4(UnkStruct_0226b4f8 *obj);
extern void func_0207d1f8(void *p, int a);
}

extern "C" void func_ov068_0226b4f8(u8 *self, UnkStruct_0226b4f8 *obj)
{
    void *p = obj->f25();
    int flag = 0;

    *((u8 *) obj + 0x561) = 0;

    if (func_0207f1d8(p) == 2) {
        if (func_0207d578(p, 0) == 0) {
            if (func_0207f270(p) != 0) {
                func_020794d4(func_0207f270(p), 0);
                *(int *) (self + 0x20) = func_020644cc(0x28) + 0x258;
            }
            flag = 1;
        }
    } else {
        if (*(int *) (self + 0x20) == 0) {
            flag = 1;
        }
    }

    if (flag != 0) {
        if (func_ov068_0226ca74(self, obj) != 0) {
            void *q = func_02096190(4);
            if (func_0201c350(obj, q, 0x6000) == 0) {
                func_020139bc(self + 0x3c);
                func_ov068_0226cce8(self, obj, 4);
            }
        } else {
            void *a = func_0207f270(p);
            u8 *b = func_020800d0(p);
            u16 tmp;
            func_02079540(a, 1);
            func_020794d4(a, 0);
            func_0204f794((char *) obj + 0x5c, b[0], b[1] + 1);
            {
                Vec *s = (Vec *) ((char *) obj + 0x5c);
                Vec *d = (Vec *) ((char *) obj + 0x68);
                d->x = s->x;
                d->y = s->y;
                d->z = s->z;
            }
            func_020139bc(self + 0x3c);
            func_ov068_0226cce8(self, obj, 0);
            func_0202e118(&tmp, obj);
            if (tmp != 0xfff1) {
                func_ov068_0226d5f4(obj);
            }
        }
    } else {
        if (*(int *) (self + 0xf8) == 0) {
            if (obj->f25() != 0) {
                func_0207d1f8(obj->f25(), 0);
            }
            *(int *) (self + 0xf8) = 0x384;
        }
    }
}
