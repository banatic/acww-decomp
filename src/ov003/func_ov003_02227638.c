/* func_ov003_02227638 @ 0x02227638, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void *func_ov003_02227654(int i);
int func_ov003_02227638(int i)
{
    void *e = func_ov003_02227654(i);
    if (e == 0) {
        return -1;
    }
    return *(s8 *) ((char *) e + 0x7e);
}
