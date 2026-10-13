/* func_ov003_0222cf1c @ 0x0222cf1c, 0x44 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0222cf1c {
    u16 a[4][4][16];
};
extern void func_ov003_0222ce50(struct UnkStruct_0222cf1c *p);

void func_ov003_0222cf1c(struct UnkStruct_0222cf1c *self)
{
    int i, j, k;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 0x10; j++) {
            for (k = 0; k < 4; k++) {
                self->a[i][k][j] = 0xffff;
            }
        }
    }
    func_ov003_0222ce50(self);
}
