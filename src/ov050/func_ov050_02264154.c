/* func_ov050_02264154 @ 0x02264154, 0x34 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern void func_02019d0c(char *a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k);

int func_ov050_02264154(char *ptr)
{
    func_02019d0c(ptr + 0x564, 0xa, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
