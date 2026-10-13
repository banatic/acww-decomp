/* func_0204e204 @ 0x0204e204, 0x124 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

// The accumulator is updated in three separate statements.

typedef struct {
    int unk_00, unk_04, unk_08;
} UnkStruct_0204e204;
typedef struct {
    u16 a, b;
} UnkStruct_0204e204_2;

extern void func_0204e328(u16 *out, void *arg, UnkStruct_0204e204 *p3, int *p4, int *p5, u16 a, u16 b, u32 c);
extern int func_0204bcdc(void *s);
extern int func_0204bc64(void *p);
extern void *func_020b3b50(void *s);
extern u32 func_020b3d90(void *h);
extern int func_020b3d04(void *h, UnkStruct_0204e204 *a, UnkStruct_0204e204 *b, UnkStruct_0204e204 *c, u32 i);
extern int FX_Div(int a, int b);
extern int func_020310c8(int a);

void func_0204e204(u16 *out, void *arg, int *dst, int *o4, int *o5, u16 a, u16 b, u32 c)
{
    UnkStruct_0204e204_2 s;
    int p4v, p5v;
    UnkStruct_0204e204 vec, A, B, C;
    void *h;
    u32 n, i;
    int sx, sy;
    int result;
    int qx, t, u, d;

    func_0204e328((u16 *) &s, arg, &vec, &p4v, &p5v, a, b, c);
    if (func_0204bcdc(&s)) {
        s.b = 0xfff1;
        result = (func_0204bc64(&s) == func_0204bc64(&s.b));
    } else {
        result = (s.a == 0xfff1);
    }
    if (result) {
        goto fail;
    }
    h = func_020b3b50(&s);
    if (h == 0) {
        goto fail;
    }
    n = func_020b3d90(h);
    sx = 0;
    sy = 0;
    i = 0;
    while (i < n) {
        if (func_020b3d04(h, &A, &B, &C, i)) {
            sx = sx + A.unk_00;
            sx = sx + B.unk_00;
            sx = sx + C.unk_00;
            sy = sy + A.unk_08;
            sy = sy + B.unk_08;
            sy = sy + C.unk_08;
        }
        i++;
    }
    d = (3 * func_020b3d90(h)) << 12;
    qx = FX_Div(sx, d);
    t = vec.unk_08 + FX_Div(sy, d) + 0x1000;
    u = func_020310c8(0);
    dst[0] = vec.unk_00 + qx;
    dst[1] = u;
    dst[2] = t;
    if (o4 != 0) {
        *o4 = p4v;
    }
    if (o5 != 0) {
        *o5 = p5v;
    }
    *out = s.a;
    return;
fail:
    *out = 0xfff1;
}
