/* func_ov004_022368bc @ 0x022368bc, 0x1bc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 bytes[17];
} Descriptor;
#define W(p, o) (*(int *) ((p) + (o)))
#define S(p, o) (*(short *) ((p) + (o)))
extern Descriptor data_ov004_02247924[];
extern int FX_MulFunc(int, int), func_ov004_02239460(int, int);
extern void func_ov004_02239944(void *, int, int, int);
void func_ov004_022368bc(u8 *self)
{
    int radius, upper, lower, raw;
    short angle;
    radius = FX_MulFunc(0x1800, (data_ov004_02247924[W(self, 0x15c)].bytes[3] << 12) >> 7);
    upper = W(self, 0x1b0) + radius;
    lower = W(self, 0x1b0) - radius;
    if (W(self, 0x1a8) < 0x4000 || W(self, 0x1a8) > 0x1e000) {
        return;
    }
    if (self[0x1ee] == 1) {
        self[0x1fc] = 0;
        self[0x1fd] = 0;
        return;
    }
    raw = S(self, 0x1c0);
    if (raw < 0) {
        raw = -raw;
    }
    angle = (short) raw;
    if ((upper >= 0x15dc2 && self[0x1fc]) || (upper <= 0x11000 && self[0x1fc]) ||
        (upper >= 0x15dc2 && angle < 0x4000 && !self[0x1fc]) || (lower <= 0x11000 && angle > 0x4000 && !self[0x1fc])) {
        if (!self[0x1f1]) {
            if (!self[0x1fd]) {
                if (func_ov004_02239460(0, 100) < 75) {
                    self[0x1fd] = 1;
                } else {
                    self[0x1fd] = 2;
                    return;
                }
            } else if (self[0x1eb] >= 2) {
                self[0x1fd] = 1;
                self[0x1fc] = 0;
                self[0x1eb] = 0;
            }
            if (self[0x1fd] == 1) {
                if (!self[0x1fc]) {
                    func_ov004_02239944(self, 0, 1, 4);
                    self[0x1fc] = 1;
                    if (W(self, 0x1a8) >= 0xb000 && W(self, 0x1a8) <= 0x17000 && func_ov004_02239460(0, 100) < 20) {
                        int neg = 0;
                        neg = ~neg;
                        S(self, 0x200) *= neg;
                    }
                }
                self[0x22f] = 0;
                S(self, 0x1c0) += S(self, 0x200);
                if (self[0x1ee] == 5) {
                    self[0x1ee] = 4;
                    W(self, 0x158) = 0;
                }
            }
        } else {
            self[0x1fc] = 0;
            self[0x1fd] = 0;
        }
    } else {
        self[0x1fc] = 0;
        self[0x1fd] = 0;
    }
}
