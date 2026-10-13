/* func_ov119_0229ae84 @ 0x0229ae84, 0xe0 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0229ae84 {
    u8 pad_00[0x1e10];
    u16 A[16]; // 0x1e10
    u16 B[16]; // 0x1e30
    u16 C[16]; // 0x1e50
    u16 D[16]; // 0x1e70
};

extern void func_ov119_0229a410(struct UnkStruct_0229ae84 *s, int v);
extern void MIi_CpuCopy16(void *dst, const void *src, int len);
extern u16 func_ov119_0229af64(struct UnkStruct_0229ae84 *s, u16 a, u16 b, int n, int c);

void func_ov119_0229ae84(struct UnkStruct_0229ae84 *s, int n)
{
    int i;

    if (n < 0) {
        n = 0;
    } else if (n > 5) {
        n = 5;
    }

    func_ov119_0229a410(s, 0x20);

    MIi_CpuCopy16(s->A, s->C, 0x20); // copy C into A
    MIi_CpuCopy16(s->B, s->D, 0x20); // copy D into B

    for (i = 2; i <= 5; i++) {
        s->D[i] = func_ov119_0229af64(s, s->B[i], s->B[14], n, 5);
    }

    s->D[15] = func_ov119_0229af64(s, s->B[15], s->B[14], n, 5);

    for (i = 1; i <= 3; i++) {
        s->C[i] = func_ov119_0229af64(s, s->A[i], s->A[14], n, 5);
    }

    s->C[15] = func_ov119_0229af64(s, s->C[15], s->A[14], n, 5);
}
