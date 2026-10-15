/* func_ov068_02269684 @ 0x02269684, 0x148 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

class UnkStruct_02269684 {
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
struct UnkStruct_02269684_2 {
    int unk_00;
    int unk_04;
    int unk_08;
};
struct TE {
    u16 a;
    u8 b;
    u8 c;
};

extern "C" {
extern int func_02019de8(void *p);
extern int func_ov068_022697cc(void *self, UnkStruct_02269684 *obj, int c);
extern int func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern int func_020164a0(void *p, int a);
extern int func_020644cc(int a);
extern int func_020912d4(int a, Vec *v, s16 *ang, int d);
extern int func_0200442c(void *p, int a, int b, int c);
extern void func_ov068_0226cce8(void *self, UnkStruct_02269684 *obj, int c);
extern void func_0207d0f0(void *p, int a);
}

extern u16 data_020c80f8;
extern TE data_ov068_022767a4[];

extern "C" void func_ov068_02269684(u8 *self, UnkStruct_02269684 *obj)
{
    void *node = *(void **) (self + 0xe4);

    if (node != 0) {
        if (func_02019de8((char *) obj + 0x564) != 0) {
            if (func_ov068_022697cc(self, obj, 0x3000) != 0) {
                func_02019d0c((char *) obj + 0x564, 0xb, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
                self[0x1c] = 2;
                *(int *) (self + 0x20) = 0xc8;
            } else {
                void *n = *(void **) (self + 0xe4);
                UnkStruct_02269684_2 *q = (UnkStruct_02269684_2 *) ((char *) n + 0x5c);
                func_02019d0c((char *) obj + 0x564, 2, 1, q->unk_00, q->unk_08, 0, 0, 0, 0, data_020c80f8, 0);
                self[0x1c] = 1;
                *(int *) (self + 0x20) = 0xc8;
            }
        } else if (func_020164a0((char *) obj + 0x334, 0) == 0xdf) {
            if (((*(unsigned int *) ((char *) obj + 0x190) << 4) >> 16) == 9) {
                s16 ang;
                Vec v;
                TE *e;
                v.x = *(int *) ((char *) obj + 0x478);
                v.y = *(int *) ((char *) obj + 0x47c);
                v.z = *(int *) ((char *) obj + 0x480);
                ang = *(s16 *) ((char *) obj + 0x8e);
                e = &data_ov068_022767a4[func_020644cc(2)];
                func_020912d4(e->a, &v, &ang, 0);
                func_0200442c((char *) obj + 0x514, e->b + 0x84, 0x7f, 0);
            }
        }
    } else {
        func_ov068_0226cce8(self, obj, 0);
        *(int *) (self + 0xf4) = 0x4b0;
        if (obj->f25() != 0) {
            func_0207d0f0(obj->f25(), -1);
        }
    }
}
