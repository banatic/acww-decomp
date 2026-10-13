/* func_ov134_0229b808 @ 0x0229b808, 0x40 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void func_ov134_0229b808(u8 *self, unsigned int k, int v)
{
    switch (k) {
        case 0:
            self[0xbd] = (u8) v;
            break;
        case 1:
            self[0xbc] = (u8) (v + 1);
            break;
        case 2:
            self[0xbb] = (u8) (v + 1);
            break;
        case 3:
            self[0xba] = (u8) v;
            break;
        case 4:
            self[0xb9] = (u8) v;
            break;
        case 5:
            break;
    }
}
