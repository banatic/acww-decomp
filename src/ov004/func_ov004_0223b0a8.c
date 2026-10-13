/* func_ov004_0223b0a8 @ 0x0223b0a8, 0x80 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0223b0a8 {
    int x, y, z;
};
struct UnkStruct_0223b0a8_2 {
    int w[12];
};

struct UnkStruct_0223b0a8_3 {
    u8 unk_00;
    u8 pad_01[3];
    int unk_04;
    int unk_08;
    int unk_0C;
    u8 pad_10[0x2c - 0x10];
    u8 unk_2C[0x90 - 0x2c];
    struct UnkStruct_0223b0a8_2 unk_90;
};

extern struct UnkStruct_0223b0a8_2 data_021fbe48;
extern void func_02055060(void *p, int b, int c, int d, int e, int f);
extern void func_020e96c8(struct UnkStruct_0223b0a8_2 *m, int x, int y, int z);
extern void func_020e9744(struct UnkStruct_0223b0a8_2 *m, s16 a);

int func_ov004_0223b0a8(struct UnkStruct_0223b0a8_3 *a, int b, u8 *c, struct UnkStruct_0223b0a8 *d, s16 e)
{
    if (*c == 0 && a->unk_00 == 0 && b != 0) {
        func_02055060(a->unk_2C, b, 1, 0x1000, 0, 0);
        a->unk_00 = 1;
        *c = a->unk_00;
        a->unk_04 = d->x;
        a->unk_08 = d->y;
        a->unk_0C = d->z;
        func_020e96c8(&data_021fbe48, d->x, d->y, d->z);
        func_020e9744(&data_021fbe48, e);
        a->unk_90 = data_021fbe48;
        return 1;
    }
    return 0;
}
