/* func_ov003_02220268 @ 0x02220268, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_ov003_0223cef0[];

int func_ov003_02220268(unsigned int value)
{
    unsigned int i;
    for (i = 0; i < 0x20; i++) {
        if (data_ov003_0223cef0[i] == 0) {
            data_ov003_0223cef0[i] = value;
            return 1;
        }
    }
    return 0;
}
