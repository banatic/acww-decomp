/* func_ov004_02238704 @ 0x02238704, 0xac bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02238704 {
    int x, y, z;
};

struct UnkStruct_02238704_2 {
    u8 pad_00[0x158];
    int unk_158;
    u8 pad_15C[0x1a8 - 0x15c];
    int unk_1A8;
    int unk_1AC;
    int unk_1B0;
    u8 pad_1B4[0x1fc - 0x1b4];
    int unk_1FC;
    u8 pad_200[0x208 - 0x200];
    unsigned short unk_208;
    u8 pad_20A[0x211 - 0x20a];
    u8 unk_211;
};

extern struct UnkStruct_02238704 data_ov004_02258a30;
extern void func_020042c0(void *p, struct UnkStruct_02238704 *v);
extern void func_ov004_02238698(struct UnkStruct_02238704_2 *self);
extern void func_ov004_02238608(struct UnkStruct_02238704_2 *self);

void func_ov004_02238704(struct UnkStruct_02238704_2 *self)
{
    struct {
        struct UnkStruct_02238704 t;
        struct UnkStruct_02238704 u;
    } o;

    o.t.x = data_ov004_02258a30.x;
    o.t.y = data_ov004_02258a30.y;
    o.t.z = data_ov004_02258a30.z;
    self->unk_1A8 = o.t.x;
    self->unk_1AC = o.t.y;
    self->unk_1B0 = o.t.z;
    o.u.x = self->unk_1A8;
    o.u.y = self->unk_1AC;
    o.u.z = self->unk_1B0;
    func_020042c0(&self->unk_1FC, &o.u);
    switch (self->unk_211) {
        case 2:
            func_ov004_02238698(self);
            break;
        case 4:
            func_ov004_02238608(self);
            break;
        case 6:
            if (self->unk_158 >= self->unk_208) {
                self->unk_211 = 2;
                self->unk_158 = 0;
            }
            break;
    }
    self->unk_158 = self->unk_158 + 1;
}
