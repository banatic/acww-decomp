/* func_ov133_0229bf24 @ 0x0229bf24, 0x30 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 data_021fbdd8;
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);
extern int func_ov133_0229b344(void *self);
extern void func_ov133_0229b2e4(void *self, u8 v);

void func_ov133_0229bf24(void *self)
{
    if (data_021fbdd8 == 0) {
        func_ov002_02208098(self, 0);
    } else {
        func_ov133_0229b2e4(self, func_ov133_0229b344(self));
    }
}
