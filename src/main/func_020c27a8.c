/* func_020c27a8 @ 0x020c27a8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(int);

int func_020c27a8(int arg0)
{
    int result;
    int ret;

    result = func_02014868(arg0 + 0x618);
    if (result == 0) {
        ret = 1;
    } else {
        ret = 0;
    }
    return ret;
}
