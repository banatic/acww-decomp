/* func_ov048_02261be8 @ 0x02261be8, 0xfc bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02261be8_2 {
    char pad_00[0x40];
    int unk_40;
} UnkStruct_02261be8_2;

typedef struct UnkStruct_02261be8 {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02261be8;

extern UnkStruct_02261be8 *data_020ccf94;
extern int func_020984e8(void);
extern int func_02099020(int t, int a);
extern int func_02073d90(UnkStruct_02261be8 *g);
extern int func_02073918(UnkStruct_02261be8 *g, int a);
extern int func_02073dd4(UnkStruct_02261be8 *g, int a);
extern int func_ov048_02260a24(void *receiver);
extern void func_020a0194(void);
extern int func_02099664(int t);
extern void *func_02077bcc(void *record);
extern int func_020eb064(void *data);
extern int func_020eb6ac(int a);
extern long long func_020eb694(int a);
extern void func_ov048_02262588(UnkStruct_02261be8_2 *self, long long v);
extern int func_020a0174(void);
extern void func_0206844c(int h, u8 *p, int k);
extern int data_ov048_02263d20;

void func_ov048_02261be8(UnkStruct_02261be8_2 *self, int mode)
{
    u8 arg;
    int code;
    int t;
    UnkStruct_02261be8 *g;
    int q;
    int valid;

    t = func_020984e8();
    code = 0xff;
    switch (mode) {
        case 0:
            if (func_02099020(t, 1) != 0) {
                code = 8;
                break;
            }
            g = data_020ccf94;
            if (func_02073d90(g) != 0 && func_02073918(g, 0) != 0) {
                code = 0x50;
                break;
            }
            if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
                code = 0x51;
            } else {
                code = 0x52;
            }
            break;
        case 1:
            if (func_02099020(t, 1) != 0) {
                code = 0xe;
            } else {
                code = func_ov048_02260a24(self);
            }
            break;
        case 2:
            if (func_02073918(data_020ccf94, 0) != 0) {
                break;
            }
            if (func_02099020(t, 1) != 0) {
                code = 8;
                break;
            }
            func_020a0194();
            q = (int) func_02077bcc((void *) func_02099664(t));
            valid = func_020eb064((void *) q);
            if (valid != 0) {
                if (func_020eb6ac(q) != 0) {
                    code = 0x29;
                    func_ov048_02262588(self, func_020eb694(q));
                } else {
                    code = 0x23;
                }
            } else {
                code = 0x2f;
            }
            func_020a0174();
            break;
    }
    if (code != 0xff) {
        arg = (u8) code;
        func_0206844c(self->unk_40, &arg, data_ov048_02263d20);
    }
}
