/* func_ov004_0223ef1c @ 0x0223ef1c, 0x7c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 func_ov004_0223ee98(void *self, u8 i);
extern void func_ov004_0223fa10(void *self, signed char i);
extern int func_02071298(void *, u16 *);
extern char data_021f38f8[];

void func_ov004_0223ef1c(char *self)
{
    u8 target = (u8) * (int *) (self + 8);
    int flag = 0;
    u8 i;
    u16 v;
    for (i = 0; i < 0x39; i++) {
        if (func_ov004_0223ee98(self, i) == target) {
            v = (i < 0x38) ? (u16) (0x12b0 + i) : (u16) 0x12b0;
            if (i == 0x38) {
                if (flag != 0) {
                    func_ov004_0223fa10(self, (signed char) i);
                }
            } else if (func_02071298(data_021f38f8, &v) != 0) {
                func_ov004_0223fa10(self, (signed char) i);
                if (i == 0x23) {
                    flag = 1;
                }
            }
        }
    }
}
