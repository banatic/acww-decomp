/* func_ov003_022360d8 @ 0x022360d8, 0x36 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_022360b8(unsigned short *p, int i, int j);

void func_ov003_022360d8(unsigned short *p, int i, int j)
{
    unsigned char s;
    unsigned char k;
    s = i & 0xf;
    k = j & 0xf;
    if (func_ov003_022360b8(p, i, j)) {
        return;
    }
    p[k] |= 1 << s;
    p[0x10]--;
}
