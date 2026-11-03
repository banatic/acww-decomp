/* town_layout_2: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204ead0 @ 0x0204ead0, 0x4c bytes, Thumb
 * func_0204ea98 @ 0x0204ea98, 0x38 bytes, Thumb
 * func_0204ea40 @ 0x0204ea40, 0x58 bytes, Thumb
 * func_0204ea00 @ 0x0204ea00, 0x3e bytes, Thumb
 * func_0204e9c0 @ 0x0204e9c0, 0x40 bytes, Thumb
 * func_0204e9a8 @ 0x0204e9a8, 0x18 bytes, Thumb
 * func_0204e97c @ 0x0204e97c, 0x2a bytes, Thumb
 * func_0204e96c @ 0x0204e96c, 0x10 bytes, Thumb
 * func_0204e938 @ 0x0204e938, 0x34 bytes, Thumb
 * func_0204e8c4 @ 0x0204e8c4, 0x74 bytes, Thumb
 * func_0204e854 @ 0x0204e854, 0x70 bytes, Thumb
 */

#include "types.h"

struct Pair {
    int a;
    int b;
};

struct Pair_0204e97c {
    int x;
    int y;
};

typedef struct {
    unsigned char pad_00[0x2224];
    unsigned char bitfield : 2;
} UnkStruct_0204e96c;

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    int a;
    int b;
    int c;
    int d;
} UnkStruct_0204e8c4;

// Same as func_0204e77c: both grid counters live in one struct whose address is taken.
typedef struct UnkStruct_0204e854 {
    int i;
    int j;
} UnkStruct_0204e854;

extern void *func_0204e6d8(void *);
extern int func_0204e6f8(void *);
extern void func_02037d0c(void *);
extern void func_02037d10(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_0204e6bc(void *p);
extern void func_02037d00(void *p);
extern void *func_0204e6b8(void *addr);
extern unsigned int func_020b7098(void);
extern void func_020b0698(unsigned int);
extern unsigned char data_021f3b56[];
extern UnkStruct_0204e8c4 *func_0204f86c(int size, int);

int func_0204e97c(int a, struct Pair_0204e97c *p2, struct Pair_0204e97c *p3);

void *func_0204ead0(void *p)
{
    __cxa_vec_ctor((void *) ((char *) p + 0x24), 0x10, 0x200, (((void (*)(void *)) func_0204e6f8)),
                   (((void (*)(void *)) func_0204e6d8)));
    __cxa_vec_ctor((void *) ((char *) p + 0x2024), 0x10, 0x20, (void (*)(void *)) func_02037d10,
                   (void (*)(void *)) func_02037d0c);
    return p;
}

void *func_0204ea98(void *p)
{
    __cxa_vec_cleanup((void *) ((char *) p + 0x2024), 0x10, 0x20, (void (*)(void *)) func_02037d0c);
    __cxa_vec_cleanup((void *) ((char *) p + 0x24), 0x10, 0x200, (((void (*)(void *)) func_0204e6d8)));
    return p;
}

void func_0204ea40(unsigned char *base)
{
    unsigned char *dst, *a, *b;
    int i, j;

    dst = base;
    a = base + 0x24;
    b = base + 0x2024;

    for (i = 0; i < 0x24; i++) {
        *dst++ = 0x86;
    }

    for (j = 0; j < 0x10; j++) {
        func_0204e6bc(a);
        func_02037d00(b);
        a += 0x200;
        b += 0x20;
    }

    *(base + 0x2224) &= ~3;
}

int func_0204ea00(void *arg0, int *arg1)
{
    struct Pair p1, p2;
    int result = 0;

    p1.a = 0;
    p1.b = 0;
    p2.a = arg1[0];
    p2.b = arg1[1];

    if (func_0204e97c((int) arg0, (struct Pair_0204e97c *) (&p1), (struct Pair_0204e97c *) (&p2))) {
        result = (int) func_0204e6b8((char *) arg0 + 0x24 + (p1.b << 11) + (p1.a << 9));
    }
    return result;
}

void *func_0204e9c0(void *base, int *src)
{
    int out[2];
    int in[2];
    void *result;

    out[0] = 0;
    out[1] = 0;
    in[0] = src[0];
    in[1] = src[1];

    result = 0;
    if (func_0204e97c((int) base, (struct Pair_0204e97c *) out, (struct Pair_0204e97c *) in)) {
        result = (char *) base + 0x2024 + (out[1] << 7) + (out[0] << 5);
    }
    return result;
}

int func_0204e9a8(int r0, int r1, int r2)
{
    if (r1 > 0 && r1 < 5 && r2 > 0 && r2 < 5) {
        return 1;
    }
    return 0;
}

int func_0204e97c(int a, struct Pair_0204e97c *p2, struct Pair_0204e97c *p3)
{
    int result = 0;
    if (func_0204e9a8(a, p3->x, p3->y)) {
        p2->x = p3->x - 1;
        p2->y = p3->y - 1;
        result = 1;
    }
    return result;
}

unsigned int func_0204e96c(UnkStruct_0204e96c *ptr)
{
    return (unsigned int) ptr->bitfield;
}

void func_0204e938(unsigned int arg)
{
    unsigned int tmp;
    unsigned char *p;

    tmp = func_020b7098();
    p = (unsigned char *) (arg + 0x2224);
    *p = (*p & ~0xFC) | (((unsigned char) tmp & 0x3F) << 2);
    func_020b0698((unsigned int) data_021f3b56);
}

UnkStruct_0204e8c4 *func_0204e8c4(unsigned char *p0, int argument1)
{
    Point pt;
    Point o;
    UnkStruct_0204e8c4 *arr;
    int n;
    UnkStruct_0204e8c4 *e;

    pt.x = 0;
    pt.y = 0;
    arr = func_0204f86c(0x24, (int) argument1);
    if (arr == 0) {
        goto ret;
    }
    n = 0;
    pt.y = 0;
    o.x = 0;
    o.y = 0;
    for (; pt.y < 6; pt.y++) {
        for (pt.x = o.x; pt.x < 6; pt.x++) {
            e = &arr[n];
            e->a = *(p0 + pt.y * 6 + pt.x);
            e->b = func_0204ea00((void *) p0, (int *) (&pt));
            e->c = o.y;
            e->d = (int) func_0204e9c0((void *) p0, (int *) (&pt));
            n++;
        }
    }
ret:
    return arr;
}

int func_0204e854(void *a)
{
    int n;
    UnkStruct_0204e854 s;
    u16 *p;
    int k;
    int count;
    int result;

    count = 0;
    s.i = 0;
    s.j = 0;
    result = 0;
    for (s.j = 0, n = 0; s.j < 6; s.j++) {
        for (s.i = 0; s.i < 6; s.i++) {
            p = (u16 *) func_0204ea00(a, &s.i);
            if (p != 0) {
                // do/while: the loop has no entry check.
                k = n;
                do {
                    if (*p == 0x500a) {
                        count++;
                    }
                    p++;
                    k++;
                } while (k < 256);
            }
        }
    }
    if (count >= 9) {
        result = 1;
    }
    return result;
}
