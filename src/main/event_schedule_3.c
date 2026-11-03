/* event_schedule_3: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204101c @ 0x0204101c, 0x40 bytes, Thumb
 * func_02040f8c @ 0x02040f8c, 0x8e bytes, Thumb
 * func_02040f04 @ 0x02040f04, 0x86 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int a;
    int b;
} Pair;

typedef struct UnkStruct_02040f04 {
    int a;
    int b;
} UnkStruct_02040f04;

extern void *func_020409c8(void *a, int b);
extern void func_020408d4(void *p);
extern int func_020ae3b8(void *p);
extern int func_020ae64c(void *);
extern int func_020ae67c(void *);
extern char data_021f3b30;
extern int func_02041110(void *p0, int *p1, int n);
extern int func_0204105c(void *p0, unsigned char *p3);
extern void func_0209e29c(void *buf, int n);
extern void func_020408b8(void *ptr, unsigned char byte, void *buf2);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int n);

void func_0204101c(void *arg)
{
    char *p = func_020409c8(arg, 1);
    int i;
    void *lock;

    for (i = 0; i < 5; i++) {
        func_020408d4(p);
        p += 6;
    }
    lock = &data_021f3b30;
    func_020ae64c((void *) func_020ae3b8(lock));
    func_020ae67c((void *) func_020ae3b8(lock));
}

void func_02040f8c(void *p0, int *p1, int *counter, unsigned char *p3, const void *p4)
{
    int i = 0;
    int local0 = 0;
    void *ptr;
    int local1 = 0;
    int idx;
    int val;
    Pair tmp1, tmp2;

    for (; i < 2; i++) {
        val = 0x63;
        if (*counter > 0) {
            idx = func_02041110(p0, p1, *counter);
            if (idx >= 0) {
                val = func_0204105c(p0, p3);
                p1[idx] = local0;
                (*counter)--;
            }
            ptr = func_020409c8(p0, idx + 1);
            if (ptr != 0) {
                tmp1.a = local1;
                tmp1.b = local1;
                MI_CpuCopy8(p4, &tmp1, 8);
                func_0209e29c(&tmp1, idx + 1);
                MI_CpuCopy8(&tmp1, &tmp2, 8);
                func_020408b8(ptr, (unsigned char) val, &tmp2);
            }
        }
        p3[5] = (unsigned char) val;
    }
}

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
                func_0209e29c((void *) (&s), idx + 1);
                MI_CpuCopy8(&s, &t, 8);
                func_020408b8(p, (u8) ((u8) st), (void *) (&t));
            }
        }
    }
}
