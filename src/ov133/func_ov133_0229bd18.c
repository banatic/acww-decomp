/* func_ov133_0229bd18 @ 0x0229bd18, 0x68 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u16 data_021fbe40;
extern void func_ov133_0229ae8c(char *self);
extern unsigned char *func_ov002_02208098(char *self, unsigned char value);
extern int func_ov133_0229ae5c(char *self);
extern int func_ov133_0229b1e8(char *self, int v);
extern int func_ov133_0229ba84(char *self);
extern int func_ov133_0229ba34(char *self);
extern void func_ov002_0220a0b4(char *p, int a, int b);

void func_ov133_0229bd18(char *self)
{
    int a;
    int b;

    if ((data_021fbe40 & 2) == 0) {
        func_ov133_0229ae8c(self);
        func_ov002_02208098(self, 3);
    } else if (func_ov133_0229ae5c(self)) {
        if (func_ov133_0229b1e8(self, 1)) {
            if (*(u8 *) (self + 0x9c) == 0xc) {
                a = func_ov133_0229ba84(self);
                b = func_ov133_0229ba34(self);
                func_ov002_0220a0b4(self + 0x11c, a, b);
            }
        }
    }
}
