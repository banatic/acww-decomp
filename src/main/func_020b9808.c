/* func_020b9808 @ 0x020b9808, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b9834(short *p, int value, int character);

void func_020b9808(short *p, int q, const signed char *s)
{
    while (*s != 0) {
        func_020b9834(p, q, *s++);
        p++;
    }
}
