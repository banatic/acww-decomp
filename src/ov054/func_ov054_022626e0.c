/* func_ov054_022626e0 @ 0x022626e0, 0x17c bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0202edc8(void *self);
extern void func_0201c280(void *self, void *p);
extern void func_ov054_02261f5c(void *p, void *self);
extern int func_ov054_02260474(void *self);
extern int func_0204bcdc(void *p);
extern int func_0204bc64(void *p);
extern void func_0209def4(void *p);
extern int func_020a12e8(void);
extern void func_02003348(int a, int b, void *c, void *d, void *e);
extern void func_0201af28(void *p, int a, int b, int c, int d);
extern void func_0201c400(void *self, void *p);
extern void func_0203edf4(void *self, int a);

extern u16 data_ov054_02262990[];
extern u32 data_ov054_022629e0[];
extern u16 data_020c80f8;

typedef struct UnkStruct_022626e0 {
    char pad_00[0x5c];
    u32 unk_5C;
    u32 unk_60;
    u32 unk_64;
    char pad_68[0xea - 0x68];
    u16 unk_EA;
    char pad_EC[0x350 - 0xec];
    char pad_350[0x658 - 0x350];
    char pad_658[0x808 - 0x658];
    u32 unk_808;
    u32 unk_80C;
    char pad_810[0x812 - 0x810];
    u16 unk_812;
} UnkStruct_022626e0;

typedef struct UnkStruct_022626e0_2 {
    u8 pad_00;
    u8 type;
    u16 unk_02;
    u16 unk_04;
    u16 arr0[3];
} UnkStruct_022626e0_2;

int func_ov054_022626e0(void *self)
{
    UnkStruct_022626e0_2 info;
    u32 vec3[3];
    int flag;
    int a;
    int b;
    unsigned int r5;

    if (func_0202edc8(self) == 0) {
        return 0;
    }

    func_0201c280(self, (char *) self + 0x658);
    func_ov054_02261f5c((char *) self + 0x658, self);

    if (func_ov054_02260474(self)) {
        if (func_0204bcdc((char *) self + 0xea)) {
            info.unk_04 = data_ov054_02262990[0];
            a = func_0204bc64((char *) self + 0xea);
            b = func_0204bc64(&info.unk_04);
            if (a == b) {
                flag = 1;
            } else {
                flag = 0;
            }
        } else {
            if (*(u16 *) ((char *) self + 0xea) == data_ov054_02262990[0]) {
                flag = 1;
            } else {
                flag = 0;
            }
        }

        if (flag) {
            ((UnkStruct_022626e0 *) self)->unk_808 = 0;
            ((UnkStruct_022626e0 *) self)->unk_80C = 1;
            ((UnkStruct_022626e0 *) self)->unk_5C = data_ov054_022629e0[3];
            ((UnkStruct_022626e0 *) self)->unk_60 = data_ov054_022629e0[4];
            ((UnkStruct_022626e0 *) self)->unk_64 = data_ov054_022629e0[5];
            info.arr0[0] = 0;
            info.arr0[1] = 0;
            info.arr0[2] = 0;
            vec3[0] = data_ov054_022629e0[0];
            vec3[1] = data_ov054_022629e0[1];
            vec3[2] = data_ov054_022629e0[2];
            func_02003348(0x7a, data_ov054_02262990[1], vec3, info.arr0, self);
        } else {
            ((UnkStruct_022626e0 *) self)->unk_808 = 1;
            ((UnkStruct_022626e0 *) self)->unk_80C = 0;
            ((UnkStruct_022626e0 *) self)->unk_5C = data_ov054_022629e0[0];
            ((UnkStruct_022626e0 *) self)->unk_60 = data_ov054_022629e0[1];
            ((UnkStruct_022626e0 *) self)->unk_64 = data_ov054_022629e0[2];
        }
    } else {
        func_0209def4(&info);
        r5 = info.type;
        ((UnkStruct_022626e0 *) self)->unk_808 = 0;
        if (func_020a12e8() == 0) {
            if (r5 >= 0x16 || r5 < 7) {
                ((UnkStruct_022626e0 *) self)->unk_808 = 1;
            }
        }
        func_0201af28((char *) self + 0x350, 2, 0x399, 0xcc, 0x133);
        info.unk_02 = data_ov054_02262990[((UnkStruct_022626e0 *) self)->unk_808];
        func_0201c400(self, &info.unk_02);
        *(u16 *) ((char *) self + 0xea) = data_ov054_02262990[((UnkStruct_022626e0 *) self)->unk_808];
    }

    func_0203edf4(self, 0x5000);
    ((UnkStruct_022626e0 *) self)->unk_812 = data_020c80f8;
    return 1;
}
