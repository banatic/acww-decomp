/* func_ov003_0222c16c @ 0x0222c16c, 0x50 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
extern void *data_021c67a4;
extern Vec3 data_021c67d0;
int func_ov003_0222799c(void *a, Vec3 *b, int dx, int dz, int dz2);

int func_ov003_0222c16c(char *e)
{
    int r = 0;
    Vec3 t;
    if (data_021c67a4 == 0) {
        return 1;
    }
    t.x = data_021c67d0.x;
    t.y = data_021c67d0.y;
    t.z = data_021c67d0.z;
    if (func_ov003_0222799c(e + 0x34, &t, 0x8000, 0x6000, 0x6000) == 0) {
        r = 1;
    }
    return r;
}
