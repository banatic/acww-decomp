/* func_ov004_02235c54 @ 0x02235c54, 0x188 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#define W(p, o) (*(int *) ((p) + (o)))
#define S(p, o) (*(short *) ((p) + (o)))
extern u8 *data_ov004_022594d4[];
extern u8 data_ov004_02247927[], data_ov004_02247924[];
extern void func_ov004_02235ac4(void *), func_ov004_0223635c(void *, void *), func_ov004_02235b28(void *),
    func_020e89dc(short *, int, int);
void func_ov004_02235c54(u8 *self)
{
    if (self[0x1ee] == 1) {
        return;
    }
    if (self[0x40]) {
        if (!self[0x1f1]) {
            func_ov004_02235ac4(self);
            self[0x1ca] = 1;
            return;
        }
        if (self[0x252] != self[0x1e8]) {
            self[0x252] = self[0x1e8];
            self[0x254] = 0;
        } else {
            u8 ticks;
            self[0x254]++;
            ticks = self[0x254];
            if (ticks >= 125) {
                u8 *other = data_ov004_022594d4[self[0x1e8]];
                if (!other) {
                    return;
                }
                if (data_ov004_02247927[W(self, 0x15c) * 17] <= data_ov004_02247927[W(other, 0x15c) * 17]) {
                    func_ov004_0223635c(self, other + 0x1a8);
                    self[0x254] = 0;
                    return;
                }
                if (ticks >= 145) {
                    func_ov004_0223635c(self, other + 0x1a8);
                    self[0x254] = 0;
                    return;
                }
            }
        }
        if (self[0x1ee] == 6 || (self[0x1ee] == 5 && W(self, 0x15c) >= 35)) {
            self[0x1ee] = 2;
        }
        if ((self[0x1ea] & 8) || (self[0x1ea] & 16)) {
            if (self[0x1ee] != 4 && data_ov004_02247924[W(self, 0x15c) * 17] <= data_ov004_02247924[self[0x1e8] * 17]) {
                self[0x1ee] = 4;
                W(self, 0x158) = 0;
            }
        }
        if (self[0x1ea] >= 64) {
            if (!self[0x1c9]) {
                func_ov004_02235b28(self);
            }
        } else if (self[0x1ea] & 32) {
            self[0x1ca] = 1;
            self[0x1c9] = 1;
        }
        func_020e89dc((short *) (self + 0x1c0), S(self, 0x1ec), 0x38e);
    } else {
        func_ov004_02235ac4(self);
    }
}
