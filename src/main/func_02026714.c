/* func_02026714 @ 0x02026714, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202d190(void *, int, int, unsigned char);

void func_02026714(unsigned short *out, unsigned char *in)
{
    *out = 0xfff1;
    if (func_0202d190(out, 3, 4, in[4]) == 0) {
        func_0202d190(out, 0, 2, in[4]);
    }
}
