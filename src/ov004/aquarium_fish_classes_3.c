/* aquarium_fish_classes_3: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022389f4 @ 0x022389f4, 0x64 bytes, Thumb
 * func_ov004_0223896c @ 0x0223896c, 0x88 bytes, Thumb
 */

#include "types.h"

extern void func_02055dc8(void *, void *, void *);
extern int func_ov004_02239460(int, int);
extern void func_ov004_022354e0(void *);
extern void func_ov004_0223653c(char *arg0);
extern void func_ov004_02238804(void *self, int a, int b);
extern void func_ov004_02239768(void *self);
extern void func_ov004_022395d0(void *self, int a, int b);

void func_ov004_022389f4(char *self)
{
    int *p = (int *) (self + 0x15c);
    int r;
    *(u8 *) (self + 0x1e8) = (u8) *p;
    *(u8 *) (self + 0x1c7) = 0;
    if ((unsigned) (*p - 0x35) <= 1) {
        func_02055dc8(self + 0x64, (void *) &func_ov004_0223653c, self);
    }
    if (func_ov004_02239460(0, 2) > 0) {
        r = 1;
    } else {
        r = -1;
    }
    *(s16 *) (self + 0x1c0) = (s16) (r << 0xe);
    func_ov004_022354e0(self);
}

void func_ov004_0223896c(void *self)
{
    int v;
    int *p;

    v = *(int *) ((char *) self + 0x15c);
    if ((unsigned int) (v - 0x35) <= 1) {
        func_ov004_02238804(self, 2, 0x20);
    } else if (v == 0x34) {
        func_ov004_02238804(self, ~3, 0x26);
    }
    if (*((unsigned char *) self + 0x1ee) != 2 && *((unsigned char *) self + 0x1ee) != 6) {
        func_ov004_02239768(self);
        v = *(int *) ((char *) self + 0x15c);
        if ((unsigned int) (v - 0x35) <= 1) {
            func_ov004_022395d0(self, 0x924, 0x28a);
        } else if (v == 0x34) {
            func_ov004_022395d0(self, 0x71c, 0x28a);
        }
    }
    p = (int *) ((char *) self + 0x158);
    *p = *p + 1;
}
