/* func_ov003_022293b0 @ 0x022293b0, 0x78 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

extern int data_020c904c;
extern short func_0200322c(int a, void *p);
extern void func_ov003_0222be78(void *p, int d, int h);
extern void func_02091278(void *h, Vec3 *v, int a, int b);

int func_ov003_022293b0(char *self, int a1)
{
    int t;
    int d;
    Vec3 v;
    t = *(int *) (self + 0x7c);
    d = (t + 2) << 7;
    if (t == 0) {
        *(short *) (self + 0x98) = func_0200322c(a1, self + 0x54);
    } else if (t >= 0x1e) {
        *(int *) (self + 0x40) = 4;
    }
    if (d > 0x214) {
        d = 0x214;
    }
    func_ov003_0222be78(self + 0x54, d, *(short *) (self + 0x98));
    *(int *) (self + 0x7c) += 1;
    v.x = *(int *) (self + 0x54);
    v.y = *(int *) (self + 0x58);
    v.z = *(int *) (self + 0x5c);
    v.y = data_020c904c;
    func_02091278(*(void **) (self + 0x9c), &v, 0, 0);
    return 1;
}
