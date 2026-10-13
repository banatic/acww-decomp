/* func_02051f4c @ 0x02051f4c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f818(int *, int *, int);
extern void func_02051f74(int, int, int, int);

void func_02051f4c(int a, int b, int c)
{
    int sp0;
    int sp4;

    func_0204f818(&sp0, &sp4, b);
    func_02051f74(a, sp0, sp4, c);
}
