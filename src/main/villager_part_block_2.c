/* villager_part_block_2: 13 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209b4d4 @ 0x0209b4d4, 0x2 bytes, Thumb
 * func_0209b4cc @ 0x0209b4cc, 0x8 bytes, Thumb
 * func_0209b484 @ 0x0209b484, 0x48 bytes, Thumb
 * func_0209b42c @ 0x0209b42c, 0x58 bytes, Thumb
 * func_0209b414 @ 0x0209b414, 0x16 bytes, Thumb
 * func_0209b40c @ 0x0209b40c, 0x6 bytes, Thumb
 * func_0209b408 @ 0x0209b408, 0x4 bytes, Thumb
 * func_0209b3cc @ 0x0209b3cc, 0x3c bytes, Thumb
 * func_0209b3b0 @ 0x0209b3b0, 0x1c bytes, Thumb
 * func_0209b2a8 @ 0x0209b2a8, 0x108 bytes, Thumb
 * func_0209b28c @ 0x0209b28c, 0x1c bytes, Thumb
 * func_0209b270 @ 0x0209b270, 0x1c bytes, Thumb
 * func_0209b254 @ 0x0209b254, 0x1c bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[44];
    unsigned char unk_2C;
} UnkStruct_0209b40c;

typedef struct {
    u8 pad_00[0xc];
    u8 unk_0C[0x10];
    u8 unk_1C[0x10];
} UnkStruct_0209b2a8;

typedef struct {
    u8 d[0x20];
} OA;

typedef struct {
    u8 d[0x60];
} OB;

extern int data_020ccf94;
extern int func_02073d90(int);
extern int func_0209c310(int);
extern int func_0209bd44(void *);
extern int func_0209bc94(int);
extern int func_0209bc40(int);
extern int func_0209bc44(int, int *);
extern unsigned int func_0209bba0(int);
extern unsigned char data_020e3514[];
extern void func_02063ccc(void *, int, int);
extern void func_020638d4(void *, void *, int, int, int, int, int);
extern void func_02063cc8(void *);
extern void func_0209bb68(int, unsigned short *);
extern u8 data_020d1a48[];
extern u8 data_020e3494[];
extern int func_02003704(u8 *);
extern void *func_02094fd4(OA *);
extern void *func_02094fbc(OA *);
extern void *func_020a8228(OB *);
extern void *func_020a8210(OB *);
extern int func_02003618(u8 *, OA *);
extern int func_0203d7c4(int, void *);
extern void func_020a8c1c(void *);
extern int func_0209c54c(int *, int);
extern void *func_020b49d4(OB *, u8 *, int);
extern int func_0200366c(u8 *, u8 *, int, void *);
extern u8 func_020644cc(int);
extern void func_02066104(void *, u8 *, u8 *, u8 *, u8 *, u8 *, void *, u8 *, u8 *, int);

void *func_0209b4d4(void *object)
{
    return object;
}

int func_0209b4cc(int p0, int p1)
{
    return ((int) (((int) (p0) + (12))) + ((p1 << 4)));
}

int func_0209b484(int a, int b)
{
    int r, result;

    if (func_02073d90(data_020ccf94)) {
        return 0;
    }

    r = func_0209c310(b);
    result = 0;

    switch (a) {
        case 10:
            if (r == 1) {
                result = 1;
            }
            break;
        case 19:
            if (r == 1) {
                result = 1;
            }
            // fall through
        default:
            break;
    }

    return result;
}

int func_0209b42c(int a, int b)
{
    int flag = 0;
    int local;
    if (func_0209bd44((void *) a) != 0) {
        if (func_0209bc94(b) == 1) {
            if (b == func_0209bc40(a)) {
                if (func_0209bc44(a, &local) != 0) {
                    if (func_0209bba0(a) > data_020e3514[local * 20]) {
                        flag = 1;
                    }
                }
            }
        }
    }
    return flag;
}

int func_0209b414(int x)
{
    return func_0209b42c(x, func_0209bc40((int) ((unsigned char *) x)));
}

void func_0209b40c(UnkStruct_0209b40c *p, unsigned char v)
{
    p->unk_2C = v;
}

int func_0209b408(int p0)
{
    return ((int) (p0) + (44));
}

int func_0209b3cc(void *param)
{
    int d;
    struct {
        int x;
        int y;
    } e;

    func_02063ccc(&e, 2, 0);
    func_020638d4(&d, &e, 0, 0, 1, 1, 0);
    func_02063cc8(&e);
    func_0209bb68((int) param, (unsigned short *) (&d));

    return 1;
}

int func_0209b3b0(int arg)
{
    unsigned short value = 0x1565;
    func_0209bb68(arg, &value);
    return 1;
}

void func_0209b2a8(UnkStruct_0209b2a8 *a0, void *a1)
{
    u8 buf[8];
    int v;
    u8 str[0x20];
    OA a;
    OB b;
    int i;
    int h;

    if (func_02003704(a0->unk_0C) && func_02003704(a0->unk_1C)) {
        func_02094fd4(&a);
        func_020a8228(&b);
        v = 0;
        func_02003618(a0->unk_1C, &a);
        func_0203d7c4(0, &a);
        func_020a8c1c(&a);
        func_02003618(a0->unk_0C, &a);
        func_0203d7c4(1, &a);
        for (i = 0; i < 6; i++) {
            h = func_0209c54c(&v, i);
            func_020a8c1c(&b);
            buf[0] = (u8) v;
            func_020b49d4(&b, buf, h);
            func_0203d7c4(i + 2, &b);
        }
        func_0200366c(a0->unk_0C, str, 0x1e, data_020d1a48);
        buf[1] = func_020644cc(10);
        buf[2] = func_020644cc(10);
        buf[3] = func_020644cc(10);
        buf[4] = func_020644cc(10);
        func_02066104(a1, &buf[1], &buf[2], &buf[3], &buf[4], str, data_020e3494, a0->unk_0C, a0->unk_1C, 1);
        func_020a8210(&b);
        func_02094fbc(&a);
    }
}

int func_0209b28c(int arg)
{
    unsigned short value = 0x1563;
    func_0209bb68(arg, &value);
    return 1;
}

int func_0209b270(void *arg0)
{
    unsigned short local = 0x1561;
    func_0209bb68((int) arg0, &local);
    return 1;
}

int func_0209b254(int param)
{
    unsigned short data = 0x1564;
    func_0209bb68(param, (unsigned short *) (&data));
    return 1;
}
