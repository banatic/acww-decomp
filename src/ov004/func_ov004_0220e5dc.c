/* func_ov004_0220e5dc @ 0x0220e5dc, 0x3e bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0220ff4c(void *self, int *p, int a);
extern void func_ov004_0220fefc(void *self, int *p);
extern void func_ov004_0220e61c(void *self, int *p);

void func_ov004_0220e5dc(char *self, int a)
{
    int t0[3];
    int t1[3];
    int out[3];
    int y;

    func_ov004_0220ff4c(self, t0, a);
    func_ov004_0220fefc(self, t1);
    y = *(int *) (self + 0x60);
    out[0] = (t0[0] + t1[0]) >> 1;
    out[1] = y;
    out[2] = (t0[2] + t1[2]) >> 1;
    func_ov004_0220e61c(self, out);
}
