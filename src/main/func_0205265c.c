/* func_0205265c @ 0x0205265c, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern int func_ov004_0220e758(unsigned int a0, unsigned int *a1, unsigned int *a2, int a3, int a4);
extern int func_ov004_0220fd8c(unsigned int a0);
extern int func_020525a4(unsigned int a0, unsigned int a1, int a2, int a3, int a4, int a5, int a6);

int func_0205265c(unsigned int a0, int a1, int a2, int a3)
{
    unsigned int var_c, var_10;
    unsigned int flag = (data_020e54a8 == 1) ? 1 : 0;

    if (flag != 0) {
        if (func_ov004_0220e758(a0, &var_c, &var_10, 0, 0) != 0) {
            return func_020525a4(var_c, var_10, func_ov004_0220fd8c(a0), a1, a2, a3, 1);
        }
    }
    return 0;
}
