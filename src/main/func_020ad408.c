/* func_020ad408 @ 0x020ad408, 0xf4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int FX_Div(int a, int b);     // 0x01ffc5a4
extern int FX_MulFunc(int a, int b); // 0x01ffcb0c
                                     // 0x021367a8

extern void func_020e96c8(void *a, int b, int c, int d);
extern void func_020e9838(void *a, int b, int c, int d);
extern void MTX_Concat43(void *a, void *b, void *c);
extern void func_020ad720(void *a, void *b);
extern u16 func_0206586c(void);  // 0x0206586c
extern int func_020655c4(int a); // 0x020655c4

extern void func_0209def4(u8 *p);

typedef union {
    u16 raw;
    struct {
        u16 f0 : 5;
        u16 f1 : 5;
        u16 f2 : 5;
        u16 pad : 1;
    } bits;
} UnkStruct_020ad408;

extern int data_021f47d0;
extern u8 data_020e4100;
extern u8 data_020e4104;
extern char data_021fbe48[];
extern char data_0213fee4[];
extern char data_021f486c[];
extern char data_021f4848[];

void func_020ad408(void)
{
    struct {
        u16 a;
        u8 b;
        u8 c;
        UnkStruct_020ad408 d;
    } l;
    int angle;
    u8 v;

    func_0209def4(&l.b);

    data_021f47d0 = FX_MulFunc((FX_Div((l.b + 60 * ((l.c + 6) % 12)) << 12, 0x2d0000) - 0x800) << 1, 0x1000);

    func_020e96c8(data_021fbe48, 0, 0, 0);
    func_020e9838(data_021fbe48, 0x20000, 0x20000, 0x20000);
    MTX_Concat43(data_021fbe48, data_0213fee4, data_021f486c);
    func_020ad720(data_021f486c, data_021f4848);

    l.a = func_0206586c();
    l.d.raw = l.a;

    angle = (u8) (FX_MulFunc(0x10000, FX_Div(((u8) (l.d.bits.f0 + l.d.bits.f1 + l.d.bits.f2)) << 12, 0x5d000)) >> 12);
    {
        int e = func_020655c4(0);
        v = (u8) (e + angle);
    }
    if (v > 31) {
        v = 31;
    }

    data_020e4104 = v;
    data_020e4100 = v;
}