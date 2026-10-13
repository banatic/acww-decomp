/* func_02012444 @ 0x02012444, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02012464(unsigned short *a, unsigned short *b, int c, int d);

void func_02012444(unsigned short *p, int b, int c)
{
    if (p[0] != 0xFFF1) {
        func_02012464(p, p, b, c);
    }
}
