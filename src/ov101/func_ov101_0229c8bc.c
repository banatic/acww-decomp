/* func_ov101_0229c8bc @ 0x0229c8bc, 0x50 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov101_0229c878(unsigned char *);
extern int func_ov101_0229c868(unsigned char *);
extern void func_ov101_0229c680(unsigned char *);
extern void func_ov002_0220a0b4(unsigned char *, int, int);
extern void func_ov002_0220a374(unsigned char *, int);

void func_ov101_0229c8bc(unsigned char *self)
{
    int a, b;

    a = func_ov101_0229c878(self);
    b = func_ov101_0229c868(self);
    func_ov002_0220a0b4(self + 0x229c, a, b);
    if (self[0xb3] == 15) {
        func_ov002_0220a374(self + 0x229c, 7);
    } else {
        func_ov002_0220a374(self + 0x229c, 1);
    }
    func_ov101_0229c680(self);
}
