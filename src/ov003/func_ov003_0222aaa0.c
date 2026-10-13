/* func_ov003_0222aaa0 @ 0x0222aaa0, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;
extern u8 data_020cb784[];
extern u8 data_ov003_0223c026[];

void func_ov003_0222aaa0(Vec3 *out, int i)
{
    int k, v, q;
    if (i < 0 || i >= 0x3b) {
        out->x = 0x1000;
        out->y = 0x1000;
        out->z = 0x1000;
    } else {
        k = data_020cb784[i * 6];
        v = data_ov003_0223c026[k * 0x14];
        q = (v << 12) / 100;
        out->x = q;
        out->y = q;
        out->z = q;
    }
}
