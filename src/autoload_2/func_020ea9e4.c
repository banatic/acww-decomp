/* func_020ea9e4 @ 0x020ea9e4, 0x48 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int func_020eacf8(long long);

typedef struct {
    int x, y, z;
} Vec3;

int func_020ea9e4(Vec3 *a, Vec3 *b)
{
    int d;
    long long sum;

    d = a->x - b->x;
    sum = (long long) d * d;
    d = a->y - b->y;
    sum += (long long) d * d;
    d = a->z - b->z;
    sum += (long long) d * d;

    return func_020eacf8(sum);
}
