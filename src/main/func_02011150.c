/* func_02011150 @ 0x02011150, 0x16c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02011150 {
    u8 pad_00[8];
    u32 unk_08;
    u8 pad_0C[0x7f4];
    u32 unk_800;
} UnkStruct_02011150;

extern u32 data_020ccf94;
extern u8 func_020112bc(void *);
extern int func_020b65c4(void);
extern int func_020b67ac(void);
extern int func_02096180(u32);
extern int func_02073908(int, u32);
extern int func_0200ee0c(UnkStruct_02011150 *);
extern int func_02011368(UnkStruct_02011150 *);
extern int func_0200f814(UnkStruct_02011150 *, u32 *, u32 *);
extern int func_0209e380(u32 *, u32 *);
extern u8 *func_0209626c(void);
extern void func_020997b4(int, int);
extern void func_0200f7ac(UnkStruct_02011150 *, int, u16 *);
extern void func_0200f11c(UnkStruct_02011150 *);
extern u16 *func_02096274(void);

u8 func_02011150(UnkStruct_02011150 *obj, int flag)
{
    u8 ret;
    u8 *ptr4;
    int sp0;
    int sp4;
    int sp8;
    u16 temp;
    u32 arr1[2];
    u32 arr2[2];
    int rel;
    int ch;
    u16 *p;

    ret = func_020112bc(obj);
    sp0 = 0;

    ch = func_020b65c4();
    if (ch == 0x2e || ch == 0x0d || ch == 0x0e || ch == 0x0c || ch == 0x2f) {
        return ret;
    }

    if (func_020b67ac() != 0 && func_02096180(obj->unk_08) == 8) {
        goto L_then;
    }

    if (func_02073908(data_020ccf94, obj->unk_800) == 0) {
        return ret;
    }
    if (flag != 0) {
        goto L_common;
    }
    return ret;

L_then:
    if (flag == 1) {
        flag = 0;
    }

L_common:
    if (func_0200ee0c(obj) != 0) {
        sp0 = 1;
    }

    sp4 = func_02011368(obj);

    arr1[0] = 0;
    arr1[1] = 0;
    arr2[0] = 0;
    arr2[1] = 0;

    rel = func_0200f814(obj, arr1, arr2);

    temp = (temp & ~0x7f) | ((((u8 *) arr1)[5] & 0x7f));
    temp = (temp & ~0x0780) | (((((u8 *) arr1)[4] & 0xf) << 7));
    temp = (temp & ~0xf800) | (((((u8 *) arr1)[3] & 0x1f) << 11));

    switch (rel) {
        case -1:
            if (flag != 0) {
                func_0200f7ac(obj, sp4, &temp);
            }
            break;
        case 0:
            break;
        default:
            sp8 = func_0209e380(arr2, arr1);
            ptr4 = func_0209626c();

            if (sp8 >= 2) {
                if (ret > (sp8 >> 1)) {
                    ret = (u8) (ret - (sp8 >> 1));
                } else {
                    ret = 0;
                }

                if (flag != 0) {
                    func_020997b4(sp4, ret);
                    func_0200f7ac(obj, sp4, &temp);
                    *ptr4 &= 0xfd; // clear bit 1
                    if (sp0 == 0) {
                        *ptr4 &= ~0x10; // clear bit 4
                    }
                    func_0200f11c(obj);
                }
            }
            *ptr4 &= 0xfe; // clear bit 0
            break;
    }

    p = func_02096274();
    if (*p == 0) {
        *p = 0x4650;
    }

    return ret;
}