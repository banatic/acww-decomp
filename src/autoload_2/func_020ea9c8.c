/* func_020ea9c8 @ 0x020ea9c8, 0x1c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

/* FAKEMATCH: the identity inline on z makes the z load come before the x load; the plain expression loads x first */

extern void func_020eacf8(long long value);

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

inline long long widen(int x)
{
    return (long long) x;
}

void func_020ea9c8(Vec3 *v)
{
    int z = v->z;
    int x = v->x;

    func_020eacf8(widen(z) * z + (long long) x * x);
}
