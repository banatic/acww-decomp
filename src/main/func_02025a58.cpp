/* func_02025a58 @ 0x02025a58, 0xfc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern "C" {
}

struct SubOut {
    u32 data;
    u8 flag;
};

struct UnkStruct_02025a58 {
    u8 pad_00[8];
    int unk_08;
};

struct Whole {
    u8 kind;
    u8 pad1;
    u16 val;
    SubOut sub;
};

class UnkStruct_02025a58_2 {
  public:
    u8 pad_00[0x40];
    UnkStruct_02025a58 *unk_40;
    u8 pad1[0xb0 - 0x44];
    void (UnkStruct_02025a58_2::*pmf)(SubOut *);
    u8 pad_B8[0x124 - 0xb8];
    u16 unk_124;
    u8 pad_126[0x164 - 0x126];
    void *unk_164;
};

struct Locals {
    Whole w;
    u32 ab[2];
};

extern "C" {
void func_0209e474(u32 *p);
int func_0204c878(u16 *p);
u16 *func_0209b8c4(void *p);
void func_0202da88(UnkStruct_02025a58_2 *self, const char *s);
void func_02015de4(UnkStruct_02025a58_2 *self, void *p, int a, int b);
void func_0206844c(UnkStruct_02025a58 *p, void *w, u32 data);
}

extern unsigned char data_021c2d1c[];
extern unsigned char data_021c2d4c[];
extern unsigned char data_021c2d64[];

extern "C" void func_02025a58(UnkStruct_02025a58_2 *self)
{
    Locals loc;
    int r4 = 0;
    int r6;
    loc.ab[0] = 0;
    loc.ab[1] = 0;
    r6 = r4;
    func_0209e474(loc.ab);

    if (self->unk_124 != 0xfff1) {
        r4 = func_0204c878(&self->unk_124);
    }

    loc.w.val = *func_0209b8c4(self->unk_164);
    if (loc.w.val != 0xfff1) {
        r6 = func_0204c878(&loc.w.val);
    }

    if (r4 == r6) {
        func_0202da88(self, (const char *) data_021c2d64);
    } else if (r4 > r6) {
        func_0202da88(self, (const char *) data_021c2d1c);
    } else {
        func_0202da88(self, (const char *) data_021c2d4c);
    }

    if (self->unk_124 != 0xfff1) {
        func_02015de4(self, &self->unk_124, 2, 7);
    }

    if (loc.w.val != 0xfff1) {
        func_02015de4(self, &loc.w.val, 3, 7);
    }

    if (self->unk_40 != 0) {
        self->unk_40->unk_08 = 1;
    }

    if (self->pmf) {
        (self->*self->pmf)(&loc.w.sub);
    }

    loc.w.kind = loc.w.sub.flag;
    func_0206844c(self->unk_40, &loc.w, loc.w.sub.data);
}
