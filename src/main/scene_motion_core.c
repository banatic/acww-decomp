/* scene_motion_core: 12 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02019b68 @ 0x02019b68, 0x6 bytes, Thumb
 * func_02019b60 @ 0x02019b60, 0x6 bytes, Thumb
 * func_02019af8 @ 0x02019af8, 0x68 bytes, Thumb
 * func_02019af0 @ 0x02019af0, 0x6 bytes, Thumb
 * func_02019ac0 @ 0x02019ac0, 0x30 bytes, Thumb
 * func_02019a84 @ 0x02019a84, 0x3c bytes, Thumb
 * func_02019a58 @ 0x02019a58, 0x2a bytes, Thumb
 * func_02019a2c @ 0x02019a2c, 0x2c bytes, Thumb
 * func_02019a18 @ 0x02019a18, 0x14 bytes, Thumb
 * func_020199f8 @ 0x020199f8, 0x1e bytes, Thumb
 * func_020199ec @ 0x020199ec, 0xc bytes, Thumb
 * func_020199d8 @ 0x020199d8, 0x12 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[24];
    unsigned char unk_18;
} UnkStruct_02019b68;

typedef struct {
    unsigned char pad_00[24];
    unsigned char unk_18;
} UnkStruct_02019b60;

typedef struct UnkStruct_02019af8 {
    u8 pad_00[0x14];
    int unk_14;
    u8 pad_18[0x1];
    u8 unk_19;
    u8 pad_1A[0x0a];
    int unk_24;
    int unk_28;
    u8 pad_2C[0x34];
} UnkStruct_02019af8;

typedef struct {
    unsigned char pad_00[148];
    unsigned long unk_94;
} UnkStruct_02019af0;

extern int func_02019de8(UnkStruct_02019af8 *self);
extern void func_02019e80(void *a, void *b);
extern void func_02019d94(UnkStruct_02019af8 *self, int p, int x, int y);
extern void func_02019d78(UnkStruct_02019af8 *self);
extern void func_020779b8(void *, int, int);
extern void func_02077978(unsigned char *dst, int a, int b);
extern void MI_CpuCopy8(void *dest, const void *src, unsigned int n);
extern void func_020778b0(int a, unsigned short b, void *c);
extern int func_02077898(int);

void func_02019b68(UnkStruct_02019b68 *p)
{
    p->unk_18 = 1;
}

void func_02019b60(UnkStruct_02019b60 *p)
{
    p->unk_18 = 0;
}

void func_02019af8(UnkStruct_02019af8 *self, int param1)
{
    if (self->unk_28 != 0 && (self->unk_28 >= self->unk_14 || func_02019de8(self) != 0 || self->unk_14 == 3)) {
        func_02019e80((u8 *) self + 0x60, (u8 *) self + 0x2c);
        func_02019d94(self, param1, self->unk_24, self->unk_28);
    }

    if (self->unk_19 == 1) {
        func_02019b68((UnkStruct_02019b68 *) self);
        self->unk_19 = 0;
    } else if (self->unk_19 == 2) {
        func_02019b60((UnkStruct_02019b60 *) self);
        self->unk_19 = 0;
    }

    func_02019d78(self);
}

void func_02019af0(UnkStruct_02019af0 *p, unsigned long v)
{
    p->unk_94 = v;
}

void func_02019ac0(unsigned char *out, int x, int y, int z, int d, short e, unsigned short f)
{
    func_020779b8(out, x, y);
    func_020779b8(out + 5, z, d);
    MI_CpuCopy8(&e, (const void *) (out + 10), 2);
    out[12] = (unsigned char) f;
}

void func_02019a84(int a, int b, int c, int d, int e, short *f, unsigned char *p)
{
    func_02077978(p, a, b);
    func_02077978(p + 5, c, d);
    MI_CpuCopy8((void *) (p + 10), (const void *) e, 2);
    *f = p[12];
}

void func_02019a58(char *p, unsigned short a, unsigned short b, char c)
{
    MI_CpuCopy8(&a, p, 2);
    MI_CpuCopy8(&b, p + 2, 2);
    p[4] = c;
}

void func_02019a2c(void *param0, void *param1, unsigned short *param2, unsigned char *param3)
{
    unsigned char temp;

    MI_CpuCopy8(param3, param0, 2);
    MI_CpuCopy8(param3 + 2, param1, 2);
    temp = param3[4];
    *param2 = temp;
}

void func_02019a18(unsigned char *dst, unsigned char a, unsigned char b, unsigned char c, unsigned short d)
{
    dst[0] = a;
    dst[1] = b;
    dst[2] = c;
    dst[3] = (unsigned char) d;
}

// placeholder, not used
void func_020199f8(unsigned int *r0, unsigned char *r1, unsigned short *r2, unsigned short *r3, const unsigned char *r5)
{
    unsigned int temp;
    unsigned char byte0, byte1, byte2, byte3;

    temp = *r5;
    *r0 = temp;
    byte0 = r5[1];
    *r1 = byte0;
    byte1 = r5[2];
    *r2 = byte1;
    byte2 = r5[3];
    *r3 = byte2;
}

void func_020199ec(int a, int b, void *c)
{
    func_020778b0(b, *(unsigned short *) c, c);
}

void func_020199d8(unsigned short *out, int in)
{
    *out = func_02077898(in);
}
