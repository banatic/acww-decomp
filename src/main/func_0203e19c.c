/* func_0203e19c @ 0x0203e19c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203e4c0(int);
extern unsigned char *data_021c72b8;

int func_0203e19c(void)
{
    int ret;

    if (func_0203e4c0(9) == 0) {
        ret = 0;
    } else {
        data_021c72b8[0x16] = 6;
        ret = 1;
    }
    return ret;
}
