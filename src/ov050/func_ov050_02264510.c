/* func_ov050_02264510 @ 0x02264510, 0x34 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern void func_02019d0c(void *p, int, int, int, int, int, int, int, int, int, int);

int func_ov050_02264510(void *param)
{
    func_02019d0c((char *) param + 0x564, 1, 1, 0, 0, 0, 0, 0, 0, (int) data_020c80f8, 0);
    return 1;
}
