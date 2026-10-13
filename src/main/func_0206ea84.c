/* func_0206ea84 @ 0x0206ea84, 0x3a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned long long func_02136778(long long x, int y);

void func_0206ea84(unsigned long long *out, const unsigned char *in)
{
    int i = 0;
    *out = 0;
    do {
        *out |= func_02136778(in[i] & 0xf, i * 4);
        i++;
    } while (i < 16);
}
