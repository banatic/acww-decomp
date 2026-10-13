/* func_ov133_0229af90 @ 0x0229af90, 0x5c bytes, Thumb, module ov133
 * mwccarm 1.2/base -O1,s
 */

extern void func_0206fdd4(unsigned char *, int, int, int, int, int);

void func_ov133_0229af90(unsigned char *p)
{
    unsigned char v, w;
    int lo, hi;
    int a, b;
    func_0206fdd4(p + 0xb94, 4, 7, 0x1b, 8, 4);
    v = p[0xa3];
    w = p[0xa2];
    if (w == v) {
        return;
    }
    if (w > v) {
        lo = v;
        hi = w;
    } else {
        lo = w;
        hi = v;
    }
    a = lo * 2 + 4;
    b = hi * 2 + 3;
    func_0206fdd4(p + 0xb94, a, 7, b, 8, 8);
}
