/* func_ov133_0229c158 @ 0x0229c158, 0x84 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#define TIMER(s) (*(vu8 *) ((s) + 0x9e))

extern void func_020b9ccc(u8 *p);
extern void func_ov133_0229bb64(u8 *self);
extern void func_ov002_0220af74(u8 *p);
extern void func_ov133_0229ad9c(u8 *self, u8 v);

void func_ov133_0229c158(u8 *self)
{
    func_020b9ccc(self + 0x34c);
    func_020b9ccc(self + 0x370);
    func_ov133_0229bb64(self);
    func_ov002_0220af74(self + 0x180);
    if (TIMER(self) != 0) {
        TIMER(self) = TIMER(self) - 1;
        if (TIMER(self) == 0) {
            if (self[0x9d] != 0) {
                TIMER(self) = 1;
            } else {
                func_ov133_0229ad9c(self, self[0xa0]);
            }
        }
    }
    self[0xa1] = self[0xa1] + 1;
}
