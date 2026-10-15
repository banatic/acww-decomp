/* func_ov048_02263508 @ 0x02263508, 0x3c bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;

extern int func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);

int func_ov048_02263508(unsigned char *p)
{
    func_02019d0c(p + 0x564, 3, 1, 0, 0, 0, *(signed short *) (p + 0xe6c), 0, 0, data_020c80f8, 0);
    return 1;
}
