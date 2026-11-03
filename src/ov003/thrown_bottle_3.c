/* thrown_bottle_3: 4 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0222c3e0 @ 0x0222c3e0, 0x34 bytes, Thumb
 * func_ov003_0222c3d0 @ 0x0222c3d0, 0x10 bytes, Thumb
 * func_ov003_0222c3a8 @ 0x0222c3a8, 0x28 bytes, Thumb
 * func_ov003_0222c364 @ 0x0222c364, 0x44 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x30];
    u8 unk_30;
    char pad_31[3];
    int unk_34, unk_38, unk_3C, unk_40, unk_44, unk_48, unk_4C, unk_50, unk_54, unk_58;
} UnkStruct_0222c3e0;

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    char pad_00[0x4c];
    Vec3 unk_4C;
    char pad_58[8];
} UnkStruct_0222c3a8;

typedef struct {
    char pad_00[0x30];
    u8 unk_30;
    char pad_31[0x27];
    int unk_58;
    char pad_5C[4];
} UnkStruct_0222c364;

void *func_02032c64(void *p);
void *func_02032c50(void *p);
extern UnkStruct_0222c3a8 data_ov003_0225f35c[];
int func_ov003_0222c16c(UnkStruct_0222c364 *e);

void *func_ov003_0222c3e0(UnkStruct_0222c3e0 *self)
{
    func_02032c64(self);
    self->unk_30 = 0;
    self->unk_34 = 0x1000;
    self->unk_38 = 0x1000;
    self->unk_3C = 0x1000;
    self->unk_40 = 0x1000;
    self->unk_44 = 0x1000;
    self->unk_48 = 0x1000;
    self->unk_4C = 0x1000;
    self->unk_50 = 0x1000;
    self->unk_54 = 0x1000;
    self->unk_58 = 0;
    return self;
}

void *func_ov003_0222c3d0(void *self)
{
    func_02032c50(self);
    return self;
}

void func_ov003_0222c3a8(Vec3 *src, int i)
{
    UnkStruct_0222c3a8 *e;
    Vec3 *q;
    if (i >= 0 && i < 4) {
        e = &data_ov003_0225f35c[i];
        q = &e->unk_4C;
        q->x = src->x;
        q->y = src->y;
        q->z = src->z;
    }
}

int func_ov003_0222c364(int i)
{
    UnkStruct_0222c364 *e;
    int st;
    if (i < 0 || i >= 4) {
        return 0;
    }
    e = &((UnkStruct_0222c364 *) data_ov003_0225f35c)[i];
    st = *(u8 *) ((char *) e + 0x30);
    if (st == 0 || (st == 2 && e->unk_58 > 0x64) || func_ov003_0222c16c(e) != 0) {
        return 0;
    }
    return 1;
}
