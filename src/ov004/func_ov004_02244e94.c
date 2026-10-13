/* func_ov004_02244e94 @ 0x02244e94, 0x8c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

extern void func_02034270(void *w, Vec3 *v, int a, int b);
extern int func_020341c8(void *w, int a);
extern void func_0203423c(void *w);

int func_ov004_02244e94(Vec3 *a, Vec3 *b)
{
    Vec3 v1;
    char w1[0x40];
    Vec3 v2;
    char w2[0x40];
    int r, f, t;

    r = 1;
    t = b->z;
    v1.x = a->x;
    v1.y = 0;
    v1.z = t;
    func_02034270(w1, &v1, 0, 0);
    if (func_020341c8(w1, 0) > 0x200) {
        f = 1;
    } else {
        f = 0;
    }
    func_0203423c(w1);
    if (f != 0) {
        a->x = b->x;
        r = 0;
    }
    t = a->z;
    v2.x = b->x;
    v2.y = 0;
    v2.z = t;
    func_02034270(w2, &v2, 0, 0);
    if (func_020341c8(w2, 0) > 0x200) {
        f = 1;
    } else {
        f = 0;
    }
    func_0203423c(w2);
    if (f != 0) {
        a->z = b->z;
        r = 0;
    }
    return r;
}
