/* func_020e908c @ 0x020e908c, 0x120 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

typedef struct {
    int a;
    int pad_04;
    int b;
} Pair;

extern void func_020eaca0(Pair *out, const Pair *src, const Pair *dst);
extern int func_020ea9c8(const Pair *in);
extern void func_020eabc8(Pair *in, int value);
extern int FX_Div(int factor, int value);

int func_020e908c(Pair *dst, const Pair *src, int mult, int upper, int lower)
{
    Pair local;
    int value, factor;

    if (dst->a == src->a) {
        if (dst->b == src->b) {
            return 0;
        }
    }

    func_020eaca0(&local, src, dst);
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

    func_020eabc8(&local, FX_Div(factor, value));

    dst->a += local.a;
    dst->b += local.b;

    return value - factor;
}
