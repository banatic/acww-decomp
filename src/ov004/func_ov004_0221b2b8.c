/* func_ov004_0221b2b8 @ 0x0221b2b8, 0x9c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_0203ee14(void *s, void *q);
extern void func_020a8164(void *p, void *v);
extern unsigned int func_020712b0(void *g, u16 *k);
extern void *func_02094fd4(void *o);
extern int func_02070fe4(void *g, void *o, u16 *k);
extern void func_02068404(int h, int a, void *o);
extern void *func_02094fbc(void *o);
extern int data_ov004_022534cc;
extern int data_021f38f8;

int func_ov004_0221b2b8(char *s)
{
    u16 kk[2];
    char obj[0x20];
    char *q = s;
    void *g;
    if (s != 0) {
        q = q + 0xec;
    }
    func_0203ee14(s, q);
    func_020a8164(s + 0xec, &data_ov004_022534cc);
    kk[1] = 0x12e4;
    g = &data_021f38f8;
    if (func_020712b0(g, &kk[1]) <= 1) {
        func_02094fd4(obj);
        if (func_02070fe4(g, obj, &kk[1]) != 0) {
            *(u8 *) (s + 0x10a) = 3;
            func_02068404(*(int *) (s + 0x12c), 0, obj);
        }
        func_02094fbc(obj);
    } else {
        *(u8 *) (s + 0x10a) = 4;
    }
    *(int *) (*(int *) (s + 0x12c) + 8) = 1;
    *(u8 *) (s + 0x16c) = (u8) (*(u8 *) (s + 0x16c) + 1);
    return 1;
}
