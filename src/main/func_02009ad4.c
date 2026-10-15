/* func_02009ad4 @ 0x02009ad4, 0x134 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern volatile u8 data_020e54a8;

extern int func_02095694(int a, u32 b);
extern int func_02008258(void *self, u32 p);
extern int func_0200c3b0(void *self, int a, int b, int c);
extern int func_0200c9a8(void *self, int a, int b, int c);
extern int func_0200faf0(void *self, int a);
extern void func_020108cc(void *self, int a, int b);
extern int func_02056f94(void *p);

void func_02009ad4(char *self)
{
    char *r6;
    u16 r4;
    int cond;
    int code;

    r6 = self + 0x7d4;
    r4 = *(u16 *) (r6 + 4);
    cond = (data_020e54a8 == 1) ? 1 : 0;

    if (cond != 0) {
        if (r4 >= 0x1369 && r4 <= 0x13a7) {
            func_02095694(r4 - 0x1368, *(u32 *) (self + 0x800));
        } else {
            func_02095694(0, *(u32 *) (self + 0x800));
        }

        *(int *) (self + 0x7fc) = func_02008258(self, *(u32 *) (self + 0x7f0));
        if (*(u8 *) (r6 + 6) != 0) {
            func_0200c3b0(self, 3, 5, -1);
        } else {
            func_0200c9a8(self, 3, 5, -1);
        }
    } else {
        func_0200faf0(self, 0x400);
        code = (*(u32 *) (self + 0x2d8) << 4) >> 16;

        switch (code) {
            case 8:
                func_02095694(0, *(u32 *) (self + 0x800));
                break;
            case 11:
                if (r4 >= 0x1369 && r4 <= 0x13a7) {
                    func_02095694(r4 - 0x1368, *(u32 *) (self + 0x800));
                }
                break;
            case 14:
                func_020108cc(self, 0, 6);
                break;
            default:
                break;
        }

        if (func_02056f94(self + 0x2d0) != 0) {
            *(int *) (self + 0x7fc) = func_02008258(self, *(u32 *) (self + 0x7f0));
            if (*(u8 *) (r6 + 6) != 0) {
                func_0200c3b0(self, 3, 5, -1);
            } else {
                func_0200c9a8(self, 3, 5, -1);
            }
        }
    }
}
