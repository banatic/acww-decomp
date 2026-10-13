/* func_02060ee0 @ 0x02060ee0, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02060f30(int);
int func_02060ee0(int a, int b)
{
    int ret = 0;
    if (func_02060f30(b)) {
        ret = a + b * 0x450;
    }
    return ret;
}
