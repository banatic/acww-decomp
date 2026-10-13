/* func_ov133_0229afec @ 0x0229afec, 0xe8 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov002_0220a620(void *, int);
extern void func_ov002_0220a63c(void *, int);
extern void func_ov002_0220a658(void *, int);
void func_ov133_0229afec(u8 *self)
{
    int i;
    u8 *p;
    p = self + 0xb94;
    p += 0x1c8;
    for (i = 0; i < 12; i++) {
        if ((*((self + 0xa4) + i)) == 0xa) {
            u16 v;
            v = *((u16 *) p);
            *((u16 *) p) = (v & 0xfc00) | 0x176;
            v = *((u16 *) (p + 2));
            *((u16 *) (p + 2)) = (v & 0xfc00) | 0x176;
            v = *((u16 *) (p + 0x40));
            *((u16 *) (p + 0x40)) = (v & 0xfc00) | 0x176;
            v = *((u16 *) (p + 0x42));
            *((u16 *) (p + 0x42)) = (v & 0xfc00) | 0x176;
        } else {
            int x;
            u16 v;
            x = ((*((self + 0xa4) + i)) << 2) + 0x84;
            v = *((u16 *) p);
            *((u16 *) p) = (v & 0xfc00) | x;
            v = *((u16 *) (p + 2));
            *((u16 *) (p + 2)) = (v & 0xfc00) | (x + 1);
            v = *((u16 *) (p + 0x40));
            *((u16 *) (p + 0x40)) = (v & 0xfc00) | (x + 2);
            v = *((u16 *) (p + 0x42));
            *((u16 *) (p + 0x42)) = (v & 0xfc00) | (x + 3);
        }
        p += 4;
    }

    if (func_ov002_0220a620(self + 0x180, 6)) {
        if (self[0xaf] != 0xa) {
            func_ov002_0220a63c(self + 0x180, 6);
        }
    } else if (self[0xaf] == 0xa) {
        func_ov002_0220a658(self + 0x180, 6);
    }
}
