/* func_ov133_0229be4c @ 0x0229be4c, 0xd8 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov002_02208014(char *self);
extern void func_ov133_0229bbf0(char *self);
extern void *func_ov002_02208008(char *self);
extern int func_ov133_0229b790(char *self, void *pad);
extern void func_ov133_0229b9a8(char *self);
extern void func_ov133_0229b978(char *self);
extern int func_ov133_0229b1e8(char *self, int v);
extern void func_ov002_02208098(char *self, int v);
extern int func_ov133_0229ba84(char *self);
extern int func_ov133_0229ba34(char *self);
extern void func_ov002_0220a0b4(char *p, int a, int b);
extern void func_ov133_0229b4b0(char *self);
extern void func_ov133_0229ba10(char *self);
extern int func_ov002_0220a620(char *p, int i);
extern void func_ov133_0229b500(char *self);
extern u16 data_021fbe40[];

void func_ov133_0229be4c(char *self)
{
    u16 keys;
    int a;
    int b;

    if (func_ov002_02208014(self)) {
        func_ov133_0229bbf0(self);
        return;
    }
    if (func_ov133_0229b790(self, func_ov002_02208008(self))) {
        func_ov133_0229b9a8(self);
        return;
    }
    keys = data_021fbe40[1];
    if (keys & 1) {
        func_ov133_0229b978(self);
        return;
    }
    if (keys & 2) {
        if (func_ov133_0229b1e8(self, 0)) {
            *(u8 *) (self + 0x9d) = 0xd;
            func_ov002_02208098(self, 8);
            if (*(u8 *) (self + 0x9c) == 0xc) {
                a = func_ov133_0229ba84(self);
                b = func_ov133_0229ba34(self);
                func_ov002_0220a0b4(self + 0x11c, a, b);
            }
        } else {
            func_ov133_0229b4b0(self);
            func_ov133_0229ba10(self);
        }
        return;
    }
    if (keys & 8) {
        if (func_ov002_0220a620(self + 0x180, 6) == 0) {
            func_ov133_0229b500(self);
            func_ov133_0229ba10(self);
        }
    }
}
