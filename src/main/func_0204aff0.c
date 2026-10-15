/* func_0204aff0 @ 0x0204aff0, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f800(int *, int *, int, int, int, int);
extern void func_0204a25c(int, int, int, int, int);

void func_0204aff0(int u0, int p1, int p2, int p3, int p4)
{
    int l1, l2;
    int hi, lo;

    hi = p4 % 16;
    lo = p4 / 16;
    func_0204f800(&l1, &l2, p2, p3, hi, lo);
    func_0204a25c(p1, l1, l2, 0xfff1, 0);
}
