/* func_02034858 @ 0x02034858, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern short data_020c9f0c[];
extern short data_020c9f04[];
extern void func_0203488c(int param, unsigned char idx, short a, short b);

void func_02034858(int param)
{
    unsigned char i;
    for (i = 0; i < 3; i++) {
        func_0203488c(param, i, data_020c9f0c[i], data_020c9f04[i]);
    }
}
