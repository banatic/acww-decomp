/* func_ov003_02224768 @ 0x02224768, 0x17c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} UnkStruct_02224768;

extern void *data_021c80bc;
extern volatile u8 data_ov003_02236ca0[];
extern void func_0204f818(int *x, int *z, UnkStruct_02224768 *p);
extern u16 *func_0204f5e0(void *g, int gx, int gz, int ox, int oz, int f);
extern int func_02049ec4(u16 *e);
extern void func_0204f794(void *a, int x, int z);

int func_ov003_02224768(void *owner, UnkStruct_02224768 *pos, int mask)
{
    int i;
    void *scene;
    unsigned int h, g, f, e, d, c, b, a;
    volatile UnkStruct_02224768 tmp;
    int gx, gz;
    int ret;
    u16 *ent;
    int x, z, cx, cz;
    u16 id;
    u8 k;

    scene = data_021c80bc;
    ret = 0;
    if (scene != 0) {
        tmp.x = pos->x;
        tmp.y = pos->y;
        tmp.z = pos->z;
        gx = 0;
        gz = 0;
        func_0204f818(&gx, &gz, pos);
        for (i = 0; i < 0x51; i++) {
            k = data_ov003_02236ca0[i];
            x = gx + ((k >> 4) - 8);
            z = gz + ((k & 0xf) - 8);
            cx = x >> 4;
            cz = z >> 4;
            ent = func_0204f5e0(scene, cx, cz, x - (cx << 4), z - (cz << 4), 0);
            if (ent == 0) {
                continue;
            }
            h = 1;
            g = 1;
            f = 1;
            e = 1;
            d = 1;
            c = 1;
            b = 1;
            a = 0;
            id = *ent;
            if (id <= 5) {
                a = 1;
            }
            if (a == 0) {
                if (!(id >= 6 && id <= 0xb)) {
                    b = 0;
                }
            }
            if (b == 0) {
                if (!(id >= 0xc && id <= 0x11)) {
                    c = 0;
                }
            }
            if (c == 0) {
                if (!((id >= 0x12 && id <= 0x19) || id == 0x1c)) {
                    d = 0;
                }
            }
            if (d == 0) {
                if (!((id >= 0x8a && id <= 0x8f) || (id >= 0x90 && id <= 0x95) || (id >= 0x96 && id <= 0x9b) ||
                      (id >= 0x9c && id <= 0xa3) || id == 0xa5)) {
                    e = 0;
                }
            }
            if (e == 0) {
                if (id != 0x1a) {
                    f = 0;
                }
            }
            if (f == 0) {
                if (id != 0xa4) {
                    g = 0;
                }
            }
            if (g == 0) {
                if (id != 0x1d) {
                    h = 0;
                }
            }
            if (h != 0) {
                if ((mask >> func_02049ec4(ent) & 1) != 0) {
                    k = data_ov003_02236ca0[i];
                    gx = gx + ((k >> 4) - 8);
                    gz = gz + ((k & 0xf) - 8);
                    func_0204f794(owner, gx, gz);
                    ret = 1;
                    break;
                }
            }
        }
    }
    return ret;
}
