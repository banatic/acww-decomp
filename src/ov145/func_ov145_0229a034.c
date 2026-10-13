/* func_ov145_0229a034 @ 0x0229a034, 0x24 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov145_0229a058(char *a, char *b, int c, int d);

void func_ov145_0229a034(char *p)
{
    *(unsigned short *) (p + 0xbe) = func_ov145_0229a058(p, p + 0xb44, 0x450c, 0x34);
}
