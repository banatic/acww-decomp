/* func_ov068_022724fc @ 0x022724fc, 0x34 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov068_022724fc(int param1);
extern int func_ov003_02219a64(int a, int b, int c, int d);

int func_ov068_022724fc(int param1)
{
    int result;
    int val;
    int val2;
    int val3;

    val = param1 + 0x2c0;
    val2 = param1 + 0x2c8;
    val3 = 0xffff8000;
    result = func_ov003_02219a64(1, val, val2, val3);
    if (result != 0) {
        return 1;
    } else {
        return 0;
    }
}
