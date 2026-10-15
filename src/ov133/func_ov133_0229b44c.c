/* func_ov133_0229b44c @ 0x0229b44c, 0x64 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov133_0229ae94(char *self);
extern unsigned char *func_ov002_02208098(char *self, unsigned char value);
extern int func_ov002_0220a620(char *p, int i);
extern void func_ov133_0229b500(char *self);
extern void func_ov133_0229b4b0(char *self);

int func_ov133_0229b44c(char *self)
{
    u8 k = *(u8 *) (self + 0x9c);

    if (k <= 0xb) {
        if (func_ov133_0229ae94(self)) {
            func_ov002_02208098(self, 7);
            return 1;
        }
        return 2;
    }
    switch (k) {
        case 0xc:
            break;
        case 0xd:
            if (func_ov002_0220a620(self + 0x180, 6) == 0) {
                func_ov133_0229b500(self);
                return 1;
            }
            return 0;
        case 0xe:
            func_ov133_0229b4b0(self);
            return 1;
    }
    return 0;
}
