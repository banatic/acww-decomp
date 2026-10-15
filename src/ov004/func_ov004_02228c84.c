/* func_ov004_02228c84 @ 0x02228c84, 0x90 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200dc8c(void *self);
extern int func_0200dc48(void *self);
extern int func_02064558(short v);
extern int func_ov004_0223c40c(void *p, short a);
extern int func_ov004_0223c3b8(void *p, short a);
extern int func_ov004_0223c364(void *p, short a);
extern int func_ov004_02228a3c(void *self, int a, int b, int c);

void func_ov004_02228c84(char *self)
{
    if (func_0200dc8c(self) > 0) {
        switch (func_02064558((short) (*(short *) (self + 0x8e) - func_0200dc48(self)))) {
            case 0:
                if (func_ov004_0223c40c(self + 0x5c, *(short *) (self + 0x8e)) != 0) {
                    func_ov004_02228a3c(self, 0, 6, -1);
                }
                break;
            case 3:
                if (func_ov004_0223c3b8(self + 0x5c, *(short *) (self + 0x8e)) != 0) {
                    func_ov004_02228a3c(self, 1, 6, -1);
                }
                break;
            case 1:
                if (func_ov004_0223c364(self + 0x5c, *(short *) (self + 0x8e)) != 0) {
                    func_ov004_02228a3c(self, 2, 6, -1);
                }
                break;
        }
    }
}
