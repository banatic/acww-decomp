/* func_ov004_0223ce18 @ 0x0223ce18, 0x46 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_ov004_0223c130(void);

int func_ov004_0223ce18(int *arr, int val)
{
    unsigned int i = 0;
    while (i < func_ov004_0223c130()) {
        int t = arr[i];
        if (t == val) {
            return 1;
        }
        i++;
    }
    i = 0;
    while (i < func_ov004_0223c130()) {
        int t = arr[i];
        if (t == 0) {
            arr[i] = val;
            return 1;
        }
        i++;
    }
    return 0;
}
