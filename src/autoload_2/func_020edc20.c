/* func_020edc20 @ 0x020edc20, 0x38 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int (*data_021fcfe8)(int);
int func_020edc20(int arg)
{
    if (data_021fcfe8 == 0) {
        return 2;
    }
    return data_021fcfe8(arg);
}
