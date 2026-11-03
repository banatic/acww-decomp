/* tti_npc: 7 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02225b60 @ 0x02225b60, 0x44 bytes, Thumb
 * func_ov004_02225b14 @ 0x02225b14, 0x4c bytes, Thumb
 * func_ov004_02225ae4 @ 0x02225ae4, 0x30 bytes, Thumb
 * func_ov004_02225a60 @ 0x02225a60, 0x84 bytes, Thumb
 * func_ov004_02225a14 @ 0x02225a14, 0x4c bytes, Thumb
 * func_ov004_022259f4 @ 0x022259f4, 0x20 bytes, Thumb
 * func_ov004_022259dc @ 0x022259dc, 0x18 bytes, Thumb
 */

#include "types.h"

struct _Obj {
    void *vtbl;
};

extern int func_02019d0c(void *, int, int, int, int, int, int, int, int, int, int);
extern void *data_020c80f8;
extern int func_020e8858(void *p);
extern int func_020a186c(void);
extern void func_ov004_02225ba4(void *self, int k);
extern int func_02019c20(void *, int, int, int, int, int);
extern int func_02016884(void *, int, void *);
extern int func_02019de8(void *);
extern char *data_ov004_02258200;
extern void *func_0202ee5c(void *);
extern void func_020edf54(void *);
extern char data_ov004_02254a38;

int func_ov004_02225b60(char *self)
{
    // DECLS
    // ENDDECLS
    func_02019d0c(self + 0x564, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, *(u16 *) ((char *) &data_020c80f8), 0x0);
    *(u8 *) (self + 0x658) = 0xa;
    return 0x1;
}

int func_ov004_02225b14(void *self)
{
    unsigned int a, b;

    a = ((unsigned int) *(int *) ((char *) self + 0x190) << 4) >> 16;
    b = ((unsigned int) *(int *) ((char *) self + 0x18c) << 4) >> 16;
    if (a == b - 1 && func_020e8858((char *) self + 0x658) == 0 && func_020a186c() != 0) {
        func_ov004_02225ba4(self, 1);
    }
    return 1;
}

int func_ov004_02225ae4(char *self)
{
    // DECLS
    // ENDDECLS
    func_02019c20(self + 0x564, 0x1, 0x100, 0x1, *(u16 *) ((char *) &data_020c80f8), 0x0);
    return 0x1;
}

int func_ov004_02225a60(char *self)
{
    // DECLS
    // ENDDECLS
    if (func_02016884(self + 0x334, 0x100, self + 0x2a0) != 0x0 && func_02019de8(self + 0x564) != 0x0) {
        func_02019c20(self + 0x564, 0x1, 0x101, 0x1, *(u16 *) ((char *) &data_020c80f8), 0x0);
    }
    if (func_02016884(self + 0x334, 0x101, self + 0x2a0) != 0x0 && func_02019de8(self + 0x564) != 0x0) {
        func_ov004_02225ba4(self, 0x0);
    }
    return 0x1;
}

int func_ov004_02225a14(void)
{
    char *p = data_ov004_02258200;

    if (p != 0) {
        if (func_02016884(p + 0x334, 0xff, p + 0x2a0) != 0) {
            if (*(int *) (data_ov004_02258200 + 0x654) == 0) {
                return 1;
            }
        }
        return 0;
    }
    return 1;
}

void *func_ov004_022259f4(struct _Obj *obj)
{
    obj->vtbl = &data_ov004_02254a38;
    func_0202ee5c(obj);
    func_020edf54(obj);
    return obj;
}

void *func_ov004_022259dc(void *arg)
{
    *((void **) arg) = ((int *) &data_ov004_02254a38);
    func_0202ee5c(arg);
    return arg;
}
