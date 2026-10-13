/* func_ov003_0222ce50 @ 0x0222ce50, 0xcc bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u16 a[4][4][16];
} UnkStruct_0222ce50;

extern u16 func_0204bbd4(unsigned int i);
extern void *func_020b3b50(u16 *id);
extern unsigned int func_020b3f44(void *h);
extern void *func_ov003_02220174(u16 id);
extern int func_020b3e8c(void *h, int *px, int *pz, unsigned int j);
extern int func_ov009_02262fa4(void *o);
extern int func_ov009_02262fc0(void *o);
extern int func_ov009_02262fb4(void *o);

void func_ov003_0222ce50(UnkStruct_0222ce50 *self)
{
    u16 id;
    void *h;
    unsigned int n;
    void *o;
    unsigned int i, j;
    int x, z;
    int px, pz;
    int kx, iz, jz, bit;

    for (i = 0; i < 0x22; i++) {
        id = func_0204bbd4(i);
        h = func_020b3b50(&id);
        if (h == 0) {
            continue;
        }
        n = func_020b3f44(h);
        if (n == 0) {
            continue;
        }
        o = func_ov003_02220174(id);
        if (o == 0) {
            continue;
        }
        for (j = 0; j < n; j++) {
            if (func_020b3e8c(h, &x, &z, j) == 0) {
                continue;
            }
            if (func_ov009_02262fa4(o) != 1) {
                continue;
            }
            px = x + func_ov009_02262fc0(o);
            pz = z + func_ov009_02262fb4(o);
            kx = (px - 0x10) / 0x10;
            iz = (pz - 0x10) / 0x10;
            jz = pz % 0x10;
            bit = px % 0x10;
            *(u16 *) ((char *) self + kx * 32 + iz * 128 + jz * 2) &= 0xffff - (1 << bit);
        }
    }
}
