/* func_020edbec @ 0x020edbec, 0x34 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern void (*data_021fcfec)(int);

void func_020edbec(int arg)
{
    if (data_021fcfec == 0) {
        return;
    }
    data_021fcfec(arg);
}
