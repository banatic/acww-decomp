/* func_ov004_0222820c @ 0x0222820c, 0xa4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_022282bc(void *dst, int b);
extern void func_ov004_022282b8(void *dst, unsigned char b);
extern void func_020109a0(void *self, int a, int b, int c);
extern void func_02056fcc(void *p, unsigned int h, int a, int b, unsigned short g);
extern int func_02073908(int a, int b);
extern void func_ov004_0223b334(void *p, short a);
extern int data_020ccf94;
void func_ov004_0222820c(unsigned char *self, unsigned char *p)
{
    int b, k;
    unsigned int h;
    b = *(int *) (p + 0xc);
    func_ov004_022282bc(self + 0x7d4, b);
    func_ov004_022282b8(self + 0x8f0, (unsigned char) b);
    switch (*(int *) (p + 0xc)) {
        case 0:
            k = 0x38;
            break;
        case 1:
            k = 0x39;
            break;
        case 2:
            k = 0x3a;
            break;
    }
    func_020109a0(self, k, 3, 0);
    h = (unsigned int) (*(int *) (self + 0x2d4) << 4) >> 16;
    func_02056fcc(self + 0x2d0, h, 3, 0x1000, (unsigned short) (h - 1));
    if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) == 0) {
        func_ov004_0223b334(self + 0x5c, *(short *) (self + 0x8e));
    }
}
