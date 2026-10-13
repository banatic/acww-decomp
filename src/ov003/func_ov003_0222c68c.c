/* func_ov003_0222c68c @ 0x0222c68c, 0x62 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} UnkStruct_0222c68c;

extern int func_020644cc(int a);
extern void func_0204f7ac(UnkStruct_0222c68c *out, int gx, int gz, int bit, int row);

void func_ov003_0222c68c(int a, u16 *mask, int *px, int *pz)
{
    UnkStruct_0222c68c t;
    int n;
    int i;
    u16 *p;
    int j;

    n = func_020644cc(a);
    for (i = 0; i < 16; i++) {
        j = 0;
        p = mask + i;
        for (; j < 16; j++) {
            if (((*p >> j) & 1) == 0) {
                if (n-- == 0) {
                    func_0204f7ac(&t, *px + 1, *pz + 1, j, i);
                    *px = t.x;
                    *pz = t.z;
                    return;
                }
            }
        }
    }
}
