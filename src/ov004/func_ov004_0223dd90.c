/* func_ov004_0223dd90 @ 0x0223dd90, 0x84 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_020961a8(int);
extern int func_02089cc0(void *p, unsigned int mask);
extern void *data_ov004_02259a14;

int func_ov004_0223dd90(char *self)
{
    char *n = (char *) func_020961a8(4);
    char *g;
    if (*(u8 *) (self + 0x214) != 0 && *(u8 *) (self + 0x22a) == 0) {
        if (n != 0 && *(int *) (n + 0x98) > 0 && func_02089cc0(self + 0x1d8, 4) != 0) {
            *(int *) (self + 0x10c) = 2;
            return 1;
        }
        g = (char *) data_ov004_02259a14;
        if (g != 0 && *(int *) (g + 0x98) > 0 && func_02089cc0(self + 0x1d8, 8) != 0) {
            *(int *) (self + 0x10c) = 2;
            return 1;
        }
    }
    return 0;
}
