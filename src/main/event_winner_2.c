/* event_winner_2: 13 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02086834 @ 0x02086834, 0x6 bytes, Thumb
 * func_020867e4 @ 0x020867e4, 0x50 bytes, Thumb
 * func_020867e0 @ 0x020867e0, 0x2 bytes, Thumb
 * func_020867a4 @ 0x020867a4, 0x3a bytes, Thumb
 * func_020867a0 @ 0x020867a0, 0x4 bytes, Thumb
 * func_02086794 @ 0x02086794, 0xc bytes, Thumb
 * func_02086760 @ 0x02086760, 0x34 bytes, Thumb
 * func_0208675c @ 0x0208675c, 0x4 bytes, Thumb
 * func_02086754 @ 0x02086754, 0x6 bytes, Thumb
 * func_0208674c @ 0x0208674c, 0x6 bytes, Thumb
 * func_02086748 @ 0x02086748, 0x4 bytes, Thumb
 * func_02086744 @ 0x02086744, 0x4 bytes, Thumb
 * func_020866b8 @ 0x020866b8, 0x8c bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[71];
    unsigned char unk_47;
} UnkStruct_02086834;

typedef struct UnkStruct_020867e4 {
    unsigned short v[6];
} UnkStruct_020867e4;

typedef struct UnkStruct_020867e4_2 {
    unsigned short unk_00;
    UnkStruct_020867e4 unk_02;
    unsigned short unk_0E;
    UnkStruct_020867e4 unk_10;
    signed char unk_1C;
    unsigned char unk_1D;
    unsigned char unk_1E[4];
} UnkStruct_020867e4_2;

typedef struct Src {
    u16 f0;
    u16 arr[6];
    u8 b0;
    u8 b1;
} Src;

typedef struct Dst {
    u8 pad_00[0x1e];
    u16 f0;
    u16 arr[6];
    u8 b0;
    u8 b1;
} Dst;

struct Blk {
    u16 v[6];
};

typedef struct Dst_02086760 {
    u8 pad_00[0x2e];
    u16 f0;
    u16 arr[6];
    u8 b0;
    u8 b1;
} Dst_02086760;

typedef struct {
    unsigned short f;
} UnkStruct_02086754;

typedef struct {
    unsigned char pad_00[0x3e];
    unsigned short f;
} UnkStruct_02086754_2;

typedef struct {
    unsigned short f;
} UnkStruct_0208674c;

typedef struct {
    unsigned char pad_00[0x3e];
    unsigned short f;
} UnkStruct_0208674c_2;

typedef struct {
    char pad_00[0x44];
    unsigned char b0;
    unsigned char b1;
    unsigned char b2;
} UnkStruct_020866b8;

extern void func_02003738(void *);
extern void func_02095238(void *);
extern void func_0209df64(unsigned char *);
extern void func_0208683c(UnkStruct_020866b8 *);
extern int func_02098844(unsigned int, int);
extern int func_02099a28(unsigned int object);
extern int func_02099670(int);
extern void func_02088b38(int, int);
extern void func_02088b1c(int, int);
extern int data_021dc7bc;

void func_02086834(UnkStruct_02086834 *p, unsigned char v)
{
    p->unk_47 = v;
}

void func_020867e4(UnkStruct_020867e4_2 *d, UnkStruct_020867e4_2 *s)
{
    d->unk_00 = s->unk_00;
    d->unk_02 = s->unk_02;
    d->unk_0E = s->unk_0E;
    d->unk_10 = s->unk_10;
    d->unk_1C = s->unk_1C;
    d->unk_1D = s->unk_1D;
    func_02003738(&d->unk_1E);
}

void *func_020867e0(void *record)
{
    return record;
}

void func_020867a4(Dst *dst, const Src *src)
{
    dst->f0 = src->f0;
    *(struct Blk *) ((char *) dst + 0x20) = *(struct Blk *) ((char *) src + 2);
    dst->b0 = src->b0;
    dst->b1 = src->b1;
    func_02095238(dst);
}

int func_020867a0(int p0)
{
    return ((int) (p0) + (30));
}

void func_02086794(int arg)
{
    func_02003738((void *) (arg + 0x2e));
}

void func_02086760(Dst_02086760 *dst, const Src *src)
{
    u16 *pSrc;
    u16 *pDst;
    int count;

    dst->f0 = src->f0;
    *(struct Blk *) ((char *) dst + 0x30) = *(struct Blk *) ((char *) src + 2);
    dst->b0 = src->b0;
    dst->b1 = src->b1;
}

int func_0208675c(int p0)
{
    return ((int) (p0) + (46));
}

void func_02086754(UnkStruct_02086754_2 *dst, UnkStruct_02086754 *src)
{
    dst->f = src->f;
}

void func_0208674c(UnkStruct_0208674c *dst, UnkStruct_0208674c_2 *src)
{
    dst->f = src->f;
}

void func_02086748(int *p0, int p1)
{
    p0[16] = p1;
}

int func_02086744(int *p0)
{
    return p0[16];
}

void func_020866b8(UnkStruct_020866b8 *p, int mode)
{
    unsigned char arr[3];
    int i, val, zero;

    func_0209df64(arr);

    if (p->b2 == arr[2] && p->b1 == arr[1] && p->b0 == arr[0]) {
        return;
    }

    func_0208683c(p);

    zero = 0;

    for (i = 0; i < 4; i++) {
        val = func_02098844((unsigned int) &data_021dc7bc, i);
        if (val != 0 && func_02099a28((unsigned int) val) != 0) {
            switch (mode) {
                case 1:
                    func_02088b38(func_02099670(val), zero);
                    break;
                case 2:
                    func_02088b1c(func_02099670(val), zero);
                    break;
                default:
                    break;
            }
        }
    }
}
