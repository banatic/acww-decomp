/* func_ov133_0229bd80 @ 0x0229bd80, 0x40 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u16 data_021fbe40;
extern void func_ov133_0229ae8c(void *self);
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);
extern int func_ov133_0229b958(void *self);
extern int func_ov133_0229ae5c(void *self);
extern int func_ov133_0229b3f8(void *self, int x);

void func_ov133_0229bd80(void *self)
{
    if ((data_021fbe40 & 1) == 0) {
        func_ov133_0229ae8c(self);
        func_ov002_02208098(self, 3);
        func_ov133_0229b958(self);
    } else if (func_ov133_0229ae5c(self)) {
        func_ov133_0229b3f8(self, 0);
    }
}
