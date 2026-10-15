/* func_ov054_02261df8 @ 0x02261df8, 0x14c bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
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

extern void *func_020984e8(void);
extern int func_02099640(int object);
extern void *func_0209a850(void *);
extern int func_ov054_02260474(void);
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

    if (((void) *(u8 *volatile *) &obj->unk_B0, func_ov054_02260474()) != 0) {
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
