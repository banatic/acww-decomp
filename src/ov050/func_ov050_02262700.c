/* func_ov050_02262700 @ 0x02262700, 0x34 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_020154b4(void *a, unsigned short *b, int c, int d, int e);

void func_ov050_02262700(void *p, int event)
{
    int zero;
    unsigned short hw;
    hw = 0x1564;
    zero = 0;
    func_020154b4(p, &hw, 2, 5, zero);
    *((char *) ((char *) *(char **) ((char *) p + 0xb4) + 0x73e)) = 0;
}
