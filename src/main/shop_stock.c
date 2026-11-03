/* shop_stock: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b0164 @ 0x020b0164, 0x78 bytes, Thumb
 * func_020b00fc @ 0x020b00fc, 0x68 bytes, Thumb
 * func_020b00c8 @ 0x020b00c8, 0x34 bytes, Thumb
 * func_020b00a8 @ 0x020b00a8, 0x1e bytes, Thumb
 * func_020b0074 @ 0x020b0074, 0x32 bytes, Thumb
 * func_020b0038 @ 0x020b0038, 0x3c bytes, Thumb
 * func_020aff84 @ 0x020aff84, 0xb4 bytes, Thumb
 */

#include "types.h"

extern void func_02063ccc(void *buf, int a, int b);
extern int func_020638b0(void *a, unsigned int b, void *c, int d, void *e, int f, int g, int h);
extern void func_02063cc8(void *buf);
extern void func_02061b1c(void *out, void *src, int n);
extern char data_021f4a80[];
extern int func_020637d0(unsigned short *, unsigned int, int, int, int, int, int, int, int);
extern unsigned int data_021f49f0;
extern unsigned int data_021f49f4;
extern int func_0204bcdc(void *ptr);
extern int func_0204bc64(void *ptr);

void func_020b0164(char *base, int *index_ptr, int p2, int p3, unsigned int count, int p5, unsigned char flag)
{
    if (count == 0) {
        return;
    }
    {
        int off;
        unsigned short buffer2;
        unsigned int buffer[3];
        unsigned int i;

        func_02063ccc(buffer, p2, p3);
        func_020638b0(base + 2 * (*index_ptr), count, buffer, 0, &data_021f4a80, 0, 1, 0);
        func_02063cc8(buffer);
        if (flag != 0) {
            for (i = 0; i < count; i++) {
                off = (i + *index_ptr) * 2;
                func_02061b1c(&buffer2, base + off, 1);
                *(unsigned short *) (base + off) = buffer2;
            }
        }
        *index_ptr += count;
    }
}

void func_020b00fc(unsigned short *p0, int *index_ptr, int param2, int param3, unsigned int count, unsigned int unused,
                   unsigned char flag)
{
    if (count == 0) {
        return;
    }

    func_020637d0(p0 + *index_ptr, count, param2, param3, 0, 0, 10, (unsigned int) ((unsigned char *) data_021f4a80), 0);

    if (flag != 0) {
        unsigned int off;
        unsigned int i;
        unsigned short tmp;

        for (i = 0; i < count; i++) {
            off = (i + *index_ptr) * 2;
            func_02061b1c((void *) (&tmp), (void *) ((unsigned short *) ((char *) p0 + off)), 1);
            *(unsigned short *) ((char *) p0 + off) = tmp;
        }
    }

    *index_ptr += count;
}

void func_020b00c8(unsigned short *r0, unsigned char *r1, unsigned int r2)
{
    unsigned int r5;
    unsigned int r3;
    unsigned int r4;
    unsigned int r0_temp;

    r5 = 0;
    r4 = 0x0000fff1;
    while (r5 < r2) {
        r0[r5] = (unsigned short) r4;
        r5++;
    }
    r3 = (r2 >> 3) + 1;
    r2 = 0;
    r0_temp = r2;
    while (r2 < r3) {
        r1[r2] = (unsigned char) r0_temp;
        r2++;
    }
}

int func_020b00a8(unsigned int a, unsigned int b, unsigned char *c)
{
    if (a < b) {
        if ((c[a >> 3] >> (a & 7)) & 1) {
            return 1;
        }
        return 0;
    }
    return 1;
}

int func_020b0074(unsigned int a, unsigned int b, unsigned char *arr)
{
    if (a < b && func_020b00a8(a, b, arr) == 0) {
        arr[a >> 3] |= (1 << (a & 7));
        return 1;
    }
    return 0;
}

void *func_020b0038(unsigned int idx, unsigned short *base, unsigned int x, unsigned int count, unsigned short *out)
{
    unsigned short *p;

    if (idx < count) {
        p = base + idx;
        if (out) {
            *out = *p;
        }
        if (func_020b00a8(idx, count, (unsigned char *) x)) {
            return &data_021f49f4;
        } else {
            return p;
        }
    } else {
        return &data_021f49f0;
    }
}

static __inline int EqA(void *a, void *b)
{
    if (func_0204bc64(a) == func_0204bc64(b)) {
        return 1;
    }
    return 0;
}

static __inline int EqB(u16 a, u16 b)
{
    if (a == b) {
        return 1;
    }
    return 0;
}

int func_020aff84(void *p0, int p1, int p2, unsigned int p3)
{
    unsigned int i;
    void *ptr;
    int cond;
    int cond2;

    for (i = 0; i < p3; i++) {
        ptr = (void *) func_020b0038(i, (unsigned short *) p1, p2, p3, 0);

        if (func_0204bcdc(ptr)) {
            cond = EqA(ptr, p0);
        } else {
            cond = EqB(*(u16 *) ptr, *(u16 *) p0);
        }

        if (cond) {
            if (func_0204bcdc(p0)) {
                cond2 = EqA(p0, ((u16 *) &data_021f49f4));
            } else {
                cond2 = EqB(*(u16 *) p0, (*(u16 *) &data_021f49f4));
            }
            if (cond2 == 0) {
                return i;
            }
        }
    }
    return -1;
}
