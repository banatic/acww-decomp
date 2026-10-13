/* func_ov003_02231104 @ 0x02231104, 0x168 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

extern void func_ov003_0223597c(Vec3 *d, int ang);
extern int func_020644cc(int a);
extern int FX_MulFunc(int a, int b);
extern int FX_Div(int a, int b);

void func_ov003_02231104(unsigned char *self)
{
    Vec3 *hi;
    Vec3 *lo;
    Vec3 v[2];
    short ang;
    unsigned char flag;
    Vec3 *p;

    hi = (Vec3 *) (self + 0x1bc);
    lo = (Vec3 *) (self + 0x1b0);
    ang = *(short *) (self + 0x23a);
    flag = self[0x24b];
    v[0].x = 0;
    v[0].y = 0;
    v[0].z = 0;
    p = (Vec3 *) (self + 0x204);
    v[1].x = p->x;
    v[1].y = p->y;
    v[1].z = p->z;
    if (func_020644cc(0x64) > 0x50) {
        if (self[0x24f] % 0x14 == 0) {
            if (flag == 0) {
                flag = 1;
            } else {
                flag = 0;
            }
            self[0x24b] = flag;
        }
        if (flag != 0) {
            if (*(signed char *) (self + 0x24d) == 0x33) {
                ang = (short) (ang + (short) *(int *) (self + 0x21c));
            } else {
                ang = (short) (ang + 0xaaa);
            }
        } else {
            if (*(signed char *) (self + 0x24d) == 0x33) {
                ang = (short) (ang + 0xaaa);
            } else {
                ang = (short) (ang - (short) *(int *) (self + 0x21c));
            }
        }
    }
    func_ov003_0223597c(&v[0], ang);
    *(short *) (self + 0x23a) = ang;
    p->z = p->z + FX_Div(FX_MulFunc(self[0x257] << 12, v[0].z), 0x20000);
    p->x = p->x + FX_Div(FX_MulFunc(self[0x257] << 12, v[0].x), 0x20000);
    if (p->x < lo->x || p->x > hi->x) {
        p->x = v[1].x;
    }
    if (p->z < lo->z || p->z > hi->z) {
        p->z = v[1].z;
    }
    if (*(signed char *) (self + 0x24d) != 0x33) {
        if (p->z != v[1].z) {
            p->y = p->y - (p->z - v[1].z);
        }
        if (p->y < lo->y && p->y > hi->y) {
            p->y = v[1].y;
        }
    }
}
