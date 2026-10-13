/* func_ov004_02226920 @ 0x02226920, 0x88 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int FX_MulFunc(int a, int b);
extern void func_020109c8(void *self, int a, int b, int c);
extern void func_02054860(void *p);
extern void func_0200f95c(void *self);

void func_ov004_02226920(char *self)
{
    int v;
    int n;

    v = *(int *) (self + 0x98);
    n = FX_MulFunc(v, 0x3ae1);
    if (n < 0x800) {
        n = 0x800;
    }
    if (n <= *(int *) (self + 0x2d4)) {
        *(int *) (self + 0x2e0) = n;
    }
    if (v > 0x53f) {
        if (*(int *) (self + 0x704) != 2) {
            func_020109c8(self, 2, 3, 0);
        }
    } else {
        if (*(int *) (self + 0x704) != 1) {
            func_020109c8(self, 1, 3, 0);
        }
    }
    func_02054860(self + 0x234);
    func_0200f95c(self);
}
