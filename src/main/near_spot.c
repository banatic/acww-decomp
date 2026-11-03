/* near_spot: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02087e74 @ 0x02087e74, 0x2 bytes, Thumb
 * func_02087e70 @ 0x02087e70, 0x2 bytes, Thumb
 * func_02087e64 @ 0x02087e64, 0xc bytes, Thumb
 * func_02087e58 @ 0x02087e58, 0xa bytes, Thumb
 * func_02087e4c @ 0x02087e4c, 0xa bytes, Thumb
 * func_02087e38 @ 0x02087e38, 0x12 bytes, Thumb
 * func_02087e2c @ 0x02087e2c, 0xc bytes, Thumb
 * func_02087e20 @ 0x02087e20, 0xa bytes, Thumb
 * func_02087e0c @ 0x02087e0c, 0x12 bytes, Thumb
 * func_02087e00 @ 0x02087e00, 0xa bytes, Thumb
 * func_02087df4 @ 0x02087df4, 0xa bytes, Thumb
 * func_02087de8 @ 0x02087de8, 0xc bytes, Thumb
 * func_02087dd8 @ 0x02087dd8, 0x10 bytes, Thumb
 * func_02087dd0 @ 0x02087dd0, 0x8 bytes, Thumb
 * func_02087d00 @ 0x02087d00, 0xce bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned long a;
    unsigned long b;
} UnkStruct_02087e58;

typedef struct {
    unsigned long x;
    unsigned char pad_04[4];
    unsigned long y;
} UnkStruct_02087e58_2;

typedef struct {
    unsigned long a;
    unsigned long b;
} UnkStruct_02087e4c;

typedef struct {
    unsigned long x;
    unsigned char pad_04[4];
    unsigned long y;
} UnkStruct_02087e4c_2;

struct UnkStruct_02087e38 {
    unsigned char pad_00[8];
    unsigned char b0 : 1;
};

typedef struct {
    unsigned char pad_00[8];
    unsigned char flag : 1;
} UnkStruct_02087e2c;

typedef struct {
    unsigned char pad_00[8];
    unsigned char bit0 : 1;
    unsigned char bit1 : 1;
} TestStruct;

typedef struct {
    unsigned char pad_00[8];
    unsigned char flags;
} UnkStruct_02087e00;

typedef struct {
    unsigned char pad_00[8];
    unsigned char flags;
} UnkStruct_02087df4;

extern void MI_CpuFill8(int, int, int);
extern int func_02088024(void *b, void *a, int c);
extern int func_020644cc(int);

void func_02087e74(void *object) {}

void func_02087e70(void *object) {}

void func_02087e64(int p0)
{
    MI_CpuFill8(p0, 0, 12);
}

void func_02087e58(UnkStruct_02087e58 *dst, UnkStruct_02087e58_2 *src)
{
    dst->a = src->x;
    dst->b = src->y;
}

void func_02087e4c(UnkStruct_02087e4c *src, UnkStruct_02087e4c_2 *dst)
{
    dst->x = src->a;
    dst->y = src->b;
}

int func_02087e38(struct UnkStruct_02087e38 *s)
{
    if (s->b0) {
        return 1;
    } else {
        return 0;
    }
}

void func_02087e2c(UnkStruct_02087e2c *ptr)
{
    ptr->flag = 1;
}

void func_02087e20(unsigned char *p)
{
    p[8] = (unsigned char) (p[8] & ~1);
}

int func_02087e0c(TestStruct *p)
{
    if (p->bit1) {
        return 1;
    } else {
        return 0;
    }
}

void func_02087e00(UnkStruct_02087e00 *p)
{
    p->flags &= ~2;
}

void func_02087df4(UnkStruct_02087df4 *p)
{
    p->flags |= 2;
}

int func_02087de8(unsigned char *arg)
{
    unsigned int x = arg[8];
    unsigned int t = (x << 28) >> 30;
    t <<= 30;
    return (int) t >> 16;
}

int func_02087dd8(void *a, void *b, int c)
{
    return func_02088024(b, a, c);
}

int func_02087dd0(int argument0, int argument1, void *argument2)
{
    return func_02088024((void *) ((int) argument0), (void *) ((int) argument1), (int) ((void *) argument2));
}

int func_02087d00(int *out, int (*fn)(int, int, int), int ctx, int lo, int hi, int arg, u16 *bits, int nrows)
{
    int row;
    int k;
    int bit2;
    int bit;
    int count;
    int row2;
    int i;
    int t;
    u16 v;

    bit = 0;
    row = 0;
    count = 0;
    if (lo > hi) {
        t = lo;
        lo = hi;
        hi = t;
    }
    MI_CpuFill8((int) bits, 0, nrows * 2);
    for (i = lo; i <= hi; i++) {
        if (fn(ctx, i, arg) != 0) {
            v = bits[row];
            bits[row] = v | (1 << bit);
            count++;
        }
        bit++;
        if (bit >= 0x10) {
            bit = 0;
            row++;
        }
        if (row >= nrows) {
            break;
        }
    }
    if (count > 0) {
        k = func_020644cc(count);
        bit2 = 0;
        row2 = 0;
        for (; lo <= hi; lo++) {
            if (((bits[row2] >> bit2) & 1) != 0) {
                if (k == 0) {
                    *out = lo;
                    return 1;
                }
                k--;
            }
            bit2++;
            if (bit2 >= 0x10) {
                bit2 = 0;
                row2++;
            }
            if (row2 >= nrows) {
                break;
            }
        }
    }
    return 0;
}
