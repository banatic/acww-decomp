/* func_ov003_02210c8c @ 0x02210c8c, 0x1c0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0xec];
    u8 unk_EC[0x2d0 - 0xec];
    u8 unk_2D0[0x704 - 0x2d0];
    int unk_704;
    u8 pad_708[0x7d4 - 0x708];
    u8 unk_7D4[4];
    u8 pad_7D8[0x7f0 - 0x7d8];
    int unk_7F0;
    u8 pad_7F4[0x7fc - 0x7f4];
    int unk_7FC;
    int unk_800;
    u8 pad_804[0x80c - 0x804];
    int unk_80C;
    u8 pad_810[0x81c - 0x810];
    int unk_81C;
    s16 unk_820;
} UnkStruct_02210c8c;
extern int data_020ccf94;
extern int func_02056f94(void *);
extern int func_02008258(UnkStruct_02210c8c *, int);
extern void func_0200d4e8(UnkStruct_02210c8c *, int, int, int);
extern int func_02073908(int, int);
extern void func_0209a110(s16 *);
extern void func_020109fc(UnkStruct_02210c8c *, int, int, int);
extern int func_0206f6b0(u16);
extern int func_0206fbc0(void);
extern int func_0206fc6c(void);
extern int func_0200f290(UnkStruct_02210c8c *, int);
extern void func_0200f268(UnkStruct_02210c8c *, int);
extern void func_0203ee08(UnkStruct_02210c8c *, void *);
extern void func_0203e19c(void);
extern void func_ov003_02210c24(UnkStruct_02210c8c *, int, int *, u16, int, int);
inline int inline_fn(UnkStruct_02210c8c *arg0)
{
    return arg0->unk_800;
}

void func_ov003_02210c8c(UnkStruct_02210c8c *a)
{
    u8 *pst;
    u8 *pf;
    u8 *base;
    int pair[2];
    u8 val;
    u16 h;
    int val2;
    pf = a->unk_7D4;
    pst = pf + 2;
    switch (pf[2]) {
        case 0:
            if (func_02056f94(a->unk_2D0) == 0) {
                break;
            }
            a->unk_7FC = func_02008258(a, a->unk_7F0);
            func_0200d4e8(a, 3, 1, -1);
            if (func_02073908(data_020ccf94, inline_fn(a)) == 0) {
                break;
            }
            func_0209a110(&a->unk_820);
            break;

        case 1:
            if (a->unk_704 == 0x50) {
                if (func_02056f94(a->unk_2D0) == 0) {
                    break;
                }
                func_020109fc(a, 0x6c, 3, 3);
            }
            if (func_02073908(data_020ccf94, inline_fn(a)) != 0) {
                if (a->unk_81C == 5) {
                    if (func_0206f6b0((u16) a->unk_820) == 0) {
                        break;
                    }
                    a->unk_81C = 6;
                    break;
                    goto next;
                next:;
                }
                if (a->unk_81C == 6) {
                    if (func_0206fbc0() == 0) {
                        break;
                    }
                    a->unk_81C = 0xf;
                    if (func_0206fc6c() != 0) {
                        func_0200f268(a, 0xd);
                        if (func_0200f290(a, 0x11) != 0) {
                            func_0200f268(a, 0x11);
                            base = (u8 *) a;
                            if (a != 0) {
                                base = a->unk_EC;
                            }
                            func_0203ee08(a, base);
                        }
                        func_0203e19c();
                        a->unk_7FC = func_02008258(a, a->unk_7F0);
                        func_0200d4e8(a, 3, 1, -1);
                        break;
                    }
                } else if (a->unk_81C < 0xf) {
                    break;
                }
                if (func_0200f290(a, 0x11) != 0) {
                    func_0200f268(a, 0x11);
                    base = (u8 *) a;
                    if (a != 0) {
                        base = a->unk_EC;
                    }
                    func_0203ee08(a, base);
                }
                func_0203e19c();
                *pst = (u8) ((*pst) + 1);
            } else {
                a->unk_7FC = func_02008258(a, val2 = a->unk_7F0);
                func_0200f268(a, 0xd);
            }
            break;

        case 2:
            if (a->unk_80C != (-1)) {
                break;
            }
            val = pf[1];
            h = (u16) a->unk_820;
            pair[0] = pf[0];
            pair[1] = val;
            func_ov003_02210c24(a, 2, pair, h, 6, -1);
            func_0200f268(a, 0xd);
            break;
    }
}
