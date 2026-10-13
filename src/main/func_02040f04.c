/* func_02040f04 @ 0x02040f04, 0x86 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02040f04 {
    int a;
    int b;
} UnkStruct_02040f04;

extern int func_02041110(void *a, int *arr, int n);
extern void *func_020409c8(void *a, int i);
extern void MI_CpuCopy8(const void *src, void *dst, int n);
extern void func_0209e29c(UnkStruct_02040f04 *s, int i);
extern void func_020408b8(void *p, u8 st, UnkStruct_02040f04 *t);

void func_02040f04(void *a, int *arr, int *count, UnkStruct_02040f04 *d)
{
    int st;
    int zeroA = 0;
    void *p;
    int zeroB = 0;
    UnkStruct_02040f04 s;
    UnkStruct_02040f04 t;
    int i;
    int idx;

    for (i = 0; i < 2; i++) {
        st = 0x63;
        if (*count > 0) {
            idx = func_02041110(a, arr, *count);
            if (idx >= 0) {
                st = 0x45;
                arr[idx] = zeroA;
                *count = *count - 1;
            }
            p = func_020409c8(a, idx + 1);
            if (p != 0) {
                s.a = zeroB;
                s.b = zeroB;
                MI_CpuCopy8(d, &s, 8);
                func_0209e29c(&s, idx + 1);
                MI_CpuCopy8(&s, &t, 8);
                func_020408b8(p, (u8) st, &t);
            }
        }
    }
}
