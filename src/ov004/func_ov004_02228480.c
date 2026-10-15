/* func_ov004_02228480 @ 0x02228480, 0x90 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int *func_0200f27c(void *self, int a);
extern void func_020109a0(void *self, int a, int b, unsigned short d);
extern int func_02073908(int a, int b);
extern int func_ov004_0223b33c(void *p, short a);
extern int data_020ccf94;
void func_ov004_02228480(unsigned char *self)
{
    int s, k, n;
    s = *(int *) (self + 0x704);
    if (s == 0x1a || s == 0) {
        n = ((unsigned int) (*(int *) (self + 0x2d8) << 4) >> 16) == 0 ? 1 : 0;
        if (n < 6) {
            func_0200f27c(self, 2);
            switch (*(unsigned char *) (self + 0x7de)) {
                case 0:
                    k = 0x3b;
                    break;
                case 1:
                    k = 0x3c;
                    break;
                case 2:
                    k = 0x3d;
                    break;
            }
            func_020109a0(self, k, 3, 0);
            if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) == 0) {
                func_ov004_0223b33c(self + 0x5c, *(short *) (self + 0x8e));
            }
        }
    }
}
