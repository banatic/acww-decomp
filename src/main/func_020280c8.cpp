/* func_020280c8 @ 0x020280c8, 0x128 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_020280c8;
typedef void (UnkStruct_020280c8::*PMF)(int *);

struct UnkStruct_020280c8_2 {
    int pad0[2];
    int unk_08;
};
struct UnkStruct_020280c8_3 {
    u8 pad_00[0x830];
    void *unk_830;
};
struct UnkStruct_020280c8_4 {
    int a;
    int b;
};

struct UnkStruct_020280c8 {
    u8 pad0[0x40];
    UnkStruct_020280c8_2 *unk_40;
    u8 pad_44[0xb0 - 0x44];
    PMF cb;
    u8 pad_B8[0x100 - 0xb8];
    UnkStruct_020280c8_3 *unk_100;
    u8 pad_104[0x124 - 0x104];
    u16 unk_124;
    u8 pad_126[0x160 - 0x126];
    void *unk_160;
};

struct UnkStruct_020280c8_5 {
    u8 unk_00;
    u8 pad0;
    u16 unk_02;
    int unk_04;
    u8 unk_08;
};

extern char data_021c2a7c[];
extern char data_021c2a94[];
extern UnkStruct_020280c8_4 data_020d8f08;
extern char data_021e5a2c[];

extern "C" int func_020984e8(void);
extern "C" int func_02099734(int);
extern "C" int func_0202d9c4(UnkStruct_020280c8 *p);
extern "C" int func_0209bc40(int x);
extern "C" u16 *func_0209bb70(int x);
extern "C" int func_0202d794(int a, u16 *b);
extern "C" int func_02098f0c(int a, u16 *b, int c, int d);
extern "C" void func_0202da88(UnkStruct_020280c8 *p, char *s);
extern "C" int func_02068484(UnkStruct_020280c8_2 *b, UnkStruct_020280c8_5 *l, int v);
extern "C" int func_02015330(UnkStruct_020280c8 *p, u16 *q, int m, int n, int o);
extern "C" void func_0202dbf0(UnkStruct_020280c8 *p, UnkStruct_020280c8_4 c);
extern "C" int func_0208150c(void *x);
extern "C" int func_0209b4cc(void *x, int y);
extern "C" void func_0207bae8(char *s, int a, int b, int c);

extern "C" void func_020280c8(UnkStruct_020280c8 *p)
{
    UnkStruct_020280c8_5 loc;
    int r6;
    int idx;
    int a;
    int b;

    r6 = func_02099734((int) func_020984e8());
    switch (func_0209bc40(func_0202d9c4(p))) {
        case 0xa:
            idx = func_0202d794(r6, func_0209bb70(func_0202d9c4(p)));
            if (idx != -1) {
                p->unk_124 = *func_0209bb70(func_0202d9c4(p));
                loc.unk_02 = 0xfff1;
                func_02098f0c(r6, &loc.unk_02, idx, 0);
                func_0202da88(p, data_021c2a7c);
            } else {
                func_0202da88(p, data_021c2a94);
            }
            if (p->cb) {
                (p->*(p->cb))(&loc.unk_04);
            }
            loc.unk_00 = loc.unk_08;
            func_02068484(p->unk_40, &loc, loc.unk_04);
            break;
        case 0x13:
            p->unk_124 = 0x1565;
            func_02015330(p, &p->unk_124, 0, 5, 0);
            func_0202dbf0(p, data_020d8f08);
            break;
    }
    a = func_0208150c(p->unk_100->unk_830);
    b = func_0209b4cc(p->unk_160, 1);
    func_0207bae8(data_021e5a2c, a, b, -10);
}
