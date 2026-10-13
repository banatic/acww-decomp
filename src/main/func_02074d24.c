/* func_02074d24 @ 0x02074d24, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *data_020ccf94;
extern unsigned int func_0207762c(int);
extern int func_0205cb68(int, int);
extern int func_020ecf20(int);

int func_02074d24(int arg)
{
    unsigned int max = 0;
    int i = 0x45;
    unsigned int ret;

    do {
        ret = func_0207762c(i);
        if (ret > max) {
            max = ret;
        }
        i--;
    } while (i >= 0);

    data_020ccf94[0x6d] = max;
    return func_020ecf20(func_0205cb68(0x4b000, arg));
}
