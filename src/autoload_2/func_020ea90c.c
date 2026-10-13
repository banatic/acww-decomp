/* func_020ea90c @ 0x020ea90c, 0x34 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

int func_020ea90c(const Vec3 *p, const Vec3 *q)
{
    return (int) (((long long) p->x * q->x + (long long) p->z * q->z) >> 12);
}
