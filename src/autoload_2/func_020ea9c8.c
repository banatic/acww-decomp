/* func_020ea9c8 @ 0x020ea9c8, 0x1c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int func_020eacf8(long long value);

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

int func_020ea9c8(Vec3 *v)
{
    int x = v->x;
    int z = v->z;

    return func_020eacf8((long long) x * x + (long long) z * z);
}
