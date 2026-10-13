/* func_020b73fc @ 0x020b73fc, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern int func_ov004_0221b27c(int a, int flag);

int func_020b73fc(int a)
{
    int flag;
    int result;

    if (data_020e54a8 == 1) {
        flag = 1;
    } else {
        flag = 0;
    }

    if (flag != 0) {
        result = func_ov004_0221b27c(a, flag);
    } else {
        result = 0;
    }

    return result;
}
