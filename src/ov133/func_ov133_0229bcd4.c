/* func_ov133_0229bcd4 @ 0x0229bcd4, 0x44 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u16 data_021fbe40;
extern unsigned char *func_ov002_02208098(char *self, unsigned char value);
extern int func_ov133_0229b958(char *self);
extern int func_ov002_02208008(char *self);
extern int func_ov133_0229b36c(char *self, int a);
extern void func_ov133_0229b2e4(char *self, u8 v);

void func_ov133_0229bcd4(char *self)
{
    if ((data_021fbe40 & 1) == 0) {
        func_ov002_02208098(self, 3);
        func_ov133_0229b958(self);
    } else if (func_ov133_0229b36c(self, func_ov002_02208008(self))) {
        func_ov133_0229b2e4(self, *(u8 *) (self + 0x9f));
    }
}
