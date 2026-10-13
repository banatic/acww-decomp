/* func_ov134_02299bcc @ 0x02299bcc, 0x94 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov134_022995c0(u8 *self, int mask);
extern int func_ov134_02299c60(u8 *self, int n, int m);
extern int func_ov134_02299cb8(u8 *self, int n, int m);

int func_ov134_02299bcc(u8 *self, int n)
{
    int hi;
    int lo;

    switch (self[0xa5]) {
        case 1:
        case 2:
            n++;
            break;
    }
    if (self[0xa0] == 1 && self[0xa5] == 3) {
        hi = self[0xb3];
        lo = self[0xb2];
        if ((unsigned int) lo < (unsigned int) hi) {
            if (n < lo || n > hi) {
                return 1;
            }
        } else {
            if (n < lo && n > hi) {
                return 1;
            }
        }
        return 0;
    }
    if (func_ov134_022995c0(self, 0x80) != 0) {
        if (func_ov134_02299c60(self, n, self[0xa5]) != 0) {
            return 1;
        }
    }
    if (func_ov134_022995c0(self, 0x40) != 0) {
        return func_ov134_02299cb8(self, n, self[0xa5]);
    }
    return 0;
}
