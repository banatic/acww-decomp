/* func_0205db80 @ 0x0205db80, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e9b9c(void *p);
extern void *data_021c9ad4;

void func_0205db80(void **arr)
{
    int i;

    for (i = 0; i < 9; i++) {
        if (arr[i] != 0) {
            func_020e9b9c(arr[i]);
            arr[i] = 0;
        }
    }
    if (data_021c9ad4 != 0) {
        func_020e9b9c(data_021c9ad4);
    }
}
