/* func_02027b58 @ 0x02027b58, 0x100 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02027b58;
typedef void (UnkStruct_02027b58::*PMF)(int *);

struct UnkStruct_02027b58_2 {
    int pad0[2];
    int unk_08;
};

struct UnkStruct_02027b58_3 {
    int a;
    int b;
};

struct UnkStruct_02027b58 {
    u8 pad0[0x40];
    UnkStruct_02027b58_2 *unk_40;
    u8 pad_44[0xb0 - 0x44];
    PMF cb;
    u8 pad_B8[0x124 - 0xb8];
    u16 unk_124;
};

struct UnkStruct_02027b58_4 {
    u8 unk_00;
    u8 pad0;
    u16 unk_02;
    int unk_04;
    u8 unk_08;
};

extern char data_021c2adc[];
extern char data_021c2af4[];
extern UnkStruct_02027b58_3 data_020d8e48;

extern "C" int func_0206fc6c(UnkStruct_02027b58 *p);
extern "C" int func_0202d9c4(UnkStruct_02027b58 *p);
extern "C" int func_0209bc40(int x);
extern "C" void func_0202da88(UnkStruct_02027b58 *p, char *s);
extern "C" int func_0206fc8c(void);
extern "C" void func_020984e8(void);
extern "C" int func_02099734(void);
extern "C" u16 *func_02098f48(int a, int b);
extern "C" void func_02098f0c(int a, u16 *b, int c, int d);
extern "C" void func_0206844c(UnkStruct_02027b58_2 *b, UnkStruct_02027b58_4 *l, int v);
extern "C" void func_0202dbdc(UnkStruct_02027b58 *p, UnkStruct_02027b58_3 c);
extern "C" void func_02015330(UnkStruct_02027b58 *p, u16 *q, int m, int n, int o);

extern "C" void func_02027b58(UnkStruct_02027b58 *p)
{
    UnkStruct_02027b58_4 loc;
    int mode;
    int r6;
    int r7;
    UnkStruct_02027b58_2 *b;

    if (func_0206fc6c(p) == 0) {
        if (func_0209bc40(func_0202d9c4(p)) == 0x13) {
            b = p->unk_40;
            if (b) {
                b->unk_08 = 1;
            }
        }
        func_0202da88(p, data_021c2adc);
    } else {
        mode = 2;
        r6 = func_0206fc8c();
        func_020984e8();
        r7 = func_02099734();
        switch (func_0209bc40(func_0202d9c4(p))) {
            case 0xa:
                p->unk_124 = *func_02098f48(r7, r6);
                loc.unk_02 = 0xfff1;
                func_02098f0c(r7, &loc.unk_02, r6, 0);
                break;
            case 0x13:
                func_0202dbdc(p, data_020d8e48);
                p->unk_124 = 0x1565;
                mode = 0;
                break;
        }
        func_0202da88(p, data_021c2af4);
        func_02015330(p, &p->unk_124, mode, 4, 0);
    }
    if (p->cb) {
        (p->*(p->cb))(&loc.unk_04);
    }
    loc.unk_00 = loc.unk_08;
    func_0206844c(p->unk_40, &loc, loc.unk_04);
}
