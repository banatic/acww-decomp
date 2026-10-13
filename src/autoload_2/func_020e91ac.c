/* func_020e91ac @ 0x020e91ac, 0x124 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

extern void func_020eaca0(Vec3 *out, const Vec3 *src, const Vec3 *dst);
extern int VEC_Mag(const Vec3 *in);
extern void func_020eabc8(Vec3 *in, int value);
extern int FX_Div(int factor, int value);
extern void VEC_Add(Vec3 *out, const Vec3 *a, const Vec3 *b);

int func_020e91ac(Vec3 *dst, const Vec3 *src, int mult, int upper, int lower)
{
    Vec3 local;
    int value, factor;

    if (dst->x == src->x) {
        if (dst->z == src->z) {
            return 0;
        }
    }

    func_020eaca0(&local, src, dst);
    value = VEC_Mag(&local);

    if (value < lower) {
        dst->x = src->x;
        dst->y = src->y;
        dst->z = src->z;
        return 0;
    }

    factor = (int) ((unsigned long long) ((long long) value * mult + 0x800) >> 12);

    if (factor == 0) {
        dst->x = src->x;
        dst->y = src->y;
        dst->z = src->z;
        return 0;
    }

    if (factor > upper) {
        factor = upper;
    } else if (factor < lower) {
        factor = lower;
    }

    func_020eabc8(&local, FX_Div(factor, value));
    VEC_Add(dst, &local, dst);

    return value - factor;
}
