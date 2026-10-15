/* func_ov003_02217678 @ 0x02217678, 0x158 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

struct UnkStruct_02217678;
struct UnkStruct_02217678_2;

extern void func_0205eae0(void *a, int b, int c, int d);
extern void func_020109a0(void *a, int b, int c, unsigned short d);
extern void func_02056fcc(void *a, u32 b, int c, u32 d, u32 e);
extern void *func_0205e8e4(void *a);
extern int func_0200f328(void *a, int b);
extern void func_020110c4(void *a, void *b);
extern u32 func_02011368(void *a);
extern void func_0209971c(u32 a, void *b);
extern void func_0200f268(void *a, int b);
extern void func_ov003_0221781c(struct UnkStruct_02217678_2 *a, int b, u8 c, u32 d, u32 e, s16 f);
extern void func_ov003_022177f4(struct UnkStruct_02217678 *a, u8 b, u32 c, u32 d, s16 e);

void func_ov003_02217678(char *self, u8 *p, int previous)
{
    u8 *p2;
    u8 flg;
    struct UnkStruct_02217678_2 *misc;
    struct UnkStruct_02217678 *base;
    int a;
    u32 b, c;
    s16 d;
    u8 buf[4];
    u32 x;
    u32 w, w2;
    void *q;

    p2 = p;
    p2 += 0xc;
    flg = p2[0xe];
    misc = (struct UnkStruct_02217678_2 *) (self + 0x7d4);

    func_0205eae0(self + 0x5a0, 0x24, 3, 1);

    if ((flg & 3) != 2) {
        func_020109a0(self, 0x62, 3, 0);
        w = (*(u32 *) (self + 0x2d4) << 4) >> 16;
        func_02056fcc(self + 0x2d0, w, 3, 0x1000, (u16) (w - 1));

        q = func_0205e8e4(self + 0x5a0);
        w2 = (*(u32 *) ((u8 *) q + 0xa0) << 4) >> 16;
        func_02056fcc((u8 *) q + 0x9c, w2, 3, 0x1000, (u16) (w2 - 1));

        func_0200f328(self, 0x858);
    } else {
        func_020110c4(buf, self);
        x = func_02011368(self);
        *(u16 *) (buf + 2) = (u16) 0xfff1;
        func_0209971c(x, buf + 2);
        func_020109a0(self, 0x62, 3, 0);
        func_0209971c(x, buf);
        func_0200f268(self, 0);
    }

    a = *(int *) p2;
    b = *(u32 *) (p2 + 4);
    c = *(u32 *) (p2 + 8);
    d = *(s16 *) (p2 + 0xc);

    func_ov003_0221781c(misc, a, flg, b, c, d);

    base = (struct UnkStruct_02217678 *) (self + 0x8f0);

    switch (a) {
        case 0x38:
            break;
        case 0x39:
            flg = flg | 0x10;
            break;
        case 0x10:
            flg = flg | 0x20;
            break;
        case 2:
            flg = flg | 0x30;
            break;
        default:
            break;
    }

    func_ov003_022177f4(base, flg, b, c, d);

    func_0200f328(self, 0x4f);
}
