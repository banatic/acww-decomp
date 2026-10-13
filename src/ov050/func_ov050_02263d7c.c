/* func_ov050_02263d7c @ 0x02263d7c, 0x40 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201c2c8(int, int);
extern void func_02019d0c(int, int, int, int, int, int, int, int, int, int, int);
extern unsigned short data_020c80f8;

int func_ov050_02263d7c(int arg0)
{
    int ret = func_0201c2c8(arg0, 4);
    func_02019d0c(arg0 + 0x564, 3, 1, 0, 0, 0, ret, 0, 0, data_020c80f8, 0);
    return 1;
}
