/* func_02036830 @ 0x02036830, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02036830(void *param);

void func_02036830(void *param)
{
    unsigned char *p = (unsigned char *) param;
    unsigned short *s = (unsigned short *) ((unsigned char *) param + 0xa);

    p[8] = 0x3f;
    *s = 0xffff;
    p[0xc] = 0;
    p[0xd] = 0;
    p[0xe] = 0;
    p[0xf] = 0;
    p[0x10] = 0;
}
