/* func_0201dfa0 @ 0x0201dfa0, 0xd4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Pair {
    u32 a;
    u32 b;
};

struct UnkStruct_0201dfa0;

struct UnkStruct_0201dfa0 {
    u8 pad_00[0x40];
    u32 unk_40;
    u8 pad_44[0x6c];
    void (UnkStruct_0201dfa0::*m_cb)(u8 *); // at 0xb0
    u8 pad_B8[0xe0];
    int unk_198; // at 0x198
};

extern "C" void func_0202da88(UnkStruct_0201dfa0 *self, void *arg);
extern "C" void func_0206844c(u32 a, u8 *b, u32 c);
extern "C" int func_020154b4(UnkStruct_0201dfa0 *self, u8 *p, int r2, int r3, int r4);
extern "C" void func_0202dbf0(UnkStruct_0201dfa0 *self, Pair p);
extern Pair data_020d9138;

extern unsigned char data_021c2244[];
extern unsigned char data_021c225c[];

extern "C" void func_0201dfa0(UnkStruct_0201dfa0 *self)
{
    u8 b0;
    u8 b1;
    u16 hval;
    u8 buf[8]; // used as 8-byte buffer for callbacks
    int val = self->unk_198;

    if (val >= 2) {
        func_0202da88(self, (void *) data_021c2244);
        if (self->m_cb) {
            (self->*self->m_cb)(buf);
        }
        b0 = buf[4];
        func_0206844c(self->unk_40, &b0, *(u32 *) (buf));
    } else if (val == 1) {
        func_0202da88(self, (void *) data_021c225c);
        if (self->m_cb) {
            (self->*self->m_cb)(buf);
        }
        b1 = buf[4];
        func_0206844c(self->unk_40, &b1, *(u32 *) (buf));
    } else {
        hval = 0x3818;
        func_020154b4(self, (u8 *) &hval, 0, 5, 0);
        func_0202dbf0(self, data_020d9138);
    }
}
