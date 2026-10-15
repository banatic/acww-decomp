/* func_ov048_02261b54 @ 0x02261b54, 0x94 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02261b54_2 {
    char pad_00[0x40];
    int unk_40;
} UnkStruct_02261b54_2;

typedef struct UnkStruct_02261b54 {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02261b54;

extern UnkStruct_02261b54 *data_020ccf94;
extern int func_020984e8(void);
extern int func_02099020(int t, int a);
extern int func_02073d90(UnkStruct_02261b54 *g);
extern int func_02073918(UnkStruct_02261b54 *g, int a);
extern int func_02073dd4(UnkStruct_02261b54 *g, int a);
extern int func_ov048_02260a24(void);
extern void func_0206844c(int h, u8 *p, int k);
extern int data_ov048_02263d20;

void func_ov048_02261b54(UnkStruct_02261b54_2 *self, int mode)
{
    u8 arg;
    int code;
    int t;
    UnkStruct_02261b54 *g;

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
                asm {
                    mov r0, self
                }
                code = func_ov048_02260a24();
            }
            break;
    }
    if (code != 0xff) {
        arg = (u8) code;
        func_0206844c(self->unk_40, &arg, data_ov048_02263d20);
    }
}
