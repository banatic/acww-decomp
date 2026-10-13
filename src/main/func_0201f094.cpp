/* func_0201f094 @ 0x0201f094, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern "C" {
}

class UnkStruct_0201f094 {
  public:
    u8 pad_00[0x40];
    void *unk_40; // 0x040
    u8 pad_44[0xb0 - 0x44];
    typedef void (UnkStruct_0201f094::*PMF)(void *arg);
    PMF pmf; // 0x0b0
    u8 pad_B8[0x124 - 0xb8];
    u16 unk_124; // 0x124
};

struct UnkStruct_0201f094_2 {
    u8 a;      // 0x00
    u8 pad_01; // 0x01
    u16 b;     // 0x02
    u32 c;     // 0x04
    u8 d;      // 0x08
};

struct Pair {
    u32 a, b;
};

extern "C" {
extern u32 data_020d9048[2];
extern int func_0206fc6c(UnkStruct_0201f094 *self);
extern void *func_0206fc8c(int arg);
extern void *func_020984e8(void *arg);
extern void *func_02099734(void *arg);
extern u16 *func_02098f48(void *a, void *b);
extern void func_0209a088(u16 *p, int x, void *y);
extern void func_02015330(UnkStruct_0201f094 *self, u16 *field, int a, int b, int c);
extern void func_0202dbdc(UnkStruct_0201f094 *self, struct Pair pair);
extern void func_0202da88(UnkStruct_0201f094 *self, void *addr);
extern void func_0206844c(void *field, UnkStruct_0201f094_2 *local, u32 c);
}

extern unsigned char data_021c25ec[];

extern "C" void func_0201f094(UnkStruct_0201f094 *self)
{
    UnkStruct_0201f094_2 local;
    int r;

    r = func_0206fc6c(self);
    if (r != 0) {
        void *p = func_0206fc8c(r);
        void *t = func_020984e8(p);
        void *q = func_02099734(t);
        u16 *res = func_02098f48(q, p);

        self->unk_124 = *res;

        local.b = 0xfff1;
        func_0209a088(&local.b, 0, p);
        func_02015330(self, &self->unk_124, 0, 5, 0);
        func_0202dbdc(self, *(struct Pair *) data_020d9048);
        return;
    }

    func_0202da88(self, (void *) data_021c25ec);
    if (self->unk_40 != 0) {
        *(int *) ((char *) self->unk_40 + 8) = 1;
    }
    if (self->pmf != 0) {
        (self->*self->pmf)(&local.c);
    }
    local.a = local.d;
    func_0206844c(self->unk_40, &local, local.c);
}
