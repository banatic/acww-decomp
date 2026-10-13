/* func_ov004_0221041c @ 0x0221041c, 0x210 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_ov004_0220ffa4(char *);
extern void *func_ov004_0220e220(void *);
extern void *func_ov004_0220d9ec(void *, int);
extern void *func_ov004_0220d9e0(void *, int);
extern void *func_ov004_0220da04(void *, int);
extern void *func_ov004_0220d9d4(void *, int);
extern void *func_ov004_0220d9f8(void *, int);
extern void *func_ov004_0220e050(void *);
extern int func_0209d324(void *);
extern int func_020564d0(void *, void *, int);
extern int func_0205650c(void *, void *, int);
extern int func_02055140(void *, int);
extern void func_02056478(void *, void *, u8, int, u16);
extern void func_02056424(void *, void *, void *, u8, int, u16);
extern void func_02055060(void *, void *, int, int, u16, u16);
extern void func_02055050(void *);
extern void *func_02055e00(void *);
extern void func_020563dc(void *, void *);
void func_ov004_0221041c(char *self, int selector, u8 mode, int speed, u16 frame)
{
    void *context = func_ov004_0220ffa4(self);
    int slot = selector & 1;
    if (func_ov004_0220d9ec(func_ov004_0220e220(self + 0x6cc), slot)) {
        void *resource = *(void **) (self + 0x594);
        if (func_020564d0(self + 0x824, resource, func_0209d324(context))) {
            func_02056478(self + 0x824, func_ov004_0220d9ec(func_ov004_0220e220(self + 0x6cc), slot), mode, speed, frame);
            func_020563dc(self + 0x824, func_02055e00(self + 0x538));
        }
    }
    if (func_ov004_0220d9f8(func_ov004_0220e220(self + 0x6cc), slot)) {
        void *resource = *(void **) (self + 0x594);
        if (func_0205650c(self + 0x7c4, resource, func_0209d324(context))) {
            func_02056478(self + 0x7c4, func_ov004_0220d9f8(func_ov004_0220e220(self + 0x6cc), slot), mode, speed, frame);
            func_020563dc(self + 0x7c4, func_02055e00(self + 0x538));
        }
    }
    if (func_ov004_0220d9e0(func_ov004_0220e220(self + 0x6cc), slot)) {
        void *resource = *(void **) (self + 0x594);
        if (func_0205650c(self + 0x7e4, resource, func_0209d324(context))) {
            func_02056478(self + 0x7e4, func_ov004_0220d9e0(func_ov004_0220e220(self + 0x6cc), slot), mode, speed, frame);
            func_020563dc(self + 0x7e4, func_02055e00(self + 0x538));
        }
    }
    if (func_ov004_0220d9d4(func_ov004_0220e220(self + 0x6cc), slot)) {
        void *resource = *(void **) (self + 0x594);
        if (func_0205650c(self + 0x804, resource, func_0209d324(context))) {
            void *res = func_ov004_0220d9d4(func_ov004_0220e220(self + 0x6cc), slot);
            func_02056424(self + 0x804, res, func_ov004_0220e050(self + 0x6cc), mode, speed, frame);
            func_020563dc(self + 0x804, func_02055e00(self + 0x538));
        }
    }
    if (func_ov004_0220da04(func_ov004_0220e220(self + 0x6cc), slot)) {
        if (func_02055140(self + 0x538, func_0209d324(context))) {
            func_02055060(self + 0x538, func_ov004_0220da04(func_ov004_0220e220(self + 0x6cc), slot), mode, speed, frame, 0);
            func_02055050(self + 0x538);
        }
    }
}
