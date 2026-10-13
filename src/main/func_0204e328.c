/* func_0204e328 @ 0x0204e328, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0204f3e4(void *a, u32 *b, u32 *c, u32 *d, u32 *e, u16 *f, u16 *g, u32 h, int i);
extern void func_0204f800(int *a, int *b, u32 c, u32 d, u32 e, u32 f);
extern void func_0204f794(u32 a, int b, int c);
extern u16 *func_0204f5e0(void *a, int b, int c, int d, int e, int f);

void func_0204e328(u16 *out, void *arg, u32 p3, int *p4, int *p5, u16 a, u16 b, u32 c)
{
    u16 pair[2];
    u32 v[8];
    int p4_val, p5_val;
    int high4, high5, low4, low5;
    u16 *res;

    pair[0] = a;
    pair[1] = b;

    if (func_0204f3e4(arg, &v[2], &v[3], &v[0], &v[1], &pair[0], &pair[1], c, 0) != 0) {
        func_0204f800(p4, p5, v[2], v[3], v[0], v[1]);
        func_0204f794(p3, *p4, *p5);

        p4_val = *p4;
        p5_val = *p5;
        high4 = p4_val >> 4;
        high5 = p5_val >> 4;
        low5 = p5_val - (high5 << 4);
        low4 = p4_val - (high4 << 4);

        res = func_0204f5e0(arg, high4, high5, low4, low5, 0);
        if (res != 0) {
            *out = *res;
            return;
        }
    }
    *out = 0xfff1;
}