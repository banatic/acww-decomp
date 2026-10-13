/* func_0209036c @ 0x0209036c, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0209036c {
    u32 unk_00;
    u8 pad_04[0xc];
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
    u8 pad_22[0x24 - 0x22];
    u8 unk_24[0xe0 - 0x24];
    u32 unk_E0;
    u32 unk_E4;
    u8 pad_E8[0x108 - 0xe8];
    u8 unk_108[0x128 - 0x108];
    u8 unk_128[1];
};

extern void func_02055060(void *, int, int, int, int, int);
extern void func_02056478(void *, int, int, int, int);
extern int NNS_G3dGetJntAnmSet(u32);
extern int func_02107b44(int, int);
extern int NNS_G3dGetMatCAnmSet(u32);
extern int func_02107b80(int, int);
extern int NNS_G3dGetVisAnmSet(u32);
extern int func_02107cf0(int, int);

void func_0209036c(struct UnkStruct_0209036c *self, char *base, void (*callback)(struct UnkStruct_0209036c *))
{
    char *p;
    int t;

    self->unk_00 = 1;
    self->unk_10 = 0x1000;
    self->unk_14 = 0x1000;
    self->unk_18 = 0x1000;
    self->unk_1C = 0;
    self->unk_1E = 0;
    self->unk_20 = 0;

    p = base + 0x524;
    t = func_02107b44(NNS_G3dGetJntAnmSet(*(u32 *) p), 0);
    func_02055060(self->unk_24, t, 1, 0x1000, 0, 0);

    if (self->unk_E0) {
        t = func_02107b80(NNS_G3dGetMatCAnmSet(*(u32 *) (p + 4)), 0);
        func_02056478(self->unk_108, t, 1, 0x1000, 0);
    }

    if (self->unk_E4) {
        t = func_02107cf0(NNS_G3dGetVisAnmSet(*(u32 *) (p + 8)), 0);
        func_02056478(self->unk_128, t, 1, 0x1000, 0);
    }

    callback(self);
}
