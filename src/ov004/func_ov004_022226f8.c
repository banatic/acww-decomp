/* func_ov004_022226f8 @ 0x022226f8, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern char data_021e5a2c[];
extern int func_0207b410(char *p);
extern int func_0209a67c(int v);
int func_ov004_022226f8(void)
{
    int r;
    if (func_0209a67c(func_0207b410(data_021e5a2c)) != 0) {
        r = 1;
    } else {
        r = 0;
    }
    return r;
}
