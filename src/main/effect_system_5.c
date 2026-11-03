/* effect_system_5: 21 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020916cc @ 0x020916cc, 0x14 bytes, Thumb
 * func_020916a4 @ 0x020916a4, 0x28 bytes, Thumb
 * func_0209167c @ 0x0209167c, 0x28 bytes, Thumb
 * func_02091658 @ 0x02091658, 0x24 bytes, Thumb
 * func_02091634 @ 0x02091634, 0x22 bytes, Thumb
 * func_02091610 @ 0x02091610, 0x24 bytes, Thumb
 * func_020915fc @ 0x020915fc, 0x14 bytes, Thumb
 * func_020915d4 @ 0x020915d4, 0x28 bytes, Thumb
 * func_020915c0 @ 0x020915c0, 0x14 bytes, Thumb
 * func_02091598 @ 0x02091598, 0x28 bytes, Thumb
 * func_02091574 @ 0x02091574, 0x24 bytes, Thumb
 * func_02091550 @ 0x02091550, 0x24 bytes, Thumb
 * func_0209154c @ 0x0209154c, 0x4 bytes, Thumb
 * func_02091528 @ 0x02091528, 0x24 bytes, Thumb
 * func_02091504 @ 0x02091504, 0x24 bytes, Thumb
 * func_020914dc @ 0x020914dc, 0x28 bytes, Thumb
 * func_02091494 @ 0x02091494, 0x48 bytes, Thumb
 * func_02091468 @ 0x02091468, 0x2c bytes, Thumb
 * func_02091444 @ 0x02091444, 0x24 bytes, Thumb
 * func_020913f0 @ 0x020913f0, 0x54 bytes, Thumb
 * func_020913c8 @ 0x020913c8, 0x26 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0xe];
    short unk_0E;
    short unk_10;
    int unk_14;
    short unk_18;
} UnkStruct_020914dc;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    short unk_0C;
    short unk_0E;
    short unk_10;
    int unk_14;
    short unk_18;
} UnkStruct_02091494;

typedef struct {
    u32 a;
    u32 b;
    u32 c;
    s16 d;
    u16 pad_0E;
    s16 e;
    u16 pad_12;
    u32 id;
    u32 tail;
} Entry;

typedef struct Entry_020913c8 {
    char pad_00[14];
    short unk_0E;
    int pad_10;
    int unk_14;
    char pad_18[4];
} Entry_020913c8;

extern void func_02094d48(int param1, const void *param2, const void *param3);
extern unsigned char data_020d17bc;
extern unsigned char data_020d1750;
extern int func_02094cf8(int, int, int, int, int, int);
extern unsigned char data_020e27d0[];
extern int func_02094840(int, int, int, int, int, void (*)(void *));
extern int data_020d16f0;
extern int data_020d175c;
extern unsigned char data_020e286c[];
extern int data_020d1810;
extern int data_020d16d8;
extern unsigned char data_020e2798[];
extern int func_02094b58(int p1, int p2, int p3, int p4, int p5, int p6);
extern void MI_CpuFill8(void *p, int, int);

void func_020916cc(int param0)
{
    func_02094d48(param0, &data_020d17bc, &data_020d1750);
}

void func_020916a4(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = (unsigned int) data_020e27d0;
    func_02094cf8(0x14, r0, r1, r2, sp[0], sp[1]);
}

void func_0209167c(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = (unsigned int) data_020e27d0;
    func_02094cf8(0x82, r0, r1, r2, sp[0], sp[1]);
}

void func_02091658(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = 0;
    func_02094cf8(0x15, r0, r1, r2, sp[0], sp[1]);
}

int func_02091634(int a, int b, int c, int d)
{
    return func_02094840(0, a, b, c, d, 0);
}

void func_02091610(int a, int b, int c, int d)
{
    void (*local)(void *) = 0;
    func_02094840(1, a, b, c, d, local);
}

void func_020915fc(int param)
{
    func_02094d48(param, (const void *) (&data_020d16f0), (const void *) (&data_020d175c));
}

void func_020915d4(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = (unsigned int) data_020e286c;
    func_02094cf8(0x51, r0, r1, r2, sp[0], sp[1]);
}

void func_020915c0(void *arg0)
{
    func_02094d48((int) arg0, (const void *) (&data_020d1810), (const void *) (&data_020d16d8));
}

void func_02091598(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = (unsigned int) data_020e2798;
    func_02094cf8(0x7b, r0, r1, r2, sp[0], sp[1]);
}

int func_02091574(int a, int b, int c, int d)
{
    return func_02094b58(124, a, b, c, d, 0);
}

int func_02091550(int a, int b, int c, int d)
{
    return func_02094cf8(0x7d, a, b, c, d, 0);
}

int func_0209154c(void)
{
    return 3;
}

int func_02091528(int a0, int a1, int a2, int a3, int a4)
{
    return func_02094cf8(a4, a0, a1, a2, a3, 0);
}

void func_02091504(int a, int b, int c, int d, int e)
{
    func_02094b58(e, a, b, c, d, 0);
}

void func_020914dc(UnkStruct_020914dc *p)
{
    MI_CpuFill8(p, 0, 0x14);
    p->unk_0E = -1;
    p->unk_10 = 0x1000;
    p->unk_14 = -1;
    p->unk_18 = 0x66;
}

void func_02091494(UnkStruct_02091494 *out, int a, short b, int *src, short *p1, short *p2, short c)
{
    func_020914dc((UnkStruct_020914dc *) out);
    out->unk_14 = a;
    out->unk_18 = b;
    out->unk_00 = src[0];
    out->unk_04 = src[1];
    out->unk_08 = src[2];
    if (p1) {
        out->unk_0C = *p1;
    }
    if (p2) {
        out->unk_10 = *p2;
    }
    out->unk_0E = c;
}

void func_02091468(void *arg0)
{
    int i;
    void *ptr;

    ptr = (void *) ((unsigned int) arg0 + 0x380);
    func_020914dc((UnkStruct_020914dc *) ptr);
    for (i = 0; i < 0x20; i++) {
        func_020914dc((UnkStruct_020914dc *) ((void *) ((unsigned int) arg0 + (i * 0x1c))));
    }
}

int func_02091444(int param1, int param2, int param3, int param4)
{
    int i;
    int result;
    int *ptr;

    result = 0;
    i = 0;
    ptr = (int *) param3;

    while (i < param4) {
        if (param2 == *(ptr + 5)) {
            result = (int) ptr;
            break;
        }
        ptr = (int *) ((char *) ptr + 0x1c);
        i++;
    }

    return result;
}

void func_020913f0(Entry *arr, int id, const u32 *src, const s16 *p1, const s16 *p2)
{
    int i;
    if (id == -1) {
        return;
    }
    for (i = 0; i < 32; i++) {
        Entry *e = &arr[i];
        if (id == e->id) {
            e->a = src[0];
            e->b = src[1];
            e->c = src[2];
            if (p1) {
                e->d = *p1;
            }
            if (p2) {
                e->e = *p2;
            }
        }
    }
}

void func_020913c8(Entry_020913c8 *arr, int key, short value)
{
    int i;
    i = 0;
    if (key == -1) {
        return;
    }
    for (; i < 32; i++) {
        Entry_020913c8 *p = &arr[i];
        if (key == p->unk_14) {
            p->unk_0E = value;
        }
    }
}
