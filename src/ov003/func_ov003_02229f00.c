/* func_ov003_02229f00 @ 0x02229f00, 0x2a bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void func_ov003_02229eac(void *p, void *a);
void func_ov003_02229e2c(void *p, void *a);
void func_ov003_02229dc0(void *p, void *a);

void func_ov003_02229f00(char *p, void *a)
{
    switch (*(u8 *) (p + 3)) {
        case 0:
            func_ov003_02229eac(p, a);
            break;
        case 1:
            func_ov003_02229e2c(p, a);
            break;
        case 2:
            func_ov003_02229dc0(p, a);
            break;
    }
}
