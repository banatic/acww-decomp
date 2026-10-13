/* func_020316fc @ 0x020316fc, 0xc6 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    unsigned char pad_00[0x30];
    int unk_30;
    unsigned char pad_34[8];
    int unk_3C;
} Big;

extern void func_02034270(Big *big, void *src, int c, int d);
extern void func_0203423c(Big *big);
extern void func_01ffd070(Vec3 *dst, void *mtx, Vec3 *src);

int func_020316fc(void *a, int d, int *out, int p3)
{
    Big t;
    Vec3 v;
    Big u;
    Vec3 dirs[8];
    int res;
    int i;
    Vec3 *p;

    func_02034270(&t, a, 0, p3);
    if (t.unk_30 != 0) {
        dirs[0].x = -d;
        dirs[0].y = 0;
        dirs[0].z = -d;
        p = &dirs[1];
        p->x = -d;
        p->y = 0;
        p->z = d;
        p = &dirs[2];
        p->x = d;
        p->y = 0;
        p->z = d;
        p = &dirs[3];
        p->x = d;
        p->y = 0;
        p->z = -d;
        p = &dirs[4];
        p->x = -d;
        p->y = 0;
        p->z = 0;
        p = &dirs[5];
        p->x = d;
        p->y = 0;
        p->z = 0;
        p = &dirs[6];
        p->x = 0;
        p->y = 0;
        p->z = d;
        p = &dirs[7];
        p->x = 0;
        p->y = 0;
        p->z = -d;
        res = 0;
        for (i = 0; i < 8; i++) {
            func_01ffd070(&v, a, &dirs[i]);
            func_02034270(&u, &v, 0, p3);
            if (u.unk_30 == 0) {
                func_0203423c(&u);
                func_0203423c(&t);
                return 0;
            }
            res = t.unk_3C;
            func_0203423c(&u);
        }
        if (out != 0) {
            *out = res;
        }
        func_0203423c(&t);
        return 1;
    }
    func_0203423c(&t);
    return 0;
}
