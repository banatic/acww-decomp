/* func_02006530 @ 0x02006530, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201108c(int a, int b);
extern unsigned char data_020c77d0[];

void func_02006530(int a, int b, int c)
{
    if (c != 0) {
        b = 1;
    } else {
        b = data_020c77d0[b];
    }
    if (b) {
        func_0201108c(a, 0);
    }
}
