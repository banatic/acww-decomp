/* func_ov004_0222bf20 @ 0x0222bf20, 0x2e bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02096718(int argument0);
extern int func_ov004_02227324(void *argument0, int argument1, int argument2, int argument3, short argument4);

int func_ov004_0222bf20(char *self, char *a1)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_02096718((int) ((int) (0x4)));
    if (v1 != 0x0) {
        return func_ov004_02227324((void *) (v1), (int) (*(u8 *) (self)), (int) (*(u8 *) (a1)), (int) (0x6), (short) (-0x1));
    }
    return 0x0;
}
