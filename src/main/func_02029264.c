/* func_02029264 @ 0x02029264, 0x4e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02015ea0(int a, int b, int c);
extern void func_02015fb0(int a, int b, int c, int d, int e, int f);

void func_02029264(int a, unsigned char *p)
{
    unsigned int b2;
    b2 = p[2];
    if (b2 >= 12) {
        b2 -= 12;
    }
    if (b2 == 0) {
        b2 = 12;
    }
    func_02015ea0(a, p[3], 0);
    func_02015fb0(a, b2, 1, 2, 0, 0);
    func_02015fb0(a, p[1], 2, 2, 6, 9);
}
