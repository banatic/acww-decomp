/* func_ov004_022458dc @ 0x022458dc, 0x50 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0222c110(int, int);
extern void func_0208e508(void *, int);
extern void *func_0208e260(void *);
void func_ov004_022458dc(char *self)
{
    int a = 0;
    unsigned char v = *(unsigned char *) (self + 0x31c);
    unsigned char i;
    if (v == 0 || v == 2) {
        a = 1;
    }
    func_ov004_0222c110(a, 1);
    func_0208e508(self + 0x50, 0);
    for (i = 0; i < 5; i++) {
        func_0208e260(self + 0x9c + (i << 7));
    }
    *(short *) (self + 0x324) = 0x19;
}
