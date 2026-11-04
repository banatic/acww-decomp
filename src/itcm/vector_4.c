/* vector_4: 2 functions, module itcm
 * mwccarm 1.2/base -O4,s
 * func_01ffd070 @ 0x01ffd070, 0x44 bytes, ARM
 * func_01ffd028 @ 0x01ffd028, 0x48 bytes, ARM
 */

typedef struct {
    int x, y, z;
} Vec3;

void func_01ffd070(int *out, const int *a, const int *b)
{
    int x0, x1, x2;
    int y0, y1, y2;

    x0 = a[0];
    y0 = b[0];
    x2 = a[2];
    y2 = b[2];
    x1 = a[1];
    y1 = b[1];

    out[0] = x0 + y0;
    out[1] = x1 + y1;
    out[2] = x2 + y2;
}

long long func_01ffd028(const Vec3 *p, const Vec3 *q)
{
    long long sum;

    sum = (long long) (p->x - q->x) * (p->x - q->x);
    sum += (long long) (p->y - q->y) * (p->y - q->y);
    sum += (long long) (p->z - q->z) * (p->z - q->z);
    return sum >> 12;
}
