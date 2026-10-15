/* func_ov094_0229a110 @ 0x0229a110, 0xb0 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020984e8(void);
extern int func_02099870(int a);
extern void *func_020641c8(void *a);
extern int func_02095040(int a);
extern void func_02064210(int a, void *b);
extern void *func_020b496c(int a, void *b);
extern void func_02070adc(void *p, u8 b, int c, int d, int e, int f, int g);
extern int func_0207094c(void *p, int a);
extern void func_02070a04(void *p, int a, int b);
extern void *func_02094fd4(void *a);
extern void *func_02095074(int a, void *b);
extern void *func_020a8bb8(void *p, void *b);
extern void *func_02094fbc(void *a);
extern void *func_020641b0(void *a);

void func_ov094_0229a110(void *self)
{
    char local1[0x20];
    char local2[0x20];
    int v;

    v = func_02099870(func_020984e8());
    func_020641c8(local1);
    func_02064210(func_02095040(v), local1);
    func_020b496c(0, local1);
    func_02070adc((char *) self + 0xe0, ((u8 *) self)[0xe], 17, 10, 15, 12, 0);
    func_0207094c((char *) self + 0xe0, 102);
    func_02070a04((char *) self + 0xe0, 1, 0);
    func_02094fd4(local2);
    func_02095074(v, local2);
    func_02070adc((char *) self + 0x14c, ((u8 *) self)[0xe], 37, 8, 15, 12, 0);
    func_020a8bb8((char *) self + 0x14c, local2);
    func_02070a04((char *) self + 0x14c, 1, 0);
    func_02094fbc(local2);
    func_020641b0(local1);
}
