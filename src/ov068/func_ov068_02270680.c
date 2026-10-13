/* func_ov068_02270680 @ 0x02270680, 0xd0 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} VecFx32;

extern u8 *func_020961a8(int a);
extern int func_ov003_02233e4c(u8 *self, VecFx32 *v);
extern int func_020ea990(VecFx32 *a, void *b);
extern int func_ov068_022704cc(u8 *self, u8 m, void *q);
extern int func_ov068_02270328(u8 *self, u8 m, void *q, s16 *buf);

int func_ov068_02270680(u8 *self, s16 *buf)
{
    int ret;
    u8 *q;
    int d;
    VecFx32 v;
    s16 n;
    s8 m;

    ret = 0;
    q = func_020961a8(4);
    if (q != 0) {
        q = q + 0x5c;
        m = (s8) func_ov003_02233e4c(self, &v);
        n = self[0x254];
        if (n > 0) {
            d = *(int *) (self + 0x224);
            if (func_020ea990(&v, self + 0x204) > d) {
                n = n - 3;
                self[0x254] = (n > 0) ? n : 0;
            }
        }
        if (n >= 0x14 || *(s16 *) (self + 0x232) > 0) {
            if (self[0x247] != 0) {
                ret = func_ov068_022704cc(self, (u8) m, q);
            } else {
                m = 1;
            }
        }
        if ((n >= 0x14 && self[0x247] == 0) || n >= self[0x255] || *buf > 0) {
            ret = func_ov068_02270328(self, (u8) m, q, buf);
        }
    }
    return ret;
}
