/* func_ov068_02273030 @ 0x02273030, 0x58 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *data_ov068_022787fc;
extern int func_ov004_0222c3c4(void *p, int a);
extern void func_02055060(void *p, int a, int b, int c, int d, int e);

int func_ov068_02273030(void)
{
    int temp;
    if (data_ov068_022787fc) {
        data_ov068_022787fc[0x430] = 1;
        temp = func_ov004_0222c3c4((char *) data_ov068_022787fc + 0x388, 0);
        func_02055060((char *) data_ov068_022787fc + 0x2d0, temp, 1, 0x1000, 0, 0);
        return 1;
    } else {
        return 0;
    }
}
