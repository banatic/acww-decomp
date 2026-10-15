/* func_ov004_022168fc @ 0x022168fc, 0x1f0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#define W(p, o) (*(int *) ((p) + (o)))
#define B(p, o) (*(signed char *) ((p) + (o)))
#define H(p, o) (*(u16 *) ((p) + (o)))
extern void func_0209def4(u16 *);
extern int func_ov004_0220e5c8(void *), func_ov004_0223c10c(void), func_ov004_0223c1e0(void);
extern void func_ov004_0223cf18(void *, short), func_ov004_0223cf40(void *, int, void *),
    func_ov004_0223cf54(void *, int, void *);
extern void *func_ov004_0220e220(void *), *func_ov004_0220da04(void *, int);
extern void func_02055060(void *, void *, int, int, int, int), func_02054cdc(void *), func_020550e4(void *, int);
extern int func_02056f94(void *);
extern int func_ov004_0220ffbc(void *);
extern int func_ov004_022106fc(void *);
int func_ov004_022168fc(u8 *self)
{
    int frame;
    H(self, 0x848) = H(self, 0x846);
    func_0209def4((u16 *) (self + 0x846));
    if (W(self, 0x780) == 0x10) {
        if (!func_ov004_0220e5c8(self) && B(self, 0x844) >= 0 && B(self, 0x844) != B(self, 0x845) && self[0x84b]) {
            func_ov004_0223cf18(self + 0x798, 1);
        }
        B(self, 0x845) = B(self, 0x844);
        if (B(self, 0x844) == -1) {
            if (func_ov004_0220e5c8(self)) {
                B(self, 0x844) = 1;
            } else if (!func_ov004_0223c10c() && self[0x849] != self[0x847]) {
                B(self, 0x844) = self[0x847] % 12;
                if (B(self, 0x844) == 0) {
                    B(self, 0x844) = 12;
                }
                if (!func_ov004_0220e5c8(self)) {
                    func_ov004_0223cf40(self + 0x798, 0x42d, self + 0x7b8);
                }
                func_02055060(self + 0x538, func_ov004_0220da04(func_ov004_0220e220(self + 0x6cc), 0), 1, 0x1000, 0, 0);
            }
        } else if (B(self, 0x844) > 0) {
            if (!func_ov004_0220e5c8(self)) {
                func_ov004_0223cf40(self + 0x798, 0x42d, self + 0x7b8);
            }
            func_02054cdc(self + 0x538);
            if (func_02056f94(self + 0x5d4)) {
                func_02055060(self + 0x538, func_ov004_0220da04(func_ov004_0220e220(self + 0x6cc), 0), 1, 0x1000, 0, 0);
                if (!func_ov004_0220e5c8(self)) {
                    --B(self, 0x844);
                }
                if (B(self, 0x844) == 0) {
                    B(self, 0x844) = -1;
                }
            }
        }
    } else if (W(self, 0x780) == 0x2b) {
        func_ov004_0220ffbc(self);
    }
    frame = func_ov004_0223c1e0();
    if (W(self, 0x780) == 0x11) {
        func_020550e4(self + 0x538, frame);
    }
    if (self[0x84a] && (frame == 9 || frame == 0x1d)) {
        if (W(self, 0x780) == 0x10) {
            func_ov004_0223cf54(self + 0x798, 0x4d0, self + 0x7b8);
        } else {
            func_ov004_022106fc(self);
        }
    }
    self[0x84a] = 0;
    self[0x84b] = 0;
    return 1;
}
