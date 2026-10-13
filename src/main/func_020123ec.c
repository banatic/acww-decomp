/* func_020123ec @ 0x020123ec, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201240c(unsigned short *, unsigned short *, int, int);

void func_020123ec(unsigned short *p, int a, int b)
{
    if (*p != 0xfff1) {
        func_0201240c(p, p, a, b);
    }
}
