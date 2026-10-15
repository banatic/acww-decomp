/* func_ov090_02298fac @ 0x02298fac, 0xac bytes, Thumb, module ov090
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 b[0x60];
} UnkStruct_02298fac;
typedef struct UnkStruct_02298fac_2 UnkStruct_02298fac_2;
struct UnkStruct_02298fac_2 {
    u8 unk_00[0x93];
    u8 unk_93;
    u8 p1[2];
    u8 unk_96;
    u8 p2[5];
    u8 unk_9C[0xd4 - 0x9c];
    u8 unk_D4[0x10c - 0xd4];
    u8 unk_10C[0x144 - 0x10c];
    u8 unk_144[0x944 - 0x144];
    UnkStruct_02298fac unk_944[8];
    u8 p3[0x1144 - 0xc44];
    u8 unk_1144[0x20];
};
extern int func_020b9c10(u8 *, u8 *, int, int, int, int);
extern int func_020b9a18(u8 *, UnkStruct_02298fac *, u8 *, int, int, int, int, int);
extern int func_02064328(u8 *, void *, int);
extern int func_02064af4(u8 *, u8 *, int);
extern int func_020b9b6c(u8 *, u8 *, int, int);
extern u8 data_ov090_02299900[];

void func_ov090_02298fac(UnkStruct_02298fac_2 *self, int idx)
{
    u8 buf[0x24];
    UnkStruct_02298fac *e;
    int t;

    self->unk_93 = (u8) idx;
    if ((unsigned int) idx > 7) {
        return;
    }
    if (idx == self->unk_96) {
        return;
    }
    func_020b9c10(self->unk_9C, self->unk_144, 8, 0x80, 0x80, 0xbf);
    e = &self->unk_944[idx];
    t = idx * 3 + 0x80;
    func_020b9a18(self->unk_D4, e, (u8 *) e + 0x400, 8, t, t + 2, t + 0x20, t + 0x22);
    func_02064328(buf, data_ov090_02299900, idx);
    func_02064af4(buf, self->unk_1144, 0x20);
    func_020b9b6c(self->unk_10C, self->unk_1144, 8, 0xf);
    self->unk_96 = (u8) idx;
}
