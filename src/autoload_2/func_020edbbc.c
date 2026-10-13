/* func_020edbbc @ 0x020edbbc, 0x30 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int func_020edc58(int a, int b);

int func_020edbbc(int a, int b)
{
    if (b == 0) {
        return 0;
    }
    return func_020edc58(a, b + 0x14);
}
