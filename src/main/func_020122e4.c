/* func_020122e4 @ 0x020122e4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02012304(void *p1, void *p2, int a, int b);

void func_020122e4(unsigned short *p, int a, int b)
{
    if (*p != 0xfff1) {
        func_02012304(p, p, a, b);
    }
}
