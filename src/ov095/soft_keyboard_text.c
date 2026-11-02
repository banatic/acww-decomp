/* soft_keyboard_text: 11 functions, module ov095
 * mwccarm 1.2/base -O4,s
 * func_ov095_0229be18 @ 0x0229be18, 0xa4 bytes, Thumb
 * func_ov095_0229bdd4 @ 0x0229bdd4, 0x42 bytes, Thumb
 * func_ov095_0229bd40 @ 0x0229bd40, 0x94 bytes, Thumb
 * func_ov095_0229bcec @ 0x0229bcec, 0x54 bytes, Thumb
 * func_ov095_0229bc00 @ 0x0229bc00, 0xec bytes, Thumb
 * func_ov095_0229bbc0 @ 0x0229bbc0, 0x40 bytes, Thumb
 * func_ov095_0229bba0 @ 0x0229bba0, 0x20 bytes, Thumb
 * func_ov095_0229bb9c @ 0x0229bb9c, 0x4 bytes, Thumb
 * func_ov095_0229bb98 @ 0x0229bb98, 0x4 bytes, Thumb
 * func_ov095_0229bb94 @ 0x0229bb94, 0x4 bytes, Thumb
 * func_ov095_0229bb34 @ 0x0229bb34, 0x5e bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229bd40 {
    unsigned char pad_00[0x10];
    unsigned short unk_10;
    unsigned short unk_12;
};

extern int func_ov095_022999b0(void *a, int b);
extern void func_ov095_022999a8(void *a, int b);
extern int func_02051c8c_unk(void *a, int b);
extern int func_02051d08(void *a, int b);
extern int func_02051d30(void *a);
extern int func_ov095_0229b784(void *a, int b);
extern int func_ov095_0229b9e0(void *a, int b);
extern void func_ov095_0229b400(void *a, int b, int c);
extern void func_ov095_0229b3ec(void *a);
extern void func_ov095_022999c0(int a, int b);
extern void func_ov095_022999a0(int a, int b);
extern void *data_021fbe94;
extern void *func_020e9958(void *p, int size);
extern void func_020e993c(void *p, void *handle);
extern void func_02051c08(void *a, void *b, u32 c);
extern int func_0206de88(void *handle, void *out1, void *out2, u32 a4, u32 a5, u32 a7, u32 a6);
extern int func_02051c14(const unsigned short *a, int b, int c, int *d, int e);

int func_ov095_0229be18(void *a0, unsigned short *a1, void *a2, int a3, int a4, int a5)
{
    if (a4 == a3) {
        if (func_ov095_022999b0(a0, 0x100) == 0) {
            func_ov095_022999a8(a0, 0x40);
        }
        return 0;
    } else {
        int res;
        int r1;
        int r2;

        res = func_02051c8c_unk(a1, a4);
        if (res == a4 && a1[res - 1] != 0x3000) {
            if (func_ov095_022999b0(a0, 0x100) == 0) {
                func_ov095_022999a8(a0, 0x40);
            }
            return 0;
        }
        if (a5 < 0) {
            return 1;
        }
        r1 = func_02051d08(a1, a4);
        r2 = func_02051d30(a2);
        if (r1 + r2 > a5) {
            if (func_ov095_022999b0(a0, 0x100) == 0) {
                func_ov095_022999a8(a0, 0x80);
            }
            return 0;
        }
        return 1;
    }
}

int func_ov095_0229bdd4(int a0, unsigned short *a1, unsigned short a2, int a3, int a4, int a5)
{
    int i;
    if (!func_ov095_0229be18((void *) a0, a1, (void *) a2, a3, a4, a5)) {
        return 0;
    }
    i = a4 - 1;
    while (i > a3) {
        a1[i] = a1[i - 1];
        i--;
    }
    a1[a3] = a2;
    return 1;
}

int func_ov095_0229bd40(struct UnkStruct_0229bd40 *a0, unsigned short *a1, int a2, unsigned char *a3, int a4, int a5, int a6)
{
    int ret = func_ov095_0229b784(a0, a2);
    int tmp = *a3;
    if (ret == 0 || ret == 2) {
        if (func_ov095_0229bdd4((int) a0, (unsigned short *) a1, a0->unk_12, tmp, a4, -1) != 0) {
            (*a3)++;
        } else {
            return 0;
        }
    }
    if (ret == 1 || ret == 2) {
        a1[tmp - 1] = a0->unk_10;
    }
    if (a5 == 0) {
        if (func_ov095_0229b9e0(a0, a2) != 0) {
            func_ov095_0229b400(a0, a2, ret);
        } else {
            func_ov095_0229b3ec(a0);
        }
        if (a6 != 0) {
            func_ov095_022999c0((int) a0, a2);
        }
    }
    return 1;
}

int func_ov095_0229bcec(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7)
{
    if (p6) {
        func_ov095_022999a8((void *) p0, 0x100);
    } else {
        func_ov095_022999a0(p0, 0x40);
        func_ov095_022999a0(p0, 0x80);
        func_ov095_022999a0(p0, 0x100);
    }
    return func_ov095_0229bd40((struct UnkStruct_0229bd40 *) p0, (unsigned short *) p1, p2, (unsigned char *) p3, p4, p6, p7);
}

int func_ov095_0229bc00(u32 a0, u16 *a1, u32 a2, u8 *a3, u32 a4, u32 a5, u32 a6, u32 a7, u32 a8, u32 a9)
{
    u32 a2_save = a2;
    u8 *a3_save = a3;
    void *p = data_021fbe94;
    void *handle;
    u8 byte;
    u32 buf2[1]; // 4 bytes
    u32 buf1[8]; // 32 bytes

    handle = func_020e9958(p, 0xC0);
    if (handle == 0) {
        return 0;
    }

    func_02051c08(a1, handle, a4);

    byte = *a3_save;

    if (!func_ov095_0229bcec(a0, (int) handle, a2_save, (int) (&byte), a4, 0x2710, a8, 0)) {
        func_020e993c(p, handle);
        return 0;
    }

    if (!func_0206de88(handle, buf1, buf2, a4, a5, a7, a6)) {
        func_020e993c(p, handle);
        if (func_ov095_022999b0((void *) a0, 0x100) == 0) {
            func_ov095_022999a8((void *) a0, 0x80);
        }
        return 0;
    }

    if (a8 == 0) {
        func_02051c08(handle, a1, a4);
        *a3_save = byte;
        if (a9 == 1 && byte != 0) {
            func_ov095_022999c0(a0, a1[byte - 1]);
        }
    }

    func_020e993c(p, handle);
    return 1;
}

int func_ov095_0229bbc0(int unused, unsigned short *arr, int a, int b, int n)
{
    int i, j, lo, hi;
    if (a > b) {
        lo = b;
        hi = a;
    } else {
        lo = a;
        hi = b;
    }
    for (i = 0; i + hi < n; i++) {
        arr[i + lo] = arr[i + hi];
    }
    hi -= lo;
    for (j = 1; j <= hi; j++) {
        arr[n - j] = 0;
    }
    return lo;
}

int func_ov095_0229bba0(int a, unsigned short *b, int c, int d)
{
    if (d == 0) {
        return 0;
    }
    b[d - 1] = c;
    func_ov095_022999c0(a, c);
    return 1;
}

int func_ov095_0229bb9c(void *receiver, int value)
{
    return 0;
}

int func_ov095_0229bb98(void *receiver, int value)
{
    return 0;
}

int func_ov095_0229bb94(void *receiver, int value)
{
    return 0;
}

unsigned char func_ov095_0229bb34(int unused, const unsigned short *arr, int p3, int p4, unsigned char threshold,
                                  unsigned char *dst)
{
    int count;
    int i;
    int sum;
    int lim;
    func_02051c14(arr, p3, p4, &count, 0);
    sum = 0;
    i = 0;
    lim = threshold;
    while (i < count) {
        int v = func_02051d30((void *) arr[i]);
        if (sum + (v >> 1) > lim) {
            if (dst != 0) {
                *dst = (unsigned char) i;
            }
            return (unsigned char) sum;
        }
        sum += v;
        i++;
    }
    if (dst != 0) {
        *dst = (unsigned char) count;
    }
    return (unsigned char) sum;
}
