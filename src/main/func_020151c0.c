/* func_020151c0 @ 0x020151c0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201596c(int arg0, int arg1);

int func_020151c0(int arg)
{
    int ret = 0;
    if (func_0201596c(arg, 5) != 0) {
        ret = 1;
    }
    return ret;
}
