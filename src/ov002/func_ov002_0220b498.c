/* func_ov002_0220b498 @ 0x0220b498, 0x64 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c60;
extern u8 data_021f6c5c;
extern int func_0208aef0(void *self);
extern int func_0208aeec(void *self);

int func_ov002_0220b498(void *self)
{
    int ok;
    int t;
    int dy;
    int dx;

    if (data_021fbdd8 != 0 && data_021fbddc != 0) {
        ok = 1;
    } else {
        ok = 0;
    }
    if (ok) {
        t = data_021f6c60;
        dy = t - func_0208aef0(self);
        t = data_021f6c5c;
        dx = t - func_0208aeec(self);
        if (dy >= 0 && dy <= 0x40 && dx >= 0 && dx <= 0x18) {
            return 1;
        }
    }
    return 0;
}
