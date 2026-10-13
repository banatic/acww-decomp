/* func_02014e2c @ 0x02014e2c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201596c(int a, int b);

int func_02014e2c(int arg0)
{
    int result = 0;

    if (func_0201596c(arg0, 8) != 0) {
        result = 1;
    }

    return result;
}
