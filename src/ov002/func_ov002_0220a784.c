/* func_ov002_0220a784 @ 0x0220a784, 0x3c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 data_021f6c58;
extern u8 data_021f6c54;
extern void func_ov002_0220a7c0(u8 *self, int x, int a, int b);

void func_ov002_0220a784(u8 *self, int x)
{
    int a = data_021f6c58;
    int b = data_021f6c54;

    switch (self[0x1c8]) {
        case 8:
            b += 0x1e;
            break;
        case 0xc:
            b += 0x20;
            break;
        case 0xd:
            b += 0xe;
            break;
    }
    func_ov002_0220a7c0(self, x, a, b);
}
