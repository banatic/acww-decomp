/* paged_choice_6: 5 functions, module ov002
 * mwccarm 1.2/base -O4,s
 * func_ov002_02209c08 @ 0x02209c08, 0x38 bytes, Thumb
 * func_ov002_02209bf0 @ 0x02209bf0, 0x18 bytes, Thumb
 * func_ov002_02209bd0 @ 0x02209bd0, 0x20 bytes, Thumb
 * func_ov002_02209b94 @ 0x02209b94, 0x3c bytes, Thumb
 * func_ov002_02209b6c @ 0x02209b6c, 0x28 bytes, Thumb
 */

#include "types.h"

struct _Obj {
    void *vtbl;
};

extern void *func_02070c2c(void *);
extern void *data_ov002_0220bba8;
extern void *func_02070ba4(void *);
extern void func_020edb3c(void *);
extern void func_02070adc(void *self, int a, int b, int c, int d, int e, int f);

void *func_ov002_02209c08(char *self)
{
    // DECLS
    // ENDDECLS
    func_02070c2c(self);
    *(void **) (self) = &data_ov002_0220bba8;
    *(u8 *) (self + 0x6e) = 0x3;
    *(u16 *) (self + 0x6c) = 0x0;
    *(u8 *) (self + 0x6f) = 0x1;
    *(u8 *) (self + 0x70) = 0x9;
    return self;
}

void *func_ov002_02209bf0(void *arg)
{
    *((void **) arg) = ((int *) &data_ov002_0220bba8);
    func_02070ba4(arg);
    return arg;
}

void *func_ov002_02209bd0(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov002_0220bba8);
    func_02070ba4(obj);
    func_020edb3c(obj);
    return obj;
}

void func_ov002_02209b94(char *self, int i)
{
    u8 a;

    a = *(u8 *) (self + 0x6f);
    if (i >= 0) {
        a = i & 0xf;
    }
    func_02070adc(self, *(u8 *) (self + 0x6e), *(u16 *) (self + 0x6c), 0xd, a, *(u8 *) (self + 0x70), 0);
}

void func_ov002_02209b6c(char *self, u8 a, u16 b, u8 c, u8 d)
{
    *(u8 *) (self + 0x6e) = a;
    *(u16 *) (self + 0x6c) = b;
    *(u8 *) (self + 0x6f) = c;
    *(u8 *) (self + 0x70) = d;
}
