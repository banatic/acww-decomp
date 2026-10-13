/* func_ov105_0229e728 @ 0x0229e728, 0x94 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov105_0229d1c4(unsigned char *);
extern void func_ov105_0229d390(unsigned char *);
extern int func_ov105_0229d69c(unsigned char *, int, int, int);
extern int func_ov105_0229d468(unsigned char *, int);
extern int func_ov105_0229d650(unsigned char *, int);
extern void func_ov105_0229d82c(unsigned char *, unsigned char, int);
extern void func_ov105_0229d354(unsigned char *, int);
extern void func_ov105_0229db14(unsigned char *);
extern void func_ov094_022999d8(int);
extern unsigned char data_021fbdd8;

void func_ov105_0229e728(unsigned char *self)
{
    unsigned int r4;
    int x;
    int y;

    func_ov105_0229d1c4(self);
    func_ov105_0229d390(self);
    r4 = *(unsigned int *) (self + 0xac) + 8;
    x = func_ov105_0229d69c(self, r4, *(unsigned int *) (self + 0xb0) + 0x18, 0);

    if (x == 0x40) {
        goto x_eq_0x40;
    }

    if (data_021fbdd8 != 0) {
        goto flag_nonzero;
    }

    if (func_ov105_0229d468(self, x) != 0) {
        goto call_d82c;
    }

    y = func_ov105_0229d650(self, x);
    if (y != 0) {
        goto ext_block;
    }

call_d82c:
    func_ov105_0229d82c(self, self[0x2b7], r4);
    return;

ext_block:
    func_ov094_022999d8(y);
    func_ov105_0229db14(self);
    return;

flag_nonzero:
    func_ov105_0229d354(self, x);
    return;

x_eq_0x40:
    if (data_021fbdd8 != 0) {
        return;
    }
    func_ov105_0229d82c(self, self[0x2b7], r4);
    return;
}
