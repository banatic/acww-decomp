/* func_ov105_0229d7d4 @ 0x0229d7d4, 0x20 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209a1e8(void);

int func_ov105_0229d7d4(void)
{
    int result;
    int ret;

    result = func_0209a1e8();
    if (result == -1) {
        ret = 0x40;
    } else {
        ret = (unsigned char) (result + 0x1a);
    }
    return ret;
}
