/* func_ov004_022264c8 @ 0x022264c8, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_02225de0(void *self, int *t, int *p, int *t0);

void func_ov004_022264c8(void *self)
{
    int t0, t[3];
    int *p = (int *) ((char *) self + 0x7d4);
    t0 = p[4];
    t[0] = p[0];
    t[1] = p[1];
    t[2] = p[2];
    func_ov004_02225de0(self, t, p + 3, &t0);
}
