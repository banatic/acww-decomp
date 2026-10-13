/* func_ov112_0229f900 @ 0x0229f900, 0x2c bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov112_0229fe70(void *p, int a);

int func_ov112_0229f900(unsigned char *p0)
{
    if ((func_ov112_0229fe70(p0, 0x100) == 0) || (p0[0xbe] == p0[0xbf])) {
        return 0;
    }
    return 1;
}
