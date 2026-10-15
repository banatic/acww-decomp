/* func_020b73d4 @ 0x020b73d4, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_propagation off

extern unsigned char data_020e54a8;
extern unsigned int func_ov004_0222fc84(void);

int func_020b73d4(void)
{
    int flag;
    int result;

    flag = (data_020e54a8 == 1);

    if (flag != 0) {
        result = func_ov004_0222fc84();
    } else {
        result = 0;
    }

    return result;
}
