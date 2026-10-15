/* func_ov133_0229c210 @ 0x0229c210, 0x4c bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020984e8(void);
extern int func_02099870(int object);
extern int func_020950c0(signed char *);
extern void func_0200458c(int x);

void func_ov133_0229c210(char *self)
{
    int object;
    *(u8 *) (self + 0x9a) = 0;
    *(u16 *) (self + 0x98) = 0;
    *(u8 *) (self + 0x9c) = 0xb;
    *(u8 *) (self + 0x9e) = 0;
    *(u8 *) (self + 0x9d) = 0;
    if ((object = func_020984e8()) != 0) {
        if (func_020950c0((signed char *) func_02099870(object)) == 0) {
            func_0200458c(0);
            return;
        }
    }
    func_0200458c(1);
}
