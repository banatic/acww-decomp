/* func_ov003_0222a398 @ 0x0222a398, 0x54 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void func_020604fc(int h, int k);

int func_ov003_0222a398(char *e)
{
    int h = *(int *) (e + 0x22c);
    if (h == 0) {
        return 0;
    }
    *(u8 *) (e + 0x23d) = 0;
    *(s8 *) (e + 0x227) = -1;
    func_020604fc(h, 0);
    *(int *) (e + 0x22c) = 0;
    *(u8 *) (e + 0x23c) = 0;
    *(u8 *) (e + 0x224) = 7;
    *(int *) (e + 0x13c) = 0;
    return 1;
}
