/* func_ov004_02217eb8 @ 0x02217eb8, 0x74 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int data_020ca0ec;

int func_ov004_02217eb8(char *self)
{
    unsigned int t;
    t = (*(int *) (self + 0x5c) < (data_020ca0ec >> 1)) ? 1 : 0;
    *(u8 *) (self + 0x846) = (u8) t;
    t = (*(int *) (self + 0x64) < 0x16000) ? 1 : 0;
    *(u8 *) (self + 0x847) = (u8) t;
    if (*(u8 *) (self + 0x846) != 0) {
        if (*(u8 *) (self + 0x847) != 0) {
            *(u8 *) (self + 0x848) = 0;
        } else {
            *(u8 *) (self + 0x848) = 2;
        }
    } else {
        if (*(u8 *) (self + 0x847) != 0) {
            *(u8 *) (self + 0x848) = 1;
        } else {
            *(u8 *) (self + 0x848) = 3;
        }
    }
    return 1;
}
