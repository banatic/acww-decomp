/* func_020b7424 @ 0x020b7424, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern int func_ov004_0220c4ac(int value);

int func_020b7424(void)
{
    int flag;
    int result;

    if (data_020e54a8 == 1) {
        flag = 1;
    } else {
        flag = 0;
    }

    if (flag != 0) {
        result = func_ov004_0220c4ac(flag);
    } else {
        result = 0;
    }

    return result;
}
