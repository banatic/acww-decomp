/* func_ov127_0229960c @ 0x0229960c, 0x74 bytes, Thumb, module ov127
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x2a];
    u16 ids[16];
} UnkStruct_0229960c;

extern u8 *func_ov127_022996bc(u16 id);

void func_ov127_0229960c(UnkStruct_0229960c *a, u8 *out)
{
    int m;
    int i;
    int j;
    int k;
    int n;
    u8 *q;
    u8 *p;
    int id;

    for (m = 0; m < 0x11; m++) {
        out[m] = 0xff;
    }

    n = 0;
    for (i = 0; i < 0x10; i++) {
        id = a->ids[i];
        if (id == 0xffff) {
            continue;
        }
        q = func_ov127_022996bc((u16) id);
        for (j = 0; j < 2; j++) {
            k = 0;
            for (; k <= n; k++) {
                if (k == n) {
                    out[n] = q[j];
                    n++;
                    k = n + 1;
                } else if (out[k] == q[j]) {
                    k = n + 1;
                }
            }
        }
    }
}
