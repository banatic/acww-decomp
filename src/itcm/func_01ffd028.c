/* func_01ffd028 @ 0x01ffd028, 0x48 bytes, ARM, module itcm
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

long long func_01ffd028(const Vec3 *p, const Vec3 *q)
{
    long long sum;

    sum = (long long) (p->x - q->x) * (p->x - q->x);
    sum += (long long) (p->y - q->y) * (p->y - q->y);
    sum += (long long) (p->z - q->z) * (p->z - q->z);
    return sum >> 12;
}
