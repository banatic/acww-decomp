/* func_ov004_0223cde8 @ 0x0223cde8, 0x2e bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_ov004_0223c130(void);

int func_ov004_0223cde8(int *arr, int val)
{
    unsigned int i = 0;
    while (i < func_ov004_0223c130()) {
        int t = arr[i];
        if (t == val) {
            arr[i] = 0;
            return 1;
        }
        i++;
    }
    return 0;
}
