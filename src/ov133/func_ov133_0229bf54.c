/* func_ov133_0229bf54 @ 0x0229bf54, 0x34 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 data_021fbdd8;
extern void func_ov133_0229ae8c(void *self);
extern void func_ov002_02208098(void *self, int x);
extern int func_ov133_0229ae5c(void *self);
extern void func_ov133_0229b3f8(void *self, int x);

void func_ov133_0229bf54(void *self)
{
    if (data_021fbdd8 == 0) {
        func_ov133_0229ae8c(self);
        func_ov002_02208098(self, 0);
    } else if (func_ov133_0229ae5c(self)) {
        func_ov133_0229b3f8(self, 0);
    }
}
