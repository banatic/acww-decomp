/* func_ov004_02228344 @ 0x02228344, 0x78 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_022283c8(void *dst, int b);
extern void func_ov004_022283c4(void *dst, int b);
extern void func_020109fc(void *self, int a, int b, int c);
extern int func_02073908(int a, int b);
extern void func_ov004_0223b338(void *p, short a);
extern int data_020ccf94;
void func_ov004_02228344(unsigned char *self, unsigned char *p)
{
    int b, k;
    b = *(unsigned char *) (p + 0xc);
    func_ov004_022283c8(self + 0x7d4, b);
    func_ov004_022283c4(self + 0x8f0, b);
    switch (*(unsigned char *) (p + 0xc)) {
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
    func_020109fc(self, k, 3, 0);
    if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) == 0) {
        func_ov004_0223b338(self + 0x5c, *(short *) (self + 0x8e));
    }
}
