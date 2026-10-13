/* func_ov050_02261918 @ 0x02261918, 0x2a0 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02261918 {
    char pad_00[0x732];
    u16 unk_732;
} UnkStruct_02261918;

typedef struct UnkStruct_02261918_2 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb4 - 0x44];
    UnkStruct_02261918 *unk_B4;
    char pad_B8[0xd0 - 0xb8];
    int unk_D0;
} UnkStruct_02261918_2;

extern int func_0204bcdc(u16 *);
extern int func_0204bc64(u16 *);
extern int func_020984e8(void);
extern int func_02099020(int, int);
extern void func_02098ff8(int, int);
extern int func_0202e9fc(void);
extern int func_ov050_02260510(UnkStruct_02261918 *);
extern void func_0206844c(int, void *, int);
extern char data_021f43e8[];

void func_ov050_02261918(UnkStruct_02261918_2 *self)
{
    u16 tmp;
    u16 *p;
    int g;
    int t;
    int ok;
    int flag;

    p = &self->unk_B4->unk_732;
    if (func_0204bcdc(p) != 0) {
        tmp = 0xfff1;
        t = func_0204bc64(p);
        if (t == func_0204bc64(&tmp)) {
            ok = 1;
        } else {
            ok = 0;
        }
    } else {
        ok = (*p == 0xfff1) ? 1 : 0;
    }
    if (ok != 0) {
        return;
    }

    g = func_020984e8();
    do {
        flag = 0;
        if (self->unk_B4->unk_732 >= 0x1369 && self->unk_B4->unk_732 <= 0x1369) {
            flag = 1;
        }
        if (flag != 0 && func_02099020(g, 0x29) == 0) {
            self->unk_D0 = 0x24;
            func_02098ff8(g, 0x29);
            break;
        }
        flag = 0;
        if (self->unk_B4->unk_732 >= 0x1376 && self->unk_B4->unk_732 <= 0x1376) {
            flag = 1;
        }
        if (flag != 0 && func_02099020(g, 0x2a) == 0) {
            self->unk_D0 = 0x25;
            func_02098ff8(g, 0x2a);
            break;
        }
        flag = 0;
        if (self->unk_B4->unk_732 >= 0x1374 && self->unk_B4->unk_732 <= 0x1374) {
            flag = 1;
        }
        if (flag != 0 && func_02099020(g, 0x2b) == 0) {
            self->unk_D0 = 0x26;
            func_02098ff8(g, 0x2b);
            break;
        }
        flag = 0;
        if (self->unk_B4->unk_732 >= 0x136b && self->unk_B4->unk_732 <= 0x1372) {
            flag = 1;
        }
        if (flag != 0 && func_02099020(g, 0x2c) == 0) {
            self->unk_D0 = 0x27;
            func_02098ff8(g, 0x2c);
            break;
        }
        flag = 0;
        if (self->unk_B4->unk_732 >= 0x1378 && self->unk_B4->unk_732 <= 0x1378) {
            flag = 1;
        }
        if (flag != 0 && func_02099020(g, 0x2d) == 0) {
            self->unk_D0 = 0x28;
            func_02098ff8(g, 0x2d);
            break;
        }
        flag = 0;
        if (self->unk_B4->unk_732 >= 0x137a && self->unk_B4->unk_732 <= 0x137a) {
            flag = 1;
        }
        if (flag != 0 && func_02099020(g, 0x2e) == 0) {
            self->unk_D0 = 0x29;
            func_02098ff8(g, 0x2e);
            break;
        }
        flag = 0;
        if (self->unk_B4->unk_732 >= 0x151f && self->unk_B4->unk_732 <= 0x151f) {
            flag = 1;
        }
        if (flag != 0 && func_02099020(g, 0x2f) == 0) {
            self->unk_D0 = 0x39;
            func_02098ff8(g, 0x2f);
            break;
        }
        flag = 0;
        if (self->unk_B4->unk_732 >= 0x156c && self->unk_B4->unk_732 <= 0x156c) {
            flag = 1;
        }
        if (flag != 0 && func_02099020(g, 0x37) == 0) {
            self->unk_D0 = 0x10;
            func_02098ff8(g, 0x37);
            break;
        }
    } while (0);

    if (self->unk_D0 == 0xff && func_0202e9fc() != 0 && func_ov050_02260510(self->unk_B4) != 0 &&
        func_02099020(g, 0x38) == 0) {
        self->unk_D0 = 0x30;
        func_02098ff8(g, 0x38);
    } else {
        func_0206844c(self->unk_40, data_021f43e8, 0);
    }
}
