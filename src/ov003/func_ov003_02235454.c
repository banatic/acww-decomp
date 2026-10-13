/* func_ov003_02235454 @ 0x02235454, 0xc4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

extern void func_02034270(int *st, Vec3 *v, int a, int b);
extern void func_020042a0(void *p, int a);
extern void func_020912d4(int a, Vec3 *v, int b, int c);
extern void func_0203423c(int *st);

int func_ov003_02235454(char *self)
{
    Vec3 v;
    int st[17];
    int *p;

    p = (int *) (self + 0x204);
    v.x = p[0];
    v.y = p[1];
    v.z = p[2];
    func_02034270(st, &v, 0, 1);
    if (st[12] != 0) {
        v.y = st[15] + 0x100;
        func_020042a0(self + 0x174, 0x7e5);
        switch (*(signed char *) (self + 0x24d)) {
            case 0xc:
            case 0xd:
            case 0x1e:
            case 0x1f:
                func_020912d4(0x13, &v, 0, 0);
                break;
            case 0x36:
            case 0x37:
                func_020912d4(0x14, &v, 0, 0);
                break;
            default:
                func_020912d4(0x12, &v, 0, 0);
                break;
        }
        func_0203423c(st);
        return 1;
    }
    func_0203423c(st);
    return 0;
}
