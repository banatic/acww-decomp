/* town_spot: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02087950 @ 0x02087950, 0xb8 bytes, Thumb
 * func_0208786c @ 0x0208786c, 0xe2 bytes, Thumb
 * func_02087864 @ 0x02087864, 0x6 bytes, Thumb
 * func_02087854 @ 0x02087854, 0xe bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x;
    int y;
} Pt;

typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_0208786c;

typedef struct {
    int a;
    int b;
} UnkStruct_0208786c_2;

typedef struct {
    int unk_00;
    UnkStruct_0208786c_2 s;
} UnkStruct_0208786c_3;

typedef struct {
    unsigned long a;
    unsigned long b;
} UnkStruct_02087864;

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
} SrcStruct;

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
} DstStruct;

extern void MI_CpuFill8(void *dst, int val, int n);
extern void func_0204f800(int *a, int *b, int c, int d, int e, int f);
extern int func_02088024(int x, int y, int c);
extern void func_0204f794(int a, int x, int y);
extern int func_020644cc(int);
extern UnkStruct_0208786c_3 *func_0204e414(void);
extern int func_02087a08(int p0, Pt *pos, UnkStruct_0208786c_3 *obj);

void func_02087864(UnkStruct_02087864 *p, unsigned long a, unsigned long b);

int func_02087950(int p0, int p1, Pt *p2, int p3)
{
    int bx;
    int by;
    int startx;
    int count;
    int xi;
    int yi;
    int k;
    u16 *m;
    u16 *m2;
    int xj;
    int yj;
    u16 mask[16];

    count = 0;
    bx = 0;
    by = 0;
    MI_CpuFill8(mask, 0, 0x20);
    func_0204f800(&bx, &by, p2->x, p2->y, 0, 0);
    yi = 0;
    startx = 0;
    for (yi = 0; yi < 0x10; yi++) {
        xi = startx;
        m = &mask[yi];
        for (; xi < 0x10; xi++) {
            if (func_02088024(bx + xi, by + yi, p3) != 0) {
                *m = *m | (1 << xi);
                count++;
            }
        }
    }
    if (count > 0) {
        k = func_020644cc(count);
        for (yj = 0; yj < 0x10; yj++) {
            xj = 0;
            m2 = &mask[yj];
            for (; xj < 0x10; xj++) {
                if (((*m2 >> xj) & 1) != 0) {
                    if (k == 0) {
                        func_0204f794(p1, bx + xj, by + yj);
                        return 1;
                    }
                    k--;
                }
            }
        }
    }
    return 0;
}

int func_0208786c(int p0)
{
    UnkStruct_0208786c_3 *obj;
    u8 mask[4];
    Pt pos;
    UnkStruct_0208786c r;
    int count;
    int w;
    int h;
    int k;
    u8 *m;
    UnkStruct_0208786c_2 *q;

    obj = func_0204e414();
    if (obj != 0) {
        count = 0;
        pos.x = 0;
        pos.y = 0;
        q = &obj->s;
        w = q->a;
        h = q->b;
        MI_CpuFill8(mask, 0, 4);
        for (pos.y = 1; pos.y < h - 1; pos.y++) {
            for (pos.x = 1; pos.x < w - 1; pos.x++) {
                if (func_02087a08(p0, &pos, obj) != 0) {
                    mask[pos.y - 1] = mask[pos.y - 1] | (1 << (pos.x - 1));
                    count++;
                }
            }
        }
        if (count > 0) {
            k = func_020644cc(count);
            pos.y = 1;
            m = mask;
            for (; pos.y < h - 1; pos.y++) {
                for (pos.x = 1; pos.x < w - 1; pos.x++) {
                    if (((m[pos.y - 1] >> (pos.x - 1)) & 1) != 0) {
                        if (k == 0) {
                            func_02087950(p0, (int) (&r), &pos, (int) obj);
                            func_02087864((UnkStruct_02087864 *) p0, r.a, r.c);
                            return 1;
                        }
                        k--;
                    }
                }
            }
        }
    }
    return 0;
}

void func_02087864(UnkStruct_02087864 *p, unsigned long a, unsigned long b)
{
    p->a = a;
    p->b = b;
}

int func_02087854(SrcStruct *src, DstStruct *dst)
{
    dst->unk_00 = src->unk_00;
    dst->unk_08 = src->unk_04;
    dst->unk_04 = 0;
    return 0;
}
