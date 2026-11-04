/* approach_4: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020e91ac @ 0x020e91ac, 0x124 bytes, ARM
 * func_020e908c @ 0x020e908c, 0x120 bytes, ARM
 */

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

typedef struct {
    int a;
    int pad_04;
    int b;
} Pair;

extern void func_020eaca0(Vec3 *out, const Vec3 *src, const Vec3 *dst);
extern int VEC_Mag(const Vec3 *in);
extern void func_020eabc8(Vec3 *in, int value);
extern int FX_Div(int factor, int value);
extern void VEC_Add(Vec3 *out, const Vec3 *a, const Vec3 *b);
extern int func_020ea9c8(const Pair *in);

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

int func_020e908c(Pair *dst, const Pair *src, int mult, int upper, int lower)
{
    Pair local;
    int value, factor;

    if (dst->a == src->a) {
        if (dst->b == src->b) {
            return 0;
        }
    }

    func_020eaca0((Vec3 *) (&local), (const Vec3 *) src, (const Vec3 *) dst);
    value = func_020ea9c8(&local);

    if (value < lower) {
        dst->a = src->a;
        dst->b = src->b;
        return 0;
    }

    factor = (int) ((unsigned long long) ((long long) value * mult + 0x800) >> 12);

    if (factor == 0) {
        dst->a = src->a;
        dst->b = src->b;
        return 0;
    }

    if (factor > upper) {
        factor = upper;
    } else if (factor < lower) {
        factor = lower;
    }

    func_020eabc8((Vec3 *) (&local), FX_Div(factor, value));

    dst->a += local.a;
    dst->b += local.b;

    return value - factor;
}
