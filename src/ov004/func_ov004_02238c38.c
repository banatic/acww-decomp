/* func_ov004_02238c38 @ 0x02238c38, 0xe0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02238c38 {
    int x, y, z;
};
struct UnkStruct_02238c38_2 {
    int w[12];
};
struct UnkStruct_02238c38_3 {
    u8 unk_00[0x11];
};

struct UnkStruct_02238c38_4 {
    u8 pad_00[0xc8];
    struct UnkStruct_02238c38_2 unk_C8;
    u8 pad_F8[0x15c - 0xf8];
    int unk_15C;
    u8 pad_160[0x1a8 - 0x160];
    int unk_1A8;
    int unk_1AC;
    int unk_1B0;
};

extern struct UnkStruct_02238c38_3 data_ov004_02247924[];
extern struct UnkStruct_02238c38_2 data_021fbe48;
extern int data_ov004_022593a8;
extern int data_ov004_022593b0;
extern int data_ov004_022593bc;
extern int data_ov004_022593c0;
extern void MTX_MultVec43(struct UnkStruct_02238c38 *a, struct UnkStruct_02238c38_2 *m, struct UnkStruct_02238c38 *out);

void func_ov004_02238c38(struct UnkStruct_02238c38_4 *self, struct UnkStruct_02238c38 *out)
{
    struct UnkStruct_02238c38 a;
    struct UnkStruct_02238c38 b;
    struct UnkStruct_02238c38 r1;
    struct UnkStruct_02238c38 r2;
    int i;
    int *p;

    i = self->unk_15C;
    if ((data_ov004_022593bc & 1) == 0) {
        data_ov004_022593b0 = (data_ov004_02247924[i].unk_00[2] << 12) >> 7;
        data_ov004_022593bc |= 1;
    }
    if ((data_ov004_022593c0 & 1) == 0) {
        data_ov004_022593a8 = (data_ov004_02247924[i].unk_00[3] << 12) >> 7;
        data_ov004_022593c0 |= 1;
    }
    a.x = 0;
    a.y = data_ov004_022593b0;
    a.z = 0;
    b.x = 0;
    b.y = 0;
    b.z = data_ov004_022593a8;
    data_021fbe48 = self->unk_C8;
    MTX_MultVec43(&a, &data_021fbe48, &r1);
    MTX_MultVec43(&b, &data_021fbe48, &r2);
    p = &self->unk_1A8;
    out->x = (p[0] + r1.x) >> 1;
    out->z = (p[2] + r1.z) >> 1;
    if (r2.y < p[1]) {
        out->y = r2.y;
    } else {
        out->y = p[1];
    }
}
