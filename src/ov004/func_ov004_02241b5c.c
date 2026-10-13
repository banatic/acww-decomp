/* func_ov004_02241b5c @ 0x02241b5c, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern long FX_MulFunc(long, long);
typedef struct {
    long x, y, z;
} UnkStruct_02241b5c;
void func_ov004_02241b5c(UnkStruct_02241b5c *dst, UnkStruct_02241b5c *src, long s)
{
    long lim = FX_MulFunc(s << 12, 0x40);
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
    dst->y = 0;
    if (src->x > lim) {
        dst->x = lim;
    } else if (src->x < -lim) {
        dst->x = -lim;
    }
    if (src->z > lim) {
        dst->z = lim;
    } else if (src->z < -lim) {
        dst->z = -lim;
    }
}
