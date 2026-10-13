/* func_ov003_02229100 @ 0x02229100, 0x84 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    char pad_00[0x40];
    int unk_40;
    char p2[0x60 - 0x44];
    Vec3 unk_60;
    char p3[0xa4 - 0x6c];
} UnkStruct_02229100;

extern UnkStruct_02229100 data_ov003_0225f4dc[];
extern int func_ov003_0222a960(unsigned i, int k);

int func_ov003_02229100(void *a0, unsigned i)
{
    UnkStruct_02229100 *e;
    volatile Vec3 v;
    Vec3 *s;
    int st;
    if (i >= 4) {
        return 0;
    }
    e = &data_ov003_0225f4dc[i];
    s = &e->unk_60;
    v.x = s->x;
    v.y = s->y;
    v.z = s->z;
    st = e->unk_40;
    if (st == 3) {
        if (func_ov003_0222a960(i, 0) == 0) {
            e->unk_40 = 4;
            return 0;
        }
    } else if (st == 0) {
        if (func_ov003_0222a960(i, 1) == 0) {
            e->unk_40 = 4;
            return 0;
        }
    } else if (st == 2) {
        e->unk_40 = 3;
        if (func_ov003_0222a960(i, 0) == 0) {
            e->unk_40 = 4;
            return 0;
        }
    }
    return 1;
}
