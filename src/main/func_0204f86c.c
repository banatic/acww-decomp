/* func_0204f86c @ 0x0204f86c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char *func_020e9958(int a, int b);
extern void func_0204f89c(char *ptr);

char *func_0204f86c(int arg0, int arg1)
{
    char *result;
    int i;
    result = func_020e9958(arg1, arg0 << 4);
    if (result != 0) {
        for (i = 0; i < arg0; i++) {
            if (result + (i << 4) != 0) {
                func_0204f89c(result + (i << 4));
            }
        }
    }
    return result;
}
