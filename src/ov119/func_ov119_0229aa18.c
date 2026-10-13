/* func_ov119_0229aa18 @ 0x0229aa18, 0xb4 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_020984e8(void);
extern u32 func_02099870(void);
extern u32 func_ov119_0229bb44(u32);
extern void func_020641c8(void *);
extern u32 func_02095040(u32);
extern void func_02064210(u32, void *);
extern void func_020b496c(u32, void *);
extern void func_0207094c(u32, u32);
extern void func_02070adc(u32, u32, u32, u32, u32, u32, u32);
extern void func_02070a04(u32, u32, u32);
extern void func_02094fd4(void *);
extern void func_02095074(u32, void *);
extern void func_020a8bb8(u32, void *);
extern void func_02094fbc(void *);
extern void func_020641b0(void *);

void func_ov119_0229aa18(u32 p)
{
    u32 loc0[8];
    u32 loc1[8];
    u32 b;
    u32 a;

    func_020984e8();
    b = func_02099870();
    a = func_ov119_0229bb44(p);
    func_020641c8(loc0);
    func_02064210(func_02095040(b), loc0);
    func_020b496c(0, loc0);
    func_0207094c(a, 0x66);
    func_02070adc(a, 4, 0x102, 0xa, 0xf, 0, 0);
    func_02070a04(a, 0, 0);

    a = func_ov119_0229bb44(p);
    func_02094fd4(loc1);
    func_02095074(b, loc1);
    func_020a8bb8(a, loc1);
    func_02070adc(a, 4, 0x116, 8, 0xf, 0, 0);
    func_02070a04(a, 0, 0);

    func_02094fbc(loc1);
    func_020641b0(loc0);
}
