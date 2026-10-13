/* func_ov004_0223bb88 @ 0x0223bb88, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern unsigned int func_ov004_0223c130(void);
extern void *func_ov004_0223ce84(void);
extern char *func_ov004_0223cd58(void *, unsigned int);

int func_ov004_0223bb88(unsigned int i)
{
    if (i < func_ov004_0223c130()) {
        if (func_ov004_0223cd58(func_ov004_0223ce84(), i) != 0) {
            return *(u8 *) (func_ov004_0223cd58(func_ov004_0223ce84(), i) + 0x288);
        }
    }
    return 0;
}
