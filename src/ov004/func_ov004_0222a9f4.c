/* func_ov004_0222a9f4 @ 0x0222a9f4, 0x98 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(void *self);
extern int func_02056f28(void *p, int a);
extern int func_02008258(void *self, int a);
extern int func_0200d4e8(void *self, int a, int b, int c);
extern unsigned int *func_0200f27c(void *self, int a);

void func_ov004_0222a9f4(char *self)
{
    unsigned char *q;
    unsigned int k;
    int m;

    q = (unsigned char *) (self + 0x7d4);
    if (q[5] >= 6) {
        func_02010f5c(self);
        return;
    }
    k = q[4];
    if (k == 2) {
        if (func_02056f28(self + 0x2d0, 7) != 0) {
            *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
            func_0200d4e8(self, 3, 1, -1);
            return;
        }
    } else if (k == 0) {
        if (((unsigned int) (*(int *) (self + 0x2d8) << 4) >> 16) < 7) {
            m = *(int *) (self + 0x818);
            if (m == 2) {
                q[4] = 2;
            } else if (m == 1) {
                q[4] = 1;
                func_0200f27c(self, 0xd);
            }
        }
    }
    func_02010f5c(self);
}
