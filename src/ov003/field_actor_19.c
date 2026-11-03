/* field_actor_19: 5 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02210e4c @ 0x02210e4c, 0x6c bytes, Thumb
 * func_ov003_02210c8c @ 0x02210c8c, 0x1c0 bytes, Thumb
 * func_ov003_02210c70 @ 0x02210c70, 0x1a bytes, Thumb
 * func_ov003_02210c24 @ 0x02210c24, 0x4c bytes, Thumb
 * func_ov003_02210c08 @ 0x02210c08, 0x1c bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02210e4c {
    char pad_00[0x2d8];
    int unk_2D8;
    char pad_2DC[0x428];
    int unk_704;
    char pad_708[0x128];
    int array[3];
};

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

typedef struct {
    u16 unk_00;
    u8 unk_02;
    u8 unk_03;
    u8 unk_04;
} UnkStruct_02210c24;

typedef struct {
    u8 pad_00[0xc];
    UnkStruct_02210c24 sub;
    u8 pad_12[0xa];
} Buf;

struct UnkStruct_02210c08 {
    char pad_00;
    char pad_01;
    char unk_02;
    char unk_03;
    char unk_04;
};

extern void func_02010f5c(struct UnkStruct_02210e4c *);
extern int _s32_div_f(int, int);
extern void func_0200f268(struct UnkStruct_02210e4c *, int);
extern void func_0200f650(struct UnkStruct_02210e4c *, int);
extern int data_020ccf94;
extern int func_02056f94(void *);
extern int func_02008258(UnkStruct_02210c8c *, int);
extern int func_0200d4e8(UnkStruct_02210c8c *, int, int, int);
extern int func_02073908(int, int);
extern int func_0209a110(s16 *);
extern void func_020109fc(UnkStruct_02210c8c *, int, int, int);
extern int func_0206f6b0(u16);
extern int func_0206fbc0(void);
extern int func_0206fc6c(void);
extern int func_0200f290(UnkStruct_02210c8c *, int);
extern void func_0203ee08(UnkStruct_02210c8c *, void *);
extern int func_0203e19c(void);
extern void func_02010d64(void *);
extern unsigned int func_0200e92c(Buf *);
extern void func_0200e90c(Buf *, int, u32, short);
extern void *func_0200e894(void *, Buf *);
extern int func_0200e91c(Buf *);
extern void func_020778b0(void *p, int a2);

void *func_ov003_02210c24(void *a0, u32 a1, u32 *a2, u16 a3, u32 a4, short a5);

void func_ov003_02210e4c(struct UnkStruct_02210e4c *param)
{
    int r4;
    int shifted;
    int result;

    func_02010f5c(param);
    if (param->unk_704 == 0x50) {
        shifted = (int) (((unsigned int) ((param->unk_2D8 >> 12) << 16)) >> 4);
        result = _s32_div_f(shifted, 6);
        r4 = 0x1000 - result;
        if (r4 < 0) {
            r4 = 0;
            func_0200f268(param, 13);
        }
    } else {
        r4 = 0;
    }
    param->array[0] = r4;
    param->array[1] = r4;
    param->array[2] = r4;
    func_0200f650(param, r4);
}

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
                        func_0200f268((struct UnkStruct_02210e4c *) a, 0xd);
                        if (func_0200f290(a, 0x11) != 0) {
                            func_0200f268((struct UnkStruct_02210e4c *) a, 0x11);
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
                    func_0200f268((struct UnkStruct_02210e4c *) a, 0x11);
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
                func_0200f268((struct UnkStruct_02210e4c *) a, 0xd);
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
            func_ov003_02210c24((void *) a, 2, (u32 *) pair, h, 6, -1);
            func_0200f268((struct UnkStruct_02210e4c *) a, 0xd);
            break;
    }
}

void func_ov003_02210c70(void *p)
{
    func_ov003_02210e4c((struct UnkStruct_02210e4c *) p);
    func_02010d64(p);
    func_ov003_02210c8c((UnkStruct_02210c8c *) p);
}

void *func_ov003_02210c24(void *a0, u32 a1, u32 *a2, u16 a3, u32 a4, short a5)
{
    Buf buf;
    UnkStruct_02210c24 *p;
    void *ret;

    func_0200e92c(&buf);
    p = &buf.sub;
    func_0200e90c(&buf, 0x61, a4, a5);
    p->unk_00 = a3;
    p->unk_04 = (u8) a1;
    p->unk_02 = (u8) a2[0];
    p->unk_03 = (u8) a2[1];
    ret = func_0200e894(a0, &buf);
    func_0200e91c(&buf);
    return ret;
}

void func_ov003_02210c08(struct UnkStruct_02210c08 *p, int a2, char a3, char a4, unsigned char a5)
{
    func_020778b0(p, a2);
    p->unk_02 = a3;
    p->unk_03 = a4;
    p->unk_04 = a5;
}
