/* func_020265c0 @ 0x020265c0, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202cbdc(void *p, int a, int b, unsigned char c, unsigned char d);

void func_020265c0(unsigned short *out, unsigned char *in)
{
    *out = 0xFFF1;
    if (func_0202cbdc(out, 3, 4, in[4], in[3]) != 0) {
        return;
    }
    func_0202cbdc(out, 0, 2, in[4], in[3]);
}
