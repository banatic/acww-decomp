/* func_ov055_02260ac8 @ 0x02260ac8, 0x28 bytes, Thumb, module ov055
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021c75b8;
extern void func_ov055_02260b24(int a, int b);

int func_ov055_02260ac8(int param)
{
    unsigned int flag = (data_021c75b8 == 2) ? 1 : 0;
    if (flag != 0) {
        func_ov055_02260b24(param, 1);
    }
    return 1;
}
