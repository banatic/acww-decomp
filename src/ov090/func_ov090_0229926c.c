/* func_ov090_0229926c @ 0x0229926c, 0xdc bytes, Thumb, module ov090
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

// Case 7 goes to the default; gaps in the jump table need no explicit case.

typedef struct UnkStruct_0229926c {
    char pad_00[0x8d];
    u8 unk_8D;
    char pad_8E[5];
    u8 unk_93;
    char pad_94;
    u8 unk_95;
} UnkStruct_0229926c;

extern u8 data_ov090_02299960;
extern u8 data_020e54a8;

extern void func_0207000c(int);
extern void func_0206fc98(u8);

void func_ov090_0229926c(UnkStruct_0229926c *o)
{
    int t;

    if (data_ov090_02299960 != 0) {
        return;
    }
    o->unk_95 = 0;
    switch (o->unk_93) {
        case 0:
            t = 0;
            if (data_020e54a8 == 0) {
                t = 1;
            }
            if (t) {
                func_0207000c(2);
            } else {
                func_0207000c(1);
            }
            break;
        case 1:
            func_0207000c(3);
            break;
        case 2:
            func_0207000c(4);
            break;
        case 3:
            func_0207000c(5);
            break;
        case 4:
            func_0207000c(6);
            break;
        case 5:
            func_0207000c(7);
            break;
        case 8:
            func_0207000c(8);
            break;
        case 6:
            func_0207000c(0x24);
            break;
        case 9:
        case 10:
        case 11:
        case 12:
            func_0207000c(0xf);
            func_0206fc98((u8) (o->unk_93 + 0xf));
            break;
        case 13:
        case 14:
            func_0207000c(0x2b);
            func_0206fc98(o->unk_93);
            break;
    }
    o->unk_8D = 0;
}
