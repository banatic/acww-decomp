/* func_020599a8 @ 0x020599a8, 0x11c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_020599a8 {
    u8 pad_00[0x50];
    u16 unk_50;
    u8 pad_52[2];
    int unk_54;
    u8 unk_58;
    u8 pad_59[3];
    int unk_5C;
    u8 pad_60[0xbc - 0x60];
    int unk_BC;
    u8 pad_C0[4];
    int unk_C4;
    u8 unk_C8;
    u8 pad_C9[3];
    int unk_CC;
    int unk_D0;
} UnkStruct_020599a8;

extern int func_0204bcdc(u16 *x);
extern int func_0204bc64(u16 *x);
extern int func_020b65c4(void);
extern int func_0204fea4(void);
extern int data_020cbaf8;
extern int data_020cbafc;

int func_020599a8(UnkStruct_020599a8 *p, u16 *src, int a3, u8 a4, int a5, int a6, int a7)
{
    int t;
    int b;
    u16 tmp;

    if (p->unk_C8 == 0 && a6 != 0) {
        p->unk_50 = *src;
        p->unk_54 = a3;
        p->unk_58 = a4;
        p->unk_5C = a5;
        p->unk_CC = a6;
        p->unk_D0 = a7;
        if (func_0204bcdc(&p->unk_50)) {
            tmp = 0x1565;
            t = (func_0204bc64(&p->unk_50) == func_0204bc64(&tmp));
        } else {
            t = (p->unk_50 == 0x1565);
        }
        if ((t && p->unk_54 == 0) || ((b = (p->unk_50 >= 0x1492 && p->unk_50 <= 0x14fd)) == 1 && p->unk_54 == 2)) {
            if (func_020b65c4() == 9 || func_020b65c4() == 0x10) {
                p->unk_BC = data_020cbaf8;
            } else {
                p->unk_BC = data_020cbafc;
            }
        } else {
            p->unk_BC = data_020cbafc;
        }
        b = 0;
        if (p->unk_50 >= 0x12e8 && p->unk_50 <= 0x131f) {
            b = 1;
        }
        if (b) {
            p->unk_C4 = func_0204fea4();
        }
    }
    return 0;
}
