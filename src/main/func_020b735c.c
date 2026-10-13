/* func_020b735c @ 0x020b735c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern int func_ov003_02236204(int a, int flag);

int func_020b735c(int a)
{
    int flag;
    int result;

    if (data_020e54a8 == 0) {
        flag = 1;
    } else {
        flag = 0;
    }

    if (flag != 0) {
        result = func_ov003_02236204(a, flag);
    } else {
        result = 0;
    }

    return result;
}
