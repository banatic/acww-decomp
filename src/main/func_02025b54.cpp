/* func_02025b54 @ 0x02025b54, 0xa4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02025b54 {
    u32 a;
    u8 b;
};

struct UnkStruct_02025b54_2 {
    u8 pad_00[8];
    u32 flag;
};

typedef struct {
    u32 a;
    u32 b;
} Pair;

class UnkStruct_02025b54_3 {
  public:
    char pad_00[0x40];
    UnkStruct_02025b54_2 *unk_40;
    char pad_44[0x6c];
    void (UnkStruct_02025b54_3::*pmf)(UnkStruct_02025b54 *);
    char pad_B8[0x6c];
    u16 unk_124;
};

extern int data_021c2adc;
extern Pair data_020d92e8;

extern "C" int func_0206fc6c(void);
extern "C" void func_0202da88(UnkStruct_02025b54_3 *self, void *arg);
extern "C" void func_0206844c(UnkStruct_02025b54_2 *sub, u8 *byte, u32 word);
extern "C" u32 func_0206fc8c(void);
extern "C" int func_020984e8(void);
extern "C" u32 func_02099734(int);
extern "C" u16 *func_02098f48(u32 a, u32 b);
extern "C" int func_02015330(UnkStruct_02025b54_3 *self, u16 *ptr, u32 a, u32 b, u32 c);
extern "C" void func_0202dbdc(UnkStruct_02025b54_3 *self, Pair p);

extern "C" void func_02025b54(UnkStruct_02025b54_3 *self)
{
    if (func_0206fc6c() == 0) {
        if (self->unk_40) {
            self->unk_40->flag = 1;
        }
        func_0202da88(self, &data_021c2adc);

        u8 byte;
        UnkStruct_02025b54 tmp;

        if (self->pmf) {
            (self->*self->pmf)(&tmp);
        }
        byte = tmp.b;
        func_0206844c(self->unk_40, &byte, tmp.a);
    } else {
        u32 r5 = func_0206fc8c();
        u32 a = func_02099734((int) func_020984e8());
        u16 w = *func_02098f48(a, r5);
        self->unk_124 = w;
        func_02015330(self, &self->unk_124, 0, 4, 0);
        func_0202dbdc(self, data_020d92e8);
    }
}
