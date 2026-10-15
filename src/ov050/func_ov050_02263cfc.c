/* func_ov050_02263cfc @ 0x02263cfc, 0x40 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019d0c(void *a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k);
extern unsigned short data_020c80f8;

int func_ov050_02263cfc(void *p)
{
    *(unsigned char *) ((char *) p + 0x73d) = 0x32;
    func_02019d0c((char *) p + 0x564, 1, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
