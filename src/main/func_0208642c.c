/* func_0208642c @ 0x0208642c, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u16 unk_00;
} Entry;
typedef struct {
    int dx;
    int dz;
} Off;

extern void *func_0208150c(void *a);
extern int func_02003704(void *a);
extern u8 *func_020800d0(void *a);
extern Entry *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern int func_020864f4(unsigned int *out, Entry *e);
extern int func_020864cc(unsigned int mask);
extern const Off data_021d2820[];

int func_0208642c(void *a, void *ctx)
{
    int result;
    void *tmp;
    const Off *t;
    int i;
    int count;
    unsigned int mask;
    int x, z, cx, cz;
    Entry *e;
    unsigned int out;
    u8 *p;

    tmp = func_0208150c(a);
    result = 0;
    if (func_02003704(tmp) != 0) {
        mask = 0;
        p = func_020800d0(a);
        x = p[0];
        z = p[1];
        t = data_021d2820;
        count = 0;
        out = 0;
        for (i = 0; i < 14; i++) {
            int wx = x + t->dx;
            int wz = z + t->dz;
            cx = wx >> 4;
            cz = wz >> 4;
            e = func_0204f5e0(ctx, cx, cz, wx - (cx << 4), wz - (cz << 4), 0);
            out = 0;
            if (e != 0) {
                if (func_020864f4(&out, e) != 0) {
                    if (out < 0x20) {
                        mask |= 1 << out;
                    }
                    count++;
                }
            }
            t++;
        }
        result = func_020864cc(mask);
        result = count * result;
    }
    return result;
}
