/* player_fish_5: 4 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0222ab14 @ 0x0222ab14, 0x38 bytes, Thumb
 * func_ov003_0222aae8 @ 0x0222aae8, 0x2c bytes, Thumb
 * func_ov003_0222aaa0 @ 0x0222aaa0, 0x48 bytes, Thumb
 * func_ov003_0222aa50 @ 0x0222aa50, 0x50 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x3c];
    u8 unk_80;
    char pad_81[0x23];
} UnkStruct_0222ab14;

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x3c];
    u8 unk_80;
    char pad_81[0x23];
} UnkStruct_0222aae8;

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    char pad_00[0x54];
    Vec3 unk_54;
    char pad_60[0x24];
    Vec3 unk_84;
    char pad_90[0x14];
} UnkStruct_0222aa50;

extern UnkStruct_0222ab14 data_ov003_0225f4dc[];
extern u8 data_020cb784[];
extern u8 data_ov003_0223c026[];

int func_ov003_0222ab14(char *p)
{
    int r = 0;
    s8 k;
    if (p == 0) {
        return r;
    }
    k = *(s8 *) (p + 0x227);
    if (k == -1) {
        return r;
    }
    {
        UnkStruct_0222ab14 *e = &data_ov003_0225f4dc[k];
        if (e->unk_80 != 0) {
            r = 1;
        }
    }
    return r;
}

int func_ov003_0222aae8(char *p)
{
    s8 k;
    if (p == 0) {
        return 0;
    }
    k = *(s8 *) (p + 0x227);
    if (k == -1) {
        return 0;
    }
    {
        UnkStruct_0222aae8 *e = &((UnkStruct_0222aae8 *) data_ov003_0225f4dc)[k];
        e->unk_40 = 4;
    }
    return 1;
}

void func_ov003_0222aaa0(Vec3 *out, int i)
{
    int k, v, q;
    if (i < 0 || i >= 0x3b) {
        out->x = 0x1000;
        out->y = 0x1000;
        out->z = 0x1000;
    } else {
        k = data_020cb784[i * 6];
        v = data_ov003_0223c026[k * 0x14];
        q = (v << 12) / 100;
        out->x = q;
        out->y = q;
        out->z = q;
    }
}

int func_ov003_0222aa50(char *p, Vec3 *a, Vec3 *b)
{
    s8 k;
    UnkStruct_0222aa50 *e;
    Vec3 *q;
    if (p == 0) {
        return 0;
    }
    k = *(s8 *) (p + 0x227);
    if (k == -1) {
        return 0;
    }
    e = &((UnkStruct_0222aa50 *) data_ov003_0225f4dc)[k];
    q = &e->unk_54;
    q->x = a->x;
    q->y = a->y;
    q->z = a->z;
    q = &e->unk_84;
    q->x = b->x;
    q->y = b->y;
    q->z = b->z;
    return 1;
}
