/* flea_market_villager_6: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221ff70 @ 0x0221ff70, 0x54 bytes, Thumb
 * func_ov004_0221ff40 @ 0x0221ff40, 0x30 bytes, Thumb
 * func_ov004_0221febc @ 0x0221febc, 0x84 bytes, Thumb
 * func_ov004_0221fe84 @ 0x0221fe84, 0x38 bytes, Thumb
 */

#include "types.h"

extern void *func_020edf70(int size);
extern void *func_0202e8e4(void *p);
extern void *func_ov004_0221f860(void *p);
extern int data_ov004_02253bb4;
extern int func_0202e364(void *);
extern void func_0201c280(void *, void *);
extern void func_ov004_0221f800(void *, void *);
extern int func_0202e1fc(void *s);
extern void func_ov004_0223d33c(void);
extern void func_02013c0c(void *p);
extern int func_020b65b8(void);
extern int func_020b6654(int);
extern void func_ov004_0221fdf4(void *s, int a);
extern int func_02030864(int a);
extern int func_0201c444(void *s);
extern int func_0204d624(void *p, int a, int b);
extern int data_021fbe94;
extern int func_0202e1a0(void *);
extern void func_020e9898(int);

void *func_ov004_0221ff70(void)
{
    char *o = (char *) func_020edf70(0xa60);
    if (o != 0) {
        func_0202e8e4(o);
        *(int *) o = (int) &data_ov004_02253bb4;
        *(u16 *) (o + 0x898) = 0xfff1;
        *(int *) (o + 0x89c) = 0;
        *(int *) (o + 0x8a0) = 0;
        func_ov004_0221f860(o + 0x8a8);
    }
    return o;
}

int func_ov004_0221ff40(u8 *self)
{
    if (func_0202e364(self) == 0) {
        return 0;
    }
    func_0201c280(self, self + 0x8a8);
    func_ov004_0221f800(self + 0x8a8, self);
    return 1;
}

int func_ov004_0221febc(char *s)
{
    if (func_0202e1fc(s) == 0) {
        return 0;
    }
    func_ov004_0223d33c();
    *(u16 *) (s + 0x898) = 0xfff1;
    func_02013c0c(s + 0x558);
    if (func_020b6654((int) func_020b65b8()) != 0) {
        func_ov004_0221fdf4(s, 4);
    } else {
        func_ov004_0221fdf4(s, 0);
    }
    func_02030864(0);
    *(int *) (s + 0xa5c) = 0;
    *(int *) (s + 0xa58) = func_0204d624(s + 0xa5c, func_0201c444(s), data_021fbe94);
    return 1;
}

int func_ov004_0221fe84(char *self)
{
    // DECLS
    // ENDDECLS
    if (func_0202e1a0(self) == 0x0) {
        return 0x0;
    } else {
        if (*(int *) (self + 0xa58) != 0x0) {
            func_020e9898(*(int *) (self + 0xa58));
            *(void **) (self + 0xa58) = 0x0;
            *(void **) (self + 0xa5c) = 0x0;
        }
        return 0x1;
    }
}
