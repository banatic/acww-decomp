/* func_ov106_0229d57c @ 0x0229d57c, 0x48 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov002_02207d24(void *, int);
extern void func_ov106_0229cd88(u8 *, int);
extern void func_ov106_0229ce0c(u8 *);
extern void func_ov094_022999c0(void);

void func_ov106_0229d57c(u8 *self, int val)
{
    self[0xB7] = (u8) val;
    func_ov002_02207d24((void *) (self + 0x21b8), 1);
    func_ov106_0229cd88(self, val);
    if (self[0xB4] == 1) {
        self[0xBB] = 8;
    }
    func_ov106_0229ce0c(self);
    func_ov094_022999c0();
}
