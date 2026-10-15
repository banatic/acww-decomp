/* func_ov004_0223cbe8 @ 0x0223cbe8, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f818(int *, int *, int);
extern void *func_ov004_0223cc10(int, int, int, int);

void *func_ov004_0223cbe8(int a, int b, int c)
{
    int sp0;
    int sp4;

    func_0204f818(&sp0, &sp4, b);
    return func_ov004_0223cc10(a, sp0, sp4, c);
}
