/* func_ov133_0229bf88 @ 0x0229bf88, 0xc8 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov002_02208054(char *self, int v);
extern void func_ov133_0229bbd4(char *self);
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern u8 data_021f6c54;
extern int func_ov002_0220a620(char *p, int i);
extern int func_ov002_0220a784(char *p, int i);
extern void func_ov133_0229b500(char *self);
extern void func_ov133_0229b4b0(char *self);
extern int func_ov133_0229b73c(char *self, int x, int y);
extern int func_ov133_0229b344(char *self);
extern void func_ov133_0229b320(char *self, u8 v);
extern unsigned char *func_ov002_02208098(char *self, unsigned char value);
extern int func_ov133_0229ae94(char *self);

void func_ov133_0229bf88(char *self)
{
    int ok;
    int r;

    if (func_ov002_02208054(self, 1)) {
        func_ov133_0229bbd4(self);
        return;
    }
    if (data_021fbdd8 != 0 && data_021fbddc != 0) {
        ok = 1;
    } else {
        ok = 0;
    }
    if (!ok) {
        return;
    }
    if (func_ov002_0220a620(self + 0x180, 6) == 0) {
        if (func_ov002_0220a784(self + 0x180, 6)) {
            func_ov133_0229b500(self);
            return;
        }
    }
    if (func_ov002_0220a784(self + 0x180, 7)) {
        func_ov133_0229b4b0(self);
        return;
    }
    r = func_ov133_0229b73c(self, data_021f6c58, data_021f6c54);
    if (r == 0xc) {
        func_ov133_0229b320(self, func_ov133_0229b344(self));
        func_ov002_02208098(self, 2);
    } else if (r != 0xf) {
        if (func_ov133_0229ae94(self)) {
            func_ov002_02208098(self, 1);
        }
    }
}
