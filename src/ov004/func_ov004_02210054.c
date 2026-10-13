/* func_ov004_02210054 @ 0x02210054, 0x190 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02210054 {
    int unk_00;
    u16 unk_04;
};

extern void *func_ov004_0220e220(void *p);
extern struct UnkStruct_02210054 *func_ov004_0220d9ec(void *p, int i);
extern struct UnkStruct_02210054 *func_ov004_0220d9f8(void *p, int i);
extern struct UnkStruct_02210054 *func_ov004_0220d9e0(void *p, int i);
extern struct UnkStruct_02210054 *func_ov004_0220d9d4(void *p, int i);
extern struct UnkStruct_02210054 *func_ov004_0220da04(void *p, int i);
extern int func_02055e00(void *p);
extern int func_ov004_0220e050(void *p);
extern void func_02056440(void *p, int a, struct UnkStruct_02210054 *e, int b, int c, int d);
extern void func_020563ec(void *p, int a, struct UnkStruct_02210054 *e, int b, int c, int d, int f);
extern void func_02055060(void *p, struct UnkStruct_02210054 *e, int a, int b, int c, int d);

void func_ov004_02210054(char *self, int k, int p2, int p3)
{
    struct UnkStruct_02210054 *e1;
    struct UnkStruct_02210054 *e2;
    struct UnkStruct_02210054 *e3;
    struct UnkStruct_02210054 *e4;
    int t;
    struct UnkStruct_02210054 *e5;
    int i;

    i = k & 1;
    if (func_ov004_0220d9ec(func_ov004_0220e220(self + 0x6cc), i) != 0) {
        e1 = func_ov004_0220d9ec(func_ov004_0220e220(self + 0x6cc), i);
        func_02056440(self + 0x824, func_02055e00(self + 0x538), e1, p2, p3, (u16) (e1->unk_04 - 1));
    }
    if (func_ov004_0220d9f8(func_ov004_0220e220(self + 0x6cc), i) != 0) {
        e2 = func_ov004_0220d9f8(func_ov004_0220e220(self + 0x6cc), i);
        func_02056440(self + 0x7c4, func_02055e00(self + 0x538), e2, p2, p3, (u16) (e2->unk_04 - 1));
    }
    if (func_ov004_0220d9e0(func_ov004_0220e220(self + 0x6cc), i) != 0) {
        e3 = func_ov004_0220d9e0(func_ov004_0220e220(self + 0x6cc), i);
        func_02056440(self + 0x7e4, func_02055e00(self + 0x538), e3, p2, p3, (u16) (e3->unk_04 - 1));
    }
    if (func_ov004_0220d9d4(func_ov004_0220e220(self + 0x6cc), i) != 0) {
        e4 = func_ov004_0220d9d4(func_ov004_0220e220(self + 0x6cc), i);
        t = func_02055e00(self + 0x538);
        func_020563ec(self + 0x804, t, e4, func_ov004_0220e050(self + 0x6cc), p2, p3, (u16) (e4->unk_04 - 1));
    }
    if (func_ov004_0220da04(func_ov004_0220e220(self + 0x6cc), i) != 0) {
        e5 = func_ov004_0220da04(func_ov004_0220e220(self + 0x6cc), i);
        func_02055060(self + 0x538, e5, p2, p3, (u16) (e5->unk_04 - 1), 0);
    }
}
