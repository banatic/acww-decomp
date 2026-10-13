/* func_020ac39c @ 0x020ac39c, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0209d368(int, int);
extern void func_02001e74(int, int);

struct func_020ac39c_ctx {
    unsigned char pad_00[0x14];
    int unk_14;
    u16 unk_18;
    u16 unk_1A;
};

void func_020ac39c(struct func_020ac39c_ctx *p, int x, int y)
{
    int a = func_0209d368(0x66, 2);
    int b = func_0209d368(0x66, 3) - 8;
    int c = 13 - p->unk_14;
    int r;

    if (c < 0) {
        c = 0;
    }
    r = x + (a + b * c);
    func_02001e74(r, y);
    p->unk_18 = r;
    p->unk_1A = y;
}
