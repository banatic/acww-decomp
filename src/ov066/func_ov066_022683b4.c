/* func_ov066_022683b4 @ 0x022683b4, 0x38 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

int func_ov066_022683b4(unsigned char *a, unsigned char *b)
{
    int i = 0;
    do {
        if (a[i] > b[i]) {
            return 1;
        }
        if (a[i] < b[i]) {
            return -1;
        }
        i++;
    } while (i < 6);
    return 0;
}
