/* func_0209987c @ 0x0209987c, 0x1ac bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef struct {
    u16 v;
} UnkStruct_0209987c;

extern void func_02095158(void *p, int a, int b, int c, int d);
extern void func_02099834(void *self, int a);
extern void func_02099808(void *self, int a);
extern void func_020997e0(void *self, int a);
extern void func_020997b4(void *self, int a);
extern void func_02099768(void *self, int a);
extern void func_02099740(void *self, int a);
extern void func_02098f80(void *p);
extern void func_02098aa0(void *p, int a, int b);
extern void func_02072c50(void *self, void *p);
extern void func_020adf54(void *p);
extern void func_0203cf38(void *p);
extern void func_02097dd4(void *p);
extern void func_02097dac(void *p);
extern void func_02077be8(void *p);
extern void func_02077d04(void *p);
extern void func_02099794(void *self, UnkStruct_0209987c w);
extern void func_020992c4(void *self);
extern void func_02088c08(void *p);
extern int func_02088754(void *p);
extern void func_020983f4(void *p);
extern void func_0203fa84(void *p);
extern void *func_02099308(void *self);
extern void func_0209df64(void *p);
extern void MI_CpuFill8(void *p, int v, int n);

void func_0209987c(u8 *self, int a1, int a2, int a3, int a5, u8 a6, u8 a7, u8 a8, u8 a9, u8 a10, int a11, u16 *a12)
{
    UnkStruct_0209987c w;

    func_02095158(self + 0x247e, a1, a2, a3, a5);
    func_02099834(self, a6);
    func_02099808(self, a7);
    func_020997e0(self, a8);
    func_020997b4(self, a9);
    func_02099768(self, 0);
    func_02099740(self, a10);
    func_02098f80(self + 0x11a8);
    func_02098aa0(self + 0x11a8, a11, 1);
    *(u16 *) (self + 0x2406) = *a12;
    func_02072c50(self, self + 0x247e);
    func_020adf54(self + 0x2404);
    func_0203cf38(self + 0x1c18);
    func_02097dd4(self + 0x1d3c);
    func_02097dac(self + 0x243e);
    func_02077be8(self + 0x1f0c);
    func_02077d04(self + 0x1f5c);
    *(u16 *) (self + 0x240e) = 0x3884;
    w.v = (w.v & ~0x7f) | 0;
    w.v = (w.v & 0xfffff87f) | 0x80;
    w.v = (w.v & 0xffff07ff) | 0x800;
    func_02099794(self, w);
    func_020992c4(self);
    *(u16 *) (self + 0x2408) = 0x11a8;
    func_02088c08(self + 0x2416);
    *(u16 *) (self + 0x240c) = 0xfff1;
    *(u16 *) (self + 0x240a) = 0xfff1;
    *(u16 *) (self + 0x2410) = 0x11fa;
    func_02088754(self + 0x2427);
    func_020983f4(self + 0x23e0);
    func_0203fa84(self + 0x23e8);
    func_0209df64(func_02099308(self));
    MI_CpuFill8(self + 0x2454, 0xff, 8);
}
