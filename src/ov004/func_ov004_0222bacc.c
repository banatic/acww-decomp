/* func_ov004_0222bacc @ 0x0222bacc, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010d88(void *self, int *t, int a, int b);
extern void func_02089fc8(void *p);

void func_ov004_0222bacc(void *self)
{
    int t[4];
    int *p;

    p = (int *) ((char *) self + 0x7d4);
    t[0] = p[0];
    t[1] = p[1];
    t[2] = p[2];
    func_02010d88(self, t, 0x1000, 0x1000);
    func_02089fc8((char *) self + 0x1c4);
}
