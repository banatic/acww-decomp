/* func_020320e0 @ 0x020320e0, 0x9e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

extern void func_020eaca0(int *r0, int *r1, int *r2);
extern void func_01ffd070(Vec3 *dst, void *mtx, Vec3 *src);

int func_020320e0(Vec3 *p1, Vec3 *p2, Vec3 *p3, Vec3 *p4)
{
    Vec3 *arr[2];
    Vec3 v1;
    Vec3 v2;
    int mask;
    int i;

    arr[0] = p3;
    arr[1] = p4;
    func_020eaca0((int *) &v1, (int *) p1, (int *) p2);
    func_01ffd070(&v2, (void *) p1, p2);
    mask = 0xff;
    for (i = 0; i < 2; i++) {
        Vec3 *p = arr[i];
        int flags = 0;
        if (p->x < v1.x) {
            flags |= 1;
        } else if (p->x > v2.x) {
            flags |= 2;
        }
        if (p->z < v1.z) {
            flags |= 4;
        } else if (p->z > v2.z) {
            flags |= 8;
        }
        if (flags == 0) {
            return 0;
        }
        mask &= flags;
    }
    if (mask == 1) {
        return 1;
    }
    if (mask == 2) {
        return 1;
    }
    if (mask == 4) {
        return 1;
    }
    if (mask == 8) {
        return 1;
    }
    return 0;
}
