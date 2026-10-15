/* func_ov102_0229d4ac @ 0x0229d4ac, 0x1e bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_02099fe8(void);

int func_ov102_0229d4ac(void *receiver)
{
    int result;
    int ret;

    result = func_02099fe8();
    if (result == -1) {
        ret = 0x25;
    } else {
        ret = (unsigned char) result;
    }
    return ret;
}
