/* func_ov003_02228380 @ 0x02228380, 0x64 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

int func_ov003_02228348(void *a, void *b);
int func_ov003_0222ab4c(void *b);
void func_ov003_02228cd4(void *a);
void func_ov003_02228d48(void *a, void *c);

void func_ov003_02228380(char *a, char *b, void *c)
{
    int v = *(u8 *) (b + 0x1fd);
    if (v == 0x1f) {
        func_ov003_02228348(a, b);
    } else if (v != 0x1f) {
        if (*(u8 *) (b + 0x7f) == 0) {
            *(u8 *) (b + 0x1fd) = (u8) (v - 1);
        }
    }
    if (*(u8 *) (b + 0x1fd) <= 1) {
        *(u8 *) (b + 0x1fd) = 0x1f;
        if (func_ov003_0222ab4c(b) == 2) {
            if (*(u8 *) (b + 0x7f) != 0) {
                func_ov003_02228cd4(a);
            }
        }
        func_ov003_02228d48(a, c);
    }
}
