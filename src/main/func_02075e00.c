/* func_02075e00 @ 0x02075e00, 0x13c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_020ccf94;
extern void func_02073044(void);
extern int func_020ebf70(void);
extern void func_02137550(void *p, int n);
extern u8 *func_02073d28(void *h, int n);
extern void func_02077b3c(u8 *p, int a, int b);
extern void *func_02090040(int x);
extern void MI_CpuCopy8(const void *s, void *d, int n);
extern int func_02077a8c(int mask);
extern int func_02073e30(void *h, u8 *p0, int n0, int t0, u8 *p1, int n1, int t1, u8 *p2, int n2, int t2);

int func_02075e00(int k0, int b0, int k1, int b1, int k2, int b2)
{
    unsigned int i;
    int kind;
    void *h;
    u8 *p;
    u16 tag[3];
    int A[3];
    int B[3];
    u8 *C[3];
    int D[3];

    func_02073044();
    if (func_020ebf70() == 0) {
        goto fail;
    }
    A[0] = k0;
    A[1] = k1;
    A[2] = k2;
    B[0] = b0;
    B[1] = b1;
    B[2] = b2;
    func_02137550(C, 0xc);
    func_02137550(D, 0xc);
    func_02137550(tag, 6);
    i = 0;
    h = data_020ccf94;
    for (; i < 3; i++) {
        kind = A[i];
        if (kind == 3) {
            continue;
        }
        C[i] = func_02073d28(h, i + 1);
        p = C[i];
        func_02077b3c(p, 0, 3);
        D[i] = D[i] + 1;
        if (kind == 0) {
            p[1] = 0;
            D[i] = D[i] + 1;
        } else if (kind == 1) {
            p[1] = 1;
            D[i] = D[i] + 1;
        } else {
            MI_CpuCopy8(func_02090040(B[i]), p + 1, 0x950);
            D[i] = D[i] + 0x950;
        }
        tag[i] = (u16) (1 << (i + 1));
    }
    if (k0 == 3 && k1 == 3 && k2 == 3) {
        goto ret1;
    }
    if (func_02077a8c((u16) (tag[2] | (tag[0] | tag[1]))) == 0) {
        goto ret0;
    }
    return func_02073e30(h, C[0], D[0], tag[0], C[1], D[1], tag[1], C[2], D[2], tag[2]);
ret0:
    return 0;
ret1:
    return 1;
fail:
    return 0;
}
