/* func_02024f40 @ 0x02024f40, 0xa4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct TwoWords {
    u32 a;
    u32 b;
};

struct UnkStruct_02024f40 {
    u8 pad[8];
    u32 unk_08;
};

struct UnkStruct_02024f40_2 {
    u8 pad_00[0x40];
    struct UnkStruct_02024f40 *unk_40;
    u8 pad_44[0xb0 - 0x44];
    void (UnkStruct_02024f40_2::*pmf)(void *);
    u8 pad_B8[0x124 - 0xb8];
    u16 unk_124;
};

struct Locals {
    u8 dst;
    u8 pad[3];
    u32 word;
    u8 unk_08;
};

extern "C" int func_0206fc6c(void);
extern "C" int func_0206fc8c(void);
extern "C" void func_0202da88(void *p, unsigned int lit);
extern "C" int func_020984e8(void);
extern "C" int func_02099734(int);
extern "C" void *func_02098f48(int a, int b);
extern "C" int func_02015330(void *a, void *b, int c, int d, int e);
extern "C" void func_0202dbdc(void *p, struct TwoWords tw);
extern "C" void func_0206844c(void *a, void *b, unsigned int c);
extern const u32 data_020d9200[2];

extern unsigned char data_021c2adc[];

extern "C" void func_02024f40(struct UnkStruct_02024f40_2 *p)
{
    int res = func_0206fc6c();
    if (res == 0) {
        if (p->unk_40) {
            p->unk_40->unk_08 = 1;
        }
        func_0202da88(p, (unsigned int) data_021c2adc);

        struct Locals locals;
        if (p->pmf) {
            (p->*p->pmf)(&locals.word);
        }
        locals.dst = locals.unk_08;
        func_0206844c(p->unk_40, &locals, locals.word);
    } else {
        int a = func_0206fc8c();
        void *ptr = func_02098f48(func_02099734((int) func_020984e8()), a);
        p->unk_124 = *(u16 *) ptr;
        func_02015330(p, &p->unk_124, 0, 4, 0);
        func_0202dbdc(p, *(struct TwoWords *) &data_020d9200);
    }
}
