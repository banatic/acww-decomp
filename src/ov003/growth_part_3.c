/* growth_part_3: 4 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02224138 @ 0x02224138, 0x6 bytes, Thumb
 * func_ov003_022240fc @ 0x022240fc, 0x3c bytes, Thumb
 * func_ov003_022240cc @ 0x022240cc, 0x30 bytes, Thumb
 * func_ov003_0222409c @ 0x0222409c, 0x2e bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned long unk_00;
} UnkStruct_02224138;

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    int unk_00, unk_04, unk_08;
    u8 unk_0C, unk_0D, unk_0E, unk_0F;
    char pad_10[4];
    int unk_14, unk_18, unk_1C;
} UnkStruct_022240fc;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    u8 unk_0C;
} UnkStruct_022240cc;

typedef struct {
    int unk_00;
    u16 unk_04;
    u16 unk_06;
    short unk_08;
} UnkStruct_0222409c;

typedef struct {
    char pad_00[0xd];
    u8 unk_0D;
} UnkStruct_0222409c_2;

typedef struct {
    char pad_00[0x50];
    int unk_50;
    char pad_54[4];
    u16 unk_58;
    char pad_5A[0xe];
    u8 unk_68;
} UnkStruct_0222409c_3;

extern int data_ov003_0223ac00[];
extern void ****data_ov003_02239f68[];

void func_ov003_02224138(UnkStruct_02224138 *p)
{
    p->unk_00 = 3;
}

void func_ov003_022240fc(UnkStruct_022240fc *o, int a1, int a2, int k, int a5, Vec3 *v, int flag)
{
    o->unk_00 = a1;
    o->unk_04 = a2;
    o->unk_0E = 0;
    o->unk_14 = v->x;
    o->unk_18 = v->y;
    o->unk_1C = v->z;
    o->unk_0F = (u8) k;
    if (flag == 0) {
        o->unk_08 = data_ov003_0223ac00[k];
    } else {
        o->unk_08 = 4;
    }
    o->unk_0C = (u8) a5;
}

void *func_ov003_022240cc(UnkStruct_022240cc *o)
{
    void ****a;
    void ***b;
    void **c;
    void *r = 0;
    a = data_ov003_02239f68[o->unk_00];
    if (a != 0) {
        b = a[o->unk_08];
        if (b != 0) {
            c = b[o->unk_0C];
            if (c != 0) {
                r = c[o->unk_04];
            }
        }
    }
    return r;
}

void func_ov003_0222409c(UnkStruct_0222409c_2 *a, UnkStruct_0222409c_3 *b)
{
    UnkStruct_0222409c *x = (UnkStruct_0222409c *) func_ov003_022240cc((UnkStruct_022240cc *) a);
    b->unk_68 = (u8) x->unk_04;
    b->unk_58 = x->unk_06;
    b->unk_50 = x->unk_08;
    a->unk_0D = (u8) x->unk_00;
}
