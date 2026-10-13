/* func_ov133_0229bc08 @ 0x0229bc08, 0x36 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_ov133_0229b714(void *self);
extern int func_0206fc8c(void *a);
extern int func_02077c3c(void *a);
extern int func_02077d68(int t);
extern int func_020eaf48(u8 a, int c);
extern void func_ov002_02208098(void *self, int a);

void func_ov133_0229bc08(void *self)
{
    void *a = func_ov133_0229b714(self);
    int b = func_0206fc8c(a);
    int c = func_02077d68(func_02077c3c(a));

    if (func_020eaf48(b, c)) {
        func_ov002_02208098(self, 0xa);
    }
}
