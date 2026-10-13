/* func_ov104_0229c944 @ 0x0229c944, 0x80 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02065ec0(u8 *p);
extern int func_02065e9c(u8 *p);
extern void func_0206f980(u8 *p);
extern void func_02066650(u8 *p);

unsigned short func_ov104_0229c944(void *unused, u8 *p)
{
    unsigned short flags;
    int found;
    int i;
    u8 *q;
    u8 *hit;

    flags = 0;
    found = -1;
    q = p;
    for (i = 0; i < 10; i++) {
        if (func_02065ec0(q) == 1 && func_02065e9c(q) != 0) {
            if (found == -1) {
                found = i;
            } else {
                found = -2;
            }
        }
        q += 0x100;
    }
    if (found != -1) {
        if (found == -2) {
            flags |= 2;
        } else {
            flags |= 1;
            hit = p + (found << 8);
            func_0206f980(hit);
            func_02066650(hit);
        }
    }
    return flags;
}
