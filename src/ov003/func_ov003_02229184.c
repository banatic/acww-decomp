/* func_ov003_02229184 @ 0x02229184, 0x44 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[4];
    int unk_48;
    char pad_4C[0x14];
    Vec3 unk_60;
    char pad_6C[0x24];
    int unk_90;
    char pad_94[0x10];
} UnkStruct_02229184;
extern UnkStruct_02229184 data_ov003_0225f4dc[];

int func_ov003_02229184(void *a, unsigned int i, int k, Vec3 *v)
{
    UnkStruct_02229184 *e;
    Vec3 *q;
    if (i >= 4) {
        return 0;
    }
    e = &data_ov003_0225f4dc[i];
    if (e->unk_40 != 0) {
        return 0;
    }
    q = &e->unk_60;
    q->x = v->x;
    q->y = v->y;
    q->z = v->z;
    e->unk_90 = k;
    e->unk_40 = 1;
    e->unk_48 = 2;
    return 1;
}
