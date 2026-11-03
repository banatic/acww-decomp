/* my_designs_use_2: 2 functions, module ov121
 * mwccarm 1.2/base -O4,s
 * func_ov121_0229a524 @ 0x0229a524, 0x16 bytes, Thumb
 * func_ov121_0229a50c @ 0x0229a50c, 0x16 bytes, Thumb
 */

#include "types.h"

extern BOOL func_0203ac5c(void);
extern int func_0203ac44(void);
extern int func_0203ac2c(void);

void func_ov121_0229a524(void *receiver)
{
    if (!func_0203ac5c()) {
        func_0203ac44();
    }
}

int func_ov121_0229a50c(void *receiver)
{
    int result = (int) func_0203ac5c();
    if (result) {
        result = func_0203ac2c();
    }
    return result;
}
