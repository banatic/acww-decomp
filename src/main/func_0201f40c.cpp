/* func_0201f40c @ 0x0201f40c, 0x114 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0201f40c;
typedef void (UnkStruct_0201f40c::*PMF)(int);

struct UnkStruct_0201f40c_2 {
    u8 pad_00[0x830];
    void *unk_830;
};

struct UnkStruct_0201f40c {
    u8 pad_00[0xb0];
    PMF cb;
    u8 pad_B8[0x100 - 0xb8];
    UnkStruct_0201f40c_2 *unk_100;
    u8 pad_104[0x128 - 0x104];
    int unk_128;
    int unk_12C;
};

extern char data_021c252c[];
extern char data_021c255c[];
extern char data_021c258c[];
extern char data_021c2544[];

extern "C" int func_020644cc(int);
extern "C" int func_02020a5c(UnkStruct_0201f40c *, int);
extern "C" void func_0202d8f8(UnkStruct_0201f40c *, int *, int *, void *, int);
extern "C" int func_020819bc(void);
extern "C" void func_0202da88(UnkStruct_0201f40c *, char *);
struct ItemFlags {
    unsigned short bits;
    unsigned char count;
};
extern "C" int func_02099f1c(ItemFlags *, int (*)(unsigned short *));
extern "C" void func_020819e0(unsigned short *);
extern "C" int func_0201f550(unsigned short *);

extern "C" void func_0201f40c(UnkStruct_0201f40c *p, int arg)
{
    unsigned short *condition_value0;
    void *x;
    int a;
    int b;
    ItemFlags loc;

    x = p->unk_100->unk_830;
    a = func_020644cc(0xa) & 1;
    b = func_020644cc(0xa) & 1;
    if (func_02020a5c(p, arg)) {
        func_0202d8f8(p, &p->unk_12C, &p->unk_128, x, 0);
        return;
    }
    if (p->unk_12C == 0 || func_020819bc() == 0) {
        func_0202da88(p, data_021c252c);
    } else if (a == 0) {
        func_0202da88(p, data_021c255c);
    } else if (b == 0) {
        if (func_02099f1c(&loc, func_0201f550) > 0) {
            func_0202da88(p, data_021c258c);
        } else {
            func_0202da88(p, data_021c255c);
        }
    } else {
        func_0202da88(p, data_021c2544);
    }
    if (p->cb) {
        (p->*(p->cb))(arg);
    }
    func_0202d8f8(p, &p->unk_12C, &p->unk_128, x, 0);
    if ((condition_value0 = (unsigned short *) (p->unk_12C))) {
        func_020819e0(condition_value0);
    }
}
