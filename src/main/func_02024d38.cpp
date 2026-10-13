/* func_02024d38 @ 0x02024d38, 0x208 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02024d38 {
    u8 pad[8];
    u32 unk_08;
};

struct Big {
    u8 pad[0x830];
    void *unk_830;
};

struct UnkStruct_02024d38_2 {
    u8 unk_00;
    u8 unk_01;
};

struct UnkStruct_02024d38_3 {
    u8 pad_00[0x40];
    UnkStruct_02024d38 *unk_40;
    u8 pad_44[0xb0 - 0x44];
    void (UnkStruct_02024d38_3::*pmf)(void *);
    u8 pad_B8[0x100 - 0xb8];
    Big *unk_100;
    u8 pad_104[0x124 - 0x104];
    u16 unk_124;
    u8 pad_126[0x164 - 0x126];
    int unk_164;
};

struct Locals {
    u8 dst;
    u8 pad[3];
    u32 word;
    u8 unk_08;
};

extern "C" {
extern int func_0202d9c4(void *);
extern int func_0209bc40(int);
extern void func_0202da88(void *, unsigned int);
extern void func_02015de4(void *, u16 *, int, int);
extern unsigned int func_0209b914(int);
extern int func_02026250(u16 *);
extern void func_0209b890(int, u8);
extern void func_02078618(void *, u8);
extern UnkStruct_02024d38_2 *func_020808b0(void *);
extern u16 *func_02080ce4(void *);
extern int func_0204bcdc(u16 *);
extern int func_0204bc64(u16 *);
extern int func_0204c228(u16 *);
extern int func_02080834(void *, u16 *);
extern int func_0207f708(void *, u16 *);
extern int func_02053bc0(u16 *);
extern void func_0206844c(void *, void *, u32);
}

extern unsigned char data_021c2e0c[];
extern unsigned char data_021c2e24[];
extern unsigned char data_021c2e3c[];

extern "C" void func_02024d38(UnkStruct_02024d38_3 *p)
{
    void *a = p->unk_100->unk_830;
    int ok;

    switch (func_0209bc40(func_0202d9c4(p))) {
        case 2:
            func_0202da88(p, (unsigned int) data_021c2e3c);
            if (p->unk_124 != 0xfff1) {
                func_02015de4(p, &p->unk_124, 0, 7);
            }
            if (func_0209b914(p->unk_164) < 2) {
                break;
            }
            if (func_0209b914(p->unk_164) > 4) {
                break;
            }
            {
                int r = func_02026250(&p->unk_124);
                func_0209b890(p->unk_164, (u8) r);
                func_02078618(a, (u8) r);
            }
            break;
        case 3:
            if (func_0209b914(p->unk_164) >= 2) {
                func_0202da88(p, (unsigned int) data_021c2e3c);
            } else {
                UnkStruct_02024d38_2 *q = func_020808b0(a);
                u16 *b = func_02080ce4(a);
                if (func_0204bcdc(&p->unk_124) != 0) {
                    int t = func_0204bc64(&p->unk_124);
                    if (t == func_0204bc64(b)) {
                        ok = 1;
                    } else {
                        ok = 0;
                    }
                } else {
                    ok = (p->unk_124 == *b) ? 1 : 0;
                }
                if (ok != 0) {
                    func_0202da88(p, (unsigned int) data_021c2e24);
                } else if (q->unk_01 != func_0204c228(&p->unk_124)) {
                    func_0202da88(p, (unsigned int) data_021c2e3c);
                } else {
                    func_0202da88(p, (unsigned int) data_021c2e0c);
                }
            }
            if (p->unk_124 != 0xfff1) {
                func_02015de4(p, &p->unk_124, 2, 7);
            }
            break;
        case 4:
            if (func_02080834(a, &p->unk_124) > 0) {
                if (func_0204bcdc(&p->unk_124) != 0) {
                    int n = func_0207f708(a, &p->unk_124);
                    int m = func_02053bc0(&p->unk_124);
                    if (n >= 2 || (n == 1 && m == 2)) {
                        func_0202da88(p, (unsigned int) data_021c2e24);
                    } else {
                        func_0202da88(p, (unsigned int) data_021c2e3c);
                    }
                } else {
                    func_0202da88(p, (unsigned int) data_021c2e0c);
                }
            } else {
                func_0202da88(p, (unsigned int) data_021c2e0c);
            }
            if (p->unk_124 != 0xfff1) {
                func_02015de4(p, &p->unk_124, 0, 7);
            }
            break;
    }

    if (p->unk_40) {
        p->unk_40->unk_08 = 1;
    }
    {
        Locals locals;
        if (p->pmf) {
            (p->*p->pmf)(&locals.word);
        }
        locals.dst = locals.unk_08;
        func_0206844c(p->unk_40, &locals, locals.word);
    }
}
