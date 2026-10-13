/* func_ov068_0226fd28 @ 0x0226fd28, 0x58 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov068_0226fd28(int param);

int func_ov068_0226fd28(int param)
{
    if (param < 0x99a) {
        return 3;
    }
    if (param < 0xb33) {
        return 2;
    }
    if (param < 0xccd) {
        return 1;
    }
    if (param < 0xe66) {
        return 0;
    }
    if (param < 0x1000) {
        return 1;
    }
    if (param < 0x119a) {
        return 2;
    }
    return 3;
}
