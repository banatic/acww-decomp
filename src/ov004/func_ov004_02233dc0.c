/* func_ov004_02233dc0 @ 0x02233dc0, 0x58 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
extern void *func_0204c63c(void *);
extern int func_ov004_02233e18(void *, void *, Vec3 *, Vec3 *, short, short, short);

void func_ov004_02233dc0(void *self, unsigned short id, Vec3 *a, Vec3 *b, short p5, short p6, short p7)
{
    volatile unsigned short t = 0xfff1;
    Vec3 va, vb;
    void *r;
    t = id;
    va.x = a->x;
    va.y = a->y;
    va.z = a->z;
    vb.x = b->x;
    vb.y = b->y;
    vb.z = b->z;
    r = func_0204c63c((void *) &t);
    func_ov004_02233e18(self, r, &va, &vb, p5, p6, p7);
}
