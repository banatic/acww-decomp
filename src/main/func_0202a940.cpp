/* func_0202a940 @ 0x0202a940, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0202a940 {
    u8 a;
    u32 b;
    u8 c;
};

struct Pair {
    u32 a;
    u32 b;
};

struct UnkStruct_0202a940_2 {
    u8 buf[0x20];
    s8 pair[2];
};

class UnkStruct_0202a940_3 {
  public:
    char pad_00[0x40];
    u32 unk_40;
    char pad_44[0xb0 - 0x44];
    void (UnkStruct_0202a940_3::*pmf)(u32 *arg);
    char pad_B8[0x12c - 0xb8];
    u32 unk_12C;
};

extern "C" {
int func_02081d20(u32);
void func_0201cfb4(UnkStruct_0202a940_3 *, UnkStruct_0202a940_2 *);
void func_0201cf90(UnkStruct_0202a940_3 *, UnkStruct_0202a940_2 *, int, int, int, char *);
void func_0201cec8(UnkStruct_0202a940_3 *, UnkStruct_0202a940_2 *);
extern Pair data_020d8f68;
void func_0202da74(UnkStruct_0202a940_3 *, Pair);
void func_02068388(u32, int);
void func_0202da88(UnkStruct_0202a940_3 *, char *);
int func_02068484(u32, UnkStruct_0202a940 *, u32);
extern char data_021c27c4;
extern char data_021c280c;
}

extern "C" void func_0202a940(UnkStruct_0202a940_3 *self)
{
    UnkStruct_0202a940 out;
    UnkStruct_0202a940_2 d;

    if (self->unk_12C != 0 && func_02081d20(self->unk_12C) >= 0x40) {
        func_0201cfb4(self, &d);
        func_0201cf90(self, &d, 0, 0x47, 0x47, &data_021c27c4);
        func_0201cf90(self, &d, 1, 0x48, 0x48, &data_021c280c);
        d.pair[0] = 2;
        d.pair[1] = -1;
        func_0201cec8(self, &d);
        func_0202da74(self, data_020d8f68);
        func_02068388(self->unk_40, 1);
    } else {
        func_0202da88(self, &data_021c280c);
        if (self->pmf) {
            (self->*self->pmf)(&out.b);
        }
        out.a = out.c;
        func_02068484(self->unk_40, &out, out.b);
    }
}
