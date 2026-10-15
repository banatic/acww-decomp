/* func_ov004_0222a94c @ 0x0222a94c, 0xa8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200f290(void *self, int a);
extern int func_ov004_0223badc(int a);
extern unsigned int *func_0200f27c(void *self, int a);
extern int _s32_div_f(int a, int b);
extern void func_0200f268(void *self, int a);
extern void func_0200f650(void *self, int a);

void func_ov004_0222a94c(char *self)
{
    int *q;
    int t;
    unsigned int v;

    if (func_0200f290(self, 0xd) == 0) {
        q = (int *) (self + 0x7d4);
        if (*q < 0) {
            return;
        }
        if (func_ov004_0223badc(*q) == 0) {
            return;
        }
        func_0200f27c(self, 0xd);
        *q = -1;
    }
    if (*(int *) (self + 0x704) != 0x19) {
        *(int *) (self + 0x830) = 0;
        *(int *) (self + 0x834) = 0;
        *(int *) (self + 0x838) = 0;
        return;
    }
    v = (unsigned int) (*(int *) (self + 0x2d8) << 4) >> 16;
    if (v < 8) {
        return;
    }
    t = 0x1000 - _s32_div_f((v - 8) << 12, 7);
    if (t < 0) {
        t = 0;
        func_0200f268(self, 0xd);
    }
    *(int *) (self + 0x830) = t;
    *(int *) (self + 0x834) = t;
    *(int *) (self + 0x838) = t;
    func_0200f650(self, t);
}
