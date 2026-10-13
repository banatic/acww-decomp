/* func_ov004_02238d88 @ 0x02238d88, 0x80 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#define F(k) (*(int *) (self + k))
void func_ov004_02238d88(char *self)
{
    F(0x258) = F(0x27c) + F(0x278) * F(0x268);
    if (F(0x258) >= 0x1000) {
        F(0x258) = 0x1000;
        F(0x25c) = 0x1000;
        F(0x260) = 0x1000;
        *(u8 *) (self + 0x264) = 2;
        F(0x268) = 0;
        if (*(u8 *) (self + 0x280) == 4) {
            F(0x27c) = 0x99a;
        }
    } else {
        F(0x25c) = F(0x258);
        F(0x260) = F(0x258);
    }
}
