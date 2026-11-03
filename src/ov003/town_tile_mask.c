/* town_tile_mask: 4 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0222c71c @ 0x0222c71c, 0x3a bytes, Thumb
 * func_ov003_0222c704 @ 0x0222c704, 0x16 bytes, Thumb
 * func_ov003_0222c6f0 @ 0x0222c6f0, 0x12 bytes, Thumb
 * func_ov003_0222c68c @ 0x0222c68c, 0x62 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} UnkStruct_0222c68c;

extern int func_020644cc(int a);
extern void func_0204f7ac(UnkStruct_0222c68c *out, int gx, int gz, int bit, int row);

int func_ov003_0222c71c(unsigned short *p)
{
    unsigned short v = *p;
    if (v == 0x2a || v == 0x61 || (v >= 0x33 && v <= 0x36) || (v >= 0x3b && v <= 0x3e) || (v >= 0x43 && v <= 0x46) ||
        (v >= 0x4b && v <= 0x4e) || (v >= 0x53 && v <= 0x56)) {
        return 1;
    }
    return 0;
}

int func_ov003_0222c704(unsigned short *p)
{
    if (*p == 0x5b || (*p >= 0x66 && *p <= 0x6d)) {
        return 1;
    }
    return 0;
}

int func_ov003_0222c6f0(unsigned short *p)
{
    int r = 0;
    if (*p >= 0xcc && *p <= 0xcf) {
        r = 1;
    }
    return r;
}

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
