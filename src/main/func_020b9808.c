/* func_020b9808 @ 0x020b9808, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b9834(short *p, void *q, signed char c);

void func_020b9808(short *p, void *q, signed char *s)
{
    while (*s != 0) {
        func_020b9834(p, q, *s++);
        p++;
    }
}
