/* func_ov003_022360b8 @ 0x022360b8, 0x1e bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

int func_ov003_022360b8(unsigned short *p, int i, int j)
{
    unsigned char s;
    unsigned char k;
    s = i & 0xf;
    k = j & 0xf;
    if ((p[k] >> s) & 1) {
        return 1;
    }
    return 0;
}
