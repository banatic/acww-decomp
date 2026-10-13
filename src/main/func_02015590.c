/* func_02015590 @ 0x02015590, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201596c(int param1, int param2);

int func_02015590(int param1, int param2)
{
    int result;
    int *ptr;

    if (func_0201596c(param1, 2) != 0) {
        ptr = (int *) (param1 + 0xa8);
        *ptr = param2;
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
