/* func_ov114_0229d5b8 @ 0x0229d5b8, 0xd0 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_020896b8(int a, void *b, int c, void *d, int e, int f, int g);
extern void func_02088df8(int a, void *b, int c, void *d, int e, int f, int g, int h, int i, int j, int k, int l);

extern int data_ov114_0229dac8[];
extern int data_ov114_0229db00[];
extern int data_ov114_0229db08[];
extern int data_ov114_0229db10[];

void func_ov114_0229d5b8(u8 *self, u8 *arg1)
{
    u8 *base;
    int i;
    int v;
    u8 *q;
    u8 *p;

    base = arg1 + 0x60;
    for (i = 0; i < 2; i++) {
        v = *(int *) (self + i * 4 + 0x129c);
        q = self + i + 0x12ae;
        if (*q != 0) {
            *q = *q - 1;
            v = 6;
        }
        func_020896b8(1, &data_ov114_0229dac8[i * 2], 0x80, base, v, 1, 0);
    }

    p = base;
    if (self[0x12bb] == 0) {
        p = base + 2;
    }
    func_020896b8(1, data_ov114_0229db00, 0x80, p, -1, 1, 0);

    p = base;
    if (self[0x12bb] == 1) {
        p = base + 2;
    }
    func_020896b8(1, data_ov114_0229db08, 0x80, p, -1, 1, 0);

    func_02088df8(1, data_ov114_0229db10, 0x80, base, -1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
}
