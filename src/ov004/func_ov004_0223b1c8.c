/* func_ov004_0223b1c8 @ 0x0223b1c8, 0x64 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0223b1c8 {
    int x, y, z;
};
struct UnkStruct_0223b1c8_2 {
    int w[12];
};

struct UnkStruct_0223b1c8_3 {
    u8 unk_00;
    u8 unk_01;
};

struct UnkStruct_0223b1c8_4 {
    u8 pad[0x4c];
    struct UnkStruct_0223b1c8 unk_4C;
};

struct UnkStruct_0223b1c8_5 {
    u8 pad[0x2c];
    struct UnkStruct_0223b1c8_2 *unk_2C;
};

struct UnkStruct_0223b1c8_6 {
    struct UnkStruct_0223b1c8_3 *unk_00;
    struct UnkStruct_0223b1c8_5 *unk_04;
    u8 pad[0xb4 - 8];
    struct UnkStruct_0223b1c8_4 *unk_B4;
};

extern struct UnkStruct_0223b1c8_2 data_021fbe48;
extern struct UnkStruct_0223b1c8_2 *func_ov004_0223b138(struct UnkStruct_0223b1c8_2 *p);
extern void MTX_MultVec43(struct UnkStruct_0223b1c8 *a, struct UnkStruct_0223b1c8_2 *m, struct UnkStruct_0223b1c8 *out);
extern void func_ov004_0223b128(struct UnkStruct_0223b1c8_2 *p, struct UnkStruct_0223b1c8 *out);

void func_ov004_0223b1c8(struct UnkStruct_0223b1c8_6 *a)
{
    struct UnkStruct_0223b1c8 v;
    struct UnkStruct_0223b1c8 out;
    struct UnkStruct_0223b1c8_4 *b;
    struct UnkStruct_0223b1c8 *q;
    struct UnkStruct_0223b1c8_2 *m;
    struct UnkStruct_0223b1c8_2 *r;

    if (a == 0) {
        return;
    }
    if (a->unk_00->unk_01 != 0) {
        return;
    }
    b = a->unk_B4;
    q = &b->unk_4C;
    v.x = b->unk_4C.x;
    v.y = q->y;
    v.z = q->z;
    m = a->unk_04->unk_2C;
    if (m == 0) {
        return;
    }
    r = func_ov004_0223b138(m);
    data_021fbe48 = *r;
    MTX_MultVec43(&v, &data_021fbe48, &out);
    func_ov004_0223b128(m, &out);
}
