/* func_ov074_02279668 @ 0x02279668, 0x38 bytes, Thumb, module ov074
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c67a4;
extern int data_021c67d0[3];
extern int func_ov074_022796a0(void *p, int *arr, void *base);

int func_ov074_02279668(void *p)
{
    void *base = (char *) p + 0x5c;
    int result = 0;
    if (data_021c67a4 != 0) {
        int arr[3];
        arr[0] = data_021c67d0[0];
        arr[1] = data_021c67d0[1];
        arr[2] = data_021c67d0[2];
        result = func_ov074_022796a0(p, arr, base);
    }
    return result;
}
