/* func_0202add4 @ 0x0202add4, 0xcc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Other {
    u8 pad[0x824];
    u8 unk_824;
    u8 pad2[0x830 - 0x825];
    u32 unk_830;
};

struct UnkStruct_0202add4;
typedef void (UnkStruct_0202add4::*PMF)(void *);

struct UnkStruct_0202add4 {
    u8 pad_00[0x40];
    u32 unk_40;
    u8 pad_44[0xb0 - 0x44];
    PMF pmf;
    u8 pad2[0x100 - 0xb8];
    Other *unk_100;
    u8 pad_104[0x12c - 0x104];
    void *unk_12C;
};

extern int data_021c274c;

extern "C" int func_0206fc6c(UnkStruct_0202add4 *self);
extern "C" void func_0202da88(UnkStruct_0202add4 *self, void *arg);
extern "C" void *func_0206fc44(void);
extern "C" void func_02080a4c(void *dst, void *src, int n);
extern "C" int func_02081edc(void *p);
extern "C" void func_02081ac8(void *p, void *q, int n);
extern "C" void *func_020984e8(void *p);
extern "C" void *func_02099870(void *p);
extern "C" void func_02080108(void *a, void *b, int n, void *c);
extern "C" void func_0206844c(u32 base, void *local, u32 data);

extern "C" void func_0202add4(UnkStruct_0202add4 *self)
{
    struct UnkStruct_0202add4_2 {
        u8 flag;
        u8 pad[3];
        u32 data;
        u8 other;
    };
    UnkStruct_0202add4_2 local;

    if (func_0206fc6c(self)) {
        void *word = (void *) self->unk_100->unk_830;
        func_0202da88(self, (void *) &data_021c274c);
        if (self->unk_100->unk_824 == 0) {
            func_02080a4c(word, func_0206fc44(), 4);
        } else {
            if (self->unk_12C != 0 && func_02081edc(self->unk_12C) != 0) {
                func_02081ac8(self->unk_12C, func_0206fc44(), 0xa);
            } else {
                void *tmp = func_0206fc44();
                void *tmp2 = func_020984e8(tmp);
                void *tmp3 = func_02099870(tmp2);
                func_02080108(word, tmp, 0xa, tmp3);
            }
        }
    }
    if (self->pmf) {
        (self->*self->pmf)(&local.data);
    }
    local.flag = local.other;
    func_0206844c(self->unk_40, &local, local.data);
}
