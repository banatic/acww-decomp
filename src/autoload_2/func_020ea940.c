/* func_020ea940 @ 0x020ea940, 0x30 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

long long func_020ea940(Vec3 *a, Vec3 *b)
{
    int dx = a->x - b->x;
    long long sum = (long long) dx * dx;
    int dz = a->z - b->z;
    sum += (long long) dz * dz;
    return sum >> 12;
}
