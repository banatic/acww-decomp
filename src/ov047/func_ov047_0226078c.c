/* func_ov047_0226078c @ 0x0226078c, 0x16c bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0226078c {
    u8 pad_00[0xcc];
    u8 unk_CC;
    u8 pad_CD[3];
    int unk_D0;
} UnkStruct_0226078c;

extern int func_0209f150(void *, int);
extern int func_0202e9fc(void);
extern int func_02073d90(void *);
extern short *func_0209d358(int, int);
extern void *func_020984e8(void);
extern int func_0206f9d8(void *);
extern int func_02099020(void *, int);
extern int func_02070dc0(void *);
extern int func_02070fa0(void *);
extern void func_ov047_02261c00(void);

extern u8 data_021dc7a8[];
extern void *data_020ccf94;
extern u8 data_021f38f8[];

void func_ov047_0226078c(UnkStruct_0226078c *obj, int sel)
{
    void *h;
    void *p;
    int r;

    if (func_0209f150(data_021dc7a8, 0xc) != 0) {
        if (sel == 2) {
            sel = 4;
        } else if (sel > 2) {
            sel--;
        }
    }

    switch (sel) {
        case 0:
            obj->unk_CC = 0;
            if (func_0202e9fc() != 0) {
                if (func_02073d90(data_020ccf94) != 0 || *func_0209d358(0, 0x4a) != 0) {
                    obj->unk_D0 = 0x41;
                } else {
                    obj->unk_D0 = 0x14;
                }
            } else {
                obj->unk_D0 = 0x40;
            }
            break;
        case 1:
            obj->unk_CC = 0;
            h = func_020984e8();
            if (func_0206f9d8((void *) func_ov047_02261c00) == 0) {
                obj->unk_D0 = 0x18;
            } else if (func_02099020(h, 0x35) == 0) {
                obj->unk_CC = 1;
                obj->unk_D0 = 0x17;
            } else {
                obj->unk_CC = 1;
                obj->unk_D0 = 0x16;
            }
            break;
        case 2:
            if (func_02073d90(data_020ccf94) != 0 || *func_0209d358(0, 0x4a) != 0) {
                obj->unk_D0 = 0x4a;
            } else {
                obj->unk_D0 = 0xd;
            }
            break;
        case 3:
            p = data_021f38f8;
            r = func_02070dc0(p);
            obj->unk_D0 = 0x13;
            if (r == 0) {
                obj->unk_D0 = 0x10;
            } else if (r <= 0x1e000) {
                obj->unk_D0 = 0x11;
            } else if (r <= 0x46000) {
                obj->unk_D0 = 0x12;
            } else if (func_02070fa0(p) != 0) {
                obj->unk_D0 = 0x49;
            }
            break;
        case 4:
            obj->unk_D0 = 0x3f;
            break;
    }
}
