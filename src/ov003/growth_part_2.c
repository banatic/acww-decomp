/* growth_part_2: 5 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02223f0c @ 0x02223f0c, 0x60 bytes, Thumb
 * func_ov003_02223edc @ 0x02223edc, 0x30 bytes, Thumb
 * func_ov003_02223ea8 @ 0x02223ea8, 0x34 bytes, Thumb
 * func_ov003_02223e88 @ 0x02223e88, 0x1e bytes, Thumb
 * func_ov003_02223dc8 @ 0x02223dc8, 0xc0 bytes, Thumb
 */

#include "types.h"

typedef struct {
    volatile int unk_00;
    int unk_04;
    int unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 unk_0F;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
} UnkStruct_02223f0c;

typedef struct {
    int unk_00;
    char pad_04[9];
    s8 unk_0D;
    s8 unk_0E;
    char pad_0F[1];
    char pad_10[0x10];
} UnkStruct_02223edc;

typedef struct {
    char pad_00[0xa];
    u8 unk_0A;
} UnkStruct_02223edc_2;

typedef struct {
    int unk_00;
    char pad_04[0x1c];
} UnkStruct_02223ea8;

typedef struct {
    char pad_00[0xa];
    u8 unk_0A;
    char pad_0B[1];
    int unk_0C;
} UnkStruct_02223ea8_2;

typedef struct {
    int unk_00;
    char pad_04[0x1c];
} UnkStruct_02223e88;

struct Pair {
    int a;
    int b;
};

extern UnkStruct_02223f0c data_ov003_0223cfa0[];
extern int data_ov003_02236be8[][4];
extern void func_02090d64(void *self);
extern void func_ov003_02223f6c(UnkStruct_02223f0c *e, void *t);
extern void func_ov003_0222409c(UnkStruct_02223f0c *e, void *t);
int func_02090d50(UnkStruct_02223ea8_2 *o);
extern unsigned char *func_0204cab4(void);
extern void func_0204f794(void *a4, int a5, int a6);
extern unsigned char data_ov003_02236b88[];

int func_ov003_02223ea8(UnkStruct_02223ea8_2 *o);

void func_ov003_02223f0c(void *self)
{

    int idx;
    char *t = *(char **) ((char *) self + 0xc);
    UnkStruct_02223f0c *e;

    func_02090d64(self);
    *(u8 *) ((char *) self + 0xa) = (u8) data_ov003_0223cfa0[2].unk_00;
    idx = data_ov003_0223cfa0[2].unk_00;
    if (idx < 0) {
        idx = 0;
    }
    e = &data_ov003_0223cfa0[idx];
    func_ov003_02223f6c(e, t);
    *(u8 *) ((char *) self + 0xa) = (u8) idx;
    func_ov003_0222409c(e, t);
    *(int *) (t + 0x44) = data_ov003_02236be8[data_ov003_0223cfa0[idx].unk_00][e->unk_0C];
    *(u8 *) (t + 0x80) = (u8) e->unk_10;
}

int func_ov003_02223edc(UnkStruct_02223edc_2 *o)
{
    UnkStruct_02223edc *e = &((UnkStruct_02223edc *) data_ov003_0223cfa0)[o->unk_0A];
    int v = e->unk_0D;
    if (v - 1 < 0) {
        e->unk_00 = 3;
    }
    e->unk_0D = (s8) (v - 1);
    e->unk_0E = (s8) (e->unk_0E + 1);
    return func_ov003_02223ea8((UnkStruct_02223ea8_2 *) o);
}

int func_ov003_02223ea8(UnkStruct_02223ea8_2 *o)
{
    int r = 1;
    UnkStruct_02223ea8 *e;
    func_02090d50(o);
    e = &((UnkStruct_02223ea8 *) data_ov003_0223cfa0)[o->unk_0A];
    if (e->unk_00 == 3) {
        r = 0;
    } else {
        func_ov003_02223f6c((UnkStruct_02223f0c *) e, (void *) o->unk_0C);
    }
    return r;
}

void *func_ov003_02223e88(char *o)
{
    int i;
    for (i = 0; i < 2; i++) {
        if (((UnkStruct_02223e88 *) o)[i].unk_00 == 3) {
            *(int *) (o + 0x40) = i;
            return &((UnkStruct_02223e88 *) o)[i];
        }
    }
    return 0;
}

void func_ov003_02223dc8(unsigned char *a0, int *p1, int *p2, int *p3, void *a4, unsigned short *a5, struct Pair *a6)
{
    unsigned char *base = func_0204cab4();
    int flag = 0;
    unsigned short val = *a5;
    int t;

    if (val >= 0x26 && val <= 0x2a) {
        flag = 1;
    }

    if (flag || (val >= 0x2b && val <= 0x2e) || val == 0x67) {
        t = (a6->a ^ a6->b) & 1;
        *p2 = 0;
        p1[4] = t;
        *p3 = 0x22;
        t = t * 23;
        if (*(&data_ov003_02236b88[t] + (unsigned int) base) != 0) {
            *p3 = 0x24;
        }
    } else if ((val >= 0x5d && val <= 0x61) || (val >= 0x62 && val <= 0x65) || val == 0x6d || val == 0x6b) {
        *p2 = 1;
        p1[4] = 3;
        *p3 = 0x25;
    } else if ((val >= 0xc8 && val <= 0xcf) || (val >= 0xd0 && val <= 0xd3)) {
        *p2 = 2;
        p1[4] = 3;
        *p3 = 0x27;
    } else {
        *p2 = 0;
        p1[4] = 2;
        *p3 = 0x22;
    }

    func_0204f794(a4, a6->a, a6->b);
}
