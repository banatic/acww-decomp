/* func_02014f60 @ 0x02014f60, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201596c(int, int);

int func_02014f60(int arg)
{
    int result;
    result = 0;
    if (func_0201596c(arg, 7) != 0) {
        result = 1;
    }
    return result;
}
