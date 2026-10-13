/* func_02023fc8 @ 0x02023fc8, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct LocalSub {
    u32 c;
    u8 d;
};

struct UnkStruct_02023fc8_2 {
    u8 a;
    u16 b;
    LocalSub sub;
};

class UnkStruct_02023fc8 {
  public:
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0x6c];
    void (UnkStruct_02023fc8::*pmf)(LocalSub *);
    char pad_B8[0x6c];
    u16 unk_124;
};

extern "C" {
void *func_0206fc6c(UnkStruct_02023fc8 *self);
void *func_0206fc8c(void *arg);
void *func_020984e8(void *arg);
void *func_02099734(void *arg);
u16 *func_02098f48(void *arg1, void *arg2);
void func_0209a088(u16 *addr, int zero, void *arg);
void func_0202da88(UnkStruct_02023fc8 *self, void *addr);
void func_02015330(UnkStruct_02023fc8 *self, u16 *ptr, int zero, int five, int stackarg);
void func_0206844c(void *field40, UnkStruct_02023fc8_2 *local, u32 c);
}

extern unsigned char data_021c2adc[];
extern unsigned char data_021c2efc[];

extern "C" void func_02023fc8(UnkStruct_02023fc8 *self)
{
    UnkStruct_02023fc8_2 local;
    void *v1 = func_0206fc6c(self);
    if (v1 != 0) {
        void *v2 = func_0206fc8c(v1);
        void *v3 = func_020984e8(v2);
        void *v4 = func_02099734(v3);
        u16 *p = func_02098f48(v4, v2);
        self->unk_124 = *p;
        local.b = 0xfff1;
        func_0209a088(&local.b, 0, v2);
        func_0202da88(self, (void *) data_021c2efc);
        func_02015330(self, &self->unk_124, 0, 5, 0);
    } else {
        func_0202da88(self, (void *) data_021c2adc);
    }
    if (self->pmf) {
        (self->*self->pmf)(&local.sub);
    }
    local.a = local.sub.d;
    func_0206844c(self->unk_40, &local, local.sub.c);
}
