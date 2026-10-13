/* func_020267d0 @ 0x020267d0, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202d190(void *a, int b, int c, unsigned char d);

void func_020267d0(unsigned short *a, unsigned char *b)
{
    *a = 0xFFF1;
    if (func_0202d190(a, 0, 1, b[4]) == 0) {
        func_0202d190(a, 2, 4, b[4]);
    }
}
