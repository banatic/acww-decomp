/* func_ov004_02243f0c @ 0x02243f0c, 0xe0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
int func_ov004_02243f0c(unsigned char *self)
{
    Vec3 a;
    Vec3 b;
    int t;
    int u;
    int pz;
    Vec3 *q;
    volatile int v[11];
    int px;
    unsigned char *s;
    int u2;
    int db;
    int da;
    int t2;
    Vec3 *p;

    s = self;
    p = (Vec3 *) (s + 0x2c8);
    switch (*(signed char *) (s + 0x196)) {
        case 0x15:
            a.x = 0x16c00;
            v[0] = 0x1400;
            a.z = 0xd200;
            b.x = 0x1a600;
            v[1] = 0x1400;
            b.z = 0x13c00;
            break;
        case 0x16:
            a.x = 0x13200;
            v[0] = 0x1400;
            a.z = 0x10d00;
            b.x = 0x16600;
            v[1] = 0x1400;
            b.z = 0x14200;
            break;
        default:
            a.x = 0x17800;
            v[0] = 0x1400;
            a.z = 0x12200;
            b.x = 0x12b00;
            v[1] = 0x1a00;
            b.z = 0xda00;
            break;
    }
    px = p->x;
    v[3] = px;
    t = px - a.x;
    if (t < 0) {
        t = -t;
    }
    pz = p->z;
    v[2] = pz;
    u = pz - a.z;
    if (u < 0) {
        u = -u;
    }
    da = t + u;
    t2 = v[3] - b.x;
    if (t2 < 0) {
        t2 = -t2;
    }
    u2 = v[2] - b.z;
    if (u2 < 0) {
        u2 = -u2;
    }
    db = t2 + u2;
    if (da < db) {
        q = (Vec3 *) (s + 0x40);
        q->x = a.x;
        q->y = v[0];
        q->z = a.z;
        return da;
    }
    q = (Vec3 *) (s + 0x40);
    q->x = b.x;
    q->y = v[1];
    q->z = b.z;
    return db;
}
