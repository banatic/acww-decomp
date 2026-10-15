/* func_ov004_02241e88 @ 0x02241e88, 0x100 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02241e88 {
    char unk_00[0xc];
    int unk_0C;
    char p1[4];
    u8 unk_14;
    char p2[7];
};
extern int func_ov004_02244658(void *self, struct UnkStruct_02241e88 *s);
extern void func_ov004_02241d20(void *self, struct UnkStruct_02241e88 *s);
extern int func_020e8870(short *t, int a, int b);
extern short func_0200322c(void *a, void *b);
extern int func_020644cc(int);
extern int func_ov004_02244c20(void *self);
extern int func_020ea990(void *a, void *b);
extern int func_ov004_0221b1cc(void);

void func_ov004_02241e88(char *self)
{
    struct UnkStruct_02241e88 s;
    short t;
    u8 b;
    int r = func_ov004_02244658(self, &s);
    if (*(short *) (self + 0x9c) > 0x50) {
        *(short *) (self + 0x9c) = 0x50;
    }
    switch (*(short *) (self + 0x172)) {
        case 4:
            func_ov004_02241d20(self, &s);
            break;
        case 3:
            t = *(short *) (self + 0x192);
            if (func_020e8870(&t, *(short *) (self + 0xac), 0x2000) != 0) {
                *(short *) (self + 0x172) = 4;
            }
            *(short *) (self + 0x192) = t;
            break;
        default:
            if (r == 3) {
                *(short *) (self + 0xac) = func_0200322c(&s, self + 0x2c8);
                *(int *) (self + 0x174) = 0x14 * (func_020644cc(4) + 2);
                *(short *) (self + 0x172) = 3;
            } else if (func_ov004_02244c20(self) != 0) {
                *(short *) (self + 0x172) = 4;
                *(int *) (self + 0x174) = 0x14 * (func_020644cc(4) + 1);
            }
            break;
    }

    if (*(int *) (self + 0x4c) == 0) {
        b = s.unk_14;
        if (b != 0 && b > 0 && s.unk_0C > 0 && *(short *) (self + 0x98) == 0) {
            if (func_020ea990(&s, self + 0x2c8) < 0xe66) {
                func_ov004_0221b1cc();
                *(int *) (self + 0x4c) = 1;
            }
        }
    }
}
