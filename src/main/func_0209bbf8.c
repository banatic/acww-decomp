/* func_0209bbf8 @ 0x0209bbf8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209bc94(unsigned int param);

int func_0209bbf8(unsigned int param)
{
    int ret = 2;
    if (func_0209bc94(param) == 1) {
        if (param < 19) {
            ret = 0;
        } else if (param < 20) {
            ret = 1;
        }
    }
    return ret;
}
