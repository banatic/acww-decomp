/* func_02078af0 @ 0x02078af0, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c9abc;
extern void func_020e9b9c(int);

void func_02078af0(int *arr)
{
    int local = 0;
    int r5 = data_021c9abc;
    int i;
    for (i = 0; i < 4; i++) {
        if (arr[i] != 0) {
            func_020e9b9c(arr[i]);
            arr[i] = local;
        }
    }
    if (r5 != 0) {
        func_020e9b9c(r5);
    }
}
