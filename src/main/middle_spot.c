/* middle_spot: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02087f58 @ 0x02087f58, 0xcc bytes, Thumb
 * func_02087f4c @ 0x02087f4c, 0xa bytes, Thumb
 * func_02087f40 @ 0x02087f40, 0xa bytes, Thumb
 * func_02087f30 @ 0x02087f30, 0xe bytes, Thumb
 * func_02087f28 @ 0x02087f28, 0x6 bytes, Thumb
 * func_02087f20 @ 0x02087f20, 0x6 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_02087f58;

typedef struct {
    char pad_00[8];
    u8 unk_08;
} UnkStruct_02087f58_2;

typedef struct {
    unsigned long a;
    unsigned long b;
} UnkStruct_02087f4c;

typedef struct {
    unsigned long x;
    unsigned char pad_04[4];
    unsigned long y;
} UnkStruct_02087f4c_2;

typedef struct {
    unsigned long a;
    unsigned long b;
} UnkStruct_02087f40;

typedef struct {
    unsigned long x;
    unsigned char pad_04[4];
    unsigned long y;
} UnkStruct_02087f40_2;

typedef struct {
    unsigned char pad_00[8];
    unsigned char unk_08;
} UnkStruct_02087f28;

typedef struct {
    unsigned char pad_00[8];
    unsigned char unk_08;
} UnkStruct_02087f20;

extern void *func_0204e414(void);
extern void MI_CpuFill8(void *dst, int v, int n);
extern void func_0204f800(int *a, int *b, int c, int d, int e, int f);
extern int func_02088024(int x, int y, void *obj);
extern void func_0204f794(UnkStruct_02087f58 *r, int x, int y);
extern int func_020644cc(int);
extern unsigned int data_021d2890[];

void func_02087f4c(UnkStruct_02087f4c *dst, UnkStruct_02087f4c_2 *src);

void func_02087f58(UnkStruct_02087f58_2 *p0)
{
    void *obj;
    unsigned int *b;
    int bx;
    int by;
    int startx;
    int startx2;
    int count;
    int k;
    int xi;
    int yi;
    int xj;
    int yj;
    UnkStruct_02087f58 r;

    obj = func_0204e414();
    if (obj != 0) {
        count = 0;
        bx = 0;
        by = 0;
        b = data_021d2890;
        MI_CpuFill8(b, 0, 0x80);
        func_0204f800(&bx, &by, 2, 2, 0, 0);
        yi = 0;
        startx = 0;
        for (yi = 0; yi < 0x20; yi++) {
            for (xi = startx; xi < 0x20; xi++) {
                if (func_02088024(bx + xi, by + yi, obj) != 0) {
                    *b = *b | (1 << xi);
                    count++;
                }
            }
            b++;
        }
        if (count > 0) {
            k = func_020644cc(count);
            b = data_021d2890;
            yj = 0;
            startx2 = 0;
            for (yj = 0; yj < 0x20; yj++) {
                for (xj = startx2; xj < 0x20; xj++) {
                    if (((*b >> xj) & 1) != 0) {
                        if (k == 0) {
                            func_0204f794(&r, bx + xj, by + yj);
                            func_02087f4c((UnkStruct_02087f4c *) p0, (UnkStruct_02087f4c_2 *) (&r));
                            break;
                        }
                        k--;
                    }
                }
                if (xj < 0x20) {
                    break;
                }
                b++;
            }
        }
    }
    p0->unk_08 = 0;
}

void func_02087f4c(UnkStruct_02087f4c *dst, UnkStruct_02087f4c_2 *src)
{
    dst->a = src->x;
    dst->b = src->y;
}

void func_02087f40(UnkStruct_02087f40 *src, UnkStruct_02087f40_2 *dst)
{
    dst->x = src->a;
    dst->y = src->b;
}

int func_02087f30(void *ptr)
{
    if (*(unsigned char *) ((char *) ptr + 8) != 0) {
        return 1;
    } else {
        return 0;
    }
}

void func_02087f28(UnkStruct_02087f28 *p)
{
    p->unk_08 = 1;
}

void func_02087f20(UnkStruct_02087f20 *p)
{
    p->unk_08 = 0;
}
