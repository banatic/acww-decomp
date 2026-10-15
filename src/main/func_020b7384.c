/* func_020b7384 @ 0x020b7384, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_propagation off

extern unsigned char data_020e54a8;
extern int func_ov004_0221ad40(int index);

int func_020b7384(int a)
{
    int flag;
    int result;

    flag = (data_020e54a8 == 1);

    if (flag != 0) {
        result = func_ov004_0221ad40(a);
    } else {
        result = 0;
    }

    return result;
}
