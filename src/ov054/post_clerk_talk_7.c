/* post_clerk_talk_7: 7 functions, module ov054
 * mwccarm 1.2/base -O4,s
 * func_ov054_02261f44 @ 0x02261f44, 0x16 bytes, Thumb
 * func_ov054_02261df8 @ 0x02261df8, 0x14c bytes, Thumb
 * func_ov054_02261ddc @ 0x02261ddc, 0x1c bytes, Thumb
 * func_ov054_02261dc0 @ 0x02261dc0, 0x1c bytes, Thumb
 * func_ov054_02261da4 @ 0x02261da4, 0x1c bytes, Thumb
 * func_ov054_02261d8c @ 0x02261d8c, 0x18 bytes, Thumb
 * func_ov054_02261d54 @ 0x02261d54, 0x38 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 pad_00[0xb0];
    u8 *unk_B0;
} UnkStruct_02261df8;

typedef struct {
    u8 a : 2;
    u8 y : 3;
    u8 z : 3;
    u8 pad_01;
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[6];
} Buf;

extern int func_020749c4(void);
extern int func_020a0174(void);
extern void *func_020984e8(void);
extern int func_02099640(int object);
extern void *func_0209a850(void *);
extern int func_ov054_02260474(void *self);
extern int func_020a12e8(void);
extern int func_02099020(void *, int);
extern int func_020a12d4(void);
extern int func_020a12c0(void);
extern void func_02098ff8(void *, int);
extern int func_0209af80(void *, u16 *);
extern int func_0202ea40(void *, Buf *, int);
extern unsigned char func_ov054_02260484(void *receiver);
extern u8 data_ov054_022629f8[][6];
extern u8 data_ov054_02262974[];
extern int data_ov054_02262fac[][3];
extern int func_0206f898(void);
extern int func_0206f8c8(void);
extern int func_0206f8b4(void);
extern int func_0206f860(void);
extern int func_020154b4(unsigned char *p, unsigned short *addr, int a, int b, int c);

int func_ov054_02261dc0(int param);
unsigned char func_ov054_02261da4(void *receiver);

void func_ov054_02261f44(void *receiver)
{
    if (func_020749c4()) {
        func_020a0174();
    }
}

void func_ov054_02261df8(UnkStruct_02261df8 *obj, void *m)
{
    void *h;
    void *y;
    Buf buf;
    int sel;
    int flag;

    h = func_020984e8();
    sel = 0;
    y = func_0209a850((void *) func_02099640((int) h));
    flag = sel;

    if (func_ov054_02260474(obj->unk_B0) != 0) {
        flag = 1;
    } else if (func_020a12e8() != 0) {
        if (func_02099020(h, 9) == 0) {
            if (func_020a12d4() != 0 || func_020a12c0() != 0) {
                ((u8 *) m)[4] = 0x12;
            } else {
                ((u8 *) m)[4] = 0x20;
            }
            func_02098ff8(h, 9);
        } else {
            ((u8 *) m)[4] = 7;
        }
        sel = 2;
    } else {
        buf.unk_02 = 0xd006;
        if (func_0209af80(y, &buf.unk_02) != 0) {
            goto bad;
        }
        buf.unk_04 = 0xd007;
        if (func_0209af80(y, &buf.unk_04) != 0) {
        bad:
            ((u8 *) m)[4] = 0x5f;
            sel = 0;
        } else if (obj->unk_B0[0x814] == 0 && func_0202ea40(obj->unk_B0, &buf, sel) != 0) {
            ((u8 *) m)[4] = data_ov054_022629f8[buf.y][buf.z];
            sel = 1;
            obj->unk_B0[0x814] = 1;
        } else {
            flag = 1;
        }
    }

    if (flag != 0) {
        ((u8 *) m)[4] = data_ov054_02262974[*(int *) (obj->unk_B0 + 0x80c)];
        sel = 0;
        if (*(int *) (obj->unk_B0 + 0x80c) == 0 && func_ov054_02260484(obj->unk_B0) != 0) {
            ((u8 *) m)[4] = 8;
        }
    }

    *(int *) m = data_ov054_02262fac[*(int *) (obj->unk_B0 + 0x808)][sel];
}

int func_ov054_02261ddc(int arg)
{
    if (func_0206f898() != 0) {
        return 0x61;
    }
    return func_ov054_02261dc0(arg);
}

int func_ov054_02261dc0(int param)
{
    if (func_0206f8c8() != 0) {
        return 0x58;
    }
    return func_ov054_02261da4((void *) param);
}

unsigned char func_ov054_02261da4(void *receiver)
{
    int x;
    x = func_0206f8b4();
    if (x != 0) {
        return (unsigned char) (x + 0x58);
    } else {
        return 9;
    }
}

int func_ov054_02261d8c(void *receiver)
{
    int result;
    if (func_0206f860() != 0) {
        result = 5;
    } else {
        result = 9;
    }
    return result;
}

void func_ov054_02261d54(unsigned char *p)
{
    int stackArg;
    unsigned short localHalf;
    if (p[0xbc] == 0) {
        localHalf = 0x1565;
        stackArg = 1;
        func_020154b4(p, &localHalf, 0, 5, stackArg);
        p[0xbc] = 1;
    }
}
