/* func_ov004_02237454 @ 0x02237454, 0x1dc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#define W(p, o) (*(int *) ((p) + (o)))
#define S(p, o) (*(short *) ((p) + (o)))
#define B(p, o) (*(signed char *) ((p) + (o)))
extern int FX_MulFunc(int, int);
void func_ov004_02237454(u8 *self)
{
    switch (self[0x1ee]) {
        case 3:
            ++W(self, 0x23c);
            break;
        case 5:
            --W(self, 0x23c);
            break;
        case 4:
            if (!self[0x258]) {
                W(self, 0x158) = 0;
            }
            break;
        case 1:
            W(self, 0x1ac) -= W(self, 0x224) * 2;
            if (W(self, 0x1ac) < W(self, 0x228)) {
                W(self, 0x1ac) = W(self, 0x228);
            }
            return;
    }
    {
        int pitch = -W(self, 0x23c) * B(self, 0x256);
        pitch *= ((W(self, 0x20c) * 1000) >> 12);
        S(self, 0x1c4) = pitch;
    }
    if (S(self, 0x1c4) <= -0x1554) {
        S(self, 0x1c4) = -0x1554;
    } else if (S(self, 0x1c4) >= 0x1554) {
        S(self, 0x1c4) = 0x1554;
    }
    W(self, 0x1ac) += W(self, 0x224) * B(self, 0x256);
    switch (self[0x258]) {
        case 0:
            if (W(self, 0x1ac) > 0x299a && self[0x1ee] == 4) {
                ++self[0x257];
                if (self[0x257] >= 20) {
                    self[0x1ee] = 5;
                    self[0x258] = 1;
                    self[0x257] = 0;
                }
            }
            break;
        case 1:
            W(self, 0x1ac) -= FX_MulFunc(0x1800, W(self, 0x224) * B(self, 0x256));
            if (self[0x1ee] == 6) {
                if (W(self, 0x1ac) < W(self, 0x1cc)) {
                    B(self, 0x256) = 1;
                    self[0x255] = 0;
                    self[0x258] = 0;
                    self[0x259] = 1;
                } else {
                    self[0x1ee] = 2;
                    B(self, 0x256) = -1;
                    self[0x258] = 2;
                }
            }
            break;
        case 2:
            if (W(self, 0x1ac) < W(self, 0x1cc) && self[0x1ee] == 2) {
                B(self, 0x256) = 1;
                self[0x255] = 0;
                self[0x258] = 0;
                self[0x259] = 1;
            }
            break;
    }
    if (W(self, 0x1ac) > 0x299a) {
        W(self, 0x1ac) = 0x299a;
    } else if (W(self, 0x1ac) < W(self, 0x228)) {
        W(self, 0x1ac) = W(self, 0x228);
    }
}
