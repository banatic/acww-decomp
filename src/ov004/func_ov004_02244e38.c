/* func_ov004_02244e38 @ 0x02244e38, 0x5a bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_02244e38 {
    char unk_00[0x58];
    int xmin;
    int zmin;
    int xmax;
    int zmax;
} UnkStruct_02244e38;

int func_ov004_02244e38(UnkStruct_02244e38 *self, Vec3 *p)
{
    unsigned char f;
    int *hi, *lo;

    hi = &self->xmax;
    lo = (int *) ((int) self + 0x58);
    f = 0;
    if (p->x < self->xmin) {
        p->x = self->xmin;
        f = 1;
    } else if (p->x > hi[0]) {
        p->x = hi[0];
        f |= 2;
    }
    if (p->z < lo[1]) {
        p->z = lo[1];
        f |= 4;
    } else if (p->z > hi[1]) {
        p->z = hi[1];
        f |= 8;
    }
    return f;
}
