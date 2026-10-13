/* func_02054740 @ 0x02054740, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02054a94(unsigned int, unsigned int);
extern void func_02054a64(unsigned int, unsigned int);

void func_02054740(unsigned int a, unsigned int b, unsigned int c)
{
    while (b <= c) {
        func_02054a94(a, b);
        func_02054a64(a, b);
        b++;
    }
}
