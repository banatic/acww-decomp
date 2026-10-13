/* func_ov120_0229bb80 @ 0x0229bb80, 0xcc bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov120_0229abd0(unsigned char *self);
extern void func_ov120_0229ab20(unsigned char *self);
extern void func_0200284c(int a, int b, int c);
extern void func_ov120_0229a438(unsigned char *self, int v);
extern void func_ov120_0229a928(unsigned char *self);
extern int func_ov120_0229a448(unsigned char *self, int v);
extern void func_ov120_0229b548(unsigned char *self);
extern void func_ov120_0229a428(unsigned char *self, int v);
extern int func_020b9bbc(unsigned char *a, unsigned char *b, int c, int d, int e);

void func_ov120_0229bb80(unsigned char *self)
{
    if (func_ov120_0229abd0(self) != 0) {
        func_ov120_0229ab20(self);
        func_0200284c(6, 0, (int) (*(unsigned short *) (self + 0x98)) - 0x50);
        if (*(unsigned char *) (self + 0xa3) != (int) (*(unsigned short *) (self + 0x98)) >> 4) {
            func_ov120_0229a438(self, 0x80);
        }
    }
    func_ov120_0229a928(self);
    if (func_ov120_0229a448(self, 0x80) != 0) {
        func_ov120_0229b548(self);
        func_ov120_0229a428(self, 0x80);
    }
    if (func_ov120_0229a448(self, 0x20) != 0) {
        if (func_020b9bbc(self + 0xd4, self + 0x720, 4, 0x800, 0) != 0) {
            func_ov120_0229a428(self, 0x20);
        }
    }
    if (func_ov120_0229a448(self, 2) != 0) {
        if (func_020b9bbc(self + 0xb0, self + 0xf20, 6, 0x800, 0) != 0) {
            func_ov120_0229a428(self, 2);
        }
    }
}
