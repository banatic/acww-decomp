/* func_ov003_022278e0 @ 0x022278e0, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    char pad_00[0x48];
    int unk_48;
    char pad_4C[0x14];
    Vec3 unk_60;
    char pad_6C[0x38];
} UnkStruct_022278e0;
extern UnkStruct_022278e0 data_ov003_0225f4dc[];

int func_ov003_022278e0(Vec3 *out, int i)
{
    int r = 0;
    UnkStruct_022278e0 *e;
    Vec3 *q;
    if (i < 0 || i >= 4) {
        return 0;
    }
    e = &data_ov003_0225f4dc[i];
    if (e->unk_48 == 1) {
        q = &e->unk_60;
        out->x = q->x;
        out->y = q->y;
        out->z = q->z;
        r = 1;
    }
    return r;
}
